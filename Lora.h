/**   __  ___     ____  _    ______        __     ____         __                  ____
 *   /  |/  /_ __/ / /_(_)__/_  __/__ ____/ /    / __/_ _____ / /____ __ _  ___   /  _/__  ____
 *  / /|_/ / // / / __/ /___// / / -_) __/ _ \  _\ \/ // (_-</ __/ -_)  ' \(_-<  _/ // _ \/ __/  __
 * /_/  /_/\_,_/_/\__/_/    /_/  \__/\__/_//_/ /___/\_, /___/\__/\__/_/_/_/___/ /___/_//_/\__/  /_/
 * Copyright (C) 2015 by Multi-Tech Systems        /___/
 *
 *
 * @author Jason Reiss
 * @date   10-31-2015
 * @brief  lora namespace defines global settings, structures and enums for the lora library
 *
 * @details
 *
 *
 *
 */

#ifndef __LORA_H__
#define __LORA_H__

#include "mbed.h"
#include <assert.h>
#include "MTSLog.h"
//#include <cstring>
#include <inttypes.h>


namespace lora {

    extern const char* const MAC_VERSION;

    /**
     * Frequency bandwidth of a Datarate, higher bandwidth gives higher datarate
     */
    enum Bandwidth {
        BW_125,
        BW_250,
        BW_500,
        BW_FSK = 50
    };

    /**
     * Spreading factor of a Datarate, lower spreading factor gives higher datarate
     */
    enum SpreadingFactors {
        SF_6 = 6,
        SF_7,
        SF_8,
        SF_9,
        SF_10,
        SF_11,
        SF_12,
        SF_FSK,
        SF_INVALID
    };

    /**
     * Datarates for use with ChannelPlan
     */
    enum Datarates {
        DR_0 = 0,
        DR_1,
        DR_2,
        DR_3,
        DR_4,
        DR_5,
        DR_6,
        DR_7,
        DR_8,
        DR_9,
        DR_10,
        DR_11,
        DR_12,
        DR_13,
        DR_14,
        DR_15
    };

    const uint8_t MIN_DATARATE = (uint8_t) DR_0;             //!< Minimum datarate


    const uint8_t MAX_PHY_PACKET_SIZE = 255;                    //!< Maximum size for a packet
    const uint8_t MAX_APPS = 8;                                 //!< Maximum number of apps sessions to save
    const uint8_t MAX_MULTICAST_SESSIONS = 8;                   //!< Maximum number of multicast sessions to save
    const uint8_t EUI_SIZE = 8;                                 //!< Number of bytes in an EUI
    const uint8_t KEY_SIZE = 16;                                //!< Number of bytes in an AES key

    const uint8_t DEFAULT_NUM_CHANNELS = 16;                    //!< Default number of channels in a plan
    const uint8_t DEFAULT_RX1_DR_OFFSET = 0;                    //!< Default datarate offset for first rx window
    const uint8_t DEFAULT_RX2_DATARATE = 0;                     //!< Default datarate for second rx window
    const uint8_t DEFAULT_TX_POWER = 14;                        //!< Default transmit power
    const uint8_t DEFAULT_CODE_RATE = 1;                        //!< Default coding rate 1:4/5, 2:4/6, 3:4/7, 4:4/8
    const uint8_t DEFAULT_PREAMBLE_LEN = 8;                     //!< Default preamble length

    const int32_t MAX_FCNT_GAP = 16384;                         //!< Maximum allowed gap in sequence numbers before roll-over

