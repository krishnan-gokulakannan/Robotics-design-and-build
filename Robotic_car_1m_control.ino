// =====================================================
// Romeo V2 - DC Motor 1 Metre Forward Control
// =====================================================

// Motor pins
int E1 = 5;       // M1 Speed Control
int E2 = 6;       // M2 Speed Control
int M1 = 4;       // M1 Direction Control
int M2 = 7;       // M2 Direction Control

// Motor speed (0-255)
int motorSpeed = 150;

// Target distance
float distanceCM = 100.0;

// IMPORTANT:
// Calibrate this value using your actual robot.
// Example: if robot travels 100 cm in 5 seconds,
// speed = 100 / 5 = 20 cm/s.
float speedCMperSec = 20.0;


// -----------------------------------------------------
// Stop both motors
// -----------------------------------------------------
void stopMotors()
{
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
}


// -----------------------------------------------------
// Move robot forward
// -----------------------------------------------------
void moveForward(int speed1, int speed2)
{
  analogWrite(E1, speed1);
  digitalWrite(M1, LOW);

  analogWrite(E2, speed2);
  digitalWrite(M2, LOW);
}


// -----------------------------------------------------
// Move a specified distance
// -----------------------------------------------------
void moveDistance(float distance, int pwmSpeed)
{
  if (speedCMperSec <= 0)
  {
    Serial.println("ERROR: Speed is not calibrated!");
    return;
  }

  // Calculate required time
  float timeSec = distance / speedCMperSec;

  unsigned long timeMs = (unsigned long)(timeSec * 1000);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Moving for: ");
  Serial.print(timeSec);
  Serial.println(" seconds");

  // Start moving
  moveForward(pwmSpeed, pwmSpeed);

  // Keep moving for calculated time
  delay(timeMs);

  // Stop
  stopMotors();

  Serial.println("Movement completed.");
}


// -----------------------------------------------------
// Setup
// -----------------------------------------------------
void setup()
{
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  Serial.begin(19200);

  stopMotors();

  Serial.println("================================");
  Serial.println("Robotic Car Motor Control");
  Serial.println("================================");
  Serial.println("Send 'g' to move forward 1 metre.");
  Serial.println("Send 's' to stop the motors.");
}


// -----------------------------------------------------
// Main loop
// -----------------------------------------------------
void loop()
{
  if (Serial.available() > 0)
  {
    char command = Serial.read();

    // Move forward 1 metre
    if (command == 'g')
    {
      Serial.println("Moving forward 1 metre...");
      moveDistance(distanceCM, motorSpeed);
    }

    // Stop motors
    else if (command == 's')
    {
      stopMotors();
      Serial.println("Motors stopped.");
    }
  }
}