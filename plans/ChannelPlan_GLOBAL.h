/**   __  ___     ____  _    ______        __     ____         __                  ____
 *   /  |/  /_ __/ / /_(_)__/_  __/__ ____/ /    / __/_ _____ / /____ __ _  ___   /  _/__  ____
 *  / /|_/ / // / / __/ /___// / / -_) __/ _ \  _\ \/ // (_-</ __/ -_)  ' \(_-<  _/ // _ \/ __/ __
 * /_/  /_/\_,_/_/\__/_/    /_/  \__/\__/_//_/ /___/\_, /___/\__/\__/_/_/_/___/ /___/_//_/\__/ /_/
 * Copyright (C) 2015 by Multi-Tech Systems        /___/
 *
 *
 * @author Jason Reiss
 * @date   10-31-2015
 * @brief  lora::ChannelPlan provides an interface for LoRaWAN channel schemes
 *
 * @details
 *
 */

#ifndef __CHANNEL_PLAN_ALL_H__
#define __CHANNEL_PLAN_ALL_H__

#include "Lora.h"
#include "SxRadio.h"
#include "ChannelPlan.h"
#include "ChannelPlans.h"
#include <vector>

namespace lora {

    class ChannelPlan_GLOBAL : public lora::ChannelPlan {
        public:

            /**
             * ChannelPlan constructor
             * @param radio SxRadio object used to set Tx/Rx config
             * @param settings Settings object
             */
            ChannelPlan_GLOBAL(uint8_t plan_id);
            ChannelPlan_GLOBAL(uint8_t plan_id, Settings* settings);
            ChannelPlan_GLOBAL(uint8_t plan_id, SxRadio* radio, Settings* settings);

            /**
             * ChannelPlan destructor
             */
            virtual ~ChannelPlan_GLOBAL();

            /**
             * Initialize channels, datarates and duty cycle bands according to current channel plan in settings
             */
            virtual void Init();

            virtual void Init_EU868();
            virtual void Init_US915();
            virtual void Init_AU915();
            virtual void Init_AS923();
            virtual void Init_KR920();
            virtual void Init_IN865();
            virtual void Init_RU864();

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
             * Get rx window settings for requested window
             * RX_1, RX_2, RX_BEACON, RX_SLOT
             * @param window
             * @return RxWindow
             */
            virtual RxWindow GetRxWindow(uint8_t window, int8_t id = 0);

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
             * Callback to for downlink channel request ServerCommand
             * @param payload packet data
             * @param index of start of command buffer
             * @param size number of bytes in command buffer
             * @param[out] status to be returned in MoteCommand answer
             * @return LORA_OK
             */
            virtual uint8_t HandleDownlinkChannelReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status);

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
             * Get max payload size for current datarate
             * @return size in bytes
             */
            virtual uint8_t GetMaxPayloadSize() { return GetMaxPayloadSize(GetSettings()->Session.TxDatarate); }

            /**
             * Get max payload size for given datarate
             * @return size in bytes
             */
            virtual uint8_t GetMaxPayloadSize(uint8_t dr, Direction dir = DIR_UP);

            virtual uint8_t GetMinDatarate();

            virtual uint8_t GetMaxDatarate();

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
            /**
             * Update class B beacon and ping slot settings if frequency hopping enabled
             * @param time received in the last beacon
             * @param period of the beacon
             * @param devAddr of this end device
             */
            virtual void FrequencyHop(uint32_t time, uint32_t period, uint32_t devAddr);

            /**
             * Called when MAC layer doesn't know about a command.
             * Use to add custom or new mac command handling
             * @return LORA_OK
             */
            virtual uint8_t HandleMacCommand(uint8_t* payload, uint8_t& index);

            /**
             * Decrements the datarate based on TxDwellTime
             */
            virtual void DecrementDatarate();

            /**
             * Set LBT time and threshold to defaults
             */
            virtual void DefaultLBT();

        protected:

            uint8_t _plan_id;
            uint32_t _as923_freq_offset;

            static const uint8_t US915_TX_POWERS[16];                   //!< List of available tx powers
            static const uint8_t US915_MAX_PAYLOAD_SIZE[];              //!< List of max payload sizes for each datarate
            static const uint8_t US915_MAX_PAYLOAD_SIZE_REPEATER[];     //!< List of repeater compatible max payload sizes for each datarate

            typedef struct __attribute__((packed)) {
                uint8_t RFU1[5];
                uint8_t Time[4];
                uint8_t CRC1[2];
                uint8_t GwSpecific[7];
                uint8_t RFU2[3];
                uint8_t CRC2[2];
            } BCNPayload_US915;

