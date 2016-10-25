## arduino
Helper libraries for Arduino projects

# Soft SN3218
SN3218 is a great inexpensive PWM controller with 18 channels, sold as a breakout board by Pimoroni, and as a standalone chip eg on Aliexpress. 

Unfortunately its I2C address is hardwired, meaning you can only run one of them with the hardware I2C bus.

To overcome this limitation, I modified the Pimoroni-supplied library to also make it work with the SoftSerial library, allowing to run N soft I2C buses using any N+1 free pins (if you share the scl pin)
