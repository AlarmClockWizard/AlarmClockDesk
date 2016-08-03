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

#ifndef BUTTON_H
#define BUTTON_H

#include <MI0283QT2.h>
#include <ADS7846.h>
#include "Types.h"

namespace AlarmClock
{
  class Button
  {
    protected:
     bool _stateIsEnabled;
     bool _stateIsEnabledOld;
     bool _stateIsPressed;
     bool _stateIsPressedOld;
     bool _stateIsActive;
     bool _stateIsActiveOld;
     bool _stateIsHidden;
     bool _stateIsHiddenOld;
     bool _highlightUnderscore;
     bool _highlightUnderscoreOld;
     bool _highlightDot;
     bool _highlightDotOld;
     uint32 _lastPressedTicks;
     bool _lastPressedState;
     bool _buttonWasInUnpressedState;
    
     String _text;
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
     uint16 _textOffsetX; 
     uint16 _textOffsetY; 
     
     bool isPressedWithoutCooldown();
     void paint();
         
    public:
      Button();
      ~Button();
      void setup(String text, MI0283QT2* lcd, ADS7846* touch, uint16 posX, uint16 posY, uint16 dimX, uint16 dimY, uint16 textColor, uint16 bgColor, uint16 activeTextColor, uint16 activeBGColor, uint16 pressedTextColor, uint16 pressedBGColor, uint16 textOffsetX, uint16 textOffsetY );
      void redraw();
      void draw();
      void drawToogle();

      void setEnabled();
      void unsetEnabled();
      bool isEnabled();
      
      void setActive();
      void unsetActive();
      bool isActive();
      
      void setHidden();
      void unsetHidden();
      bool isHidden();   

      void setHighlightUnderscore();
      void unsetHighlightUnderscore();
      void setHighlightDot();
      void unsetHighlightDot();
      bool isPressed(); 
      bool wasClicked();
      
      uint16 getPosX();
      uint16 getPosY();
  };
}

#endif //BUTTON_H

