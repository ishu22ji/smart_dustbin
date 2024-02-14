#include <Servo.h>

const int trigPin = 2;   // Ultrasonic sensor trigger pin
const int echoPin = 3;    // Ultrasonic sensor echo pin
const int ledPin = 13;    // Built-in LED pin
const int servoPin = 4;   // Servo motor control pin

Servo servo;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  servo.attach(servoPin); // Attach servo to its pin
  servo.write(0);         // Initialize the servo position
}

void loop() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigger pin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  float distance = duration * 0.034 / 2;

  if (distance > 5 && distance < 20) {
    // If motion is detected in medium range
    Serial.println("Motion Detected!");
    digitalWrite(ledPin, HIGH);  // Turn on LED
    
    // Open the dustbin lid by turning the servo motor
    servo.write(0);  // Adjust the angle as needed
    
    delay(4000);  // Delay to keep the lid open for a moment
  } else {
    // If no motion is detected
    Serial.println("Nothing Detected");
    digitalWrite(ledPin, LOW);   // Turn off LED
    
    // Close the dustbin lid by turning the servo motor back
    servo.write(160);  // Adjust the angle as needed
    
    delay(100);  // Small delay before next measurement
  }
}

