/* mbed Example Program
 * Copyright (c) 2006-2014 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/***************************************************************** Includes **/
#include "xmc_wdt.h"
#include "xmc_scu.h"
#include "Watchdog.h"
#include "mbed.h"

/****************************************************************** Globals **/
XMC_WDT_CONFIG_t wdt_cfg;

/**************************************************************** Functions **/

/** @brief Constructor
 *  Check if watchdog was cause of reset
 */
Watchdog::Watchdog() : {

    /* Check if watchdog was cause of reset */
    if ((XMC_SCU_RESET_GetDeviceResetReason() & XMC_SCU_RESET_REASON_WATCHDOG) != 0){

        wdreset = true;
    }
    wdreset = false;

    /* Clear system reset status */
    SCU_RESET->RSTCLR |= SCU_RESET_RSTCLR_RSCLR_Msk;
}

/** @brief Destructor
 *  Disable & stop watchdog timer
 */
Watchdog::~Watchdog() : {

    XMC_WDT_Stop();
}

/** @brief Configure watchdog timer
 *
 *  @param time Time in seconds
 */
void Watchdog::configure(float time) {

    float sec_time;

    /* Use standby clock as watchdog clock source */
    XMC_SCU_HIB_EnableHibernateDomain();
    XMC_SCU_CLOCK_SetWdtClockSource(XMC_SCU_CLOCK_WDTCLKSRC_STDBY);
    XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_WDT);

    wdt_time = time / (1 / XMC_SCU_CLOCK_GetWdtClockFrequency());

    /* Configure watchdog */
    wdt_cfg.window_lower_bound = 0;
    wdt_cfg.window_upper_bound = (uint32_t)wdt_time;
    wdt_cfg.service_pulse_width = 255;


    XMC_WDT_Init(&wdt_cfg);
    XMC_WDT_Start();
}

/** @brief Watchdog service
 *
 */
void Watchdog::service() {

    XMC_WDT_Service();
}

/** @brief Check if watchdog was cause of reset
 *
 *  @return true if yes, no otherwise
 */
bool Watchdog::watchdogCausedReset() {

    return wdreset;
}

/*EOF*/