    const uint16_t PRIVATE_JOIN_DELAY = 1000;                   //!< Default join delay used for private network
    const uint16_t PUBLIC_JOIN_DELAY = 5000;                    //!< Default join delay used for public network
    const uint16_t DEFAULT_JOIN_DELAY = PRIVATE_JOIN_DELAY;     //!< Default join delay1
    const uint16_t DEFAULT_RX_DELAY = 1000;                     //!< Default delay for first receive window
    const uint16_t DEFAULT_RX_TIMEOUT = 3000;                   //!< Default timeout for receive windows
#if defined(TARGET_MAX32660)
    const uint8_t HI_DR_SYMBOL_TIMEOUT = 30;                    //!< Symbol timeout for receive at datarate with SF < 11
    const uint8_t LO_DR_SYMBOL_TIMEOUT = 20;                    //!< Symbol timeout for receive at datarate with SF > 10
#else
    const uint8_t HI_DR_SYMBOL_TIMEOUT = 12;                    //!< Symbol timeout for receive at datarate with SF < 11
    const uint8_t LO_DR_SYMBOL_TIMEOUT = 8;                     //!< Symbol timeout for receive at datarate with SF > 10
#endif

    const uint16_t RX2_DELAY_OFFSET = 1000;                     //!< Delay between first and second window
    const uint16_t RXC_OFFSET = 50;                             //!< Time between end of RXC after TX and RX1

    const uint16_t BEACON_PREAMBLE_LENGTH = 10U;                //!< Beacon preamble length
    const uint16_t DEFAULT_BEACON_PERIOD = 128U;                //!< Default period of the beacon (in seconds)
    const uint16_t PING_SLOT_LENGTH = 30U;                      //!< Duration of each class B ping slot (in milliseconds)
    const uint32_t BEACON_RESERVED_TIME = 2120U;                //!< Time reserved for beacon broadcast (in milliseconds)
    const uint16_t BEACON_GUARD_TIME = 3000U;                   //!< Guard time before beacon transmission where no ping slots can be scheduled (in milliseconds)
    const std::chrono::seconds MAX_BEACONLESS_OP_TIME = 7200s;  //!< Maximum time to operate in class B since last beacon received (in seconds)
    const uint16_t MAX_CLASS_B_WINDOW_GROWTH = 3U;              //!< Maximum window growth factor for beacons and ping slots in beacon-less operation
    const uint16_t DEFAULT_PING_NB = 1U;                        //!< Default number of ping slots per beacon interval
    const uint16_t CLS_B_PAD = 20U;                             //!< Pad added to the beginning of ping slot rx windows (in milliseconds)
    const uint16_t BEACON_PAD = 100U;                           //!< Pad beacon window is expanded (in milliseconds)

    const int16_t DEFAULT_FREE_CHAN_RSSI_THRESHOLD = -90;       //!< Threshold for channel activity detection (CAD) dBm

    const uint8_t CHAN_MASK_SIZE = 16;                          //!< Number of bits in a channel mask
    const uint8_t COMMANDS_BUFFER_SIZE = 64;                    //!< Size of Mac Command buffer

    const uint8_t PKT_HEADER = 0;                               //!< Index to packet mHdr field
    const uint8_t PKT_ADDRESS = 1;                              //!< Index to first byte of packet address field
    const uint8_t PKT_FRAME_CONTROL = PKT_ADDRESS + 4;          //!< Index to packet fCtrl field @see UplinkControl
    const uint8_t PKT_FRAME_COUNTER = PKT_FRAME_CONTROL + 1;    //!< Index to packet frame counter field
    const uint8_t PKT_OPTIONS_START = PKT_FRAME_COUNTER + 2;    //!< Index to start of optional mac commands

    const uint8_t PKT_JOIN_APP_NONCE = 1;                       //!< Index to application nonce in Join Accept message
    const uint8_t PKT_JOIN_NETWORK_ID = 4;                      //!< Index to network id in Join Accept message
    const uint8_t PKT_JOIN_NETWORK_ADDRESS = 7;                 //!< Index to network address in Join Accept message
    const uint8_t PKT_JOIN_DL_SETTINGS = 11;                    //!< Index to downlink settings in Join Accept message
    const uint8_t PKT_JOIN_RX_DELAY = 12;                       //!< Index to rx delay in Join Accept message

    const uint8_t DEFAULT_ADR_ACK_LIMIT = 64;                   //!< Number of packets without ADR ACK Request
    const uint8_t DEFAULT_ADR_ACK_DELAY = 32;                   //!< Number of packets to expect ADR ACK Response within

