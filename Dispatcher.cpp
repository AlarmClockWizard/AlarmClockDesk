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

#include "Dispatcher.h"
#include "Defines.h"

namespace AlarmClock
{
  
  Dispatcher::Dispatcher() : _fileSystem(&_gui), _alarm(&_beeper)
  {
    _currentPageIndex = 0;
    _lastPagePressedTicks = 0;  
    _lastSnozzeTicks = 0;
    _snozzeTicksLeft = 0; 
    _snozzeButtonPressBeginSnozzeTicks    = millis();
    _snozzeButtonPressBeginStopAlarmTicks = millis();
 
    _backlightOffBegin     = 0;
    _backlightOffCurrent   = 0;
    _backlightLowBegin     = 0;
    _backlightLowCurrent   = 0;
    _backlightNormalBegin  = 0;
    _backlightNormalCurrent= 0;
    _backlightQuickBegin   = 0;
    _backlightQuickCurrent = 0;
    _backlightOldValue     = Defines::backlightNormal;
    _backlightCurrentValue = Defines::backlightNormal;
    _backlightTargetValue  = Defines::backlightNormal;
    _backlightDimmCounter  = 0;
    _backlightDimmIncrementTicksBegin = millis();    
  }  
  
  uint8 Dispatcher::getDisplayPageIndex(Time currentTime)
  {    
    //is an page select button pressend?
    uint8 selectedPageIndex = _gui.whichPageIsSelected();    
    if(selectedPageIndex != Defines::invalidPageIndex)
    {
      _lastPagePressedTicks = millis();
      return selectedPageIndex;
    }    
    
    //don't change the users display until we  waited a little bit
    uint32 currentTicks  = millis();
    if( currentTicks - _lastPagePressedTicks > Defines::dispatcherPageChangeCooldownTicks )
    {
      //Ok if we waited long enouth, so we can change the time
      
      //Is the current display day the day of interest?
      uint8 dayOfInterest =  currentTime.getDayOfWeek();
      if( currentTime.hour > 12 )
      {
        dayOfInterest = (dayOfInterest + 1) % 7;
      }      
      
      return dayOfInterest;
    }
    
    return _currentPageIndex;  
  }
  
  uint8 Dispatcher::getCountOfSnozzeButtonPressed()
  {
    uint8 count = 0;
 
    int buttonState0 = digitalRead(Defines::snozze0Pin);
    int buttonState1 = digitalRead(Defines::snozze1Pin);
    int buttonState2 = digitalRead(Defines::snozze2Pin);
    int buttonState3 = digitalRead(Defines::snozze3Pin);
    
    if( buttonState0 == HIGH){ count++; }
    if( buttonState1 == HIGH){ count++; }
    if( buttonState2 == HIGH){ count++; }
    if( buttonState3 == HIGH){ count++; }
  
    return count;
  }
  
  bool Dispatcher::updateSnozze()
  {
    //if the buttons have been presses long enought we will add an snozze increment
    {
      uint8 snozzeButtonCount = getCountOfSnozzeButtonPressed();
      if(snozzeButtonCount < 2)
      {
        _snozzeButtonPressBeginSnozzeTicks    = millis();
        _snozzeButtonPressBeginStopAlarmTicks = millis();
      }
      else
      {
        uint32 snozzeTicksDifferenceSnozze = millis() - _snozzeButtonPressBeginSnozzeTicks;
        if( snozzeTicksDifferenceSnozze >= Defines::snozzeTicksDifferenceForSnozze)
        {
           _snozzeTicksLeft = Defines::snozzeSnozzeTicks;
           _lastSnozzeTicks = millis();
           _beeper.stop(); 
           _beeper.play(NOTE_D1,200);
        }
        
        uint32 snozzeTicksDifferenceStopAlarm = millis() - _snozzeButtonPressBeginStopAlarmTicks;
        if( snozzeTicksDifferenceStopAlarm >= Defines::snozzeTicksDifferenceForSnozzeStopAlarm)
        {
           _snozzeTicksLeft = Defines::snozzeStopAlarmTicks;
           _lastSnozzeTicks = millis();
           _beeper.stop(); 
           _beeper.play(NOTE_B3,2000);
        }
      }
    }
          
    if( _lastSnozzeTicks != 0 )
    {
      uint64 snozzeDecrement = (uint64)(millis()) - _lastSnozzeTicks;
      if( snozzeDecrement >= _snozzeTicksLeft )
      {
        _snozzeTicksLeft = 0;
      }
      else
      {
        _snozzeTicksLeft -= snozzeDecrement;
      }
      _lastSnozzeTicks = millis();
    }

    if(_snozzeTicksLeft != 0)
    { 
      return true;
    }
    
    return false;
  }
  
