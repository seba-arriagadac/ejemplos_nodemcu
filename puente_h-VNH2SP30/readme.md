# Ejemplo con Puente h  VNH2SP30

## PWM
La resolución de 10 bits

## Acceso a la señal de PWM con el IDE Arduino

Para generar una señal PWM con el IDE de Arduino se usa la función `analogWrite()` y se usa asi:
```cpp
analogWrite(pin, value)
```
donde `value` por defecto va de 0 a 1023. Este rango se puede modificar con la función:
```cpp
analogWriteRange(new_range)
```
La frecuencia de la PWM por defecto es de 1 _KHz_ pero puede ser cambiada con la función:
```cpp
analogWriteFreq(new_frequency)
```
## Páginas con informacion útil
[Arduino AnalogWrite](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/)
[electronicwings.com pwm arduino IDE](https://www.electronicwings.com/nodemcu/nodemcu-pwm-with-arduino-ide)
[Ejemplo completo de VNH2SP30](https://www.puntoflotante.net/DRIVER-VNH2SP30-PWM-PUENTE-H-MOTORES-CD.htm)
## Pinout referencial
![nodeMCU_pinout](https://www.luisllamas.es/wp-content/uploads/2018/06/esp8266-nodemcu-pinout.png)