    const uint16_t ACK_TIMEOUT = 2000;                          //!< Base millisecond timeout to resend after missed ACK
    const uint16_t ACK_TIMEOUT_RND = 1000;                      //!< Random millisecond adjustment to resend after missed ACK

    const uint8_t FRAME_OVERHEAD = 13;                          //!< Bytes of network info overhead in a frame

    const uint16_t MAX_OFF_AIR_WAIT = 10000U;                   //!< Max time in ms to block for a duty cycle restriction to expire before erroring out

    const int16_t INVALID_RSSI = 0x7FFF;                        //!< Value used in statistics when RSSI value is unknown

    const int16_t INVALID_SNR = 0x7FFF;                         //!< Value used in statistics when SNR value is unknown

    /**
     * Settings for type of network
     *
     * PRIVATE_MTS - Sync Word 0x12, US/AU Downlink frequencies per Frequency Sub Band
     * PUBLIC_LORAWAN - Sync Word 0x34
     * PRIVATE_LORAWAN - Sync Word 0x12
     * PEER_TO_PEER - Sync Word 0x56 used for Dot to Dot communication
     *
     * Join Delay window settings are independent of Network Type setting
     */
    enum NetworkType {
        PRIVATE_MTS = 0,
        PUBLIC_LORAWAN = 1,
        PRIVATE_LORAWAN = 2,
        PEER_TO_PEER = 4
    };

    /**
     * Enum for on/off settings
     */
    enum Enabled {
        OFF = 0,
        ON = 1
    };

    /**
     * Return status of mac functions
     */
    enum MacStatus {
        LORA_OK = 0,
        LORA_ERROR = 1,
        LORA_JOIN_ERROR = 2,
        LORA_SEND_ERROR = 3,
        LORA_MIC_ERROR = 4,
        LORA_ADDRESS_ERROR = 5,
        LORA_NO_CHANS_ENABLED = 6,
        LORA_COMMAND_BUFFER_FULL = 7,
        LORA_UNKNOWN_MAC_COMMAND = 8,
        LORA_ADR_OFF = 9,
        LORA_MAC_BUSY = 10,
        LORA_LINK_BUSY = 11,
        LORA_RADIO_BUSY = 12,
        LORA_BUFFER_FULL = 13,
        LORA_JOIN_BACKOFF = 14,
        LORA_NO_FREE_CHAN = 15,
        LORA_AGGREGATED_DUTY_CYCLE = 16,
        LORA_MAC_COMMAND_ERROR = 17,
        LORA_MAX_PAYLOAD_EXCEEDED = 18,
        LORA_LBT_CHANNEL_BUSY = 19,
        LORA_BEACON_SIZE = 20,
        LORA_BEACON_CRC = 21,
        LORA_UNSUPPORTED = 22
    };

    /**
     * State for Link
     */
    enum LinkState {
        LINK_IDLE = 0,  //!< Link ready to send or receive
        LINK_TX,        //!< Link is busy sending
        LINK_ACK_TX,    //!< Link is busy resending after missed ACK
        LINK_REP_TX,    //!< Link is busy repeating
        LINK_RX,        //!< Link has receive window open
        LINK_RX1,       //!< Link has first received window open
        LINK_RX2,       //!< Link has second received window open
        LINK_RXC,       //!< Link has class C received window open
        LINK_RX_BEACON, //!< Link has a beacon receive window open
        LINK_RX_PING,   //!< Link has a ping slot receive window open
        LINK_P2P        //!< Link is busy sending
    };

    /**
     * State for MAC
     */
    enum MacState {
        MAC_IDLE,
        MAC_RX1,
        MAC_RX2,
        MAC_RXC,
        MAC_TX,
        MAC_JOIN
    };

    /**
     * Operation class for device
     */
    enum MoteClass {
        CLASS_A = 0x00, //!< Device can only receive in windows opened after a transmit
        CLASS_B = 0x01, //!< Device can receive in windows sychronized with gateway beacon
        CLASS_C = 0x02  //!< Device can receive any time when not transmitting
    };

