#define segA 8
#define segB 7
#define segC 6
#define segD 5
#define segE 4
#define segF 3
#define segG 2
#define digitOne 9
#define digitTwo 10
#define digitThree 11
#define digitFour 12
#define potentiometerPinOne A0
#define potentiometerPinTwo A1

// segment encoding for digits 0-9
const int digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

const int segmentPins[7] = {segA, segB, segC, segD, segE, segF, segG};

void setup() {
  // Set segment pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW); // Turn off initially
  }

  // Set digit control pins as outputs
  pinMode(digitOne, OUTPUT);
  pinMode(digitTwo, OUTPUT);
  digitalWrite(digitOne, HIGH); // Off initially
  digitalWrite(digitTwo, HIGH);

  pinMode(digitThree, OUTPUT);
  pinMode(digitFour, OUTPUT);
  digitalWrite(digitThree, HIGH); // Off initially
  digitalWrite(digitFour, HIGH);

  // Potentiometer input
  pinMode(potentiometerPinOne, INPUT);
  pinMode(potentiometerPinTwo, INPUT);
}

void displayDigit(int digit, int position) {
  // Turn off both digits before updating
  digitalWrite(digitOne, HIGH);
  digitalWrite(digitTwo, HIGH);
  digitalWrite(digitThree, HIGH);
  digitalWrite(digitFour, HIGH);

  // Set segment pins based on digit pattern (HIGH = ON for common cathode)
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[digit][i] ? HIGH : LOW);
  }

  // Activate the correct digit (LOW = ON)
  if (position == 1) {
    digitalWrite(digitOne, LOW);
  } else if (position == 2) {
    digitalWrite(digitTwo, LOW);
  } else if (position == 3) {
    digitalWrite(digitThree, LOW);
  } else if (position == 4) {
    digitalWrite(digitFour, LOW);
  }
}

void loop() {
  // Read potentiometer and map to 0–99
  int potValueOne = analogRead(potentiometerPinOne);
  int numberOne = map(potValueOne, 0, 910, 0, 50);

  // Break number into tens and ones
  int tensOne = numberOne / 10;
  int onesOne = numberOne % 10;

  // Read potentiometer and map to 0–99
  int potValueTwo = analogRead(potentiometerPinTwo);
  int numberTwo = map(potValueTwo, 0, 910, 0, 50);

  // Break number into tens and ones
  int tensTwo = numberTwo / 10;
  int onesTwo = numberTwo % 10;

  // Multiplex display
  displayDigit(tensOne, 1);
  delay(4); // Reduce delay for smoother display
  displayDigit(onesOne, 2);
  delay(4);
  displayDigit(tensTwo, 3);
  delay(4); // Reduce delay for smoother display
  displayDigit(onesTwo, 4);
  delay(4);
}
