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
 * GNU Genzeral Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AwesomeArduinoAlarmClock.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Copyright ï¿œ 2011-2012 Roland
 **/

#include "DCF77.h"
#include "Defines.h"
#include "Gui.h"

namespace AlarmClock
{

volatile unsigned char DCF77::DCFSignalState = 0;
volatile float64 DCF77::interuptMillis = 0;

/**
 * Interrupthandler for INT0 - called when the signal on Pin 2 changes.
 */
void DCF77int0handler() 
{
  // check the value again - since it takes some time to
  // activate the interrupt routine, we get a clear signal.
  DCF77::DCFSignalState = digitalRead(Defines::DCF77Pin);
  DCF77::interuptMillis = millis();
}

DCF77::DCF77()
{
  _timeIsValid = false;
  tick_counter = 0;
  DCFSignalState = 0; 
}

void DCF77::setup()
{
  previousSignalState=0;
  previousFlankTime=0;
  bufferPosition=0;
  dcf_rx_buffer=0;
  _time.second = 0;
  _time.minute = 0;
  _time.hour   = 0;
  _time.day    = 0;
  _time.month  = 0;
  _time.year   = 0;
  pinMode(Defines::DCF77Pin, INPUT);

  //Timer2 Settings: Timer Prescaler /64, 

  //TCCR2B |= (1<<CS22);    // turn on CS22 bit
  //TCCR2B &= ~((1<<CS21) | (1<<CS20));    // turn off CS21 and CS20 bits   

  // Use normal mode
  //TCCR2A &= ~((1<<WGM21) | (1<<WGM20));   // turn off WGM21 and WGM20 bits 
  //TCCR2B &= ~(1<<WGM22);                  // turn off WGM22

  // Use internal clock - external clock not used in Arduino
  //ASSR |= (0<<AS2);
  //TIMSK2 |= (1<<TOIE2) | (0<<OCIE2A);     //Timer2 Overflow Interrupt Enable  

  //RESET_TIMER2;
  attachInterrupt(4, DCF77int0handler, CHANGE);
}

/*void DCF77::loop() 
{
  //if (ss != previous_time.second) 
  //{
  //  serialDumpTime();
  //  previous_time.second = ss;
  //}
  if (DCFSignalState != previousSignalState) 
  {
    scanSignal();
    //if (DCFSignalState) 
    //{
    //  digitalWrite(BLINKPIN, HIGH);
    //} else {
    //  digitalWrite(BLINKPIN, LOW);
    //}
    previousSignalState = DCFSignalState;
  }
    //delay(20);
}*/
/*
void DCF77::loop() 
{
  if (ss != previousSecond) 
  {
    serialDumpTime();
    previousSecond = ss;
  }
  if (DCFSignalState != previousSignalState) 
  {
    scanSignal();
    if (DCFSignalState) 
    {
      digitalWrite(BLINKPIN, HIGH);
    } else {
      digitalWrite(BLINKPIN, LOW);
    }
    previousSignalState = DCFSignalState;
  }
    //delay(20);
}*/


void DCF77::loop(Gui* gui) 
{
  //Serial.print(millis(), DEC);
  //Serial.print(DCFSignalState, DEC);
  if (ss != previousSecond) 
  {
    serialDumpTime();
    previousSecond = ss;
  }
  if (DCFSignalState != previousSignalState) 
  {
    scanSignal();
    previousSignalState = DCFSignalState;
  }
    //delay(20);
    
  //gui->debug("bufferPosition ", (float64)(bufferPosition), 20);
  //gui->debug("millis         ", (float64)(millis()), 30);
  //gui->debug("interuptMillis ", (float64)(interuptMillis), 40);
  //gui->debug("read           ", (float64)(digitalRead(Defines::DCF77Pin)), 50);
  
}

/**
 * Append a signal to the dcf_rx_buffer. Argument can be 1 or 0. An internal
 * counter shifts the writing position within the buffer. If position > 59,
 * a new minute begins -> time to call finalizeBuffer().
 */
void DCF77::appendSignal(unsigned char signal) 
{
#ifdef DCF_DEBUG
  Serial.print(", appending value ");
  Serial.print(signal, DEC);
  Serial.print(" at position ");
  Serial.println(bufferPosition);
#endif
  //Serial.print(" at position ");
  //Serial.println(bufferPosition);

  dcf_rx_buffer = dcf_rx_buffer | ((unsigned long long) signal << bufferPosition);
  // Update the parity bits. First: Reset when minute, hour or date starts.
  if (bufferPosition ==  21 || bufferPosition ==  29 || bufferPosition ==  36) 
  {
	flags.parity_flag = 0;
  }
  // save the parity when the corresponding segment ends
  if (bufferPosition ==  28) {flags.parity_min  = flags.parity_flag;};
  if (bufferPosition ==  35) {flags.parity_hour = flags.parity_flag;};
  if (bufferPosition ==  58) {flags.parity_date = flags.parity_flag;};
  // When we received a 1, toggle the parity flag
  if (signal == 1) 
  {
    flags.parity_flag = flags.parity_flag ^ 1;
  }
  bufferPosition++;
  if (bufferPosition > 59) 
  {
    finalizeBuffer();
  }
}

/**
 * Evaluates the information stored in the buffer. This is where the DCF77
 * signal is decoded and the internal clock is updated.
 */
void DCF77::finalizeBuffer(void)
{
  if (bufferPosition == 59) 
  {
    //#ifdef DCF_DEBUG
    Serial.println("Finalizing Buffer");
    //#endif
    struct DCF77Buffer *rx_buffer;
    rx_buffer = (struct DCF77Buffer *)(unsigned long long)&dcf_rx_buffer;
    if (flags.parity_min == rx_buffer->P1  &&
        flags.parity_hour == rx_buffer->P2  &&
        flags.parity_date == rx_buffer->P3) 
    { 
    //#ifdef DCF_DEBUG
      Serial.println("Parity check OK - updating time.");
    //#endif
      //convert the received bits from BCD
      _time.minute = rx_buffer->Min-((rx_buffer->Min/16)*6);
      _time.hour = rx_buffer->Hour-((rx_buffer->Hour/16)*6);
      _time.day= rx_buffer->Day-((rx_buffer->Day/16)*6); 
      _time.month= rx_buffer->Month-((rx_buffer->Month/16)*6);
      _time.year= 2000 + rx_buffer->Year-((rx_buffer->Year/16)*6);
      _timeIsValid = true;
    }
    //#ifdef DCF_DEBUG
    else 
    {
        Serial.println("Parity check NOK - running on internal clock.");
    }
    //#endif
  } 
  // reset stuff
  _time.second = 0;
  bufferPosition = 0;
  dcf_rx_buffer=0;
}

/**
 * Dump the time to the serial line.
 */
void DCF77::serialDumpTime(void)
{
  Serial.print("Time: ");
  Serial.print(_time.hour, DEC);
  Serial.print(":");
  Serial.print(_time.minute, DEC);
  Serial.print(":");
  Serial.print(ss, DEC);
  Serial.print(" Date: ");
  Serial.print(_time.day, DEC);
  Serial.print(".");
  Serial.print(_time.month, DEC);
  Serial.print(".");
  Serial.println(_time.year, DEC);
  Serial.println(bufferPosition);
}


/**
 * Evaluates the signal as it is received. Decides whether we received
 * a "1" or a "0" based on the 
 */
void DCF77::scanSignal(void)
{ 
    if (DCFSignalState == 1) 
    {
      int thisFlankTime=millis();
      if (thisFlankTime - previousFlankTime > DCF_sync_millis) 
      {
        #ifdef DCF_DEBUG
                Serial.println("####");
                Serial.println("#### Begin of new Minute!!!");
                Serial.println("####");
        #endif
        finalizeBuffer();
      }
      previousFlankTime=thisFlankTime;
      #ifdef DCF_DEBUG
            Serial.print(previousFlankTime);
            Serial.print(": DCF77 Signal detected, ");
      #endif
    } 
    else 
    {
      /* or a falling flank */
      int difference=millis() - previousFlankTime;
      #ifdef DCF_DEBUG
            Serial.print("duration: ");
            Serial.print(difference);
      #endif
      if (difference < DCF_split_millis) 
      {
        Serial.print("0");
        appendSignal(0);
      } 
      else 
      {
        Serial.print("1");
        appendSignal(1);
      }
    }
}

Time DCF77::getTime()
{
  _timeIsValid = false;
  Time time(_time.year,_time.month,_time.day,_time.hour,_time.minute,_time.second);
  return time;
}

bool DCF77::timeIsValid()
{
  return _timeIsValid;
}

}// namespace AlarmClock


