#include <rn2483.h>

/*
 * Author: JP Meijers
 * Date: 2016-02-07
 * 
 * Transmit a one byte packet via TTN. This happens as fast as possible, while still keeping to 
 * the 1% duty cycle rules enforced by the RN2483's built in LoRaWAN stack. Even though this is 
 * allowed by the radio regulations of the 868MHz band, the fair use policy of TTN may prohibit this.
 * 
 * CHECK THE RULES BEFORE USING THIS PROGRAM!
 * 
 * CHANGE ADDRESS!
 * Change the address this device should use to either a testing address or one from a range you "own".
 * The appropriate line is "myLora.initTTN("XXXXXX");
 * 
 * Connect the RN2483 as follows:
 * RN2483 -- Arduino
 * Uart TX -- 10
 * Uart RX -- 11
 * Reset -- 12
 * Vcc -- 3.3V
 * Gnd -- Gnd
 * 
 * If you use an Arduino with a free hardware serial port, you can replace 
 * the line "rn2483 myLora(mySerial);"
 * with     "rn2483 myLora(SerialX);"
 * where the parameter is the serial port the RN2483 is connected to.
 * Remember that the serial port should be initialised before calling initTTN().
 * For best performance the serial port should be set to 57600 baud, which is impossible with a software serial port.
 * If you use 57600 baud, you can remove the line "myLora.autobaud();".
 * 
 */

String str;

unsigned long time = 0;

//create an instance of the rn2483 library, 
rn2483 myLora(Serial1);

// the setup routine runs once when you press reset:
void setup() {
  //output LED pin
  pinMode(13, OUTPUT);
  led_on();

  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  Serial.println("Startup");

  Serial.print("autobauding...");
  Serial1.begin(9600);
  myLora.autobaud();
  Serial.println("done!");

  //print out the HWEUI so that we can register it via ttnctl
  Serial.println("When using OTAA, register this DevEUI: ");
  Serial.println(myLora.hweui());
  Serial.println("RN2483 version number:");
  Serial.println(myLora.sysver());
  
  //ABP: init(String AppEUI, String NwkSKey, String AppSKey, String addr);
  myLora.init("70B3D57ED0000A91", "706D1AC808CCDFB986E07CC651555EFC", "D9BEDF84504046327014E8D934AE5CD4", "B03C701C");
  
  //OTAA: init(String AppEUI, String AppKey);
  //myLora.init("70B3D57ED00001A6", "A23C96EE13804963F8C2BD6285448198");

  //transmit a startup message
  myLora.txUncnf("Fast TXer (TTN)");

  led_off();
  delay(2000);
}

// the loop routine runs over and over again forever:
void loop() {
    
    led_on();

    Serial.println("TXing");
    myLora.txUncnf("!"); //one byte, blocking function
    
    led_off();
    delay(200);
}

void led_on()
{
  digitalWrite(13, 1);
}

void led_off()
{
  digitalWrite(13, 0);
}

