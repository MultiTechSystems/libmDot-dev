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
 *
 * @author Jason Reiss
 * @date   10-31-2015
 * @brief  lora::ChannelPlan provides an interface for LoRaWAN channel schemes
 *
 * @details
 *
 */

#ifndef __CHANNEL_PLAN_AS923_H__
#define __CHANNEL_PLAN_AS923_H__

#include "Lora.h"
#include "SxRadio.h"
#include <vector>
#include "ChannelPlan.h"

namespace lora {

    const uint8_t  AS923_125K_NUM_CHANS = 16;        //!< Number of 125k channels in AS923 channel plan
    const uint8_t  AS923_DEFAULT_NUM_CHANS = 2;      //!< Number of default channels in AS923 channel plan
    const uint32_t AS923_125K_FREQ_BASE = 923200000; //!< Frequency base for 125k AS923 uplink channels
    const uint32_t AS923_125K_FREQ_STEP = 200000;    //!< Frequency step for 125k AS923 uplink channels
    const uint32_t AS923_RX2_FREQ = 923200000;       //!< Frequency default for second rx window in AS923
    const uint8_t  AS923_BEACON_DR = DR_3;           //!< Default beacon datarate
    const uint32_t AS923_BEACON_FREQ = 923400000U;   //!< Default beacon broadcast frequency

    class ChannelPlan_AS923: public lora::ChannelPlan {
        public:
            /**
             * ChannelPlan constructor
             * @param radio SxRadio object used to set Tx/Rx config
             * @param settings Settings object
             */
            ChannelPlan_AS923();
            ChannelPlan_AS923(Settings* settings);
            ChannelPlan_AS923(SxRadio* radio, Settings* settings);

            /**
             * ChannelPlan destructor
             */
            virtual ~ChannelPlan_AS923();

            /**
             * Initialize channels, datarates and duty cycle bands according to current channel plan in settings
             */
            virtual void Init();

            /**
             * Get the next channel to use to transmit
             * @return LORA_OK if channel was found
             * @return LORA_NO_CHANS_ENABLED
             */
            virtual uint8_t GetNextChannel();

            /**
             * Add a channel to the ChannelPlan
             * @param index of channel, use -1 to add to end
             * @param channel settings to add
             */
            virtual uint8_t AddChannel(int8_t index, Channel channel);

            /**
             * Get channel at index
             * @return Channel
             */
            virtual Channel GetChannel(int8_t index);

            /**
             * ACK timeout in milliseconds
             * @return millisecond timeout for RX2 datarate max payload size
             */
            virtual uint32_t GetAckTimeout();

            /**
             * Get rx window settings for requested window
             * RX_1, RX_2, RX_BEACON, RX_SLOT
             * @param window
             * @return RxWindow
             */
            virtual RxWindow GetRxWindow(uint8_t window, int8_t id = -1);

            /**
             * Get datarate to use on the join request
             * @return datarate index
             */
            virtual uint8_t GetJoinDatarate();

            /**
             * Get next channel and set the SxRadio tx config with current settings
             * @return LORA_OK
             */
            virtual uint8_t SetTxConfig();

            /**
             * Set frequency sub band if supported by plan
             * @param sub_band
             * @return LORA_OK
             */
            virtual uint8_t SetFrequencySubBand(uint8_t sub_band);

            /**
             * Callback for Join Accept packet to load optional channels
             * @return LORA_OK
             */
            virtual uint8_t HandleJoinAccept(const uint8_t* buffer, uint8_t size);

            /**
             * Callback to for rx parameter setup ServerCommand
             * @param payload packet data
             * @param index of start of command buffer
             * @param size number of bytes in command buffer
             * @param[out] status to be returned in MoteCommand answer
             * @return LORA_OK
             */
            virtual uint8_t HandleRxParamSetup(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status);

            /**
             * Callback to for new channel ServerCommand
             * @param payload packet data
             * @param index of start of command buffer
             * @param size number of bytes in command buffer
             * @param[out] status to be returned in MoteCommand answer
             * @return LORA_OK
             */
            virtual uint8_t HandleNewChannel(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status);

            /**
             * Callback to for ping slot channel request ServerCommand
             * @param payload packet data
             * @param index of start of command buffer
             * @param size number of bytes in command buffer
             * @param[out] status to be returned in MoteCommand answer
             * @return LORA_OK
             */
            virtual uint8_t HandlePingSlotChannelReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status);

