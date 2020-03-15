# ADS1100  ADC Arduino Library
Library for TI's ADS1100 ADC.
		
The ADS1100 ADC is a I2C, Self-Calibrating, Differenatal, 16-Bit ADC that has its refferece voltage directly tied to the Vdd voltage.  
This done to keep the ADC small.  It uses only 6 pins in a SOT-23-6 package.  It can recored up to 128 SPS although with a lower bit rate.  
It also contains up to a 8x Gain Amplifire
[Datasheet](http://www.ti.com/lit/ds/sbas239b/sbas239b.pdf)

#Available in 8 Preprogramed I2C address

* ADS1100A0 = 0x48
* ADS1100A1 = 0x49
* ADS1100A2 = 0x4A
* ADS1100A3 = 0x4B
* ADS1100A4 = 0x4C
* ADS1100A5 = 0x4D
* ADS1100A6 = 0x4E
* ADS1100A7 = 0x4F


