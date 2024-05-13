/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Generic radio driver definition

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#ifndef __SXRADIO_H__
#define __SXRADIO_H__

#include <stdint.h>
#include "SxRadioEvents.h"

/*!
 * \brief Radio driver definition
 */
class SxRadio
{
public:
    /*!
     * Radio driver supported modems
     */
    typedef enum
    {
        MODEM_FSK = 0,
        MODEM_LORA,
    }RadioModems_t;

    /*!
     * Radio driver internal state machine states definition
     */
    typedef enum
    {
        RF_IDLE = 0,
        RF_RX_RUNNING,
        RF_TX_RUNNING,
        RF_CAD,
        RF_LBT
    }RadioState_t;

    SxRadio(uint32_t WakeupTime) : WakeupTime(WakeupTime), freq_offset(0), State(RF_IDLE), Modem(MODEM_LORA) { }
    virtual ~SxRadio() {};

    /*!
     * \brief Initializes the radio
     *
     * \param [IN] events Structure containing the driver callback functions
     */
    virtual void Init( SxRadioEvents *events ) = 0;
    /*!
     * \brief Prepares the radio for destruction
     */
    virtual void Terminate( void ) = 0;
    /*!
     * Return current radio status
     *
     * \param status Radio status.[RF_IDLE, RF_RX_RUNNING, RF_TX_RUNNING]
     */
    virtual RadioState_t Status( void ) { return State; }
    /*!
     * \brief Configures the radio with the given modem
     *
     * \param [IN] modem Modem to be used [0: FSK, 1: LoRa]
     */
    virtual void SetModem( RadioModems_t modem ) = 0;
	virtual RadioModems_t GetModem( void ) { return Modem; }
    /*!
     * \brief Sets the channel frequency
     *
     * \param [IN] freq         Channel RF frequency
     */
    virtual void SetChannel( uint32_t freq ) = 0;
    /*!
     * \brief Sets the channels configuration
     *
     * \param [IN] modem      Radio modem to be used [0: FSK, 1: LoRa]
     * \param [IN] freq       Channel RF frequency
     * \param [IN] rssiThresh RSSI threshold
     * \param [IN] rssiVal    pointer to variable to hold RSSI value if desired - ignored if NULL
     *
     * \retval isFree         [true: Channel is free, false: Channel is not free]
     */
    virtual bool IsChannelFree( RadioModems_t modem, uint32_t freq, int16_t rssiThresh, uint32_t timeout = 5000, int16_t *rssiVal = NULL ) = 0;
    /*!
     * \brief Generates a 32 bits random value based on the RSSI readings
     *
     * \remark This function sets the radio in LoRa modem mode and disables
     *         all interrupts.
     *         After calling this function either Radio.SetRxConfig or
     *         Radio.SetTxConfig functions must be called.
     *
     * \retval randomValue    32 bits random value
     */
    virtual uint32_t Random( void ) = 0;
    /*!
     * \brief Sets the reception parameters
     *
     * \param [IN] modem        Radio modem to be used [0: FSK, 1: LoRa]
     * \param [IN] bandwidth    Sets the bandwidth
     *                          FSK : >= 2600 and <= 250000 Hz
     *                          LoRa: [0: 125 kHz, 1: 250 kHz,
     *                                 2: 500 kHz, 3: Reserved]
     * \param [IN] datarate     Sets the Datarate
     *                          FSK : 600..300000 bits/s
     *                          LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
     *                                10: 1024, 11: 2048, 12: 4096  chips]
     * \param [IN] coderate     Sets the coding rate (LoRa only)
     *                          FSK : N/A ( set to 0 )
     *                          LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
     * \param [IN] bandwidthAfc Sets the AFC Bandwidth (FSK only)
     *                          FSK : >= 2600 and <= 250000 Hz
     *                          LoRa: N/A ( set to 0 )
     * \param [IN] preambleLen  Sets the Preamble length
     *                          FSK : Number of bytes
     *                          LoRa: Length in symbols (the hardware adds 4 more symbols)
     * \param [IN] symbTimeout  Sets the RxSingle timeout value (LoRa only)
     *                          FSK : N/A ( set to 0 )
     *                          LoRa: timeout in symbols
     * \param [IN] fixLen       Fixed length packets [0: variable, 1: fixed]
     * \param [IN] payloadLen   Sets payload length when fixed length is used
     * \param [IN] crcOn        Enables/Disables the CRC [0: OFF, 1: ON]
     * \param [IN] FreqHopOn    Enables disables the intra-packet frequency hopping
     *                          FSK : N/A ( set to 0 )
     *                          LoRa: [0: OFF, 1: ON]
     * \param [IN] HopPeriod    Number of symbols bewteen each hop
     *                          FSK : N/A ( set to 0 )
     *                          LoRa: Number of symbols
     * \param [IN] iqInverted   Inverts IQ signals (LoRa only)
     *                          FSK : N/A ( set to 0 )
     *                          LoRa: [0: not inverted, 1: inverted]
     * \param [IN] rxContinuous Sets the reception in continuous mode
     *                          [false: single mode, true: continuous mode]
     * \param [IN] fskPad       Duration in ms to increase FSK rx window
     *                          FSK: time in ms to increase FSK rx window duration
     *                          LoRa: N/A
     */
    virtual void SetRxConfig( RadioModems_t modem, uint32_t bandwidth,
                              uint32_t datarate, uint8_t coderate,
                              uint32_t bandwidthAfc, uint16_t preambleLen,
                              uint16_t symbTimeout, bool fixLen,
                              uint8_t payloadLen,
                              bool crcOn, bool FreqHopOn, uint8_t HopPeriod,
                              bool iqInverted, bool rxContinuous , uint32_t fskPad = 0) = 0;
    /*!
     * \brief Sets the transmission parameters
     *
     * \param [IN] modem        Radio modem to be used [0: FSK, 1: LoRa]
     * \param [IN] power        Sets the output power [dBm]
     * \param [IN] fdev         Sets the frequency deviation (FSK only)
     *                          FSK : [Hz]
     *                          LoRa: 0
     * \param [IN] bandwidth    Sets the bandwidth (LoRa only)
     *                          FSK : 0
     *                          LoRa: [0: 125 kHz, 1: 250 kHz,
     *                                 2: 500 kHz, 3: Reserved]
     * \param [IN] datarate     Sets the Datarate
     *                          FSK : 600..300000 bits/s
     *                          LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
     *                                10: 1024, 11: 2048, 12: 4096  chips]
     * \param [IN] coderate     Sets the coding rate (LoRa only)
     *                          FSK : N/A ( set to 0 )
     *                          LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
     * \param [IN] preambleLen  Sets the preamble length
     *                          FSK : Number of bytes
     *                          LoRa: Length in symbols (the hardware adds 4 more symbols)
     * \param [IN] fixLen       Fixed length packets [0: variable, 1: fixed]
     * \param [IN] crcOn        Enables disables the CRC [0: OFF, 1: ON]
     * \param [IN] FreqHopOn    Enables disables the intra-packet frequency hopping
     *                          FSK : N/A ( set to 0 )
     *                          LoRa: [0: OFF, 1: ON]
     * \param [IN] HopPeriod    Number of symbols bewteen each hop
     *                          FSK : N/A ( set to 0 )
     *                          LoRa: Number of symbols
     * \param [IN] iqInverted   Inverts IQ signals (LoRa only)
     *                          FSK : N/A ( set to 0 )
     *                          LoRa: [0: not inverted, 1: inverted]
     * \param [IN] timeout      Transmission timeout [us]
     */
    virtual void SetTxConfig( RadioModems_t modem, int8_t power, uint32_t fdev,
                              uint32_t bandwidth, uint32_t datarate,
                              uint8_t coderate, uint16_t preambleLen,
                              bool fixLen, bool crcOn, bool FreqHopOn,
                              uint8_t HopPeriod, bool iqInverted, uint32_t timeout ) = 0;