    /**
     * Direction of a packet
     */
    enum Direction {
        DIR_UP = 0,     //!< Packet is sent from mote to gateway
        DIR_DOWN = 1,   //!< Packet was received from gateway
        DIR_PEER = 2    //!< Packet was received from peer
    };


    /**
     * Receive window used by Link
     */
    enum ReceiveWindows {
        RX_1 = 1,           //!< First receive window
        RX_2,               //!< Second receive window
        RX_SLOT,            //!< Ping slot receive window
        RX_BEACON,          //!< Beacon receive window
        RXC,                //!< Class C continuous window
        RX_TEST
    };

    /**
     * Beacon info descriptors for the GwSpecific Info field
     */
    enum BeaconInfoDesc {
        GPS_FIRST_ANTENNA = 0,    //!< GPS coordinates of the gateway's first antenna
        GPS_SECOND_ANTENNA,       //!< GPS coordinates of the gateway's second antenna
        GPS_THIRD_ANTENNA,        //!< GPS coordinates of the gateway's third antenna
    };

    /**
     * Datarate range for a Channel
     */
    typedef union {
            uint8_t Value;
            struct {
                    uint8_t Min :4;
                    uint8_t Max :4;
            } Fields;
    } DatarateRange;

    /**
     * Datarate used for transmitting and receiving
     */
    typedef struct Datarate {
            uint8_t Index;
            uint8_t Bandwidth;
            uint8_t Coderate;
            uint8_t PreambleLength;
            uint8_t SpreadingFactor;
            uint8_t Crc;
            uint8_t TxIQ;
            uint8_t RxIQ;
            uint16_t SymbolTimeout(uint16_t pad_ms = 0);
            float Timeout();
            Datarate();
    } Datarate;

    /**
     * Channel used for transmitting
     */
    typedef struct {
            uint8_t Index;
            uint32_t Frequency;
            DatarateRange DrRange;
    } Channel;

    /**
     * Receive window
     */
    typedef struct {
            uint8_t Index;
            uint32_t Frequency;
            uint8_t DatarateIndex;
    } RxWindow;

    /**
     * Duty band for limiting time-on-air for regional regulations
     */
    typedef struct {
            uint8_t Index;
            uint32_t FrequencyMin;
            uint32_t FrequencyMax;
            uint8_t PowerMax;
            uint16_t DutyCycle;          //!< Multiplier of time on air, 0:100%, 1:50%, 2:33%, 10:10%, 100:1%, 1000,0.1%
            uint32_t TimeOffEnd;         //!< Timestamp when this band will be available
    } DutyBand;

    /**
     * Beacon data content (w/o CRCs and RFUs)
     */
    typedef struct {
        uint32_t Time;
        uint8_t InfoDesc;
        uint32_t Latitude;
        uint32_t Longitude;
    } BeaconData_t;

    /**
     * Device configuration
     */
    typedef struct {
            uint8_t FrequencyBand;      //!< Used to choose ChannelPlan
            uint8_t EUI[8];             //!< Unique identifier assigned to device
    } DeviceConfig;

