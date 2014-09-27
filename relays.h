int relays[TOTAL_RELAYS];
int statuses[TOTAL_RELAYS];

void initRelays(){
	Serial.println("Initializing Relays");
	for(int i=0; i<TOTAL_RELAYS; i++){
		statuses[i] = 0;
	    relays[i] = (22+i);
	    pinMode(relays[i], OUTPUT);
	}
}

void turnOnRelay(int id){
	digitalWrite(relays[id], LOW);
	delay(100);
}

void turnOffRelay(int id){
	digitalWrite(relays[id], HIGH);
	delay(100);
}

void toggleSwitch(int id){
	if(statuses[id]){
	    statuses[id] = 0;
	    turnOffRelay(id);
	}else{
		statuses[id] = 1;
		turnOnRelay(id);
	}
}

int getRelayStatus(int id){
	return statuses[id];
}

void showRelayData(){
	for(int i=0; i< TOTAL_RELAYS; i++){
		Serial.print("relay ");
		Serial.print(i);
		Serial.print(" is ");
	    Serial.println(statuses[i]);
	}
}

boolean isDoorOpen(){
    return statuses[0];
  }

  boolean isLightOn(){
    return statuses[1];
  }

  boolean isAlarmOn(){
    return statuses[2];
  }

  boolean isGeneratorOn(){
    return statuses[3];
  }

  boolean isAcOn(){
    return statuses[4];
  }

  boolean isMainsOn(){
    return statuses[5];
  }