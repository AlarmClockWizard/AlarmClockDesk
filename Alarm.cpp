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

#include "Alarm.h"
#include "Defines.h"

namespace AlarmClock
{
  
Alarm::Alarm(Beeper* beeper) //: _radio(Defines::radioResetPin, Defines::i2cInputOutputPin, Defines::i2cClockPin)
{
  _beeper = beeper;
}
  
void Alarm::setup()
{
  _enabledRadio  = false;
  _enabledBuzzer = false;
  _enabledLight  = false;
  _enabledBeep   = false;
    
  _ticksBegin = millis();
  pinMode(Defines::lightPin, OUTPUT);
  pinMode(Defines::buzzerPin,OUTPUT);
  
  //_radio.powerOn();
}
   
void Alarm::loop(Schedule* schedule,Time time, bool snozzeEnabled)
{
  if( snozzeEnabled )
  {
    if(_enabledRadio  == true){_enabledRadio  = false; endRadio ();}
    if(_enabledBuzzer == true){_enabledBuzzer = false; endBuzzer();} 
    if(_enabledLight  == true){_enabledLight  = false; endLight ();} 
    if(_enabledBeep   == true){_enabledBeep   = false; endBeep  ();}  
  }
  else
  {
    //Radio
    if(schedule->alarmRadio(time))
    {
      if(_enabledRadio == false)
      {
        _enabledRadio = true;
        beginRadio();
      }
      continueRadio();
    }
    else
    {
      if(_enabledRadio == true)
      {
        _enabledRadio = false;
        endRadio();
      }
    }
    
    //Buzzer
    if(schedule->alarmBuzzer(time))
    {
      if(_enabledBuzzer == false)
      {
        _enabledBuzzer = true;
        beginBuzzer();
      }
      continueBuzzer();
    }
    else
    {
      if(_enabledBuzzer == true)
      {
        _enabledBuzzer = false;
        endBuzzer();
      }
    }
    
    //Light
    if(schedule->alarmLight(time))
    {
      if(_enabledLight == false)
      {
        _enabledLight = true;
        beginLight();
      }
      continueLight();
    }
    else
    {
      if(_enabledLight == true)
      {
        _enabledLight = false;
        endLight();
      }
    }
    
    //Beep
    if(schedule->alarmBeep(time))
    {
      if(_enabledBeep == false)
      {
        _enabledBeep = true;
        beginBeep();
      }
      continueBeep();
    }
    else
    {
      if(_enabledBeep == true)
      {
        _enabledBeep = false;
        endBeep();
      }
    }
  }
}

bool Alarm::isEnabled()
{
    return (_enabledRadio || _enabledBuzzer || _enabledLight || _enabledBeep);  
}

void Alarm::beginRadio()
{
  //_radio.setChannel(Defines::alarmRadioChannel);
  //_radio.setVolume(15);
}

void Alarm::continueRadio()
{
  
}

void Alarm::endRadio()
{
  //_radio.setVolume(0);
}

void Alarm::beginBuzzer()
{
  
}

void Alarm::continueBuzzer()
{
  if( intervallActive() )
  {
    digitalWrite(Defines::buzzerPin, HIGH);
  }
  else
  {
    digitalWrite(Defines::buzzerPin, LOW);
  }
}

void Alarm::endBuzzer()
{
  digitalWrite(Defines::buzzerPin, LOW);
}

void Alarm::beginLight()
{
  
}

void Alarm::continueLight()
{
  if( intervallActive() )
  {
    digitalWrite(Defines::lightPin, HIGH);
  }
  else
  {
    digitalWrite(Defines::lightPin, LOW);
  }
}

void Alarm::endLight()
{
  digitalWrite(Defines::lightPin, LOW);
}

void Alarm::beginBeep()
{
  _beeperTicksAtNextInteraction = 0;
  _beeperCurrentIndex = 0;
}

void Alarm::continueBeep()
{  
  //melodiy
  uint32 meldoyLength  = 20;
  uint32 melodyNotes[] = {NOTE_C5, NOTE_C5, NOTE_C5, NOTE_D4, NOTE_C5, NOTE_C5, NOTE_D4, NOTE_C5, NOTE_D4, NOTE_C5,
                          NOTE_B4, NOTE_B4, NOTE_B4, NOTE_C3, NOTE_B4, NOTE_B4, NOTE_C1, NOTE_B4, NOTE_C3, NOTE_B4};
  uint32 melodyBeats[] = {200,     200,     200,     150,     150,     200,     150,     150,     150,     200    ,
                          200,     200,     200,     150,     150,     200,     150,     150,     150,     200    };
 
  //play melody
  if(millis() < _beeperTicksAtNextInteraction)
  {
    return; //nothing to do in this time frame
  }
  
  if(_beeperCurrentIndex >= meldoyLength)
  {
    //melody seams finished after the current note was played:)
    _beeperTicksAtNextInteraction = millis() + 100;
    _beeperCurrentIndex = 0;
    return;
  }

  uint64 beatOfCurrentIndex = melodyBeats[_beeperCurrentIndex] * 0.45;
  uint64 pauseOfCurrentIndex = beatOfCurrentIndex * 0.8;
  _beeper->play(melodyNotes[_beeperCurrentIndex], beatOfCurrentIndex);
  _beeperTicksAtNextInteraction = millis() + beatOfCurrentIndex + pauseOfCurrentIndex;
  _beeperCurrentIndex++; 
}

void Alarm::endBeep()
{
  //_beeper->stop();
}


bool Alarm::intervallActive()
{
  uint64 currentTicks = millis();
  uint64 tickDifference = currentTicks - _ticksBegin;
  uint64 block = tickDifference / Defines::alarmTickIntervall;
  
  if( block % 2 == 0 )
  {
    return true;
  }

  return false;
}

} //namespace AlarmClock


