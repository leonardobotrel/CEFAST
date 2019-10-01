#include <HX711.h>                    
 
#define DOUT1  4     
#define CLK1  2
#define DOUT2  6                      
#define CLK2  5
#define DOUT3  10                      
#define CLK3  8
                        
 
HX711 balanca1;         
HX711 balanca2; 
HX711 balanca3;   
 
float calibration_factor1 = 371200; 
float calibration_factor2 = 327200;
float calibration_factor3 = 219200;   
 
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
}
 
void loop()
{ 
  Serial.print("Balança 1:   ");                           
  Serial.print(balanca1.get_units(), 3);              
  Serial.println(" kg\t");      
  Serial.print("                      Balança 2:   "); 
  Serial.print(balanca2.get_units(), 3);              
  Serial.println(" kg\t");
  Serial.print("                                      Balança 3:   ");
  Serial.print(balanca3.get_units(), 3);              
  Serial.println(" kg\t");                     
  delay(500) ;                                      
  if (Serial.available())                           
  {
    int temp = Serial.read();                      
    if (temp == '1')                 
    {
      balanca1.tare();                                           
    }
    if (temp == '2')                
    {
      balanca2.tare();                                           
    }
    if (temp == '3')               
    {
      balanca3.tare();                                           
    }
    if (temp == '4')                
    {
      balanca1.tare();  
      balanca2.tare();
      balanca3.tare();                                         
    }
  }
}