  void Dispatcher::updatedBacklight()
  {
    _backlightDimmCounter++;
    
    //updated counters
    uint32 photoResistorValue = analogRead(Defines::photoResistorPin);

    //enable the backlight for special cases
    if (  digitalRead(Defines::distanceSenstorPin) == LOW //the distance sensor overwrites the photo resitor
       || _gui.getPressure() > 5  //we will also enable the backlight if the display is pressed
       || _alarm.isEnabled() )    //and last but not least an active alarm
    {
      if( _backlightQuickBegin == 0 )
      {        
        _backlightQuickBegin   = millis();
        _backlightQuickCurrent = millis();
      }
      if( _backlightNormalCurrent - _backlightNormalBegin < Defines::backlightWaitTicks )
      {
        _backlightQuickCurrent = millis();
      }
      _backlightOffBegin     = 0;
      _backlightOffCurrent   = 0;
      _backlightLowBegin     = 0;
      _backlightLowCurrent   = 0;
      _backlightNormalBegin  = 0;
      _backlightNormalCurrent= 0;
    }
    else
    {
      _backlightQuickBegin   = 0;
      _backlightQuickCurrent = 0;
    }
           
    if( photoResistorValue <= Defines::backlightThresholdOff )
    {
      if( _backlightOffBegin == 0 )
      {        
        _backlightOffBegin   = millis();
        _backlightOffCurrent = millis();
      }
      if( _backlightOffCurrent - _backlightOffBegin < Defines::backlightWaitTicks )
      {
        _backlightOffCurrent = millis();
      }
      _backlightLowBegin     = 0;
      _backlightLowCurrent   = 0;
      _backlightNormalBegin  = 0;
      _backlightNormalCurrent= 0;
    }
    else
    {
      if( photoResistorValue <= Defines::backlightThresholdLow )
      {
        if( _backlightLowBegin == 0 )
        {        
          _backlightLowBegin   = millis();
          _backlightLowCurrent = millis();
        }
        if( _backlightLowCurrent - _backlightLowBegin < Defines::backlightWaitTicks )
        {
          _backlightLowCurrent = millis();
        }
        _backlightOffBegin     = 0;
        _backlightOffCurrent   = 0;
        _backlightNormalBegin  = 0;
        _backlightNormalCurrent= 0;
      }
      else
      { 
        if( _backlightNormalBegin == 0 )
        {        
          _backlightNormalBegin   = millis();
          _backlightNormalCurrent = millis();
        }
        if( _backlightNormalCurrent - _backlightNormalBegin < Defines::backlightWaitTicks )
        {
          _backlightNormalCurrent = millis();
        }
        _backlightOffBegin     = 0;
        _backlightOffCurrent   = 0;
        _backlightLowBegin     = 0;
        _backlightLowCurrent   = 0;
      }
    }
    
    //uint8 backlightTargetValueOld = _backlightTargetValue;
    if( _backlightOffCurrent - _backlightOffBegin >= Defines::backlightWaitTicks )
    {
      if( _backlightTargetValue != Defines::backlightOff )
      {
        _backlightOldValue = _backlightCurrentValue;
        _backlightTargetValue  = Defines::backlightOff;
        _backlightDimmIncrementTicksBegin = millis();
      }
    }
    else 
    {
      if( (_backlightLowCurrent - _backlightLowBegin >= Defines::backlightWaitTicks)
        ||( _backlightQuickCurrent - _backlightQuickBegin >= Defines::backlightWaitTicksQuick ))
      {
        if( _backlightTargetValue != Defines::backlightLow )
        {
          _backlightOldValue = _backlightCurrentValue;
          _backlightTargetValue = Defines::backlightLow;
          _backlightDimmIncrementTicksBegin = millis();
        }
      }
      else
      { 
        if( _backlightNormalCurrent - _backlightNormalBegin >= Defines::backlightWaitTicks )
        {
          if( _backlightTargetValue != Defines::backlightNormal )
          {
            _backlightOldValue = _backlightCurrentValue;
            _backlightTargetValue = Defines::backlightNormal;
            _backlightDimmIncrementTicksBegin = millis();
          }
        }
      }
    }
    
    if( _backlightCurrentValue != _backlightTargetValue )
    {
        float64 targetValueDifference = (float64)(_backlightTargetValue)  - (float64)(_backlightOldValue);
        float64 incrementPerStep      = targetValueDifference / Defines::backlightStepCount;
        float64 ticksPerStep          = Defines::backlightTickIntervall / Defines::backlightStepCount;
        float64 ticksCurrent          = (float64)(millis());
        float64 ticksSinceBegin       = ticksCurrent - (float64)(_backlightDimmIncrementTicksBegin);
        float64 stepsSinceBegin       = ticksSinceBegin / ticksPerStep;
        float64 currentStep           = incrementPerStep * stepsSinceBegin;
        float64 currentValue          = _backlightOldValue + currentStep;
  
        if( _backlightOldValue < _backlightTargetValue )
        { //dimm up
          if( currentValue > _backlightTargetValue )
          { //difference was to big
            currentValue = _backlightTargetValue;
          }
        }
        else
        { //dimm down
          if( currentValue < _backlightTargetValue )
          { //difference was to big
            currentValue = _backlightTargetValue;
          }
        }
        
        _backlightCurrentValue = currentValue;
        _gui.setBacklight(_backlightCurrentValue);
    }
  }

