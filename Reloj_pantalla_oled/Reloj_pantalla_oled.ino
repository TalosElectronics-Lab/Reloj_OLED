
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

RTC_DS3231 RTC;

// Definir constantes
#define ANCHO_PANTALLA 128 // ancho pantalla OLED
#define ALTO_PANTALLA 64 // alto pantalla OLED

// Objeto de la clase Adafruit_SSD1306
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

String dia_semana[] = {"Domingo", "Lunes", "martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
char data[16];
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  //RTC.adjust(DateTime(__DATE__, __TIME__));
  DateTime now = RTC.now();
  Serial.println("Iniciando pantalla OLED");

  // Iniciar pantalla OLED en la dirección 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("No se encuentra la pantalla OLED");
    while (true);
  }

  // Limpir buffer
  display.clearDisplay();

  // Color del texto
  display.setTextColor(SSD1306_WHITE);

}

void loop()
{
  
  DateTime now = RTC.now();

  int hora = now.hour();
  int minutos = now.minute();
  int load = 0;
  uint8_t par;
  
  display.fillRoundRect(0, 0, 128, 12, 3, SSD1306_WHITE);
  display.setCursor(8, 2);
  // Tamaño del texto
  display.setTextSize(1);
  display.setTextColor(SSD1306_BLACK);
  display.print(dia_semana[now.dayOfWeek()]);
  display.print("  ");
  display.print(now.day());
  display.print("/");
  display.print(now.month());
  display.print("/");
  display.println(now.year());
  display.setTextColor(SSD1306_WHITE);
  // Tamaño del texto
  display.setTextSize(3);
  display.setCursor(15, 20);


  display.print(hora);
  par = now.second() & 0b1;
  if (par)
  {
    //numero impar
    display.print(" ");
  }
  else
  {
    //numero par
    display.print(":");
  }
  if (minutos < 10)
  {
    display.print("0");
  }
  else
  {
    // Posición del texto
    display.print("");
  }
  display.print(minutos);

  display.drawCircle(117, 48, 10, SSD1306_WHITE);
  display.setCursor(112, 45);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  if (now.second() < 10)
  {
    display.print("0");
    display.print(now.second());
  }
  else
  {
    display.println(now.second());
  }
  load = map(now.second(), 0, 59, 15, 106);
  display.drawLine(15, 50, load, 50, SSD1306_WHITE);

  // Enviar a pantalla
  display.display();

  // Limpir buffer
  display.clearDisplay();

}
