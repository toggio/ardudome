<?php

/*

ArduDome 0.9
Domotic with Arduino + RaspberryPI + PHP + JSON + jQuery
Opensource platform and browser-independent web based Arduino bidirectional remote control & sensors
by Luca Soltoggio
15/03/2013
http://arduinoelettronica.wordpress.com/

THIS IS JUST THE PHP PART

This script communicate with jQuery page and Arduino for getting and setting PIN status.
If invoked without parameters (like http://www.yoursite.com/ardudome.php) it returns a json string
with status of digital output and value of analog input.
For example:
{"02":0,"03":0,"04":0,"05":0,"06":0,"07":0,"08":0,"09":0,"10":0,"11":0,"12":0,"13":0,"14":756,"15":745,"16":722,"17":679,"18":634,"19":494}
If invoked with the GET method it use two parameters: "pin" (from P02 to P13) and "cmd" (0 or 1).
For example http://www.yoursite.com/ardudome.php?pin=P13&cmd=1, will send the following command "/*CMD13H" to Arduino
putting Digital Port 13 in "High" status.
This script is designed to work with his jQuery script, but it could be integrated in other prjects using the syntax above.
If used with his original jQuery script, it will automatically get "pin" and "cmd" from web page modules.

*/

error_reporting(E_ALL);
ini_set('display_errors', '1');
require ('php_serial.class.php');

// Inizialize message string to send to Arduino
$message="/";

// If is coming some command from jQuery web page convert name like "P03" in "03" and value like "1" in "H"
if (isset($_GET['pin']) && isset($_GET['cmd'])) {
    if ($_GET['cmd']=="0") $gcmd="L"; elseif ($_GET['cmd']=="1") $gcmd="H"; else $gcmd="/";
    if ((strlen($_GET['pin'])==3) && (substr($_GET['pin'],0,1)=="P")) {
        if (intval(substr($_GET['pin'],-2))<=13 && intval(substr($_GET['pin'],-2))>=2) $gpin=substr($_GET['pin'],-2); else $gpin="";
    $message="/*CMD".$gpin.$gcmd."/";   // create message string
    }
}

// initialize serial port
$serial = new phpSerial;
$serial->deviceSet("/dev/ttyACM0");
$serial->confBaudRate(38400);
$serial->confParity("none");
$serial->confCharacterLength(8);
$serial->confStopBits(1);
$serial->deviceOpen();

// create message for sending and getting data to Arduino
for ($i = 2; $i<=19; $i++) {

   $pin = sprintf('%02s', $i);
   $message=$message."*CMD".$pin."V/";
}

$serial->sendMessage($message);
$read= $serial->readPort();

$serial->deviceClose();

$tempArray=explode("\n\n",$read,18);

// create array with read values
for ($i = 2; $i<=19; $i++) {

   $pin = sprintf('%02s', $i);
   $myArray[$pin]=intval(str_replace("\n","",$tempArray[$i-2]));
}

// creato json string
echo json_encode($myArray);

?>
