#include <Wire.h>
#include <ADS1100.h>
//Input Voltage
//This determins The Max Voltage Range and the VRef 
const float Vref = 5;  
ADS1100A0 ads;   //TI ADS1100 A0 Version
//ADS1100A1 ads; //TI ADS1100 A1 Version
//ADS1100A2 ads; //TI ADS1100 A2 Version
//ADS1100A3 ads; //TI ADS1100 A3 Version
//ADS1100A4 ads; //TI ADS1100 A4 Version
//ADS1100A5 ads; //TI ADS1100 A5 Version
//ADS1100A6 ads; //TI ADS1100 A6 Version
//ADS1100A7 ads; //TI ADS1100 A7 Version
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
/*Single Endeded mode at 8SPS
 8 SPS = 16 Bit Resultion
 Single ended mode loses 1 bit
    Conversion Factor = (Vref/Gain) /2^(16-1)
    Conversion Factor = (5V)/2^15 bits
    Conversion Factor = .1526mV/bit
 */
void loop() {
  float cf = 0.1526F;
  int16_t results;
  results = ads.readADC(); //Read the ADC in Single Coversion Mode
  Serial.print("Differential: "); 
  Serial.print(results); 
  Serial.print("("); 
  Serial.print(results * cf); 
  Serial.println("mV)");
  delay(200);  
}
