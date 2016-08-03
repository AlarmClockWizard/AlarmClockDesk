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

#ifndef TIME_H
#define TIME_H

#include "Types.h"

namespace AlarmClock
{

class Time
{
  public:
    uint16 year;
    uint8 month;
    uint8 day;
    uint8 hour;
    uint8 minute;
    uint8 second;
   
    Time(uint16 currentYear = 0, uint8 currentMonth = 0, uint8 currentDay = 0,  uint8 currentHour  = 0, uint8 currentMinute= 0, uint8 currentSecond= 0);
    uint8 getDayOfWeek() const;
    bool operator== (const Time& otherTime) const;
    bool operator!= (const Time& otherTime) const;
};

}

#endif //TIME_H