    virtual void SetTxPower(int8_t power) = 0;

    virtual void SetTxContinuousWave( uint32_t freq, int8_t power, uint16_t time ) = 0;

    virtual void SetTxContinuousWave( uint32_t freq, int8_t pa, int8_t hp, int8_t tx, uint16_t time ) = 0;

    /*!
     * \brief Checks if the given RF frequency is supported by the hardware
     *
     * \param [IN] frequency RF frequency to be checked
     * \retval isSupported [true: supported, false: unsupported]
     */
    virtual bool CheckRfFrequency( uint32_t frequency ) { return true; }
    /*!
     * \brief Computes the packet time on air for the given payload
     *
     * \Remark Can only be called once SetRxConfig or SetTxConfig have been called
     *
     * \param [IN] modem      Radio modem to be used [0: FSK, 1: LoRa]
     * \param [IN] pktLen     Packet payload length
     *
     * \retval airTime        Computed airTime for the given packet payload length
     */
    virtual double TimeOnAir( RadioModems_t modem, uint8_t pktLen ) = 0;
    /*!
     * \brief Sends the buffer of size. Prepares the packet to be sent and sets
     *        the radio in transmission
     *
     * \param [IN]: buffer     Buffer pointer
     * \param [IN]: size       Buffer size
     */
    virtual void Send( const uint8_t *buffer, uint8_t size ) = 0;
    /*!
     * \brief Sets the radio in sleep mode
     */
    virtual void Sleep( void ) = 0;
    /*!
     * \brief Sets the radio in standby mode
     */
    virtual void Standby( void ) = 0;
    /*!
     * \brief Sets the radio in reception mode for the given time
     * \param [IN] timeout Reception timeout [us]
     *                     [0: continuous, others timeout]
     */
    virtual void Rx( uint32_t timeout ) = 0;
    /*!
     * \brief Start a Channel Activity Detection
     */
    virtual void StartCad( void ) = 0;
    /*!
     * \brief Reads the current RSSI value
     *
     * \retval rssiValue Current RSSI value in [dBm]
     */
    virtual int16_t Rssi( RadioModems_t modem ) = 0;
    /*!
     * \brief Writes the radio register at the specified address
     *
     * \param [IN]: addr Register address
     * \param [IN]: data New register value
     */
#if !defined(TARGET_XDOT_MAX32670)
    virtual void Write( uint8_t addr, uint8_t data ) = 0;
    /*!
     * \brief Reads the radio register at the specified address
     *
     * \param [IN]: addr Register address
     * \retval data Register value
     */
    virtual uint8_t Read ( uint8_t addr ) = 0;
    /*!
     * \brief Writes multiple radio registers starting at address
     *
     * \param [IN] addr   First Radio register address
     * \param [IN] buffer Buffer containing the new register's values
     * \param [IN] size   Number of registers to be written
     */
    virtual void WriteBuffer( uint8_t addr, const uint8_t *buffer, uint8_t size ) = 0;
    /*!
     * \brief Reads multiple radio registers starting at address
     *
     * \param [IN] addr First Radio register address
     * \param [OUT] buffer Buffer where to copy the registers data
     * \param [IN] size Number of registers to be read
     */
    virtual void ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size ) = 0;
