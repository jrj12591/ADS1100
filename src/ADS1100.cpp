/**************************************************************************/
/*!
    @file     ADS1100.cpp
    @author   JASON JOHNSTON

    
	Driver for the Texas Instrument ADS1100 ADC

    
	Please Note This driver is based on the driver for the ADS1015 created by Adafruit
	
    @section  HISTORY

    v1.0 - First release
	v1.0.1 - Removed Default value from Function call to allow for better support amoung arduino devices.
	v2.0 - Rewrote the I2c interaface to support arudino with multiple i2c ports
*/
/**************************************************************************/

#include "ADS1100.h"

/**************************************************************************/
/*!
    Writes 8-bits to the specified destination register
*/
/**************************************************************************/
void ADS1100::writeRegister(uint8_t value) 
{
  _i2cPort->beginTransmission(_i2cAddress);
  _i2cPort->write((uint8_t)value);
  _i2cPort->endTransmission();
}
	
/**************************************************************************/
/*!
      Reads the 16-bits From the Data Registor
*/
/**************************************************************************/
uint16_t ADS1100::readRegister() {
  _i2cPort->beginTransmission(_i2cAddress);
  _i2cPort->endTransmission();
  _i2cPort->requestFrom(_i2cAddress, (uint8_t)2);
  return ((_i2cPort->read()<<8) | _i2cPort->read()); 
}
/**************************************************************************/
/*!
        Instantiates a new ADS1100 class w/appropriate properties
*/
/**************************************************************************/
ADS1100::ADS1100(uint8_t i2cAddress, TwoWire &wirePort) 
{
   _i2cAddress = i2cAddress;
   _i2cPort = &wirePort;
   m_gain = GAIN_ONE;
   m_sps = SPS_8;
   
}

/**************************************************************************/
/*!
    Sets up the HW (reads coefficients values, etc.)
*/
/**************************************************************************/
void ADS1100::begin() {
  _i2cPort->begin();
}

/**************************************************************************/
/*!
        Sets the gain and input voltage range
*/
/**************************************************************************/

void ADS1100::setGain(adsGain_t gain)
{
  m_gain = gain;
}

/**************************************************************************
/*!
    Sets the Sample Speed
*/
/**************************************************************************/

void ADS1100::setSPS(adsSPS_t sps){
  m_sps = sps;
}

/**************************************************************************/
/*!
    Gets The Data From the ADC
*/
/**************************************************************************/
int16_t ADS1100::readADC(uint8_t mode) 
{
	uint16_t results;
	uint8_t config1 = 	m_gain						    		| // Set Gain Settings
						mode									| // Set Operation Mode
						m_sps;									  // Sample Rate
	// Determine if in continous or Single Shot mode
	if (mode == ADS1100_REG_CONFIG_OS_SINGLE){
		config1 = config1| ADS1100_REG_CONFIG_SINGLE_START; //Add Single Shot Start Command
		writeRegister(config1);//Write Configruation Data to Chip
		delay(5);//Wait for converson to complete
		results = readRegister();//Read Conversion data
		
	}
	else if(mode == ADS1100_REG_CONFIG_OS_CONTINIUS){
		writeRegister(config1);//Write Configruation Data to Chip
		delay(5);//Wait for converson to complete
		results = readRegister();//Read Conversion data
	}
  return results;	
}




