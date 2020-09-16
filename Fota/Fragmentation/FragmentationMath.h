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

#ifndef _FRAGMENTATION_MATH_H
#define _FRAGMENTATION_MATH_H
#ifdef FOTA

#include "mbed.h"
#include "mDot.h"
#include "WriteFile.h"

#define FRAG_SESSION_ONGOING    0xffffffff

#ifndef MAX_PARITY
#if defined(TARGET_MTS_MDOT_F411RE)
#define MAX_PARITY 300
#else
#define MAX_PARITY 150
#endif
#endif

class FragmentationMath
{
  public:
    FragmentationMath(mDot* dot, uint16_t frame_count, uint8_t frame_size, WriteFile* fh);
    ~FragmentationMath();
    bool Init();
    int getLostFrameCount();
    int getTotalMissingFrameCount();
    int getTotalRcvdFrameCount();
    void reset(uint16_t fcount);
    void setFrameFound(uint16_t frameCounter);
    bool processParityFrag(uint16_t frameCounter, uint8_t *pFrag);

    int FragmentationPrbs23(int x);
    bool IsPowerOfTwo(unsigned int x);
    int32_t FindMissingFrameIndex(uint16_t x);
    int32_t FindTrueFrameIndex(uint16_t x);
    void GetRowInFlash(int l, uint8_t *rowData);
    int FindFirstOne(uint8_t *boolData, int size);
    void StoreRowInFlash(uint8_t *rowData, int index);
    void XorLineData(uint8_t *dataL1, uint8_t *dataL2, int size);
    void XorLineBit(uint8_t *dataL1, uint8_t *dataL2, int size);
    void XorRowWithMatrix(uint8_t* row, int matrix_row_num);
    void FragmentationGetParityMatrixRow(int N, int M, uint8_t *matrixRow);
    void CondenseRow(uint8_t *row, int row_number, int start);
    void ExpandAndXorRow(uint8_t *row, int row_number);
    bool CheckIfMissing(int row_number, int index);
    void CompleteRow(int row_num);
    void printMatrix();

    bool _initialized;
    uint8_t _frame_size;
    uint16_t _frame_count;
    uint16_t _max_parity;
    int16_t numFramesMissing;
    uint16_t lastReceiveFrameCnt;
    int filled;

    uint8_t *matrix;
    uint8_t *matrixRow;
    uint8_t *parity_frag;
    uint8_t *missingFrameIndex;
    uint8_t *frag_in_flash;

    bool empty;
    int index_of_first;
    int matrix_row_num;
    int index;

    mDot* _dot;
    WriteFile* _fh;
};
#endif
#endif // _FRAGMENTATION_MATH_H