            /**
             * Callback to for beacon frequency request ServerCommand
             * @param payload packet data
             * @param index of start of command buffer
             * @param size number of bytes in command buffer
             * @param[out] status to be returned in MoteCommand answer
             * @return LORA_OK
             */
            virtual uint8_t HandleBeaconFrequencyReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status);

            /**
             * Callback to for adaptive datarate ServerCommand
             * @param payload packet data
             * @param index of start of command buffer
             * @param size number of bytes in command buffer
             * @param[out] status to be returned in MoteCommand answer
             * @return LORA_OK
             */
            virtual uint8_t HandleAdrCommand(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status);

            /**
             * Validate the configuration after multiple ADR commands have been applied
             * @return status to be returned in MoteCommand answer
             */
            virtual uint8_t ValidateAdrConfiguration();

            /**
             * Update duty cycle with at given frequency and time on air
             * @param freq frequency
             * @param time_on_air_ms tx time on air
             */
            virtual void UpdateDutyCycle(uint32_t freq, uint32_t time_on_air_ms);

            /**
             * Get the time the radio must be off air to comply with regulations
             * Time to wait may be dependent on duty-cycle restrictions per channel
             * Or duty-cycle of join requests if OTAA is being attempted
             * @return ms of time to wait for next tx opportunity
             */
            virtual uint32_t GetTimeOffAir();

            /**
             * Get the channels in use by current channel plan
             * @return channel frequencies
             */
            virtual std::vector<uint32_t> GetChannels();

            /**
             * Get the channel datarate ranges in use by current channel plan
             * @return channel datarate ranges
             */
            virtual std::vector<uint8_t> GetChannelRanges();

            /**
             * Print log message for given rx window
             * @param wnd 1 or 2
             */
            virtual void LogRxWindow(uint8_t wnd);

            /**
             * Enable the default channels of the channel plan
             */
            virtual void EnableDefaultChannels();

            /**
             * Called when MAC layer doesn't know about a command.
             * Use to add custom or new mac command handling
             * @return LORA_OK
             */
            virtual uint8_t HandleMacCommand(uint8_t* payload, uint8_t& index);

            /**
             * Get max payload size for current datarate
             * @return size in bytes
             */
            virtual uint8_t GetMaxPayloadSize() { return GetMaxPayloadSize(GetSettings()->Session.TxDatarate); }

            /**
             * Get max payload size for given datarate
             * @return size in bytes
             */
            virtual uint8_t GetMaxPayloadSize(uint8_t dr, Direction dir = DIR_UP);

            /**
             * Decrements the datarate based on TxDwellTime
             */
            virtual void DecrementDatarate();

            /**
             * Check if this packet is a beacon and if so extract parameters needed
             * @param payload of potential beacon
             * @param size of the packet
             * @param [out] data extracted from the beacon if this packet was indeed a beacon
             * @return true if this packet is beacon, false if not
             */
            virtual uint8_t DecodeBeacon(const uint8_t* payload,
                                      size_t size,
                                      BeaconData_t& data);


            virtual uint8_t GetMinDatarate();

        protected:

            static const uint8_t AS923_TX_POWERS[8];                    //!< List of available tx powers
            static const uint8_t AS923_MAX_PAYLOAD_SIZE[];              //!< List of max payload sizes for each datarate
            static const uint8_t AS923_MAX_PAYLOAD_SIZE_400[];          //!< List of max payload sizes for each datarate
            static const uint8_t AS923_MAX_PAYLOAD_SIZE_REPEATER[];     //!< List of repeater compatible max payload sizes for each datarate
            static const uint8_t AS923_MAX_PAYLOAD_SIZE_REPEATER_400[]; //!< List of repeater compatible max payload sizes for each datarate
            static const uint8_t MAX_ERP_VALUES[];                      //!< Lookup table for Max EIRP (dBm) codes
            typedef struct __attribute__((packed)) {
                uint8_t RFU[2];
                uint8_t Time[4];
                uint8_t CRC1[2];
                uint8_t GwSpecific[7];
                uint8_t CRC2[2];
            } BCNPayload;
    };
}

#endif //__CHANNEL_PLAN_AS923_H__
