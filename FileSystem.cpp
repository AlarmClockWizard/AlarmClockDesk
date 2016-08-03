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

#include "FileSystem.h"
#include <SD.h>
namespace AlarmClock
{
  
  SDcard sd;

ISR(TIMER2_OVF_vect) //Timer 2 Interrupt, called every 1ms
{
  static uint8_t count=1;

  TCNT2 -= 250; //1000 Hz

  if(--count == 0) //100 Hz
  {
    count = 10;
    sd.service();
  }
}


void WriteFile(char *file)
{
  FIL fdst;     //file objects
  FRESULT res;  //result code
  UINT wr;      //file R/W count
  char data[16];

  res = f_open(&fdst, file, FA_CREATE_ALWAYS | FA_WRITE);
  if(res == FR_OK)
  {
    strcpy(data, "test 123");
    res = f_write(&fdst, data, strlen(data), &wr);
    f_close(&fdst);
    return;
  }
  
  char buffer[2];
  sprintf(buffer, "%i", res);

  Serial.println("Error!");
  Serial.println(buffer);
}

FileSystem::FileSystem(AlarmClock::Gui* gui)
{
  _errorString = "";
  _gui = gui;  
}

void FileSystem::setup()
{
  //init Serial port
  Serial.begin(9600); 

  //init LCD
  Serial.println("Init Display...");

  //init SD-Card
  Serial.println("Init SD-Card...");
  sd.init(4); //spi-clk = Fcpu/4

  //init Timer2 for SD service routine
  TCCR2B  = (1<<CS22); //clk=F_CPU/64
  TCNT2   = 0x00;
  TIMSK2 |= (1<<TOIE2); //enable overflow interupt
  
  //interrupts on
  sei();
}

   
void FileSystem::loop()
{
}

void FileSystem::error(String string)
{
  Serial.println(string);
  //_errorString += "|";
  //_errorString += string;
}

void FileSystem::error(String string, FRESULT resultCode)
{
  char buffer[2];
  sprintf(buffer, "%i", resultCode);
  String resultCodeAsString( buffer );
  string += " ";
  string += resultCodeAsString;
  
  error(string);
}

String FileSystem::getScheduleFileName(uint8 dayIndex)
{
  if(dayIndex > 6)
  {
    error("dayIndex invalid");
    return "day0.txt";
  }
 
  char buffer[2];
  sprintf(buffer, "%i", dayIndex);
  
  String fileName = "day";
  fileName += buffer;
  fileName += ".schedule";
  
  error(fileName);
  return fileName;
}

void FileSystem::saveSchedule(uint8 dayIndex, Schedule schedule)
{  
  if(sd.mount() == 0)
  {
    String fileName = getScheduleFileName(dayIndex);
    char fileNameBuffer[16];
    fileName.toCharArray(fileNameBuffer, fileName.length());
    error(fileName);
    
    FIL file;     //file objects
    UINT wr;      //file R/W count    
    FRESULT resultCodeOpen = f_open(&file, fileNameBuffer, FA_CREATE_ALWAYS | FA_WRITE);
    if(resultCodeOpen == FR_OK)
    {
      //char data[16];
      char* schedulePointer = (char*)&schedule;
      FRESULT resultCodeWrite = f_write(&file, schedulePointer, sizeof(Schedule), &wr);      
      error("saveSchedule: f_write result", resultCodeWrite);      
      
      f_close(&file);
      error("saveSchedule: woohoo");
    }
    else
    {
      error("saveSchedule: resultCodeOpen != FR_OK!", resultCodeOpen);
    }    
    sd.unmount();
  }
  else
  {
    error("saveSchedule: No card found!");
  }
  
  return;
}

Schedule FileSystem::loadSchedule(uint8 dayIndex)
{  
  Schedule schedule;
  
  if(sd.mount() == 0)
  {
    error("loadSchedule: sd.mount() == 0");
    String fileName = getScheduleFileName(dayIndex);
    char fileNameBuffer[16];
    fileName.toCharArray(fileNameBuffer, fileName.length());
    //return schedule;
    FIL file;     //file objects
    UINT rd;      //file R/W count
     
    FRESULT resultCodeOpen = f_open(&file, fileNameBuffer, FA_OPEN_EXISTING | FA_READ);
    if(resultCodeOpen == FR_OK)
    {
      char* schedulePointer = (char*)&schedule;
  
      FRESULT resultCodeRead = f_read(&file, schedulePointer, sizeof(Schedule), &rd);
      if(resultCodeRead == FR_OK)
      {
        if(rd != sizeof(Schedule))
        {
          error("loadSchedule: rd !=sizeof(Schedule)");
          _gui->debug("loadSchedule: size rd =", 
          (float64)(rd), 50);
          _gui->debug("loadSchedule: sizeof(Schedule) = ", 
          (float64)(sizeof(Schedule)), 60);
        }
        else
        {
           error("loadSchedule: woohoo");
        }
      }
      else
      {
        error("loadSchedule: resultCodeRead != FR_OK", resultCodeRead); 
      }    
      
      f_close(&file);
    }
    else
    {
      error("loadSchedule: resultCodeOpen != FR_OK!", resultCodeOpen);
    }
    
    sd.unmount();
  }
  else
  {
    error("loadSchedule: No card found!");
  }
  
  schedule.dayIndex = dayIndex;
  return schedule;
}

} //namespace AlarmClock


