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

#ifndef MULTICASTGROUP_H
#define MULTICASTGROUP_H
#include "mDot.h"
#include "mbed.h"
#include "ApplicationLayerPackage.h"
#define GPS_EPOCH 315964800U


class MulticastGroup : public ApplicationLayerPackage {
    public:
        MulticastGroup(mDot* dot);
        ~MulticastGroup();
        void reset();
        //void newTime();
        uint8_t getPort();
        void processCmd(ApplicationMessage& recv, ApplicationMessage& resp);
        int32_t timeToStart();
        void fixEventQueue();
        void setClockOffset(int32_t offset);
        int32_t getClockOffset();

        bool switchClassIfPending();
        void switchClass();
        bool isClassSwitchActive() const;
    private:
        enum MulticastCommands {
            PACKAGE_VERSION,
            STATUS,
            SETUP,
            DELETE,
            CLASS_C_SESSION,
            CLASS_B_SESSION_REQ
        };

        typedef struct {
            bool valid;
            uint8_t dr;
            uint8_t fragGroup;
            uint16_t timeout;
            uint32_t tme;
            uint32_t freq;
            uint32_t addr;
            uint32_t max_frame_count;
            us_timestamp_t timetostart;
            char dev_class;
            time_t time_setup;
            int8_t periodicity;
        } mcgroup;


        bool* _filled;
        uint8_t _groupId;
        uint8_t _ans;
        uint8_t _delay;
        uint8_t _token;
        uint8_t _dr;
        uint32_t _freq;
        uint32_t _frame_count;
        time_t _now;
        int32_t _clk_sync;

        // Thread _event_thread;
        // EventQueue _switch_class_queue;
        mcgroup _mcGroup[MULTICAST_SESSIONS];
        char _org_class;
        Mutex _class_switch_lock;

        struct {
            mcgroup* group;
            bool active;
            bool pending;
            #if defined(TARGET_MAX32660EVSYS) || defined(TARGET_MAX32630FTHR)
                Timeout timer;
            #else
                LowPowerTimeout timer;
            #endif
        } _class_switch;

        void setupClassB(uint8_t id);
        void setupClassC(uint8_t id);
        void setupClassSwitch(uint8_t id);

        void pendClassSwitch();
};
#endif
