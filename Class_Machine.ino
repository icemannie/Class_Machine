
/*
   GWC club intoductory machine
Simple program to show use of IDE and Github
John Boyle September 2018
*/


//set up IO pin assignments
const int startPB = 2;
const int stopPB = 3;
const int leftGuardSwitch = 4;
const int rightGuardSwitch = 5;
const int backGuardSwitch = 6;
const int maintenanceKeySwitch = 7;
const int directionSwitch = 8;
const int PWM_out_pin = 9;
const int  runningLight = 10;
const int  guardsClosedLight = 11;
const int  maintenanceLight = 12;
const int motorDirection = 13;
const int sensorPin = A0;    // select the input pin for the potentiometer

//assign variables
int t1 = 0; // declares variable t1
int t2 = 0;   // declares variable t2
int test1 = 0;
bool machineRunning;
bool guardsClosed;
bool maintenanceSwitch;
bool chosenDirection;

void setup() {
  // put your setup code here, to run once:
  pinMode(startPB, INPUT);//2
  pinMode(stopPB, INPUT);//3
  pinMode(leftGuardSwitch, INPUT);//4
  pinMode(rightGuardSwitch, INPUT);//5
  pinMode(backGuardSwitch, INPUT);//6
  pinMode(maintenanceKeySwitch, INPUT);//7
  pinMode(directionSwitch, INPUT);//8

  pinMode(PWM_out_pin, OUTPUT); //9
  pinMode(runningLight, OUTPUT); //10
  pinMode(guardsClosedLight, OUTPUT); //11
  pinMode(maintenanceLight, OUTPUT); //12
  pinMode (motorDirection, OUTPUT);//13
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  stopMotor();
}

void loop() {
  // put your main code here, to run repeatedly:

  //monitor the guard switches and control light
  guardsClosed = digitalRead(leftGuardSwitch) && digitalRead(rightGuardSwitch);
  digitalWrite(guardsClosedLight, guardsClosed);

  //monitor the maintenance switch and control light
  maintenanceSwitch = digitalRead(maintenanceKeySwitch);
  digitalWrite(maintenanceLight, maintenanceSwitch);

  //direction control
  chosenDirection = digitalRead(directionSwitch);

  if (digitalRead(startPB) && (guardsClosed || maintenanceSwitch))machineRunning = HIGH;
  if (digitalRead(stopPB) || (!guardsClosed && !maintenanceSwitch))machineRunning = LOW;

  if ( machineRunning) {

    runMotor(chosenDirection, analogRead(sensorPin));
    test1++;
  }
  else {

    stopMotor();

  }
}
/*
   Functions placed heer outside the loop


*/
void runMotor(bool direction, int speed) {
  digitalWrite(motorDirection, chosenDirection);
  t2 = speed; // reads the voltage at A0 and saves in t2
  t1 = 1023 - t2;      // subtracts t2 from 1000 ans saves the result in t1
  digitalWrite(PWM_out_pin, HIGH); // sets pin 9 HIGH
  delayMicroseconds(t2);   // waits for t1 uS (high time)
  digitalWrite(PWM_out_pin, LOW);  // sets pin 9 LOW
  delayMicroseconds(t1);   // waits for t2 uS (low time)

}

void stopMotor() {
  digitalWrite(PWM_out_pin, LOW);
}
