ArduDome
========
<b>Domotic with Arduino + RaspberryPI + PHP + JSON + jQuery.</b><br>
Opensource platform and browser-independent web based Arduino bidirectional remote control &amp; sensors. (Smartphone optizimized)<br>

Quick Start
-----------

1 - Download all the zip files<br>
2 - Load the sketch ArduDome.ino in your Arduino UNO board<br>
3 - Put a 10uF capacitor between GND and RESET (this will disable autoreset feature on serial open)<br>
4 - Connect you Arduino UNO through USB port to your RaspberryPI (or any other Linux PC) with apache and php preinstalled<br>
5 - Put all files (except for Ardudome.ino and functions.ino) in your www directory (usually /var/www)<br>
6 - Verify the name of your USB serial port (usually /dev/ttyACM0) and change it in ardudome.php ($serial->deviceSet("/dev/ttyACM0");)<br>
7 - Give the user www-data permission for dialout (usermod -a -G dialout www-data)<br>
8 - Verify connection (php ardudome.php)<br>
9 - Open your web browser from smartphone or PC to http://yourraspberryip/ardudome.html<br>

Enjoy!

http://www.arduinoelettronica.com

by Luca Soltoggio

## Help us

If you find this project useful and would like to support its development, consider making a donation. Any contribution is greatly appreciated!

**Bitcoin (BTC) Address:** `3Ctmurhy18PmkTKPa2s7PjfAKzR8ZBj8Na`
