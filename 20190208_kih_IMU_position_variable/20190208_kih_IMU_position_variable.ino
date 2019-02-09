/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Taehun Lim (Darby) */

#include <DynamixelWorkbench.h>
#include <IMU.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  57600
#define DXL_ID    1

DynamixelWorkbench dxl_wb;
cIMU    IMU;



uint8_t   err_code;
uint8_t   led_tog = 0;
uint8_t   led_pin = 13;

void setup() 
{
  const char *log;
  bool result = false;
  static uint32_t imu_time = 0;
  static uint32_t tTime[3];
  uint8_t dxl_id = DXL_ID;
  uint16_t model_number = 0;
  Serial.begin(57600);
  IMU.begin();
  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  result = dxl_wb.ping(dxl_id, &model_number, &log);
  result = dxl_wb.jointMode(dxl_id, 0, 0, &log);
  
}

void loop() 
{
  
    
  

  const char *log;
  bool result = false;
  static uint32_t imu_time = 0;
  static uint32_t tTime[3];
  uint8_t dxl_id = DXL_ID;
  uint16_t model_number = 0;
   
  IMU.update();
       
    

    Serial.print(imu_time);
    Serial.print(" ");
    Serial.println(IMU.rpy[0]);
    
  
      if (IMU.rpy[0]<10&&IMU.rpy[0]>-10)
    {
      dxl_wb.goalPosition(dxl_id, (int32_t)2023);
      delay(500);
      }
      else if(IMU.rpy[0]>10)
      {

     dxl_wb.goalPosition(dxl_id, (int32_t)0);
      delay(500);
      }
      else
      {
        dxl_wb.goalPosition(dxl_id, (int32_t)4095);
      delay(500);
        }
    

    
}
