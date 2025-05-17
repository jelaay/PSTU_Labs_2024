#include <OneWire.h>
#include <DallasTemperature.h>

// Определение пинов
const int lightSensorPin = A1;    // Фоторезистор на A1
const int ledPin = 9;              // Светодиод на 9
const int tempSensorPin = 2;       // Датчик температуры на D2

// Пороговые значения (можно настроить)
const int lightThreshold = 75;     // Новый порог освещенности (0-1023)
const float tempThreshold = 25.0;   // Порог температуры в °C

// Настройка OneWire и DallasTemperature
OneWire oneWire(tempSensorPin);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);               // Инициализация Serial-порта
  pinMode(ledPin, OUTPUT);          // Настройка светодиода как выхода
  sensors.begin();                  // Инициализация датчика температуры
}

void loop() {
  // Чтение данных с датчиков
  int lightValue = analogRead(lightSensorPin)/10; // Значение освещенности (0-1023)
  sensors.requestTemperatures();                 // Запрос температуры
  float tempValue = sensors.getTempCByIndex(0); // Температура в °C

  // Определение состояния подогрева
  bool heating = (lightValue > lightThreshold && tempValue > tempThreshold);
  digitalWrite(ledPin, heating ? HIGH : LOW);

  // Новый формат вывода с явным указанием состояния
  Serial.print("Освещенность:");
  Serial.print(lightValue);
  Serial.print(",Температура:");
  Serial.print(tempValue);
  Serial.print(",Подогрев:");
  Serial.println(heating ? "ON" : "OFF"); // Ключевое изменение!


  delay(1000); // Задержка 1 секунда
}
