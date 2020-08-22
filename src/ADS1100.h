/**************************************************************************/
/*!
   @file     ADS1100.h
   @author   JASON JOHNSTON

    
	Driver for the Texas Instrument ADS1100 ADC

    
	Please Note This driver is based on the driver for the ADS1015 created by Adafruit
	
    @section  HISTORY

    v1.0 - First release
	v1.0.1 - Removed Default value from Function call in .cpp to allow for better support amoung arduino devices.
*/
/**************************************************************************/
#ifndef ADS1100_H
	#define ADS1100_H
	
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
	const uint8_t ADS1100_A0 = 0x48;
	const uint8_t ADS1100_A1 = 0x49;
	const uint8_t ADS1100_A2 = 0x4A;
	const uint8_t ADS1100_A3 = 0x4B;
	const uint8_t ADS1100_A4 = 0x4C;
	const uint8_t ADS1100_A5 = 0x4D;
	const uint8_t ADS1100_A6 = 0x4E;
	const uint8_t ADS1100_A7 = 0x4F;
/*=========================================================================*/




/*=========================================================================
    CONFIG REGISTER
    -----------------------------------------------------------------------*/
	const uint8_t ADS1100_REG_CONFIG_SINGLE_START = 0x80;  // START/STANDBY - ONLY USED FOR SINGLE CONVERION MODE
    const uint8_t ADS1100_REG_CONFIG_OS_SINGLE = 0x10;  // Single Conversion Mode
	const uint8_t ADS1100_REG_CONFIG_OS_CONTINIUS = 0x00;	// Continous Conversion Mode (Default)
	const uint8_t ADS1100_REG_CONFIG_DR_128SPS = 0x00;	// 128	SPS Data Rate
	const uint8_t ADS1100_REG_CONFIG_DR_32SPS = 0x04;	// 32	SPS Data Rate
	const uint8_t ADS1100_REG_CONFIG_DR_16SPS = 0x08;	// 16	SPS Data Rate
	const uint8_t ADS1100_REG_CONFIG_DR_8SPS = 0x0C;	// 8	SPS Data Rate (Default)
	const uint8_t ADS1100_REG_CONFIG_GAIN_0	 = 0x00;	// Gain 0 (Default)
	const uint8_t ADS1100_REG_CONFIG_GAIN_2 = 0x01;	// Gain 2
	const uint8_t ADS1100_REG_CONFIG_GAIN_4 = 0x02;	// Gain 4
	const uint8_t ADS1100_REG_CONFIG_GAIN_8 = 0x03;	// Gain 8
	
/*=========================================================================*/

typedef enum
{
  GAIN_ONE          = ADS1100_REG_CONFIG_GAIN_0,
  GAIN_TWO          = ADS1100_REG_CONFIG_GAIN_2,
  GAIN_FOUR         = ADS1100_REG_CONFIG_GAIN_4,
  GAIN_EIGHT        = ADS1100_REG_CONFIG_GAIN_8
  
  
} adsGain_t;

typedef enum
{
	SPS_128			= ADS1100_REG_CONFIG_DR_128SPS,
	SPS_32			= ADS1100_REG_CONFIG_DR_32SPS, 
	SPS_16			= ADS1100_REG_CONFIG_DR_16SPS, 
	SPS_8			= ADS1100_REG_CONFIG_DR_8SPS 
	 
} adsSPS_t;

class ADS1100
{
protected:
   // Instance-specific properties
   uint8_t m_i2cAddress;
   adsGain_t m_gain;
   adsSPS_t  m_sps;

 public:
  ADS1100(uint8_t i2cAddress = ADS1100_A0);
  void begin(void);
  int16_t  readADC(uint8_t mode = ADS1100_REG_CONFIG_OS_SINGLE);
  void      setGain(adsGain_t gain);
  void		setSPS(adsSPS_t sps);

 private:
};

#endif