  void Dispatcher::setup()
  {
    _clock.setup();
    _gui.setup();
    _gui.setBacklight(5);
    _fileSystem.setup();
    _beeper.setup(); 
    _alarm.setup();
//#############################
/*#*/_clock._gui = &_gui; /*#*/
//#############################

    for(uint8 currentPageIndex = 0; currentPageIndex < 7; currentPageIndex++)
    {
      Schedule blankSchedule;
      blankSchedule.activateRadio = true;
      _fileSystem.saveSchedule( currentPageIndex, blankSchedule );
      _schedules[currentPageIndex] = _fileSystem.loadSchedule( currentPageIndex );
    }
    
    pinMode(Defines::distanceSenstorPin, INPUT);
    pinMode(Defines::snozze0Pin, INPUT);
    pinMode(Defines::snozze1Pin, INPUT);
    pinMode(Defines::snozze2Pin, INPUT);
    pinMode(Defines::snozze3Pin, INPUT);
    
    _gui.showSchedulePage();
  }
  
  void Dispatcher::loop()
  {
    _clock.loop();
    _currentTime = _clock.getTime();

    uint8 newPageIndex = getDisplayPageIndex(_currentTime);   
    if(newPageIndex != _currentPageIndex)
    {
      //the current page index has changed so we might have to hide the schedule or radio gui
      if(_currentPageIndex <= 6 && newPageIndex == 7)
      {
	_gui.showRadioPage();
      }
      else if(_currentPageIndex == 7 && newPageIndex <= 6)
      {
	_gui.showSchedulePage();
      }  
      _currentPageIndex = newPageIndex;
    }
    
    if(_currentPageIndex <= 6)
    {//normal schedule display
      _gui.handleScheduleGui(&_schedules[_currentPageIndex], _snozzeTicksLeft); 
    }
    else
    {//radio time     
      _gui.handleRadioGui(&_radioSettings); 
    }
    _gui.drawClock(_currentTime);
    _gui.handleTabButtons(_currentPageIndex, _currentTime); 
    updatedBacklight();
    
    if( _gui.configButtonIsActive() && _gui.saveButtonIsPressed() )
    {
      _fileSystem.saveSchedule( _currentPageIndex, _schedules[_currentPageIndex]);
    }
    
    if( _gui.configButtonIsActive() && _gui.loadButtonIsPressed() )
    {
       _schedules[_currentPageIndex] = _fileSystem.loadSchedule(_currentPageIndex);
    }
        
    _alarm.loop( &_schedules[_currentTime.getDayOfWeek()], _currentTime, updateSnozze() );
  }
}

