#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6QmC81r_"
#define BLYNK_DEVICE_NAME "DoAn"
#define BLYNK_AUTH_TOKEN "ytFTyiLrhZs1D9ugaxysckra7rLDP2xr"
#define trigPin D0
#define echoPin D1
#define trigPin1 D2
#define echoPin1 D3
#define LedW01 D6
#define LedR01 D5
#define LedW02 D7
#define LedR02 D8
#define Buzzer D4
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "ytFTyiLrhZs1D9ugaxysckra7rLDP2xr";
char ssid[] = "NhatTruong";
char pass[] = "tamsohai";
int duration;
float d_cm;
int duration1;
float d_cm1;
float sinVal;
int toneVal;
WidgetLED appLedW01(V3);
WidgetLED appLedR01(V4);
WidgetLED appLedW02(V5);
WidgetLED appLedR02(V6);
void setup()
{  
  Serial.begin(9600);// Debug console
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  pinMode(LedW01,OUTPUT);
  pinMode(LedR01,OUTPUT);
  pinMode(LedW02,OUTPUT);
  pinMode(LedR02,OUTPUT);
  pinMode(Buzzer , OUTPUT);
  Blynk.begin(auth, ssid, pass);
  //Thong bao ket noi
  Serial.println("DEVICE IS CONNECTED");
}
void CamBien01()
{
  //cam bien song am 1 ==============================================================
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH); // doc gia tri canh len phan hoi ve mat doc
  d_cm = duration * 0.034/2.; // S = T 0.0343/2 Khoang cach tu vat den mat
}
void CamBien02()
{
  //cam bien song am 2 ==============================================================
  digitalWrite(trigPin1,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1,LOW);
  duration1 = pulseIn(echoPin1,HIGH);  // doc gia tri canh len phan hoi ve mat doc
  d_cm1 = duration1 * 0.034/2.;// S = T 0.0343/2 Khoang cach tu vat den mat
}

void buzzer()
{
  for(int x=0; x<180; x++){
    // convert degrees to radians then obtain value
    sinVal = (sin(x*(3.1412/180)));
    // generate a frequency from the sin value
    toneVal = 2000+(int(sinVal*1000));
    tone(Buzzer, toneVal);
    delay(2); 
  }  
}

void DenBao()
{
  if(d_cm<30){
    appLedR01.on();
    appLedW01.off();
    digitalWrite(LedR01,HIGH);
    digitalWrite(LedW01,LOW);
  }
  else{
    appLedR01.off();
    appLedW01.on();
    digitalWrite(LedW01,HIGH);
    digitalWrite(LedR01,LOW);
  }
  if(d_cm1<30){
    appLedR02.on();
    appLedW02.off();
    digitalWrite(LedR02,HIGH);
    digitalWrite(LedW02,LOW);
  }
  else{
    appLedR02.off();
    appLedW02.on();
    digitalWrite(LedW02,HIGH);
    digitalWrite(LedR02,LOW);
  }
  if(d_cm1<10 || d_cm<10)
  {    
    buzzer();
    delay(2500);
    noTone(Buzzer);
    delay(1500);
  }
  if(d_cm1>=10 && d_cm>=10)
  {
    noTone(Buzzer);
  }
}
void sendUptime()
{
  //print ra man hinh
  Serial.print("khoang cach1: ");
  Serial.print(d_cm);
  Serial.print("cm                            ");
  Serial.print("khoang cach2: ");
  Serial.print(d_cm1);
  Serial.println("cm");
  //Truyen du lien len Blynk==========================================================
  Blynk.virtualWrite(V0,d_cm);
  Blynk.virtualWrite(V2,d_cm1);
  delay(500);  
}
void loop()
{
  Blynk.run();                   
  CamBien01();
  CamBien02();
  sendUptime();
  DenBao();
}