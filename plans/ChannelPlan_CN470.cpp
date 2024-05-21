/**********************************************************************
* COPYRIGHT 2016 MULTI-TECH SYSTEMS, INC.
*
* ALL RIGHTS RESERVED BY AND FOR THE EXCLUSIVE BENEFIT OF
* MULTI-TECH SYSTEMS, INC.
*
* MULTI-TECH SYSTEMS, INC. - CONFIDENTIAL AND PROPRIETARY
* INFORMATION AND/OR TRADE SECRET.
*
* NOTICE: ALL CODE, PROGRAM, INFORMATION, SCRIPT, INSTRUCTION,
* DATA, AND COMMENT HEREIN IS AND SHALL REMAIN THE CONFIDENTIAL
* INFORMATION AND PROPERTY OF MULTI-TECH SYSTEMS, INC.
* USE AND DISCLOSURE THEREOF, EXCEPT AS STRICTLY AUTHORIZED IN A
* WRITTEN AGREEMENT SIGNED BY MULTI-TECH SYSTEMS, INC. IS PROHIBITED.
*
***********************************************************************/

#include "ChannelPlan_CN470.h"
#include "limits.h"

using namespace lora;

const uint8_t ChannelPlan_CN470::CN470_TX_POWERS[] = { 17, 16, 14, 12, 10, 7, 5, 2, 0 };

