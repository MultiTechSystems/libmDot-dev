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

#ifndef __CHANNEL_STRATEGY_H__
#define __CHANNEL_STRATEGY_H__

#include "mbed_events.h"

#include "RandomChannel.h"
#include "Lora.h"
#include "SxRadio.h"
#include <vector>

#if USE_SX1262
#define RADIO_POWERS_SIZE 22
#else
#define RADIO_POWERS_SIZE 20
#endif

using namespace std::chrono;

namespace lora {

    class ChannelPlan {
        public:

            /**
             * Descriptions for channel plans & region information.
             * Bits 0-2 represent the plan type (fixed or dynamic)
             *   0b000              cannot be used as plans may line up with old definitions and cause much badness
             *   0b001              fixed channel plans
             *   0b010              dynamic channel plans
             *   0b011 - 0b111      RFU
             * Bits 3-7 represent the specific channel plan/region within the plan type
             */
            enum PlanType {
                FIXED = 0x20,
                DYNAMIC = 0x40,
            };

            enum Plan {
                EU868_OLD = 0x00,
                US915_OLD = 0x01,
                AU915_OLD = 0x02,

                FB_EU868 = 0x00,
                FB_US915 = 0x01,
                FB_AU915 = 0x02,

                FB_868 = 0x00,
                FB_915 = 0x01,

                US915 = FIXED | 0x00,
                AU915 = FIXED | 0x01,

                EU868 = DYNAMIC | 0x00,
                IN865 = DYNAMIC | 0x01,
                AS923 = DYNAMIC | 0x02,
                KR920 = DYNAMIC | 0x03,
                AS923_JAPAN = DYNAMIC | 0x04,
                RU864 = DYNAMIC | 0x05,
                AS923_2 = DYNAMIC | 0x06,
                AS923_3 = DYNAMIC | 0x07,
                AS923_JAPAN1 = DYNAMIC | 0x08,
                AS923_JAPAN2 = DYNAMIC | 0x09,
                AS923_4 = DYNAMIC | 0x0A,
                CN470 = FIXED | 0x0B,

                NONE = 0xFF,
            };

            uint32_t u1_hour_max = 36000;
            uint32_t u10_hour_max = 70000;
            uint32_t u24_hour_max = 78000;

            /**
             * ChannelPlan constructor
             * @param radio SxRadio object used to set Tx/Rx config
             * @param settings Settings object
             */
            ChannelPlan(SxRadio* radio, Settings* settings);

            /**
             * ChannelPlan destructor
             */
            virtual ~ChannelPlan();

            /**
             * Checks that at least one channel exist for the data rate
             */
            virtual uint8_t ValidateAdrDatarate(uint8_t status);

            /**
             * Initialize channels, datarates and duty cycle bands according to current channel plan in settings
             */
            virtual void Init() = 0;

            /**
             * Set SxRadio object to be used to set Tx/Rx config
             */
            virtual void SetRadio(SxRadio* radio);

            /**
             * Set Settings object
             */
            virtual void SetSettings(Settings* settings);

            /**
             * Setter for the event queue
             */
            virtual void SetEventQueue(EventQueue* queue);

            /**
             * Get the next channel to use to transmit
             * @return LORA_OK if channel was found
             * @return LORA_NO_CHANS_ENABLED
             */
            virtual uint8_t GetNextChannel() = 0;

            /**
             * Set the number of channels in the plan
             */
            virtual void SetNumberOfChannels(uint8_t channels, bool resize = true);

            /**
             * Get the number of channels in the plan
             */
            virtual uint8_t GetNumberOfChannels();

            /**
             * Check if channel is enabled
             * @return true if enabled
             */
            virtual bool IsChannelEnabled(uint8_t channel);

            /**
             * Set a 16 bit channel mask with offset
             * @param index of mask to set 0:0-15, 1:16-31 ...
             * @param mask 16 bit mask of enabled channels
             * @return true
             */
            virtual bool SetChannelMask(uint8_t index, uint16_t mask);

            /**
             * Get the channel mask of currently enabled channels
             * @return vector containing channel bit masks
             */
            virtual std::vector<uint16_t> GetChannelMask();

