/************************************************************
  LINE TRACER
  Follows a Black line on a White surface autonomously 
 
 HARDWARE- 
 1. Atmega328 microcontroller Board
 2. L293D Motor Driver
 3. IR Line sensors
 4. 9V Battery
 5. TSOP Sensor
 
 The circuit: 
 1. Line Sensors
 * Left Sensor connected to Pin 3
 * Right Sensor connected to Pin 2
 * VCC 5V from Controller board
 * GROUND from Groung of controller board
 
 2. L293D Motor Driver
 * Left Motor to Pin 5 and Pin 6
 * Right Motor to Pin 9 and Pin 10
 * VCC 9V from Battery
 * GROUND from Ground of controller board

 3. TSOP Sensor
 * Connected to Pin 4

 Author :- Raj Agarwal
 
***********************************************************************/


//MOTOR CONNECTIONS
int Left_motor1 = 5;      // Left Motor Positive connected to Pin 5
int Left_motor2 = 6;      // Left Motor Negative connected to pin 6 
int Right_motor1 = 9;     // Right Motor Positive connected to Pin 9 
int Right_motor2 = 8;     // Right Motor Negative connected to Pin 10

//SENSORS CONNECTIONS
int Left_sensor = 2;      // Left sensor connected to Pin 3
int Right_sensor = 3;     // Right sensor connected to Pin 2
int TSOP = 4;             // TSOP sensor connected to Pin 4

//SENSORS INITIALIZATION
int Left_sensorstate = 0;
int Right_sensorstate = 0;
int TSOP_sensorstate = 0;

// the setup routine runs once when you press reset or start the Robot:
void setup() 
{
  // initialize serial communication at 9600 bits per second(to see output on Serial Monitor):
  Serial.begin(9600);

  // initialize the Sensor pins as INPUT:
  pinMode(Left_sensor, INPUT);
  pinMode(Right_sensor, INPUT);
  pinMode(TSOP, INPUT);
  
  // initialize the Motor pins as OUTPUT:
  pinMode(Left_motor1, OUTPUT);
  pinMode(Left_motor2, OUTPUT);
  pinMode(Right_motor1, OUTPUT);
  pinMode(Right_motor2, OUTPUT);
  
  Serial.println("OBJECT DETECTOR ROBOT");
}

// the loop routine runs over and over again forever:
void loop() 
{
  //Reading from both the Sensors
  Left_sensorstate = digitalRead(Left_sensor);
  Right_sensorstate = digitalRead(Right_sensor);
  
  //Reading from TSOP Sensors
  TSOP_sensorstate = digitalRead(TSOP);
 
  if (Left_sensorstate == HIGH)
  {
      digitalWrite(Left_motor1, HIGH);       // Robot going in Left direction,take Right turn
      digitalWrite(Left_motor2, LOW);
  }
  
  else
  {
      digitalWrite(Left_motor1, LOW);       // Stop the motor
      digitalWrite(Left_motor2, LOW);
  }
  
  if (Right_sensorstate == HIGH)
  {
      digitalWrite(Right_motor1, HIGH);    // Robot going in Right direction,take Left turn
      digitalWrite(Right_motor2, LOW);
  }
  
  else
  {
      digitalWrite(Right_motor1, LOW);     // Stop the motor
      digitalWrite(Right_motor2, LOW);
  }
  
  //When both sensors on the line Stop the robot
  if (Left_sensorstate == LOW && Right_sensorstate == LOW)
  {
      digitalWrite(Left_motor1, LOW);    // Stop Left motor
      digitalWrite(Left_motor2, LOW);
      digitalWrite(Right_motor1, LOW);    // Stop Right motor
      digitalWrite(Right_motor2, LOW);
  }
  
  //When Object is detected Stop and take right turn
  if (TSOP_sensorstate == HIGH)
  {
      digitalWrite(Left_motor1, LOW);    // Stop Left motor
      digitalWrite(Left_motor2, LOW);
      digitalWrite(Right_motor1, LOW);    // Stop Right motor
      digitalWrite(Right_motor2, LOW);
      
      delay(1000);
      
      for(int i = 0; i < 5000; i++)
      {
        //Right turn
      digitalWrite(Left_motor1, LOW);    // Stop Left motor
      digitalWrite(Left_motor2, LOW);
      digitalWrite(Right_motor1, HIGH);    // Stop Right motor
      digitalWrite(Right_motor2, LOW);
      }
  }
  
  //Printing Sensor OUTPUT on Serial Monitor
  Serial.print("LEFT SENSOR-->");
  Serial.print(Left_sensorstate);
  Serial.print("    ");
  Serial.print("RIGHT SENSOR-->");
  Serial.print(Right_sensorstate);
  Serial.print("    ");
  Serial.print("TSOP SENSOR-->");
  Serial.println(TSOP_sensorstate);
  delay(100);
}


