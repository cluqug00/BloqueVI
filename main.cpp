#include <Arduino.h>
#include <DIYables_IRcontroller.h> 

#define BUZZER_PIN 18
#define LED_PIN_1 23
#define LED_PIN_2 22
#define LED_PIN_3 21
#define LED_PIN_4 19
#define IR_RECEIVER_PIN 13
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

DIYables_IRcontroller_21 irController(IR_RECEIVER_PIN, 200);

enum LedSequence
{
  NONE,
  SEQUENCE_1,
  SEQUENCE_2,
  SEQUENCE_3,
  SEQUENCE_4,
  ALL_ON
};
LedSequence currentSequence = NONE;
bool isVillancicoPlaying = false;
int tempo = 108;

// Se ponen las notas, seguidas de la duración.
// El número 4 es un cuarto de nota, 8 un octavo y 16 es 1/16
// los valores negativos son para marcar notas con puntillo

int melody[] = {
    // We Wish You a Merry Christmas

    NOTE_C5, 4, // 1
    NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
    NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
    NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
    NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,
    NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8,
    NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,

    NOTE_F5, 2, NOTE_C5, 4, // 8
    NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
    NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
    NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
    NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,
    NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8,
    NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, NOTE_C5, 4,

    NOTE_F5, 4, NOTE_F5, 4, NOTE_F5, 4, // 17
    NOTE_E5, 2, NOTE_E5, 4,
    NOTE_F5, 4, NOTE_E5, 4, NOTE_D5, 4,
    NOTE_C5, 2, NOTE_A5, 4,
    NOTE_AS5, 4, NOTE_A5, 4, NOTE_G5, 4,
    NOTE_C6, 4, NOTE_C5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, NOTE_C5, 4,
    NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
    NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,

    NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8, // 27
    NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,
    NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8,
    NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, NOTE_C5, 4,
    NOTE_F5, 4, NOTE_F5, 4, NOTE_F5, 4,
    NOTE_E5, 2, NOTE_E5, 4,
    NOTE_F5, 4, NOTE_E5, 4, NOTE_D5, 4,

    NOTE_C5, 2, NOTE_A5, 4, // 36
    NOTE_AS5, 4, NOTE_A5, 4, NOTE_G5, 4,
    NOTE_C6, 4, NOTE_C5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, NOTE_C5, 4,
    NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
    NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
    NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
    NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,

    NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, // 45
    NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, NOTE_C5, 4,
    NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
    NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
    NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
    NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,

    NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, // 53
    NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2,

    REST, 1, // Para que no suene

};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;
void playVillancicoWithLights();
void stopVillancico();
void runLedSequence(LedSequence sequence);
void ledSequence1();
void ledSequence2();
void ledSequence3();
void ledSequence4();
void setAllLedsOn();

void setup()
{
  Serial.begin(115200);
  irController.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
}

void loop()
{
  Key21 command = irController.getKey();

  // Gestión de los comandos del mando
  if (command != Key21::NONE)
  {
    switch (command)
    {
    case Key21::KEY_1:
      currentSequence = SEQUENCE_1;
      break;
    case Key21::KEY_2:
      currentSequence = SEQUENCE_2;
      break;
    case Key21::KEY_3:
      currentSequence = SEQUENCE_3;
      break;
    case Key21::KEY_4:
      currentSequence = SEQUENCE_4;
      break;
    case Key21::KEY_5:
      currentSequence = ALL_ON;
      break;
    case Key21::KEY_6:
      isVillancicoPlaying = !isVillancicoPlaying;
      if (isVillancicoPlaying)
      {
        Serial.println("Villancico comenzado");
        playVillancicoWithLights();
      }
      else
      {
        Serial.println("Villancico detenido");
        stopVillancico();
      }
      break;
    default:
      // Si se presiona un botón no definido, detener todo
      Serial.println("Comando indefinido. Deteniendo villancico y luces.");
      if (isVillancicoPlaying)
      {
        Serial.println("Villancico detenido por otro botón");
        stopVillancico();
      }
      currentSequence = NONE; // Detener la secuencia de LEDs
      break;
    }
  }

  // Ejecutar la secuencia de LEDs actual
  if (!isVillancicoPlaying)
  {
    runLedSequence(currentSequence);
  }
}