    /**
     * Network configuration
     */
    typedef struct {
            uint8_t Mode;               //!< PUBLIC, PRIVATE or PEER_TO_PEER network mode
            uint8_t Class;              //!< Operating class of device
            uint8_t EUI[8];             //!< Network ID or AppEUI
            uint16_t DevNonce;         //!< Incrementing DevNonce Counter
            uint32_t AppNonce;          //!< Incrementing AppNonce Counter
            uint8_t Key[16];            //!< Network Key or AppKey
            uint8_t GenAppKey[16];      //!< Generic App Key, will be AppKey for LW 1.1.x
            uint8_t McKEKey[16];        //!< Multicast Key Encryption Key
            uint8_t JoinDelay;          //!< Number of seconds to wait before 1st RX Window
            uint8_t RxDelay;            //!< Number of seconds to wait before 1st RX Window
            uint8_t FrequencySubBand;   //!< FrequencySubBand used for US915 hybrid operation 0:72 channels, 1:1-8 channels ...
            uint8_t AckEnabled;         //!< Enable confirmed messages to be sent with Retries
            uint8_t Retries;            //!< Number of times to resend a packet without receiving an ACK, redundancy
            uint8_t ADREnabled;         //!< Enable adaptive datarate
            uint8_t AdrAckLimit;       //!< Number of uplinks without a downlink to allow before setting ADRACKReq
            uint8_t AdrAckDelay;       //!< Number of downlinks to expect ADR ACK Response within
            uint8_t CADEnabled;         //!< Enable listen before talk/channel activity detection
            uint8_t RepeaterMode;       //!< Limit payloads to repeater compatible sizes
            uint8_t TxPower;            //!< Default radio output power in dBm
            uint8_t TxPowerMax;         //!< Max transmit power
            uint8_t TxDatarate;         //!< Datarate for P2P transmit
            uint32_t TxFrequency;       //!< Frequency for P2P transmit
            int8_t AntennaGain;         //!< Antenna Gain
            uint8_t ClassBTimeout;      //!< Time in seconds a device is expected to respond to ACK or MAC commands in Class B packet
            uint8_t ClassCTimeout;      //!< Time in seconds a device is expected to respond to ACK or MAC commands in Class C packet
            uint16_t P2PACKTimeout;
            uint16_t P2PACKBackoff;
            uint8_t JoinRx1DatarateOffset;  //!< Offset for datarate for first window
            uint32_t JoinRx2Frequency;      //!< Frequency used in second window
            uint8_t JoinRx2DatarateIndex;   //!< Datarate for second window
            uint8_t PingPeriodicity;        //!< Number of ping slots to open in a beacon interval (2^(7-PingPeriodicity))
    } NetworkConfig;

    /**
     * Network session info
     * Some settings are acquired in join message and others may be changed through Mac Commands from server
     */
    typedef struct {
            uint8_t Joined;                     //!< State of session
            uint8_t Class;                      //!< Operating class of device
            uint8_t Rx1DatarateOffset;          //!< Offset for datarate for first window
            uint32_t Rx2Frequency;              //!< Frequency used in second window
            uint8_t Rx2DatarateIndex;           //!< Datarate for second window
            uint32_t BeaconFrequency;           //!< Frequency used for the beacon window
            bool BeaconFreqHop;                 //!< Beacon frequency hopping enable
            uint32_t PingSlotFrequency;         //!< Frequency used for ping slot windows
            uint8_t PingSlotDatarateIndex;      //!< Datarate for the ping slots
            bool PingSlotFreqHop;               //!< Ping slot frequency hopping enable
            uint8_t TxPower;                    //!< Current total radiated output power in dBm
            uint8_t TxDatarate;                 //!< Current datarate can be changed when ADR is enabled
            uint32_t Address;                   //!< Network address
            uint32_t NetworkID;                 //!< Network ID 24-bits
            uint8_t NetworkSessionKey[16];      //!< Network session key
            uint8_t ApplicationSessionKey[16];  //!< Data session key
            uint16_t ChannelMask[4];            //!< Current channel mask
            uint16_t ChannelMask500k;           //!< Current channel mask for 500k channels
            uint32_t DownlinkCounter;           //!< Downlink counter of last packet received from server
            uint32_t UplinkCounter;             //!< Uplink counter of last packet sent to server
            uint8_t Redundancy;                 //!< Number of time to repeat an uplink
            uint8_t MaxDutyCycle;               //!< Current Max Duty Cycle value
            uint32_t JoinTimeOnAir;              //!< Balance of time on air used during join attempts
            uint32_t JoinTimeOffEnd;            //!< RTC time of next join attempt
            uint32_t JoinFirstAttempt;          //!< RTC time of first failed join attempt
            uint32_t AggregatedTimeOffEnd;      //!< Time off air expiration for aggregate duty cycle
            uint16_t AggregateDutyCycle;        //!< Used for enforcing time-on-air
            uint8_t AdrCounter;                 //!< Current number of packets received without downlink from server
            uint8_t RxDelay;                    //!< Number of seconds to wait before 1st RX Window
            uint8_t CommandBuffer[COMMANDS_BUFFER_SIZE]; //!< Buffer to hold Mac Commands and parameters to be sent in next packet
            uint8_t CommandBufferIndex;         //!< Index to place next Mac Command, also current size of Command Buffer
            bool SrvRequestedAck;               //!< Indicator of ACK requested by server in last packet received
            bool DataPending;                   //!< Indicator of data pending at server
            uint8_t RxTimingSetupReqReceived;   //!< Indicator that RxTimingSetupAns should be included in uplink
            uint8_t RxParamSetupReqAnswer;      //!< Indicator that RxParamSetupAns should be included in uplink
            uint8_t DlChannelReqAnswer;         //!< Indicator that DlChannelAns should be included in uplink
            uint8_t DownlinkDwelltime;          //!< On air dwell time for downlink packets 0:NONE,1:400ms
            uint8_t UplinkDwelltime;            //!< On air dwell time for uplink packets 0:NONE,1:400ms
            uint8_t Max_EIRP;                   //!< Maximum allowed EIRP for uplink
    } NetworkSession;

