#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

// Cria um objeto para o BMP085
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup() {
  Serial.begin(9600);

  if (!bmp.begin()) {
    Serial.println("Não foi possível encontrar o BMP085");
    while (1); // Loop infinito se o sensor não for encontrado
  }

  Serial.println("BMP085 encontrado");
}

void loop() {
  sensors_event_t event;
  bmp.getEvent(&event);
  float qnh_local = 1015; //PUXE OS DADOS DO METAR DO AEROPORTO MAIS PROXIMO E INCLUA AQUI O OFFSET
  
  if (event.pressure) {
    // Leitura de pressão e temperatura
    float temperatura;
    bmp.getTemperature(&temperatura);
    
    // Imprime os dados no monitor serial
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" C");

    Serial.print("Pressão: ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    
    // Calcula e imprime a altitude
    float altitude = bmp.pressureToAltitude(qnh_local, event.pressure); // Ajuste o valor de referência para a pressão ao nível do mar
    Serial.print("Altitude: ");
    Serial.print(altitude);
    Serial.println(" m");
  } else {
    Serial.println("Não foi possível ler a pressão");
  }
  
  delay(2000); // Aguarda 2 segundos antes de ler novamente
}
