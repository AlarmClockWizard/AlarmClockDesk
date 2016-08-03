/**
 * This file is part of AwesomeArduinoAlarmClock.
 * 
 * AwesomeArduinoAlarmClock is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AwesomeArduinoAlarmClock is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AwesomeArduinoAlarmClock.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Copyright ï¿œ 2011-2012 Roland
 **/

#ifndef DCF77_H
#define DCF77_H

#include "Types.h"
#include "Time.h"
#include "Gui.h"

namespace AlarmClock
{

class DCF77
{
  private:
/**
Specifies a function to call when an external interrupt occurs. 
Replaces any previous function that was attached to the interrupt. 
Most Arduino boards have two external interrupts: numbers 0 (on digital pin 2) 
and 1 (on digital pin 3). The Arduino Mega has an additional four: numbers 2 (pin 21),
3 (pin 20), 4 (pin 19), and 5 (pin 18).
**/

/**
 * Where is the DCF receiver connected?
 */
//#define DCF77PIN 30
/**
 * Where is the LED connected?
 */
//#define BLINKPIN 31
/**
 * Turn debugging on or off
 */
//#define DCF_DEBUG 1

/**
 * Number of milliseconds to elapse before we assume a "1",
 * if we receive a falling flank before - its a 0.
 */
#define DCF_split_millis 140
/**
 * There is no signal in second 59 - detect the beginning of 
 * a new minute.
 */
#define DCF_sync_millis 1200
/**
 * Definitions for the timer interrupt 2 handler:
 * The Arduino runs at 16 Mhz, we use a prescaler of 64 -> We need to 
 * initialize the counter with 6. This way, we have 1000 interrupts per second.
 * We use tick_counter to count the interrupts.
 */
#define INIT_TIMER_COUNT 6
#define RESET_TIMER2 TCNT2 = INIT_TIMER_COUNT
int tick_counter;
/**
 * DCF time format struct
 */
struct DCF77Buffer 
{
  unsigned long long prefix	:21;
  unsigned long long Min	:7;	// minutes
  unsigned long long P1		:1;	// parity minutes
  unsigned long long Hour	:6;	// hours
  unsigned long long P2		:1;	// parity hours
  unsigned long long Day	:6;	// day
  unsigned long long Weekday	:3;	// day of week
  unsigned long long Month	:5;	// month
  unsigned long long Year	:8;	// year (5 -> 2005)
  unsigned long long P3		:1;	// parity
};

struct 
{
  unsigned char parity_flag	:1;
  unsigned char parity_min	:1;
  unsigned char parity_hour	:1;
  unsigned char parity_date	:1;
} flags;

/**
 * Clock variables 
 */
unsigned char previousSignalState;
int previousFlankTime;
int bufferPosition;
unsigned long long dcf_rx_buffer;

/**
 * time vars: the time is stored here!
 */
//volatile unsigned char ss;
//volatile unsigned char mm;
//volatile unsigned char hh;
//volatile unsigned char day;
//volatile unsigned char mon;
//volatile unsigned int year;
volatile Time _time;

bool _timeIsValid;


/**
 * used in main loop: detect a new second...
 */
unsigned char previousSecond;
unsigned char ss;

  void DCF77Init(); 
  void appendSignal(unsigned char signal);
  void finalizeBuffer(void);
  void serialDumpTime(void);
  void scanSignal(void);
  

  
  public:
    DCF77();
    void setup();
    void loop(Gui* gui);
    Time getTime();
    bool timeIsValid();
    uint8 getBufferPosition()
    { return bufferPosition; }
    
    static volatile unsigned char DCFSignalState;
    static volatile float64 interuptMillis;
};

}//namespace AlarmClock

#endif //DCF77_H

