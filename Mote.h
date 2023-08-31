/**   __  ___     ____  _    ______        __     ____         __                  ____
 *   /  |/  /_ __/ / /_(_)__/_  __/__ ____/ /    / __/_ _____ / /____ __ _  ___   /  _/__  ____
 *  / /|_/ / // / / __/ /___// / / -_) __/ _ \  _\ \/ // (_-</ __/ -_)  ' \(_-<  _/ // _ \/ __/ __
 * /_/  /_/\_,_/_/\__/_/    /_/  \__/\__/_//_/ /___/\_, /___/\__/\__/_/_/_/___/ /___/_//_/\__/ /_/
 * Copyright (C) 2015 by Multi-Tech Systems        /___/
 *
 *
 * @author Jason Reiss
 * @date   10-31-2015
 * @brief  lora::Mote provides a user level class that abstracts the complexity of the Mac layer
 *
 * @details
 *
 */

#ifndef __LORA_MOTE_H__
#define __LORA_MOTE_H__

#include "mbed.h"
#include "mbed_events.h"

#include "MacEvents.h"

#include <vector>

class SxRadio;
#if defined(TARGET_XDOT_MAX32670)
class SxRadio1262;
#else
class SxRadio1272;
#endif


namespace lora {

    class Mac;
    class ChannelPlan;

    class MoteEvents: public MacEvents {

            /**
             * Fired at start of TX
             */
            virtual void TxStart(void);

            /**
             * Fired at end of TX
             * @param dr datarate used for TX
             */
            virtual void TxDone(uint8_t dr);

            /**
             * Fired if TX timed out
             */
            virtual void TxTimeout(void);

            /**
             * Fired when JoinAccept message is received and MIC is validated
             * @param payload received bytes
             * @param size number of received bytes
             * @param rssi of received packet
             * @param snr of received packet
             */
            virtual void JoinAccept(uint8_t *payload, uint16_t size, int16_t rssi, int16_t snr);

            /**
             * Fired when JoinAccept message is received and MIC is not valid
             * @param payload received bytes
             * @param size number of received bytes
             * @param rssi of received packet
             * @param snr of received packet
             */
            virtual void JoinFailed(uint8_t *payload, uint16_t size, int16_t rssi, int16_t snr);

            /**
             * Fired when packet is received and MIC is valid
             * @param port of packet
             * @param payload received bytes
             * @param size number of received bytes
             * @param rssi of received packet
             * @param snr of received packet
             * @param ctrl Downlink control field of packet
             * @param slot rx window packet was received
             * @param retries number of attempts before ack was received
             * @param address of the end device
             * @param dupRx set if this packet has already been received
             */
            virtual void PacketRx(uint8_t port, uint8_t *payload, uint16_t size, int16_t rssi, int16_t snr, lora::DownlinkControl ctrl, uint8_t slot, uint8_t retries = 0, uint32_t address = 0, uint32_t fcnt = 0, bool dupRx=false);

            /**
             * Fired when radio has received a packet, packet is not validated
             * @param payload received bytes
             * @param size number of received bytes
             * @param rssi of received packet
             * @param snr of received packet
             * @param ctrl Downlink control field of packet
             * @param slot rx window packet was received
             */
            virtual void RxDone(uint8_t *payload, uint16_t size, int16_t rssi, int16_t snr, lora::DownlinkControl ctrl, uint8_t slot);

            /**
             * Fired when a beacon is received
             * @param beacon_data parsed from the beacon payload
             * @param rssi of received beacon
             * @param snr of received beacon
             */
            virtual void BeaconRx(const BeaconData_t& beacon_data, int16_t rssi, int16_t snr);

            /**
             * Fired upon losing beacon synchronization (120 minutes elapsed from last beacon reception)
             */
            virtual void BeaconLost();

            /**
             * Fired if rx window times out
             * @param slot rx window that timed out
             */
            virtual void RxTimeout(uint8_t slot);

            /**
             * Fired if rx CRC error
             * @param slot rx window that errored
             */
            virtual void RxError(uint8_t slot);

            /**
             * Fired if pong packet is received
             * @param m_rssi of received packet at mote
             * @param m_snr of received packet at mote
             * @param s_rssi of received packet at server
             * @param s_snr of received packet at server
             */
            virtual void Pong(int16_t m_rssi, int16_t m_snr, int16_t s_rssi, int16_t s_snr);

            /**
             * Fired if network link check answer is received
             * @param m_rssi of received packet at mote
             * @param m_snr of received packet at mote
             * @param s_snr margin of received packet at server
             * @param s_gateways number of gateways reporting the packet
             */
            virtual void NetworkLinkCheck(int16_t m_rssi, int16_t m_snr, int16_t s_snr, uint8_t s_gateways);

            /**
             * Fired upon receiving a server time answer
             * @param seconds from the GPS epoch
             * @param sub_seconds from the GPS epoch
             */
            virtual void ServerTime(uint32_t seconds, uint8_t sub_seconds);

            /**
             * Callback to for device to measure the battery level and report to server
             * @return battery level 0-255, 0 - external power, 1-254 level min-max, 255 device unable to measure battery
             */
            virtual uint8_t MeasureBattery();

