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

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "Alarm.h"
#include "Beeper.h"
#include "Clock.h"
#include "FileSystem.h"
#include "Gui.h"
#include "RadioSettings.h"
#include "Schedule.h"

namespace AlarmClock
{  
  class Dispatcher
  {
    private:
      Schedule _schedules[7];
      RadioSettings _radioSettings;
      Time  _currentTime;
      uint8 _currentPageIndex;
      Clock _clock;
      Gui   _gui;
      FileSystem _fileSystem;
      Beeper _beeper;
      Alarm _alarm;
      
      uint32 _lastPagePressedTicks;
      uint64 _lastSnozzeTicks;
      uint64 _snozzeTicksLeft;
      uint32 _snozzeButtonPressBeginSnozzeTicks;
      uint32 _snozzeButtonPressBeginStopAlarmTicks;
      
      uint32 _backlightOffBegin;
      uint32 _backlightOffCurrent;
      uint32 _backlightLowBegin;
      uint32 _backlightLowCurrent;
      uint32 _backlightNormalBegin;
      uint32 _backlightNormalCurrent;
      uint32 _backlightQuickBegin;
      uint32 _backlightQuickCurrent;
      uint8  _backlightOldValue;
      uint8  _backlightCurrentValue;
      uint8  _backlightTargetValue;
      uint32 _backlightDimmCounter;
      float64 _backlightDimmIncrementTicksBegin;  
      
      uint8 getDisplayPageIndex(Time currentTime);
      uint8 getCountOfSnozzeButtonPressed();
      bool updateSnozze();       
      void updatedBacklight();      
    
    public:
      Dispatcher();
      void setup();
      void loop();
  };
}

#endif //DISPATCHER_H

