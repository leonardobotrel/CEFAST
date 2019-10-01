/*Ligacao
 * A5: sck/scl
 * A4: sda/sdi
 */

#include <Adafruit_Sensor.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_BMP280.h> //INCLUSÃO DE BIBLIOTECA
 
Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)

void setup(){
  Serial.begin(9600); //INICIALIZA A SERIAL

  if(!bmp.begin(0x76)){ //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76, FAZ
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões.")); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
  else {
    Serial.print("ok");
  }
}
 
void loop(){
    //Imprime a temperatura
    Serial.print(F("Temperatura: "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C (Grau Celsius)");
    Serial.println("");
    
    delay(1000); //INTERVALO DE 1 SEGUNDOS
}
