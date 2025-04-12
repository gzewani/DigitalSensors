#define PRESSURE_SENSOR_PIN 39 // Аналоговый вход для давления

void setup() {
  Serial.begin(115200);
  analogReadResolution(10); // Устанавливаем разрешение АЦП 10 бит (0-1023)
  
  // На ESP32 pinMode для аналоговых пинов не обязателен, но можно оставить
  pinMode(PRESSURE_SENSOR_PIN, INPUT);
}

void loop() {
  // Чтение и обработка давления
  int pressureRaw = analogRead(PRESSURE_SENSOR_PIN);
  float Pressure = map(pressureRaw, 96, 920, 0, 150);
  float kpa = Pressure * 6.9 / 100;

  // Формирование строки вывода
  Serial.print("begin");
  
  // Проверка тревоги давления
  if (pressureRaw > 750) {
    Serial.print("palarmc");
  } else {
    Serial.print(kpa, 2); // Давление в кПа
    Serial.print("c");
  }
  
  Serial.println("end");
  delay(1500);
}
