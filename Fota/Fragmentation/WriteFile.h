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

#ifndef _WRITE_FILE_H
#define _WRITE_FILE_H

#include "mDot.h"
#include "FlashRecordStore.h"

#ifdef FOTA
class WriteFile {
    public:
#if FLASH_RECORD_STORE_FILE_ENABLE
        WriteFile(mts::FlashFileRecord* file);
#else
        WriteFile(mDot* dot);
#endif
        ~WriteFile();
        int writeFragment(uint32_t offset, uint8_t* buffer, uint32_t size);
        int padFile(uint32_t size);
        int writeFile(uint8_t* buffer, uint32_t size);
        int readFile(uint8_t* buffer, uint32_t size);
        int seekFile(uint32_t index);
        int createFile(uint16_t numOfFrags, uint8_t fragSize, uint8_t padding);
        bool completeFile();
        bool checkCrc();
        uint64_t getCrc() const;
        int cleanUp(bool complete);
        void reset();

    private:
        int doPadding(uint32_t size);
        uint8_t _padding;
        uint8_t _frag_size;
        uint16_t _num_frags;
        uint64_t _crc;
        static Mutex _lock;

#if FLASH_RECORD_STORE_FILE_ENABLE
        mts::FlashFileRecord* _fota_file;
#elif defined(TARGET_MTS_MDOT_F411RE)
        int writeWithVerify(uint8_t* buffer, uint32_t size);
        int readWithRetry(int32_t pos, uint8_t* buffer, uint32_t size);
        mDot* _dot;
        char _firmware[2];
        uint8_t* _frag;
        uint32_t _fsize;
        mDot::mdot_file _upgrade;
#endif
};
#endif
#endif // WRITE_FILE_H
