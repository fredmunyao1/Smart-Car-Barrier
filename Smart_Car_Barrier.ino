#include <Servo.h>

// Define pins for ultrasonic sensor
const int trigPin = 2;
const int echoPin = 4;

// Define pin for servo motor
const int servoPin = 9;

// Create a servo object
Servo barrierServo;

// Variables for measuring distance
long duration;
int distance;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pin modes for ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo to the defined pin
  barrierServo.attach(servoPin);

  // Initialize servo position (barrier down)
  barrierServo.write(0);
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the ultrasonic pulse by setting trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, which returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Raise the barrier if a vehicle is detected within 20 cm
  if (distance <= 20) {
    barrierServo.write(90); // Barrier up
  } else {
    barrierServo.write(0); // Barrier down
  }

  // Wait for 500 milliseconds before the next loop
  delay(500);
}
