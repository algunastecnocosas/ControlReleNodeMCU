/*
* Módulo NodeMCU genera una wifi propia y actúa como servidor web desde el  * que se controla el estado de un módulo de 2 reles. * 
 * Basado en "Encender y apagar LED con WiFi usando NodeMCU ESP8266" en 
 * https://parzibyte.me/blog/2020/02/11/encender-apagar-led-wifi-nodemcu-esp8266/
 * 
 */


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
// Datos de la red wifi que genera el módulo NodeMCU
const char *NOMBRE_RED = "ControlReles",
           *CLAVE_RED = "holacaracola";

const int PUERTO = 80;

IPAddress ip(192, 168, 1, 1);    // El servidor web creado por el NodeMCU se accederá en la dirección 192.168.1.1
IPAddress puertaDeEnlace(192, 168, 1, 1);
IPAddress mascaraDeRed(255, 255, 255, 0);

ESP8266WebServer servidor(PUERTO);

// Conexion de los dos reles
int pinRele1 = 8;
int pinRele2 = 7;

// Estados de los reles. Inicialmente ambos estan apagados
boolean estadoRele1 = false;    
boolean estadoRele2 = false;

// ********** FUNCIONES QUE PRODUCEN LA INTERFAZ WEB
String obtenerInterfaz()
{
  String HtmlRespuesta = "<!DOCTYPE html>"
                         "<html lang='en'>"
                         "<head>"
                         "<meta charset='UTF-8'>"
                         "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                         "<title>Control de 2 reles</title>"
                         "</head>"
                         "<body>";
  HtmlRespuesta += "<h1>**Encender y apagar RELE 1**</h1>";
  HtmlRespuesta += "<p>El Rele1 est&aacute; actualmente ";
  if (estadoRele1)
  {
    HtmlRespuesta += "encendido</p>";
    HtmlRespuesta += "<a href='/apagar1'>Apagar</a>";
  }
  else
  {
    HtmlRespuesta += "apagado</p>";
    HtmlRespuesta += "<a href='/encender1'>Encender</a>";
  }
  HtmlRespuesta += "<h1>**Encender y apagar RELE 2**</h1>";
  HtmlRespuesta += "<p>El Rele2 est&aacute; actualmente ";
  if (estadoRele2)
  {
    HtmlRespuesta += "encendido</p>";
    HtmlRespuesta += "<a href='/apagar2'>Apagar</a>";
  }
  else
  {
    HtmlRespuesta += "apagado</p>";
    HtmlRespuesta += "<a href='/encender2'>Encender</a>";
  }

  HtmlRespuesta += "<br><br><br><br><a href='http://enlacezapatista.ezln.org.mx/'><i>Para todxs todo. Para nosotrxs nada.</i></a>";
  HtmlRespuesta += "</body>"
                   "</html>";
  return HtmlRespuesta;
}

void mostrarInterfazHTML()
{
  servidor.send(200, "text/html", obtenerInterfaz());
}

void rutaRaiz()
{
  mostrarInterfazHTML();
}

void rutaNoEncontrada()
{
  servidor.send(404, "text/plain", "404");
}
// ***********************





// ******* FUNCIONES QUE ACTIVAN Y DESACTIVAN EL RELE1 Y EL RELE2
void rutaEncenderRele1()
{
  estadoRele1 = true;
  digitalWrite(pinRele1, HIGH);  
  Serial.println("Rele1 ON");
  mostrarInterfazHTML();
}

void rutaApagarRele1()
{
  estadoRele1 = false;
  digitalWrite(pinRele1, LOW);  
  Serial.println("Rele1 OFF");
  mostrarInterfazHTML();
}

void rutaEncenderRele2()
{
  estadoRele2 = true;
  digitalWrite(pinRele2, HIGH); 
  Serial.println("Rele2 ON");
  mostrarInterfazHTML();
}

void rutaApagarRele2()
{
  estadoRele2 = false;
  digitalWrite(pinRele2, LOW);  
  Serial.println("Rele2 OFF");
  mostrarInterfazHTML();
}
// ***************************




void setup()
{

  pinMode(pinRele1, OUTPUT);
  pinMode(pinRele2, OUTPUT);

  // Configurar como un access point
  WiFi.softAP(NOMBRE_RED, CLAVE_RED);
  WiFi.softAPConfig(ip, puertaDeEnlace, mascaraDeRed);
  delay(100);

  // Configuramos la ruta y la función que responderá a la solicitud de dicha ruta
  servidor.on("/", rutaRaiz);
  servidor.on("/encender1", rutaEncenderRele1);
  servidor.on("/apagar1", rutaApagarRele1);
  servidor.on("/encender2", rutaEncenderRele2);
  servidor.on("/apagar2", rutaApagarRele2);
  servidor.onNotFound(rutaNoEncontrada);
  // Empezar a escuchar
  servidor.begin();

}



void loop() 
{

  servidor.handleClient();
  
}
