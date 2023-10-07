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

#include "ChannelPlan_AS923_Japan2.h"

using namespace lora;

ChannelPlan_AS923_Japan2::ChannelPlan_AS923_Japan2()
:
    ChannelPlan_AS923(NULL, NULL)
{

}

ChannelPlan_AS923_Japan2::ChannelPlan_AS923_Japan2(Settings* settings)
:
    ChannelPlan_AS923(NULL, settings)
{

}

ChannelPlan_AS923_Japan2::ChannelPlan_AS923_Japan2(SxRadio* radio, Settings* settings)
:
    ChannelPlan_AS923(radio, settings)
{

}

ChannelPlan_AS923_Japan2::~ChannelPlan_AS923_Japan2() {

}

void ChannelPlan_AS923_Japan2::Init() {
    ChannelPlan_AS923::Init();

    _plan = AS923_JAPAN;
    _planName = "AS923-JAPAN2";
    _minFrequency = 922400000;
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

    DefaultLBT();
}

void ChannelPlan_AS923_Japan2::DefaultLBT() {
    _LBT_TimeUs = 128;
    _LBT_Threshold = -80;
}

