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

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Types.h"
#include "Time.h"

namespace AlarmClock
{

class Schedule
{
  private:
    bool timeCorrect(Time currentTime, Time scheduleTime, uint8 delayBegin, uint8 delayEnd);
  
  public:
    uint8 dayIndex;
    Time alarmTime;
    bool activateRadio;
    bool activateBuzzer;
    bool activateLight;
    bool activateBeep;
    uint8 radioDelayBegin;
    uint8 radioDelayEnd;
    uint8 buzzerDelayBegin;
    uint8 buzzerDelayEnd;
    uint8 lightDelayBegin;
    uint8 lightDelayEnd;
    uint8 beepDelayBegin;
    uint8 beepDelayEnd;
    
    bool alarmRadio(Time currentTime);
    bool alarmBuzzer(Time currentTime);
    bool alarmLight(Time currentTime);
    bool alarmBeep(Time currentTime);
    Schedule();
};

}

#endif //SCHEDULE_H

