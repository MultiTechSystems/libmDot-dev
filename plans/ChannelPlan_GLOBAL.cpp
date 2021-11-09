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

#include "ChannelPlan_GLOBAL.h"
#include "limits.h"

using namespace lora;

const uint8_t ChannelPlan_GLOBAL::US915_TX_POWERS[] = { 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0 };
const uint8_t ChannelPlan_GLOBAL::US915_MAX_PAYLOAD_SIZE[] =          { 11, 53, 125, 242, 242, 0, 0, 0, 53, 129, 242, 242, 242, 242, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::US915_MAX_PAYLOAD_SIZE_REPEATER[] = { 11, 53, 125, 222, 222, 0, 0, 0, 33, 109, 222, 222, 222, 222, 0, 0 };

const uint8_t ChannelPlan_GLOBAL::RU864_TX_POWERS[] = { 16, 14, 12, 10, 8, 6, 4, 2 };
const uint8_t ChannelPlan_GLOBAL::RU864_MAX_PAYLOAD_SIZE[] = { 51, 51, 51, 115, 242, 242, 242, 242, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::RU864_MAX_PAYLOAD_SIZE_REPEATER[] = { 51, 51, 51, 115, 222, 222, 222, 222, 0, 0, 0, 0, 0, 0, 0, 0 };

const uint8_t ChannelPlan_GLOBAL::KR920_TX_POWERS[] = { 14, 12, 10, 8, 6, 4, 2, 0 };
const uint8_t ChannelPlan_GLOBAL::KR920_MAX_PAYLOAD_SIZE[] = { 51, 51, 51, 115, 242, 242, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::KR920_MAX_PAYLOAD_SIZE_REPEATER[] = { 51, 51, 51, 115, 222, 222, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const uint8_t ChannelPlan_GLOBAL::IN865_TX_POWERS[] = { 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10 };
const uint8_t ChannelPlan_GLOBAL::IN865_MAX_PAYLOAD_SIZE[] = { 51, 51, 51, 115, 242, 242, 242, 242, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::IN865_MAX_PAYLOAD_SIZE_REPEATER[] = { 51, 51, 51, 115, 222, 222, 222, 222, 0, 0, 0, 0, 0, 0, 0, 0 };

const uint8_t ChannelPlan_GLOBAL::EU868_TX_POWERS[] = { 16, 14, 12, 10, 8, 6, 4, 2 };
const uint8_t ChannelPlan_GLOBAL::EU868_MAX_PAYLOAD_SIZE[] = { 51, 51, 51, 115, 242, 242, 242, 242, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::EU868_MAX_PAYLOAD_SIZE_REPEATER[] = { 51, 51, 51, 115, 222, 222, 222, 222, 0, 0, 0, 0, 0, 0, 0, 0 };

const uint8_t ChannelPlan_GLOBAL::AU915_TX_POWERS[] = { 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10 };
const uint8_t ChannelPlan_GLOBAL::AU915_MAX_PAYLOAD_SIZE[] = { 51, 51, 51, 115, 242, 242, 242, 0, 53, 129, 242, 242, 242, 242, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::AU915_MAX_PAYLOAD_SIZE_REPEATER[] = { 51, 51, 51, 115, 222, 222, 222, 0, 33, 109, 222, 222, 222, 222, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::AU915_MAX_PAYLOAD_SIZE_400[] = { 0, 0, 11, 53, 125, 242, 242, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::AU915_MAX_PAYLOAD_SIZE_REPEATER_400[] = { 0, 0, 11, 53, 125, 222, 222, 222, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::AU915_MAX_ERP_VALUES[] = { 8, 10, 12, 13, 14, 16, 18, 20, 21, 24, 26, 27, 29, 30, 33, 36 };

const uint8_t ChannelPlan_GLOBAL::AS923_MAX_PAYLOAD_SIZE[] = { 51, 51, 115, 115, 242, 242, 242, 242, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::AS923_MAX_PAYLOAD_SIZE_REPEATER[] = { 51, 51, 115, 115, 222, 222, 222, 222, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::AS923_MAX_PAYLOAD_SIZE_400[] = { 0, 0, 11, 53, 125, 242, 242, 242, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::AS923_MAX_PAYLOAD_SIZE_REPEATER_400[] = { 0, 0, 11, 53, 125, 222, 222, 222, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t ChannelPlan_GLOBAL::AS923_MAX_ERP_VALUES[] = { 8, 10, 12, 13, 14, 16, 18, 20, 21, 24, 26, 27, 29, 30, 33, 36 };



ChannelPlan_GLOBAL::ChannelPlan_GLOBAL(uint8_t plan_id)
:
  ChannelPlan(NULL, NULL),
  _plan_id(plan_id)
{
}

ChannelPlan_GLOBAL::ChannelPlan_GLOBAL(uint8_t plan_id, Settings* settings)
:
  ChannelPlan(NULL, settings),
  _plan_id(plan_id)
{
}

ChannelPlan_GLOBAL::ChannelPlan_GLOBAL(uint8_t plan_id, SxRadio* radio, Settings* settings)
:
  ChannelPlan(radio, settings),
  _plan_id(plan_id)
{

}

ChannelPlan_GLOBAL::~ChannelPlan_GLOBAL() {

}

void ChannelPlan_GLOBAL::Init() {

    switch (_plan_id) {
        case lora::ChannelPlan::US915:
        case lora::ChannelPlan::US915_OLD:
            Init_US915();
            break;
        case lora::ChannelPlan::EU868:
        case lora::ChannelPlan::EU868_OLD:
            Init_EU868();
            break;
        case lora::ChannelPlan::AU915:
        case lora::ChannelPlan::AU915_OLD:
            Init_AU915();
            break;
        case lora::ChannelPlan::AS923:
        case lora::ChannelPlan::AS923_2:
        case lora::ChannelPlan::AS923_3:
        case lora::ChannelPlan::AS923_4:
        case lora::ChannelPlan::AS923_JAPAN:
        case lora::ChannelPlan::AS923_JAPAN1:
        case lora::ChannelPlan::AS923_JAPAN2:
            Init_AS923();
            break;
    }

}

void ChannelPlan_GLOBAL::Init_EU868() {
    _datarates.clear();
    _channels.clear();
    _dutyBands.clear();

    DutyBand band;

    band.Index = 0;
    band.DutyCycle = 0;

    Datarate dr;

    _plan = EU868;
    _planName = "EU868";
    _maxTxPower = 27;
    _minTxPower = 0;

    _minFrequency = EU868_FREQ_MIN;
    _maxFrequency = EU868_FREQ_MAX;

    TX_POWERS = EU868_TX_POWERS;
    MAX_PAYLOAD_SIZE = EU868_MAX_PAYLOAD_SIZE;
    MAX_PAYLOAD_SIZE_REPEATER = EU868_MAX_PAYLOAD_SIZE_REPEATER;

    _minDatarate = EU868_MIN_DATARATE;
    _maxDatarate = EU868_MAX_DATARATE;

    _minRx2Datarate = DR_0;
    _maxRx2Datarate = DR_7;

    _minDatarateOffset = EU868_MIN_DATARATE_OFFSET;
    _maxDatarateOffset = EU868_MAX_DATARATE_OFFSET;

    _numChans125k = EU868_125K_NUM_CHANS;
    _numChans500k = 0;

    _numDefaultChans = EU868_DEFAULT_NUM_CHANS;

    GetSettings()->Session.Rx2Frequency = EU868_RX2_FREQ;
    GetSettings()->Session.Rx2DatarateIndex = DR_0;

    _beaconSize = sizeof(BCNPayload_EU868);

    GetSettings()->Session.BeaconFrequency = EU868_BEACON_FREQ;
    GetSettings()->Session.BeaconFreqHop = false;
    GetSettings()->Session.PingSlotFrequency = EU868_BEACON_FREQ;
    GetSettings()->Session.PingSlotDatarateIndex = EU868_BEACON_DR;
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

    _maxDatarate = DR_7;

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
    chan.Frequency = EU868_125K_FREQ_BASE;
    SetNumberOfChannels(EU868_125K_NUM_CHANS);

    for (uint8_t i = 0; i < EU868_DEFAULT_NUM_CHANS; i++) {
        chan.DrRange.Fields.Max = DR_5;

        AddChannel(i, chan);
        chan.Index++;
        chan.Frequency += EU868_125K_FREQ_STEP;
    }

    chan.DrRange.Value = 0;
    chan.Frequency = 0;

    for (uint8_t i = EU868_DEFAULT_NUM_CHANS; i < EU868_125K_NUM_CHANS; i++) {
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
    band.FrequencyMin = EU868_MILLI_FREQ_MIN;
    band.FrequencyMax = EU868_MILLI_FREQ_MAX;
    band.PowerMax = 16;
    band.TimeOffEnd = 0;

    // Limiting to 865-868 allows for 1% duty cycle
    band.DutyCycle = 100;

    AddDutyBand(-1, band);

    band.Index++;
    band.FrequencyMin = EU868_CENTI_FREQ_MIN;
    band.FrequencyMax = EU868_CENTI_FREQ_MAX;
    band.DutyCycle = 100;

    AddDutyBand(-1, band);

    band.Index++;
    band.FrequencyMin = EU868_DECI_FREQ_MIN;
    band.FrequencyMax = EU868_DECI_FREQ_MAX;
    band.PowerMax = 29;
    band.DutyCycle = 10;

    AddDutyBand(-1, band);

    band.Index++;
    band.FrequencyMin = EU868_VAR_FREQ_MIN;
    band.FrequencyMax = EU868_VAR_FREQ_MAX;
    band.DutyCycle = 100;

    AddDutyBand(-1, band);

    band.Index++;
    band.FrequencyMin = EU868_MILLI_1_FREQ_MIN;
    band.FrequencyMax = EU868_MILLI_1_FREQ_MAX;
    band.PowerMax = 14;
    band.TimeOffEnd = 0;
    band.DutyCycle = 1000;

    AddDutyBand(-1, band);

    GetSettings()->Session.TxPower = GetSettings()->Network.TxPower;
}

void ChannelPlan_GLOBAL::Init_US915() {

    _plan = US915;
    _planName = "US915";

    _datarates.clear();
    _channels.clear();
    _dutyBands.clear();

    DutyBand band;

    band.Index = 0;
    band.DutyCycle = 0;

    Datarate dr;

    _maxTxPower = 30;
    _minTxPower = 0;

    _minFrequency = US915_FREQ_MIN;
    _maxFrequency = US915_FREQ_MAX;

    TX_POWERS = US915_TX_POWERS;
    MAX_PAYLOAD_SIZE = US915_MAX_PAYLOAD_SIZE;
    MAX_PAYLOAD_SIZE_REPEATER = US915_MAX_PAYLOAD_SIZE_REPEATER;

    band.FrequencyMin = US915_FREQ_MIN;
    band.FrequencyMax = US915_FREQ_MAX;

    _freqUBase125k = US915_125K_FREQ_BASE;
    _freqUStep125k = US915_125K_FREQ_STEP;
    _freqUBase500k = US915_500K_FREQ_BASE;
    _freqUStep500k = US915_500K_FREQ_STEP;
    _freqDBase500k = US915_500K_DBASE;
    _freqDStep500k = US915_500K_DSTEP;
    GetSettings()->Session.Rx2Frequency = US915_500K_DBASE;

    GetSettings()->Session.BeaconFrequency = US915_BEACON_FREQ_BASE;
    GetSettings()->Session.BeaconFreqHop = true;
    GetSettings()->Session.PingSlotFrequency = US915_BEACON_FREQ_BASE;
    GetSettings()->Session.PingSlotDatarateIndex = US915_BEACON_DR;
    GetSettings()->Session.PingSlotFreqHop = true;

    _minDatarate = US915_MIN_DATARATE;
    _maxDatarate = US915_MAX_DATARATE;
    _minRx2Datarate = DR_8;
    _maxRx2Datarate = DR_13;
    _minDatarateOffset = US915_MIN_DATARATE_OFFSET;
    _maxDatarateOffset = US915_MAX_DATARATE_OFFSET;

    _numChans125k = US915_125K_NUM_CHANS;
    _numChans500k = US915_500K_NUM_CHANS;

    logInfo("Initialize channels...");

    SetNumberOfChannels(US915_125K_NUM_CHANS + US915_500K_NUM_CHANS, false);

    dr.SpreadingFactor = SF_10;

    logInfo("Initialize datarates...");

    // Add DR0-3
    while (dr.SpreadingFactor >= SF_7) {
        AddDatarate(-1, dr);
        dr.SpreadingFactor--;
        dr.Index++;
    }

    // Add DR4
    dr.SpreadingFactor = SF_8;
    dr.Bandwidth = BW_500;
    AddDatarate(-1, dr);
    dr.Index++;

    // Skip DR5-7 RFU
    dr.SpreadingFactor = SF_INVALID;
    AddDatarate(-1, dr), dr.Index++;
    AddDatarate(-1, dr), dr.Index++;
    AddDatarate(-1, dr), dr.Index++;

    band.PowerMax = 30;

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

    SetFrequencySubBand(GetSettings()->Network.FrequencySubBand);

    _beaconSize = sizeof(BCNPayload_US915);

}

void ChannelPlan_GLOBAL::Init_AU915() {
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
    GetSettings()->Session.Rx2Frequency = AU915_500K_DBASE;

    _beaconSize = sizeof(BCNPayload_AU915);

    GetSettings()->Session.BeaconFrequency = AU915_BEACON_FREQ_BASE;
    GetSettings()->Session.BeaconFreqHop = true;
    GetSettings()->Session.PingSlotFrequency = AU915_BEACON_FREQ_BASE;
    GetSettings()->Session.PingSlotDatarateIndex = AU915_BEACON_DR;
    GetSettings()->Session.PingSlotFreqHop = true;

    _minDatarate = lora::DR_2;
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

void ChannelPlan_GLOBAL::Init_AS923() {

    _datarates.clear();
    _channels.clear();
    _dutyBands.clear();

    DutyBand band;

    band.Index = 0;
    band.DutyCycle = 0;

    Datarate dr;

    _maxTxPower = 36;
    _minTxPower = 0;

    _minFrequency = 915000000;
    _maxFrequency = 928000000;

    MAX_PAYLOAD_SIZE = AS923_MAX_PAYLOAD_SIZE;
    MAX_PAYLOAD_SIZE_REPEATER = AS923_MAX_PAYLOAD_SIZE_REPEATER;

    _minDatarate = 0;
    _maxDatarate = 7;

    _minRx2Datarate = DR_0;
    _maxRx2Datarate = DR_7;

    _minDatarateOffset = 0;
    _maxDatarateOffset = 7;

    _numChans125k = 16;
    _numChans500k = 0;
    _numDefaultChans = AS923_DEFAULT_NUM_CHANS;

    GetSettings()->Session.UplinkDwelltime = 1;
    GetSettings()->Session.Max_EIRP  = 16;

    band.Index = 0;
    band.FrequencyMin = _minFrequency;
    band.FrequencyMax = _maxFrequency;
    band.PowerMax = 14;
    band.TimeOffEnd = 0;

    // Disable duty-cycle limits
    band.DutyCycle = 0;

    AddDutyBand(-1, band);

    switch (_plan_id) {
        case lora::ChannelPlan::AS923:
            _plan = AS923;
            _planName = "AS923";
            _as923_freq_offset = 0;
            break;
        case lora::ChannelPlan::AS923_2:
            _plan = AS923_2;
            _planName = "AS923-2";
            _as923_freq_offset = -1800000U;
            break;
        case lora::ChannelPlan::AS923_3:
            _plan = AS923_3;
            _planName = "AS923-3";
            _as923_freq_offset = -6600000U;
            break;
        case lora::ChannelPlan::AS923_4:
            _plan = AS923_4;
            _planName = "AS923-4";
            _as923_freq_offset = -5900000U;
            break;
        case lora::ChannelPlan::AS923_JAPAN:
            _plan = AS923_JAPAN;
            _planName = "AS923-JAPAN";
            _as923_freq_offset = 0;
            _minFrequency = 920600000;
            _maxFrequency = 928000000;

            _minDatarate = 2;
            _maxDatarate = 5;

            _minRx2Datarate = DR_2;
            _maxRx2Datarate = DR_5;

            _minDatarateOffset = 2;
            _maxDatarateOffset = 5;

            GetSettings()->Session.UplinkDwelltime = 1;
            GetSettings()->Session.Max_EIRP  = 13;

            _LBT_TimeUs = 5000;
            _LBT_Threshold = -80;
            break;
        case lora::ChannelPlan::AS923_JAPAN1:
            _plan = AS923_JAPAN1;
            _planName = "AS923-JAPAN1";
            _as923_freq_offset = 0;
            _minFrequency = 920600000;
            _maxFrequency = 923400000;

            _minDatarate = 2;
            _maxDatarate = 5;

            _minRx2Datarate = DR_2;
            _maxRx2Datarate = DR_5;

            _minDatarateOffset = 2;
            _maxDatarateOffset = 5;

            GetSettings()->Session.UplinkDwelltime = 1;
            GetSettings()->Session.Max_EIRP  = 16;

            _LBT_TimeUs = 5000;
            _LBT_Threshold = -80;
            break;
        case lora::ChannelPlan::AS923_JAPAN2:
            _plan = AS923_JAPAN2;
            _planName = "AS923-JAPAN2";
            _as923_freq_offset = 0;
            _minFrequency = 920600000;
            _maxFrequency = 928000000;

            _minDatarate = 2;
            _maxDatarate = 5;

            _minRx2Datarate = DR_2;
            _maxRx2Datarate = DR_5;

            _minDatarateOffset = 2;
            _maxDatarateOffset = 5;

            _dutyBands.clear();

            DutyBand band;

            band.Index = 0;
            band.DutyCycle = 100;
            band.FrequencyMin = _minFrequency;
            band.FrequencyMax = _maxFrequency;
            band.PowerMax = 14;
            band.TimeOffEnd = 0;

            AddDutyBand(-1, band);

            GetSettings()->Session.UplinkDwelltime = 1;
            GetSettings()->Session.Max_EIRP  = 16;
            break;
    }


    GetSettings()->Session.Rx2Frequency = AS923_RX2_FREQ + _as923_freq_offset;
    GetSettings()->Session.Rx2DatarateIndex = DR_2;

    GetSettings()->Session.BeaconFrequency = AS923_BEACON_FREQ + _as923_freq_offset;
    GetSettings()->Session.BeaconFreqHop = false;
    GetSettings()->Session.PingSlotFrequency = AS923_BEACON_FREQ + _as923_freq_offset;
    GetSettings()->Session.PingSlotDatarateIndex = AS923_BEACON_DR;
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

    _maxDatarate = DR_7;

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
    chan.Frequency = AS923_125K_FREQ_BASE + _as923_freq_offset;
    SetNumberOfChannels(16);

    for (uint8_t i = 0; i < AS923_DEFAULT_NUM_CHANS; i++) {
        AddChannel(i, chan);
        chan.Index++;
        chan.Frequency += 200000;
    }

    chan.DrRange.Value = 0;
    chan.Frequency = 0;

    for (uint8_t i = AS923_DEFAULT_NUM_CHANS; i < 16; i++) {
        AddChannel(i, chan);
        chan.Index++;
    }

    SetChannelMask(0, 0x03);


    // Add downlink channel defaults
    chan.Index = 0;
    _dlChannels.resize(16);
    for (uint8_t i = 0; i < 16; i++) {
        AddDownlinkChannel(i, chan);
        chan.Index++;
    }

    GetSettings()->Session.TxPower = GetSettings()->Network.TxPower;

}

void ChannelPlan_GLOBAL::DefaultLBT() {
    _LBT_TimeUs = 0;
    _LBT_Threshold = 0;

    if (IsPlanAS923()) {
        if (_plan_id == AS923_JAPAN2) {
            _LBT_TimeUs = 128;
            _LBT_Threshold = -80;
        } else if (_plan_id == AS923_JAPAN1
          || _plan_id == AS923_JAPAN) {
            _LBT_TimeUs = 5000;
            _LBT_Threshold = -80;
        }
    }
}



void ChannelPlan_GLOBAL::Init_KR920() {

}

void ChannelPlan_GLOBAL::Init_IN865() {

}

void ChannelPlan_GLOBAL::Init_RU864() {

}




uint8_t ChannelPlan_GLOBAL::HandleJoinAccept(const uint8_t* buffer, uint8_t size) {

    // byte 28 idicates CFList or ChMask content
    if (IsPlanFixed() && size > 17 && buffer[28] == 0x01) {
        for (int i = 13; i < size - 5; i += 2) {
            SetChannelMask((i-13)/2, buffer[i+1] << 8 | buffer[i]);
        }
    } else if (IsPlanDynamic() && size > 17 && buffer[28] == 0x00) {
        Channel ch;
        int index = 3;
        for (int i = 13; i < size - 5; i += 3) {

            ch.Frequency = ((buffer[i]) | (buffer[i + 1] << 8) | (buffer[i + 2] << 16)) * 100u;

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

uint8_t ChannelPlan_GLOBAL::GetMinDatarate() {
    if (IsPlanFixed() && GetSettings()->Network.Mode == lora::PEER_TO_PEER)
        return 8;
    else {
        if (GetSettings()->Session.UplinkDwelltime == 1)
            return lora::DR_2;
        else
            return _minDatarate;
    }
}

uint8_t ChannelPlan_GLOBAL::GetMaxDatarate() {
    if (IsPlanFixed() && GetSettings()->Network.Mode == lora::PEER_TO_PEER)
        return 13;
    else
        return _maxDatarate;
}

uint8_t ChannelPlan_GLOBAL::SetTxConfig() {

    uint8_t band = GetDutyBand(GetChannel(_txChannel).Frequency);
    Datarate txDr = GetDatarate(GetSettings()->Session.TxDatarate);
    int8_t max_pwr = _dutyBands[band].PowerMax;
    uint8_t chans_enabled = 0;

    int8_t pwr = GetSettings()->Session.TxPower;

    switch (_plan) {
        case US915:
        {
            if (txDr.Bandwidth == BW_125) {
                // spec states that if < 50 125kHz channels are enabled, power is limited to 21dB conducted
                chans_enabled += CountBits(_channelMask[0]);
                chans_enabled += CountBits(_channelMask[1]);
                chans_enabled += CountBits(_channelMask[2]);
                chans_enabled += CountBits(_channelMask[3]);

                if (chans_enabled < 50 && pwr > 21) {
                    pwr = 21;
                }
            }

            pwr = std::min < int8_t > (pwr, max_pwr);
        }
        break;
        case AU915:
        {
            // Antenna gain is allowed up to +6 dBi, gain above 6 must be reduced from the conducted output
            if (pwr + GetSettings()->Network.AntennaGain >= max_pwr + 6 && GetSettings()->Network.AntennaGain > 6) {
                max_pwr -= (GetSettings()->Network.AntennaGain - 6);
            }

            pwr = std::min < int8_t > (pwr, max_pwr);
        }
        break;
        default:
            pwr = std::min < int8_t > (GetSettings()->Session.TxPower, max_pwr);
            pwr -= GetSettings()->Network.AntennaGain;
            break;
    }

    for (int i = 20; i >= 0; i--) {
        if (RADIO_POWERS[i] <= pwr) {
            pwr = i;
            break;
        }
        if (i == 0) {
            pwr = i;
        }
    }

    logDebug("Session pwr: %d ant: %d max: %d", GetSettings()->Session.TxPower, GetSettings()->Network.AntennaGain, max_pwr);
    logDebug("Radio Power index: %d output: %d total: %d", pwr, RADIO_POWERS[pwr], RADIO_POWERS[pwr] + GetSettings()->Network.AntennaGain);

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

    logDebug("TX PWR: %u DR: %u SF: %u BW: %u CR: %u PL: %u CRC: %d IQ: %d", pwr, txDr.Index, sf, bw, cr, pl, crc, iq);

    return LORA_OK;
}


uint8_t ChannelPlan_GLOBAL::AddChannel(int8_t index, Channel channel) {
    logTrace("Add Channel %d : %lu : %02x %d", index, channel.Frequency, channel.DrRange.Value, _channels.size());

    assert(index < (int) _channels.size());

    if (index >= 0) {
        _channels[index] = channel;
    } else {
        _channels.push_back(channel);
    }

    return LORA_OK;
}

Channel ChannelPlan_GLOBAL::GetChannel(int8_t index) {
    Channel chan;
    memset(&chan, 0, sizeof(Channel));

    if (IsPlanFixed()) {
        if (_channels.size() > 0) {
            chan = _channels[index];
        } else {
            if (index < 64) {
                chan.Index = index;
                chan.DrRange.Fields.Min = _minDatarate;
                chan.DrRange.Fields.Max = _maxDatarate - 1;
                chan.Frequency = _freqUBase125k + (_freqUStep125k * index);
            } else if (index < 72) {
                chan.Index = index;
                chan.DrRange.Fields.Min = _maxDatarate;
                chan.DrRange.Fields.Max = _maxDatarate;
                chan.Frequency = _freqUBase500k + (_freqUStep500k * (index - 64));
            }
        }
    } else {
        chan = _channels[index];
    }

    return chan;
}

uint8_t ChannelPlan_GLOBAL::SetFrequencySubBand(uint8_t sub_band) {

    if (IsPlanFixed()) {
        _txFrequencySubBand = sub_band;

        if (sub_band > 0) {
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
    }

    return LORA_OK;
}


void ChannelPlan_GLOBAL::LogRxWindow(uint8_t wnd) {

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

    if (sf == SF_FSK) {
        sf = 0;
        bw = 0;
        crc = true;
    }

    logTrace("RX%d on freq: %lu", wnd, freq);
    logTrace("RX DR: %u SF: %u BW: %u CR: %u PL: %u STO: %u CRC: %d IQ: %d", rxDr.Index, sf, bw, cr, pl, sto, crc, iq);
}

RxWindow ChannelPlan_GLOBAL::GetRxWindow(uint8_t window, int8_t id) {
    RxWindow rxw;
    int index = 0;

    if (P2PEnabled()) {
        rxw.Frequency = GetSettings()->Network.TxFrequency;
        index = GetSettings()->Session.TxDatarate;
    } else {
        switch (window) {
        case RX_1:
            if (IsPlanFixed()) {
                if (_txChannel < _numChans125k) {
                    if (GetSettings()->Network.Mode == lora::PRIVATE_MTS)
                        rxw.Frequency = _freqDBase500k + (_txChannel / 8) * _freqDStep500k;
                    else
                        rxw.Frequency = _freqDBase500k + (_txChannel % 8) * _freqDStep500k;
                } else
                    rxw.Frequency = _freqDBase500k + (_txChannel - _numChans125k) * _freqDStep500k;

                if (_plan == US915) {
                    if (GetSettings()->Session.TxDatarate <= DR_4) {
                        index = GetSettings()->Session.TxDatarate + 10 - GetSettings()->Session.Rx1DatarateOffset;

                        if (index < DR_8)
                            index = DR_8;
                        if (index > DR_13)
                            index = DR_13;
                    } else if (GetSettings()->Session.TxDatarate >= DR_8) {
                        index = GetSettings()->Session.TxDatarate - GetSettings()->Session.Rx1DatarateOffset;
                        if (index < DR_8)
                            index = DR_8;
                    }
                } else {
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
                }
            } else {
                rxw.Frequency = _channels[_txChannel].Frequency;
                if (IsPlanAS923()) {
                    if (GetSettings()->Session.Rx1DatarateOffset >= 6) {
                        index =  GetSettings()->Session.TxDatarate + (GetSettings()->Session.Rx1DatarateOffset == 6 ? 1 : 2);
                        index = std::min<int>(index, _maxDatarate);
                    } else if (GetSettings()->Session.TxDatarate > GetSettings()->Session.Rx1DatarateOffset) {
                        index = GetSettings()->Session.TxDatarate - GetSettings()->Session.Rx1DatarateOffset;
                    } else {
                        index = 0;
                    }
                } else {
                    if (GetSettings()->Session.TxDatarate > GetSettings()->Session.Rx1DatarateOffset) {
                        index = GetSettings()->Session.TxDatarate - GetSettings()->Session.Rx1DatarateOffset;
                    } else {
                        index = 0;
                    }
                }
            }
            break;

        case RX_BEACON:
            rxw.Frequency = GetSettings()->Session.BeaconFrequency;
            switch (_plan) {
                case US915:
                    index = US915_BEACON_DR;
                    break;
                case AU915:
                    index = AU915_BEACON_DR;
                    break;
                case EU868:
                    index = EU868_BEACON_DR;
                    break;
            }
            if (IsPlanAS923()) {
                index = AS923_BEACON_DR;
            }
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
            if (IsPlanFixed() && GetSettings()->Network.Mode == lora::PRIVATE_MTS) {
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

uint8_t ChannelPlan_GLOBAL::HandleRxParamSetup(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {
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

uint8_t ChannelPlan_GLOBAL::HandleNewChannel(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {

    if (IsPlanFixed()) {
        // Not Supported in US915/AU915
        status = 0;
    } else {
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
    }
    return LORA_OK;
}

uint8_t ChannelPlan_GLOBAL::HandleDownlinkChannelReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {

    if (IsPlanFixed()) {
        // Not Supported in US915/AU915
        status = 0;
    } else {
        uint8_t channelIndex = 0;
        Channel chParam;

        status = 0x03;

        channelIndex = payload[index++];
        lora::CopyFreqtoInt(payload + index, chParam.Frequency);

        chParam.Index = channelIndex;
        chParam.DrRange.Value = 0;
        if (channelIndex > 15) {
            status = 0x00;
        } else {
            if (_channels[channelIndex].Frequency == 0) {
                logError("DL channel index %d not defined", channelIndex);
                status &= 0xFE;
            }

            if (chParam.Frequency != 0 &&
                (chParam.Frequency < _minFrequency || chParam.Frequency > _maxFrequency)) {
                logError("DL channel frequency %d out of range", chParam.Frequency);
                status &= 0xFD;
            }
        }

        if (status == 0x03 && GetSettings()->Session.CommandBufferIndex+1 < std::min<int>(GetMaxPayloadSize(), COMMANDS_BUFFER_SIZE)) {
            AddDownlinkChannel(channelIndex, chParam);
        }

        GetSettings()->Session.DlChannelReqAnswer = status;

        logDebug("DL Channel: index: %d freq: %d status: %d", channelIndex, chParam.Frequency, status);
    }
    return LORA_OK;
}

uint8_t ChannelPlan_GLOBAL::HandlePingSlotChannelReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {
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
        switch (_plan) {
            case US915:
                freq = US915_BEACON_FREQ_BASE;
                break;
            case AU915:
                freq = AU915_BEACON_FREQ_BASE;
                break;
            case EU868:
                freq = EU868_BEACON_FREQ;
                break;
        }
        if (IsPlanAS923()) {
            freq = AS923_BEACON_FREQ + _as923_freq_offset;
        }
        freqHop = IsPlanFixed();
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

uint8_t ChannelPlan_GLOBAL::HandleBeaconFrequencyReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {
    uint32_t freq = 0;
    bool freqHop = false;

    status = 0x01;

    freq = payload[index++];
    freq |= payload[index++] << 8;
    freq |= payload[index] << 16;
    freq *= 100;

    if (freq == 0U) {
        logInfo("Received request to reset beacon frequency to default");
        switch (_plan) {
            case US915:
                freq = US915_BEACON_FREQ_BASE;
                break;
            case AU915:
                freq = AU915_BEACON_FREQ_BASE;
                break;
            case EU868:
                freq = EU868_BEACON_FREQ;
                break;
        }
        if (IsPlanAS923()) {
            freq = AS923_BEACON_FREQ + _as923_freq_offset;
        }
        freqHop = IsPlanFixed();
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


uint8_t ChannelPlan_GLOBAL::HandleAdrCommand(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) {

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

    switch (_plan) {
        case US915:
        {
            //
            // Remark MaxTxPower = 0 and MinTxPower = 14
            //
            if (power != 0xF && power > 14) {
                status &= 0xFB; // TxPower KO
            }
        }
        break;
        case AU915:
        {
            //
            // Remark MaxTxPower = 0 and MinTxPower = 10
            //
            if (power != 0xF && power > 10) {
                status &= 0xFB; // TxPower KO
            }
        }
        break;
        case EU868:
        {
            //
            // Remark MaxTxPower = 0 and MinTxPower = 7
            //
            if (power != 0xF && power > 7) {
                status &= 0xFB; // TxPower KO
            }
        }
        break;
    }

    if (IsPlanAS923()) {
        //
        // Remark MaxTxPower = 0 and MinTxPower = 7
        //
        if (power != 0xF && power > 7) {
            status &= 0xFB; // TxPower KO
        }
    }

    if (IsPlanFixed()) {
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
                if(mask != 0) {
                    for(int i = 0; i < 8; i++) {  //0 - 7 bits
                        if(((mask >> i) & 1) == 1) { //if bit in mask is a one
                            t_125k |= (0xff << ((i % 2) * 8)); // this does either 0xff00 or 0x00ff to t_125k
                        }
                        if(i % 2 == 1) { // if 1 then both halfs of the mask were set
                            SetChannelMask(i/2, t_125k);
                            t_125k = 0; //reset mask for next two bits
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
    } else {
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
    }

    if (GetSettings()->Network.ADREnabled) {
        if (status == 0x07) {
            if (datarate != 0xF)
                GetSettings()->Session.TxDatarate = datarate;

            if (IsPlanAS923()) {
                if (power != 0xF)
                    GetSettings()->Session.TxPower = GetSettings()->Session.Max_EIRP - (power * 2);
            } else {
                if (power != 0xF)
                    GetSettings()->Session.TxPower = TX_POWERS[power];
            }

            logDebug("ADR Set Redundancy %d", nbRep);
            GetSettings()->Session.Redundancy = nbRep;
        }
    } else {
        logDebug("ADR is disabled, DR and Power not changed.");
    }

    logDebug("ADR DR: %u PWR: %u Ctrl: %02x Mask: %04x NbRep: %u Stat: %02x", datarate, power, ctrl, mask, nbRep, status);

    return LORA_OK;
}

uint8_t ChannelPlan_GLOBAL::ValidateAdrConfiguration() {
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

        if (IsPlanAS923() || _plan == AU915) {
            if (GetSettings()->Session.UplinkDwelltime != 0 && datarate < DR_2) {
                logWarning("ADR Datarate KO - TxDwelltime != 0 and DR < 2");
                status &= 0xFD; // Datarate KO
            }
        }
    }

    if (IsPlanFixed()) {
        // at least 2 125kHz channels must be enabled
        chans_enabled += CountBits(_channelMask[0]);
        chans_enabled += CountBits(_channelMask[1]);
        chans_enabled += CountBits(_channelMask[2]);
        chans_enabled += CountBits(_channelMask[3]);
        // Semtech reference (LoRaMac-node) enforces at least 2 channels
        if (datarate < 4 && chans_enabled < 2) {
            logWarning("ADR Channel Mask KO - at least 2 125kHz channels must be enabled");
            status &= 0xFE; // ChannelMask KO
        }

        switch (_plan) {
            case US915:
            {
                // if TXDR == 4 (SF8@500kHz) at least 1 500kHz channel must be enabled
                if (datarate == DR_4 && (CountBits(_channelMask[4] & 0xFF) == 0)) {
                    logWarning("ADR Datarate KO - DR4 requires at least 1 500kHz channel enabled");
                    status &= 0xFD; // Datarate KO
                }
            }
            break;
            case AU915:
            {
                // if TXDR == 6 (SF8@500kHz) at least 1 500kHz channel must be enabled
                if (datarate == DR_6 && (CountBits(_channelMask[4] & 0xFF) == 0)) {
                    logWarning("ADR Datarate KO - DR4 requires at least 1 500kHz channel enabled");
                    status &= 0xFD; // Datarate KO
                }
            }
            break;
        }
    } else {
        // mask must not contain any undefined channels
        for (int i = _numDefaultChans; i < 16; i++) {
            if ((_channelMask[0] & (1 << i)) && (_channels[i].Frequency == 0)) {
                logWarning("ADR Channel Mask KO - cannot enable undefined channel");
                status &= 0xFE; // ChannelMask KO
                break;
            }
        }
    }

    return status;
}

uint32_t ChannelPlan_GLOBAL::GetTimeOffAir()
{
    uint32_t min = 0;
    uint32_t now = std::chrono::duration_cast<std::chrono::milliseconds>(_dutyCycleTimer.elapsed_time()).count();

    if (GetSettings()->Test.DisableDutyCycle == lora::OFF) {
        min = UINT_MAX;
        int8_t band = 0;

        if (P2PEnabled() || GetSettings()->Network.TxFrequency != 0) {
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

void ChannelPlan_GLOBAL::UpdateDutyCycle(uint32_t freq, uint32_t time_on_air_ms) {
    _dutyCycleTimer.start();

    if (GetSettings()->Session.MaxDutyCycle > 0 && GetSettings()->Session.MaxDutyCycle <= 15) {
        GetSettings()->Session.AggregatedTimeOffEnd = _dutyCycleTimer.read_ms() + time_on_air_ms * GetSettings()->Session.AggregateDutyCycle;
        logDebug("Updated Aggregate DCycle Time-off: %lu DC: %f", GetSettings()->Session.AggregatedTimeOffEnd, 1 / float(GetSettings()->Session.AggregateDutyCycle));
    } else {
        GetSettings()->Session.AggregatedTimeOffEnd = 0;
    }

    uint32_t time_off_air = 0;
    uint32_t now = _dutyCycleTimer.read_ms();

    for (size_t i = 0; i < _dutyBands.size(); i++) {
        if (_dutyBands[i].TimeOffEnd < now) {
            _dutyBands[i].TimeOffEnd = 0;
        } else {
            _dutyBands[i].TimeOffEnd -= now;
        }

        if (freq >= _dutyBands[i].FrequencyMin && freq <= _dutyBands[i].FrequencyMax) {
            logDebug("update TOE: freq: %d i:%d toa: %d DC:%d", freq, i, time_on_air_ms, _dutyBands[i].DutyCycle);

            if (_plan == EU868 && freq > EU868_VAR_FREQ_MIN && freq < EU868_VAR_FREQ_MAX && (GetSettings()->Session.TxPower + GetSettings()->Network.AntennaGain) <= 7) {
                _dutyBands[i].TimeOffEnd = 0;
            } else {
                time_off_air = time_on_air_ms * _dutyBands[i].DutyCycle;
                _dutyBands[i].TimeOffEnd = time_off_air;
            }
        }
    }

    ResetDutyCycleTimer();
}

std::vector<uint32_t> lora::ChannelPlan_GLOBAL::GetChannels() {
    std::vector < uint32_t > chans;

    if (IsPlanFixed() &&  GetSettings()->Network.FrequencySubBand > 0) {
        uint8_t chans_per_group = 8;
        size_t start = (GetSettings()->Network.FrequencySubBand - 1) * chans_per_group;
        for (int8_t i = start; i < int8_t(start + chans_per_group); i++) {
            chans.push_back(GetChannel(i).Frequency);
        }
        chans.push_back(GetChannel(_numChans125k + (GetSettings()->Network.FrequencySubBand - 1)).Frequency);
    } else {
        int8_t numChans = IsPlanFixed() ? _numChans : _channels.size();
        for (int8_t i = 0; i < numChans; i++) {
            chans.push_back(GetChannel(i).Frequency);
        }
    }

    chans.push_back(GetRxWindow(2).Frequency);

    return chans;
}

std::vector<uint8_t> lora::ChannelPlan_GLOBAL::GetChannelRanges() {
    std::vector < uint8_t > ranges;

    if (IsPlanFixed() && GetSettings()->Network.FrequencySubBand > 0) {
        uint8_t chans_per_group = 8;
        size_t start = (GetSettings()->Network.FrequencySubBand - 1) * chans_per_group;
        for (int8_t i = start; i < int8_t(start + chans_per_group); i++) {
            ranges.push_back(GetChannel(i).DrRange.Value);
        }
        ranges.push_back(GetChannel(_numChans125k + (GetSettings()->Network.FrequencySubBand - 1)).DrRange.Value);
    } else {
        int8_t numChans = IsPlanFixed() ? _numChans : _channels.size();
        for (int8_t i = 0; i < numChans; i++) {
            ranges.push_back(GetChannel(i).DrRange.Value);
        }
    }

    ranges.push_back(GetRxWindow(2).DatarateIndex);

    return ranges;

}

void lora::ChannelPlan_GLOBAL::EnableDefaultChannels() {
    if (IsPlanFixed()) {
        SetFrequencySubBand(GetFrequencySubBand());
    } else {
        if (_numDefaultChans == 3)
            _channelMask[0] |= 0x0007;
        else if (_numDefaultChans == 2)
            _channelMask[0] |= 0x0003;
    }
}

uint8_t ChannelPlan_GLOBAL::GetNextChannel()
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

        _dutyBands[0].PowerMax = 26;
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
    uint32_t now = std::chrono::duration_cast<std::chrono::milliseconds>(_dutyCycleTimer.elapsed_time()).count();

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

    if (IsPlanFixed()) {
        if (GetTxDatarate().Bandwidth == BW_500) {
            _dutyBands[0].PowerMax = 26;
        } else {
            if (nbEnabledChannels < 50)
                _dutyBands[0].PowerMax = 21;
            else
                _dutyBands[0].PowerMax = 30;
        }
        logInfo("Adjust PowerMax to %d", _dutyBands[0].PowerMax);
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

        for (uint8_t j = rand_r(0, nbEnabledChannels - 1); std::chrono::duration_cast<std::chrono::milliseconds>(tmr.elapsed_time()).count() < timeout; j++) {
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

uint8_t lora::ChannelPlan_GLOBAL::GetJoinDatarate() {
    uint8_t dr = GetSettings()->Session.TxDatarate;

    if (IsPlanFixed()) {
        static uint8_t fsb = 1;
        static uint8_t dr4_fsb = 1;
        static bool altdr = false;

        if (GetSettings()->Test.DisableRandomJoinDatarate == lora::OFF) {
            if (GetSettings()->Network.FrequencySubBand == 0) {
                if (fsb < 9) {
                    SetFrequencySubBand(fsb);
                    logDebug("JoinDatarate setting frequency sub band to %d",fsb);
                    fsb++;
                    dr = lora::DR_0;
                    dr = (_plan == US915 ? lora::DR_0 : lora::DR_2); // US or AU
                } else {
                    dr = (_plan == US915 ? lora::DR_4 : lora::DR_6); // US or AU
                    fsb = 1;
                    dr4_fsb++;
                    if(dr4_fsb > 8)
                        dr4_fsb = 1;
                    SetFrequencySubBand(dr4_fsb);
                }
            } else if (altdr && CountBits(_channelMask[4] > 0)) {
                dr = (_plan == US915 ? lora::DR_4 : lora::DR_6); // US or AU
            } else {
                dr = (_plan == US915 ? lora::DR_0 : lora::DR_2); // US or AU
            }
            altdr = !altdr;
        }
    } else {
        static uint8_t cnt = 1;

        if (GetSettings()->Test.DisableRandomJoinDatarate == lora::OFF) {
            if (!IsPlanAS923() && (cnt++ % 20) == 0) {
                dr = lora::DR_0;
            } else if (!IsPlanAS923() && (cnt % 16) == 0) {
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
    }
    return dr;
}

uint8_t lora::ChannelPlan_GLOBAL::CalculateJoinBackoff(uint8_t size) {

    time_t now = time(NULL);
    uint32_t time_on_max = 0;
    static uint32_t time_off_max = 15;
    uint32_t rand_time_off = 0;
    static uint16_t join_cnt = 0;

    // TODO: calc time-off-max based on RTC time from JoinFirstAttempt, time-off-max is lost over sleep

    if ((time_t)GetSettings()->Session.JoinTimeOffEnd > now) {
        return LORA_JOIN_BACKOFF;
    }

    uint32_t secs_since_first_attempt = (now - GetSettings()->Session.JoinFirstAttempt);
    uint16_t hours_since_first_attempt = secs_since_first_attempt / (60 * 60);

    if (IsPlanFixed()) {
        join_cnt = (join_cnt+1) % 16;
    } else {
        join_cnt = (join_cnt+1) % 8;
    }

    if (GetSettings()->Session.JoinFirstAttempt == 0) {
        /* 1 % duty-cycle for first hour
         * 0.1 % next 10 hours
         * 0.01 % upto 24 hours         */
        GetSettings()->Session.JoinFirstAttempt = now;
        GetSettings()->Session.JoinTimeOnAir += GetTimeOnAir(size);
        GetSettings()->Session.JoinTimeOffEnd = now + rand_r(GetSettings()->Network.JoinDelay + 2, GetSettings()->Network.JoinDelay + 3);
    } else if (join_cnt == 0) {
        if (hours_since_first_attempt < 1) {
            time_on_max = 36000;
            rand_time_off = rand_r(time_off_max / 2, time_off_max + 1);
            // time off max 1 hour
            time_off_max = std::min < uint32_t > (time_off_max * 2, 60 * 60);

            if (GetSettings()->Session.JoinTimeOnAir < time_on_max) {
                GetSettings()->Session.JoinTimeOnAir += GetTimeOnAir(size);
                GetSettings()->Session.JoinTimeOffEnd = now + rand_time_off;
            } else {
                logWarning("Max time-on-air limit met for current join backoff period");
                GetSettings()->Session.JoinTimeOffEnd = GetSettings()->Session.JoinFirstAttempt + 60 * 60;
            }
        } else if (hours_since_first_attempt < 11) {
            if (GetSettings()->Session.JoinTimeOnAir < 36000) {
                GetSettings()->Session.JoinTimeOnAir = 36000;
            }
            time_on_max = 72000;
            rand_time_off = rand_r(time_off_max / 2, time_off_max + 1);
            // time off max 1 hour
            time_off_max = std::min < uint32_t > (time_off_max * 2, 60 * 60);

            if (GetSettings()->Session.JoinTimeOnAir < time_on_max) {
                GetSettings()->Session.JoinTimeOnAir += GetTimeOnAir(size);
                GetSettings()->Session.JoinTimeOffEnd = now + rand_time_off;
            } else {
                logWarning("Max time-on-air limit met for current join backoff period");
                GetSettings()->Session.JoinTimeOffEnd = GetSettings()->Session.JoinFirstAttempt + 11 * 60 * 60;
            }
        } else {
            if (GetSettings()->Session.JoinTimeOnAir < 72000) {
                GetSettings()->Session.JoinTimeOnAir = 72000;
            }

            uint32_t join_time = 1200;

            if (IsPlanFixed()) {
                // 16 join attempts is ~3192 ms, check if this is the third of the 24 hour period
                // join time is not used
                join_time = 0;
            }

            time_on_max = 80700;
            time_off_max = 1 * 60 * 60; // 1 hour
            rand_time_off = rand_r(time_off_max / 2, time_off_max);

            if (GetSettings()->Session.JoinTimeOnAir < time_on_max - join_time) {
                GetSettings()->Session.JoinTimeOnAir += GetTimeOnAir(size);
                GetSettings()->Session.JoinTimeOffEnd = now + rand_time_off;
            } else {
                logWarning("Max time-on-air limit met for current join backoff period");
                // Reset the join time on air and set end of restriction to the next 24 hour period
                GetSettings()->Session.JoinTimeOnAir = 72000;
                uint16_t days = (now - GetSettings()->Session.JoinFirstAttempt) / (24 * 60 * 60) + 1;
                logWarning("days : %d", days);
                GetSettings()->Session.JoinTimeOffEnd = GetSettings()->Session.JoinFirstAttempt + ((days * 24) + 11) * 60 * 60;
            }
        }

        logWarning("JoinBackoff: %lu seconds  Time On Air: %lu / %lu", GetSettings()->Session.JoinTimeOffEnd - now, GetSettings()->Session.JoinTimeOnAir, time_on_max);
    } else {
        if (IsPlanFixed()) {
            GetSettings()->Session.JoinTimeOnAir += GetTimeOnAir(size);
            GetSettings()->Session.JoinTimeOffEnd = now + rand_r(GetSettings()->Network.JoinDelay + 2, GetSettings()->Network.JoinDelay + 3);
        } else {
            GetSettings()->Session.JoinTimeOnAir += GetTimeOnAir(size);
            GetSettings()->Session.JoinTimeOffEnd = now + (GetTimeOnAir(size) / 10);
        }
    }

    return LORA_OK;
}

uint8_t ChannelPlan_GLOBAL::HandleMacCommand(uint8_t* payload, uint8_t& index) {
    logDebug("GLOBAL Handle Mac index: %d", index);

    if (_plan == AU915 || IsPlanAS923()) {
        switch (payload[index++]) {
            case SRV_MAC_TX_PARAM_SETUP_REQ: {
                uint8_t eirp_dwell = payload[index++];

                GetSettings()->Session.DownlinkDwelltime = eirp_dwell >> 5 & 0x01;
                GetSettings()->Session.UplinkDwelltime = eirp_dwell >> 4 & 0x01;
                //change data rate with if dwell time changes
                if(GetSettings()->Session.UplinkDwelltime == 0) {
                    _minDatarate = lora::DR_0;
                } else {
                    _minDatarate = lora::DR_2;
                    if(GetSettings()->Session.TxDatarate < lora::DR_2) {
                        GetSettings()->Session.TxDatarate = lora::DR_2;
                        logDebug("Datarate is now DR%d",GetSettings()->Session.TxDatarate);
                    }
                }

                if (_plan == AU915)
                    GetSettings()->Session.Max_EIRP = AU915_MAX_ERP_VALUES[(eirp_dwell & 0x0F)];
                else if (_plan )
                logDebug("buffer index %d", GetSettings()->Session.CommandBufferIndex);
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
    } else {
        return LORA_ERROR;
    }

    return LORA_OK;
}

uint8_t ChannelPlan_GLOBAL::GetMaxPayloadSize(uint8_t dr) {
    if (GetSettings()->Session.UplinkDwelltime == 1) {
        if (_plan == AU915) {
            if (GetSettings()->Network.RepeaterMode)
                return AU915_MAX_PAYLOAD_SIZE_REPEATER_400[dr];
            else
                return AU915_MAX_PAYLOAD_SIZE_400[dr];
        } else if (IsPlanAS923()) {
            if (GetSettings()->Network.RepeaterMode)
                return AS923_MAX_PAYLOAD_SIZE_REPEATER_400[dr];
            else
                return AS923_MAX_PAYLOAD_SIZE_400[dr];
        }
    } else {
        if (GetSettings()->Network.RepeaterMode)
            return MAX_PAYLOAD_SIZE_REPEATER[dr];
        else
            return MAX_PAYLOAD_SIZE[dr];
    }

    return 0;
}


void ChannelPlan_GLOBAL::DecrementDatarate() {
    if(GetSettings()->Session.UplinkDwelltime == 0) {
        _minDatarate = lora::DR_0;
    } else {
        _minDatarate = lora::DR_2;
    }

    if (GetSettings()->Session.TxDatarate > _minDatarate) {
        GetSettings()->Session.TxDatarate--;
    }
}

uint8_t ChannelPlan_GLOBAL::DecodeBeacon(const uint8_t* payload, size_t size, BeaconData_t& data) {
    uint16_t crc1, crc1_rx, crc2, crc2_rx;

    if (_plan == US915) {
        const BCNPayload_US915* beacon = (const BCNPayload_US915*)payload;

        // First check the size of the packet
        if (size != sizeof(BCNPayload_US915))
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
    } else if (_plan == AU915) {
        const BCNPayload_AU915* beacon = (const BCNPayload_AU915*)payload;

        // First check the size of the packet
        if (size != sizeof(BCNPayload_AU915))
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
    } else if (_plan == EU868) {
        const BCNPayload_EU868* beacon = (const BCNPayload_EU868*)payload;

        // First check the size of the packet
        if (size != sizeof(BCNPayload_EU868))
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
    } else if (IsPlanAS923()) {
        const BCNPayload_AS923* beacon = (const BCNPayload_AS923*)payload;

        // First check the size of the packet
        if (size != sizeof(BCNPayload_AS923))
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
    }

    return LORA_OK;
}

void ChannelPlan_GLOBAL::FrequencyHop(uint32_t time, uint32_t period, uint32_t devAddr) {
    uint32_t channel;
    uint32_t freq;

    if (_plan == US915) {
        if (GetSettings()->Session.BeaconFreqHop) {
            channel = (time / period) % US915_BEACON_CHANNELS;
            freq = US915_BEACON_FREQ_BASE + (channel * US915_BEACON_FREQ_STEP);
            GetSettings()->Session.BeaconFrequency = freq;
        }

        if (GetSettings()->Session.PingSlotFreqHop) {
            channel = (time / period + devAddr) % US915_BEACON_CHANNELS;
            freq = US915_BEACON_FREQ_BASE + (channel * US915_BEACON_FREQ_STEP);
            GetSettings()->Session.PingSlotFrequency = freq;
        }

        for (int i = 0; i < lora::MAX_MULTICAST_SESSIONS; ++i) {
            if (GetSettings()->Multicast[i].Address != 0) {
                channel = (time / period + GetSettings()->Multicast[i].Address) % US915_BEACON_CHANNELS;
                freq = US915_BEACON_FREQ_BASE + (channel * US915_BEACON_FREQ_STEP);
                GetSettings()->Multicast[i].Frequency = freq;
            }
        }
    } else if (_plan == AU915) {
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
}