            /**
             * Add a channel to the ChannelPlan
             * @param index of channel, use -1 to add to end
             * @param channel settings to add
             */
            virtual uint8_t AddChannel(int8_t index, Channel channel) = 0;

            /**
             * Get channel at index
             * @return Channel
             */
            virtual Channel GetChannel(int8_t index) = 0;

            /**
             * Add a downlink channel to the ChannelPlan
             * Set to 0 to use the default uplink channel frequency
             * @param index of channel, use -1 to add to end
             * @param channel settings to add
             */
            virtual uint8_t AddDownlinkChannel(int8_t index, Channel channel);

            /**
             * Get channel at index
             * @return Channel
             */
            virtual Channel GetDownlinkChannel(uint8_t index);

            /**
             * Set number of datarates in ChannelPlan
             * @param datarates
             */
            virtual void SetNumberOfDatarates(uint8_t datarates);

            /**
             * Add a datarate to the ChannelPlan
             * @param index of datarate, use -1 to add to end
             * @param datarate settings to add
             */
            virtual uint8_t AddDatarate(int8_t index, Datarate datarate);

            /**
             * Get datarate at index
             * @return Datarate
             */
            virtual Datarate GetDatarate(int8_t index);

            /**
             * Get max payload size for current datarate
             * @return size in bytes
             */
            virtual uint8_t GetMaxPayloadSize();

            /**
             * Get max payload size for a given datarate
             * @return size in bytes
             */
            virtual uint8_t GetMaxPayloadSize(uint8_t dr, Direction dir = DIR_UP);

            /**
             * Get rx window settings for requested window
             * RX_1, RX_2, RX_BEACON, RX_SLOT
             * @param window
             * @return RxWindow
             */
            virtual RxWindow GetRxWindow(uint8_t window, int8_t id = 0) = 0;

            /**
             * Get current channel to use for transmitting
             * @param channel index of channel
             * @return LORA_OK
             */
            virtual uint8_t SetTxChannel(uint8_t channel);

            /**
             * Get datarate to use on the join request
             * @return datarate index
             */
            virtual uint8_t GetJoinDatarate() = 0;

            /**
             * Get the current join count based off currentDevNonce
             * @return join count
            */
            virtual uint16_t GetJoinCount();

            /**
             * Calculate the next time a join request is possible
             * @param size of join frame
             * @returns LORA_OK
             */
            virtual uint8_t CalculateJoinBackoff(uint8_t size);

            /**
             * Get the current datarate
             * @return Datarate
             */
            virtual Datarate GetTxDatarate();

            /**
             * Set the current datarate
             * @param index of datarate
             * @return LORA_OK
             */
            virtual uint8_t SetTxDatarate(uint8_t index);

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
            virtual uint8_t SetTxConfig() = 0;

            /**
             * Set the SxRadio rx config provided window
             * @param window to be opened
             * @param continuous keep window open
             * @param wnd_growth factor to increase the rx window by
             * @param pad_ms time in milliseconds to add to computed window size
             * @return LORA_OK
             */
            virtual uint8_t SetRxConfig(uint8_t window,
                                        bool continuous,
                                        uint16_t wnd_growth = 1,
                                        uint16_t pad_ms = 0,
                                        int8_t id = 0);

            /**
             * Set frequency sub band if supported by plan
             * @param sub_band
             * @return LORA_OK
             */
            virtual uint8_t SetFrequencySubBand(uint8_t group) = 0;

            /**
             * Get frequency sub band if supported by plan
             * @return sub band 0-8 or 0 if not supported
             */
            virtual uint8_t GetFrequencySubBand();

            /**
             * Callback for radio to request channel change when frequency hopping
             * @param currentChannel
             */
            virtual void FhssChangeChannel(uint8_t currentChannel);

            /**
             * Callback for ACK timeout event
             * @return LORA_OK
             */
            virtual uint8_t HandleAckTimeout();

            /**
             * Callback for Join Accept packet to load optional channels
             * @return LORA_OK
             */
            virtual uint8_t HandleJoinAccept(const uint8_t* buffer, uint8_t size) = 0;

