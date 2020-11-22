#include <RGBmatrixPanel.h>

// For LED matrix
#define CLK 11
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

// For motors
#define PWM_R 7
#define PWM_L 12
#define PWM_EXT 5
#define DIR_R 8
#define DIR_L 6
#define DIR_EXT 3
#define PWM_MAX 80

//-------- LED matrix setup --------//

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);
String text = "FRC Team 568 The Nerds of the North";
void setup() {

  Serial.begin(74880);

  // Setup LED Matrix
  matrix.begin();
  matrix.setTextSize(1);
  matrix.setTextWrap(true);

  // Set LED matrix text
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setCursor(0, 0);
  for (int i = 0; i < text.length(); ++i) {

    int wheelNum = i % 25;
    matrix.setTextColor(Wheel(wheelNum));
    matrix.print(text[i]);
    
  }

  // Pin modes
  pinMode(PWM_R, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(PWM_EXT, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(DIR_EXT, OUTPUT);

}

double multiplier = 1;
bool forward = false;
bool backward = false;
bool right = false;
bool left = false;
bool up = false;
bool down = false;

void loop() {

  // Move robot
  if (forward) {

    digitalWrite(DIR_L, HIGH);
    digitalWrite(DIR_R, HIGH);
    analogWrite(PWM_L, PWM_MAX * multiplier);
    analogWrite(PWM_R, PWM_MAX * multiplier);
    
  } else if (backward) {

    digitalWrite(DIR_L, LOW);
    digitalWrite(DIR_R, LOW);
    analogWrite(PWM_L, PWM_MAX * multiplier);
    analogWrite(PWM_R, PWM_MAX * multiplier);
    
  } else if (right) {

    digitalWrite(DIR_L, HIGH);
    digitalWrite(DIR_R, LOW);
    analogWrite(PWM_L, PWM_MAX * multiplier);
    analogWrite(PWM_R, PWM_MAX * multiplier);
    
  } else if (left) {

    digitalWrite(DIR_L, LOW);
    digitalWrite(DIR_R, HIGH);
    analogWrite(PWM_L, PWM_MAX * multiplier);
    analogWrite(PWM_R, PWM_MAX * multiplier);
    
  } else {

    digitalWrite(DIR_L, LOW);
    digitalWrite(DIR_R, LOW);
    analogWrite(PWM_L, 0);
    analogWrite(PWM_R, 0);
    
  }

  // Move extender
  if (up) {

    digitalWrite(DIR_EXT, HIGH);
    analogWrite(PWM_EXT, PWM_MAX * multiplier);
    
  } else if (down) {

    digitalWrite(DIR_EXT, LOW);
    analogWrite(PWM_EXT, PWM_MAX * multiplier);
    
  } else {

    digitalWrite(DIR_EXT, LOW);
    analogWrite(PWM_EXT, 0);
    
  }
  
  // Check for input command
  while (Serial.available() > 0) {

    // Receives data from the Pi
    String d = Serial.readStringUntil('\n');
    
    if (d == "a") {

      // Stop
      forward = false;
      backward = false;
      right = false;
      left = false;
      up = false;
      down = false;
      
    } else if (d == "b") {

      // Forward
      forward = true;
      backward = false;
      right = false;
      left = false;
      
    } else if (d == "c") {

      // Backward
      forward = false;
      backward = true;
      right = false;
      left = false;
      
    } else if (d == "d") {

      // Turn right
      forward = false;
      backward = false;
      right = true;
      left = false;
      
    } else if (d == "e") {

      // Turn left
      forward = false;
      backward = false;
      right = false;
      left = true;
      
    } else if (d == "f") {

      // Set slow
      multiplier = 0.7;
      
    } else if (d == "g") {

      // Set normal
      multiplier = 1.0;
      
    } else if (d == "h") {

      // Extend up
      up = true;
      down = false;
      
    } else if (d == "i") {

      // Retract down
      up = false;
      down = true;
      
    } else if (d == "j") {

      // Stop extender
      up = false;
      down = false;
      
    } else if (d[0] == 'k') {

      d.remove(0, 1);
      text = d;
      
      // Set LED matrix text
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.setCursor(0, 0);
      for (int i = 0; i < text.length(); ++i) {
    
        int wheelNum = i % 25;
        matrix.setTextColor(Wheel(wheelNum));
        matrix.print(text[i]);
        
      }
      
    }

  }

}

uint16_t Wheel(byte WheelPos) {
  
  if (WheelPos < 8) {
    
    return matrix.Color333(7 - WheelPos, WheelPos, 0);
  
  } else if (WheelPos < 16) {
    
    WheelPos -= 8;
    return matrix.Color333(0, 7-WheelPos, WheelPos);
  
  } else {
   
   WheelPos -= 16;
   return matrix.Color333(WheelPos, 0, 7 - WheelPos);
  
  }

}
