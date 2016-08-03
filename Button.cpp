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

#include "Button.h"
#include "Defines.h"

namespace AlarmClock
{
  
Button::Button()
{
  _stateIsEnabled         = true;
  _stateIsEnabledOld      = true;
  _stateIsPressed         = true;
  _stateIsPressedOld      = _stateIsPressed;
  _stateIsActive          = false;
  _stateIsActiveOld       = !_stateIsActive;  
  _stateIsHidden          = false;
  _stateIsHiddenOld       = _stateIsHidden; 
  _highlightUnderscore    = false;
  _highlightUnderscoreOld = false;
  _highlightDot           = false;
  _highlightDotOld        = false;  
  _lastPressedTicks       = millis();
  _lastPressedState	  = false;
  _buttonWasInUnpressedState = true;
      
  _text = "";
  _lcd = NULL; 
  _touch = NULL;
  _posX = 0;
  _posY = 0;
  _dimX = 0;
  _dimY = 0;
  _textColor = 0;
  _bgColor = 0;
  _activeTextColor = 0;
  _activeBGColor = 0;
  _pressedTextColor = 0;
  _pressedBGColor = 0;
  _textOffsetX = 0; 
  _textOffsetY = 0;   
}

Button::~Button()
{
  setHidden();
}

void Button::setup
(
  String text,
  MI0283QT2* lcd, 
  ADS7846* touch,
  uint16 posX,
  uint16 posY,
  uint16 dimX,
  uint16 dimY,
  uint16 textColor,
  uint16 bgColor,
  uint16 activeTextColor,
  uint16 activeBGColor,
  uint16 pressedTextColor,
  uint16 pressedBGColor,
  uint16 textOffsetX,
  uint16 textOffsetY  
)
{
  _text = text;
  _lcd = lcd;
  _touch = touch;
  _posX = posX;
  _posY = posY;
  _dimX = dimX;
  _dimY = dimY;
  _textColor = textColor;
  _bgColor = bgColor;
  _activeTextColor = activeTextColor;
  _activeBGColor = activeBGColor;
  _pressedTextColor = pressedTextColor,
  _pressedBGColor = pressedBGColor;
  _textOffsetX = textOffsetX;
  _textOffsetY = textOffsetY; 
}

void Button::drawToogle()
{
  if(wasClicked())
  {
      _stateIsActive = !_stateIsActive;
  }
  
  draw();
}

void Button::draw()
{
  _stateIsPressed = isPressed();
  if( _stateIsPressedOld      != _stateIsPressed
   || _stateIsEnabledOld      != _stateIsEnabled
   || _stateIsActiveOld       != _stateIsActive
   || _stateIsHiddenOld       != _stateIsHidden
   || _highlightUnderscoreOld != _highlightUnderscore
   || _highlightDotOld        != _highlightDot)
  {
    paint();
  }
}
void Button::redraw()
{
  paint();
}

void Button::paint()
{
  if(_lcd != NULL)
  {
    if(_stateIsHidden)
    {
      _lcd->fillRect(_posX, _posY, _posX + _dimX, _posY + _dimY, Defines::guiBGColor);
    }
    else
    {
      //normal colors (unpressed and not activated
      uint16 textColor = _textColor;
      uint16 bgColor = _bgColor;

      //overwrite color if button is toggled active
      if(_stateIsActive)
      {
	textColor = _activeTextColor;
	bgColor = _activeBGColor;
      }       

      //if button is currently pressed this will overwrite the other colors
      if(_stateIsPressed)
      {
	textColor = _pressedTextColor;
	bgColor = _pressedBGColor;
      }

      //draw button background
      _lcd->fillRect(_posX, _posY, _posX + _dimX, _posY + _dimY, bgColor);

      //draw bar below text if highlightUnderscore is active
      if( _highlightUnderscore )
      {
	String underscoreText = _text;
	for( uint32 charIndex = 0; charIndex != underscoreText.length(); charIndex++)
	{
	  underscoreText.setCharAt(charIndex, '_');
	}

	_lcd->drawText(_posX + _textOffsetX, _posY + _textOffsetY + 3, underscoreText, 1, textColor, bgColor);
      }

      //draw dot next to button if if _highlightDot is active
      if( _highlightDot )
      {      
	_lcd->fillCircle(_posX + 15 + (_text.length() * 8), _posY + 15, 4, _pressedBGColor); 
      }

      //draw "guarding" border arrount button if it is disabled (grayed out without function)
      if( _stateIsEnabled == false )
      {      
	_lcd->drawRect(_posX, _posY, _posX + _dimX, _posY + _dimY, Defines::guiLineColor);
      }
      
      //draw normal text of button
      _lcd->drawText(_posX + _textOffsetX, _posY + _textOffsetY, _text, 1, textColor, bgColor);
    }
  }
  
  //update state  
  _stateIsPressedOld      = _stateIsPressed;
  _stateIsActiveOld       = _stateIsActive;
  _stateIsHiddenOld       = _stateIsHidden;
  _stateIsPressedOld      = _stateIsPressed;
  _stateIsEnabledOld      = _stateIsEnabled;
  _highlightUnderscoreOld = _highlightUnderscore;
  _highlightDotOld        = _highlightDot;
}

void Button::setEnabled()
{
  _stateIsEnabled = true;
}

void Button::unsetEnabled()
{
  _stateIsEnabled = false;
}

bool Button::isEnabled()
{
  return _stateIsEnabled;
}

void Button::setActive()
{
   _stateIsActive = true;
}

void Button::unsetActive()
{
   _stateIsActive = false;
}

bool Button::isActive()
{
  return _stateIsActive;
}

void Button::setHidden()
{
  _stateIsHidden = true;  
  draw(); 
}

void Button::unsetHidden()
{
  _stateIsHidden = false;
  draw(); 
}

bool Button::isHidden()
{
  return _stateIsHidden;
}

void Button::setHighlightUnderscore()
{
  _highlightUnderscore = true;
}

void Button::unsetHighlightUnderscore()
{
  _highlightUnderscore = false;
}

void Button::setHighlightDot()
{
  _highlightDot = true;
}

void Button::unsetHighlightDot()
{
  _highlightDot = false;
}

bool Button::isPressed()
{
  if(_stateIsEnabled)
  {
    uint32 currentTicks  = millis();
    if( currentTicks -_lastPressedTicks > Defines::buttonCooldownTicks )
    { 
      _lastPressedTicks = currentTicks;
      _lastPressedState =  isPressedWithoutCooldown();  
    } 
  }  
  return _lastPressedState; 
}

bool Button::wasClicked()
{ //same as isPressed but with release between events
  _stateIsPressed = isPressed();
  
  if(_stateIsPressed == true)
  {
    if(_buttonWasInUnpressedState == true)
    {
      _buttonWasInUnpressedState = false;
      return true;
    }
  }
  else
  {
    _buttonWasInUnpressedState = true;
  }
  
  return false;
}

bool Button::isPressedWithoutCooldown()
{
  if(_touch != NULL)
  {
    if(_touch->getPressure() > 10) //touch press?
    {
      uint16 touchX = _touch->getX();
      uint16 touchY = _touch->getY();

      if( touchX >= _posX && touchX <= _posX + _dimX )
      {
	if( touchY >= _posY && touchY <= _posY + _dimY )
	{
	  return true;
	}
      }
    }
  }
  
  return false; 
}

uint16 Button::getPosX()
{
  return _posX;
}

uint16 Button::getPosY()
{
  return _posY;
}

}

