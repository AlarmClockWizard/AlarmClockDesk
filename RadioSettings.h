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

#ifndef RADIO_SETTINGS_H
#define RADIO_SETTINGS_H

#include "Types.h"
#include "Time.h"

namespace AlarmClock
{

class RadioSettings
{
  private:
    int _channelFrequence0;
    int _channelFrequence1;
    int _channelFrequence2;
    uint8 _alarmChannel;
    uint8 _entertainmentChannel;    
    
    uint64 _entertainmentChannelEndTicks;
    bool _entertainmentChannelContiniousePlay;
  
  public:
    RadioSettings();
    uint8 getAlarmChannel() const;
    uint8 getEntertainmentChannel() const;
    bool isEntertainmentChannelActive() const;
    bool isAlarmChannel(uint8 channelIndex) const;
    bool isEntertainmentChannel(uint8 channelIndex) const;
    int  getChannelFrequence(uint8 channelIndex) const;
    void setChannelFrequence(uint8 channelIndex, int channelFrequence);
    void setAlarmChannel(uint8 channelIndex);
    void setEntertainmentChannel(uint8 channelIndex);
    void setEntertainmentChannelEndTicks(uint64 endTicks);
    uint64 getEntertainmentChannelEndTicks();
};

}

#endif //RADIO_SETTINGS_H

