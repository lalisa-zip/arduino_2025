const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;
const int buttonPin = 2;  

int mood = 0;
const int neutralMood = 10;
bool ButtonPressed = false;
unsigned long lastPressTime = 0;  

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  
  mood = neutralMood;
}

void loop() {
  int buttonState = digitalRead(buttonPin);

 
  if (buttonState == LOW && !ButtonPressed) {
    ButtonPressed = true;
    mood++;
    if (mood > 20) mood = 20;
    lastPressTime = millis(); 、
  }

  if (buttonState == HIGH && ButtonPressed) {
    ButtonPressed = false;
  }

  if (millis() - lastPressTime > 1500 && mood > 0) { 
    mood--;
    if (mood < 0) mood = 0;
    lastPressTime = millis();
  }

  showLEDState(mood);
  delay(50);
}

void showLEDState(int m) {
  // red to purple to blue range 
  int redValue = map(m, 0, 20, 255, 0); 
  int greenValue = map(m, 0, 20, 0, 255); 
  int blueValue = 255;                   

  analogWrite(RledPin, redValue);
  analogWrite(GledPin, greenValue);
  analogWrite(BledPin, blueValue);
}
