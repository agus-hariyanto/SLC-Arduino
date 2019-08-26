#include <HID.h>

#include <OneWire.h>
#include <DallasTemperature.h>

// Create a Onewire Referenca and assign it to pin 10 on your Arduino
OneWire oneWire(2);

// declare as sensor referenec by passing oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// declare your device address
// YOUR ADDRESS GOES HERE!!!!
//DeviceAddress tempSensor = {0x28, 0xFF, 0x2B, 0x45, 0x4C, 0x04, 0x00, 0x10};

DeviceAddress tempSensor = {0x28, 0xAC, 0xBA, 0x41, 0x0B, 0x00, 0x00, 0x63};

//Alarm Set Points
char lowSetPoint = 23;
char hiSetPoint = 26;

// A Variable to hold the temperature you retrieve
float tempC;

void setup(void)
{
  char alarmTemp;
  // start your serial port
  Serial.begin(9600);
  // Start up the DallasTemperature library
  sensors.begin();
  
  // alarm when temp is higher than value assigned to hiSetPoint
  sensors.setHighAlarmTemp(tempSensor, hiSetPoint);  
  // alarm when temp is lower than value assigned to lowSetPoint
  sensors.setLowAlarmTemp(tempSensor, lowSetPoint);
  
  // Print the alarm set points to the serial monitor
  
  // Set Measurement Resolution
  sensors.setResolution(tempSensor, 12);
  
  alarmTemp = sensors.getHighAlarmTemp(tempSensor);
  Serial.print("High Alarm is set to ");
  Serial.print(alarmTemp, DEC);
  Serial.println(" degrees C");
  
  alarmTemp = sensors.getLowAlarmTemp(tempSensor);  
  Serial.print("Low Alarm is set to ");
  Serial.print(alarmTemp, DEC);
  Serial.println(" degrees C");
}


void loop(void)
{ 
  // tell your sensor to measure the temperature
  
  sensors.requestTemperaturesByAddress(tempSensor); // Send the command to get temperatures
  Serial.print("Current Temperature is ");
  Serial.print(sensors.getTempCByIndex(0),4);
  Serial.print(" degrees C \t");
  
  // See if the temperature is above the high set point or below the low set point
  
  if (sensors.hasAlarm(tempSensor))
  {
    Serial.println("Alarm");
  }
  else{
    Serial.println("No Alarm");    
  }
  delay(1000);
}
