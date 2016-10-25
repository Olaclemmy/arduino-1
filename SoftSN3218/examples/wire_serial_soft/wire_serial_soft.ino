#include <SoftwareWire.h>
#include <Wire.h>
#include "sn3218.h" 
// call the sn3218 constructor without arguments to use the hardware I2C pins
// call it with the numbers of sda_pin and scl_pin to run soft I2C
sn3218 sn3218_1(8,9);
sn3218 sn3218_2(10,9);
void setup()
{
  Serial.begin(9600);
  Serial.println("Hello World");
  //while(!Serial){}; // For Arduino Leonardo
  sn3218_1.begin();
  sn3218_1.enable_leds(SN3218_CH_ALL);
  sn3218_2.begin();
  sn3218_2.enable_leds(SN3218_CH_ALL);
}

void loop()
{
  Serial.println("Enter brightness...");

  while(!Serial.available()){};

  unsigned char brightness = Serial.parseInt();

  int i;
  for( i = 0; i < SN3218_NUM_CHANNELS; i++ ){
    sn3218_1.set(i,brightness);
    sn3218_2.set(i,brightness);
  }
  sn3218_1.update();
  sn3218_2.update();

  Serial.print("Brightness set to: ");
  Serial.println(brightness);
}