            /**
             * Callback to for rx parameter setup ServerCommand
             * @param payload packet data
             * @param index of start of command buffer
             * @param size number of bytes in command buffer
             * @param[out] status to be returned in MoteCommand answer
             * @return LORA_OK
             */
            virtual uint8_t HandleRxParamSetup(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) = 0;

            /**
             * Callback to for new channel ServerCommand
             * @param payload packet data
             * @param index of start of command buffer
             * @param size number of bytes in command buffer
             * @param[out] status to be returned in MoteCommand answer
             * @return LORA_OK
             */
            virtual uint8_t HandleNewChannel(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) = 0;

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
            virtual uint8_t HandlePingSlotChannelReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) = 0;

            /**
             * Callback to for beacon frequency request ServerCommand
             * @param payload packet data
             * @param index of start of command buffer
             * @param size number of bytes in command buffer
             * @param[out] status to be returned in MoteCommand answer
             * @return LORA_OK
             */
            virtual uint8_t HandleBeaconFrequencyReq(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) = 0;

            /**
             * Callback to for adaptive datarate ServerCommand
             * @param payload packet data
             * @param index of start of command buffer
             * @param size number of bytes in command buffer
             * @param[out] status to be returned in MoteCommand answer
             * @return LORA_OK
             */
            virtual uint8_t HandleAdrCommand(const uint8_t* payload, uint8_t index, uint8_t size, uint8_t& status) = 0;

            /**
             * Validate the configuration after multiple ADR commands have been applied
             * @return status to be returned in MoteCommand answer
             */
            virtual uint8_t ValidateAdrConfiguration() = 0;

            /**
             * Check that Rf Frequency is within channel plan range
             * @param freq frequency in Hz
             * @return true if valid frequency
             */
            virtual bool CheckRfFrequency(uint32_t freq);

            /**
             * Flag for ADR
             * @return true if ADR is enable in settings
             */
            virtual bool IsAdrEnabled();

            /**
             * Flag if ADR ACK should be sent in next packet
             * @return true when flag should be set
             */
            virtual bool AdrAckReq();

            /**
             * Increment the ADR counter to track when ADR ACK request should be sent
             * @return current value
             */
            virtual uint8_t IncAdrCounter();

            /**
             * Reset the ADR counter when valid downlink is received from network server
             */
            virtual void ResetAdrCounter();

            /**
             * Get the time the radio must be off air to comply with regulations
             * Time to wait may be dependent on duty-cycle restrictions per channel
             * Or duty-cycle of join requests if OTAA is being attempted
             * @return ms of time to wait for next tx opportunity
             */
            virtual uint32_t GetTimeOffAir() = 0;

            /**
             * Get the channels in use by current channel plan
             * @return channel frequencies
             */
            virtual std::vector<uint32_t> GetChannels() = 0;

            /**
             * Get the downlink channels in use by current channel plan
             * @return channel frequencies
             */
            virtual std::vector<uint32_t> GetDownlinkChannels();

            /**
             * Get the channel datarate ranges in use by current channel plan
             * @return channel datarate ranges
             */
            virtual std::vector<uint8_t> GetChannelRanges() = 0;

            /**
             * Set the time off air for the given duty band
             * @param band index
             * @param time off air in ms
             */
            virtual void SetDutyBandTimeOff(uint8_t band, uint32_t timeoff);

            /**
             * Get the time off air for the given duty band
             * @param band index
             * @return time off air in ms
             */
            virtual uint32_t GetDutyBandTimeOff(uint8_t band);

            /**
             * Set the duty cycle for the given duty band
             * @param band index
             * @param dutyCycle ratio of time off air to time on air
             */
            virtual uint8_t SetDutyBandDutyCycle(uint8_t band, uint16_t dutyCycle);

            /**
             * Get the number of duty bands in the current channel plan
             * @return number of bands
             */
            virtual uint8_t GetNumDutyBands();

            /**
             * Get the duty band index for the given frequency
             * @param freq frequency in Hz
             * @return index of duty band
             */
            virtual int8_t GetDutyBand(uint32_t freq);

