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

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "Schedule.h"
#include "Gui.h"
//#include <mmc.h>
#include <ff.h>
#include <integer.h>
#include <diskio.h>
#include <SDcard.h>
#include <ffconf.h>

//#include <MsTimer2.h>

namespace AlarmClock
{

class FileSystem
{
  private:
    AlarmClock::Gui* _gui;
    String _errorString;
    void error(String string);
    void error(String string, FRESULT resultCode);
    String getScheduleFileName(uint8 dayIndex);
    
  public:
    //static SDcard _sd;
    //SD _sd    
    //void ISR(TIMER2_OVF_vect);
 
  public:
    FileSystem(AlarmClock::Gui* gui);
    void setup();
    void loop();
    Schedule loadSchedule(uint8 dayIndex);
    void saveSchedule(uint8 dayIndex, Schedule schedule);
};

}

#endif //FILE_SYSTEM_H