    /**
     * Multicast session info
     */
    typedef struct MulticastSession {
            uint32_t Address;               //!< Network address
            uint8_t NetworkSessionKey[16];  //!< Network session key
            uint8_t DataSessionKey[16];     //!< Data session key
            uint32_t DownlinkCounter;       //!< Downlink counter of last packet received from server
            int8_t Periodicity;             //!< Number of downlink windows to open per beacon period
            uint32_t Frequency;             //!< Frequency used for downlink windows
            uint8_t DatarateIndex;          //!< Datarate used for downlink windows
            bool DataPending;               //!< Indicates network has data pending for this address
            uint16_t PingPeriod;
            int32_t NextPingSlot;
            MulticastSession() :
                Periodicity(-1)
            {

            }
    } MulticastSession;

    /**
     * Statistics of current network session
     */
    typedef struct Statistics {
            uint32_t Up;                    //!< Number of uplink packets sent
            uint32_t Down;                  //!< Number of downlink packets received
            uint32_t Joins;                 //!< Number of join requests sent
            uint32_t JoinFails;             //!< Number of join requests without response or invalid response
            uint32_t MissedAcks;            //!< Number of missed acknowledgement attempts of confirmed packets
            uint32_t CRCErrors;             //!< Number of CRC errors in received packets
            int32_t AvgCount;              //!< Number of packets used to compute rolling average of RSSI and SNR
            int16_t Rssi;                   //!< RSSI of last packet received
            int16_t RssiMin;                //!< Minimum RSSI of last AvgCount packets
            int16_t RssiMax;                //!< Maximum RSSI of last AvgCount packets
            int16_t RssiAvg;                //!< Rolling average RSSI of last AvgCount packets
            int16_t Snr;                     //!< SNR of last packet received
            int16_t SnrMin;                  //!< Minimum SNR of last AvgCount packets
            int16_t SnrMax;                  //!< Maximum SNR of last AvgCount packets
            int16_t SnrAvg;                  //!< Rolling average SNR of last AvgCount packets
    } Statistics;

    /**
     *  Testing settings
     */
    typedef struct {
            uint8_t TestMode;
            uint8_t SkipMICCheck;
            uint8_t DisableDutyCycle;
            uint8_t DisableRx1;
            uint8_t DisableRx2;
            uint8_t FixedUplinkCounter;
            uint8_t DisableRandomJoinDatarate;
            uint8_t DisableAppNonceValidation;
            uint8_t DisableADRIncrementDatarate;
    } Testing;

    /**
     * Combination of device, network, testing settings and statistics
     */
    typedef struct {
            DeviceConfig Device;
            NetworkConfig Network;
            NetworkSession Session;
            MulticastSession Multicast[MAX_MULTICAST_SESSIONS];
            Statistics Stats;
            Testing Test;
    } Settings;

