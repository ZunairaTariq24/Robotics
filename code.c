#include <Servo.h>

// --- Pin Definitions ---
// L293D Motor Driver Control Pins
const int motorLeftA = 3; // Input 1 -> Controls Left Motor Forward
const int motorLeftB = 4; // Input 2 -> Controls Left Motor Backward
const int motorRightA = 5; // Input 3 -> Controls Right Motor Forward
const int motorRightB = 6; // Input 4 -> Controls Right Motor Backward

// Servo Motor Signal Pins
const int servoFirstPin = 8; // First Servo (Sweep Arm)
const int servoSecondPin = 10; // New Second Servo 

// --- Object & Variable Initialization ---
Servo armServo; // First servo object
Servo secondServo; // New second servo object

char command = '9'; // Stores incoming Bluetooth characters (Defaults to '9' / STOP)
int servoPos = 0; // Tracks the current angle of the first servo
bool isServoSweeping = false; // Toggles the continuous automatic servo movement

void setup() {
  // 1. Configure Motor Driver Pins as Outputs
  pinMode(motorLeftA, OUTPUT);
  pinMode(motorLeftB, OUTPUT);
  pinMode(motorRightA, OUTPUT);
  pinMode(motorRightB, OUTPUT);

  // 2. Attach and Center BOTH Servo Motors
  armServo.attach(servoFirstPin);
  armServo.write(90); // Center first servo to 90 degrees
  
  secondServo.attach(servoSecondPin);
  secondServo.write(90); // Center second servo to 90 degrees

  // 3. Start Serial Communication at 9600 Baud
  Serial.begin(9600);
  
  Serial.println("--- ROBOT INITIALIZED WITH 2 SERVOS ---");
  Serial.println("Waiting for Bluetooth commands...");

  // 4. Ensure everything starts fully stopped
  moveStop();
}

void loop() {
  // STEP 1: Listen for Incoming Bluetooth Commands from your phone
  if (Serial.available() > 0) {
    command = Serial.read(); // Read the single character sent over Bluetooth
    
    // Print the received character to your laptop screen for easy debugging
    Serial.print("Command Received: ");
    Serial.println(command);
    
    // Process the command
    switch (command) {
      case '7':  
        Serial.println("Action: Moving Chassis FORWARD");
        moveForward();
        isServoSweeping = false;
        break;
        
      case '8':  
        Serial.println("Action: Moving Chassis BACKWARD");
        moveBackward();
        isServoSweeping = false;
        break;
        
      case 'L':  
        Serial.println("Action: Turning Chassis LEFT");
        turnLeft();
        isServoSweeping = false;
        break;
        
      case 'R':  
        Serial.println("Action: Turning Chassis RIGHT");
        turnRight();
        isServoSweeping = false;
        break;
        
      case '9':  
        Serial.println("Action: STOPPING All Wheels");
        moveStop();
        isServoSweeping = false;
        break;

      case '1':  
        Serial.println("Action: Activating Continuous SERVO 1 SWEEP");
        isServoSweeping = true;
        break;

      case '2':  
        Serial.println("Action: STOPPING Servo 1 & Centering");
        isServoSweeping = false;
        armServo.write(90);
        break;

      case '3':  
        Serial.println("Action: Moving Servo 2 to 0 Degrees");
        secondServo.write(0);
        break;

      case '4':  
        Serial.println("Action: Moving Servo 2 to 180 Degrees");
        secondServo.write(180);
        break;

      default:
        Serial.println("Warning: Unrecognized Command Received!");
        break;
    }
  }

  // STEP 2: Automatic Non-Blocking Servo 1 Sweeper Loop
  if (isServoSweeping) {
    // Sweep from 0 up to 180 degrees
    for (servoPos = 0; servoPos <= 180; servoPos += 2) {
      if (Serial.available() > 0) break; // Drop out immediately if a new command arrives
      armServo.write(servoPos);
      delay(15); 
    }
    // Sweep back down from 180 to 0 degrees
    for (servoPos = 180; servoPos >= 0; servoPos -= 2) {
      if (Serial.available() > 0) break; // Drop out immediately if a new command arrives
      armServo.write(servoPos);
      delay(15);
    }
  }
}

// --- Directional Driver Functions ---

void moveForward() {
  digitalWrite(motorLeftA, HIGH);
  digitalWrite(motorLeftB, LOW);
  digitalWrite(motorRightA, HIGH);
  digitalWrite(motorRightB, LOW);
}

void moveBackward() {
  digitalWrite(motorLeftA, LOW);
  digitalWrite(motorLeftB, HIGH);
  digitalWrite(motorRightA, LOW);
  digitalWrite(motorRightB, HIGH);
}

void turnLeft() {
  digitalWrite(motorLeftA, LOW);
  digitalWrite(motorLeftB, HIGH);
  digitalWrite(motorRightA, HIGH);
  digitalWrite(motorRightB, LOW);
}

void turnRight() {
  digitalWrite(motorLeftA, HIGH);
  digitalWrite(motorLeftB, LOW);
  digitalWrite(motorRightA, LOW);
  digitalWrite(motorRightB, HIGH);
}

void moveStop() {
  digitalWrite(motorLeftA, LOW);
  digitalWrite(motorLeftB, LOW);
  digitalWrite(motorRightA, LOW);
  digitalWrite(motorRightB, LOW);
}
