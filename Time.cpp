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

#include "Time.h"

namespace AlarmClock
{  
    Time::Time
    ( 
      uint16 currentYear,
      uint8 currentMonth,
      uint8 currentDay,
      uint8 currentHour,
      uint8 currentMinute,
      uint8 currentSecond
    )
    {        
      year   = currentYear;
      month  = currentMonth;
      day    = currentDay;
      hour   = currentHour;
      minute = currentMinute;
      second = currentSecond;      
    }   

    /**
     *  Sunday = 0;
     *  Monday;
     *  Tuesday;
     *  Wednesday;
     *  Thursday;
     *  Friday;
     *  Saturday;
     **/
    uint8 Time::getDayOfWeek() const
    {
      int y = year;
      int m = month;
      int d = day;
      
      /* 0 = Sunday / int y, m, d; / 1 <= m <= 12, y > 1752 or so */
      static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}; 
      y -= m < 3; 
      int dayOfWeek = (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
      return (dayOfWeek + 6) % 7;
    }
    
    bool Time::operator== (const Time& otherTime) const
    {
      if( year == otherTime.year )
      { 
        if( month == otherTime.month )
        {
          if( day == otherTime.day )
          {
            if( hour == otherTime.hour )
            {
              if( minute == otherTime.minute )
              {
                if( second == otherTime.second )
                {
                  return true;
                }
              }
            }
          }
        }
      }
      
      return false;
    }
    
    bool Time::operator!= (const Time& otherTime) const
    {
      if( this->operator==(otherTime) )
      {
        return false;
      }
      
      return true;
    }
}


