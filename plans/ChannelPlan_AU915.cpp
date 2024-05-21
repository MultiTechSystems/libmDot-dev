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

#include "ChannelPlan_AU915.h"
#include "limits.h"

using namespace lora;

const uint8_t ChannelPlan_AU915::AU915_TX_POWERS[] = { 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2 };
const uint8_t ChannelPlan_AU915::AU915_MAX_PAYLOAD_SIZE[] = { 51, 51, 51, 115, 242, 242, 242, 0, 53, 129, 242, 242, 242, 242, 0, 0 };
const uint8_t ChannelPlan_AU915::AU915_MAX_PAYLOAD_SIZE_REPEATER[] = { 51, 51, 51, 115, 222, 222, 222, 0, 33, 109, 222, 222, 222, 222, 0, 0 };
const uint8_t ChannelPlan_AU915::AU915_MAX_PAYLOAD_SIZE_400[] = { 0, 0, 11, 53, 125, 242, 242, 0, 53, 129, 242, 242, 242, 242, 0, 0 };
const uint8_t ChannelPlan_AU915::AU915_MAX_PAYLOAD_SIZE_REPEATER_400[] = { 0, 0, 11, 53, 125, 222, 222, 222, 0, 33, 109, 222, 222, 222, 222, 0, 0 };

const uint8_t ChannelPlan_AU915::MAX_ERP_VALUES[] = { 8, 10, 12, 13, 14, 16, 18, 20, 21, 24, 26, 27, 29, 30, 33, 36 };

ChannelPlan_AU915::ChannelPlan_AU915()
:
  ChannelPlan(NULL, NULL)
{

}

ChannelPlan_AU915::ChannelPlan_AU915(Settings* settings)
:
  ChannelPlan(NULL, settings)
{

}

ChannelPlan_AU915::ChannelPlan_AU915(SxRadio* radio, Settings* settings)
:
  ChannelPlan(radio, settings)
{

}

ChannelPlan_AU915::~ChannelPlan_AU915() {

}

