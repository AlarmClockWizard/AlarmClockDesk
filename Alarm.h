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

#ifndef ALARM_H
#define ALARM_H

//#include <Si4703_Breakout.h>
#include <Tone.h>
#include "Schedule.h"
#include "Beeper.h"

namespace AlarmClock
{

class Alarm
{
  private:
    bool _enabledRadio;
    bool _enabledBuzzer;
    bool _enabledLight;
    bool _enabledBeep;
    
    uint64 _ticksBegin;
    
    Beeper* _beeper;
    uint64  _beeperTicksAtNextInteraction;
    uint32  _beeperCurrentIndex;
    
    //Si4703_Breakout _radio;
    
    bool intervallActive();

    void beginRadio();
    void continueRadio();
    void endRadio();
    
    void beginBuzzer();
    void continueBuzzer();
    void endBuzzer();
    
    void beginLight();
    void continueLight();
    void endLight();
    
    void beginBeep();
    void continueBeep();
    void endBeep();
    
  public:
    Alarm(Beeper* beeper);
    void setup();
    void loop(Schedule* schedule, Time time, bool snozzeEnabled);
    bool isEnabled();
};

}

#endif //ALARM_H

