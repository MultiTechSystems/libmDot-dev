/**********************************************************************
* COPYRIGHT 2015 MULTI-TECH SYSTEMS, INC.
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

#ifndef MDOT_EVENT_H
#define MDOT_EVENT_H

#include "mbed.h"
#include "mDot.h"
#include "MacEvents.h"
#include "MTSLog.h"
#include "MTSText.h"
#include <chrono>

typedef union {
        uint8_t Value;
        struct {
                uint8_t :1;
                uint8_t Tx :1;
                uint8_t Rx :1;
                uint8_t RxData :1;
                uint8_t RxSlot :2;
                uint8_t LinkCheck :1;
                uint8_t JoinAccept :1;
        } Bits;
} LoRaMacEventFlags;

typedef enum {
    LORAMAC_EVENT_INFO_STATUS_OK = 0,
    LORAMAC_EVENT_INFO_STATUS_ERROR,
    LORAMAC_EVENT_INFO_STATUS_TX_TIMEOUT,
    LORAMAC_EVENT_INFO_STATUS_RX_TIMEOUT,
    LORAMAC_EVENT_INFO_STATUS_RX_ERROR,
    LORAMAC_EVENT_INFO_STATUS_JOIN_FAIL,
    LORAMAC_EVENT_INFO_STATUS_DOWNLINK_FAIL,
    LORAMAC_EVENT_INFO_STATUS_ADDRESS_FAIL,
    LORAMAC_EVENT_INFO_STATUS_MIC_FAIL,
} LoRaMacEventInfoStatus;

/*!
 * LoRaMAC event information
 */
typedef struct {
        LoRaMacEventInfoStatus Status;
        lora::DownlinkControl Ctrl;
        bool TxAckReceived;
        bool DuplicateRx;
        uint8_t TxNbRetries;
        uint8_t TxDatarate;
        uint8_t RxPort;
        uint8_t *RxBuffer;
        uint8_t RxBufferSize;
        int16_t RxRssi;
        uint8_t RxSnr;
        uint16_t Energy;
        uint8_t DemodMargin;
        uint8_t NbGateways;
} LoRaMacEventInfo;

class mDotEvent: public lora::MacEvents {
    public:

        mDotEvent()
        :
          LinkCheckAnsReceived(false),
          DemodMargin(0),
          NbGateways(0),
          PacketReceived(false),
          RxPort(0),
          RxPayloadSize(0),
          BeaconLocked(false),
          PongReceived(false),
          PongRssi(0),
          PongSnr(0),
          ServerTimeReceived(false),
          ServerTimeSeconds(0U),
          AckReceived(false),
          DuplicateRx(false),
          TxNbRetries(0)
        {
            memset(&_flags, 0, sizeof(LoRaMacEventFlags));
            memset(&_info, 0, sizeof(LoRaMacEventInfo));
        }

        virtual ~mDotEvent() {
        }

        virtual void MacEvent(LoRaMacEventFlags *flags, LoRaMacEventInfo *info) {
            if (mts::MTSLog::getLogLevel() == mts::MTSLog::TRACE_LEVEL) {
                std::string msg = "OK";
                switch (info->Status) {
                    case LORAMAC_EVENT_INFO_STATUS_ERROR:
                        msg = "ERROR";
                        break;
                    case LORAMAC_EVENT_INFO_STATUS_TX_TIMEOUT:
                        msg = "TX_TIMEOUT";
                        break;
                    case LORAMAC_EVENT_INFO_STATUS_RX_TIMEOUT:
                        msg = "RX_TIMEOUT";
                        break;
                    case LORAMAC_EVENT_INFO_STATUS_RX_ERROR:
                        msg = "RX_ERROR";
                        break;
                    case LORAMAC_EVENT_INFO_STATUS_JOIN_FAIL:
                        msg = "JOIN_FAIL";
                        break;
                    case LORAMAC_EVENT_INFO_STATUS_DOWNLINK_FAIL:
                        msg = "DOWNLINK_FAIL";
                        break;
                    case LORAMAC_EVENT_INFO_STATUS_ADDRESS_FAIL:
                        msg = "ADDRESS_FAIL";
                        break;
                    case LORAMAC_EVENT_INFO_STATUS_MIC_FAIL:
                        msg = "MIC_FAIL";
                        break;
                    default:
                        break;
                }
                logTrace("Event: %s", msg.c_str());

                logTrace("Flags Tx: %d Rx: %d RxData: %d RxSlot: %d LinkCheck: %d JoinAccept: %d",
                         flags->Bits.Tx, flags->Bits.Rx, flags->Bits.RxData, flags->Bits.RxSlot, flags->Bits.LinkCheck, flags->Bits.JoinAccept);
                logTrace("Info: Status: %d ACK: %d Retries: %d TxDR: %d RxPort: %d RxSize: %d RSSI: %d SNR: %d Energy: %d Margin: %d Gateways: %d",
                         info->Status, info->TxAckReceived, info->TxNbRetries, info->TxDatarate, info->RxPort, info->RxBufferSize,
                         info->RxRssi, info->RxSnr, info->Energy, info->DemodMargin, info->NbGateways);
            }
        }

