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

#ifndef _FRAGMENTATION_SESSION_H
#define _FRAGMENTATION_SESSION_H
#ifdef FOTA

#include "mbed.h"
#include "FragmentationMath.h"
#include "ApplicationLayerPackage.h"
#include "mDot.h"
#include "WriteFile.h"



class FragmentationSession : public ApplicationLayerPackage {

    public:
        FragmentationSession(mDot* dot);
        ~FragmentationSession();
        uint8_t getPort();
        void processCmd(ApplicationMessage& downlink, ApplicationMessage& uplink);
        void reset();
        bool isReady() const;
        bool isComplete() const;
        bool allFragmentsReceived() const;
        void forceComplete();
        bool cleanUp();
        bool upgradeFile(ApplicationMessage& uplink);

        enum FragCmd {
            PACKAGE_VERSION_FRAG,
            FRAG_STATUS,
            FRAG_SESSION_SETUP,
            FRAG_SESSION_DELETE,
            DATA_FRAGMENT = 0x08,
            CHECKSUM = 0x80,
            FRAG_SESSION_COMPLETE = 0x90
        };

    private:

        typedef struct {
            uint8_t  Padding;
            uint8_t  FragmentSize;
            uint16_t NumberOfFragments;
        } FragmentationSessionOpts_t;

        typedef struct {
            bool reset;
            bool failed;
            uint8_t fragMatrix;
            uint8_t blockAckDelay;
            uint8_t mcGroupBitMask;
            uint16_t index;
            uint16_t last_frag_num;
            uint8_t validate_retry;
            FragmentationMath* math;
            FragmentationSessionOpts_t opts;
        } fragGroup;


        enum FragResult {
            FRAG_OK,
            FRAG_SIZE_INCORRECT,
            FRAG_FLASH_WRITE_ERROR,
            FRAG_NO_MEMORY,
            FRAG_COMPLETE
        };

        void reset(uint16_t num);
        bool processFrame(uint8_t fragIndex, uint16_t index, uint8_t buffer[], size_t size);
        uint32_t getDescriptor() { return _descriptor; }

        WriteFile* _fh;
        fragGroup _sessions[MULTICAST_SESSIONS];

        uint8_t ans;
        uint8_t _session_index;
        uint32_t _descriptor;
        bool _fragments_received;
        bool _complete;
        bool _validated;
        bool _ready;
};
#endif
#endif // _FRAGMENTATION_SESSION_H
