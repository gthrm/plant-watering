// даём разумное для пина, к которому подключена помпа
#define POMP1_PIN        5
#define POMP2_PIN        6
// даём разумное для пина, к которому подключён датчик влажности почвы
#define HUMIDITY_PIN    A0
// минимальный порог влажности почвы
#define HUMIDITY_MIN    30
// максимальный порог влажности почвы
#define HUMIDITY_MAX    80
// интервал между проверкой на полив растения
#define INTERVAL        6000
// переменная для хранения показания влажности почвы
unsigned int humidity = 0;

// статическая переменная для хранения времени
unsigned long waitTime = 0;

void setup(void)
{
  Serial.begin(9600);
  // пин помпы в режим выхода
  pinMode(POMP1_PIN, OUTPUT);
  pinMode(POMP2_PIN, OUTPUT);
  digitalWrite(POMP1_PIN, 1); // выключть
  digitalWrite(POMP2_PIN, 1); // выключть
}

void loop(void)
{
  // считываем текущее показания датчика влажности почвы
  int humidityNow = analogRead(HUMIDITY_PIN);
  int humidityNowMap = map(humidityNow, 545, 239, 0, 100);
  // если показания текущей влажности почвы
  // не равняется предыдущему запросу
  if (humidityNowMap != humidity) {
    // сохраняем текущие показания влажности
    humidity = humidityNowMap;
    // и выводим показания влажности на дисплей
    Serial.println(humidityNow);
  }
  // если прошёл заданный интервал времени
  // и значения датчика влажности меньше допустимой границы
  if ((waitTime == 0 || millis() - waitTime > INTERVAL) && humidity < HUMIDITY_MIN ) {
    // включаем помпу
    digitalWrite(POMP1_PIN, 0);
    digitalWrite(POMP2_PIN, 0);
    Serial.println("включаем помпу");
    // ждём 2 секунды
    delay(2000);
    // выключаем помпу
    digitalWrite(POMP1_PIN, 1);
    digitalWrite(POMP2_PIN, 1);
    Serial.println("выключаем помпу");
    // приравниваем переменной waitTime
    // значение текущего времени плюс 3 минуты
    waitTime = millis();
  }
  delay(100);
}
