10-01-2024
# Electronics Cheat Sheet

##### Everything i've been testing physically and searching on internet 

##### -> Code, Vidéos, things i found etc.
---

### Ableton Live and MAXforLive:

Note : The max for live connection kit is useful as so as the maxuino one. I didn't used it as the color sensor was sending encrypted data that couldn't be process without code.

You need to update your arduino or so into the standard firmata -> makes life more complicated as you cannot code easely into it.

The data you get from the sensor are RAW and is hard to calibrate.

Arduino/Teensy/Esp32 to ableton : https://www.youtube.com/watch?v=pBRe2xz7dgQ

Max for live connection kit : https://www.synthtopia.com/content/2016/03/24/free-max-for-live-kit-connects-ableton-live-to-arduino-mindstorms-littlebits-and-more/

https://github.com/Ableton/m4l-connection-kit/tree/main/Arduino

Arduino sensor Controller with max-msp and ableton live : https://www.hackster.io/PetrosVamvakas/arduino-sensor-controller-through-max-msp-with-ableton-live-06c0a5


---

### Adafruit 3W Class D amp : 

https://www.distrelec.ch/en/3w-class-amplifier-adafruit-3006/p/30129201?cq_src=google_ads&cq_cmp=18320642092&cq_con=&cq_term=&cq_med=pla&cq_plac=&cq_net=x&cq_pos=&cq_plt=gp&gclid=Cj0KCQiA4Y-sBhC6ARIsAGXF1g5Qu_99SGTd0GvrkiMshQF66TP-PiAr8NS5YHgeyX_eFLCZBK0RgMEaAlGHEALw_wcB&gclsrc=aw.ds

---

### Adafruit Micro-Lipo charger : 

https://www.adafruit.com/product/1904

some useful diagram based on a project : https://www.hackster.io/little_lookout/person-detection-with-tensorflow-and-arduino-47ae01

---
### Arduno-nano-BLE-33-Sense :

Note : the arduino can sometimes not be recognised in the arduino code ports. to resolve the problem : -> double click the tiny reboot button while the arduino is plugged in -> led red and green -> you can now choose a new port for your arduino.

---

### DFRobot 0.3 MegaPixels USB Camera :

https://www.dfrobot.com/product-2089.html

---
### Esp 32

saving mp3 files : https://forum.arduino.cc/t/how-to-save-mp3-file-in-sd-card-from-api-using-esp32/1033602

mp3 player : https://esp32io.com/tutorials/esp32-mp3-player

bluetooth speaker : https://www.youtube.com/watch?v=_fPgJgLfnXE


---

### ESP-32-Cam :

Note : Cool module but can only send through WiFi and i havn't found a way to stream it via USB or other.

face recognition : https://randomnerdtutorials.com/esp32-cam-video-streaming-face-recognition-arduino-ide/

Streaming video over wifi : https://www.instructables.com/ESP-32-Camera-Streaming-Video-Over-WiFi-Getting-St/


---

### Featherwing music maker synths :

Midi demo : https://www.youtube.com/watch?v=D4DvWx-1Gzc

---

### LIS3DH Accelerometer :

https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/arduino

---

### MAX-MSP :

Note : to synch max-msp midi with ableton you need to use virtual midi port (for windows i used Loopmidi)

Image to wavetable synth : https://www.maxforlive.com/library/device.php?id=5291&fbclid=IwAR1tVWFnQmYwDFyLZasqqqQTX0hgvwTimCBZ0ldcV_C76uKaFvOBAcEPMhE

Sending data between arduino and max-msp : https://maker.pro/arduino/tutorial/how-to-send-and-receive-data-between-an-arduino-and-maxmsp 

RNBO : https://cdm.link/2022/11/rnbo-max-for-web-hardware-plugin/

Scale reference : https://docs.cycling74.com/max5/refpages/max-ref/scale.html

Color position tracking : https://docs.cycling74.com/max8/tutorials/jitterchapter25

Video or webcam footages : https://www.youtube.com/watch?v=BOa0YoMD76w

arhythmic patterns : https://cycling74.com/forums/generating-arhythmic-patterns

---

### NeoPixel Ring 24 :

Dfrobot neopixel Specs : https://www.dfrobot.com/product-2542.html

With arduino nano : https://community.dfrobot.com/makelog-313679.html


---

### PixelNote IA :

https://github.com/vlall/PixelNotes

---

### Pixelsynth :

https://ojack.xyz/PIXELSYNTH/

---

### Polymer Battery 3.7V : 

Note : to use it with the adafruit microlipo and most of the arduino/esp etc ... you need to change the connection to JST.

https://www.mikroe.com/li-polymer-battery-37v-2000mah

---

### TCS230 Colorsensor : 

Note : These sensors are extreamly sensitive and also need to be calibrated. Althought pretty cool they are not useful to my project. 

interfacing with arduino uno : https://www.circuits-diy.com/interfacing-tcs230-tcs3200-color-sensor-with-arduino-uno/

Basic tutorial : https://www.youtube.com/watch?v=A-A5kRLBSn8

in depth tutorial : https://lastminuteengineers.com/tcs230-tcs3200-color-sensor-arduino-tutorial/

Calibration and code : https://github.com/MajicDesigns/MD_TCS230

https://www.instructables.com/Color-Recognition-W-TCS230-Sensor-and-Arduino-Cali/

Calibration Tutorial : https://arduinoplusplus.wordpress.com/2015/07/15/tcs230tcs3200-sensor-calibration/


---

### Teensy 4 Wifi :

Connecting to wifi :
https://forum.pjrc.com/index.php?threads/teensy-4-and-wifi.68211/

