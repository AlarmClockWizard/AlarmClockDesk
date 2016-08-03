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

#include "RadioSettings.h"
namespace AlarmClock
{
    
RadioSettings::RadioSettings()
{    
  _channelFrequence0 = 820;
  _channelFrequence1 = 102;
  _channelFrequence2 = 103;  
  
  _alarmChannel = 0;
  _entertainmentChannel = 0;
  _entertainmentChannelEndTicks = 0;
  
  _entertainmentChannelContiniousePlay = false;
}

uint8 RadioSettings::getAlarmChannel() const
{   
  return _alarmChannel;
}

uint8 RadioSettings::getEntertainmentChannel() const
{   
  return _entertainmentChannel;
}

bool RadioSettings::isEntertainmentChannelActive() const
{
  if(_entertainmentChannelContiniousePlay)
  {
    return true;
  }
  else
  {
    uint64 currentTicks = millis();
    return _entertainmentChannelEndTicks > currentTicks;
  }
  return false;
}

bool RadioSettings::isAlarmChannel(uint8 channelIndex) const
{  
  return(_alarmChannel == channelIndex);
}

bool RadioSettings::isEntertainmentChannel(uint8 channelIndex) const
{    
  return(_entertainmentChannel == channelIndex);
}

int RadioSettings::getChannelFrequence(uint8 channelIndex) const
{   
  if(channelIndex == 0)
  {
    return _channelFrequence0;
  }
  
    if(channelIndex == 1)
  {
    return _channelFrequence1;
  }
  
  if(channelIndex == 2)
  {
    return _channelFrequence2;
  }
  
  return -1; 
}

void RadioSettings::setChannelFrequence(uint8 channelIndex, int channelFrequence)
{
  if(channelIndex == 0)
  {
    _channelFrequence0 = channelFrequence;
  }  
  
  if(channelIndex == 1)
  {
    _channelFrequence1 = channelFrequence;
  } 
  
  if(channelIndex == 2)
  {
    _channelFrequence2 = channelFrequence;
  }  
}

void RadioSettings::setAlarmChannel(uint8 channelIndex)
{
  _alarmChannel = channelIndex;
}

void RadioSettings::setEntertainmentChannel(uint8 channelIndex)
{
  _entertainmentChannel = channelIndex;
}

void RadioSettings::setEntertainmentChannelEndTicks(uint64 endTicks)
{
    _entertainmentChannelEndTicks = endTicks;
}

uint64 RadioSettings::getEntertainmentChannelEndTicks()
{
    return _entertainmentChannelEndTicks;
}
 
/*
bool Schedule::timeCorrect(Time currentTime, Time scheduleTime, uint8 delayBegin, uint8 delayEnd)
{
  uint64 currentTicks = 
  (currentTime.hour   * 60 * 60) + 
  (currentTime.minute * 60 ) + 
  (currentTime.second);
  
  uint64 scheduleTicks = 
  (scheduleTime.hour   * 60 * 60) + 
  (scheduleTime.minute * 60 ) + 
  (scheduleTime.second);
  
  uint64 scheduleTicksBegin = scheduleTicks + delayBegin * 60;
  uint64 scheduleTicksEnd   = scheduleTicks + delayEnd   * 60;
  
  if(currentTicks >= scheduleTicksBegin && currentTicks <= scheduleTicksEnd)
  {
    return true;
  }
 
  return false;
}*/

} //namespace AlarmClock


