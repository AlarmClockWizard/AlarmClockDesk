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

#include "Beeper.h"
#include "Defines.h"

namespace AlarmClock
{
  
void Beeper::setup()
{
  _tone.begin(Defines::beepPin);  
}
   
void Beeper::play(uint16 frequency, uint32 duration)
{
  _tone.play(frequency, duration);
}

void Beeper::stop()
{
  _tone.stop();
}

} //namespace AlarmClock