    /**
     * Downlink settings sent in Join Accept message
     */
    typedef union {
            uint8_t Value;
            struct {
                    uint8_t Rx2Datarate :4;
                    uint8_t Rx1Offset :3;
                    uint8_t RFU :1;
            };
    } DownlinkSettings;

    /**
     * Frame structure for Join Request
     */
    typedef struct {
            uint8_t Type;
            uint8_t AppEUI[8];
            uint8_t DevEUI[8];
            uint8_t Nonce[2];
            uint8_t MIC[4];
    } JoinRequestFrame;

    /**
     * Mac header of uplink and downlink packets
     */
    typedef union {
            uint8_t Value;
            struct {
                    uint8_t Major :2;
                    uint8_t RFU :3;
                    uint8_t MType :3;
            } Bits;
    } MacHeader;

    /**
     * Frame control field of uplink packets
     */
    typedef union {
            uint8_t Value;
            struct {
                    uint8_t OptionsLength :4;
                    uint8_t ClassB :1;
                    uint8_t Ack :1;
                    uint8_t AdrAckReq :1;
                    uint8_t Adr :1;
            } Bits;
    } UplinkControl;

    /**
     * Frame control field of downlink packets
     */
    typedef union {
            uint8_t Value;
            struct {
                    uint8_t OptionsLength :4;
                    uint8_t FPending :1;
                    uint8_t Ack :1;
                    uint8_t RFU :1;
                    uint8_t Adr :1;
            } Bits;
    } DownlinkControl;

    typedef struct PingSlot {
        uint32_t MSec;
        int8_t Id;
        PingSlot() : MSec(0), Id(-1) {}
        PingSlot(uint32_t msec, int8_t id) : MSec(msec), Id(id) {}
    } PingSlot;

    /**
     * Frame type of packet
     */
    typedef enum {
        FRAME_TYPE_JOIN_REQ = 0x00,
        FRAME_TYPE_JOIN_ACCEPT = 0x01,
        FRAME_TYPE_DATA_UNCONFIRMED_UP = 0x02,
        FRAME_TYPE_DATA_UNCONFIRMED_DOWN = 0x03,
        FRAME_TYPE_DATA_CONFIRMED_UP = 0x04,
        FRAME_TYPE_DATA_CONFIRMED_DOWN = 0x05,
        FRAME_TYPE_RFU = 0x06,
        FRAME_TYPE_PROPRIETARY = 0x07,
    } FrameType;

    /**
     * LoRaWAN mote MAC commands
     */
    typedef enum {
        /* Class A */
        MOTE_MAC_LINK_CHECK_REQ = 0x02,
        MOTE_MAC_LINK_ADR_ANS = 0x03,
        MOTE_MAC_DUTY_CYCLE_ANS = 0x04,
        MOTE_MAC_RX_PARAM_SETUP_ANS = 0x05,
        MOTE_MAC_DEV_STATUS_ANS = 0x06,
        MOTE_MAC_NEW_CHANNEL_ANS = 0x07,
        MOTE_MAC_RX_TIMING_SETUP_ANS = 0x08,
        MOTE_MAC_TX_PARAM_SETUP_ANS = 0x09,
        MOTE_MAC_DL_CHANNEL_ANS = 0x0A,
        MOTE_MAC_REKEY_IND = 0x0B,
        MOTE_MAC_ADR_PARAM_SETUP_ANS = 0x0C,
        MOTE_MAC_DEVICE_TIME_REQ = 0x0D,
        MOTE_MAC_REJOIN_PARAM_SETUP_ANS = 0x0F,

        /* Class B */
        MOTE_MAC_PING_SLOT_INFO_REQ = 0x10,
        MOTE_MAC_PING_SLOT_CHANNEL_ANS = 0x11,
        MOTE_MAC_BEACON_TIMING_REQ = 0x12,
        MOTE_MAC_BEACON_FREQ_ANS = 0x13,

        /* Multitech */
        MOTE_MAC_PING_REQ = 0x80,
        MOTE_MAC_CHANGE_CLASS = 0x81,
        MOTE_MAC_MULTIPART_START_REQ = 0x82,
        MOTE_MAC_MULTIPART_START_ANS = 0x83,
        MOTE_MAC_MULTIPART_CHUNK = 0x84,
        MOTE_MAC_MULTIPART_END_REQ = 0x85,
        MOTE_MAC_MULTIPART_END_ANS = 0x86
    } MoteCommand;

