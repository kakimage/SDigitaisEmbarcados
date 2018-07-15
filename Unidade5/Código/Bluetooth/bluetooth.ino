// ******************************************************************************************************************************
// *                                        Transmite a temperatura por bluetooth                                               *
// * a temperatura eh captura por um sensor lm35 e transmitida por bluetooth usando um modulo bluetooth Hc-06                   *
// ******************************************************************************************************************************




// ******************************************************************************************************************************
// * Ligacoes do modulo bluetooth :
// * O pino TX do modulo deve ser ligado no RX do arduino e vice-versa


// ********************** LINUX ******************
// O linux mantem os nomes dos dispositivos bluetooth num cache, 
// assim ao mudar o nome, o cache do linux deve ser apagado
// /var/lib/bluetooth/MAC-address/names o pino key nao precisa ser acessado para isso


// no linux deve-se instalar o pacote blueman

// e configurar o arquivo 
// /etc/bluetooth/rfcomm.conf
//        rfcomm1 {
//            bind yes;
//            device 00:12:11:19:08:54;
//            channel    1;
//            comment "Linvor Bluetooth Module";
//        }

//e chamar sudo rfcomm connect 1

//depois, pode-se usar o terminal (as vezes existe a necessidade de id de root chmod u+s cutecom





#include <SoftwareSerial.h>
#define PINO_A0 0
#define PINO_A1 1

#define rxPin 6
#define txPin 5
char vet[50], aux[20];
long count=0;


SoftwareSerial      mySerial =  SoftwareSerial(rxPin, txPin);




// **************************************************************************************************************
// * configura o bluetooth                                                                                      *     
// **************************************************************************************************************
void configura_BLUETOOTH (void)
{
   char comando[30];
   delay(3000); 
   mySerial.print("AT\r\n");
   
 
   //delay(3000);
   mySerial.print("AT+NAME=COMPUTACAO\r\n");
   delay(3000);
   mySerial.print("AT+TEMP\r\n");
   delay(3000);
   mySerial.print("AT+PIN1234\r\n");
  
   delay(3000);
   
 
}
// **************************** Sensor de temperatura ******************************
// Para melhorar a precisao, troca a referencia do conversor AD para 1.1v  usando analogReference. Esta mudanca faz com que a equaço de temperatura deve levar em consideracao os 1.1v
// faz 1000 leituras e tira a media para melhorar a precisao
void setup() 
{ 
   pinMode(rxPin, INPUT);
   pinMode(txPin, OUTPUT);
   
   analogReference(INTERNAL);       // Referencia de 1.1V UNO (1.1/1024=0,913mv) 0,913mv de precisão ou seja 
   Serial.begin(38400);              // Serial port for debugging, Comment this line if not required  
   mySerial.begin(9600);
   mySerial.listen();
   Serial.println("Sistema rodando");    
   configura_BLUETOOTH();   
  
} 



// **************************************************************************************************************
// * Captura a temperatura usando a media das 1000 temperaturas lidas                                           *     
// **************************************************************************************************************
double captura_temperatura (byte pino)
{
   double valor = 0;

   for ( int i = 0; i < 1000; i++)   valor = valor+analogRead(pino);
   valor = valor/1000;         // Media de mil leituras
   valor = valor*(1.1/1024);   // Converte valor lido para tensão
   valor = valor*100;          // Converte para Graus = temperatura/(1/10mv)
   return valor;
}

// **************************************************************************************************************
// * Fica em loop lendo a temperatura e transmitindo por bluetooth                                              *     
// **************************************************************************************************************

void amostra_temperatura_e_transmite (void)
{
   dtostrf(captura_temperatura(PINO_A1),6,2,aux);
   strcpy(vet,"|Temperatura=");
   strcat(vet,aux);
   strcat(vet,"|");
   Serial.println(vet);
   delay(300);
   count++;
}
void loop() 
{
    
  
   mySerial.println("oi");
 

} 
 