#else
    virtual void SetSyncWord( int mode ) = 0;
#endif
    virtual void SignalMacEvent(void) {};
    virtual void SignalLinkEvent(void) {};
    virtual void SignalRxTimeout(void) {};

    virtual void ResetRadio(void) {};

    virtual uint32_t GetTimeOnAir(void) = 0;

    void GrabMutex(void) { mutex.lock(); }
    void ReleaseMutex(void) { mutex.unlock(); }

    int32_t GetFrequencyOffset() { return freq_offset; }
    void SetFrequencyOffset(int32_t offset) { freq_offset = offset; }

    const uint32_t WakeupTime;

#if defined(TARGET_XDOT_MAX32670)
    virtual uint8_t GetVddMin(void) = 0;
    virtual void SetVddMin(uint8_t vdd) = 0;

#if defined(MTS_RADIO_CTRL_COMMANDS)
    virtual void SetLNA(uint8_t rxBoosted) = 0;
    virtual uint8_t GetLNA(void) = 0;
    virtual void SetPaDutyCycle(uint8_t paDutyCycle) = 0;
    virtual uint8_t GetPaDutyCycle(void) = 0;
    virtual void SetHpMax(uint8_t hpMax) = 0;
    virtual uint8_t GetHpMax(void) = 0;
    virtual void SetXTATrim(uint8_t xtaTrim) = 0;
    virtual uint8_t GetXTATrim(void) = 0;
    virtual void SetXTBTrim(uint8_t xtbTrim) = 0;
    virtual uint8_t GetXTBTrim(void) = 0;
    virtual void setSWState(uint8_t value) = 0;
    virtual uint8_t getSWState(void) = 0;
    virtual void SetRampTime(uint8_t rampTime) = 0;
    virtual uint8_t GetRampTime(void) = 0;
    virtual void SetTxInfPreamble(uint8_t enable, int8_t power, uint32_t frequency, uint32_t bandwidth, uint8_t spreadingFactor) = 0;
    virtual uint8_t GetTxInfPreamble(void) = 0;
#endif //__MTS_RADIO_CTRL_COMMANDS__
#endif //__TARGET_XDOT_MAX32670__

protected:
    int32_t freq_offset;

    RadioState_t State;

    RadioModems_t Modem;

    /*!
     * Access protection
     */
    Mutex mutex;

};

#endif // __SXRADIO_H__

