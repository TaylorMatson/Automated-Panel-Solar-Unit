#define Equator_IN 2
#define Equator_OUT 3
#define Side_IN 4
#define Side_OUT 5

String userInput;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  pinMode(Equator_OUT, OUTPUT);
  pinMode(Side_OUT, OUTPUT);
  pinMode(Equator_IN, OUTPUT);
  pinMode(Side_IN, OUTPUT);
  userInput = String("Stopped");
}

void loop() {
  int equatorRight = analogRead( A0 );
  int equatorLeft = analogRead( A1 );
  int rearRight = analogRead( A2 );
  int rearLeft = analogRead( A3 );
  int ERFiltered = round(((equatorRight * 15) + equatorRight) / 16); //one-pole filter
  int ELFiltered = round(((equatorLeft * 15) + equatorLeft) / 16); //one-pole filter
  int RRFiltered = round(((rearRight * 15) + rearRight) / 16); //one-pole filter
  int RLFiltered = round(((rearLeft * 15) + rearLeft) / 16); //one-pole filter
  int differenceVertical = (rearLeft + rearRight) - (equatorLeft + equatorRight); // check the diffirence of up and down
  int differenceHorizontal = (rearLeft + equatorLeft) - (rearRight + equatorRight); // check the diffirence og left and right
  int tolerance = 40;

  Serial.println("Vertical Difference: ");
  Serial.println(differenceVertical);
  Serial.println(" Horizontal Difference: ");
  Serial.println(differenceHorizontal);
  Serial.println(" Check positive vertical difference.");
  if (differenceVertical > tolerance) {
    digitalWrite(Equator_OUT, HIGH);
    delay(1);
    digitalWrite(Equator_IN, LOW);
    delay(1);
    Serial.println("Intense light at rear, tilt up.");
    delay(5000);
  } else {
    digitalWrite(Equator_OUT, HIGH);
    delay(1);
    digitalWrite(Equator_IN, HIGH);
    delay(100);
  }
  Serial.println("Check negative vertical difference.");
  if (differenceVertical < -tolerance) {
    digitalWrite(Equator_OUT, LOW);
    delay(1);
    digitalWrite(Equator_IN, HIGH);
    delay(1);
    Serial.println("Intense light at equator, tilt down.");
    delay(5000);
  } else {
    digitalWrite(Equator_OUT, HIGH);
    delay(1);
    digitalWrite(Equator_IN, HIGH);
    delay(100);
  }
  Serial.println("Check positive horizontal difference.");
  if (differenceHorizontal > tolerance) {
    digitalWrite(Side_OUT, LOW);
    delay(1);
    digitalWrite(Side_IN, HIGH);
    delay(1);
    Serial.println("Intense light at right, tilt right.");
    delay(5000);
  } else {
    digitalWrite(Side_OUT, HIGH);
    delay(1);
    digitalWrite(Side_IN, HIGH);
    delay(100);
  }
  Serial.println("Check negative horizontal difference.");
  if (differenceHorizontal < -tolerance) {
    digitalWrite(Side_OUT, HIGH);
    delay(1);
    digitalWrite(Side_IN, LOW);
    delay(1);
    Serial.println("Intense light at left, tilt left.");
    delay(5000);
  } else {
    digitalWrite(Side_OUT, HIGH);
    delay(1);
    digitalWrite(Side_IN, HIGH);
    delay(100);
  }
}
