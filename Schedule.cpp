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
 * Copyright © 2011-2012 Roland
 **/

#include "Schedule.h"
#include <SD.h>
namespace AlarmClock
{
  
Schedule::Schedule()
{
  dayIndex        = 8;
  alarmTime       = Time();
  activateRadio   = false;
  activateBuzzer  = false;
  activateLight   = false;
  activateBeep    = false;
  radioDelayBegin = 0;
  radioDelayEnd   = 59; //0;
  buzzerDelayBegin= 0;
  buzzerDelayEnd  = 59; //0;
  lightDelayBegin = 0;
  lightDelayEnd   = 59; //0;
  beepDelayBegin  = 0;
  beepDelayEnd    = 59; //0;      
}

bool Schedule::timeCorrect(Time currentTime, Time scheduleTime, uint8 delayBegin, uint8 delayEnd)
{
  uint64 currentTicks = 
  (currentTime.hour   * 60 * 60) + 
  (currentTime.minute * 60 ) + 
  (currentTime.second);
  
  uint64 scheduleTicks = 
  (scheduleTime.hour   * 60 * 60) + 
  (scheduleTime.minute * 60 ) + 
  (scheduleTime.second);
  
  uint64 scheduleTicksBegin = scheduleTicks + delayBegin * 60;
  uint64 scheduleTicksEnd   = scheduleTicks + delayEnd   * 60;
  
  if(currentTicks >= scheduleTicksBegin && currentTicks <= scheduleTicksEnd)
  {
    return true;
  }
 
  return false;
}


bool Schedule::alarmRadio(Time currentTime)
{
   if(activateRadio && timeCorrect(currentTime, alarmTime, radioDelayBegin, radioDelayEnd))
   {
     return true;
   }
   return false;  
}
    
bool Schedule::alarmBuzzer(Time currentTime)
{
   if(activateBuzzer && timeCorrect(currentTime, alarmTime, buzzerDelayBegin, buzzerDelayEnd))
   {
     return true;
   }
   return false;  
}
   
bool Schedule::alarmLight(Time currentTime)
{
   if(activateLight && timeCorrect(currentTime, alarmTime, lightDelayBegin, lightDelayEnd))
   {
     return true;
   }
   return false;    
}
   
bool Schedule::alarmBeep(Time currentTime)
{
   if(activateBeep && timeCorrect(currentTime, alarmTime, beepDelayBegin, beepDelayEnd))
   {
     return true;
   }
   return false;   
}
   


} //namespace AlarmClock


