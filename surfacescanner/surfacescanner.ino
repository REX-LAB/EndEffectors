#include <Bounce.h>


const int AnzahlMessungen = 10;
float Werte[AnzahlMessungen+1];
boolean IndexListe[AnzahlMessungen+1];
const int taste1 = 4;
int tastenstatusvorher = HIGH;
int zaehler = 0;
int abstandssensor = 0;
int ledpin1 = 12;
Bounce bouncer_Taste1 = Bounce(taste1,20);

void setup()
{
  pinMode(taste1, INPUT);
  pinMode(abstandssensor, INPUT);
  pinMode(ledpin1, OUTPUT);
  Serial.begin(9600);
}

/*float Abstand()
{
  int val = analogRead(abstandssensor);
  float ret = (6787.0 /((float)val - 3.0)) -4.0;
  
  if(ret > 80.0)
    ret = 80;
    
  if (ret < 6.0)
    ret = 6;  
    
  return ret;
}  */


float Mittelwert()
{
  float xQuer = 0;
  float Sigma = 0;
  int i;
  int k;
  int AnzahlEliminiert = 0;
  
    for(i=1;i<=AnzahlMessungen;i++)
    {
      xQuer = xQuer + Werte[i];
      IndexListe[i] = true;
    }
    xQuer = xQuer / AnzahlMessungen;
    
    
     for(i=1;i<=AnzahlMessungen;i++)
    {
      Sigma = Sigma + sq(xQuer - Werte[i]);
    }
    Sigma = sqrt(Sigma / AnzahlMessungen);
  
  //   Serial.print("xQuer ");
  //   Serial.print(xQuer);
  //   Serial.print("  Sigma ");
  //   Serial.print(Sigma);
  //   Serial.print("   ");    
    
     for(i=1;i<=AnzahlMessungen;i++)
     {
     //  Serial.print(Werte[i]);
     //  Serial.print(" ");
       if (abs(Werte[i]-xQuer)>(0.8*Sigma))
       {
         AnzahlEliminiert++;
         IndexListe[i] = false;
         
       }
     }
  
   //  Serial.print(" Eliminiert: ");
   //  Serial.print(AnzahlEliminiert);
   //  Serial.print("  ");
  
  if (AnzahlEliminiert > 0)
  {
    xQuer = 0;
    for(i=1;i<=AnzahlMessungen;i++)
    {
      if (IndexListe[i] == true)
        xQuer = xQuer + Werte[i];
    }
    xQuer = xQuer / (AnzahlMessungen-AnzahlEliminiert);
  }
  
  return xQuer;
}



float Abstandsmessung()
{
  int i;
  
  digitalWrite(ledpin1, HIGH);
  delay(10);
   
  for(i=1;i<=AnzahlMessungen;i++)
  {
     int val = analogRead(abstandssensor);
      float ret = (6787.0 /((float)val - 3.0)) -4.0;
  
     if(ret > 80.0)
       ret = 80;
     if (ret <6.0)
       ret = 6;
       

     Werte[i] = ret;
     delay(60-i);
  }
  
  digitalWrite(ledpin1, LOW);
   
  return Mittelwert();
}  



void loop()
{
  bouncer_Taste1.update();
  int tastenstatus = bouncer_Taste1.read();
  if ((tastenstatus != tastenstatusvorher) && (tastenstatus == HIGH))
    {
       zaehler++;
      // Serial.println("Point");
      // Serial.print("w");
       Serial.print(zaehler);
       Serial.print(":");
       Serial.print(Abstandsmessung());
       Serial.print("\n");
       
       
    }
       
       tastenstatusvorher = tastenstatus;
}
    

