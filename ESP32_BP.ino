#define BLYNK_TEMPLATE_ID "TMPL2PZHPPhn2"
#define BLYNK_TEMPLATE_NAME "Univesp"
#define BLYNK_AUTH_TOKEN "3ub6SPzn6Gpd8uGwcJNtNn-EsohcEIKp"

/* debug do Blynk */
#define BLYNK_PRINT Serial

/* bibliotecas do Wifi e do Blynk */
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;
//define os pinos
#define pinDigitalA 13

/* Configuração das Credenciais do Wifi */
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Poliana2.4";
char pass[] = "31@BF482a";
int flag=0;
int value = 0;

BLYNK_WRITE(V1){
int value = param.asInt();
Serial.println(value);
}

void setup()
{
  Serial.begin(9600);
  pinMode(pinDigitalA,INPUT);
  timer.setInterval(250L,notifyOnButtonPress);
  timer.setInterval(1000L,myTimerEvent);

  Blynk.begin(auth, ssid, pass);

}

void myTimerEvent()
{
  Blynk.virtualWrite(V0, millis()/1000);
}

void notifyOnButtonPress()
{
  int isButtonPressed = digitalRead(pinDigitalA);
  if (isButtonPressed==0 && flag==0) {
    Serial.println("Botao do panico Acionado");
    Blynk.virtualWrite(V0, isButtonPressed);
    Serial.println(isButtonPressed);
    flag=1;
    delay(1000);
  
  }
  else if (isButtonPressed==0)
  {
    flag=0;
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}