            /**
             * Get a pointer to a duty band object
             * @param index duty band index
             * @param band output DutyBand object
             */
            virtual void GetDutyBand(uint8_t index, const DutyBand** band) const;

            /**
             * Add duty band
             * @param index of duty band or -1 to append
             * @param band DutyBand definition
             * @return LORA_OK
             */
            virtual uint8_t AddDutyBand(int8_t index, DutyBand band);

            /**
             * Update duty cycle with current settings
             */
            void UpdateDutyCycle(uint8_t bytes);

            /**
             * Update duty cycle with at given frequency and time on air
             * @param freq frequency
             * @param time_on_air_ms tx time on air
             */
            virtual void UpdateDutyCycle(uint32_t freq, uint32_t time_on_air_ms);

            /**
             * Get time on air with current settings
             * @param bytes number of bytes to be sent
             * @param cfg for setting up the radio before getting time on air
             */
            virtual uint32_t GetTimeOnAir(uint8_t bytes, RadioCfg_t cfg = TX_RADIO_CFG);

            /**
             * Reset the duty timers with the current time off air
             */
            virtual void ResetDutyCycleTimer();

            /**
             * Print log message for given rx window
             * @param wnd 1 or 2
             */
            virtual void LogRxWindow(uint8_t wnd) = 0;

            /**
             * Indicator of P2P mode
             * @return true if enabled
             */
            virtual bool P2PEnabled();

            /**
             * Ack timeout for P2P mode
             * @return timeout in ms
             */
            virtual uint16_t P2PTimeout();

            /**
             * Ack backoff for P2P mode
             * @return backoff in ms
             */
            virtual uint16_t P2PBackoff();

            /**
             * Enable the default channels of the channel plan
             */
            virtual void EnableDefaultChannels() = 0;

            /**
             *  Callback for radio thread to signal
             */
            virtual void MacEvent();

            /**
             * Called when MAC layer doesn't know about a command.
             * Use to add custom or new mac command handling
             * @return LORA_OK
             */
            virtual uint8_t HandleMacCommand(uint8_t* payload, uint8_t& index);

            virtual void DecrementDatarate();
            virtual void IncrementDatarate();

            virtual std::string GetPlanName();
            virtual uint8_t GetPlan();
            virtual bool IsPlanFixed();
            virtual bool IsPlanDynamic();
            static bool IsPlanFixed(uint8_t plan);
            static bool IsPlanDynamic(uint8_t plan);
            bool IsPlanAS923();
            virtual uint32_t GetMinFrequency();
            virtual uint32_t GetMaxFrequency();

            virtual uint8_t GetMinDatarate();
            virtual uint8_t GetMaxDatarate();
            virtual uint8_t GetMinDatarateOffset();
            virtual uint8_t GetMaxDatarateOffset();

            virtual uint8_t GetMinRx2Datarate();
            virtual uint8_t GetMaxRx2Datarate();
            virtual uint8_t GetMaxTxPower();
            virtual uint8_t GetMinTxPower();

            virtual uint16_t GetLBT_TimeUs();
            virtual void SetLBT_TimeUs(uint16_t us);

            virtual int8_t GetLBT_Threshold();
            virtual void SetLBT_Threshold(int8_t rssi);

            /**
             * Set LBT time and threshold to defaults
             */
            virtual void DefaultLBT();

            virtual bool ListenBeforeTalk();

            /**
             * use to clear downlink channels on join
             */
            virtual void ClearChannels();

            /**
             * Check if this packet is a beacon and if so extract parameters needed
             * @param payload of potential beacon
             * @param size of the packet
             * @param [out] data extracted from the beacon if this packet was indeed a beacon
             * @return true if this packet is beacon, false if not
             */
            virtual uint8_t DecodeBeacon(const uint8_t* payload,
                                      size_t size,
                                      BeaconData_t& data) = 0;

            /**
             * Update class B beacon and ping slot settings if frequency hopping enabled
             * @param time received in the last beacon
             * @param period of the beacon
             * @param devAddr of this end device
             */
            virtual void FrequencyHop(uint32_t time, uint32_t period, uint32_t devAddr) { }