        virtual void TxStart() {
            logDebug("mDotEvent - TxStart");

        }

        virtual void TxDone(uint8_t dr) {
            _timeSinceTx.reset();
            _timeSinceTx.start();

            RxPayloadSize = 0;
            LinkCheckAnsReceived = false;
            PacketReceived = false;
            AckReceived = false;
            DuplicateRx = false;
            PongReceived = false;
            TxNbRetries = 0;

            logInfo("mDotEvent - TxDone");
            memset(&_flags, 0, sizeof(LoRaMacEventFlags));
            memset(&_info, 0, sizeof(LoRaMacEventInfo));

            _flags.Bits.Tx = 1;
            _info.TxDatarate = dr;
            _info.Status = LORAMAC_EVENT_INFO_STATUS_OK;
            Notify();

        }

        void Notify() {
            MacEvent(&_flags, &_info);
        }

        virtual void TxTimeout(void) {
            logDebug("mDotEvent - TxTimeout");

            _flags.Bits.Tx = 1;
            _info.Status = LORAMAC_EVENT_INFO_STATUS_TX_TIMEOUT;
            Notify();
        }

        virtual void JoinAccept(uint8_t *payload, uint16_t size, int16_t rssi, int16_t snr) {
            logDebug("mDotEvent - JoinAccept");

            _flags.Bits.Tx = 0;
            _flags.Bits.JoinAccept = 1;
            _info.Status = LORAMAC_EVENT_INFO_STATUS_OK;
            Notify();

        }

        virtual void JoinFailed(uint8_t *payload, uint16_t size, int16_t rssi, int16_t snr) {
            logDebug("mDotEvent - JoinFailed");

            _flags.Bits.Tx = 0;
            _flags.Bits.JoinAccept = 1;
            _info.Status = LORAMAC_EVENT_INFO_STATUS_JOIN_FAIL;
            Notify();

        }

        virtual void MissedAck(uint8_t retries) {
            logDebug("mDotEvent - MissedAck : retries %u", retries);
            TxNbRetries = retries;
            _info.TxNbRetries = retries;
        }

        virtual void PacketRx(uint8_t port, uint8_t *payload, uint16_t size, int16_t rssi, int16_t snr, lora::DownlinkControl ctrl, uint8_t slot, uint8_t retries, uint32_t address, uint32_t fcnt, bool dupRx) {
            logDebug("mDotEvent - PacketRx ADDR: %08x", address);

            if (!dupRx) {
                RxPort = port;
                PacketReceived = true;

                memcpy(RxPayload, payload, size);
                RxPayloadSize = size;

                if (ctrl.Bits.Ack) {
                    AckReceived = true;
                }
            }

            DuplicateRx = dupRx;

            _flags.Bits.Tx = 0;
            _flags.Bits.Rx = 1;
            _flags.Bits.RxData = size > 0;
            _flags.Bits.RxSlot = slot;
            _info.RxBuffer = payload;
            _info.RxBufferSize = size;
            _info.RxPort = port;
            _info.RxRssi = rssi;
            _info.RxSnr = snr;
            _info.TxAckReceived = AckReceived;
            _info.DuplicateRx = DuplicateRx;
            _info.TxNbRetries = retries;
            _info.Status = LORAMAC_EVENT_INFO_STATUS_OK;
            Notify();
        }

        virtual void RxDone(uint8_t *payload, uint16_t size, int16_t rssi, int16_t snr, lora::DownlinkControl ctrl, uint8_t slot) {
            logDebug("mDotEvent - RxDone");

        }

