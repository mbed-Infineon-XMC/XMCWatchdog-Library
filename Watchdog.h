/** Watchdog class for the XMC MCU family.
 *
 * Example:
 */

#ifndef WATCHDOG_H
#define WATCHDOG_H
#include "mbed.h"

class Watchdog {
public:
    /** Create HelloWorld instance
     */
    Watchdog();

    /** Delete HelloWorld instance
     */
    ~Watchdog();

    /** Print the text
     *
     * @param timeout in seconds
     */
    void configure(float timeout);

    /** Watchdog service
     */
    void service();

    /** Check if watchdog was cause of reset
     *
     * @returns
     *  true    watchdog was cause of reset
     *  fasle   watchdog was not cause of reset
     */
    bool watchdogCausedReset();

private:

    double wdt_time;
    bool wdreset;
};


#endif // WATCHDOG_H

/*EOF*/
