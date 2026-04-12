const int BTN_1 = 5; // GPIO 16
const int BTN_2 = 17; // GPIO 17
const int BTN_3 = 16; // GPIO 18

const int LED_1 = 21; // GPIO 19
const int LED_2 = 19; // GPIO 21
const int LED_3 = 18; // GPIO 22

const int arrSize = 4;
short int pattern[arrSize], userInput[arrSize];
int LED_PINS[3] = {LED_1, LED_2, LED_3}; 

void setup() {
  Serial.begin(115200);
  // Use INPUT_PULLUP to use internal resistor
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  Serial.begin(115200);
  randomSeed(analogRead(0));
}

void loop() {
  // generate random pattern
  for (int i = 0; i < arrSize; i++) {
    pattern[i] = random(0, 3);
    Serial.println(pattern[i]);
  }
  
  // blink LED acc to pattern
  for (int i = 0; i < arrSize; i++) {
    currentPatternVal = pattern[i];
    int currentLedPin = LED_PINS[currentPatternVal];

    digitalWrite(currentLedPin, HIGH);
    delay(1000);
    digitalWrite(currentLedPin, LOW);
    delay(1000);
  }
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, HIGH);
  delay(1000);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  delay(1000);
  
  // open up buttons
  
  // user input and add to userInput[]
  int input = 0;
  while (input < 3) {
    int BTN_1_state = digitalRead(BTN_1);
    int BTN_2_state = digitalRead(BTN_2);
    int BTN_3_state = digitalRead(BTN_3);

    
    
    delay(20);
  }

  // compare

  // print correct and wrong answer pattern on LEDs
}
