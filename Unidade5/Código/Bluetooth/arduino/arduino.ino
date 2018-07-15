//Exemplo de transmissao de dados entre o PC usando terminal serial a 9600 e um dispositivo bluetooth
//O modo de envio de comados (modo 2) permite trabalhar com envio de dados para o modulo a 9600
// o Modo 1 necessita de 38400


#define PINO_KEY 8
#define PINO_ENERGIA 9

void configura_pinos (void)
{
   pinMode(PINO_KEY, OUTPUT);
   pinMode(PINO_ENERGIA, OUTPUT);
   digitalWrite(PINO_ENERGIA, LOW);
}
void MODO_DADOS (void)
{
    // serial a 9600
    digitalWrite(PINO_ENERGIA, LOW);
    delay(1000);
    digitalWrite(PINO_KEY, LOW);
    delay(100);
    digitalWrite(PINO_ENERGIA, HIGH);
    delay(1000);
    digitalWrite(PINO_KEY,HIGH);
    delay(1000);
}

void MODO_COMANDO2 (void)
{
    // serial a 9600
     Serial2.begin(9600); // liga no bluetooth
    digitalWrite(PINO_ENERGIA, LOW);
    delay(1000);
    digitalWrite(PINO_KEY, LOW);
    delay(100);
    digitalWrite(PINO_ENERGIA, HIGH);
    delay(1000);
    digitalWrite(PINO_KEY,HIGH);
    delay(1000);
}

void MODO_COMANDO1(void)
{
    Serial2.begin(38400);
    digitalWrite(PINO_ENERGIA, LOW);
    delay(200);
    digitalWrite(PINO_KEY, HIGH);
    digitalWrite(PINO_ENERGIA, HIGH);
    delay(1000);

}
void mestre_comando (char st[])
{
    int x;
    while (st[x]!=0) putchar(st[x++]);
    delay(2000);
}
void setup (void)
{
  Serial.begin(9600); // liga no Pc
 
  configura_pinos();
  
  delay(2000);
  MODO_COMANDO2();
  
 // mestre_comando("AT+role=1\r\n");
  //mestre_comando("at+iac=9e8b33\r\n");
  //mestre_comando("at+class=0\r\n");
  //mestre_comando("at+inqm=1,9,48\r\n");
  //mestre_comando("at+link=2014,4,302728\r\n");
  
  
  
  
  
  
  delay(2000);
  
  
  //MODO_DADOS();
  
  
  
  
  Serial.println("Digite para enviar");
  
  Serial2.flush();
}
void disconecta(void)
{
    digitalWrite(PINO_ENERGIA, LOW);
    delay(1000);
    digitalWrite(PINO_KEY, LOW);
    delay(100);
    digitalWrite(PINO_ENERGIA, HIGH);
    delay(1000);
    digitalWrite(PINO_KEY,HIGH);
    delay(1000);

}

void loop (void)
{
    char a, b;
    char st[30];
   if (Serial.available())
    {
        a = Serial.read();
        if (a=='&') disconecta();
        else Serial2.write(a);
    }
   
    if (Serial2.available())
    {
        Serial.write(Serial2.read());
    }
  
}
