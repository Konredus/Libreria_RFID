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

//creo un array con el dato qeu quiero chequear
//este codigo lo obtenemos del ejemplo de lectura
const int id_usuario[5]={158,137,198,219,10};

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

    //lo que hago en este if es llamar a la funcion que 
    //se encarga de chequear posicion por posicion lo
    //que se leyo de la tarjeta
    if(chequeo_tarjeta())
    {
       Serial.println("Acceso Aceptado");
    }
    else
    {
      Serial.println("Acceso Denegado");
    }
    
  }
  delay(1000);
}

//Aqui esta la funcion que se encarga de verificar
//si cada una de las posiciones coincide con el id_usuario
//que ingresamos arriba de todo

bool chequeo_tarjeta()
{
  tarjeta_rfid.readCardSerial();
  //con este for recorremos todas las posiciones
  for(int i=0;i<5;i++)
  {
    //el truco de este if es que si siguen coincidiendo
    //no hace nada
    if(tarjeta_rfid.serNum[i]==id_usuario[i])
    {
	
    }
    else  //en caso de que 1 posicion no coincida, sale del for y retorna 0
    {
      return 0;
    }
  }
  //si llego hasta aca, es por que todas las posiciones coincidieron
  //por ende esta funcion nos va a retornar 1
  return 1;
}