            /**
             * Fired when ack attempts are exhausted and RxTimeout or RxError occur
             * @param retries number of attempts to resend the packet
             */
            virtual void MissedAck(uint8_t retries);
    };

    class Mote {
        public:
            Mote(Settings* settings, ChannelPlan* plan);
            virtual ~Mote();

            /**
             * MTS LoRa version
             * @return string containing version information
             */
            const char* getId();

            /**
             * MAC version
             *
             * @return string containing version information of supported LoRaWAN MAC Version
             */
            const char* getMACVersion();

            /**
             * Indicator for network session join status
             * @return true if joined to network
             */
            bool Joined();

            /**
             * Send join request
             * @return LORA_OK if request was sent
             */
            uint8_t Join();

            /**
             * Send a packet
             * @param port to send packet
             * @param payload of packet
             * @param size in bytes
             * @return LORA_OK if successful
             * @return LORA_MAX_PAYLOAD_EXCEEDED if payload size exceeds datarate maximum
             * @return LORA_NO_CHANS_ENABLED if there is not an available channel that supports the current datarate
             * @return LORA_LINK_BUSY if link was busy
             * @return LORA_RADIO_BUSY if radio was busy
             * @return LORA_BUFFER_FULL if mac commands filled the packet, client should resend the packet
             */
            uint8_t Send(uint8_t port, const uint8_t* payload, uint8_t size);

            /**
             * Configure the channel plan
             * @param plan pointer to ChannelPlan object
             * @return LORA_OK
             */
            uint8_t SetChannelPlan(ChannelPlan* plan);


            Settings* GetSettings();

            /**
             * Get the channel mask of currently enabled channels
             * @return vector containing channel bit masks
             */
            std::vector<uint16_t> GetChannelMask();

            /**
             * Set a 16 bit channel mask with index
             * @param index of mask to set 0:0-15, 1:16-31 ...
             * @param mask 16 bit mask of enabled channels
             * @return true
             */
            virtual uint8_t SetChannelMask(uint8_t index, uint16_t mask);

            /**
             * Set the current frequency sub band for hybrid operation 1-8 else 0 for 64 channel operation
             * @param sub_band 0-8
             */
            uint8_t SetFrequencySubBand(uint8_t sub_band);

            /**
             * Get the current frequency sub band
             * @return sub band 0-8
             */
            uint8_t GetFrequencySubBand();

            /**
             * Add a channel to the channel plan
             * EU868, AS923 and KR920 allows additional channels to be added
             * Channels 0-2 are fixed default channels
             *
             * @param index of the channel
             * @param frequency of the channel or 0 to remove channel
             * @param range of datarates allowed by the channel
             * @return LORA_OK if channel was added
             */
            uint8_t AddChannel(uint8_t index, uint32_t frequency, lora::DatarateRange range);

            /**
             * Add a downlink channel to the channel plan
             * EU868, AS923 and KR920 allows downlink channels to be added
             *
             * @param index of the channel
             * @param frequency of the channel or 0 to remove channel
             * @return LORA_OK if channel was added
             */
            uint8_t AddDownlinkChannel(uint8_t index, uint32_t frequency);

            /**
             * Set network mode
             * Choose Public LoRaWAN mode or Private Multitech mode
             *
             * Public mode uses 0x34 sync word with 5/6 second join windows
             * Private mode uses 0x12 sync word with 1/2 second join windows
             *  US915/AU915 Rx1 and Rx2 are fixed per frequency sub band setting
             *
             * @param mode public or private
             * @return LORA_OK
             */
            uint8_t SetNetworkMode(uint8_t mode);

            /**
             * Get a pointer to the mac layer
             * @return Mac mac
             */
            Mac* GetMac();

            /**
             * Get a pointer to the radio
             * Can be used to read radio registers or get a random value based on RSSI
             *
             * @return SxRadio pointer
             */
            SxRadio* GetRadio();

            /**
             * Get the current statistics for the device
             * @return Statistics
             */
            Statistics& GetStats();

            /**
             * Set/restore the current statistics for the device
             */
            void SetStats(const Statistics &stats);
            
            /**
             * Reset the current statistics for the device
             */
            void ResetStats();

            /**
             * Get time on air with current settings for provided payload bytes
             * 13 overhead bytes will be added to payload
             * @param bytes of payload data
             * @return time-on-air in ms
             */
            uint32_t GetTimeOnAir(uint8_t bytes);

            /**
             * Get time off air required to adhere to duty-cycle limitations
             * @return time-off-air in ms
             */
            uint32_t GetTimeOffAir();

            /**
             * Call before setting device in sleep mode to place radio in sleep
             */
            void Sleep();

        protected:
#if defined(TARGET_XDOT_MAX32670)
            SxRadio1262* _radio;
#else
            SxRadio1272* _radio;
#endif
            Settings* _settings;
            Mac* _mac;

        private:
            ChannelPlan* _plan;
            MoteEvents _events;

            // Event queue objects for timing events
            EventQueue _evtQueue;
            Thread _dispatch_thread;
    };

}
#endif