// Función para reproducir y detener el villancico con luces
void playVillancicoWithLights() {
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // Calcula la duración de cada nota
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider; // Nota regular
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // Aumenta la duración para notas puntuales
    }

    // Toca la nota durante el 90% de la duración, dejando el 10% como pausa
    tone(BUZZER_PIN, melody[thisNote], noteDuration * 0.9);
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, HIGH);
    digitalWrite(LED_PIN_3, HIGH);
    digitalWrite(LED_PIN_4, HIGH);
    delay(noteDuration);
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, LOW);
    digitalWrite(LED_PIN_4, LOW);
    
    // Detiene la generación de la onda antes de la siguiente nota.
    noTone(BUZZER_PIN);

    // Verifica si se ha presionado otro botón
    Key21 command = irController.getKey();
    if (command != Key21::NONE && command != Key21::KEY_6) {
      stopVillancico(); // Detener el villancico si se presiona un botón diferente
      return; // Salir de la función
    }
  }
}



void stopVillancico()
{
  noTone(BUZZER_PIN);
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(LED_PIN_3, LOW);
  digitalWrite(LED_PIN_4, LOW);
  isVillancicoPlaying = false; // Resetea el estado del villancico
  currentSequence = NONE;      // Reinicia la secuencia de LEDs
}

// Funciones de las secuencias de LEDs
void runLedSequence(LedSequence sequence)
{
  switch (sequence)
  {
  case SEQUENCE_1:
    ledSequence1();
    break;
  case SEQUENCE_2:
    ledSequence2();
    break;
  case SEQUENCE_3:
    ledSequence3();
    break;
  case SEQUENCE_4:
    ledSequence4();
    break;
  case ALL_ON:
    setAllLedsOn();
    break;
  default:
    break;
  }
}

void ledSequence1()
{
  digitalWrite(LED_PIN_1, HIGH);
  delay(200);
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, HIGH);
  delay(200);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(LED_PIN_3, HIGH);
  delay(200);
  digitalWrite(LED_PIN_3, LOW);
  digitalWrite(LED_PIN_4, HIGH);
  delay(200);
  digitalWrite(LED_PIN_4, LOW);
}

void ledSequence2()
{
  digitalWrite(LED_PIN_1, HIGH);
  digitalWrite(LED_PIN_3, HIGH);
  delay(200);
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_3, LOW);
  digitalWrite(LED_PIN_2, HIGH);
  digitalWrite(LED_PIN_4, HIGH);
  delay(200);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(LED_PIN_4, LOW);
}

void ledSequence3()
{
  digitalWrite(LED_PIN_1, HIGH);
  delay(100);
  digitalWrite(LED_PIN_2, HIGH);
  delay(100);
  digitalWrite(LED_PIN_3, HIGH);
  delay(100);
  digitalWrite(LED_PIN_4, HIGH);
  delay(100);
  digitalWrite(LED_PIN_1, LOW);
  delay(100);
  digitalWrite(LED_PIN_2, LOW);
  delay(100);
  digitalWrite(LED_PIN_3, LOW);
  delay(100);
  digitalWrite(LED_PIN_4, LOW);
  delay(100);
}

void ledSequence4()
{
  digitalWrite(LED_PIN_1, HIGH);
  digitalWrite(LED_PIN_2, HIGH);
  delay(500);
  digitalWrite(LED_PIN_3, HIGH);
  digitalWrite(LED_PIN_4, HIGH);
  delay(500);
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  delay(500);
  digitalWrite(LED_PIN_3, LOW);
  digitalWrite(LED_PIN_4, LOW);
  delay(500);
}

void setAllLedsOn()
{
  digitalWrite(LED_PIN_1, HIGH);
  digitalWrite(LED_PIN_2, HIGH);
  digitalWrite(LED_PIN_3, HIGH);
  digitalWrite(LED_PIN_4, HIGH);
}