        virtual void BeaconRx(const lora::BeaconData_t& beacon_data, int16_t rssi, int16_t snr) {
            logDebug("mDotEvent - BeaconRx");
            BeaconLocked = true;
            BeaconData = beacon_data;
        }

        virtual void BeaconLost() {
            logDebug("mDotEvent - BeaconLost");
            BeaconLocked = false;
        }

        virtual void Pong(int16_t m_rssi, int16_t m_snr, int16_t s_rssi, int16_t s_snr) {
            logDebug("mDotEvent - Pong");
            PongReceived = true;
            PongRssi = s_rssi;
            PongSnr = s_snr;
        }

        virtual void ServerTime(uint32_t seconds, uint8_t sub_seconds) {
            logDebug("mDotEvent - ServerTime");
            ServerTimeReceived = true;

            std::chrono::milliseconds current_server_time_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(seconds)) +
                std::chrono::milliseconds(static_cast<uint16_t>(sub_seconds) * 4) +
                std::chrono::duration_cast<std::chrono::milliseconds>(_timeSinceTx.elapsed_time());
                // std::chrono::duration_cast<std::chrono::milliseconds>(_timeSinceTx.elapsed_time());

            ServerTimeSeconds = static_cast<uint32_t>(current_server_time_ms.count() / 1000);
            ServerTimeMillis = static_cast<uint16_t>(current_server_time_ms.count() % 1000);
        }

        virtual void NetworkLinkCheck(int16_t m_rssi, int16_t m_snr, int16_t s_snr, uint8_t s_gateways) {
            logDebug("mDotEvent - NetworkLinkCheck");
            LinkCheckAnsReceived = true;
            DemodMargin = s_snr;
            NbGateways = s_gateways;

            _flags.Bits.Tx = 0;
            _flags.Bits.LinkCheck = 1;
            _info.RxRssi = m_rssi;
            _info.RxSnr = m_snr;
            _info.DemodMargin = s_snr;
            _info.NbGateways = s_gateways;
            _info.Status = LORAMAC_EVENT_INFO_STATUS_OK;
            Notify();
        }

        virtual void RxTimeout(uint8_t slot) {
            logDebug("mDotEvent - RxTimeout on Slot %d", slot);

            _flags.Bits.Tx = 0;
            _flags.Bits.RxSlot = slot;
            _info.Status = LORAMAC_EVENT_INFO_STATUS_RX_TIMEOUT;
            Notify();

        }

        virtual void RxError(uint8_t slot) {
            logDebug("mDotEvent - RxError");

            memset(&_flags, 0, sizeof(LoRaMacEventFlags));
            memset(&_info, 0, sizeof(LoRaMacEventInfo));

            _flags.Bits.RxSlot = slot;
            _info.Status = LORAMAC_EVENT_INFO_STATUS_RX_ERROR;
            Notify();

        }

        virtual uint8_t MeasureBattery(void) {
            return 255;
        }

        bool LinkCheckAnsReceived;
        uint8_t DemodMargin;
        uint8_t NbGateways;

        bool PacketReceived;
        uint8_t RxPort;
        uint8_t RxPayload[255];
        uint8_t RxPayloadSize;

        bool BeaconLocked;
        lora::BeaconData_t BeaconData;

        bool PongReceived;
        int16_t PongRssi;
        int16_t PongSnr;

        bool ServerTimeReceived;
        uint32_t ServerTimeSeconds;
        uint16_t ServerTimeMillis;

        bool AckReceived;
        bool DuplicateRx;
        uint8_t TxNbRetries;

        LoRaMacEventFlags& Flags() {
            return _flags;
        }
        LoRaMacEventInfo& Info() {
            return _info;
        }

    private:

        LoRaMacEventFlags _flags;
        LoRaMacEventInfo _info;

        Timer _timeSinceTx;

//
//        /*!
//         * MAC layer event callback prototype.
//         *
//         * \param [IN] flags Bit field indicating the MAC events occurred
//         * \param [IN] info  Details about MAC events occurred
//         */
//        virtual void MacEvent(LoRaMacEventFlags *flags, LoRaMacEventInfo *info) {
//            logDebug("mDotEvent");
//
//            if (flags->Bits.Rx) {
//                logDebug("Rx");
//
//                // Event Object must delete RxBuffer
//                delete[] info->RxBuffer;
//            }
//        }
//

};

#endif // __MDOT_EVENT_H__
