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

#ifndef __FLASH_RECORD_STORE_H__
#define __FLASH_RECORD_STORE_H__

#include <stdint.h>

#include "FlashRecord.h"
#include "FlashRecordStoreConfig.h"

#if FLASH_RECORD_STORE_ENABLED

namespace mts {

/**
 *  Error codes returned by FlashRecordStore operations.
 * 
 */
enum FlashRecordErrors {
    FR_ERR_OK = 0,                          //! No errors
    FR_ERR_FAILED              = -10000,    //! General failure
    FR_ERR_WRITE_FAILED        = -10001,    //! Failed to write to the flash device
    FR_ERR_WRITE_CHECK_FAILED  = -10002,    //! Read back or CRC check of written data failed
    FR_ERR_WRITE_BACKUP_FAILED = -10003,    //! Failed to write the redundant copy
    FR_ERR_READ_FAILED         = -10004,    //! Failed to read from the flash device
    FR_ERR_ERASE_FAILED        = -10005,    //! Failed to read from the flash device
    FR_ERR_LOAD_FAILED         = -10006,    //! Could not load a record
    FR_ERR_INVALID_OPERATION   = -10007,    //! Operation is not permitted due to record type or state
    FR_ERR_NOT_MOUNTED         = -10008,    //! The store has not been mounted
    FR_ERR_INVALID_PARAMETER   = -10009,    //! Provided parameter was invalid for the operation
    FR_ERR_NULL_PARAMETER      = -10010,    //! A parameter was NULL
    FR_ERR_CORRUPT_RECORD      = -10011,    //! CRC check of record failed
    FR_ERR_OUT_OF_RANGE        = -10012,    //! A parameter fell outside of an allowable range
    FR_ERR_ALLOCATED_SIZE      = -10013,    //! The record sizes required overflow the allocated store size
    FR_ERR_LOW_VOTLAGE         = -10014,    //! System voltage check failed and flash operations should not be performed
    FR_ERR_FALLBACK            = -10015     //! Fell back to a previous record due to corruption
};


/**
 * Function to read data from the external flash device.
 * @param  addr Starting address to read
 * @param  size Number of bytes to read
 * @param  dst  Memory location to store data
 * @return 0 or number of bytes read on success, -1 or less on failure
 */
typedef int32_t (*FlashBlockRead)(uint32_t addr, uint32_t size, uint8_t *dst);

/**
 * Function to write data to the external flash device.
 * @param  addr Starting address to writing
 * @param  size Number of bytes to write
 * @param  dst  Memory location of data to write
 * @return 0 or number of bytes written on success, -1 or less on failure
 */
typedef int32_t (*FlashBockWrite)(uint32_t addr, uint32_t size, uint8_t *src);

/**
 * Function to erase a block on the external flash device.
 * @param  addr Starting address to erase
 * @param  size Number of bytes to erase
 * @return 0 on success, -1 or less on failure
 */
typedef int32_t (*FlashBlockErase)(uint32_t addr, uint32_t size);

/**
 * Function to calcualate crc64.
 * @param  crc  Starting crc value
 * @param  data Memory location of data to process
 * @param  size Number of bytes to process
 * @return Updated CRC64 of data
 */
typedef uint64_t (*FlashCalcCrc64)(uint64_t crc, const uint8_t* data, uint64_t size);

/**
 * Function to determine if system voltage is valid for flash operations.
 * @return True if voltage is low
 */
typedef bool (*FlashVoltageLow)();

/**
 * Function to lock access to the store.
 * @return 0 on success, -1 or less on failure
 */
typedef int32_t (*FlashRecordStoreLock)();

/**
 * Function to unlock access to the store.
 * @return 0 on success, -1 or less on failure
 */
typedef int32_t (*FlashRecordStoreUnlock)();

/** Class provides functions for read and writing records to an external flash
    device.  Functions for interacting with the device must be provided. */
class FlashRecordStore
{
public:
    /**
     * Constructor.
     * @param read      Function to read data from the external flash device
     * @param write     Function to write data to the external flash device
     * @param erase     Function to erase a block on the external flash device
     * @param crc_calc  Function to calcualate crc64
     * @param vlow      Function to determine if system voltage is valid for flash operations
     * @param lock      Function to lock access to the store (NULL if not multithreaded)
     * @param unlock    Function to unlock access to the store (NULL if not multithreaded)
     */
    FlashRecordStore(FlashBlockRead read, FlashBockWrite write, FlashBlockErase erase, 
                    FlashCalcCrc64 crc_calc, FlashVoltageLow vlow,
                    FlashRecordStoreLock lock, FlashRecordStoreUnlock unlock);

    /**
     * Set the store parameters and scan the external flash for valid records.
     * @param  root      Root address of the store
     * @param  allocated Bytes allocated to the store
     * @param  records   Array of records
     * @param  n_records Number of records
     * @return           FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t mount(uint32_t root, uint32_t allocated, FlashRecord** records, uint16_t n_records);

    /**
     * Set the store to unmounted.          
     */
    int32_t unmount();

    /**
     * Scan allocated area of existing records.
     * @param  root      Root address of the store
     * @param  allocated Bytes allocated to the store
     * @param  records   Array of records
     * @param  n_records Number of records
     * @return           FR_ERR_OK if a record data is found, otherwise FR_ERR_FAILED
     */
    int32_t scan(uint32_t root, uint32_t allocated, FlashRecord** records, uint16_t n_records);

