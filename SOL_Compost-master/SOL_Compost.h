/*
 SOL_Compost.h - Library for composter variable monitoring
  Created by A.Gordillo-Guerrero, Nov, 2022.
  Released into the public domain.

Include:

- Temperature and Humidity control using one DHT sensor
- Lecture of four analog channels using Adafruit_ADS1015 and I2C protocol
- Reading of battery voltaje using one ADC channel.
- Reading of a digital or capacitive button using one input pin.
- Reading of a digital or capacitive button using one input pin.



*/

#ifndef SOL_Compost_h
#define SOL_Compost_h

//#include "Arduino.h"
#include "Wire.h" // for IMU 6050 control
#include "I2Cdev.h"
#include "Adafruit_ADS1X15.h"
#include "DHT.h"


class Composter
{

 public:
   //////// Constructor //////////////////

   Composter(int DHTPin, int buttonPin, int relayPin);


   ///////////////////////////////////////
   //////// Attributes  //////////////////
   ///////////////////////////////////////
   //// Physical variable ////
   // DHT temperature and humidity values
   DHT dht ;
   float T,H;

   // Battery voltage read value
   float Vbat;

   // Weight read values
   int weight;

   // correct measure flags
   uint8_t flagVbat=0; // flag 1 when battery voltage is correct to open relays (marked by VbatUpperThresh and VbatLowerThresh )
   uint8_t flagH=0; // flag 1 when humidity is correct (marked by H_UpperThresh and H_LowerThresh )
   uint8_t flagT=0; // flag 1 when temperature is correct (marked by T_UpperThresh and T_LowerThresh )
   uint8_t flagWeight=0; // flag 1 when weight is correct (marked by WeightUpperThresh and WeightLowerThresh )
   uint8_t flagDebounce=0; // flag to measure to consecutive capacitive touch button events

   int CapThresh=7; // Threshold for capacitive button

   // Threshold values for correction measurements flags
   int T_UpperThresh=55; // Threshold for upper pressure
   int T_LowerThresh=2; // Threshold for lower pressure
   int H_UpperThresh=105; // Threshold for upper pressure
   int H_LowerThresh=3; // Threshold for lower pressure
   int WeightUpperThresh=250; // Threshold for upper height
   int WeightLowerThresh=1; // Threshold for lower height
   int VbatUpperThresh=16; // Threshold for upper battery voltage
   int VbatLowerThresh=11; // Threshold for lower battery voltage


    ///////////////////////////////////////
    //////// Methods  //////////////////
    ///////////////////////////////////////

    void init();
    void getStatus();
    void readandcheckAll();
    void readDHT();
    void readVbat_I2C();
    void readWeight_I2C_onesample();
    void readWeight_I2C_Nsamples(int);
    void readButton();
    void checkVbat();
    void checkH();
    void checkT();
    void checkWeight();
    void turnRelayOFF();
    void analogbuttonpressed();


 private:
    int _DHTPin;
    int _buttonPin;
    int _relayPin;

};

#endif
