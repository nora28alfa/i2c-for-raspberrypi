/*************************************************
//
// i2c.h
// Copyright (C) 2015, Y. Nomura, all right reserved.
// This software is released under the MIT License.
//	http://opensource.org/licenses/mit-license.php
//
*************************************************/

#ifndef __I2C_H_
#define __I2C_H_

//#include <cstdint>
#include <stdint.h>

namespace i2c{
	
	
	void wait_usec(uint32_t time);
	
	typedef enum{
		I2C_OK=0,
		SLAW_NACK,
		SLAR_NACK,
		T_DATA_NACK,
		I2C_NO_INIT,
		I2C_BUSY,
		I2C_TIME_OUT,
		I2C_BUS_ERROR
	}I2CResult;


	
	int Openfd();
	int SetAddrfd(int fd, uint8_t d_addr);

	I2CResult Writei2c(int fd, uint8_t r_addr,const uint8_t *buffer, uint32_t length);
	inline I2CResult Writei2c(int fd, uint8_t r_addr,uint8_t buffer){
		return Writei2c(fd,r_addr,&buffer,1);
	}

	I2CResult Readi2c(int fd, uint8_t r_addr, uint8_t *buffer, uint32_t length);
	I2CResult Readi2c(int fd, uint8_t *buffer, uint32_t length);

	I2CResult GetI2CState();
}

#endif
