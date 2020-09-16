/**********************************************************************
* COPYRIGHT 2020 MULTI-TECH SYSTEMS, INC.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of MULTI-TECH SYSTEMS, INC. nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/

#ifndef __FLASH_RECORD_H__
#define __FLASH_RECORD_H__

#include <stdint.h>
#include "FlashRecordStoreConfig.h"

#if FLASH_RECORD_STORE_ENABLED

namespace mts {

enum FlashRecordFlags {
    FR_FLAG_FILE_MODE       = 0x0001,
    FR_FLAG_JOURNAL_MODE    = 0x0002,
    FR_FLAG_REDUNDANCY      = 0x0010,
    FR_FLAG_BANK1_FULL      = 0x0100,
    FR_FLAG_BANK2_FULL      = 0x0200,
    FR_FLAG_DIRTY           = 0x1000,
    FR_FLAG_STALE_CRC       = 0x2000,
    FR_FLAG_EMPTY           = 0x4000,
};

enum FlashRecordSeekDir {
  FR_SEEK_SET,
  FR_SEEK_CUR,
  FR_SEEK_END
};

class FlashRecordStore;  // Forward declaration for friendship

class FlashRecord {
public:
    FlashRecord();
    void* source;       //!< Pointer to source object (when not in file mode)
    uint32_t ssize;     //!< Source size
    uint32_t bsize;     //!< Allocated bank size
    uint32_t fsize;     //!< Size of record in flash
    uint32_t asize;     //!< Total allocated flash size
    uint16_t version;   //!< Record version

    int32_t open();
    int32_t close();
    int32_t erase();
    int32_t validate();

    uint64_t getCrc();
    bool isEmpty();
protected:
    FlashRecordStore* _store;    // Pointer to store that owns this record
private:
    friend FlashRecordStore;
    uint16_t _flags;            // Flags for record state
    uint8_t _active;            // Active bank index
    uint32_t _bank[2];          // Flash bank addresses
    uint32_t _cursor;           // Offset into bank for read/write
    uint32_t _counter;          // Incremented each time this record is written
    uint64_t _crc;              // CRC of data in flash
    bool _open;                 // True if the record has been opened
};

#if FLASH_RECORD_STORE_FILE_ENABLE
class FlashFileRecord : public FlashRecord {
public:
    FlashFileRecord(uint32_t bsize, uint16_t version);
    int32_t read(uint8_t* data, uint32_t size);
    int32_t write(uint8_t* data, uint32_t size);
    int32_t seek(int32_t offset, int32_t whence = FR_SEEK_SET);
    int32_t pad(uint32_t size);
    int32_t calculateCrc(uint64_t& crc, uint32_t start, uint32_t size);
    int32_t finalize();

};
#endif


#if FLASH_RECORD_STORE_JOURNAL_ENABLE
class FlashJournalRecord : public FlashRecord {
public:
    FlashJournalRecord(void* source, uint32_t ssize, uint32_t bank_size, bool redundant, uint16_t version);
    int32_t load();
    int32_t save();
};
#endif
} // namespace mts

#endif // FLASH_RECORD_STORE_ENABLED

#endif // __FLASH_RECORD_H__
