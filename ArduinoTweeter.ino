/*
Kenneth Jung
2B Mechatronics Engineering
https://github.com/k22jung
*/

bool cycle = true;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); // Cycle
  pinMode(11, OUTPUT); // Green
  pinMode(10, OUTPUT); // Blue
  pinMode(9, OUTPUT); // Red
}

void loop() {
  
  // Cycle lighting
  while(Serial.available() == 0 && cycle){
     /*fade1(11, "Green");
     fade2(11,10, "Light Blue");
     fade1(10, "Blue");
     fade2(10,9, "Violet");
     fade1(9, "Red");
     fade2(9,11, "Yellow");
     fade3(11,10,9, "White");*/
     digitalWrite(13, HIGH);
     delay(500);
     digitalWrite(13, LOW);
     delay(500);
  }

  // Receive a byte from Python
  int response = Serial.read();

  cycle = false;

  // Set color if read is valid, otherwise cycle
  if (response == 'G'){
    fadeSerial(11);
  } else if (response == 'B'){
    fadeSerial(10);
  } else if (response == 'L') {
    fadeSerial2(11,10);
  } else if (response == 'R') {
    fadeSerial(9);
  } else {
    cycle = true;
  }

}



// ************ LED Functions ************

void fadeSerial (int pin){

  for (int b = 0; b < 255; ++b){
    analogWrite(pin, b);
    delay(10);
  }

  analogWrite(pin, 255);
  
  while(Serial.available() == 0);

  for (int b = 254; b > 0; --b){
    analogWrite(pin, b);
    delay(10);
  }

  analogWrite(pin, 0);
  
}

void fadeSerial2 (int pin1, int pin2){

  for (int b = 0; b < 255; ++b){
    analogWrite(pin1, b);
    analogWrite(pin2, b);
    delay(10);
  }

  analogWrite(pin1, 255);
  analogWrite(pin2, 255);
  
  while(Serial.available() == 0);

  for (int b = 254; b > 0; --b){
    analogWrite(pin1, b);
    analogWrite(pin2, b);
    delay(10);
  }

  analogWrite(pin1, 0);
  analogWrite(pin2, 0);
  
}

void fade1 (int pin, String msg){
  int b = 0;
  int fade = 1;
  bool exit = false;
  Serial.println (msg);
  
  
  while (true){
    analogWrite(pin, b);
    delay (10);

    b += fade;
    
    if (b >=255){
       fade *= -1;
       b = 255;
       exit = true;
    } else if (b <= 0 && exit) {
      analogWrite(pin, 0); //For the case that 255 isn't divisible by fade (invalid values)
      return;
    }
  }
  
}

void fade2 (int pin1, int pin2, String msg){
  int b = 0;
  int fade = 1;
  bool exit = false;
  Serial.println (msg);
  
  while (true){
    analogWrite(pin1, b);
    analogWrite(pin2, b);
    delay (10);

    b += fade;
    
    if (b >=255){
       fade *= -1;
       b = 255; // Ensures valid values for AnalogWrite.
       exit = true;
    } else if (b <= 0 && exit) {
      analogWrite(pin1, 0); // For the case that 255 isn't divisible by fade (invalid values)
      analogWrite(pin2, 0);
      return;
    }
  }
  
}

void fade3 (int pin1, int pin2, int pin3, String msg){
  int b = 0;
  int fade = 1;
  bool exit = false;
  Serial.println (msg);
  
  while (true){
    analogWrite(pin1, b);
    analogWrite(pin2, b);
    analogWrite(pin3, b);
    delay (10);

    b += fade;
    
    if (b >=255){
       fade *= -1;
       b = 255; // Ensures valid values for AnalogWrite.
       exit = true;
    } else if (b <= 0 && exit) {
      analogWrite(pin1, 0); // For the case that 255 isn't divisible by fade (invalid values)
      analogWrite(pin2, 0);
      analogWrite(pin3, 0);
      return;
    }
  }
  
}
