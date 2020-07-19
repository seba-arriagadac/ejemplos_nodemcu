#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR
#define MOTOR_A_PIN 13//7(D7)
#define MOTOR_B_PIN 12//8(D6)

#define PWM_MOTOR 14//5(D5)

#define CURRENT_SEN_1 A0//A2

#define EN_PIN_1 15//A0(D8)

short usSpeed = 150;  //default motor speed
int current_CS;
unsigned short usMotor_Status = BRAKE;

void setup()
{
  pinMode(MOTOR_A_PIN, OUTPUT);
  pinMode(MOTOR_B_PIN, OUTPUT);

  pinMode(PWM_MOTOR, OUTPUT);

  //pinMode(CURRENT_SEN_1, OUTPUT);

  pinMode(EN_PIN_1, OUTPUT);

  Serial.begin(9600);              // Initiates the serial to do the monitoring
  Serial.println("Begin motor control");
  printWelcomeMssg();

}

void loop()
{
  char user_input;
  while (Serial.available())
  {
    user_input = Serial.read(); //Read user input and trigger appropriate function
    digitalWrite(EN_PIN_1, HIGH);
    // Serial.print("recibí "); // para saber si se recibe un dato de más
    // Serial.print(user_input,DEC);
    // Serial.println("");
    switch (user_input)
    {
      case '1':
        Stop();
        break;
      case '2':
        Forward();
        break;
      case '3':
        Reverse();
        break;
      case '+':
        IncreaseSpeedFine();
        break;
      case '*':
        IncreaseSpeed();
        break;
      case '-':
        DecreaseSpeedFine();
        break;
      case '_':
        DecreaseSpeed();
        break;
      case 's':
        Serial.println(usSpeed, DEC);
        break;
      case 'm':
        switch (usMotor_Status)
        {
          case CW:
            Serial.println("Dirección Reloj");
            break;
          case CCW:
            Serial.println("Dirección Contra-Reloj");
            break;
          default:
            Serial.println("Frenado");
            break;
        }
        break;
      case '?':
        printWelcomeMssg();
        break;
      case 'c':
        current_CS = analogRead(CURRENT_SEN_1);
        Serial.println(current_CS, DEC);
        break;
      case 10:
        break;
      default:
        Serial.println("Invalid option entered.");
        break;
    }


  }
}

void Stop()
{
  Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(usMotor_Status, 0);
}

void Forward()
{
  Serial.println("Forward");
  usMotor_Status = CW;
  motorGo(usMotor_Status, usSpeed);
}

void Reverse()
{
  Serial.println("Reverse");
  usMotor_Status = CCW;
  motorGo(usMotor_Status, usSpeed);
}

void IncreaseSpeed()
{
  usSpeed = usSpeed + 10;
  if (usSpeed > 1020)
  {
    usSpeed = 1020;
  }

  Serial.print("Speed +: ");
  Serial.println(usSpeed);

  motorGo(usMotor_Status, usSpeed);
}

void IncreaseSpeedFine()
{
  usSpeed = usSpeed + 1;
  if (usSpeed > 1020)
  {
    usSpeed = 1020;
  }

  Serial.print("Speed +: ");
  Serial.println(usSpeed);

  motorGo(usMotor_Status, usSpeed);
}

void DecreaseSpeed()
{
  usSpeed = usSpeed - 10;
  if (usSpeed < 0)
  {
    usSpeed = 0;
  }

  Serial.print("Speed -: ");
  Serial.println(usSpeed);

  motorGo(usMotor_Status, usSpeed);
}

void DecreaseSpeedFine()
{
  usSpeed = usSpeed - 1;
  if (usSpeed < 0)
  {
    usSpeed = 0;
  }

  Serial.print("Speed -: ");
  Serial.println(usSpeed);

  motorGo(usMotor_Status, usSpeed);
}


void motorGo(uint8_t direct, uint16_t pwm)
{

  if (direct == CW)
  {
    digitalWrite(MOTOR_A_PIN, LOW);
    digitalWrite(MOTOR_B_PIN, HIGH);
  }
  else if (direct == CCW)
  {
    digitalWrite(MOTOR_A_PIN, HIGH);
    digitalWrite(MOTOR_B_PIN, LOW);
  }
  else
  {
    digitalWrite(MOTOR_A_PIN, LOW);
    digitalWrite(MOTOR_B_PIN, LOW);
  }

  analogWrite(PWM_MOTOR, pwm);
}
void printWelcomeMssg()
{
  Serial.print(F("Enter number for control option:\n1. STOP\n2. FORWARD\n3. REVERSE\n+. FINE INCREASE SPEED\n*. INCREASE SPEED\n-. FINE DECREASE SPEED\n_. DECREASE SPEED\ns. ASK SPEED\nm. ASK MOTOR DIRECTION\n?. OPTIONS\n"));
}
