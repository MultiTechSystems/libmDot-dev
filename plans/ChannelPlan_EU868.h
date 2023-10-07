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

#ifndef __CHANNEL_PLAN_EU868_H__
#define __CHANNEL_PLAN_EU868_H__

#include "Lora.h"
#include "SxRadio.h"
#include <vector>
#include "ChannelPlan.h"

namespace lora {

    const uint8_t EU868_125K_NUM_CHANS = 16;                    //!< Number of 125k channels in EU868 channel plan
    const uint8_t EU868_DEFAULT_NUM_CHANS = 3;                  //!< Number of defualt channels in EU868 channel plan
    const uint32_t EU868_125K_FREQ_BASE = 868100000;            //!< Frequency base for 125k EU868 uplink channels
    const uint32_t EU868_125K_FREQ_STEP = 200000;               //!< Frequency step for 125k EU868 uplink channels
    const uint32_t EU868_RX2_FREQ = 869525000;                  //!< Frequency default for second rx window in EU868

    const uint8_t EU868_TX_POWER_MAX = 14;                      //!< Max power for EU868 channel plan

    // 0.1% duty cycle 863-868
    // Limiting to 865-868 allows for 1% duty cycle
    const uint32_t EU868_MILLI_FREQ_MIN = 865000000;
    const uint32_t EU868_MILLI_FREQ_MAX = 868000000;

    const uint32_t EU868_MILLI_0_FREQ_MIN = 863000000;
    const uint32_t EU868_MILLI_0_FREQ_MAX = 865000000;

    const uint32_t EU868_MILLI_1_FREQ_MIN = 868700000;
    const uint32_t EU868_MILLI_1_FREQ_MAX = 869200000;

    // 1% duty cycle
    const uint32_t EU868_CENTI_FREQ_MIN = 868000000;
    const uint32_t EU868_CENTI_FREQ_MAX = 868600000;

    // 10% duty cycle
    const uint32_t EU868_DECI_FREQ_MIN = 869400000;
    const uint32_t EU868_DECI_FREQ_MAX = 869650000;

    // Below 7dBm there is no duty cycle for these frequencies
    // Up to 14dBm there is 1% duty cycle
    const uint32_t EU868_VAR_FREQ_MIN = 869700000;
    const uint32_t EU868_VAR_FREQ_MAX = 870000000;

    const uint32_t EU868_FREQ_MIN = 863000000;
    const uint32_t EU868_FREQ_MAX = 870000000;

    const uint8_t EU868_MIN_DATARATE = (uint8_t) DR_0;           //!< Minimum transmit datarate for EU868
    const uint8_t EU868_MAX_DATARATE = (uint8_t) DR_5;           //!< Maximum transmit datarate for EU868

    const uint8_t EU868_MIN_DATARATE_OFFSET = (uint8_t) 0;       //!< Minimum transmit datarate for US915
    const uint8_t EU868_MAX_DATARATE_OFFSET = (uint8_t) 5;       //!< Maximum transmit datarate for US915

    const uint8_t  EU868_BEACON_DR = DR_3;                       //!< Default beacon datarate
    const uint32_t EU868_BEACON_FREQ = 869525000U;               //!< Default beacon broadcast frequency

    class ChannelPlan_EU868 : public lora::ChannelPlan {
        public:
            /**
             * ChannelPlan constructor
             * @param radio SxRadio object used to set Tx/Rx config
             * @param settings Settings object
             */
            ChannelPlan_EU868();
            ChannelPlan_EU868(Settings* settings);
            ChannelPlan_EU868(SxRadio* radio, Settings* settings);

            /**
             * ChannelPlan destructor
             */
            virtual ~ChannelPlan_EU868();

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
             * Check if this packet is a beacon and if so extract parameters needed
             * @param payload of potential beacon
             * @param size of the packet
             * @param [out] data extracted from the beacon if this packet was indeed a beacon
             * @return true if this packet is beacon, false if not
             */
            virtual uint8_t DecodeBeacon(const uint8_t* payload,
                                      size_t size,
                                      BeaconData_t& data);

        protected:

            static const uint8_t EU868_TX_POWERS[8];                    //!< List of available tx powers
            static const uint8_t EU868_MAX_PAYLOAD_SIZE[];              //!< List of max payload sizes for each datarate
            static const uint8_t EU868_MAX_PAYLOAD_SIZE_REPEATER[];     //!< List of repeater compatible max payload sizes for each datarate

            typedef struct __attribute__((packed)) {
                uint8_t RFU[2];
                uint8_t Time[4];
                uint8_t CRC1[2];
                uint8_t GwSpecific[7];
                uint8_t CRC2[2];
            } BCNPayload;
    };
}

#endif //__CHANNEL_PLAN_EU868_H__
