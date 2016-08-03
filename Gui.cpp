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

#include "Gui.h"
#include "Defines.h"

namespace AlarmClock
{
  Gui::Gui()
  {
  }

  void Gui::setup()
  {
    _lcd.init(4); //spi-clk = Fcpu/4
    //_lcd.setOrientation(0);//_lcd.setOrientation(180);

    _touch.init();
    //_touch.setOrientation(180);//_touch.setOrientation(0);
    _touch.service();
    if(_touch.getPressure() > 5)
    {
      _touch.doCalibration(&_lcd, Defines::touchEepromAddress, 0); //dont check EEPROM for calibration data
    }
    else
    {
      _touch.doCalibration(&_lcd, Defines::touchEepromAddress, 1); //check EEPROM for calibration data
    }  
  
    //radio
    _radioAlarm                      .setup("alarm" , 1, &_lcd, 231, 35, Defines::guiClockTextColor, Defines::guiClockBGColor);
    _radioEntertainment              .setup("radio" , 1, &_lcd, 275, 35, Defines::guiClockTextColor, Defines::guiClockBGColor);
    _radioButtonSave                 .setup("Save"  , &_lcd,&_touch, 67,125, 50,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor , Defines::guiButtonActiveBGColor , Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
    _radioButtonLoad                 .setup("Reset" , &_lcd,&_touch,119,125, 50,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor , Defines::guiButtonActiveBGColor , Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
    _radioToggleButtonConfig         .setup("Config", &_lcd,&_touch,  5,125, 60,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);    
    _radioButtonFiveMinutes          .setup("+ 5"   , &_lcd,&_touch, 67, 40, 50,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);  
    _radioButtonOneHour              .setup("+ 60"  , &_lcd,&_touch,119, 40, 50,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);  
    _radioToggleButtonEntertainment  .setup("Radio" , &_lcd,&_touch,  5, 40, 60,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);  
    _radioLabelButtonEntertainment   .setup(""      , &_lcd,&_touch,  5, 75,164,45,Defines::guiBGColor        , Defines::guiBGColor      , Defines::guiBGColor               , Defines::guiBGColor             , Defines::guiBGColor               , Defines::guiBGColor             ,7,10);  
    _radioSpinBoxChannel0            .setup(0,999,2 , &_lcd,&_touch,190, 45,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);
    _radioSpinBoxChannel1            .setup(0,999,2 , &_lcd,&_touch,190,110,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);
    _radioSpinBoxChannel2            .setup(0,999,2 , &_lcd,&_touch,190,175,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);  
    _radioButtonChannel0Alarm        .setup(""      , &_lcd,&_touch,240, 60,30,30,Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonPressedBGColor,7,10); 
    _radioButtonChannel1Alarm        .setup(""      , &_lcd,&_touch,240,125,30,30,Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonPressedBGColor,7,10); 
    _radioButtonChannel2Alarm        .setup(""      , &_lcd,&_touch,240,190,30,30,Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonPressedBGColor,7,10);  
    _radioButtonChannel0Entertainment.setup(""      , &_lcd,&_touch,275, 60,30,30,Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonPressedBGColor,7,10);  
    _radioButtonChannel1Entertainment.setup(""      , &_lcd,&_touch,275,125,30,30,Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonPressedBGColor,7,10); 
    _radioButtonChannel2Entertainment.setup(""      , &_lcd,&_touch,275,190,30,30,Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonBGColor, Defines::guiBGColor, Defines::guiButtonPressedBGColor,7,10);     
  
    //schedule
    _tabButtons[0].setup("Mo"   , &_lcd,&_touch,  1,0,36,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
    _tabButtons[1].setup("Di"   , &_lcd,&_touch, 39,0,36,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
    _tabButtons[2].setup("Mi"   , &_lcd,&_touch, 77,0,36,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
    _tabButtons[3].setup("Do"   , &_lcd,&_touch,115,0,36,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
    _tabButtons[4].setup("Fr"   , &_lcd,&_touch,153,0,36,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
    _tabButtons[5].setup("Sa"   , &_lcd,&_touch,191,0,36,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
    _tabButtons[6].setup("So"   , &_lcd,&_touch,229,0,36,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
    _tabButtons[7].setup("Radio", &_lcd,&_touch,267,0,52,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
        
    _toggleButtonRadio .setup("Radio" , &_lcd,&_touch,175, 45,50,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);    
    _toggleButtonBuzzer.setup("Brumm" , &_lcd,&_touch,175, 95,50,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);                  
    _toggleButtonLight .setup("Licht" , &_lcd,&_touch,175,145,50,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);        
    _toggleButtonBeep  .setup("Piep"  , &_lcd,&_touch,175,195,50,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);    
     
    _spinBoxRadioBegin .setup(0, 59, 1, &_lcd,&_touch, 231, 35,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);  
    _spinBoxRadioEnd   .setup(0, 59, 1, &_lcd,&_touch, 275, 35,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);  
    _spinBoxBuzzerBegin.setup(0, 59, 1, &_lcd,&_touch, 231, 85,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);  
    _spinBoxBuzzerEnd  .setup(0, 59, 1, &_lcd,&_touch, 275, 85,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);  
    _spinBoxLightBegin .setup(0, 59, 1, &_lcd,&_touch, 231,135,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);  
    _spinBoxLightEnd   .setup(0, 59, 1, &_lcd,&_touch, 275,135,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);  
    _spinBoxBeepBegin  .setup(0, 59, 1, &_lcd,&_touch, 231,185,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);  
    _spinBoxBeepEnd    .setup(0, 59, 1, &_lcd,&_touch, 275,185,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);  
   
    _spinBoxHour  .setup(0, 23, 2, &_lcd,&_touch, 50,50,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);
    _spinBoxMinute.setup(0, 59, 2, &_lcd,&_touch, 95,50,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiClockTextColor, Defines::guiClockBGColor);

    _buttonSave        .setup("Save"  , &_lcd,&_touch, 67,125,50,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
    _buttonLoad        .setup("Reset" , &_lcd,&_touch,119,125,50,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonActiveTextColor, Defines::guiButtonActiveBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);
    _toggleButtonConfig.setup("Config", &_lcd,&_touch,  5,125,60,30,Defines::guiButtonTextColor, Defines::guiButtonBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor, Defines::guiButtonPressedTextColor, Defines::guiButtonPressedBGColor,7,10);    
    _toggleButtonConfig.setActive();//############# to enable the buttons for simple testing
    
    _labelForSpinBoxRadio .setup("-", 1, &_lcd, 264, 53, Defines::guiClockTextColor, Defines::guiClockBGColor);
    _labelForSpinBoxBuzzer.setup("-", 1, &_lcd, 264,103, Defines::guiClockTextColor, Defines::guiClockBGColor);
    _labelForSpinBoxLight .setup("-", 1, &_lcd, 264,153, Defines::guiClockTextColor, Defines::guiClockBGColor);
    _labelForSpinBoxBeep  .setup("-", 1, &_lcd, 264,203, Defines::guiClockTextColor, Defines::guiClockBGColor);
    _labelForSpinBoxTime  .setup(":", 2, &_lcd,  82, 69, Defines::guiClockTextColor, Defines::guiClockBGColor);
  
    _lcd.clear(Defines::guiBGColor);
  }
  
  uint32 Gui::getPressure()
  {
    return _touch.getPressure();
  }    

  void Gui::drawClock(const Time& time)
  {
    if(time != _lastDrawnTime)
    {
      _lastDrawnTime = time;
    
      uint16 year   = time.year;
      uint8  month  = time.month;
      uint8  day    = time.day;
      uint8  hour   = time.hour;
      uint8  minute = time.minute;
      uint8  second = time.second;

      String yearAsString  (year);
      String monthAsString (month);
      String dayAsString   (day);
      String hourAsString  (hour);
      String minuteAsString(minute);
      String secondAsString(second);  

      String timeAsString;
      timeAsString += yearAsString;
      timeAsString += "-";
      timeAsString += monthAsString;
      timeAsString += "-";
      timeAsString += dayAsString;
      timeAsString += " ";
      timeAsString += hourAsString;
      timeAsString += ":";
      timeAsString += minuteAsString;
      timeAsString += ":";
      timeAsString += secondAsString;

      char buffer[16];

      //display output
      sprintf(buffer, "%04i-%02i-%02i", year, month, day );
      _lcd.drawText(10, 170, buffer, 2, Defines::guiClockTextColor, Defines::guiClockBGColor);

      sprintf(buffer, "%02i:%02i", hour, minute);
      _lcd.drawText(10, 200, buffer, 3, Defines::guiClockTextColor, Defines::guiClockBGColor);
      
      sprintf(buffer, ":%02i", second);
      _lcd.drawText(130, 220, buffer, 1, Defines::guiClockTextColor, Defines::guiClockBGColor);
    }
  }
  
  uint8 Gui::whichPageIsSelected()
  {
    _touch.service();

    uint8 activePageIndex = Defines::invalidPageIndex;
    for(uint8 currentPageIndex = 0; currentPageIndex < Defines::invalidPageIndex; currentPageIndex++)
    {
      if( _tabButtons[currentPageIndex].isPressed() ) 
      {
        activePageIndex = currentPageIndex;
      }
    }
    
    return activePageIndex;    
  }
  
  bool Gui::saveButtonIsPressed()
  {
    return _buttonSave.isPressed();
  }
  
  bool Gui::loadButtonIsPressed()
  {
    return _buttonLoad.isPressed();
  }
  
  bool Gui::configButtonIsActive()
  {
    return _toggleButtonConfig.isActive();
  }
  
  uint32 Gui::headerToColor(char* data) 
  {
    uint32 colorArray[3];
    colorArray[0] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4)); 
    colorArray[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2)); 
    colorArray[2] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33))); 
    //data += 4; 
    
    uint32 color = RGB(colorArray[0],colorArray[1],colorArray[2]);
    return color;
  }
  
  void Gui::showSchedulePage()
  {
    _radioAlarm.setHidden(); 
    _radioEntertainment.setHidden(); 
    _radioButtonSave.setHidden();     
    _radioButtonLoad.setHidden(); 
    _radioToggleButtonConfig.setHidden(); 
    _radioToggleButtonEntertainment.setHidden();
    _radioLabelButtonEntertainment.setHidden();
    _radioButtonFiveMinutes.setHidden(); 
    _radioButtonOneHour.setHidden();            
    _radioSpinBoxChannel0.setHidden(); 
    _radioSpinBoxChannel1.setHidden(); 
    _radioSpinBoxChannel2.setHidden();
    _radioButtonChannel0Alarm.setHidden();  
    _radioButtonChannel1Alarm.setHidden(); 
    _radioButtonChannel2Alarm.setHidden();  
    _radioButtonChannel0Entertainment.setHidden();  
    _radioButtonChannel1Entertainment.setHidden(); 
    _radioButtonChannel2Entertainment.setHidden();       
    
    _toggleButtonRadio.unsetHidden();
    _toggleButtonBuzzer.unsetHidden();              
    _toggleButtonLight.unsetHidden();
    _toggleButtonBeep.unsetHidden();       
    _spinBoxRadioBegin.unsetHidden();
    _spinBoxRadioEnd.unsetHidden();
    _spinBoxBuzzerBegin.unsetHidden();
    _spinBoxBuzzerEnd.unsetHidden();
    _spinBoxLightBegin.unsetHidden();
    _spinBoxLightEnd.unsetHidden();
    _spinBoxBeepBegin.unsetHidden();
    _spinBoxBeepEnd.unsetHidden();     
    _spinBoxHour.unsetHidden();
    _spinBoxMinute.unsetHidden();   
    _buttonSave.unsetHidden();        
    _buttonLoad.unsetHidden();        
    _toggleButtonConfig.unsetHidden();      
    _labelForSpinBoxRadio.unsetHidden();
    _labelForSpinBoxBuzzer.unsetHidden();
    _labelForSpinBoxLight.unsetHidden();
    _labelForSpinBoxBeep.unsetHidden();
    _labelForSpinBoxTime.unsetHidden();    
  } 
  
  void Gui::showRadioPage()
  {
    _toggleButtonRadio.setHidden();
    _toggleButtonBuzzer.setHidden();              
    _toggleButtonLight.setHidden();
    _toggleButtonBeep.setHidden();       
    _spinBoxRadioBegin.setHidden();
    _spinBoxRadioEnd.setHidden();
    _spinBoxBuzzerBegin.setHidden();
    _spinBoxBuzzerEnd.setHidden();
    _spinBoxLightBegin.setHidden();
    _spinBoxLightEnd.setHidden();
    _spinBoxBeepBegin.setHidden();
    _spinBoxBeepEnd.setHidden();     
    _spinBoxHour.setHidden();
    _spinBoxMinute.setHidden();   
    _buttonSave.setHidden();        
    _buttonLoad.setHidden();        
    _toggleButtonConfig.setHidden();       
    _labelForSpinBoxRadio.setHidden();
    _labelForSpinBoxBuzzer.setHidden();
    _labelForSpinBoxLight.setHidden();
    _labelForSpinBoxBeep.setHidden();
    _labelForSpinBoxTime.setHidden();     
    hideSnozzeLabel();    
    
    _radioAlarm.unsetHidden(); 
    _radioEntertainment.unsetHidden(); 
    _radioButtonSave.unsetHidden();     
    _radioButtonLoad.unsetHidden(); 
    _radioToggleButtonConfig.unsetHidden(); 
    _radioToggleButtonEntertainment.unsetHidden();  
    _radioLabelButtonEntertainment.unsetHidden();
    _radioButtonFiveMinutes.unsetHidden(); 
    _radioButtonOneHour.unsetHidden();            
    _radioSpinBoxChannel0.unsetHidden(); 
    _radioSpinBoxChannel1.unsetHidden(); 
    _radioSpinBoxChannel2.unsetHidden();
    _radioButtonChannel0Alarm.unsetHidden();  
    _radioButtonChannel1Alarm.unsetHidden(); 
    _radioButtonChannel2Alarm.unsetHidden();  
    _radioButtonChannel0Entertainment.unsetHidden();  
    _radioButtonChannel1Entertainment.unsetHidden(); 
    _radioButtonChannel2Entertainment.unsetHidden();     
  } 

  void Gui::handleTabButtons(uint8 activeTabIndex, const Time& currentTime)
  {
    //update day buttons
    for(uint8 currentPageIndex = 0; currentPageIndex < Defines::invalidPageIndex; currentPageIndex++)
    {
      if( currentPageIndex == activeTabIndex)
      {
        _tabButtons[currentPageIndex].setActive();
      }
      else
      {
        _tabButtons[currentPageIndex].unsetActive();
      }     
      
      if( currentPageIndex == currentTime.getDayOfWeek())
      {
        _tabButtons[currentPageIndex].setHighlightUnderscore();
      }
      else
      {
        _tabButtons[currentPageIndex].unsetHighlightUnderscore();
      }    
      _tabButtons[currentPageIndex].draw();
    }
  }
  
  void Gui::handleScheduleGui(Schedule* schedule, uint64 snozzeTicksLeft)
  {
    updateSnozze(snozzeTicksLeft);
    
    //only enable the buttons if the config buton is pressed
    if(configButtonIsActive())
    {  
      _spinBoxHour.setEnabled();
      _spinBoxMinute.setEnabled();
      _buttonSave.setEnabled();
      _buttonLoad.setEnabled();
      _toggleButtonRadio.setEnabled();
      _toggleButtonBuzzer.setEnabled();
      _toggleButtonLight.setEnabled();
      _toggleButtonBeep.setEnabled();
      _spinBoxRadioBegin.setEnabled();
      _spinBoxRadioEnd.setEnabled();
      _spinBoxBuzzerBegin.setEnabled();
      _spinBoxBuzzerEnd.setEnabled();
      _spinBoxLightBegin.setEnabled();
      _spinBoxLightEnd.setEnabled();
      _spinBoxBeepBegin.setEnabled();
      _spinBoxBeepEnd.setEnabled();
    }
    else
    {
      _spinBoxHour.unsetEnabled();
      _spinBoxMinute.unsetEnabled();
      _buttonSave.unsetEnabled();
      _buttonLoad.unsetEnabled();
      _toggleButtonRadio.unsetEnabled();
      _toggleButtonBuzzer.unsetEnabled();
      _toggleButtonLight.unsetEnabled();
      _toggleButtonBeep.unsetEnabled();
      _spinBoxRadioBegin.unsetEnabled();
      _spinBoxRadioEnd.unsetEnabled();
      _spinBoxBuzzerBegin.unsetEnabled();
      _spinBoxBuzzerEnd.unsetEnabled();
      _spinBoxLightBegin.unsetEnabled();
      _spinBoxLightEnd.unsetEnabled();
      _spinBoxBeepBegin.unsetEnabled();
      _spinBoxBeepEnd.unsetEnabled();
    }
    
    if(schedule != NULL)
    {
      //update alarm emitter buttons
      if(schedule->activateRadio ){_toggleButtonRadio .setActive();}else{_toggleButtonRadio .unsetActive();}
      if(schedule->activateBuzzer){_toggleButtonBuzzer.setActive();}else{_toggleButtonBuzzer.unsetActive();}
      if(schedule->activateLight ){_toggleButtonLight .setActive();}else{_toggleButtonLight .unsetActive();}
      if(schedule->activateBeep  ){_toggleButtonBeep  .setActive();}else{_toggleButtonBeep  .unsetActive();}
         
      _toggleButtonRadio .drawToogle();    
      _toggleButtonBuzzer.drawToogle();              
      _toggleButtonLight .drawToogle();    
      _toggleButtonBeep  .drawToogle();
      
      schedule->activateRadio = _toggleButtonRadio .isActive();
      schedule->activateBuzzer= _toggleButtonBuzzer.isActive();
      schedule->activateLight = _toggleButtonLight .isActive();
      schedule->activateBeep  = _toggleButtonBeep  .isActive();
        
      //update alarn emitter timers
      schedule->radioDelayBegin  = _spinBoxRadioBegin .draw(schedule->radioDelayBegin );
      schedule->radioDelayEnd    = _spinBoxRadioEnd   .draw(schedule->radioDelayEnd   );
      schedule->buzzerDelayBegin = _spinBoxBuzzerBegin.draw(schedule->buzzerDelayBegin);
      schedule->buzzerDelayEnd   = _spinBoxBuzzerEnd  .draw(schedule->buzzerDelayEnd  );
      schedule->lightDelayBegin  = _spinBoxLightBegin .draw(schedule->lightDelayBegin );
      schedule->lightDelayEnd    = _spinBoxLightEnd   .draw(schedule->lightDelayEnd   );
      schedule->beepDelayBegin   = _spinBoxBeepBegin  .draw(schedule->beepDelayBegin  );
      schedule->beepDelayEnd     = _spinBoxBeepEnd    .draw(schedule->beepDelayEnd    ); 
      
      //Get shure the end time is not smaler than the begin
      if(schedule->radioDelayEnd  < schedule->radioDelayBegin ){ schedule->radioDelayEnd  = schedule->radioDelayBegin; }
      if(schedule->buzzerDelayEnd < schedule->buzzerDelayBegin){ schedule->buzzerDelayEnd = schedule->buzzerDelayBegin;}
      if(schedule->lightDelayEnd  < schedule->lightDelayBegin ){ schedule->lightDelayEnd  = schedule->lightDelayBegin; }
      if(schedule->beepDelayEnd   < schedule->beepDelayBegin  ){ schedule->beepDelayEnd   = schedule->beepDelayBegin;  }
  
      schedule->alarmTime.hour   = _spinBoxHour  .draw(schedule->alarmTime.hour  );
      schedule->alarmTime.minute = _spinBoxMinute.draw(schedule->alarmTime.minute);
  
      _labelForSpinBoxRadio .draw();
      _labelForSpinBoxBuzzer.draw();
      _labelForSpinBoxLight .draw();
      _labelForSpinBoxBeep  .draw();
      _labelForSpinBoxTime  .draw();
   
      //schedule config update
      _buttonSave.draw();
      _buttonLoad.draw();
      _toggleButtonConfig.drawToogle();
    }
  }
  
  void Gui::handleRadioGui(RadioSettings* radioSettings)
  {
    if(_radioToggleButtonConfig.isActive())
    {
      _radioButtonSave.setEnabled();     
      _radioButtonLoad.setEnabled(); 
      _radioSpinBoxChannel0.setEnabled(); 
      _radioSpinBoxChannel1.setEnabled(); 
      _radioSpinBoxChannel2.setEnabled();  
      _radioButtonChannel0Alarm.setEnabled();  
      _radioButtonChannel1Alarm.setEnabled(); 
      _radioButtonChannel2Alarm.setEnabled();  
      _radioButtonChannel0Entertainment.setEnabled();  
      _radioButtonChannel1Entertainment.setEnabled(); 
      _radioButtonChannel2Entertainment.setEnabled(); 
    }
    else
    {
      _radioButtonSave.unsetEnabled();     
      _radioButtonLoad.unsetEnabled(); 
      _radioSpinBoxChannel0.unsetEnabled(); 
      _radioSpinBoxChannel1.unsetEnabled(); 
      _radioSpinBoxChannel2.unsetEnabled();  
      _radioButtonChannel0Alarm.unsetEnabled();  
      _radioButtonChannel1Alarm.unsetEnabled(); 
      _radioButtonChannel2Alarm.unsetEnabled();  
      _radioButtonChannel0Entertainment.unsetEnabled();  
      _radioButtonChannel1Entertainment.unsetEnabled(); 
      _radioButtonChannel2Entertainment.unsetEnabled(); 
    }    
    
    if(radioSettings != NULL)
    {
      _radioAlarm.draw(); 
      _radioEntertainment.draw(); 
      _radioButtonSave.draw();     
      _radioButtonLoad.draw(); 
      _radioToggleButtonConfig.drawToogle(); 
      _radioToggleButtonEntertainment.drawToogle();   
      _radioButtonFiveMinutes.draw(); 
      _radioButtonOneHour.draw(); 
      
      if(_radioToggleButtonEntertainment.isActive())
      {
	_radioButtonFiveMinutes.unsetEnabled();
	_radioButtonOneHour.unsetEnabled();
      }
      else
      {
	_radioButtonFiveMinutes.setEnabled();
	_radioButtonOneHour.setEnabled();
      }
      
      //was the entertainment label button clicked (which serves as "hidden" reset) or
      //was the radio toogle button clicked (which serves also as an reset)
      if(  _radioLabelButtonEntertainment.wasClicked() 
	|| _radioToggleButtonEntertainment.isActive())
      {
	radioSettings->setEntertainmentChannelEndTicks(0);
	_radioLabelButtonEntertainment.redraw();
      }
      else
      {
	//update entertainment radio timers	
	uint64 currentSeconds = millis() / (uint64)(1000);
	
	//was five minute button pressed
	if(_radioButtonFiveMinutes.wasClicked())
	{
	  if(radioSettings->isEntertainmentChannelActive() == false)
	  {
	    radioSettings->setEntertainmentChannelEndTicks(currentSeconds + (uint64)(5*60));
	  }
	  else
	  {	  
	    radioSettings->setEntertainmentChannelEndTicks(radioSettings->getEntertainmentChannelEndTicks() + (uint64)(5*60));
	  }
	}
	
	//was one hour button pressed
	if(_radioButtonOneHour.wasClicked())
	{
	  if(radioSettings->isEntertainmentChannelActive() == false)
	  {
	    radioSettings->setEntertainmentChannelEndTicks(currentSeconds + (uint64)(60*60));
	  }
	  else
	  {	  
	    radioSettings->setEntertainmentChannelEndTicks(radioSettings->getEntertainmentChannelEndTicks() + (uint64)(60*60));
	  } 
	} 
	 
	//display label
	uint64 endSeconds = radioSettings->getEntertainmentChannelEndTicks();

	if(endSeconds > currentSeconds)
	{
	  uint64 secondsLeft = endSeconds-currentSeconds;
	  
	  uint16 hours   = (secondsLeft / 60 / 60) % 24;
	  uint16 minutes = (secondsLeft / 60) % 60;
	  uint16 seconds = secondsLeft % 60;
	  
	  //display output
	  char buffer[16];
	  sprintf(buffer, "%02i:%02i", hours, minutes);
	  _lcd.drawText(10, 80, buffer, 3, Defines::guiClockTextColor, Defines::guiClockBGColor);
	  
	  sprintf(buffer, ":%02i", seconds);
	  _lcd.drawText(130, 100, buffer, 1, Defines::guiClockTextColor, Defines::guiClockBGColor);	
	}
      }
      
      //update alarm and entertainment settings
      if(_radioButtonChannel0Alarm        .isPressed()){radioSettings->setAlarmChannel(0);}
      if(_radioButtonChannel1Alarm        .isPressed()){radioSettings->setAlarmChannel(1);}
      if(_radioButtonChannel2Alarm        .isPressed()){radioSettings->setAlarmChannel(2);}
      if(_radioButtonChannel0Entertainment.isPressed()){radioSettings->setEntertainmentChannel(0);}
      if(_radioButtonChannel1Entertainment.isPressed()){radioSettings->setEntertainmentChannel(1);}
      if(_radioButtonChannel2Entertainment.isPressed()){radioSettings->setEntertainmentChannel(2);}
            
      //update alarm and entertainment settings
      if(radioSettings->getAlarmChannel() == 0)
      {
        _radioButtonChannel0Alarm.setHighlightDot();
        _radioButtonChannel1Alarm.unsetHighlightDot();
        _radioButtonChannel2Alarm.unsetHighlightDot();
      }
      if(radioSettings->getAlarmChannel() == 1)
      {
        _radioButtonChannel0Alarm.unsetHighlightDot();
        _radioButtonChannel1Alarm.setHighlightDot();
        _radioButtonChannel2Alarm.unsetHighlightDot();
      }
      if(radioSettings->getAlarmChannel() == 2)
      {
        _radioButtonChannel0Alarm.unsetHighlightDot();
        _radioButtonChannel1Alarm.unsetHighlightDot();
        _radioButtonChannel2Alarm.setHighlightDot();
      }
      
      if(radioSettings->getEntertainmentChannel() == 0)
      {
        _radioButtonChannel0Entertainment.setHighlightDot();
        _radioButtonChannel1Entertainment.unsetHighlightDot();
        _radioButtonChannel2Entertainment.unsetHighlightDot();
      }
      if(radioSettings->getEntertainmentChannel() == 1)
      {
        _radioButtonChannel0Entertainment.unsetHighlightDot();
        _radioButtonChannel1Entertainment.setHighlightDot();
        _radioButtonChannel2Entertainment.unsetHighlightDot();
      }
      if(radioSettings->getEntertainmentChannel() == 2)
      {
        _radioButtonChannel0Entertainment.unsetHighlightDot();
        _radioButtonChannel1Entertainment.unsetHighlightDot();
        _radioButtonChannel2Entertainment.setHighlightDot();
      }
        
      _radioButtonChannel0Alarm.draw();  
      _radioButtonChannel1Alarm.draw(); 
      _radioButtonChannel2Alarm.draw();  
      _radioButtonChannel0Entertainment.draw();  
      _radioButtonChannel1Entertainment.draw(); 
      _radioButtonChannel2Entertainment.draw();  
 
      radioSettings->setChannelFrequence(0, _radioSpinBoxChannel0.draw(radioSettings->getChannelFrequence(0)));
      radioSettings->setChannelFrequence(1, _radioSpinBoxChannel1.draw(radioSettings->getChannelFrequence(1)));
      radioSettings->setChannelFrequence(2, _radioSpinBoxChannel2.draw(radioSettings->getChannelFrequence(2)));
   }
  }
  
  void Gui::updateSnozze(uint64 snozzeTicksLeft)
  {
    if(snozzeTicksLeft == 0)
    {
      hideSnozzeLabel();
    }
    else
    {
      if(snozzeTicksLeft <= Defines::snozzeSnozzeTicks)
      {
	uint64 snozzeTicksLeftScaled = snozzeTicksLeft / (uint64)(1000);
	if(snozzeTicksLeftScaled < 100)
	{
	  _lcd.drawText(154, 76, " ", 1, Defines::guiButtonPressedBGColor, Defines::guiClockBGColor);
	}
	if(snozzeTicksLeftScaled < 10)
	{
	  _lcd.drawText(146, 76, "  ", 1, Defines::guiButtonPressedBGColor, Defines::guiClockBGColor);
	}
	_lcd.drawInteger(138, 76, (long)(snozzeTicksLeftScaled), DEC, 1, Defines::guiButtonPressedBGColor, Defines::guiClockBGColor);
      }
      else
      {
	_lcd.drawText(130, 78, " off ", 1, Defines::guiButtonPressedBGColor, Defines::guiClockBGColor);
      }
    }
  }
  
  void Gui::hideSnozzeLabel()
  {
    _lcd.drawText(130, 76, "    ", 1, Defines::guiButtonPressedBGColor, Defines::guiClockBGColor);
  }
  
  void Gui::debug( float64 number, uint8 rowOffset)
  {
    debug("", number, rowOffset);    
  }
  
  void Gui::debug( String text, uint8 rowOffset)
  {
    _lcd.drawText(10, 220 - rowOffset, "                        ", 1, Defines::guiClockTextColor, Defines::guiClockBGColor); 
    _lcd.drawText(10, 220 - rowOffset, text, 1, Defines::guiClockTextColor, Defines::guiClockBGColor); 
  }
  
  void Gui::debug(String text, float64 number, uint8 rowOffset)
  {
    char buffer[16];
    dtostrf(number, 8, 2, buffer);
    
    String combinedString = text;
    combinedString += " ";
    combinedString += buffer;
    _lcd.drawText(10, 220 - rowOffset, "                                   ", 1, Defines::guiClockTextColor, Defines::guiClockBGColor); 
    _lcd.drawText(10, 220 - rowOffset, combinedString, 1, Defines::guiClockTextColor, Defines::guiClockBGColor); 
  }
  
  void Gui::setBacklight(uint8 percent)
  {
    //led bug will brighten the led if the value is 1 or 2
    if( percent < 5)
    {
      percent = 0;
    }
    _lcd.led(percent); //backlight 0...100%
  }
}

//helper code for icon drawing
    /*
    char* currentIconPosition = iconRadioHeaderData;
    for( uint32 y = 0; y < iconRadioHeight; y++ )
    {
      for( uint32 x = 0; x < iconRadioHeight; x++ )
      {       
        uint32 color = headerToColor(currentIconPosition);
        currentIconPosition += 4;
        if(color != 0)
        {        
          _lcd.drawPixel(10 + x, 120 + y, Defines::guiClockBGColor);
        }
        else
        {
          _lcd.drawPixel(10 + x, 120 + y, Defines::guiClockTextColor);
        }
      }      
    }
    //return schedule;
  */


