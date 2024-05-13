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

#ifndef __CHANNEL_PLAN_CN470_H__
#define __CHANNEL_PLAN_CN470_H__

#include "Lora.h"
#include "SxRadio.h"
#include "ChannelPlan.h"
#include <vector>

namespace lora {

    const uint8_t CN470_125K_NUM_CHANS = 96;                    //!< Number of 125k channels in CN470 channel plan
    const uint8_t CN470_500K_NUM_CHANS = 0;                     //!< Number of 500k channels in CN470 channel plan

    const uint32_t CN470_125K_FREQ_BASE = 470300000;            //!< Frequency base for 125k CN470 uplink channels
    const uint32_t CN470_125K_FREQ_STEP = 200000;               //!< Frequency step for 125k CN470 uplink channels


    const uint32_t CN470_125K_DBASE = 500300000;                //!< Frequency base for 500k CN470 downlink channels
    const uint32_t CN470_125K_DSTEP = 200000;                   //!< Frequency step for 500k CN470 downlink channels

    const uint32_t CN470_FREQ_RX2 = 505300000;

    const uint32_t CN470_FREQ_MIN = 470000000;
    const uint32_t CN470_FREQ_MAX = 510000000;

    const uint8_t CN470_MIN_DATARATE = (uint8_t) DR_1;          //!< Minimum transmit datarate for CN470
    const uint8_t CN470_MAX_DATARATE = (uint8_t) DR_5;          //!< Maximum transmit datarate for CN470

    const uint8_t CN470_MIN_DATARATE_OFFSET = (uint8_t) 0;      //!< Minimum transmit datarate for CN470
    const uint8_t CN470_MAX_DATARATE_OFFSET = (uint8_t) 3;      //!< Maximum transmit datarate for CN470

    const uint8_t  CN470_BEACON_DR = DR_2;                      //!< Default beacon datarate
    const uint32_t CN470_BEACON_FREQ_BASE = 500300000;         //!< Base beacon broadcast frequency
    const uint32_t CN470_BEACON_FREQ_STEP = 200000U;            //!< Step size for beacon frequencies
    const uint8_t  CN470_BEACON_CHANNELS = 8U;                  //!< Number of beacon channels

    class ChannelPlan_CN470 : public lora::ChannelPlan {
        public:

            /**
             * ChannelPlan constructor
             * @param radio SxRadio object used to set Tx/Rx config
             * @param settings Settings object
             */
            ChannelPlan_CN470();
            ChannelPlan_CN470(Settings* settings);
            ChannelPlan_CN470(SxRadio* radio, Settings* settings);

            /**
             * ChannelPlan destructor
             */
            virtual ~ChannelPlan_CN470();

            /**
             * Initialize channels, datarates and duty cycle bands according to current channel plan in settings
             */
            virtual void Init();

            /**
             * Set LBT time and threshold to defaults
             */
            virtual void DefaultLBT();

            /**
             * Get the next channel to use to transmit
             * @return LORA_OK if channel was found
             * @return LORA_NO_CHANS_ENABLED
             */
            virtual uint8_t GetNextChannel();

            /**
             * Set the number of channels in the plan
             */
            virtual void SetNumberOfChannels(uint8_t channels, bool resize = true);

            /**
             * Check if channel is enabled
             * @return true if enabled
             */
            virtual bool IsChannelEnabled(uint8_t channel);


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
             * Set the datarate offset used for first receive window
             * @param offset
             * @return LORA_OK
             */
            virtual uint8_t SetRx1Offset(uint8_t offset);

            /**
             * Set the frequency for second receive window
             * @param freq
             * @return LORA_OK
             */
            virtual uint8_t SetRx2Frequency(uint32_t freq);

            /**
             * Set the datarate index used for second receive window
             * @param index
             * @return LORA_OK
             */
            virtual uint8_t SetRx2DatarateIndex(uint8_t index);

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
             * Set the duty cycle for the given duty band
             * @param band index
             * @param dutyCycle ratio of time off air to time on air
             * @return LORA_UNSUPPORTED
             */
            virtual uint8_t SetDutyBandDutyCycle(uint8_t band, uint16_t dutyCycle);

            /**
             * Print log message for given rx window
             * @param wnd 1 or 2
             */
            virtual void LogRxWindow(uint8_t wnd);

            /**
             * Enable the default channels of the channel plan
             */
            virtual void EnableDefaultChannels();

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

        protected:

            static const uint8_t CN470_TX_POWERS[16];                   //!< List of available tx powers
            static const uint8_t CN470_MAX_PAYLOAD_SIZE[];              //!< List of max payload sizes for each datarate
            static const uint8_t CN470_MAX_PAYLOAD_SIZE_REPEATER[];     //!< List of repeater compatible max payload sizes for each datarate

            typedef struct __attribute__((packed)) {
                uint8_t RFU1[5];
                uint8_t Time[4];
                uint8_t CRC1[2];
                uint8_t GwSpecific[7];
                uint8_t RFU2[3];
                uint8_t CRC2[2];
            } BCNPayload;
    };
}

#endif // __CHANNEL_PLAN_CN470_H__