    /**
     * Open a record
     * @param  record Pointer to record to open
     * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t open(FlashRecord* record);

    /**
     * Close a record.
     * @param  record Pointer to record to close
     * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t close(FlashRecord* record);

    /**
     * Read data from a record.
     * @param  record Pointer to record to read
     * @param  data   Memory location to store data
     * @param  size   Number of bytes to read
     * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t read(FlashRecord* record, uint8_t* data, uint32_t size);

    /**
     * Write data to a record.
     * @param  record Pointer to record to write
     * @param  data   Data to write
     * @param  size   Size of data to write
     * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t write(FlashRecord* record, uint8_t* data, uint32_t size);


#if FLASH_RECORD_STORE_JOURNAL_ENABLE
    /**
     * Load saved data to the source of a journal record.  The last valid record
     * will be loaded.
     * @param  record Pointer to journal record to load
     * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t load(FlashRecord* record);

    /**
     * Save source data of a journal record.  A new journal entry is written to
     * the current data bank.  An old data bank is erased once the current bank
     * reaches a certain threshold.
     * @param  record Pointer to journal record to save
     * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t save(FlashRecord* record);
#endif
#if FLASH_RECORD_STORE_FILE_ENABLE
    /**
     * Finalize a file record.  Calculate the CRC of the entire file and write
     * the bank header to indicate it is a complete file.
     * @param  record File record to finalize
     * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t finalize(FlashRecord* record);

    /**
     * Move the write/read cursor to the desired location.
     * @param  record Pointer to file record to seek
     * @param  offset Number of bytes from whence to set the cursor
     * @param  whence Indicates where the offset will be calculated from
     * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t seek(FlashRecord* record, int32_t offset, int32_t whence);

    /**
     * Pad a file to a given size.  Zeros are written in the gap.
     * @param  record Pointer to file record to pad
     * @param  size   Desired size of stored file
     * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t pad(FlashRecord* record, uint32_t size);

    /**
     * Calculate the CRC64 of a file's content.
     * @param  record Pointer to file record to read
     * @param  crc    Resulting CRC
     * @param  start  Offset from beginning of file to start CRC calculation
     * @param  size   Length to calculate CRC over
     * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t calculateCrc(FlashRecord* record,  uint64_t& crc, uint32_t start, uint32_t size);
#endif
    /**
      * Erase stored data for the given record
      * @param  record Pointer to record to erase
      * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
      */
     int32_t erase(FlashRecord* record);

    /**
     * Validate the stored data against its recorded CRC.
     * @param  record Pointer to record to validate
     * @return        FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t validate(FlashRecord* record);

    /**
     * Erase the entire allocated storage area.
     * @return           FR_ERR_OK on success, FR_ERR_FAILED or less on failure
     */
    int32_t format();

#if FLASH_RECORD_STORE_JOURNAL_ENABLE
    /**
     * Initialize a record with journaling storage
     * @param  record    Pointer to record to initialize
     * @param  source    Pointer to data that will be stored or loaded
     * @param  ssize     Size of source data
     * @param  bank_size Size of each memory bank to allocate
     * @param  redundant Set to true to write a backup copy whenever the record is saved
     * @param  version   Version of source data
     * @return           FR_ERR_OK
     */
    static int32_t initJournalRecord(FlashRecord* record, void* source, uint32_t ssize, uint32_t bank_size, bool redundant, uint16_t version);
#endif
#if FLASH_RECORD_STORE_FILE_ENABLE
    /**
     * Initialize a record with file-like storage.
     * @param  record  Pointer to record to initialize
     * @param  asize   Number of bytes to allocate
     * @param  version Version of file
     * @return         FR_ERR_OK
     */
    static int32_t initFileRecord(FlashRecord* record, uint32_t asize, uint16_t version);
#endif

private:
    int32_t readWithRetry(uint32_t addr, uint32_t size, uint8_t *dst);
    int32_t writeWithRetry(uint32_t addr, uint32_t size, uint8_t *src);
    int32_t eraseWithRetry(uint32_t addr, uint32_t size);
    int32_t verify(uint32_t id, uint64_t exp_crc, uint32_t addr, uint32_t size);
    int32_t calculateCrc(uint64_t& crc, uint32_t addr, uint32_t size);
#if FLASH_RECORD_STORE_FILE_ENABLE
    int32_t writeFile(FlashRecord* record, uint8_t* data, uint32_t size);
    int32_t flushFile();
#endif
#if FLASH_RECORD_STORE_JOURNAL_ENABLE
    int32_t writeJournal(FlashRecord* record, uint8_t* data, uint32_t size);
    int32_t writeJournalEntry(FlashRecord* record, uint32_t* addr, uint8_t* data, uint32_t size, uint64_t data_crc);
#endif
    static int32_t initRecord(FlashRecord* record, void* source, uint32_t ssize, uint32_t asize, uint16_t flags, uint16_t version);

    bool _mounted;                      // Indicates the store is mounted
    uint32_t _root;                     // Root address of the store
    uint32_t _alloc;                    // Bytes allocation to the store
    FlashBlockRead _read;               // Flash read function
    FlashBockWrite _write;              // Flash write function
    FlashBlockErase _erase;             // Flash erase function
    FlashCalcCrc64 _crc_calc;           // CRC64 calculate function
    FlashVoltageLow _vlow;              // System voltage check function
    FlashRecordStoreLock _lock;         // Store access lock function
    FlashRecordStoreUnlock _unlock;     // Store access unlock function
#if FLASH_RECORD_STORE_FILE_ENABLE
    FlashRecord* _active_file;
    uint16_t _fwrite_index;
#endif
};

} // namespace mts

#endif // FLASH_RECORD_STORE_ENABLED

#endif // __FLASH_RECORD_STORE_H__
