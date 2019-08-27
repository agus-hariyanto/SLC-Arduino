//******************************************************//
// Ambient Light Sensor
// Sample Code 1 [Control the ambient light sensor]
//                                      - Kyung-Sik Jang//
//******************************************************//

//******************************************************//
// Hardware Configuration
//  - Connect IoT Starter Kit and Ambient Light Sensor Module
//******************************************************//
#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

#define LIGHT A3
#define WIFI_SSID   "ICT-LAB-2.4G"                       
#define WIFI_PASS   "12345678" 

IoTMakers g_im;

#define deviceID    "agush4D1566872043819"            
#define authnRqtNo  "vqodlqqvw"            
#define extrSysID   "OPEN_TCP_001PTL001_1000007613"   
#define TAG_ID "LDR"

int BUZZER = 6;
int batas;
void setup() {
  int value = analogRead(LIGHT);
  int data = map(value, 0, 1023, 1023, 0);

  Serial.begin(9600);

  pinMode(LIGHT, INPUT);
  pinMode(BUZZER, OUTPUT);
  batas = data-50;
  init_iotmakers();
}

void loop() {
//******************************************************//
  
  static unsigned long tick = millis();

 // Reconnect if platform connection is terminated
  if(g_im.isServerDisconnected() == 1) 
  {
    init_iotmakers();
  } 
  

  //tambahan ke wifi
 
 if((millis() - tick) > 1000)
  {
    send_ldr();
    tick = millis();
  }
  

  // IoTMakers 플랫폼 수신처리 및 keepalive 송신
  // IoTMakers platform processing receive and keepalive transmission
  g_im.loop();
 
}

//koneksi ke IOT Make
void init_iotmakers()
{
  while(1)
  {
    Serial.print(F("Connect to AP..."));
    while(g_im.begin(WIFI_SSID, WIFI_PASS) < 0)
    {
      Serial.println(F("retrying"));
      delay(100);
    }

    Serial.println(F("Success"));

    g_im.init(deviceID, authnRqtNo, extrSysID);
  
    Serial.print(F("Connect to platform..."));
    while(g_im.connect() < 0)
    {
      Serial.println(F("retrying."));
      delay(100);
    }
    Serial.println(F("Success"));
  
    Serial.print(F("Auth..."));
    if(g_im.auth_device() >= 0)
    {
      Serial.println(F("Success..."));
      return;
    }
  }
}

int send_ldr()
{

 int value = analogRead(LIGHT);

  // Map Function : map(value, fromLow, fromHigh, toLow, toHigh)
  // - In programming, you sometimes need to change a range of values.
  //   For example, in Arduino, when you want to output the
  //   potentiometer analog input value (0 ~ 1023) as PWM value (0 ~ 255)
  //   to control the brightness of the LED, you have to adjust the
  //   range of the input value to the output value range.
  //   It is called Mapping.
  // - Parameter 1 [value]    : analog input value
  // - Parameter 2 [fromLow]  : lower bound of current range value
  // - Parameter 3 [fromHigh] : upper bound of the current range value
  // - Parameter 4 [toLow]    : lower bound of target range value
  // - Parameter 5 [toHigh]   : upper bound of the target range value

  // The Ambient light sensor measures low voltage when it is bright
  // and high voltage when it is dark.
  int data = map(value, 0, 1023, 1023, 0);
  Serial.print("LIGHT : ");
  Serial.println(data);
   if(g_im.send_numdata(TAG_ID, (double)data) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
  if (data < batas-50 )
  {
    //tone(BUZZER, 400);
    Serial.println("ada sentuhan");
    delay(1000);
  } 
  
  delay(1000);
  noTone(BUZZER);
  return 0;
}