// CN470 regulations limit to 1s time-on-air, this reduces DR0 and DR1
const uint8_t ChannelPlan_CN470::CN470_MAX_PAYLOAD_SIZE[] =          { 0, 23, 51, 115, 242, 242, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_CN470::CN470_MAX_PAYLOAD_SIZE_REPEATER[] = { 0, 23, 51, 115, 222, 222, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

ChannelPlan_CN470::ChannelPlan_CN470()
:
  ChannelPlan(NULL, NULL)
{
    _beaconSize = sizeof(BCNPayload);
}

ChannelPlan_CN470::ChannelPlan_CN470(Settings* settings)
:
  ChannelPlan(NULL, settings)
{
    _beaconSize = sizeof(BCNPayload);
}

ChannelPlan_CN470::ChannelPlan_CN470(SxRadio* radio, Settings* settings)
:
  ChannelPlan(radio, settings)
{
    _beaconSize = sizeof(BCNPayload);
}

ChannelPlan_CN470::~ChannelPlan_CN470() {

}

void ChannelPlan_CN470::Init() {
    _plan = CN470;
    _planName = "CN470";

    _datarates.clear();
    _channels.clear();
    _dutyBands.clear();

    DutyBand band;

    band.Index = 0;
    band.DutyCycle = 0;

    Datarate dr;

    _maxTxPower = 30;
    _minTxPower = 0;

    _minFrequency = CN470_FREQ_MIN;
    _maxFrequency = CN470_FREQ_MAX;

    TX_POWERS = CN470_TX_POWERS;
    MAX_PAYLOAD_SIZE = CN470_MAX_PAYLOAD_SIZE;
    MAX_PAYLOAD_SIZE_REPEATER = CN470_MAX_PAYLOAD_SIZE_REPEATER;

    band.FrequencyMin = CN470_FREQ_MIN;
    band.FrequencyMax = CN470_FREQ_MAX;

    _freqUBase125k = CN470_125K_FREQ_BASE;
    _freqUStep125k = CN470_125K_FREQ_STEP;
    _freqDBase500k = CN470_125K_DBASE;
    _freqDStep500k = CN470_125K_DSTEP;

    _defaultRx2Frequency = CN470_FREQ_RX2;
    _defaultRx2Datarate = DR_0;

    GetSettings()->Session.Rx2Frequency = CN470_FREQ_RX2;

    GetSettings()->Session.BeaconFrequency = CN470_BEACON_FREQ_BASE;
    GetSettings()->Session.BeaconFreqHop = true;
    GetSettings()->Session.PingSlotFrequency = CN470_BEACON_FREQ_BASE;
    GetSettings()->Session.PingSlotDatarateIndex = CN470_BEACON_DR;
    GetSettings()->Session.PingSlotFreqHop = true;

    _minDatarate = CN470_MIN_DATARATE;
    _maxDatarate = CN470_MAX_DATARATE;
    _minRx2Datarate = DR_0;
    _maxRx2Datarate = DR_5;
    _minDatarateOffset = CN470_MIN_DATARATE_OFFSET;
    _maxDatarateOffset = CN470_MAX_DATARATE_OFFSET;

    _numChans125k = CN470_125K_NUM_CHANS;
    _numChans500k = CN470_500K_NUM_CHANS;

    logInfo("Initialize channels...");

    SetNumberOfChannels(CN470_125K_NUM_CHANS + CN470_500K_NUM_CHANS, false);

    dr.SpreadingFactor = SF_12;

    logInfo("Initialize datarates...");

    // Add DR0-5
    while (dr.SpreadingFactor >= SF_7) {
        AddDatarate(-1, dr);
        dr.SpreadingFactor--;
        dr.Index++;
    }

    // Skip DR6-15 RFU
    dr.SpreadingFactor = SF_INVALID;
    while (dr.Index++ <= DR_15) {
        AddDatarate(-1, dr);
    }


    band.PowerMax = 17;

    band.TimeOffEnd = 0;

    AddDutyBand(-1, band);

    GetSettings()->Session.Rx2DatarateIndex = DR_0;

    GetSettings()->Session.TxDatarate = DR_0;
    GetSettings()->Session.TxPower = GetSettings()->Network.TxPower;

    SetFrequencySubBand(GetSettings()->Network.FrequencySubBand);

}

void ChannelPlan_CN470::DefaultLBT() {
    _LBT_TimeUs = 5000;
    _LBT_Threshold = -80;
}

uint8_t ChannelPlan_CN470::HandleJoinAccept(const uint8_t* buffer, uint8_t size) {

    if (size > 17 && buffer[28] == 0x01) {
        // Channel Mask is not supported, ignore if included
    }

    uint8_t fsb = 0;

    if (_txChannel < 96)
        fsb = (_txChannel / 8);

    // Reset state of random channels to enable the last used FSB for the first tx to confirm network settings
    _randomChannel.ChannelState125K(0);
    _randomChannel.ChannelState500K(0);
    _randomChannel.MarkAllSubbandChannelsUnused(fsb);
    EnableDefaultChannels();

    return LORA_OK;
}

void ChannelPlan_CN470::SetNumberOfChannels(uint8_t channels, bool resize) {
    uint8_t newsize = ((channels - 1) / CHAN_MASK_SIZE) + 1;

    if (resize) {
        _channels.resize(channels);
    }

    _channelMask.resize(newsize, 0x0);
    _numChans = channels;

}

bool ChannelPlan_CN470::IsChannelEnabled(uint8_t channel) {
    uint8_t index = channel / CHAN_MASK_SIZE;
    uint8_t shift = channel % CHAN_MASK_SIZE;

    assert(index < _channelMask.size() * CHAN_MASK_SIZE);

    // cannot shift over 32 bits
    assert(shift < 32);

    // logDebug("index: %d shift %d cm: %04x bit: %04x enabled: %d", index, shift, _channelMask[index], (1 << shift), (_channelMask[index] & (1 << shift)) == (1 << shift));

    return (_channelMask[index] & (1 << shift)) == (1 << shift);
}

uint8_t ChannelPlan_CN470::GetMinDatarate() {
    return _minDatarate;
}

uint8_t ChannelPlan_CN470::GetMaxDatarate() {
    return _maxDatarate;
}

uint8_t ChannelPlan_CN470::SetRx1Offset(uint8_t offset) {
    GetSettings()->Session.Rx1DatarateOffset = offset;
    return LORA_OK;
}

uint8_t ChannelPlan_CN470::SetRx2Frequency(uint32_t freq) {
    GetSettings()->Session.Rx2Frequency = freq;
    return LORA_OK;
}

uint8_t ChannelPlan_CN470::SetRx2DatarateIndex(uint8_t index) {
    GetSettings()->Session.Rx2DatarateIndex = index;
    return LORA_OK;
}

uint8_t ChannelPlan_CN470::SetTxConfig() {

    uint8_t band = GetDutyBand(GetChannel(_txChannel).Frequency);
    Datarate txDr = GetDatarate(GetSettings()->Session.TxDatarate);
    int8_t max_pwr = _dutyBands[band].PowerMax;
    uint8_t chans_enabled = 0;

    int8_t pwr = GetSettings()->Session.TxPower;

    if (txDr.Bandwidth == BW_125) {

        chans_enabled += CountBits(_channelMask[0]);
        chans_enabled += CountBits(_channelMask[1]);
        chans_enabled += CountBits(_channelMask[2]);
        chans_enabled += CountBits(_channelMask[3]);
        chans_enabled += CountBits(_channelMask[4]);
        chans_enabled += CountBits(_channelMask[5]);

    }

    pwr = std::min < int8_t > (pwr, max_pwr);

    for (int i = RADIO_POWERS_SIZE; i >= 0; i--) {
        if (RADIO_POWERS[i] <= pwr) {
            pwr = i;
            break;
        }
        if (i == 0) {
            pwr = i;
        }
    }

    logInfo("Session pwr: %d ant: %d max: %d", GetSettings()->Session.TxPower, GetSettings()->Network.AntennaGain, max_pwr);
    logInfo("Radio Power index: %d output: %d total: %d", pwr, RADIO_POWERS[pwr], RADIO_POWERS[pwr] + GetSettings()->Network.AntennaGain);

    uint32_t bw = txDr.Bandwidth;
    uint32_t sf = txDr.SpreadingFactor;
    uint8_t cr = txDr.Coderate;
    uint8_t pl = txDr.PreambleLength;
    uint16_t fdev = 0;
    bool crc = P2PEnabled() ? false : txDr.Crc;
    bool iq = txDr.TxIQ;

    SxRadio::RadioModems_t modem = SxRadio::MODEM_LORA;

    if (sf == SF_FSK) {
        modem = SxRadio::MODEM_FSK;
        sf = 50e3;
        fdev = 25e3;
        bw = 0;
        crc = true;
    }

    GetRadio()->SetTxConfig(modem, pwr, fdev, bw, sf, cr, pl, false, crc, false, 0, iq, 3e3);

    logInfo("TX PWR: %u DR: %u SF: %u BW: %u CR: %u PL: %u CRC: %d IQ: %d", pwr, txDr.Index, sf, bw, cr, pl, crc, iq);

    return LORA_OK;
}


uint8_t ChannelPlan_CN470::AddChannel(int8_t index, Channel channel) {
    logTrace("Add Channel %d : %lu : %02x %d", index, channel.Frequency, channel.DrRange.Value, _channels.size());

    assert(index < (int) _channels.size());

    if (index >= 0) {
        _channels[index] = channel;
    } else {
        _channels.push_back(channel);
    }

    return LORA_OK;
}

Channel ChannelPlan_CN470::GetChannel(int8_t index) {
    Channel chan;
    memset(&chan, 0, sizeof(Channel));

    if (_channels.size() > 0) {
        chan = _channels[index];
    } else {
        if (index < 96) {
            chan.Index = index;
            chan.DrRange.Fields.Min = _minDatarate;
            chan.DrRange.Fields.Max = _maxDatarate;
            chan.Frequency = _freqUBase125k + (_freqUStep125k * index);
        }
    }

    return chan;
}

uint8_t ChannelPlan_CN470::SetFrequencySubBand(uint8_t sub_band) {

    _txFrequencySubBand = sub_band;

    if (sub_band > 0 && sub_band < 13) {
        SetChannelMask(0, 0x0000);
        SetChannelMask(1, 0x0000);
        SetChannelMask(2, 0x0000);
        SetChannelMask(3, 0x0000);
        SetChannelMask(4, 0x0000);
        SetChannelMask(5, 0x0000);
        SetChannelMask((sub_band - 1) / 2, (sub_band % 2) ? 0x00FF : 0xFF00);

    } else {
        SetChannelMask(0, 0xFFFF);
        SetChannelMask(1, 0xFFFF);
        SetChannelMask(2, 0xFFFF);
        SetChannelMask(3, 0xFFFF);
        SetChannelMask(4, 0xFFFF);
        SetChannelMask(5, 0xFFFF);
    }

    return LORA_OK;
}


void ChannelPlan_CN470::LogRxWindow(uint8_t wnd) {

#if 1 // defined(MTS_DEBUG)
    RxWindow rxw = GetRxWindow(wnd);
    Datarate rxDr = GetDatarate(rxw.DatarateIndex);
    uint8_t bw = rxDr.Bandwidth;
    uint8_t sf = rxDr.SpreadingFactor;
    uint8_t cr = rxDr.Coderate;
    uint8_t pl = rxDr.PreambleLength;
    uint16_t sto = rxDr.SymbolTimeout();
    bool crc = false; // downlink does not use CRC according to LORAWAN
    bool iq = GetTxDatarate().RxIQ;

    logTrace("RX%d on freq: %lu", wnd, rxw.Frequency);
    logTrace("RX DR: %u SF: %u BW: %u CR: %u PL: %u STO: %u CRC: %d IQ: %d", rxDr.Index, sf, bw, cr, pl, sto, crc, iq);
#endif

}

RxWindow ChannelPlan_CN470::GetRxWindow(uint8_t window, int8_t id) {
    RxWindow rxw;
    int index = 0;

    if (P2PEnabled()) {
        rxw.Frequency = GetSettings()->Network.TxFrequency;
        index = GetSettings()->Session.TxDatarate;
    } else {
        switch (window) {
        case RX_1:
            rxw.Frequency = _freqDBase500k + (_txChannel % 48) * _freqDStep500k;

            if (GetSettings()->Session.TxDatarate > GetSettings()->Session.Rx1DatarateOffset) {
                index = GetSettings()->Session.TxDatarate - GetSettings()->Session.Rx1DatarateOffset;
            } else {
                index = 0;
            }

            break;

        case RX_BEACON:
            rxw.Frequency = GetSettings()->Session.BeaconFrequency;
            index = CN470_BEACON_DR;
            break;

        case RX_SLOT:
            if (id > 0 && id < 8) {
                rxw.Frequency = GetSettings()->Multicast[id].Frequency;
                index = GetSettings()->Multicast[id].DatarateIndex;
            } else {
                rxw.Frequency = GetSettings()->Session.PingSlotFrequency;
                index = GetSettings()->Session.PingSlotDatarateIndex;
            }
            break;

        // RX2, RXC, RX_TEST, etc..
        default:
            rxw.Frequency = GetSettings()->Session.Rx2Frequency;
            index = GetSettings()->Session.Rx2DatarateIndex;
        }
    }

    rxw.DatarateIndex = index;

    return rxw;
}

uint8_t ChannelPlan_CN470::HandleRxParamSetup(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {
    status = 0x07;
    int8_t datarate = 0;
    int8_t drOffset = 0;
    uint32_t freq = 0;

    drOffset = payload[index++];
    datarate = drOffset & 0x0F;
    drOffset = (drOffset >> 4) & 0x07;

    freq = payload[index++];
    freq |= payload[index++] << 8;
    freq |= payload[index++] << 16;
    freq *= 100;

    if (!CheckRfFrequency(freq)) {
        logInfo("Freq KO");
        status &= 0xFE; // Channel frequency KO
    }

    if (datarate < _minRx2Datarate || datarate > _maxRx2Datarate) {
        logInfo("DR KO");
        status &= 0xFD; // Datarate KO
    }

    if (drOffset < 0 || drOffset > _maxDatarateOffset) {
        logInfo("DR Offset KO");
        status &= 0xFB; // Rx1DrOffset range KO
    }

    if ((status & 0x07) == 0x07) {
        logInfo("RxParamSetup accepted Rx2DR: %d Rx2Freq: %d Rx1Offset: %d", datarate, freq, drOffset);
        SetRx2DatarateIndex(datarate);
        SetRx2Frequency(freq);
        SetRx1Offset(drOffset);
    } else {
        logInfo("RxParamSetup rejected Rx2DR: %d Rx2Freq: %d Rx1Offset: %d", datarate, freq, drOffset);
    }

    return LORA_OK;
}

uint8_t ChannelPlan_CN470::HandleNewChannel(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {

    // Not Supported in CN470
    status = 0;
    return LORA_UNSUPPORTED;
}

uint8_t ChannelPlan_CN470::HandleDownlinkChannelReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {

    // Not Supported in CN470
    status = 0;
    return LORA_UNSUPPORTED;
}

uint8_t ChannelPlan_CN470::HandlePingSlotChannelReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {
    uint8_t datarate = 0;
    uint32_t freq = 0;
    bool freqHop = false;

    status = 0x03;

    freq = payload[index++];
    freq |= payload[index++] << 8;
    freq |= payload[index++] << 16;
    freq *= 100;

    datarate = payload[index] & 0x0F;

    if (freq == 0U) {
        logInfo("Received request to reset ping slot frequency to default");
        freq = CN470_BEACON_FREQ_BASE;
        freqHop = true;
    } else if (!CheckRfFrequency(freq)) {
        logInfo("Freq KO");
        status &= 0xFE; // Channel frequency KO
    }

    if (datarate < _minRx2Datarate || datarate > _maxRx2Datarate) {
        logInfo("DR KO");
        status &= 0xFD; // Datarate KO
    }

    if ((status & 0x03) == 0x03) {
        logInfo("PingSlotChannelReq accepted DR: %d Freq: %d", datarate, freq);
        GetSettings()->Session.PingSlotFrequency = freq;
        GetSettings()->Session.PingSlotDatarateIndex = datarate;
        GetSettings()->Session.PingSlotFreqHop = freqHop;
    } else {
        logInfo("PingSlotChannelReq rejected DR: %d Freq: %d", datarate, freq);
    }

    return LORA_OK;
}

uint8_t ChannelPlan_CN470::HandleBeaconFrequencyReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {
    uint32_t freq = 0;
    bool freqHop = false;

    status = 0x01;

    freq = payload[index++];
    freq |= payload[index++] << 8;
    freq |= payload[index] << 16;
    freq *= 100;

    if (freq == 0U) {
        logInfo("Received request to reset beacon frequency to default");
        freq = CN470_BEACON_FREQ_BASE;
        freqHop = true;
    } else if (!CheckRfFrequency(freq)) {
        logInfo("Freq KO");
        status &= 0xFE; // Channel frequency KO
    }

    if (status & 0x01) {
        logInfo("BeaconFrequencyReq accepted Freq: %d", freq);
        GetSettings()->Session.BeaconFrequency = freq;
        GetSettings()->Session.BeaconFreqHop = freqHop;
    } else {
        logInfo("BeaconFrequencyReq rejected Freq: %d", freq);
    }

    return LORA_OK;
}


uint8_t ChannelPlan_CN470::HandleAdrCommand(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {

    uint8_t power = 0;
    uint8_t datarate = 0;
    uint16_t mask = 0;
    uint8_t ctrl = 0;
    uint8_t nbRep = 0;

    status = 0x07;
    datarate = payload[index++];
    power = datarate & 0x0F;
    datarate = (datarate >> 4) & 0x0F;

    mask = payload[index++];
    mask |= payload[index++] << 8;

    nbRep = payload[index++];
    ctrl = (nbRep >> 4) & 0x07;
    nbRep &= 0x0F;

    if (nbRep == 0) {
        nbRep = 1;
    }

    if (datarate != 0xF && datarate > _maxDatarate) {
        status &= 0xFD; // Datarate KO
    }
    //
    // Remark MaxTxPower = 0 and MinTxPower = 14
    //
    if (power != 0xF && power > 8) {
        status &= 0xFB; // TxPower KO
    }

    switch (ctrl) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            SetChannelMask(ctrl, mask);
            break;

        case 6:
            // enable all 125 kHz channels
            SetChannelMask(0, 0xFFFF);
            SetChannelMask(1, 0xFFFF);
            SetChannelMask(2, 0xFFFF);
            SetChannelMask(3, 0xFFFF);
            SetChannelMask(4, 0xFFFF);
            SetChannelMask(5, 0xFFFF);
            break;

        case 7:
        default:
            logWarning("rejecting RFU or unknown control value %d", ctrl);
            status &= 0xFE; // ChannelMask KO
            return LORA_ERROR;
    }

    if (GetSettings()->Network.ADREnabled) {
        if (status == 0x07) {
            if (datarate != 0xF)
                GetSettings()->Session.TxDatarate = datarate;
            if (power != 0xF)
                GetSettings()->Session.TxPower = TX_POWERS[power];

            logDebug("ADR Set Redundancy %d", nbRep);
            GetSettings()->Session.Redundancy = nbRep;
        }
    } else {
        logDebug("ADR is disabled, DR and Power not changed.");
    }

    logDebug("ADR DR: %u PWR: %u Ctrl: %02x Mask: %04x NbRep: %u Stat: %02x", datarate, power, ctrl, mask, nbRep, status);

    return LORA_OK;
}

uint8_t ChannelPlan_CN470::ValidateAdrConfiguration() {
    uint8_t status = 0x07;
    uint8_t chans_enabled = 0;
    uint8_t datarate = GetSettings()->Session.TxDatarate;
    uint8_t power = GetSettings()->Session.TxPower;

    if (GetSettings()->Network.ADREnabled) {
        if (datarate > _maxDatarate) {
            logWarning("ADR Datarate KO - outside allowed range");
            status &= 0xFD; // Datarate KO
        }
        if (power < _minTxPower || power > _maxTxPower) {
            logWarning("ADR TX Power KO - outside allowed range");
            status &= 0xFB; // TxPower KO
        }
    }
    // at least 1 125kHz channels must be enabled
    chans_enabled += CountBits(_channelMask[0]);
    chans_enabled += CountBits(_channelMask[1]);
    chans_enabled += CountBits(_channelMask[2]);
    chans_enabled += CountBits(_channelMask[3]);
    chans_enabled += CountBits(_channelMask[4]);
    chans_enabled += CountBits(_channelMask[5]);

    if (chans_enabled == 0) {
        logWarning("ADR Channel Mask KO - at least 1 125kHz channel must be enabled");
        status &= 0xFE; // ChannelMask KO
    }

    return status;
}

uint32_t ChannelPlan_CN470::GetTimeOffAir()
{
    uint32_t min = 0;
    auto now = duration_cast<milliseconds>(_dutyCycleTimer.elapsed_time()).count();

    if (GetSettings()->Session.AggregatedTimeOffEnd > 0 && GetSettings()->Session.AggregatedTimeOffEnd > now) {
        min = std::max < uint32_t > (min, GetSettings()->Session.AggregatedTimeOffEnd - now);
    }

    now = time(NULL);
    uint32_t join_time = 0;

    if (GetSettings()->Session.JoinFirstAttempt != 0 && now < GetSettings()->Session.JoinTimeOffEnd) {
        join_time = (GetSettings()->Session.JoinTimeOffEnd - now) * 1000;
    }

    min = std::max < uint32_t > (join_time, min);

    return min;
}

std::vector<uint32_t> lora::ChannelPlan_CN470::GetChannels() {
    std::vector < uint32_t > chans;

    if (GetSettings()->Network.FrequencySubBand > 0) {
        uint8_t chans_per_group = 8;
        size_t start = (GetSettings()->Network.FrequencySubBand - 1) * chans_per_group;
        for (int8_t i = start; i < int8_t(start + chans_per_group); i++) {
            chans.push_back(GetChannel(i).Frequency);
        }
        chans.push_back(GetRxWindow(2).Frequency);
    } else {
        for (int8_t i = 0; i < _numChans; i++) {
            chans.push_back(GetChannel(i).Frequency);
        }
        chans.push_back(GetRxWindow(2).Frequency);
    }

    return chans;
}

std::vector<uint8_t> lora::ChannelPlan_CN470::GetChannelRanges() {
    std::vector < uint8_t > ranges;

    if (GetSettings()->Network.FrequencySubBand > 0) {
        uint8_t chans_per_group = 8;
        size_t start = (GetSettings()->Network.FrequencySubBand - 1) * chans_per_group;
        for (int8_t i = start; i < int8_t(start + chans_per_group); i++) {
            ranges.push_back(GetChannel(i).DrRange.Value);
        }
        ranges.push_back(GetRxWindow(2).DatarateIndex);
    } else {
        for (int8_t i = 0; i < _numChans; i++) {
            ranges.push_back(GetChannel(i).DrRange.Value);
        }
        ranges.push_back(GetRxWindow(2).DatarateIndex);
    }

    ranges.push_back(GetRxWindow(2).DatarateIndex);

    return ranges;

}

uint8_t ChannelPlan_CN470::SetDutyBandDutyCycle(uint8_t band, uint16_t dutyCycle) {
    return LORA_UNSUPPORTED;
}

void lora::ChannelPlan_CN470::EnableDefaultChannels() {
    SetFrequencySubBand(GetSettings()->Network.FrequencySubBand);
}

uint8_t ChannelPlan_CN470::GetNextChannel()
{
    if (GetSettings()->Session.AggregatedTimeOffEnd != 0) {
        return LORA_AGGREGATED_DUTY_CYCLE;
    }

    if (P2PEnabled() || GetSettings()->Network.TxFrequency != 0) {
        logDebug("Using frequency %d", GetSettings()->Network.TxFrequency);

        if (GetSettings()->Test.DisableDutyCycle != lora::ON) {
            int8_t band = GetDutyBand(GetSettings()->Network.TxFrequency);
            logDebug("band: %d freq: %d", band, GetSettings()->Network.TxFrequency);
            if (band != -1 && _dutyBands[band].TimeOffEnd != 0) {
                return LORA_NO_CHANS_ENABLED;
            }
        }

        GetRadio()->SetChannel(GetSettings()->Network.TxFrequency);
        return LORA_OK;
    }

    uint8_t start = 0;
    uint8_t maxChannels = _numChans125k;
    uint8_t nbEnabledChannels = 0;
    uint8_t *enabledChannels = new uint8_t[maxChannels];


    // Search how many channels are enabled
    DatarateRange range;
    uint8_t dr_index = GetSettings()->Session.TxDatarate;
    auto now = duration_cast<milliseconds>(_dutyCycleTimer.elapsed_time()).count();

    for (size_t i = 0; i < _dutyBands.size(); i++) {
        if (_dutyBands[i].TimeOffEnd < now || GetSettings()->Test.DisableDutyCycle == lora::ON) {
            _dutyBands[i].TimeOffEnd = 0;
        }
    }

    for (uint8_t i = start; i < start + maxChannels; i++) {
        range = GetChannel(i).DrRange;
        // logDebug("chan: %d freq: %d range:%02x", i, GetChannel(i).Frequency, range.Value);

        if (IsChannelEnabled(i) && (dr_index >= range.Fields.Min && dr_index <= range.Fields.Max)) {
            int8_t band = GetDutyBand(GetChannel(i).Frequency);
            // logDebug("band: %d freq: %d", band, _channels[i].Frequency);
            if (band != -1 && _dutyBands[band].TimeOffEnd == 0) {
                enabledChannels[nbEnabledChannels++] = i;
            }
        }
    }

    logTrace("Number of available channels: %d", nbEnabledChannels);

    uint32_t freq = 0;
    int16_t thres = DEFAULT_FREE_CHAN_RSSI_THRESHOLD;

    if (nbEnabledChannels == 0) {
        delete [] enabledChannels;
        return LORA_NO_CHANS_ENABLED;
    }

    if (GetSettings()->Network.CADEnabled) {
        // Search for free channel with ms timeout
        int16_t timeout = 10000;
        Timer tmr;
        tmr.start();
        auto tm_ms = duration_cast<milliseconds>(_dutyCycleTimer.elapsed_time()).count();

        for (uint8_t j = rand_r(0, nbEnabledChannels - 1); tm_ms < timeout; j++) {
            tm_ms = duration_cast<milliseconds>(_dutyCycleTimer.elapsed_time()).count();
            freq = GetChannel(enabledChannels[j]).Frequency;

            if (GetRadio()->IsChannelFree(SxRadio::MODEM_LORA, freq, thres)) {
                _txChannel = enabledChannels[j];
                break;
            }
        }
    } else {
        uint8_t j = rand_r(0, nbEnabledChannels - 1);
        _txChannel = enabledChannels[j];
        freq = GetChannel(_txChannel).Frequency;
    }

    assert(freq != 0);

    logDebug("Using channel %d : %d", _txChannel, freq);
    GetRadio()->SetChannel(freq);

    delete [] enabledChannels;
    return LORA_OK;
}

uint8_t lora::ChannelPlan_CN470::GetJoinDatarate() {
    uint8_t dr = GetSettings()->Session.TxDatarate;
    int8_t cnt = GetSettings()->Network.DevNonce % 20;

    if (GetSettings()->Test.DisableRandomJoinDatarate == lora::OFF) {
        if ((cnt % 16) == 0) {
            dr = lora::DR_1;
        } else if ((cnt % 12) == 0) {
            dr = lora::DR_2;
        } else if ((cnt % 8) == 0) {
            dr = lora::DR_3;
        } else if ((cnt % 4) == 0) {
            dr = lora::DR_4;
        } else {
            dr = lora::DR_5;
        }
    }

    return dr;
}

uint8_t ChannelPlan_CN470::DecodeBeacon(const uint8_t* payload, size_t size, BeaconData_t& data) {
    uint16_t crc1, crc1_rx, crc2, crc2_rx;
    const BCNPayload* beacon = (const BCNPayload*)payload;

    // First check the size of the packet
    if (size != sizeof(BCNPayload))
        return LORA_BEACON_SIZE;

    // Next we verify CRC1 is correct
    crc1 = CRC16(beacon->RFU1, sizeof(beacon->RFU1) + sizeof(beacon->Time));
    memcpy((uint8_t*)&crc1_rx, beacon->CRC1, sizeof(uint16_t));

    if (crc1 != crc1_rx)
        return LORA_BEACON_CRC;

    // Now that we have confirmed this packet is a beacon, parse and complete the output struct
    memcpy(&data.Time, beacon->Time, sizeof(beacon->Time));
    data.InfoDesc = beacon->GwSpecific[0];

    crc2 = CRC16(beacon->GwSpecific, sizeof(beacon->GwSpecific) + sizeof(beacon->RFU2));
    memcpy((uint8_t*)&crc2_rx, beacon->CRC2, sizeof(uint16_t));

    // Update the GPS fields if we have a gps info descriptor and valid crc
    if (crc2 == crc2_rx &&
        (data.InfoDesc == GPS_FIRST_ANTENNA ||
         data.InfoDesc == GPS_SECOND_ANTENNA ||
         data.InfoDesc == GPS_THIRD_ANTENNA)) {
        // Latitude and Longitude 3 bytes in length
        memcpy(&data.Latitude, &beacon->GwSpecific[1], 3);
        memcpy(&data.Longitude, &beacon->GwSpecific[4], 3);
    }

    return LORA_OK;
}

void ChannelPlan_CN470::FrequencyHop(uint32_t time, uint32_t period, uint32_t devAddr) {
    uint32_t channel;
    uint32_t freq;

    if (GetSettings()->Session.BeaconFreqHop) {
        channel = (time / period) % CN470_BEACON_CHANNELS;
        freq = CN470_BEACON_FREQ_BASE + (channel * CN470_BEACON_FREQ_STEP);
        GetSettings()->Session.BeaconFrequency = freq;
    }

    if (GetSettings()->Session.PingSlotFreqHop) {
        channel = (time / period + devAddr) % CN470_BEACON_CHANNELS;
        freq = CN470_BEACON_FREQ_BASE + (channel * CN470_BEACON_FREQ_STEP);
        GetSettings()->Session.PingSlotFrequency = freq;
    }

    for (int i = 0; i < lora::MAX_MULTICAST_SESSIONS; ++i) {
        if (GetSettings()->Multicast[i].Address != 0) {
            channel = (time / period + GetSettings()->Multicast[i].Address) % CN470_BEACON_CHANNELS;
            freq = CN470_BEACON_FREQ_BASE + (channel * CN470_BEACON_FREQ_STEP);
            GetSettings()->Multicast[i].Frequency = freq;
        }
    }

}
