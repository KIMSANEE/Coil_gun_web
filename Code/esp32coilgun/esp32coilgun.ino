int s1=13;
int s2=12;
int s3=14;
int s4=27;
int coil1=15;
int coil2=2;
int coil3=4;
float t0=0.0;
float t0=0.0;
float t0=0.0;
float t0=0.0;

void setup() 
{
  Serial.begin(9600);
  pinMode(coil1, OUTPUT);
  pinMode(coil2, OUTPUT);
  pinMode(coil3, OUTPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);

  digitalWrite(coil1,LOW);
  digitalWrite(coil2,LOW);
  digitalWrite(coil3,LOW);

}

void loop() 
{
  float t0=0.0;
  float t1=0.0;
  float t2=0.0;
  float t3=0.0;
  float t4=0.0;
  float ontime=0;
  float v=0.0;
  float v2=0.0;
  float v3=0.0;
  
  if(switch==true)
  {
     t0=millis();
     while(digitalRead(s1)==0 and switch==false)
     {
      digitalWrite(coil1,HIGH);
     }
     digitalWrite(coil1,LOW);
     t1=millis();
     while(digitalRead(s2)==0 and switch==false)
     {
     digitalWrite(coil2,HIGH);
     }
     digitalWrite(coil2,LOW);
     t2=millis();
     while(digitalRead(s3)==0 and switch==false)
     {
     digitalWrite(coil3,HIGH);
     }
     digitalWrite(coil3,LOW);
     t3=millis();
     while(digitalRead(s4)==0 and switch==false)
     {
     }
     t4=millis();
     switch == true;
     //Serial.print("t1=");
     //Serial.println(t1);
     //Serial.print("t2=");
     //Serial.println(t2);
     //Serial.print("t3=");
     //Serial.println(t3);
     //Serial.print("t4=");
     //Serial.println(t4);
     //Serial.print("t2-t1=");
     //Serial.println(t2-t1);
     //v1=100/(t2-t1);
     //Serial.print("--v1(m/s)=");
     //Serial.println(v1);
     //Serial.print("t3-t2=");
     //Serial.println(t3-t2);
     v=70/(t2-t1);
     ontime=(t1-t0)/1000;
     Serial.print("--on time(s)=");
     Serial.println(ontime);
     Serial.print("--v(m/s)=");
     Serial.println(v);
     //Serial.print("t4-t3=");
     //Serial.println(t4-t3);
     //v3=118.15/(t4-t3);
     //Serial.print("--v3(m/s)=");
     //Serial.println(v3);
     Serial.println("finish");
  }
}