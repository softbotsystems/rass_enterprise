#include <Wire.h>
#include <SdFat.h>
#include <Wiegand.h>
#include <easyscheduler.h>

Schedular updater;
Schedular validator;

WIEGAND wg;
long code;

#define TOTAL_USERS 10
#define SITE 10

static long rfid[TOTAL_USERS];
static int access[TOTAL_USERS];
static int index;

#include "storage.h"
#include "rfid.h"

void setup()
{        
	Wire.begin(4);
	Wire.onReceive(receiveEvent);
    Serial.begin(19200);
    index = 0;
    for(int x=0; x<TOTAL_USERS; x++){
        access[x] = 0;
    }
    connectToSD();
    initConfig();
    initRfid();
    updater.start();
    validator.start();
}

void printSlaveData(){
	for(int i=0; i<TOTAL_USERS; i++){
	    Serial.print("User ");
	    Serial.print(i);
	    Serial.print(" has rfid ");
	    Serial.print(rfid[i]);
	    Serial.println();
	}
}

void loop()
{
	delay(1000);
	updater.check(updateConfig, 10000);
	validator.check(checkRfid, 1);
}

void receiveEvent(int howMany)
{
	String digits;
	int count = 0;
	
	int i = 0;
	index = Wire.read();
    while(1 < Wire.available()) {
	  digits = digits + Wire.read();	  
	  i++;
	}
	digits = digits + Wire.read();
	char temp[9];
	for(int z=0; z<9; z++){
	    temp[z] = digits[z];
	}
	rfid[index] = atol(temp);
	// Serial.println(rfid[index]);
	// updateConfig();
}