            static const uint8_t AU915_TX_POWERS[11];                   //!< List of available tx powers
            static const uint8_t AU915_MAX_PAYLOAD_SIZE[];              //!< List of max payload sizes for each datarate
            static const uint8_t AU915_MAX_PAYLOAD_SIZE_400[];          //!< List of max payload sizes for each datarate
            static const uint8_t AU915_MAX_PAYLOAD_SIZE_REPEATER[];     //!< List of repeater compatible max payload sizes for each datarate
            static const uint8_t AU915_MAX_PAYLOAD_SIZE_REPEATER_400[]; //!< List of repeater compatible max payload sizes for each datarate
            static const uint8_t AU915_MAX_ERP_VALUES[];                      //!< Lookup table for Max EIRP (dBm) codes

            typedef struct __attribute__((packed)) {
                uint8_t RFU1[5];
                uint8_t Time[4];
                uint8_t CRC1[2];
                uint8_t GwSpecific[7];
                uint8_t RFU2[3];
                uint8_t CRC2[2];
            } BCNPayload_AU915;

            static const uint8_t AS923_TX_POWERS[8];                    //!< List of available tx powers
            static const uint8_t AS923_MAX_PAYLOAD_SIZE[];              //!< List of max payload sizes for each datarate
            static const uint8_t AS923_MAX_PAYLOAD_SIZE_400[];          //!< List of max payload sizes for each datarate
            static const uint8_t AS923_MAX_PAYLOAD_SIZE_REPEATER[];     //!< List of repeater compatible max payload sizes for each datarate
            static const uint8_t AS923_MAX_PAYLOAD_SIZE_REPEATER_400[]; //!< List of repeater compatible max payload sizes for each datarate
            static const uint8_t AS923_MAX_ERP_VALUES[];                      //!< Lookup table for Max EIRP (dBm) codes
            typedef struct __attribute__((packed)) {
                uint8_t RFU[2];
                uint8_t Time[4];
                uint8_t CRC1[2];
                uint8_t GwSpecific[7];
                uint8_t CRC2[2];
            } BCNPayload_AS923;

            static const uint8_t EU868_TX_POWERS[8];                    //!< List of available tx powers
            static const uint8_t EU868_MAX_PAYLOAD_SIZE[];              //!< List of max payload sizes for each datarate
            static const uint8_t EU868_MAX_PAYLOAD_SIZE_REPEATER[];     //!< List of repeater compatible max payload sizes for each datarate

            typedef struct __attribute__((packed)) {
                uint8_t RFU[2];
                uint8_t Time[4];
                uint8_t CRC1[2];
                uint8_t GwSpecific[7];
                uint8_t CRC2[2];
            } BCNPayload_EU868;


            static const uint8_t IN865_TX_POWERS[11];                    //!< List of available tx powers
            static const uint8_t IN865_MAX_PAYLOAD_SIZE[];              //!< List of max payload sizes for each datarate
            static const uint8_t IN865_MAX_PAYLOAD_SIZE_REPEATER[];     //!< List of repeater compatible max payload sizes for each datarate

            typedef struct __attribute__((packed)) {
                uint8_t RFU1[1];
                uint8_t Time[4];
                uint8_t CRC1[2];
                uint8_t GwSpecific[7];
                uint8_t RFU2[3];
                uint8_t CRC2[2];
            } BCNPayload_IN865;


            static const uint8_t KR920_TX_POWERS[8];                    //!< List of available tx powers
            static const uint8_t KR920_MAX_PAYLOAD_SIZE[];              //!< List of max payload sizes for each datarate
            static const uint8_t KR920_MAX_PAYLOAD_SIZE_REPEATER[];     //!< List of repeater compatible max payload sizes for each datarate

            typedef struct __attribute__((packed)) {
                uint8_t RFU[2];
                uint8_t Time[4];
                uint8_t CRC1[2];
                uint8_t GwSpecific[7];
                uint8_t CRC2[2];
            } BCNPayload_KR920;

            static const uint8_t RU864_TX_POWERS[8];                    //!< List of available tx powers
            static const uint8_t RU864_MAX_PAYLOAD_SIZE[];              //!< List of max payload sizes for each datarate
            static const uint8_t RU864_MAX_PAYLOAD_SIZE_REPEATER[];     //!< List of repeater compatible max payload sizes for each datarate

            typedef struct __attribute__((packed)) {
                uint8_t RFU[2];
                uint8_t Time[4];
                uint8_t CRC1[2];
                uint8_t GwSpecific[7];
                uint8_t CRC2[2];
            } BCNPayload_RU864;

    };
}

#endif // __CHANNEL_PLAN_ALL_H__
