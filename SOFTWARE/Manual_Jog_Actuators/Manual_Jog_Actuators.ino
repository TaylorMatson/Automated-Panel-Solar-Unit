#define Equator_IN 2
#define Equator_OUT 3
#define Side_IN 4
#define Side_OUT 5

String userInput;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Equator_OUT, OUTPUT);
  pinMode(Side_OUT, OUTPUT);
  pinMode(Equator_IN, OUTPUT);
  pinMode(Side_IN, OUTPUT);
  userInput = String("Stopped");
}

void loop() {
  // check to see if anything is available in serial recieve buffer
  userInput = Serial.readString();
  while (Serial.available() == 0) {
    Serial.println(userInput);
    if (userInput == "Stop") {
      userInput = String("Stopped");
    }
    
    if (userInput == "Equator In") {
      digitalWrite(Equator_OUT, LOW);
      delay(1);
      digitalWrite(Equator_IN, HIGH);
      delay(1);
      Serial.println("Intense light below, tilting down.");
      delay(5000);
    } else {
      digitalWrite(Equator_OUT, HIGH);
      delay(1);
      digitalWrite(Equator_IN, HIGH);
      delay(100);
    }
    
    if (userInput == "Equator Out") {
      digitalWrite(Equator_OUT, HIGH);
      delay(1);
      digitalWrite(Equator_IN, LOW);
      delay(1);
      Serial.println("Intense light above, tilting up.");
      delay(5000);
    } else {
      digitalWrite(Equator_OUT, HIGH);
      delay(1);
      digitalWrite(Equator_IN, HIGH);
      delay(100);
    }
    
    if (userInput == "Side In") {
      digitalWrite(Side_OUT, HIGH);
      delay(1);
      digitalWrite(Side_IN, LOW);
      delay(1);
      Serial.println("Intense light left, tilting left.");
      delay(5000);
    } else {
      digitalWrite(Side_OUT, HIGH);
      delay(1);
      digitalWrite(Side_IN, HIGH);
      delay(100);
    }
    
    if (userInput == "Side Out") {
      digitalWrite(Side_OUT, LOW);
      delay(1);
      digitalWrite(Side_IN, HIGH);
      delay(1);
      Serial.println("Intense light right, tilting right.");
      delay(5000);
    } else {
      digitalWrite(Side_OUT, HIGH);
      delay(1);
      digitalWrite(Side_IN, HIGH);
      delay(100);
    }
  }
}
