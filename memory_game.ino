#include <TM1637Display.h>

const int BTN_1 = 5; // GPIO 16
const int BTN_2 = 17; // GPIO 17
const int BTN_3 = 16; // GPIO 18

const int LED_1 = 21; // GPIO 19
const int LED_2 = 19; // GPIO 21
const int LED_3 = 18; // GPIO 22

#define CLK 22
#define DIO 23 

// -------- OBJECT --------
TM1637Display display(CLK, DIO);

// -------- GAME VARS --------
const int maxLevel = 20;
int pattern[maxLevel];
int level = 1;

int LED_PINS[3] = {LED_1, LED_2, LED_3};

uint8_t DISP_PRESS[] = {
  0x73, // P
  0x50, // r (approx)
  0x79, // E
  0x6D  // S
};

uint8_t DISP_FAIL[] = {
  0x71, // F
  0x77, // A
  0x06,  // I (approx)
  0x38 // L
};

uint8_t DISP_WIN[] = {
  0x3E, // U (looks like W-ish)
  0x06, // I
  0x54, // n (approx)
  0x00  // blank
};

// -------- SETUP --------
void setup() {
  Serial.begin(115200);

  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  display.setBrightness(5);

  randomSeed(analogRead(0));

  generatePattern();
}

// -------- LOOP --------
void loop() {
  showIntro();

  level = 1;

  while (level <= maxLevel) {
    display.showNumberDec(level);

    showPattern(level);

    if (!getUserInput(level)) {
      showFail();
      return; // restart game
    }

    level++;
    delay(500);
  }

  showWin();
}

// -------- FUNCTIONS --------

// generate full pattern once
void generatePattern() {
  for (int i = 0; i < maxLevel; i++) {
    pattern[i] = random(0, 3);
  }
}

// intro screen
void showIntro() {
   display.setSegments(DISP_PRESS); // looks like DISP_PRESS
  delay(500);
  display.clear();
  delay(200);
  display.setSegments(DISP_PRESS);

  // wait for any button
  while (true) {
    if (digitalRead(BTN_1) == LOW ||
        digitalRead(BTN_2) == LOW ||
        digitalRead(BTN_3) == LOW) {
      delay(300);
      break;
    }
  }
}

// show LED sequence
void showPattern(int len) {
  delay(500);

  for (int i = 0; i < len; i++) {
    int led = LED_PINS[pattern[i]];

    digitalWrite(led, HIGH);
    delay(400);
    digitalWrite(led, LOW);
    delay(200);
  }
}

// take user input
bool getUserInput(int len) {
  int index = 0;

  while (index < len) {
    if (digitalRead(BTN_1) == LOW) {
      if (!checkInput(index, 0)) return false;
      flashLED(LED_1);
      waitRelease(BTN_1);
      index++;
    }
    else if (digitalRead(BTN_2) == LOW) {
      if (!checkInput(index, 1)) return false;
      flashLED(LED_2);
      waitRelease(BTN_2);
      index++;
    }
    else if (digitalRead(BTN_3) == LOW) {
      if (!checkInput(index, 2)) return false;
      flashLED(LED_3);
      waitRelease(BTN_3);
      index++;
    }
  }
  return true;
}

void waitRelease(int btn) {
  while (digitalRead(btn) == LOW);
  delay(50); // debounce
}

// check each press immediately (better UX)
bool checkInput(int index, int value) {
  if (pattern[index] != value) {
    return false;
  }
  return true;
}

// LED feedback
void flashLED(int pin) {
  digitalWrite(pin, HIGH);
  delay(200);
  digitalWrite(pin, LOW);
  delay(200);
}

// fail animation
void showFail() {
  display.setSegments(DISP_FAIL);

  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    delay(200);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    delay(200);
  }

  delay(1500);
}

// win animation
void showWin() {
  display.setSegments(DISP_WIN);

  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_1, HIGH); delay(100); digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH); delay(100); digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, HIGH); delay(100); digitalWrite(LED_3, LOW);
  }

  delay(2000);
}
