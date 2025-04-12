#define B 3950            // B-коэффициент
#define SERIAL_R 39000    // сопротивление постоянного резистора, 39 кОм
#define THERMISTOR_R 43000// номинальное сопротивления термистора, 43 кОм
#define NOMINAL_T 25      // номинальная температура

// Пины ADC для ESP32 (например, GPIO36 и GPIO39)
#define TEMP_SENSOR_PIN 36 // Аналоговый вход для термистора
#define PRESSURE_SENSOR_PIN 39 // Аналоговый вход для давления

void setup() {
  Serial.begin(115200);
  analogReadResolution(10); // Устанавливаем разрешение АЦП 10 бит (0-1023)
  
  // На ESP32 pinMode для аналоговых пинов не обязателен, но можно оставить
  pinMode(TEMP_SENSOR_PIN, INPUT);
  pinMode(PRESSURE_SENSOR_PIN, INPUT);
}

void loop() {
  // Чтение и обработка температуры
  int t = analogRead(TEMP_SENSOR_PIN);
  float tr = 1023.0 / t - 1;
  tr = SERIAL_R / tr;
  float st = tr / THERMISTOR_R;
  st = log(st);
  st /= B;
  st += 1.0 / (NOMINAL_T + 273.15);
  st = 1.0 / st;
  st -= 273.15;

  // Чтение и обработка давления
  int pressureRaw = analogRead(PRESSURE_SENSOR_PIN);
  float Pressure = map(pressureRaw, 96, 920, 0, 150);
  float bar = Pressure * 0.069;
  float kpa = Pressure * 6.9 / 100;

  // Формирование строки вывода
  Serial.print("begin");
  
  // Проверка тревоги температуры
  if (analogRead(TEMP_SENSOR_PIN) > 900) {
    Serial.print("talarmk");
  } else {
    Serial.print(st, 0);
    Serial.print("k");
  }

  // Проверка тревоги давления
  if (pressureRaw > 750) {
    Serial.print("palarmc");
  } else {
    Serial.print(kpa, 2);
    Serial.print("c");
  }
  
  Serial.println("end");
  delay(1500);
}
