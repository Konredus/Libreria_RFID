//-----------------------------------------------------------------------------------
//    Este codigo se encarga de leer el ID de la tarjeta
//    Libreria original modificado y traducido al español de :
//    https://www.instructables.com/id/Interfacing-RFID-RC522-With-Arduino-MEGA-a-Simple-/
//    Traduccion y adaptacion: Konrad Peschka 2020 
//    Instagram: @konredus
//-------------------------------------------------------------------------------------
 
/*
PINOUT de como conectamos el Modulo al Arduino:
RC522     Uno/Nano     MEGA
SDA         D10          D9
SCK         D13          D52
MOSI        D11          D51
MISO        12           D50
IRQ         N/C          N/C
GND         GND          GND
RST         D9           D8
3.3V       3.3V         3.3V
*/
//Incluimos las librerias del SPI y del RFID
#include <SPI.h>
#include <RFID.h>

//Se definen los pines que son puntuales para este Modulo
//Que son el Reset y el SS (Select)
#define RST_PIN         9 
#define SS_PIN          10   

//Creo la Clase RFID
RFID tarjeta_rfid(SS_PIN, RST_PIN); 

void setup()
{ 
  Serial.begin(9600);

  //Con estas 2 funciones inicializo el modulo
  SPI.begin(); 
  tarjeta_rfid.init();

  //muestro un mensaje por puerto serie
  Serial.println("Apoye su tarjeta o tag RFID");
}

void loop()
{
  //se queda esperando si se detecta una tarjeta RFID
  if (tarjeta_rfid.isCard())
  {
    //imprimimos por Serial que detectamos una tarjeta
    Serial.println("Tarjeta detectada:");
    
    //con esta funcion leemos la tarjeta y lo que se leyo
    //se guarda automaticamente en un vector[5] que crea internamente
    //este vector se llama tarjeta_rfid.serNum[5], tiene 5 posiciones de 0 a 4
    tarjeta_rfid.readCardSerial();

    for(int i=0;i<5;i++)
    {
      Serial.println(tarjeta_rfid.serNum[i]);
    }
  }
  delay(1000);
}
