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
#ifndef __SXRADIOEVENTS_H__
#define __SXRADIOEVENTS_H__

/*!
 * \brief Radio driver callback functions
 */
class SxRadioEvents
{
public:
    /*!
     * \brief  Tx Start callback prototype.
     */
    virtual void TxStart( void ) {}
    /*!
     * \brief  Tx Done callback prototype.
     */
    virtual void TxDone( void ) {}
    /*!
     * \brief  Tx Timeout callback prototype.
     */
    virtual void TxTimeout( void ) {}

    /*!
     * \brief Rx Done callback prototype.
     *
     * \param [IN] payload Received buffer pointer
     * \param [IN] size    Received buffer size
     * \param [IN] rssi    RSSI value computed while receiving the frame [dBm]
     * \param [IN] snr     Raw SNR value given by the radio hardware
     *                     FSK : N/A ( set to 0 )
     *                     LoRa: SNR value is two's complement in 1/4 dB
     */
    virtual void RxDone( uint8_t *payload, uint16_t size, int16_t rssi, int16_t snr ) {}
    virtual void RxDone( uint8_t *payload, uint16_t size, int16_t rssi, int16_t snr, uint8_t wnd ) {}

    /*!
     * \brief Called if Beacon Window cannot be opened or is missed
     *
     * \param [IN] beaconTime  Updated time of beacon for the period
     * \param [IN] no_rx       True if called from rx done
     */
    virtual void OnBeaconless( uint32_t beaconTime, bool no_rx = false ) {}



    /*!
     * \brief  Rx Timeout callback prototype.
     */
    virtual void RxTimeout( void ) {}
    /*!
     * \brief Rx Error callback prototype.
     */
    virtual void RxError( void ) {}
    /*!
     * \brief  FHSS Change Channel callback prototype.
     *
     * \param [IN] currentChannel   Index number of the current channel
     */
    virtual void FhssChangeChannel( uint8_t currentChannel ) {}
    /*!
     * \brief CAD Done callback prototype.
     *
     * \param [IN] channelActivityDetected  Channel Activity detected during the CAD
     */
    virtual void CadDone( bool channelActivityDetected ) {}
    /*!
     * \brief Mac Event callback prototype.
     */
    virtual void MacEvent( void ) {}

    virtual void LinkIdle(void) {}
};

#endif // __SXRADIOEVENTS_H__

