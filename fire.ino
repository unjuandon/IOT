

#include <FirebaseESP8266.h> // incluimos librería
#include <Arduino_JSON.h>     //Librería para obtener datos JSON en arduino
#include <ESP8266WiFi.h>    //Habilitamos wifi                                               // esp8266 library
// firebase library

#define FIREBASE_HOST "https://estado-73a8e.firebaseio.com/"                         // El nombre del proyecto y la dirección de firebase.
#define FIREBASE_AUTH "fYee0VuFKFpyBYpsaN3KtFjqCEa8SAg1LqVCc02W"                    // Clave secreta de seguridad que otorga firebase.
#define WIFI_SSID "DYNAMICS MAKER"                                          // Nombre la red pública
#define WIFI_PASSWORD "MAKERDYNAMICS2020" 

FirebaseData firebaseData;
FirebaseData ledData;

                                                   
int led = 14;                                                                // Indicador.
void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(led, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //Intentamos conectar al wifi.
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //Imprimimos la dirreción ip
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // Conexión a firebase.
 //Enviamos el string inicial al indicador.
}

void loop() {

  if (Firebase.getString(ledData, "/Estado/led")){   //Obtenemos el string que está en firebase en el nodo hijo.
    Serial.println(ledData.stringData()); //Imprimimos por el puerto el dato del string
    if (ledData.stringData() == "1") {   
    digitalWrite(led, HIGH);
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(led, LOW);
    }
  }
  delay(100);
}