    extern uint8_t MoteCommandSizes[22];

    /*!
     * LoRaWAN server MAC commands
     */
    typedef enum {
        /* Class A */
        SRV_MAC_LINK_CHECK_ANS = 0x02,
        SRV_MAC_LINK_ADR_REQ = 0x03,
        SRV_MAC_DUTY_CYCLE_REQ = 0x04,
        SRV_MAC_RX_PARAM_SETUP_REQ = 0x05,
        SRV_MAC_DEV_STATUS_REQ = 0x06,
        SRV_MAC_NEW_CHANNEL_REQ = 0x07,
        SRV_MAC_RX_TIMING_SETUP_REQ = 0x08,
        SRV_MAC_TX_PARAM_SETUP_REQ = 0x09,
        SRV_MAC_DL_CHANNEL_REQ = 0x0A,
        SRV_MAC_REKEY_CONF = 0x0B,
        SRV_MAC_ADR_PARAM_SETUP_REQ = 0x0C,
        SRV_MAC_DEVICE_TIME_ANS = 0x0D,
        SRV_MAC_FORCE_REJOIN_REQ = 0x0E,
        SRV_MAC_REJOIN_PARAM_SETUP_REQ = 0x0F,

        /* Class B */
        SRV_MAC_PING_SLOT_INFO_ANS = 0x10,
        SRV_MAC_PING_SLOT_CHANNEL_REQ = 0x11,
        SRV_MAC_BEACON_TIMING_ANS = 0x12,
        SRV_MAC_BEACON_FREQ_REQ = 0x13,

        /* Multitech */
        SRV_MAC_PING_ANS = 0x80,
        SRV_MAC_CHANGE_CLASS = 0x81,
        SRV_MAC_MULTIPART_START_REQ = 0x82,
        SRV_MAC_MULTIPART_START_ANS = 0x83,
        SRV_MAC_MULTIPART_CHUNK = 0x84,
        SRV_MAC_MULTIPART_END_REQ = 0x85,
        SRV_MAC_MULTIPART_END_ANS = 0x86
    } ServerCommand;

    /**
     * Radio configuration options
     */
    typedef enum RadioCfg {
        NO_RADIO_CFG,
        TX_RADIO_CFG,
        RX_RADIO_CFG
    } RadioCfg_t;

    /**
     * Random seed for software RNG
     */
    void srand(uint32_t seed);

    /**
     * Software RNG for consistent results across differing hardware
     */
    int rand(void);

    /**
     * Generate random number bounded by min and max
     */
    int32_t rand_r(int32_t min, int32_t max);

    uint8_t CountBits(uint16_t mask);

    /**
     * Copy 3-bytes network order from array into LSB of integer value
     */
    void CopyNetIDtoInt(const uint8_t* arr, uint32_t& val);

    /**
     * Copy LSB 3-bytes from integer value into array network order
     */
    void CopyNetIDtoArray(uint32_t val, uint8_t* arr);

    /**
     * Copy 4-bytes network order from array in to integer value
     */
    void CopyAddrtoInt(const uint8_t* arr, uint32_t& val);

    /**
     * Copy 4-bytes from integer in to array network order
     */
    void CopyAddrtoArray(uint32_t val, uint8_t* arr);

    /**
     * Copy 3-bytes network order from array into integer value and multiply by 100
     */
    void CopyFreqtoInt(const uint8_t* arr, uint32_t& freq);

    /**
     * Reverse memory copy
     */
    void memcpy_r(uint8_t *dst, const uint8_t *src, size_t n);

}

#endif

