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

#include "Defines.h"
#include "Label.h"

namespace AlarmClock
{
  
Label::Label()
{
  _stateIsHidden = false;
  _stateIsHiddenOld = !_stateIsHidden;  
  _textSize = 0;
  _text = "";
  _lcd = 0;
}

Label::~Label()
{
  setHidden();
}

void Label::setup
(
  String text,
  uint8 textSize,
  MI0283QT2* lcd,
  uint16 posX,
  uint16 posY,
  uint16 textColor,
  uint16 bgColor
)
{
  _text = text;
  _textSize = textSize;
  _lcd = lcd;
  _posX = posX;
  _posY = posY;
  _textColor = textColor;
  _bgColor = bgColor;  
}

void Label::draw()
{
  if(_stateIsHiddenOld != _stateIsHidden)
  {
    _stateIsHiddenOld = _stateIsHidden;
    if(_stateIsHidden)
    {
      _lcd->drawText(_posX,_posY, _text, _textSize, Defines::guiBGColor, Defines::guiBGColor);   
    }
    else
    {
      _lcd->drawText(_posX,_posY, _text, _textSize, _textColor, _bgColor); 
    }     
  } 
}

void Label::setHidden()
{
  _stateIsHidden = true;
  draw();  
}

void Label::unsetHidden()
{
  _stateIsHidden = false;
  draw();  
}

bool Label::isHidden()
{
  return _stateIsHidden;  
}

}

