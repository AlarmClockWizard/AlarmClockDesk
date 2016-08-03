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

#ifndef DEFINES_H
#define DEFINES_H

#include "Types.h"

namespace AlarmClock
{
  namespace Defines
  {
    //GUI
    #define RGB(r,g,b)   (((r&0xF8)<<8)|((g&0xFC)<<3)|((b&0xF8)>>3)) //5 red | 6 green | 5 blue
    static const uint16 color1 = RGB(255, 172,  64);//FFAC40 dark white
    static const uint16 color2 = RGB(255, 194, 115);//FFC273 bright white
    static const uint16 color3 = RGB(255, 144,   0);//FF9000 yellow
    static const uint16 color4 = RGB(191, 129,  48);//BF8130 gray brown
    static const uint16 color5 = RGB(166,  94,   0);//A65E00 dark brown
    
    static const uint16 guiBGColor                = color4;
    static const uint16 guiLineColor              = color1; 
    static const uint16 guiTextColor              = color2; 
    static const uint16 guiClockTextColor         = color2;
    static const uint16 guiClockBGColor           = guiBGColor;
    static const uint16 guiButtonTextColor        = color1;
    static const uint16 guiButtonBGColor          = color5;
    static const uint16 guiButtonActiveTextColor  = guiButtonBGColor;
    static const uint16 guiButtonActiveBGColor    = guiBGColor;
    static const uint16 guiButtonPressedTextColor = color5;
    static const uint16 guiButtonPressedBGColor   = color3;
  
    static const uint16 touchEepromAddress = (0x00); //eeprom address for calibration data     
    
    static const uint32 buttonCooldownTicks = 150;
    static const uint32 spinBoxCooldownTicks = 100;
    static const uint32 dispatcherPageChangeCooldownTicks = 60000; //5 * 60 * 1000;
    
    static const int8  invalidPageIndex = 8;    
        
    static const uint8 backlightOff = 0;
    static const uint8 backlightLow = 10;
    static const uint8 backlightNormal = 70;
    static const uint32 backlightThresholdOff = 8;
    static const uint32 backlightThresholdLow = 600;
    static const uint32 backlightWaitTicks = 2000;
    static const uint32 backlightWaitTicksQuick = 20;
    static const float64 backlightTickIntervall = 2000;
    static const float64 backlightStepCount = 20;
    
    static const uint32 snozzeTicksDifferenceForSnozze = 1000;
    static const uint32 snozzeTicksDifferenceForSnozzeStopAlarm = 5 * 1000;
    static const uint64 snozzeSnozzeTicks    = (uint64)( 5) * (uint64)(60) * (uint64)(1000);
    static const uint64 snozzeStopAlarmTicks = (uint64)(60) * (uint64)(60) * (uint64)(1000); //one hour exceds the maximum alarm time
    
    static const uint64 alarmTickIntervall = 100;//1000;
    static const uint64 alarmRadioChannel = 876;
    
    static const int32 photoResistorPin = 0; //analog
    static const int32 distanceSenstorPin = 28; //digital
    static const int32 DCF77Pin = 19; //digital
    static const int32 snozze0Pin = 46; //digital
    static const int32 snozze1Pin = 48; //digital
    static const int32 snozze2Pin = 42; //digital
    static const int32 snozze3Pin = 44; //digital 
    static const int32 beepPin = 10; //pwm speaker
    static const int32 lightPin = 40; //digital
    static const int32 buzzerPin = 38; //digital
    static const int32 radioResetPin = 30; //digital
    static const int32 i2cInputOutputPin = 20; //digital
    static const int32 i2cClockPin = 21; //digital
  }
}

#endif //SCHEDULE_H

