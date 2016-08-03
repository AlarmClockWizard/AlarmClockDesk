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
#include "SpinBox.h"

namespace AlarmClock
{
  
SpinBox::SpinBox()
{
  _stateIsEnabled = true;
  _stateIsHidden = false;
  _stateIsHiddenOld = _stateIsHidden; 
  _minimumValue = 0;
  _maximumValue = 9;
  _textSize = 2;
  _dimX = 30;
  _dimY = 15;
  _oldValue = 99;
  _lastPressedTicks = 0;  
  _lcd = NULL; 
  _touch = NULL;
  _posX = 0;
  _posY = 0;
  _textColor = 0;
  _bgColor = 0;
  _activeTextColor = 0;
  _activeBGColor = 0;
  _pressedTextColor = 0;
  _pressedBGColor = 0; 
  _valueTextColor = 0;
  _valueBGColor = 0;
}

SpinBox::~SpinBox()
{
  setHidden();
}

void SpinBox::setup
(
  uint16 minimumValue,
  uint16 maximumValue,
  uint8 textSize,
  MI0283QT2* lcd, 
  ADS7846* touch,
  uint16 posX,
  uint16 posY,
  uint16 textColor,
  uint16 bgColor,
  uint16 activeTextColor,
  uint16 activeBGColor,
  uint16 pressedTextColor,
  uint16 pressedBGColor,
  uint16 valueTextColor, 
  uint16 valueBGColor
)
{
  _minimumValue = minimumValue;
  _maximumValue = maximumValue;
  _textSize = textSize;
  _lcd = lcd;
  _touch = touch;
  _posX = posX;
  _posY = posY;
  _textColor = textColor;
  _bgColor = bgColor;
  _activeTextColor = activeTextColor;
  _activeBGColor = activeBGColor;
  _pressedTextColor = pressedTextColor,
  _pressedBGColor = pressedBGColor;
  _valueTextColor = valueTextColor; 
  _valueBGColor = valueBGColor;
  
  uint8 textSizeOffsetY = 0; 
  if( _textSize == 2 )
  {
    textSizeOffsetY = 45;
  }
  if( _textSize == 1 )
  {
    textSizeOffsetY = 31;
  }

  _moreButton.setup(String("+"), _lcd,_touch,_posX,_posY                  ,_dimX,_dimY,_textColor,_bgColor,_activeTextColor,_activeBGColor,_pressedTextColor,_pressedBGColor,12,2);
  _lessButton.setup(String("-"), _lcd,_touch,_posX,_posY + textSizeOffsetY,_dimX,_dimY,_textColor,_bgColor,_activeTextColor,_activeBGColor,_pressedTextColor,_pressedBGColor,12,2);
}

uint16 SpinBox::draw()
{
  return draw(_oldValue);
}

uint16 SpinBox::draw(uint16 value)
{
  if(_stateIsEnabled)
  {
    uint32 currentTicks  = millis();
    if(currentTicks -_lastPressedTicks > Defines::spinBoxCooldownTicks)
    {
      _lastPressedTicks = currentTicks;
      
      if(_moreButton.isPressed())
      {
	if(value < _maximumValue)
	{
	  value++;
	}
      }
    
      if(_lessButton.isPressed())
      {
	if(value > _minimumValue)
	{
	  value--;
	}
      }
    }
  }
  
  _moreButton.draw();
  _lessButton.draw();
  paint(value);
 
  return value;
}

void SpinBox::paint(uint16 value)
{
  if(_stateIsHiddenOld != _stateIsHidden)
  {
    _stateIsHiddenOld = _stateIsHidden;
    //if hidden state changed draw value or hidde rect
    if(_stateIsHidden)
    {
      paintValue(value, Defines::guiBGColor, Defines::guiBGColor);
    }
    else
    {      
      paintValue(value, _valueTextColor, _valueBGColor);
    }
  } 
  else
  {
    _moreButton.draw();
    _lessButton.draw();
   
    if( value != _oldValue )
    {
       _oldValue = value;
       paintValue(value, _valueTextColor, _valueBGColor);
    }
  }
}

void SpinBox::paintValue(uint16 value, uint16 textColor, uint16 fillColor)
{
  if(_lcd != NULL)
  {
    int8 textSizeOffsetX0 = 0;
    int8 textSizeOffsetX = 0;
    int8 textSizeOffsetY = 0; 
    if( _textSize == 2 )
    {
      textSizeOffsetX0 = 2;
      textSizeOffsetX  = 15;
      textSizeOffsetY  = 20;
    }
    if( _textSize == 1 )
    {
      textSizeOffsetX0 = 6;
      textSizeOffsetX  = 15;
      textSizeOffsetY  = 18;
    }  

    if(value > 99)
    {
      uint16 firstDigit  = value / 100;
      uint16 secondDigit = (value - 100*firstDigit) / 10;
      uint16 thirdDigit  = value % 10;
    
      textSizeOffsetX0 -= 7;
      _lcd->drawInteger(_posX + textSizeOffsetX0                    , _posY + textSizeOffsetY, uint8(firstDigit) , DEC, _textSize, textColor, fillColor);
      _lcd->drawInteger(_posX + textSizeOffsetX0 + textSizeOffsetX  , _posY + textSizeOffsetY, uint8(secondDigit), DEC, _textSize, textColor, fillColor);
      _lcd->drawInteger(_posX + textSizeOffsetX0 + 2*textSizeOffsetX, _posY + textSizeOffsetY, uint8(thirdDigit) , DEC, _textSize, textColor, fillColor);
    }
    else
    {   
      if(_oldValue < 100)
      {
	_lcd->drawText (_posX + textSizeOffsetX0 - (textSizeOffsetX/2), _posY + textSizeOffsetY, "   ", _textSize, textColor, fillColor);  
      } 
      _lcd->drawInteger(_posX + textSizeOffsetX0                  , _posY + textSizeOffsetY, uint8(value / 10), DEC, _textSize, textColor, fillColor);
      _lcd->drawInteger(_posX + textSizeOffsetX0 + textSizeOffsetX, _posY + textSizeOffsetY, uint8(value % 10), DEC, _textSize, textColor, fillColor);
    }
  }
}

void SpinBox::setEnabled()
{
  _stateIsEnabled = true;
  _moreButton.setEnabled();
  _lessButton.setEnabled();
}

void SpinBox::unsetEnabled()
{
  _stateIsEnabled = false;
  _moreButton.unsetEnabled();
  _lessButton.unsetEnabled();
}

bool SpinBox::isEnabled()
{
  return _stateIsEnabled;
}

void SpinBox::setHidden()
{
  _stateIsHidden = true;
  _moreButton.setHidden();
  _lessButton.setHidden();
  paint(_oldValue);
}

void SpinBox::unsetHidden()
{
  _stateIsHidden = false;
  _moreButton.unsetHidden();
  _lessButton.unsetHidden();
  paint(_oldValue);
}

bool SpinBox::isHidden()
{
  return _stateIsHidden;
}

}