void ChannelPlan_AU915::Init() {
    _plan = AU915;
    _planName = "AU915";

    _datarates.clear();
    _channels.clear();
    _dutyBands.clear();

    DutyBand band;

    band.Index = 0;
    band.DutyCycle = 0;

    Datarate dr;

    _maxTxPower = 30;
    _minTxPower = 0;

    _minFrequency = AU915_FREQ_MIN;
    _maxFrequency = AU915_FREQ_MAX;

    TX_POWERS = AU915_TX_POWERS;
    MAX_PAYLOAD_SIZE = AU915_MAX_PAYLOAD_SIZE;
    MAX_PAYLOAD_SIZE_REPEATER = AU915_MAX_PAYLOAD_SIZE_REPEATER;

    band.FrequencyMin = AU915_FREQ_MIN;
    band.FrequencyMax = AU915_FREQ_MAX;

    _freqUBase125k = AU915_125K_FREQ_BASE;
    _freqUStep125k = AU915_125K_FREQ_STEP;
    _freqUBase500k = AU915_500K_FREQ_BASE;
    _freqUStep500k = AU915_500K_FREQ_STEP;
    _freqDBase500k = AU915_500K_DBASE;
    _freqDStep500k = AU915_500K_DSTEP;

    _defaultRx2Frequency = AU915_500K_DBASE;
    _defaultRx2Datarate = DR_8;

    GetSettings()->Session.Rx2Frequency = AU915_500K_DBASE;

    _beaconSize = sizeof(BCNPayload);

    GetSettings()->Session.BeaconFrequency = AU915_BEACON_FREQ_BASE;
    GetSettings()->Session.BeaconFreqHop = true;
    GetSettings()->Session.PingSlotFrequency = AU915_BEACON_FREQ_BASE;
    GetSettings()->Session.PingSlotDatarateIndex = AU915_BEACON_DR;
    GetSettings()->Session.PingSlotFreqHop = true;
    GetSettings()->Session.Max_EIRP = 30;

    _minDatarate = lora::DR_0;
    _maxDatarate = AU915_MAX_DATARATE;
    _minRx2Datarate = DR_8;
    _maxRx2Datarate = DR_13;
    _minDatarateOffset = AU915_MIN_DATARATE_OFFSET;
    _maxDatarateOffset = AU915_MAX_DATARATE_OFFSET;

    _numChans125k = AU915_125K_NUM_CHANS;
    _numChans500k = AU915_500K_NUM_CHANS;

    logInfo("Initialize channels...");

    SetNumberOfChannels(AU915_125K_NUM_CHANS + AU915_500K_NUM_CHANS, false);

    dr.SpreadingFactor = SF_12;

    logInfo("Initialize datarates...");

    // Add DR0-5
    while (dr.SpreadingFactor >= SF_7) {
        AddDatarate(-1, dr);
        dr.SpreadingFactor--;
        dr.Index++;
    }

    // Add DR6
    dr.SpreadingFactor = SF_8;
    dr.Bandwidth = BW_500;
    AddDatarate(-1, dr);
    dr.Index++;

    // Skip DR7 RFU
    dr.SpreadingFactor = SF_INVALID;
    AddDatarate(-1, dr), dr.Index++;

    if (GetSettings()->Network.FrequencySubBand == 0) {
        band.PowerMax = 30;
    } else {
        band.PowerMax = 21;
    }

    band.TimeOffEnd = 0;

    AddDutyBand(-1, band);

    GetSettings()->Session.Rx2DatarateIndex = DR_8;

    // Add DR8-13
    dr.SpreadingFactor = SF_12;
    while (dr.SpreadingFactor >= SF_7) {
        AddDatarate(-1, dr);
        dr.SpreadingFactor--;
        dr.Index++;
    }

    // Skip DR14-15 RFU
    dr.SpreadingFactor = SF_INVALID;
    AddDatarate(-1, dr), AddDatarate(-1, dr);

    GetSettings()->Session.TxDatarate = DR_0;
    GetSettings()->Session.TxPower = GetSettings()->Network.TxPower;
    GetSettings()->Session.UplinkDwelltime = 1;

    SetFrequencySubBand(GetSettings()->Network.FrequencySubBand);

}

uint8_t ChannelPlan_AU915::HandleJoinAccept(const uint8_t* buffer, uint8_t size) {

    if (size > 17 && buffer[28] == 0x01) {
        for (int i = 13; i < size - 5; i += 2) {
            SetChannelMask((i-13)/2, buffer[i+1] << 8 | buffer[i]);
        }

        if (GetSettings()->Session.TxDatarate == GetMaxDatarate() && GetChannelMask()[4] == 0x0) {
            GetSettings()->Session.TxDatarate = GetMaxDatarate() - 1;
        }
    } else {
        uint8_t fsb = 0;

        if (_txChannel < 64)
            fsb = (_txChannel / 8);
        else
            fsb = (_txChannel % 8);

        // Reset state of random channels to enable the last used FSB for the first tx to confirm network settings
        _randomChannel.ChannelState125K(0);
        _randomChannel.MarkAllSubbandChannelsUnused(fsb);
        _randomChannel.ChannelState500K(1 << fsb);
        EnableDefaultChannels();
    }

    return LORA_OK;
}

void ChannelPlan_AU915::SetNumberOfChannels(uint8_t channels, bool resize) {
    uint8_t newsize = ((channels - 1) / CHAN_MASK_SIZE) + 1;

    if (resize) {
        _channels.resize(channels);
    }

    _channelMask.resize(newsize, 0x0);
    _numChans = channels;

}

uint8_t ChannelPlan_AU915::GetMinDatarate() {
    if (GetSettings()->Network.Mode == lora::PEER_TO_PEER)
#if defined(CERTIFICATION_DATARATES)
        return 0;
#else
        return 8;
#endif
    else {
        if (GetSettings()->Session.UplinkDwelltime == 1)
            return lora::DR_2;
        else
            return _minDatarate;
    }
}

uint8_t ChannelPlan_AU915::GetMaxDatarate() {
    if (GetSettings()->Network.Mode == lora::PEER_TO_PEER)
        return 13;
    else
        return _maxDatarate;
}

