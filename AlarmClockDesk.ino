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
//#include <Si4703_Breakout.h>
#include <Tone.h>
#include <SD.h>
#include <ADS7846.h>
#include <Wire.h>
#include <BMPheader.h> //LCD
#include <MI0283QT2.h>
//#include <mmc.h> //MicroSD
#include <ff.h>
#include <integer.h>
#include <diskio.h>
#include <SDcard.h>
#include <ffconf.h>
#include <DS1307.h> //Real Time CLock

#include "Dispatcher.h"
AlarmClock::Dispatcher dispatcher;

/**
 * Standard Arduino methods below.
 */
void setup(void) 
{
  Serial.begin(9600);
  dispatcher.setup();
}

void loop(void) 
{
  dispatcher.loop();
}


