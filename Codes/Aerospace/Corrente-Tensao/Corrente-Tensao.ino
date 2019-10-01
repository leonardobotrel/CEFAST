//Bibliotecas
//#include "ACS712.h"


//Sensor de corrente 
//ACS de 30A.
// Sensor ligado na porta analópgica A1
//ACS712 sensor_corrente(ACS712_30A, A6); //Corrente
const int sensor_correntePin = A6;  
float sensor_correnteValue = 0;    
float currentValue = 0;    
float voltsporUnidade = 0.0048875855327468;
float ruido =0.00;

//Sensor de tensao
const int sensor_tensao = A7; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
 
float tensaoEntrada = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DE TENSÃO DE ENTRADA DO SENSOR
float tensaoMedida = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DA TENSÃO MEDIDA PELO SENSOR
 
float valorR1 = 30000.0; //VALOR DO RESISTOR 1 DO DIVISOR DE TENSÃO
float valorR2 = 7500.0; // VALOR DO RESISTOR 2 DO DIVISOR DE TENSÃO
int leituraSensor = 0; //VARIÁVEL PARA ARMAZENAR A LEITURA DO PINO ANALÓGICO
 
void setup() {
  // É necessário calibrar o sensor antes de usar a primeira vez com o método abaixo
  pinMode(sensor_tensao, INPUT); //DEFINE O PINO COMO ENTRADA
  Serial.begin(9600);
  //Serial.println("Aguarde. Calibrando..."); 
  //sensor_corrente.calibrate();
  //Serial.println("Fim da calibração");
}
 
void loop() {
   //sensor de corrente
   currentValue =0;
   for(int index =0; index<5000; index++){
     sensor_correnteValue = analogRead(sensor_correntePin); // le o sensor na pino analogico A1
     sensor_correnteValue = (sensor_correnteValue -510)* voltsporUnidade; // ajusta o valor lido para volts começando da metada ja que a saída do sensor é vcc/2 para corrente =0
     currentValue = currentValue +(sensor_correnteValue/66)*1000; // a saída do sensor 66 mV por amper
     //delay(1);  
   }
 
   currentValue = currentValue /5000;

   //Sensor de tensao
   leituraSensor = analogRead(sensor_tensao); //FAZ A LEITURA DO PINO ANALÓGICO E ARMAZENA NA VARIÁVEL O VALOR LIDO
   tensaoEntrada = (leituraSensor * 5.0) / 1024.0; //VARIÁVEL RECEBE O RESULTADO DO CÁLCULO
   tensaoMedida = tensaoEntrada / (valorR2/(valorR1+valorR2)); //VARIÁVEL RECEBE O VALOR DE TENSÃO DC MEDIDA PELO SENSOR
  
  //delay(1000);
  //  float V = 3.7;
  //float I = sensor_corrente.getCurrentDC(60);
  //float P = V * I;
 
  // mostra o resultado no terminal
  Serial.print("corrente = " );      
  currentValue = currentValue- ruido;
  Serial.print(currentValue, 2);  
  Serial.print("\n" );

  Serial.print("Tensão DC medida: "); //IMPRIME O TEXTO NA SERIAL
   Serial.print(tensaoMedida,2); //IMPRIME NA SERIAL O VALOR DE TENSÃO DC MEDIDA E LIMITA O VALOR A 2 CASAS DECIMAIS
   Serial.println("V"); //IMPRIME O TEXTO NA SERIAL
 
}
