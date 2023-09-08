/**********************************************************************
* COPYRIGHT 2022 MULTI-TECH SYSTEMS, INC.
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
#ifndef __LOW_POWER_H__
#define __LOW_POWER_H__


namespace LowPower {

void enableSysTick();

/**
 * Configure all the external GPIOs for low power. Used by our AT firmware
 * application. Custom applications need to configure according to what is
 * attached to their external GPIOs.
 * @param wakeMode RTC_ALARM, INTERRUPT, RTC_ALARM_OR_INTERRUPT
 * @param wakePin - Device dependent
 * @returns void
 */
void configExtGpios(uint8_t wakeMode, PinName wakePin);

void configureClocksForSleep();

/**
 * This is sleep mode. Invoked by AT firmware AT+SLEEP=1 or the mDot sleep(...)
 * function. In this mode, the mdot-library takes care of putting the Internal
 * gpio pins into a low power state but leaves it to the application to put the
 * external pins into a low power state.
 * @param wakeMode RTC_ALARM, INTERRUPT, RTC_ALARM_OR_INTERRUPT
 * @param wakePin - Device dependent
 * @param stopModeForDeepSleep - mDot can't do standby mode. Some pins require specific pull ups/downs.
 * @returns void
 */
#if defined(TARGET_MTS_MDOT_F411RE)
void enterStopMode(uint8_t wakeMode, PinName wakePin, bool stopModeForDeepSleep);
#else
void enterStopMode(uint8_t wakeMode, PinName wakePin);
#endif

/**
 * This is deepsleep mode. Invoked by AT firmware AT+SLEEP=0 or the mDot sleep(...)
 * function. In this mode, the mdot-library takes care of putting the Internal
 * and external gpio pins into a low power state. Custom applications will not be
 * able to use this if different external pin configurations are needed to achieve
 * low power due to externally attached circuitry.
 * @param none
 * @returns void
 */
#if defined(TARGET_XDOT_MAX32670)
void enterStandbyMode(uint8_t wakeMode, PinName wakePin);
#else
void enterStandbyMode();
#endif

void enableStandbyWakePin();

void disableStandbyWakePin();

void wakeup();

} // namespace LowPower

#endif
