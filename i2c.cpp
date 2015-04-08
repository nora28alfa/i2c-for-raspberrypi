/**********************************************
//	i2c.cpp
//
//	Copyright (C) 2015, Y. Nomrua, all right reserved.
//	This software is released under the MIT License.
//
//	http://opensource.org/licenses/mit-license.php
//
//	(Platform Dependent) 
//	
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
//#include <usr/include/linux/i2c-dev.h>

#include "i2c.h"
//platform dependent


#define I2CPASS "/dev/i2c-1"

namespace i2c{

	void wait_usec(uint32_t time){
		static struct timespec ts ={0,0};
		if(time>1000000){//over 1sec
			int temp=time/1000000;
			ts.tv_sec=temp;
			time-= temp*1000000;
		}
		
		ts.tv_nsec = time*1000;
		nanosleep(&ts, NULL);
	}

	//********************
	//
	// local function (typically platform independent)
	// scope is only this file
	//
	//********************
	namespace{//local funtion

		static I2CResult i2c_state = I2C_OK;

	}//end of namespace

	/****************************
	public function
	*****************************/
	/****************************
	Initialize i2c
	*****************************/
	
	int Openfd(){
		int fd;

		i2c_state=I2C_NO_INIT;
		
		if((fd = open(I2CPASS, O_RDWR)) < 0){//error
			return  -1;
		}
		return fd;
	}
	
	
	int SetAddrfd(int fd, uint8_t d_addr){
		
		if(fd<0){
			i2c_state=I2C_NO_INIT;
			return -1;
		}
		if (ioctl(fd, I2C_SLAVE, d_addr) < 0){
			i2c_state=I2C_NO_INIT;
			return -1;
		}
		
		i2c_state=I2C_OK;
	
		return fd;
	}

	/****************************
	i2c master write
	*****************************/
	
	I2CResult Writei2c(int fd, uint8_t r_addr,const uint8_t *buffer, uint32_t length){
	
		if(i2c_state==I2C_NO_INIT){
			return i2c_state;
		}
		
		uint8_t tempbuffer[25];
		tempbuffer[0]=r_addr;
		
		for(int i=1;i<=length;++i){
			tempbuffer[i]=*buffer++;
		}
		
		if(write(fd,tempbuffer,length+1)!=length+1){
			i2c_state= T_DATA_NACK;
			return i2c_state;
		}

		i2c_state= I2C_OK;
		return i2c_state;
	}

	/****************************
	i2c master read
	*****************************/
	I2CResult Readi2c(int fd, uint8_t r_addr, uint8_t *buffer, uint32_t length){

		if(i2c_state==I2C_NO_INIT){
			return i2c_state;
		}
		
		
		if(write(fd,&r_addr,1)!=1){
			i2c_state= SLAR_NACK;
			return i2c_state;
		}
		if(read(fd,buffer,length)!=length){
			i2c_state=I2C_BUS_ERROR;
			return i2c_state;
		}
	
		i2c_state= I2C_OK;
		return i2c_state;
	}
	
	/****************************
	i2c master read 2
	*****************************/
	I2CResult Readi2c(int fd, uint8_t *buffer, uint32_t length){

		if(i2c_state==I2C_NO_INIT){
			return i2c_state;
		}
		
		if(read(fd,buffer,length)!=length){
			i2c_state=I2C_BUS_ERROR;
			return i2c_state;
		}
	
		i2c_state= I2C_OK;
		return i2c_state;

	}
	
	/****************************
	Return state
	*****************************/
	
	I2CResult GetI2CState(){
		return i2c_state;
	}
}//end of namespace i2c{}