            /*
             * Get default number of channels for a plan
             */
            virtual uint8_t GetNumDefaultChans();

            /*
             * Search enabled channels for lowest available datarate
             */
            virtual uint8_t GetMinEnabledDatarate();

            SxRadio* GetRadio();                //!< Get pointer to the SxRadio object or assert if it is null
            Settings* GetSettings();            //!< Get pointer to the settings object or assert if it is null
            RandomChannel *GetRandomChannel();
        protected:

            /**
             * 16 bit ITU-T CRC implementation
             */
            uint16_t CRC16(const uint8_t* data, size_t size);

            RandomChannel _randomChannel;

            uint8_t _txChannel;                 //!< Current channel for transmit
            uint8_t _txFrequencySubBand;        //!< Current frequency sub band for hybrid operation

            std::vector<Datarate> _datarates;   //!< List of datarates

            std::vector<Channel> _channels;     //!< List of channels for transmit
            std::vector<Channel> _dlChannels;   //!< List of channels for receive if changed from default

            std::vector<DutyBand> _dutyBands;   //!< List of duty bands to limit radio time on air

            uint8_t _maxTxPower;                //!< Max Tx power for channel Plan
            uint8_t _minTxPower;

            uint32_t _minFrequency;             //!< Minimum Frequency
            uint32_t _maxFrequency;             //!< Maximum Frequency

            uint8_t _minDatarate;               //!< Minimum datarate to accept in ADR request
            uint8_t _maxDatarate;               //!< Maximum datarate to accept in ADR request

            uint8_t _minRx2Datarate;            //!< Minimum datarate to accept in for Rx2
            uint8_t _maxRx2Datarate;            //!< Maximum datarate to accept in for Rx2
            uint8_t _minDatarateOffset;         //!< Minimum datarate offset to accept
            uint8_t _maxDatarateOffset;         //!< Maximum datarate offset to accept

            uint32_t _freqUBase125k;            //!< Start of 125K uplink channels
            uint32_t _freqUStep125k;            //!< Step between 125K uplink channels
            uint32_t _freqUBase500k;            //!< Start of 500K uplink channels
            uint32_t _freqUStep500k;            //!< Step between 500K uplink channels
            uint32_t _freqDBase500k;            //!< Start of 500K downlink channels
            uint32_t _freqDStep500k;            //!< Step between 500K downlink channels

            uint8_t _numChans;                  //!< Number of total channels in plan
            uint8_t _numChans125k;              //!< Number of 125K  channels in plan
            uint8_t _numChans500k;              //!< Number of 500K channels in plan
            uint8_t _numDefaultChans;           //!< Number of default channels in plan

            uint16_t _LBT_TimeUs;               //!< Sample time in us for LBT
            int8_t _LBT_Threshold;              //!< Threshold in dBm for LBT

            std::vector<uint16_t> _channelMask; //!< Bit mask for currently enabled channels

            Timer _dutyCycleTimer;              //!< Timer for tracking time-off-air
            int _txDutyEvtId;                   //!< Event ID for expiration of time-off-air

            bool _txDutyCyclePending;           //!< Flag for pending duty cycle event

            void OnTxDutyCycleEvent();          //!< Callback for duty cycle event
            void OnTxDutyCycleEventBottom();                    //!< Callback for duty cycle event

            static const uint8_t* TX_POWERS;                    //!< List of available tx powers
            static const uint8_t RADIO_POWERS[];                    //!< List of available tx powers
            static const uint8_t* MAX_PAYLOAD_SIZE;             //!< List of max payload sizes for each datarate
            static const uint8_t* MAX_PAYLOAD_SIZE_REPEATER;    //!< List of repeater compatible max payload sizes for each datarate

            uint8_t _beaconSize;

            uint8_t _plan;
            std::string _planName;

        private:

            SxRadio* _radio;                    //!< Injected SxRadio dependency
            Settings* _settings;                //!< Current settings
            EventQueue* _evtQueue;              //!< mbed Event Queue
    };
}

#endif
