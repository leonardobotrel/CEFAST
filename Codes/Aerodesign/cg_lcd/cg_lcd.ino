#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>                    
 
#define DOUT1  3                      
#define CLK1  2
#define DOUT2  5                      
#define CLK2  4
#define DOUT3  7                      
#define CLK3  6

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Configura endereço I2C e display com 16 caracteres e 2 linhas
 

HX711 balanca1;         
HX711 balanca2; 
HX711 balanca3;    
 
float calibration_factor1 = 330200; 
float calibration_factor2 = 370200;
float calibration_factor3 = 211310;   
const int pinoBotao = 12;
int estado; 
 
void setup()
{
  Serial.begin(9600);

  balanca1.begin(DOUT1, CLK1);
  balanca2.begin(DOUT2, CLK2);
  balanca3.begin(DOUT3, CLK3); 
              
  Serial.println("Pressione t para Tara");           
  balanca1.set_scale(calibration_factor1);
  balanca2.set_scale(calibration_factor2);
  balanca3.set_scale(calibration_factor3);            
  balanca1.tare();              
  balanca2.tare();
  balanca3.tare();  

  lcd.begin (20,4);
  pinMode(pinoBotao, INPUT_PULLUP);
}
 
void loop()
{ 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1: ");                          
  lcd.print(balanca1.get_units(), 2);                   
  lcd.setCursor(0,1);
  lcd.print("2: "); 
  lcd.print(balanca2.get_units(), 2);  
  lcd.setCursor(0,2);            
  lcd.print("3: ");
  lcd.print(balanca3.get_units(), 2);                                   
                                        
  if (digitalRead(pinoBotao) == LOW && estado == 0)                          
  {
    
    estado = 1;
    balanca1.tare();
    balanca2.tare();
    balanca3.tare();
  delay(500) ;  
  }
  else if (digitalRead(pinoBotao) == HIGH && estado == 1){
    estado = 0;             
  }
  delay(500);
  
}
