#include <SoftwareSerial.h>
#include <string.h>

#define SIM900_TX_PIN 8 //SIM900 TX is connected to Arduino D8
#define SIM900_RX_PIN 7 //SIM900 RX is connected to Arduino D7

SoftwareSerial SIM900(SIM900_TX_PIN,SIM900_RX_PIN);


void settingSIM900() {
  SIM900.println("AT+CSQ"); // Mengecek Kualitas Sinyal
      delay(1000);
  ShowSerialData();

  SIM900.println("AT+CGATT?"); //Melihat Support tidaknya GPRS
  delay(1000);
  ShowSerialData();

  SIM900.println("AT+SAPBR=0,1");
  delay(1000);
  ShowSerialData();

  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(1000);
  ShowSerialData();

  SIM900.println("AT+SAPBR=3,1,\"APN\",\"m2mdev\"");
  delay(1000);
  ShowSerialData();

  SIM900.println("AT+SAPBR=1,1");
  delay(3000);
  ShowSerialData(); 
}

void setup() {
  SIM900.begin(9600);               
  Serial.begin(9600);
  delay(2); 

  settingSIM900();
  
}

void loop() {
  sendToServer(); 
}

void sendToServer()
{
      
  SIM900.println("AT+HTTPINIT"); //Persiapan HTTP request
  delay(3000); 
  ShowSerialData();

  //pengiriman data ke alamat URL web server http://104.248.159.38/store/11/12/13/14
  SIM900.print("AT+HTTPPARA=\"URL\",\"http://104.248.159.38/store/");
  SIM900.print(random(0,100));
  SIM900.print("/");
  SIM900.print(random(0,100));
  SIM900.print("/");
  SIM900.print(random(0,100));
  SIM900.print("/");
  SIM900.print(random(0,100));
  SIM900.println(" \" ");
  delay(5000);
  ShowSerialData();

  SIM900.println("AT+HTTPACTION=0"); //submit request 
  delay(5000);
  ShowSerialData();

  SIM900.println("");
  delay(100);

  SIM900.println("AT+HTTPTERM");//baca data dari website yang diakses
  delay(1000);
  ShowSerialData();
} 

void ShowSerialData()
{
  while(SIM900.available()!=0)
    Serial.write(SIM900.read());
    delay(0); 

}

