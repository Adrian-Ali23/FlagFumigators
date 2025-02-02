#include <Servo.h>

// Define Color Sensor Pins
#define S0 6
#define S1 7
#define S2 8
#define S3 9
#define COLOR_OUT 10

// Define Ultrasonic Sensor Pins
#define TRIG 11
#define ECHO 12

// Define Motor Driver Pins
#define ENA 3  // PWM for Motor A
#define IN1 4
#define IN2 5
#define ENB 9  // PWM for Motor B
#define IN3 6
#define IN4 7

// Define Servo Motor for flag drop
#define SERVO_PIN 13
Servo flagServo;
int floorColour[3]; 
int currentRing = 0;
char ringOrder[5];

// Variables for Color Detection
int red = 0, green = 0, blue = 0;

// Function to Read Color
char readColor() {
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    red = pulseIn(COLOR_OUT, LOW);

    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    green = pulseIn(COLOR_OUT, LOW);

    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    blue = pulseIn(COLOR_OUT, LOW);

    floorRed = floorColour[0];
    floorGreen = floorColour[1];
    floorBlue = floorColour[2];
    
    if (red > (floorRed + 50) && red < (floorRed - 50) && green > (floorGreen + 50) && green < (floorGreen - 50) blue > (floorBlue + 50) && red < (floorBlue - 50))
    return 'F';
    if (red < green && red < blue && red < 500){
        return 'R';  // Red Detected
    } 
    if (green < red && green < blue && green < 600){
      return 'G'; // Green Detected
    }
    if (blue < red && blue < green && blue < 700)return 'B';
    else return 'N'; 
}

void floorColour(){
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    red = pulseIn(COLOR_OUT, LOW);

    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    green = pulseIn(COLOR_OUT, LOW);

    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    blue = pulseIn(COLOR_OUT, LOW);

    floorColour[0] = red;
    floorColour[1] = green;
    floorColour[3] = blue;
}


// Move Forward
void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
}

// Turn Left
void turnLeft() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(500);
}

// Turn Right
void turnRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(500);
}

// Stop Motors
void stopMotors() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

// Drop Flag using Servo
void dropFlag() {
    flagServo.write(90); // Drop flag
    delay(1000);
    flagServo.write(0);  // Reset position
}

void setup() {
    Serial.begin(9600);

    // Initialize Motor Pins
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    // Initialize Ultrasonic Sensor Pins
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    // Initialize Color Sensor Pins
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(COLOR_OUT, INPUT);

    // Set Color Sensor Scaling
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

    // Attach Servo
    flagServo.attach(SERVO_PIN);
    floorColour();
}

void loop() {
    moveForward();
    char currentColour = '';
    while(currentColour == 'F' || currentColour == 'N'){
      currentColour = detectColour();
    }
    ringOrder[0]

}

