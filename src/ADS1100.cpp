/**************************************************************************/
/*!
    @file     ADS1100.cpp
    @author   JASON JOHNSTON

    
	Driver for the Texas Instrument ADS1100 ADC

    
	Please Note This driver is based on the driver for the ADS1015 created by Adafruit
	
    @section  HISTORY

    v1.0 - First release
	v1.0.1 - Removed Default value from Function call to allow for better support amoung arduino devices.
*/
/**************************************************************************/

#include "ADS1100.h"

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static uint8_t i2cread(void) {
  #if ARDUINO >= 100
  return Wire.read();
  #else
  return Wire.receive();
  #endif
}

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static void i2cwrite(uint8_t x) {
  #if ARDUINO >= 100
  Wire.write((uint8_t)x);
  #else
  Wire.send(x);
  #endif
}

/**************************************************************************/
/*!
    @brief  Writes 8-bits to the specified destination register
*/
/**************************************************************************/
static void writeRegister(uint8_t i2cAddress, uint8_t value) {
  Wire.beginTransmission(i2cAddress);
  i2cwrite((uint8_t)value);
  Wire.endTransmission();
}
	
/**************************************************************************/
/*!
    @brief  Reads the 16-bits From the Data Registor*/
/**************************************************************************/

static uint16_t readRegister2(uint8_t i2cAddress) {
  Wire.beginTransmission(i2cAddress);
  Wire.endTransmission();
  Wire.requestFrom(i2cAddress, (uint8_t)2);
  return ((i2cread()<<8) | i2cread());  
}
/**************************************************************************/






/**************************************************************************/
/*!
    @brief  Instantiates a new ADS1110A0 class w/appropriate properties
*/
/**************************************************************************/
ADS1100::ADS1100(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
	m_gain = GAIN_ONE;
	m_sps = SPS_8;
}

/**************************************************************************/
/*!
    @brief  Sets up the HW (reads coefficients values, etc.)
*/
/**************************************************************************/
void ADS1100::begin() {
  Wire.begin();
}

/**************************************************************************/
/*!
    @brief  Sets the gain and input voltage range
*/
/**************************************************************************/

void ADS1100::setGain(adsGain_t gain)
{
  m_gain = gain;
}

/**************************************************************************
/*!
    @brief  Sets the Sample Speed
*/
/**************************************************************************/

void ADS1100::setSPS(adsSPS_t sps){
  m_sps = sps;
}

/**************************************************************************/
/*!
    @brief  Gets The Data From the ADC
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
		writeRegister(m_i2cAddress, config1);//Write Configruation Data to Chip
		delay(5);//Wait for converson to complete
		results = readRegister2(m_i2cAddress);//Read Conversion data
		
	}
	else if(mode == ADS1100_REG_CONFIG_OS_CONTINIUS){
		writeRegister(m_i2cAddress, config1);//Write Configruation Data to Chip
		delay(5);//Wait for converson to complete
		results = readRegister2(m_i2cAddress);//Read Conversion data
	}
  return results;
	
}




