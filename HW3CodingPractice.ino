const int buttonPin = 2;  
const int ledPin = 3;     

int buttonState;           
int lastButtonState = LOW; 
int mode = 0;              
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; 

unsigned long previousMillis = 0; 

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis(); 
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        mode++;
        if (mode > 3) {
          mode = 0; // back to steady
        }
      }
    }
  }

  lastButtonState = reading;

  if (mode == 0) {
    // steady ON
    digitalWrite(ledPin, HIGH);
  } 
  else {
    unsigned long currentMillis = millis();
    int interval;

    if (mode == 1) interval = 1000;   
    if (mode == 2) interval = 400;    
    if (mode == 3) interval = 150;    

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      digitalWrite(ledPin, !digitalRead(ledPin));
    }
  }
}
