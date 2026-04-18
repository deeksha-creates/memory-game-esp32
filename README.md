# memory-game-esp32
a memory game built with a custom PCB using an ESP32, LEDs, push buttons, and a TM1637 4-digit display.

The player must remember and repeat an increasing sequence of LED patterns.

### How It Works
1. On power-up, the display shows "PRESS"
2. Press any button to start the game
3. The system flashes a sequence using LEDs
4. Repeat the sequence using the buttons
5. Each correct round increases the level
6. A wrong input ends the game (FAIL)
7. Complete all levels to win (WIN)

### Components Used
- ESP32
- 3 × LEDs
- 3 × Push Buttons (with INPUT_PULLUP)
- TM1637 4-digit 7-segment display
- 220 ohm Resistors (for LEDs)

### Pin Configuration

| Component |	GPIO |
| -------- | -------- |
| Button 1	| 5 |
| Button 2	| 17 |
| Button 3	| 16 |
| LED 1	| 21 |
| LED 2	| 19 |
| LED 3	| 18 |
| TM1637 CLK	| 22 |
| TM1637 DIO	| 23 |

### Libraries Required
TM1637Display (by Avishay Orpaz)

Install via Arduino Library Manager.

### Clone this repository
Open the code in Arduino IDE / VS Code\
Install required libraries\
Select ESP32 board\
Upload the code\
Power the circuit and play!\

### Game Logic
- A random pattern is generated once
- Each level reveals one additional step
- Player input is checked in real-time
- Game ends immediately on wrong input

### Contributing

Feel free to fork this repo and improve the game!

### License

This project is open-source and free to use.
