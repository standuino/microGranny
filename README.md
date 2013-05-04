      ::::READ ME::::
::::MICROGRANNY_OPEN_FILES::::

microGranny Information: http://www.standuino.eu/devices/instruments/microgranny/

:::Uploading the software::::

-to upload software of microGranny you need to download and install Arduino environment http://arduino.cc/en/Main/Software
-if you are using FTDi usb connector to interface with Standuino you should have driver for FTDi installed  http://www.ftdichip.com/FTDrivers.htm
-in Arduino environment select - board>Arduino UNO (this refers to the bootloader of your chip)
-install the modified version of WaveHC library to your Arduino http://arduino.cc/en/Guide/Libraries

-open Arduino environment and open microGranny sketch - now you should see the source code of microGranny
-select right serial port (see Arduino website for differences between different OS)
-click upload button and wait until the software says DONE UPLOADING
-if there is a problem uploading check your soldering and follow troubleshooting at Arduino website

-to format EEPROM memory for proper use with the device hold down all 4 big trigger buttons while turning the device ON (on microGranny the display should say "CLR" fra/frau Angelico an led ADSR / PLAY should blink several times , pause and blink several times again)



::::Preparing the microSD card and samples::::

-Of course you can use your own sounds and you can use any microSD card you want. Before you use the card it is advised to format it with the official formater to make it work faster. The original SD formater can be found here with the instructions: www.sdcard.org/downloads
-You can use any microSD card reader that shows the card in your computer as and external drive.
-You can use the samples from the Samples folder

-The samples for microGranny have to be wav files, Mono, 16 or 8 bit and with a sample rate of 22050 Hz
-To convert your samples into such a format you can use the free software Audacity
http://audacity.sourceforge.net/
-In Audacity Open your file, when it is Stereo use Track > Stereo Track to Mono

-Then change the Project Rate (bottom left corner) to 22050 and then go to File > Export

-In the Format drop down choose “Wave (Microsoft) signed 16 bit PCM” and use a name which has two letters only, use A-Z and 0-9 letters.

-Copy the file to the root directory on the SD card and everything should be ready to be played by the sampler.

::::circutBoard::::
made with Fritzing
to view go to http://fritzing.org/download/
the second part of the device is Standuino 2.2 for more see: http://www.standuino.eu/devices/standuino/

::::schematics::::
doesn`t exist yet, i have to draw it, but based on waveshield by Adafruit
http://www.ladyada.net/make/waveshield/


And don`t forget...don`t make your money with it. Hack it modify it but don`t steal it.

I have no idea what the opensource hardware licence it is but you might know.

We are too lame to be proper gituHub opensource whatever, so if you know how to help us do it! 
standuino@gmail.com


So what is the difference between Sampling and Dumpling?
find out more at www.standuino.eu

