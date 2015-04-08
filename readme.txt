/*************************************************
//
// Copyright (C) 2015, Y. Nomura, all right reserved.
// This software is released under the MIT License.
//
// http://opensource.org/licenses/mit-license.php
//
*************************************************/

This sample is released under the MIT License.

http://opensource.org/licenses/mit-license.php

This sample is tested in raspberry pi B+

if not work, please change the follwing in i2.cpp
 
#define I2CPASS "/dev/i2c-1"
#define I2CPASS "/dev/i2c-0"


i2c address in i2cdevice.h is 7bit (not 8bit). 
