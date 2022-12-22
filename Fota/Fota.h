/**********************************************************************
* COPYRIGHT 2018 MULTI-TECH SYSTEMS, INC.
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

#ifndef FOTA_H
#define FOTA_H
#include "mDot.h"
#ifdef FOTA
#include "FragmentationSession.h"
#endif
#include "MulticastGroup.h"
#include "ApplicationLayerPackage.h"

#define FOTA_MAGIC_VAL 0xF0DAF0DA
#define FOTA_MAGIC_REG 31

class Fota {

    public:
        Fota(mDot* dot);
        ~Fota();

        static Fota* getInstance(mDot* dot);
        static Fota* getInstance();
        void processCmd(uint8_t* payload, uint8_t port, uint8_t size);
        void reset();
        bool idle();
        bool txPending();
        void enable(bool enabled);
        bool enable();
        void fixEventQueue();
        bool ready();
        int32_t timeToStart();
        bool getClockSynced();
        int32_t setClockOffset(uint32_t gps_time);

    private:
        static void start();

        bool _enabled;
        Thread _send_thread;
        uint8_t p[242];
        static Fota* _instance;
        mDot* _dot;
        bool _clk_synced = false;
#ifdef FOTA
        FragmentationSession* _frag_session;
#endif
        MulticastGroup* _mc_group;

        struct {
            ApplicationMessage rx;
            ApplicationMessage tx;
        } _msg;
};
#endif
