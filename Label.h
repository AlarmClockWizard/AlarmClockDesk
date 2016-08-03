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

#ifndef LABEL_H
#define LABEL_H

#include <MI0283QT2.h>
#include "Types.h"

namespace AlarmClock
{
  class Label
  {
    private:
     MI0283QT2* _lcd; 
     bool _stateIsHidden;
     bool _stateIsHiddenOld;
     String _text;
     uint8 _textSize;
     uint16 _posX;
     uint16 _posY;
     uint16 _textColor;
     uint16 _bgColor;     
    
    public:
      Label();
      ~Label();
      void setup(String text, uint8 textSize, MI0283QT2* lcd, uint16 posX, uint16 posY, uint16 textColor, uint16 bgColor);
      void draw();
      void setHidden();
      void unsetHidden();   
      bool isHidden();       
  };     
}

#endif //Label_H

