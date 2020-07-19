#include <Ticker.h> //libreria para manejar interrupciones temporales

const uint8_t c1_pin = 2;//D4
const uint8_t c2_pin = 0;//D3

Ticker timer;
byte wheelPos;
//byte Last_wheelPos;
long pulsos = 0;  // variable para contar los pulsos
int resolucion = 11;  // resolución del encoder número de pulsos por revolución
double rpm; // variable para almacenar el calculo de la velocidad rpm
 

void ICACHE_RAM_ATTR deteccion(){  // función que se ejecuta cuando hay interrupción externa
  //pulsos++; // se incrementa la variable pulso en uno.
  wheelPos = (digitalRead(c1_pin) << 1) | digitalRead(c2_pin);
  if(wheelPos == 3 || wheelPos == 0){
    pulsos++;
  }
  else{
    pulsos--;
  }
  
}
 
void ICACHE_RAM_ATTR segundo () {  // función que se ejecuta cuando se cumple el tiempo de interrupcíón temporal
  rpm=((double)pulsos/resolucion)*60; // calculo de velocidad rpm
  pulsos=0; // pulsos
  Serial.println(rpm); // se envia via serial la variable rpm
}
 
void setup() {  

  Serial.begin(9600);// se inicia la comunicación serial
  pinMode(c1_pin, INPUT);
  pinMode(c2_pin, INPUT);
  timer1_attachInterrupt(segundo);//se establece función de interrupción
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
  /* Dividers:
    TIM_DIV1 = 0,   //80MHz (80 ticks/us - 104857.588 us max)
    TIM_DIV16 = 1,  //5MHz (5 ticks/us - 1677721.4 us max)
    TIM_DIV256 = 3  //312.5Khz (1 tick = 3.2us - 26843542.4 us max)
  Reloads:
    TIM_SINGLE  0 //on interrupt routine you need to write a new value to start the timer again
    TIM_LOOP  1 //on interrupt the counter will start with the same value again
  */
  
  // Arm the Timer for our 1s Interval
  timer1_write(5000000); // 5000000 / 5 ticks per us from TIM_DIV16 == 1000,000
 
  attachInterrupt(digitalPinToInterrupt(c1_pin), deteccion, CHANGE);// se programa un interrupción externa, cada que hay un cambio de bajo a alto
  

  
}
void loop() {
          
   
}
