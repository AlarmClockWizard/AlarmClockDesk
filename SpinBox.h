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

#ifndef SPINBOX_H
#define SPINBOX_H

#include "Button.h"z

namespace AlarmClock
{
  class SpinBox
  {
    private:
     bool _stateIsEnabled;
     bool _stateIsHidden;
     bool _stateIsHiddenOld;
     uint16 _minimumValue;
     uint16 _maximumValue;
     uint8 _textSize;
     MI0283QT2* _lcd; 
     ADS7846* _touch;
     uint16 _posX;
     uint16 _posY;
     uint16 _dimX;
     uint16 _dimY;
     uint16 _textColor;
     uint16 _bgColor;
     uint16 _activeTextColor;
     uint16 _activeBGColor; 
     uint16 _pressedTextColor;
     uint16 _pressedBGColor; 
     uint16 _valueTextColor;
     uint16 _valueBGColor;
     uint32 _lastPressedTicks;
     
     uint16 _oldValue;
     
     Button _moreButton;
     Button _lessButton;
     
     void paint(uint16 value);
     void paintValue(uint16 value, uint16 textColor, uint16 fillColor);
    
    public:
      SpinBox();
      ~SpinBox();
      void setup(uint16 minimumValue, uint16 maximumValue, uint8 textSize, MI0283QT2* lcd,  ADS7846* touch, uint16 posX, uint16 posY, uint16 textColor, uint16 bgColor, uint16 activeTextColor, uint16 activeBGColor, uint16 pressedTextColor, uint16 pressedBGColor, uint16 valueTextColor, uint16 valueBGColor);
      uint16 draw(uint16 value);
      uint16 draw();//draw with stored value (refresh display)
      void setEnabled();
      void unsetEnabled();
      bool isEnabled();      
      void setHidden();
      void unsetHidden();   
      bool isHidden();       
  };     
}

#endif //SPINBOX_H

