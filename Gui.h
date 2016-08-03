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

#ifndef GUI_H
#define GUI_H

#include <MI0283QT2.h>
#include <ADS7846.h>
#include "Button.h"
#include "Label.h"
#include "RadioSettings.h"
#include "Schedule.h"
#include "SpinBox.h"

namespace AlarmClock
{
  class Gui
  {
    private:
      MI0283QT2 _lcd; 
      ADS7846 _touch;
      
      Button _tabButtons[8];
      Time _lastDrawnTime;

      //schedule
      Button _toggleButtonRadio;    
      Button _toggleButtonBuzzer;              
      Button _toggleButtonLight;    
      Button _toggleButtonBeep;
      
      SpinBox _spinBoxRadioBegin;
      SpinBox _spinBoxRadioEnd;
      SpinBox _spinBoxBuzzerBegin;
      SpinBox _spinBoxBuzzerEnd;
      SpinBox _spinBoxLightBegin;
      SpinBox _spinBoxLightEnd;
      SpinBox _spinBoxBeepBegin;
      SpinBox _spinBoxBeepEnd;      

      SpinBox _spinBoxHour;  
      SpinBox _spinBoxMinute;  
           
      Button _buttonSave;    
      Button _buttonLoad;
      Button _toggleButtonConfig;
      
      Label _labelForSpinBoxRadio;
      Label _labelForSpinBoxBuzzer;
      Label _labelForSpinBoxLight;
      Label _labelForSpinBoxBeep;
      Label _labelForSpinBoxTime;
      
      //radio
      Label _radioAlarm;
      Label _radioEntertainment;
      Button _radioButtonSave;    
      Button _radioButtonLoad;
      Button _radioToggleButtonConfig;
      Button _radioToggleButtonEntertainment; 
      //Button _radioLabelButtonEntertainment;
      Button _radioButtonFiveMinutes; 
      Button _radioButtonOneHour;            
      SpinBox _radioSpinBoxChannel0;
      SpinBox _radioSpinBoxChannel1;
      SpinBox _radioSpinBoxChannel2; 
      Button _radioButtonChannel0Alarm; 
      Button _radioButtonChannel1Alarm;
      Button _radioButtonChannel2Alarm; 
      Button _radioButtonChannel0Entertainment; 
      Button _radioButtonChannel1Entertainment;
      Button _radioButtonChannel2Entertainment;
      
      uint32 headerToColor(char* data);
      void updateSnozze(uint64 snozzeTicksLeft);  
      void hideSnozzeLabel();
   
   public:
      Gui();
      void setup();
      uint32 getPressure();
      uint8 whichPageIsSelected(); 
      bool saveButtonIsPressed();       
      bool loadButtonIsPressed();
      bool configButtonIsActive();
      void debug(float64 number, uint8 rowOffset = 0);  
      void debug(String text, uint8 rowOffset = 0);
      void debug(String text, float64 number, uint8 rowOffset = 0);
      void setBacklight(uint8 percent);
      void showRadioPage();
      void showSchedulePage();
      
      void handleTabButtons(uint8 activeTabIndex, const Time& currentTime);
      void handleScheduleGui(Schedule* schedule, uint64 snozzeTicksLeft);
      void handleRadioGui(RadioSettings* radioSettings);
      void drawClock(const Time& time); 
  };
}

#endif //GUI_H

