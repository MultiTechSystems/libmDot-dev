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

        void setMode(uint8_t mode);
        uint8_t getMode();

        void fixEventQueue();
        bool ready();
        int32_t timeToStart();
        bool getClockSynced();

        int32_t setClockOffset(uint32_t gps_time);
        int32_t getClockOffset();
        void restoreClockOffset(int32_t offset);

        void setClockUpdated(uint32_t utc_time);
        uint32_t getClockUpdated();


        bool isSendingCRC() {
        #ifdef FOTA
            return (_msg.tx.port == APP_PORT_FRAGMENTATION) && (_msg.tx.payload.at(0) == FragmentationSession::CHECKSUM);
        #else
            return false;
        #endif
        }

        enum Mode {
            DISABLED,
            ENABLED,
            RESET,
            STATUS,
            PASSTHROUGH
        };

    private:
        static void start();

        bool _enabled;
        uint8_t _mode;
        mDot* _dot;
        Thread _send_thread;
        static Fota* _instance;
        uint8_t p[242];
        bool _clk_synced = false;
        time_t _clk_updated;
        Mutex _clk_mutex;

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
