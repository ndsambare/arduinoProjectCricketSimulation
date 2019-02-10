/* cricket
 *  
 *  CSE 132 - Assignment 3
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Namit Sambare
 *  WUSTL Key: ndsambare
 *  
 *  and if two are partnered together
 *  
 *  Name: Jacob Felger
 *  WUSTL Key: jacobfelger
 */
#define FILTER_COUNTS 7

float temperatureAvg[FILTER_COUNTS]; 

int count = 0; 



const int tempPeriod = 250; 

const int BLINK_DURATION = 150; 

long lastTemp = 0; 

long lastFlash = 0; 



const int Temp_Pin = A1; 

bool light = false; 

void setup() {
  // put your setup code here, to run once:

analogReference(INTERNAL); 
pinMode(8, OUTPUT); 

Serial.begin(9600); 

}
float sum = 0; 
void loop() {
  // put your main code here, to run repeatedly:

long now = millis(); 


if ((now - lastTemp) >= tempPeriod) {
  

 
 readTemp(); 

   int counter = 1;
 for (int i = 0; i < 7; i++) {
 
 if (temperatureAvg[i] != 0) {
  counter++;
 }
  sum += temperatureAvg[i]; 
  
 }
 
  sum = sum/counter;

 

     Serial.print(", "); 

  Serial.print(sum); 
  Serial.println(); 

  //float centTemp = 25 + (1.1* (analogRead(A1)/1023.0) - 0.75) * 100; 
  //Serial.print(centTemp); 



 // Serial.print("------"); 
  
  //Serial.print(analogRead(A1)); 
  
  lastTemp = lastTemp + tempPeriod; 


 
}

  float period1 = (sum - 10.0);
  float period2 = 7.0 * period1;
  float period3 = period2 + 40.0;
  float period4 = period3 / 60.0;
  float period5 = period4 / 1000.0;
  float period6 = 1.0 / period5;
  float period = period6;
  //float period = 1.0 / ((((7.0 * (sum - 10.0)) + 40.0) / 60.0) * 1000.0); 
  //Serial.println(period);
  //Serial.println(sum); 
  //float period = (1 / period0 / 60) * 1000; 
//int period = 500;
if (light == true) {
  

  if ((now - lastFlash) >= BLINK_DURATION) {
     digitalWrite(8, LOW); 
     //Serial.println(period);
    //Serial.println("OFF"); 
    //Serial.println(period); 
    //Serial.println(now); 
    //Serial.println(lastFlash);
    //Serial.println("------------"); 
     lastFlash = lastFlash + period - BLINK_DURATION;
     
      light = false; 
      
  }
}
else  {


  if ((now - lastFlash) >= period - BLINK_DURATION) {
    
     digitalWrite(8, HIGH); 
     //Serial.println("ON"); 
     //Serial.println(period); 
    //Serial.println(now); 
    //Serial.println(lastFlash);
    //Serial.println("------------"); 
     lastFlash = lastFlash + BLINK_DURATION; 
      
      light = true; 
      
  }
 
}

  

}



void readTemp() {
  int reading = analogRead(A1); 
   float mVolts =  1.1 * (analogRead(A1)/1023.0);  
  float centTemp = 25 + ((mVolts - 0.75) * 100); 
  temperatureAvg[count % FILTER_COUNTS] = centTemp; 
  Serial.print(centTemp); 
 

  
  count++; 
}
