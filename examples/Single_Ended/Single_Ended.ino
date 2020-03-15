#include <Wire.h>
#include <ADS1100.h>
/*TI ADS1100 is a 16 bit Single Channel 6 Pin I2C ADC.
It uses the voltage Suppled to the chip as the VREF.
It has a factory programed I2C address and comes in 8 Flavors.*/


ADS1100A0 ads;   //TI ADS1100 A0 Version (0x48)
//ADS1100A1 ads; //TI ADS1100 A1 Version (0x49)
//ADS1100A2 ads; //TI ADS1100 A2 Version (0x4A)
//ADS1100A3 ads; //TI ADS1100 A3 Version (0x4B)
//ADS1100A4 ads; //TI ADS1100 A4 Version (0x4C)
//ADS1100A5 ads; //TI ADS1100 A5 Version (0x4D)
//ADS1100A6 ads; //TI ADS1100 A6 Version (0x4E)
//ADS1100A7 ads; //TI ADS1100 A7 Version (0x4F)
void setup() {
  Serial.begin(9600);
  Serial.println("Hello!");

  Serial.println("Texas Insturments ADS1100 ADC");
  Serial.println("ADC RANGE: 0V-VDD When Gain = 1");
  
  // Set the Gain on the ADC
  ads.setGain(GAIN_ONE);  //1X Gain 0-Vref
  //ads.setGain(GAIN_TWO); //2X Gain 0-Vref/2
  //ads.setGain(GAIN_FOUR); // 4x Gain 0-Vref/4
  //ads.setGain(GAIN_EIGHT);// 8x Gain 0-Vref/8
  //Set the Data Sample Rate
  ads.setSPS(SPS_8);  //Bit Resusltion = 16
  //ads.setSPS(SPS_16);//Bit Resusltion = 15
  //ads.setSPS(SPS_32);//Bit Resusltion = 14
  //ads.setSPS(SPS_128);//Bit Resusltion = 12
  ads.begin();
  
}
/**********************************************************
 Single Endeded mode at 8SPS
 8 SPS = 16 Bit Resultion
 Single ended mode loses 1 bit
    Conversion Factor = (Vref/Gain) /2^(16-1)
    Vdd = 5V
      Conversion Factor = (5V)/2^15 bits
      Conversion Factor = .152588mV/bit
    Vdd = 3.3V (Qwiic Connector)
      Conversion Factor = (3.3V)/2^15 bits
      Conversion Factor = .100708mV/bit
 */
void loop() {
  //float cf = 0.152588F;
  float cf = .100708F;
  int16_t results = ads.readADC(); //Read the ADC in Single Coversion Mode
  Serial.print("Differential: "); 
  Serial.print(results); 
  Serial.print("("); 
  Serial.print((results * cf)/1000); 
  Serial.println("V)");
 
  delay(200);  
}
