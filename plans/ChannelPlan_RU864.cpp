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

#include "ChannelPlan_RU864.h"
#include "limits.h"

using namespace lora;

// MWF - changed RU864_TX_POWERS to match final 1.0.2 regional spec
const uint8_t ChannelPlan_RU864::RU864_TX_POWERS[] = { 16, 14, 12, 9, 8, 6, 4, 2 };
const uint8_t ChannelPlan_RU864::RU864_MAX_PAYLOAD_SIZE[] = { 51, 51, 51, 115, 242, 242, 242, 242, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_RU864::RU864_MAX_PAYLOAD_SIZE_REPEATER[] = { 51, 51, 51, 115, 222, 222, 222, 222, 0, 0, 0, 0, 0, 0, 0, 0 };

ChannelPlan_RU864::ChannelPlan_RU864()
:
    ChannelPlan(NULL, NULL)
{
    _beaconSize = sizeof(BCNPayload);
}

ChannelPlan_RU864::ChannelPlan_RU864(Settings* settings)
:
    ChannelPlan(NULL, settings)
{
    _beaconSize = sizeof(BCNPayload);
}

ChannelPlan_RU864::ChannelPlan_RU864(SxRadio* radio, Settings* settings)
:
    ChannelPlan(radio, settings)
{
    _beaconSize = sizeof(BCNPayload);
}

ChannelPlan_RU864::~ChannelPlan_RU864() {

}

void ChannelPlan_RU864::Init() {

    _datarates.clear();
    _channels.clear();
    _dutyBands.clear();

    DutyBand band;

    band.Index = 0;
    band.DutyCycle = 0;

    Datarate dr;

    _plan = RU864;
    _planName = "RU864";
    _maxTxPower = 27;
    _minTxPower = 0;

    _minFrequency = RU864_FREQ_MIN;
    _maxFrequency = RU864_FREQ_MAX;

    TX_POWERS = RU864_TX_POWERS;
    MAX_PAYLOAD_SIZE = RU864_MAX_PAYLOAD_SIZE;
    MAX_PAYLOAD_SIZE_REPEATER = RU864_MAX_PAYLOAD_SIZE_REPEATER;

    _minDatarate = DR_0;
    _minRx2Datarate = DR_0;

#if defined(ENABLE_LORAWAN_OPTIONAL_DATARATES)
    _maxDatarate = DR_7;
    _maxRx2Datarate = DR_7;
#else
    _maxDatarate = DR_5;
    _maxRx2Datarate = DR_5;
#endif

    _minDatarateOffset = RU864_MIN_DATARATE_OFFSET;
    _maxDatarateOffset = RU864_MAX_DATARATE_OFFSET;

    _numChans125k = RU864_125K_NUM_CHANS;
    _numChans500k = 0;
    _numDefaultChans = RU864_DEFAULT_NUM_CHANS;

    _defaultRx2Frequency = RU864_RX2_FREQ;
    _defaultRx2Datarate = DR_0;

    GetSettings()->Session.Rx2Frequency = RU864_RX2_FREQ;
    GetSettings()->Session.Rx2DatarateIndex = DR_0;

    GetSettings()->Session.BeaconFrequency = RU864_BEACON_FREQ;
    GetSettings()->Session.BeaconFreqHop = false;
    GetSettings()->Session.PingSlotFrequency = RU864_PING_SLOT_FREQ;
    GetSettings()->Session.PingSlotDatarateIndex = RU864_BEACON_DR;
    GetSettings()->Session.PingSlotFreqHop = false;

    logInfo("Initialize datarates...");

    dr.SpreadingFactor = SF_12;

    // Add DR0-5
    while (dr.SpreadingFactor >= SF_7) {
        AddDatarate(-1, dr);
        dr.SpreadingFactor--;
        dr.Index++;
    }

    // Add DR6
    dr.SpreadingFactor = SF_7;
    dr.Bandwidth = BW_250;
    AddDatarate(-1, dr);
    dr.Index++;

    // Add DR7
    dr.SpreadingFactor = SF_FSK;
    dr.Bandwidth = BW_FSK;
    dr.PreambleLength = 10;
    dr.Coderate = 0;
    AddDatarate(-1, dr);
    dr.Index++;


    // Skip DR8-15 RFU
    dr.SpreadingFactor = SF_INVALID;
    while (dr.Index++ <= DR_15) {
        AddDatarate(-1, dr);
    }

    GetSettings()->Session.TxDatarate = 0;

    logInfo("Initialize channels...");

    Channel chan;
    chan.DrRange.Fields.Min = DR_0;
    chan.DrRange.Fields.Max = DR_5;
    chan.Index = 0;
    chan.Frequency = RU864_125K_FREQ_BASE;
    SetNumberOfChannels(RU864_125K_NUM_CHANS);

    for (uint8_t i = 0; i < RU864_DEFAULT_NUM_CHANS; i++) {
        chan.DrRange.Fields.Max = DR_5;

        AddChannel(i, chan);
        chan.Index++;
        chan.Frequency += RU864_125K_FREQ_STEP;
    }

    chan.DrRange.Value = 0;
    chan.Frequency = 0;

    for (uint8_t i = RU864_DEFAULT_NUM_CHANS; i < RU864_125K_NUM_CHANS; i++) {
        AddChannel(i, chan);
        chan.Index++;
    }

    // Add downlink channel defaults
    chan.Index = 0;
    _dlChannels.resize(16);
    for (uint8_t i = 0; i < 16; i++) {
        AddDownlinkChannel(i, chan);
        chan.Index++;
    }

    SetChannelMask(0, 0x07);

    band.Index = 0;
    band.FrequencyMin = RU864_MILLI_FREQ_MIN;
    band.FrequencyMax = RU864_MILLI_FREQ_MAX;
    band.PowerMax = 14;
    band.TimeOffEnd = 0;

    band.DutyCycle = 1000;

    AddDutyBand(-1, band);

    band.Index++;
    band.FrequencyMin = RU864_MILLI_FREQ_MAX;
    band.FrequencyMax = RU864_FREQ_MAX;
    band.PowerMax = 14;
    band.TimeOffEnd = 0;
    band.DutyCycle = 0;

    AddDutyBand(-1, band);

    GetSettings()->Session.TxPower = GetSettings()->Network.TxPower;
}

uint8_t ChannelPlan_RU864::AddChannel(int8_t index, Channel channel) {
    logTrace("Add Channel %d : %lu : %02x %d", index, channel.Frequency, channel.DrRange.Value, _channels.size());

    assert(index < (int) _channels.size());

    if (index >= 0) {
        _channels[index] = channel;
    } else {
        _channels.push_back(channel);
    }

    return LORA_OK;
}

uint8_t ChannelPlan_RU864::HandleJoinAccept(const uint8_t* buffer, uint8_t size) {

    if (size > 17 && buffer[28] == 0x00) {
        Channel ch;
        int index = _numDefaultChans;
        for (int i = 13; i < size - 5; i += 3) {

            ch.Frequency = ((buffer[i]) | (buffer[i + 1] << 8) | (buffer[i + 2] << 16)) * 100u;
            logDebug("check %lu %03X", ch.Frequency, ch.Frequency/100);
            if (ch.Frequency > 0 && ch.Frequency >= _minFrequency && ch.Frequency <= _maxFrequency) {
                ch.Index = index;
                ch.DrRange.Fields.Min = static_cast<int8_t>(DR_0);
                ch.DrRange.Fields.Max = static_cast<int8_t>(DR_5);
                AddChannel(index, ch);

                if (GetDutyBand(ch.Frequency) > -1)
                    _channelMask[0] |= (1 << index);
                else
                    _channelMask[0] |= ~(1 << index);

                index += 1;
            }
        }
    }

    return LORA_OK;
}

uint8_t ChannelPlan_RU864::SetTxConfig() {

    uint8_t band = GetDutyBand(GetChannel(_txChannel).Frequency);
    Datarate txDr = GetDatarate(GetSettings()->Session.TxDatarate);
    int8_t max_pwr = _dutyBands[band].PowerMax;

    int8_t pwr = 0;

    pwr = std::min < int8_t > (GetSettings()->Session.TxPower, max_pwr);
    pwr -= GetSettings()->Network.AntennaGain;

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

Channel ChannelPlan_RU864::GetChannel(int8_t index) {
    Channel chan;
    memset(&chan, 0, sizeof(Channel));

    chan = _channels[index];

    return chan;
}

uint8_t ChannelPlan_RU864::SetFrequencySubBand(uint8_t sub_band) {
    return LORA_OK;
}

void ChannelPlan_RU864::LogRxWindow(uint8_t wnd) {
#if defined(MTS_DEBUG)
    RxWindow rxw = GetRxWindow(wnd);
    Datarate rxDr = GetDatarate(rxw.DatarateIndex);
    uint8_t bw = rxDr.Bandwidth;
    uint8_t sf = rxDr.SpreadingFactor;
    uint8_t cr = rxDr.Coderate;
    uint8_t pl = rxDr.PreambleLength;
    uint16_t sto = rxDr.SymbolTimeout();
    bool crc = false; // downlink does not use CRC according to LORAWAN
    bool iq = GetTxDatarate().RxIQ;
    uint32_t freq = rxw.Frequency;

    if (wnd == 1 && _dlChannels[_txChannel].Frequency != 0)
        freq = _dlChannels[_txChannel].Frequency;

    logTrace("RX%d on freq: %lu", wnd, freq);
    logTrace("RX DR: %u SF: %u BW: %u CR: %u PL: %u STO: %u CRC: %d IQ: %d", rxDr.Index, sf, bw, cr, pl, sto, crc, iq);
#endif
}

RxWindow ChannelPlan_RU864::GetRxWindow(uint8_t window, int8_t id) {
    RxWindow rxw;
    int index = 0;

    if (P2PEnabled()) {
        rxw.Frequency = GetSettings()->Network.TxFrequency;
        index = GetSettings()->Session.TxDatarate;
    } else {
        switch (window) {
        case RX_1:
            rxw.Frequency = _channels[_txChannel].Frequency;

            if (GetSettings()->Session.TxDatarate > GetSettings()->Session.Rx1DatarateOffset) {
                index = GetSettings()->Session.TxDatarate - GetSettings()->Session.Rx1DatarateOffset;
            } else {
                index = 0;
            }

            break;

        case RX_BEACON:
            rxw.Frequency = GetSettings()->Session.BeaconFrequency;
            index = RU864_BEACON_DR;
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

uint8_t ChannelPlan_RU864::HandleRxParamSetup(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {
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

uint8_t ChannelPlan_RU864::HandleNewChannel(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {

    status = 0x03;
    uint8_t channelIndex = 0;
    Channel chParam;

    channelIndex = payload[index++];
    lora::CopyFreqtoInt(payload + index, chParam.Frequency);
    index += 3;
    chParam.DrRange.Value = payload[index++];

    if (channelIndex < _numDefaultChans || channelIndex > _channels.size() - 1) {
        logError("New Channel index KO");
        status &= 0xFE; // Channel index KO
    }

    if (chParam.Frequency == 0) {
        chParam.DrRange.Value = 0;
    } else if (chParam.Frequency < _minFrequency || chParam.Frequency > _maxFrequency) {
        logError("New Channel frequency KO");
        status &= 0xFE; // Channel frequency KO
    }

    if (chParam.DrRange.Fields.Min > chParam.DrRange.Fields.Max && chParam.Frequency != 0) {
        logError("New Channel datarate min/max KO");
        status &= 0xFD; // Datarate range KO
    } else if ((chParam.DrRange.Fields.Min < _minDatarate || chParam.DrRange.Fields.Min > _maxDatarate) &&
               chParam.Frequency != 0) {
        logError("New Channel datarate min KO");
        status &= 0xFD; // Datarate range KO
    } else if ((chParam.DrRange.Fields.Max < _minDatarate || chParam.DrRange.Fields.Max > _maxDatarate) &&
               chParam.Frequency != 0) {
        logError("New Channel datarate max KO");
        status &= 0xFD; // Datarate range KO
    }

    if ((status & 0x03) == 0x03) {
        logInfo("New Channel accepted index: %d freq: %lu drRange: %02x", channelIndex, chParam.Frequency, chParam.DrRange.Value);
        AddChannel(channelIndex, chParam);
        SetChannelMask(0, _channelMask[0] | 1 << (channelIndex));
    }

    return LORA_OK;
}

uint8_t ChannelPlan_RU864::HandlePingSlotChannelReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {
    uint8_t datarate = 0;
    uint32_t freq = 0;

    status = 0x03;

    freq = payload[index++];
    freq |= payload[index++] << 8;
    freq |= payload[index++] << 16;
    freq *= 100;

    datarate = payload[index] & 0x0F;

    if (freq == 0U) {
        logInfo("Received request to reset ping slot frequency to default");
        freq = RU864_PING_SLOT_FREQ;
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
    } else {
        logInfo("PingSlotChannelReq rejected DR: %d Freq: %d", datarate, freq);
    }

    return LORA_OK;
}

uint8_t ChannelPlan_RU864::HandleBeaconFrequencyReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status)
{
    uint32_t freq = 0;

    status = 0x01;

    freq = payload[index++];
    freq |= payload[index++] << 8;
    freq |= payload[index] << 16;
    freq *= 100;

    if (freq == 0U) {
        logInfo("Received request to reset beacon frequency to default");
        freq = RU864_BEACON_FREQ;
    } else if (!CheckRfFrequency(freq)) {
        logInfo("Freq KO");
        status &= 0xFE; // Channel frequency KO
    }

    if (status & 0x01) {
        logInfo("BeaconFrequencyReq accepted Freq: %d", freq);
        GetSettings()->Session.BeaconFrequency = freq;
    } else {
        logInfo("BeaconFrequencyReq rejected Freq: %d", freq);
    }

    return LORA_OK;
}

uint8_t ChannelPlan_RU864::HandleAdrCommand(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {

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
    // Remark MaxTxPower = 0 and MinTxPower = 7
    //
    if (power != 0xF && power > 7) {
        status &= 0xFB; // TxPower KO
    }

    switch (ctrl) {
        case 0:
            SetChannelMask(0, mask);
            break;

        case 6:
            // enable all currently defined channels
            mask = 0;
            for (size_t i = 0; i < _channels.size(); i++) {
                if (_channels[i].Frequency != 0) {
                    mask |= (1 << i);
                }
            }
            SetChannelMask(0, mask);
            break;

        default:
            logWarning("rejecting RFU or unknown control value %d", ctrl);
            status &= 0xFE; // ChannelMask KO
            return LORA_ERROR;
    }

    if (GetSettings()->Network.ADREnabled) {
        if (datarate != 0xF)
            GetSettings()->Session.TxDatarate = datarate;
        if (power != 0xF)
            GetSettings()->Session.TxPower = TX_POWERS[power];
        GetSettings()->Session.Redundancy = nbRep;
    } else {
        logDebug("ADR is disabled, DR and Power not changed.");
    }

    logDebug("ADR DR: %u PWR: %u Ctrl: %02x Mask: %04x NbRep: %u Stat: %02x", datarate, power, ctrl, mask, nbRep, status);

    return LORA_OK;
}

uint8_t ChannelPlan_RU864::ValidateAdrConfiguration() {
    uint8_t status = 0x07;
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
    // mask must not contain any undefined channels
    for (size_t i = _numDefaultChans; i < _channels.size(); i++) {
        if ((_channelMask[0] & (1 << i)) && (_channels[i].Frequency == 0)) {
            logWarning("ADR Channel Mask KO - cannot enable undefined channel");
            status &= 0xFE; // ChannelMask KO
            break;
        }
    }

    return status;
}

uint32_t ChannelPlan_RU864::GetTimeOffAir()
{
    uint32_t min = 0;
    auto now = duration_cast<milliseconds>(_dutyCycleTimer.elapsed_time()).count();

    if (GetSettings()->Test.DisableDutyCycle == lora::OFF && _LBT_TimeUs == 0) {
        min = UINT_MAX;
        int8_t band = 0;

        if (P2PEnabled()) {
            int8_t band = GetDutyBand(GetSettings()->Network.TxFrequency);
            if (_dutyBands[band].TimeOffEnd > now) {
                min = _dutyBands[band].TimeOffEnd - now;
            } else {
                min = 0;
            }
        } else {
            for (size_t i = 0; i < _channels.size(); i++) {
                if (IsChannelEnabled(i) && GetChannel(i).Frequency != 0 &&
                    !(GetSettings()->Session.TxDatarate < GetChannel(i).DrRange.Fields.Min ||
                    GetSettings()->Session.TxDatarate > GetChannel(i).DrRange.Fields.Max)) {

                    band = GetDutyBand(GetChannel(i).Frequency);
                    if (band != -1) {
                        // logDebug("band: %d time-off: %d now: %d", band, _dutyBands[band].TimeOffEnd, now);
                        if (_dutyBands[band].TimeOffEnd > now) {
                            min = std::min < uint32_t > (min, _dutyBands[band].TimeOffEnd - now);
                        } else {
                            min = 0;
                            break;
                        }
                    }
                }
            }
        }

        if (min == UINT_MAX)
            min = 0;
    }

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


void ChannelPlan_RU864::UpdateDutyCycle(uint32_t freq, uint32_t time_on_air_ms) {

    _dutyCycleTimer.start();
    auto now = duration_cast<milliseconds>(_dutyCycleTimer.elapsed_time()).count();

    if (GetSettings()->Session.MaxDutyCycle > 0 && GetSettings()->Session.MaxDutyCycle <= 15) {
        GetSettings()->Session.AggregatedTimeOffEnd = now + time_on_air_ms * GetSettings()->Session.AggregateDutyCycle;
        logDebug("Updated Aggregate DCycle Time-off: %lu DC: %f", GetSettings()->Session.AggregatedTimeOffEnd, 1 / float(GetSettings()->Session.AggregateDutyCycle));
    } else {
        GetSettings()->Session.AggregatedTimeOffEnd = 0;
    }

    uint32_t time_off_air = 0;

    for (size_t i = 0; i < _dutyBands.size(); i++) {
        if (_dutyBands[i].TimeOffEnd < now) {
            _dutyBands[i].TimeOffEnd = 0;
        } else {
            _dutyBands[i].TimeOffEnd -= now;
        }

        if (freq >= _dutyBands[i].FrequencyMin && freq <= _dutyBands[i].FrequencyMax) {
            logDebug("update TOE: freq: %d i:%d toa: %d DC:%d", freq, i, time_on_air_ms, _dutyBands[i].DutyCycle);
            time_off_air = time_on_air_ms * _dutyBands[i].DutyCycle;
            _dutyBands[i].TimeOffEnd = time_off_air;
        }
    }

    ResetDutyCycleTimer();
}

std::vector<uint32_t> lora::ChannelPlan_RU864::GetChannels() {
    std::vector < uint32_t > chans;

    for (int8_t i = 0; i < (int) _channels.size(); i++) {
        chans.push_back(_channels[i].Frequency);
    }
    chans.push_back(GetRxWindow(2).Frequency);

    return chans;
}

std::vector<uint8_t> lora::ChannelPlan_RU864::GetChannelRanges() {
    std::vector < uint8_t > ranges;

    for (int8_t i = 0; i < (int) _channels.size(); i++) {
        ranges.push_back(_channels[i].DrRange.Value);
    }

    ranges.push_back(GetRxWindow(2).DatarateIndex);

    return ranges;

}

void lora::ChannelPlan_RU864::EnableDefaultChannels() {
    _channelMask[0] |= 0x0003;
}

uint8_t ChannelPlan_RU864::GetNextChannel()
{
    bool error = false;

    if (GetSettings()->Session.AggregatedTimeOffEnd != 0) {
        return LORA_AGGREGATED_DUTY_CYCLE;
    }

    if (P2PEnabled() || GetSettings()->Network.TxFrequency != 0) {
        logDebug("Using frequency %d", GetSettings()->Network.TxFrequency);

        if (GetSettings()->Test.DisableDutyCycle != lora::ON && _LBT_TimeUs == 0) {
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

    if (GetTxDatarate().Bandwidth == BW_500) {
        maxChannels = _numChans500k;
        start = _numChans125k;
    }

// Search how many channels are enabled
    DatarateRange range;
    uint8_t dr_index = GetSettings()->Session.TxDatarate;
    auto now = duration_cast<milliseconds>(_dutyCycleTimer.elapsed_time()).count();

    for (size_t i = 0; i < _dutyBands.size(); i++) {
        if (_dutyBands[i].TimeOffEnd < now || GetSettings()->Test.DisableDutyCycle == lora::ON || _LBT_TimeUs > 0) {
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

        while(std::chrono::duration_cast<std::chrono::milliseconds>(tmr.elapsed_time()).count() < timeout)
        {
            uint8_t channel = 0;
            // grab the next channel if any are enabled
            if(_randomChannel.NextChannel(enabledChannels, nbEnabledChannels, &channel)) {
                freq = GetChannel(channel).Frequency;

                if (GetRadio()->IsChannelFree(SxRadio::MODEM_LORA, freq, thres)) {
                    _txChannel = channel;
                    break;
                }
            }
            else {
            	error = true;
            }
        }
    } else {
        uint8_t channel = 0;
        if(_randomChannel.NextChannel(enabledChannels, nbEnabledChannels, &channel))  {
            _txChannel = channel;
            freq = GetChannel(_txChannel).Frequency;
        }
        else  {
        	error = true;
        }
    }

    if(error) {
        logError("Unable to select a random channel");
    }
    else {
        assert(freq != 0);

        logDebug("Using channel %d : %d", _txChannel, freq);
        GetRadio()->SetChannel(freq);
    }


    delete [] enabledChannels;
    return LORA_OK;
}


uint8_t lora::ChannelPlan_RU864::GetJoinDatarate() {
    uint8_t dr = GetSettings()->Session.TxDatarate;
    int8_t cnt = GetSettings()->Network.DevNonce % 20;

    if (GetSettings()->Test.DisableRandomJoinDatarate == lora::OFF) {
        if ((cnt % 20) == 0) {
            dr = lora::DR_0;
        } else if ((cnt % 16) == 0) {
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

uint8_t ChannelPlan_RU864::DecodeBeacon(const uint8_t* payload, size_t size, BeaconData_t& data) {
    uint16_t crc1, crc1_rx, crc2, crc2_rx;
    const BCNPayload* beacon = (const BCNPayload*)payload;

    // First check the size of the packet
    if (size != sizeof(BCNPayload))
        return LORA_BEACON_SIZE;

    // Next we verify CRC1 is correct
    crc1 = CRC16(beacon->RFU, sizeof(beacon->RFU) + sizeof(beacon->Time));
    memcpy((uint8_t*)&crc1_rx, beacon->CRC1, sizeof(uint16_t));

    if (crc1 != crc1_rx)
        return LORA_BEACON_CRC;

    // Now that we have confirmed this packet is a beacon, parse and complete the output struct
    memcpy(&data.Time, beacon->Time, sizeof(beacon->Time));
    data.InfoDesc = beacon->GwSpecific[0];

    crc2 = CRC16(beacon->GwSpecific, sizeof(beacon->GwSpecific));
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