bool ChannelPlan_AU915::IsChannelEnabled(uint8_t channel) {
    uint8_t index = channel / CHAN_MASK_SIZE;
    uint8_t shift = channel % CHAN_MASK_SIZE;

    assert(index < _channelMask.size() * CHAN_MASK_SIZE);

    // cannot shift over 32 bits
    assert(shift < 32);

    // logDebug("index: %d shift %d cm: %04x bit: %04x enabled: %d", index, shift, _channelMask[index], (1 << shift), (_channelMask[index] & (1 << shift)) == (1 << shift));

    return (_channelMask[index] & (1 << shift)) == (1 << shift);
}

uint8_t ChannelPlan_AU915::SetRx1Offset(uint8_t offset) {
    GetSettings()->Session.Rx1DatarateOffset = offset;
    return LORA_OK;
}

uint8_t ChannelPlan_AU915::SetRx2Frequency(uint32_t freq) {
    GetSettings()->Session.Rx2Frequency = freq;
    return LORA_OK;
}

uint8_t ChannelPlan_AU915::SetRx2DatarateIndex(uint8_t index) {
    GetSettings()->Session.Rx2DatarateIndex = index;
    return LORA_OK;
}

uint8_t ChannelPlan_AU915::SetTxConfig() {

    uint8_t band = GetDutyBand(GetChannel(_txChannel).Frequency);
    Datarate txDr = GetDatarate(GetSettings()->Session.TxDatarate);
    int8_t max_pwr = _dutyBands[band].PowerMax;

    int8_t pwr = 0;

    pwr = std::min < int8_t > (GetSettings()->Session.TxPower, max_pwr);
    if (pwr + GetSettings()->Network.AntennaGain >= max_pwr + 6 && GetSettings()->Network.AntennaGain > 6) {
        pwr -= (GetSettings()->Network.AntennaGain - 6);
    }

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


uint8_t ChannelPlan_AU915::AddChannel(int8_t index, Channel channel) {
    logTrace("Add Channel %d : %lu : %02x %d", index, channel.Frequency, channel.DrRange.Value, _channels.size());

    assert(index < (int) _channels.size());

    if (index >= 0) {
        _channels[index] = channel;
    } else {
        _channels.push_back(channel);
    }

    return LORA_OK;
}

Channel ChannelPlan_AU915::GetChannel(int8_t index) {
    Channel chan;
    memset(&chan, 0, sizeof(Channel));

    if (_channels.size() > 0) {
        chan = _channels[index];
    } else {
        if (index < 64) {
            chan.Index = index;
            chan.DrRange.Fields.Min = GetMinDatarate();
            chan.DrRange.Fields.Max = _maxDatarate - 1;
            chan.Frequency = _freqUBase125k + (_freqUStep125k * index);
        } else if (index < 72) {
            chan.Index = index;
            chan.DrRange.Fields.Min = _maxDatarate;
            chan.DrRange.Fields.Max = _maxDatarate;
            chan.Frequency = _freqUBase500k + (_freqUStep500k * (index - 64));
        }
    }

    return chan;
}

uint8_t ChannelPlan_AU915::SetFrequencySubBand(uint8_t sub_band) {

    _txFrequencySubBand = sub_band;

    if (sub_band > 0 && sub_band < 9) {
        SetChannelMask(0, 0x0000);
        SetChannelMask(1, 0x0000);
        SetChannelMask(2, 0x0000);
        SetChannelMask(3, 0x0000);
        SetChannelMask(4, 0x0000);
        SetChannelMask((sub_band - 1) / 2, (sub_band % 2) ? 0x00FF : 0xFF00);
        SetChannelMask(4, 1 << (sub_band - 1));
    } else {
        SetChannelMask(0, 0xFFFF);
        SetChannelMask(1, 0xFFFF);
        SetChannelMask(2, 0xFFFF);
        SetChannelMask(3, 0xFFFF);
        SetChannelMask(4, 0x00FF);
    }

    return LORA_OK;
}


void ChannelPlan_AU915::LogRxWindow(uint8_t wnd) {
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

    logTrace("RX%d on freq: %lu", wnd, rxw.Frequency);
    logTrace("RX DR: %u SF: %u BW: %u CR: %u PL: %u STO: %u CRC: %d IQ: %d", rxDr.Index, sf, bw, cr, pl, sto, crc, iq);
#endif
}

uint8_t ChannelPlan_AU915::GetMaxPayloadSize() {
    if (GetSettings()->Session.UplinkDwelltime == 1) {
        if (GetSettings()->Network.RepeaterMode)
            return AU915_MAX_PAYLOAD_SIZE_REPEATER_400[GetSettings()->Session.TxDatarate];
        else
            return AU915_MAX_PAYLOAD_SIZE_400[GetSettings()->Session.TxDatarate];
    } else {
        if (GetSettings()->Network.RepeaterMode)
            return MAX_PAYLOAD_SIZE_REPEATER[GetSettings()->Session.TxDatarate];
        else
            return MAX_PAYLOAD_SIZE[GetSettings()->Session.TxDatarate];
    }
}

RxWindow ChannelPlan_AU915::GetRxWindow(uint8_t window, int8_t id) {
    RxWindow rxw;
    int index = 0;

    if (P2PEnabled()) {
        rxw.Frequency = GetSettings()->Network.TxFrequency;
        index = GetSettings()->Session.TxDatarate;
    } else {
        switch (window) {
        case RX_1:
            if (_txChannel < _numChans125k) {
                if (GetSettings()->Network.Mode == lora::PRIVATE_MTS)
                    rxw.Frequency = _freqDBase500k + (_txChannel / 8) * _freqDStep500k;
                else
                    rxw.Frequency = _freqDBase500k + (_txChannel % 8) * _freqDStep500k;
            } else
                rxw.Frequency = _freqDBase500k + (_txChannel - _numChans125k) * _freqDStep500k;

            if (GetSettings()->Session.TxDatarate <= DR_6) {
                index = GetSettings()->Session.TxDatarate + 8 - GetSettings()->Session.Rx1DatarateOffset;

                if (index < DR_8)
                    index = DR_8;
                if (index > DR_13)
                    index = DR_13;
            } else if (GetSettings()->Session.TxDatarate >= DR_8) {
                index = GetSettings()->Session.TxDatarate - GetSettings()->Session.Rx1DatarateOffset;
                if (index < DR_8)
                    index = DR_8;
            }

            break;

        case RX_BEACON:
            rxw.Frequency = GetSettings()->Session.BeaconFrequency;
            index = AU915_BEACON_DR;
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
            if (GetSettings()->Network.Mode == lora::PRIVATE_MTS) {
                if (_txChannel < _numChans125k) {
                    rxw.Frequency = _freqDBase500k + (_txChannel / 8) * _freqDStep500k;
                } else {
                    rxw.Frequency = _freqDBase500k + (_txChannel % 8) * _freqDStep500k;
                }
            } else {
                rxw.Frequency = GetSettings()->Session.Rx2Frequency;
            }

            index = GetSettings()->Session.Rx2DatarateIndex;
        }
    }

    rxw.DatarateIndex = index;

    return rxw;
}

uint8_t ChannelPlan_AU915::HandleRxParamSetup(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {
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

uint8_t ChannelPlan_AU915::HandleNewChannel(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {

    // Not Supported in AU915
    status = 0;
    return LORA_UNSUPPORTED;
}

uint8_t ChannelPlan_AU915::HandleDownlinkChannelReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {

    // Not Supported in AU915
    status = 0;
    return LORA_UNSUPPORTED;
}

uint8_t ChannelPlan_AU915::HandlePingSlotChannelReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {
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
        freq = AU915_BEACON_FREQ_BASE;
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

uint8_t ChannelPlan_AU915::HandleBeaconFrequencyReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {
    uint32_t freq = 0;
    bool freqHop = false;

    status = 0x01;

    freq = payload[index++];
    freq |= payload[index++] << 8;
    freq |= payload[index] << 16;
    freq *= 100;

    if (freq == 0U) {
        logInfo("Received request to reset beacon frequency to default");
        freq = AU915_BEACON_FREQ_BASE;
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

uint8_t ChannelPlan_AU915::HandleAdrCommand(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {

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
    if (power != 0xF && power > 14) {
        status &= 0xFB; // TxPower KO
    }

    uint16_t t_125k = 0; //used only in ctrl case 5

    switch (ctrl) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            SetChannelMask(ctrl, mask);
            break;

        case 5:
            if(mask != 0) { //see US915 for same code with comments
                for(int i = 0; i < 8; i++) {
                    if(((mask >> i) & 1) == 1) {
                        t_125k |= (0xff << ((i % 2) * 8));
                    }
                    if(i % 2 == 1) {
                        SetChannelMask(i/2, t_125k);
                        t_125k = 0;
                    }
                }
                SetChannelMask(4, mask);
            } else {
                status &= 0xFE; // ChannelMask KO
                logWarning("Rejecting mask, will not disable all channels");
                return LORA_ERROR;
            }
            break;

        case 6:
            // enable all 125 kHz channels
            SetChannelMask(0, 0xFFFF);
            SetChannelMask(1, 0xFFFF);
            SetChannelMask(2, 0xFFFF);
            SetChannelMask(3, 0xFFFF);
            SetChannelMask(4, mask);
            break;

        case 7:
            // disable all 125 kHz channels
            SetChannelMask(0, 0x0);
            SetChannelMask(1, 0x0);
            SetChannelMask(2, 0x0);
            SetChannelMask(3, 0x0);
            SetChannelMask(4, mask);
            break;

        default:
            logWarning("rejecting RFU or unknown control value %d", ctrl);
            status &= 0xFE; // ChannelMask KO
            return LORA_ERROR;
    }

    if (GetSettings()->Network.ADREnabled) {
        if (status == 0x07) {
            if (datarate != 0xF)
                GetSettings()->Session.TxDatarate = datarate;
            if (power != 0xF) {
                if (GetSettings()->Session.Max_EIRP > (power * 2))
                    GetSettings()->Session.TxPower = GetSettings()->Session.Max_EIRP - (power * 2);
                else
                    GetSettings()->Session.TxPower = 0;
            }
            GetSettings()->Session.Redundancy = nbRep;
        }
    } else {
        logDebug("ADR is disabled, DR and Power not changed.");
    }

    logDebug("ADR DR: %u PWR: %u Ctrl: %02x Mask: %04x NbRep: %u Stat: %02x", datarate, power, ctrl, mask, nbRep, status);

    return LORA_OK;
}

uint8_t ChannelPlan_AU915::ValidateAdrConfiguration() {
    uint8_t status = 0x07;
    uint8_t chans_enabled = 0;
    uint8_t datarate = GetSettings()->Session.TxDatarate;
    uint8_t power = GetSettings()->Session.TxPower;

    if (GetSettings()->Network.ADREnabled) {
        if (datarate > _maxDatarate) {
            logWarning("ADR Datarate KO - outside allowed range");
            status &= 0xFD; // Datarate KO
        }
        if (GetSettings()->Session.UplinkDwelltime != 0 && datarate < DR_2) {
            logWarning("ADR Datarate KO - TxDwelltime != 0 and DR < 2");
            status &= 0xFD; // Datarate KO
        }
        if (power < _minTxPower || power > GetSettings()->Session.Max_EIRP) {
            logWarning("ADR TX Power KO - outside allowed range");
            status &= 0xFB; // TxPower KO
        }
    }

    // at least 2 125kHz channels must be enabled
    chans_enabled += CountBits(_channelMask[0]);
    chans_enabled += CountBits(_channelMask[1]);
    chans_enabled += CountBits(_channelMask[2]);
    chans_enabled += CountBits(_channelMask[3]);
    // Semtech reference (LoRaMac-node) enforces at least 2 channels
    if (datarate < 6 && chans_enabled < 2) {
        logWarning("ADR Channel Mask KO - at least 2 125kHz channels must be enabled");
        status &= 0xFE; // ChannelMask KO
    }

    // if TXDR == 6 (SF8@500kHz) at least 1 500kHz channel must be enabled
    if (datarate == DR_6 && (CountBits(_channelMask[4] & 0xFF) == 0)) {
        logWarning("ADR Datarate KO - DR4 requires at least 1 500kHz channel enabled");
        status &= 0xFD; // Datarate KO
    }

    return status;
}

uint32_t ChannelPlan_AU915::GetTimeOffAir()
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

std::vector<uint32_t> lora::ChannelPlan_AU915::GetChannels() {
    std::vector < uint32_t > chans;

    if (GetSettings()->Network.FrequencySubBand > 0) {
        uint8_t chans_per_group = 8;
        size_t start = (GetSettings()->Network.FrequencySubBand - 1) * chans_per_group;
        for (int8_t i = start; i < int8_t(start + chans_per_group); i++) {
            chans.push_back(GetChannel(i).Frequency);
        }
        chans.push_back(GetChannel(_numChans125k + (GetSettings()->Network.FrequencySubBand - 1)).Frequency);
        chans.push_back(GetRxWindow(2).Frequency);
    } else {
        for (int8_t i = 0; i < _numChans; i++) {
            chans.push_back(GetChannel(i).Frequency);
        }
        chans.push_back(GetRxWindow(2).Frequency);
    }

    return chans;
}

std::vector<uint8_t> lora::ChannelPlan_AU915::GetChannelRanges() {
    std::vector < uint8_t > ranges;

    if (GetSettings()->Network.FrequencySubBand > 0) {
        uint8_t chans_per_group = 8;
        size_t start = (GetSettings()->Network.FrequencySubBand - 1) * chans_per_group;
        for (int8_t i = start; i < int8_t(start + chans_per_group); i++) {
            ranges.push_back(GetChannel(i).DrRange.Value);
        }
        ranges.push_back(GetChannel(_numChans125k + (GetSettings()->Network.FrequencySubBand - 1)).DrRange.Value);
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

uint8_t ChannelPlan_AU915::SetDutyBandDutyCycle(uint8_t band, uint16_t dutyCycle) {
    return LORA_UNSUPPORTED;
}

void lora::ChannelPlan_AU915::EnableDefaultChannels() {
    SetFrequencySubBand(GetSettings()->Network.FrequencySubBand);
}

uint8_t ChannelPlan_AU915::GetNextChannel()
{
    bool error = false;

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

    if (GetSettings()->Session.TxDatarate == GetMaxDatarate() && GetChannelMask()[4] == 0x0) {
        GetSettings()->Session.TxDatarate = GetMaxDatarate() - 1;
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

    if (GetTxDatarate().Bandwidth == BW_500) {
        _dutyBands[0].PowerMax = 26;
    } else {
        if (nbEnabledChannels < 50)
            _dutyBands[0].PowerMax = 21;
        else
            _dutyBands[0].PowerMax = 30;
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

uint8_t lora::ChannelPlan_AU915::GetJoinDatarate() {
    uint8_t dr = GetSettings()->Session.TxDatarate;

    uint8_t fsb = 1;
    uint8_t dr4_fsb = 1;
    bool altdr = false;

    altdr = (GetSettings()->Network.DevNonce % 2) == 0;

    if ((GetSettings()->Network.DevNonce % 9) == 0) {
        // set DR4 fsb to 1-8 incrementing every 9th join
        dr4_fsb = ((GetSettings()->Network.DevNonce / 9) % 8) + 1;
        fsb = 9;
    } else {
        fsb = (GetSettings()->Network.DevNonce % 9);
    }

    if (GetSettings()->Network.FrequencySubBand == 0) {
        if (fsb < 9) {
            SetFrequencySubBand(fsb);
        } else {
            SetFrequencySubBand(dr4_fsb);
        }
    }

    if (GetSettings()->Test.DisableRandomJoinDatarate == lora::OFF) {
        if (GetSettings()->Network.FrequencySubBand == 0) {
            if (fsb < 9) {
                dr = (_plan == US915 ? lora::DR_0 : lora::DR_2); // US or AU
            } else {
                dr = (_plan == US915 ? lora::DR_4 : lora::DR_6); // US or AU
            }
        } else if (altdr && CountBits(_channelMask[4] > 0)) {
            dr = (_plan == US915 ? lora::DR_4 : lora::DR_6); // US or AU
        } else {
            dr = (_plan == US915 ? lora::DR_0 : lora::DR_2); // US or AU
        }
    }
    

    return dr;
}

uint8_t ChannelPlan_AU915::HandleMacCommand(uint8_t* payload, uint8_t& index) {
    logDebug("AU915 Handle Mac index: %d", index);

    switch (payload[index++]) {
        case SRV_MAC_TX_PARAM_SETUP_REQ: {
            uint8_t eirp_dwell = payload[index++];

            GetSettings()->Session.DownlinkDwelltime = (eirp_dwell >> 5) & 0x01;
            GetSettings()->Session.UplinkDwelltime = (eirp_dwell >> 4) & 0x01;
            //change data rate with if dwell time changes
            if(GetSettings()->Session.UplinkDwelltime == 1) {
                if(GetSettings()->Session.TxDatarate < lora::DR_2) {
                    GetSettings()->Session.TxDatarate = lora::DR_2;
                    logDebug("Datarate is now DR%d",GetSettings()->Session.TxDatarate);
                }
            }

            GetSettings()->Session.Max_EIRP = MAX_ERP_VALUES[(eirp_dwell & 0x0F)];
            logDebug("buffer index %d", GetSettings()->Session.CommandBufferIndex);

            if (GetSettings()->Session.TxPower > GetSettings()->Session.Max_EIRP) {
                GetSettings()->Session.TxPower = GetSettings()->Session.Max_EIRP;
            }

            if (GetSettings()->Session.CommandBufferIndex < std::min<int>(GetMaxPayloadSize(), COMMANDS_BUFFER_SIZE)) {
                logDebug("Add tx param setup mac cmd to buffer");
                GetSettings()->Session.CommandBuffer[GetSettings()->Session.CommandBufferIndex++] = MOTE_MAC_TX_PARAM_SETUP_ANS;
            }

            logDebug("TX PARAM DWELL UL: %d DL: %d Max EIRP: %d", GetSettings()->Session.UplinkDwelltime, GetSettings()->Session.DownlinkDwelltime, GetSettings()->Session.Max_EIRP);
            break;
        }
        default: {
            return LORA_ERROR;
        }
    }

    return LORA_OK;
}

uint8_t ChannelPlan_AU915::DecodeBeacon(const uint8_t* payload, size_t size, BeaconData_t& data) {
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

void ChannelPlan_AU915::FrequencyHop(uint32_t time, uint32_t period, uint32_t devAddr) {
    uint32_t channel;
    uint32_t freq;

    if (GetSettings()->Session.BeaconFreqHop) {
        channel = (time / period) % AU915_BEACON_CHANNELS;
        freq = AU915_BEACON_FREQ_BASE + (channel * AU915_BEACON_FREQ_STEP);
        GetSettings()->Session.BeaconFrequency = freq;
    }

    if (GetSettings()->Session.PingSlotFreqHop) {
        channel = (time / period + devAddr) % AU915_BEACON_CHANNELS;
        freq = AU915_BEACON_FREQ_BASE + (channel * AU915_BEACON_FREQ_STEP);
        GetSettings()->Session.PingSlotFrequency = freq;
    }

    for (int i = 0; i < lora::MAX_MULTICAST_SESSIONS; ++i) {
        if (GetSettings()->Multicast[i].Address != 0) {
            channel = (time / period + GetSettings()->Multicast[i].Address) % AU915_BEACON_CHANNELS;
            freq = AU915_BEACON_FREQ_BASE + (channel * AU915_BEACON_FREQ_STEP);
            GetSettings()->Multicast[i].Frequency = freq;
        }
    }

}
