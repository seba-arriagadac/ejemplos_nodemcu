//codigo basado en la sección "Programación Encoder Avanzado"
// https://zaragozamakerspace.com/index.php/introduccion-al-rotary-encoder/

/* Define digital pins used to read the encoder */
#define DT 4
#define CLK 5
//#define SW 2
int counter;
byte DialPos;
byte Last_DialPos;

const int timeThreshold = 5;
unsigned long currentTime;
unsigned long loopTime;

void setup()
{
  Serial.begin(9600);
  pinMode(DT, INPUT);
  pinMode(CLK, INPUT);
  //pinMode(SW, INPUT);
  //digitalWrite(SW, HIGH);

  /* Reset the counter */
  counter = 0;

  currentTime = millis();
  loopTime = currentTime;
}

/* Main program */
void loop()
{
  currentTime = millis();
  if (currentTime >= (loopTime + timeThreshold))
  {
    /* Read the status of the dial */
    DialPos = (digitalRead(CLK) << 1) | digitalRead(DT);

    /* Is the dial being turned anti-clockwise? */
    if (DialPos == 3 && Last_DialPos == 1)
    {
      counter--;
      /* Output the counter to the serial port */
      Serial.println(counter);
    }

    /* Is the dial being turned clockwise? */
    if (DialPos == 3 && Last_DialPos == 2)
    {
      counter++;
      /* Output the counter to the serial port */
      Serial.println(counter);
    }

    /* Is the switch pressed? */
    //if (!digitalRead(SW))
    //  Serial.println("Switch pressed!");

    /* Save the state of the encoder */
    Last_DialPos = DialPos;
    loopTime = currentTime;  // Actualizar tiempo
  }

}
