// Código do protótipo montado físicamente

#include "DHT.h" // Inclui biblioteca Do sensor DHT11

// Define o pino do DHT11
#define DHTPIN 13  // Substitua pelo pino correto do sensor DHT11
#define DHTTYPE DHT11  // Define Tipo de sensor DHT (DHT11)

// Define os pinos do LED e do buzzer
const int ledPin = 27;         // Pino do LED (temperatura >= 27 °C)
const int alertLedPin = 26;    // Pino do LED de alerta (temperatura < 2 °C)
const int buzzerPin = 25;      // Pino do buzzer ativo

// Inicializa o sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0; // Armazena o tempo anterior
const long interval = 5000;       // Intervalo de 5 segundos (5000 ms)

void setup() {
  // Inicializa os pinos como saída
  pinMode(ledPin, OUTPUT);
  pinMode(alertLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Inicializa a comunicação serial
  Serial.begin(115200);

  // Inicia o sensor DHT
  dht.begin();
}

void loop() {
  // Aguarda 1 segundos entre as leituras
  delay(1000);

  // Lê a umidade e a temperatura (em Celsius)
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Verifica se houve falha na leitura
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Falha ao ler do sensor DHT11!");
    return;
  }

  // Mostra a umidade e a temperatura no monitor serial
  Serial.print("Umidade: ");
  Serial.print(humidity);
  Serial.print("%  Temperatura: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Verifica a temperatura
  if (temperature >= 27.0) { // Condição para quando a temperatura estiver maior ou igual a 27 gruas
    digitalWrite(ledPin, HIGH); // Acende o LED verde

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      tone(buzzerPin, 500); // Liga o buzzer
      delay(2000); // Apita por 2 segundos
      noTone(buzzerPin); // Desliga o buzzer
    }
  } else {
    digitalWrite(ledPin, LOW);  // Apaga o LED normal
    noTone(buzzerPin); // Desliga o sinal sonoro do buzzer
  }

  // Acende o LED de alerta se a temperatura for menor que 2 °C
  if (temperature < 27.0) {   // Condição para quando a temperatura estiver que 27 graus
    digitalWrite(alertLedPin, HIGH); // Acende o LED verde
  } else {
    digitalWrite(alertLedPin, LOW);  // Apaga o LED verde
    
    delay(1000); //delay de 1 segundo para o loop do código
}
}
