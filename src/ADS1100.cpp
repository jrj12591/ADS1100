/**************************************************************************/
/*!
    @file     ADS1100.cpp
    @author   JASON JOHNSTON

    
	Driver for the Texas Instrument ADS1100 ADC

    Available in 8 Flavors
    A0 = I2C Address 0x48
    A1 = I2C Address 0x49
    A2 = I2C Address 0x50
    A3 = I2C Address 0x51
    A4 = I2C Address 0x52
    A5 = I2C Address 0x53
    A6 = I2C Address 0x54
    A7 = I2C Address 0x55
	
    @section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/



#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#include "ADS1100.h"

/**************************************************************************/
/*!
    Abstract away platform differences in Arduino wire library
    (Thanks Adafruit)
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
    Abstract away platform differences in Arduino wire library
    (Thanks Adafruit)
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
    Writes 8-bits to the specified destination register
*/
/**************************************************************************/
static void writeRegister(uint8_t i2cAddress, uint8_t value) {
  Wire.beginTransmission(i2cAddress);
  i2cwrite((uint8_t)value);
  Wire.endTransmission();
}
	
/**************************************************************************/
/*!
      Reads the 16-bits From the Data Registor
*/
/**************************************************************************/
static uint32_t readRegister(uint8_t i2cAddress) {
  Wire.beginTransmission(i2cAddress);
  Wire.endTransmission();
  Wire.requestFrom(i2cAddress, (uint8_t)3);
  return ((i2cread() << 16) | i2cread()<<8 | i2cread());
}
/**************************************************************************/
/*!
        Instantiates a new ADS1100 class w/appropriate properties
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
    Instantiates a new ADS1100A0 class w/appropriate properties
*/
/**************************************************************************/
ADS1100A0::ADS1100A0(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
	m_gain = GAIN_ONE;
	m_sps = SPS_8;
}
/**************************************************************************/
/*!
    Instantiates a new ADS1100A1 class w/appropriate properties
*/
/**************************************************************************/
ADS1100A1::ADS1100A1(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
	m_gain = GAIN_ONE;
	m_sps = SPS_8;
}
/**************************************************************************/
/*!
    Instantiates a new ADS1100A02 class w/appropriate properties
*/
/**************************************************************************/
ADS1100A2::ADS1100A2(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
	m_gain = GAIN_ONE;
	m_sps = SPS_8;
}
/**************************************************************************/
/*!
        Instantiates a new ADS1100A3 class w/appropriate properties
*/
/**************************************************************************/
ADS1100A3::ADS1100A3(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
	m_gain = GAIN_ONE;
	m_sps = SPS_8;
}
/**************************************************************************/
/*!
        Instantiates a new ADS1100A4 class w/appropriate properties
*/
/**************************************************************************/
ADS1100A4::ADS1100A4(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
	m_gain = GAIN_ONE;
	m_sps = SPS_8;
}
/**************************************************************************/
/*!
    Instantiates a new ADS1100A5 class w/appropriate properties
*/
/**************************************************************************/
ADS1100A5::ADS1100A5(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
	m_gain = GAIN_ONE;
	m_sps = SPS_8;
}
/**************************************************************************/
/*!
         Instantiates a new ADS1100A6 class w/appropriate properties
*/
/**************************************************************************/
ADS1100A6::ADS1100A6(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
	m_gain = GAIN_ONE;
	m_sps = SPS_8;
}
/**************************************************************************/
/*!
         Instantiates a new ADS1100A7 class w/appropriate properties
*/
/**************************************************************************/
ADS1100A7::ADS1100A7(uint8_t i2cAddress)
{
	m_i2cAddress = i2cAddress;
	m_gain = GAIN_ONE;
	m_sps = SPS_8;
}
/**************************************************************************/
/*!
    Sets up the HW (reads coefficients values, etc.)
*/
/**************************************************************************/
void ADS1100::begin() {
  Wire.begin();
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
int16_t ADS1100::readADC(uint8_t mode = ADS1100_REG_CONFIG_OS_SINGLE) 
{
 uint32_t results;
 uint16_t conversiondata;
 uint8_t status = (0x00);
	uint8_t config1 = 	m_gain						    		| // Set Gain Settings
						ADS1100_REG_CONFIG_OS_SINGLE			| // Set Operation Mode
						mode									| // Singe vs continous
						m_sps;									  // Sample Rate

						
  // Write config registers to the ADC and start conversion
	writeRegister(m_i2cAddress, config1);
	// Deteck if in continous or Single Shot mode
	if (mode = ADS1100_REG_CONFIG_OS_SINGLE){
	do { 
		results = readRegister(m_i2cAddress);//read the data and config regustures
		conversiondata = (uint16_t)results>>8; //Removing the configuration register data from the register read
		status = (uint8_t)results; //Removing the data registers from the configuration data
		status = status >>7; //Shifting to check MSB which indicates if conversion is finished
		delay(5);
		} while (status != 0x01); //If conversion is not ready restart the Do process
	}
	
  return conversiondata;
	
}




