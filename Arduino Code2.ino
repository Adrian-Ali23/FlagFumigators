#include <Servo.h>

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

const int trigPin = 9;
const int echoPin = 10;
const int clawmotorPin = 11;
const int rightMotorPin1 = 13;
const int rightMotorPin2 = 12;
const int leftMotorPin1 = 3;
const int leftMotorPin2 = 2;
const int colourPin = A0;
String colourPatttern[5];
bool isFinalCircle = false; 

// Servo myservo;
int pos = 0;
bool clawopen = false;

long duration;
int distance;

void setup(){

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  // Attach the servo and set up serial
  // myservo.attach(clawmotorPin);
  Serial.begin(9600);

  // Set pin modes
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency scaling to 20% on the TCS3200
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Optional servo sweep at startup:
  // for (pos = 0; pos <= 180; pos += 1) {
  //   myservo.write(pos);
  //   delay(15);
  // }
}

void loop(){

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
    
  int red, green, blue;
  
  // Ultrasonic distance measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Read colors from TCS3200
  // Read Red
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  red = pulseIn(sensorOut, LOW);

  // Read Green
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  green = pulseIn(sensorOut, LOW);

  // Read Blue
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blue = pulseIn(sensorOut, LOW);

  // Print RGB values
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print(" Green: ");
  Serial.print(green);
  Serial.print(" Blue: ");
  Serial.println(blue);

  // Determine color
  String color = detectColor(red, green, blue);
  Serial.print("Detected Color: ");
  Serial.println(color);

  // Print distance
  Serial.print("Distance: ");
  Serial.println(distance);

  delay(1000);

  while(!isFinalCircle){
    digitalWrite(motor1Pin1, HIGH);
    
  }
}

char detectColor(int r, int g, int b) {
  /*
  if (r < g && r < b) {
    return "Red";
  } else if (g < r && g < b) {
    return "Green";
  } else if (b < r && b < g) {
    return "Blue";
  } else if (r < 50 && g < 50 && b < 50) {
    return "Black";
  } else if (r > 200 && g > 200 && b > 200) {
    return "White";
  } else {
    return "Unknown";
  }
  */
  float total = r + g + b;
  float r_ratio = r / total;
  float g_ratio = g / total;
    float b_ratio = b / total;

    if (r_ratio > 0.5 && g_ratio < 0.3 && b_ratio < 0.3) {
        return 'r';
    } else if (g_ratio > 0.5 && r_ratio < 0.3 && b_ratio < 0.3) {
        return 'g';
    } else if (b_ratio > 0.5 && r_ratio < 0.3 && g_ratio < 0.3) {
        return 'b';
    } else {
        return 'u';
    } 
}
