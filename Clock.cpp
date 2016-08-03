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

#include "Clock.h"

namespace AlarmClock
{

Clock::Clock()
{
}
 
void Clock::setup()
{  
  //_rtc.set(0, 0, 0, 1, 1, 1970);
  //_rtc.set(00, 28, 22, 14, 12, 2011);
  _dcf77.setup();
  _rtc.start();
}
 
  
void Clock::loop()
{
  _dcf77.loop(_gui);
 
  if( _dcf77.timeIsValid() )
  {
    Time currentTime = _dcf77.getTime();
    _rtc.set(currentTime.second, currentTime.minute, currentTime.hour, currentTime.month, currentTime.day, currentTime.year);
  }
}


Time Clock::getTime()
{ 
  Time currentTime;
  _rtc.get
  (
    &(currentTime.second), 
    &(currentTime.minute), 
    &(currentTime.hour), 
    &(currentTime.day), 
    &(currentTime.month), 
    &(currentTime.year)
  );
  
  return currentTime;
}

}

