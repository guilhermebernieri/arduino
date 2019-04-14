const int MAX_LEVEL = 100;
int sequence[MAX_LEVEL];
int sound[MAX_LEVEL];
int gamer_sequence[MAX_LEVEL];
int level = 1;
int note = 0;
int velocity = 1000;

void setup() {
  pinMode(13, OUTPUT); //green led
  pinMode(12, OUTPUT); //red led
  pinMode(11, OUTPUT); //yellow led
  pinMode(10, OUTPUT); //blue led

  pinMode(7, INPUT_PULLUP); //button 1
  pinMode(6, INPUT_PULLUP); //button 2
  pinMode(5, INPUT_PULLUP); //button 3
  pinMode(4, INPUT_PULLUP); //button 4

  pinMode(3, OUTPUT); //buzzer
}

void loop() {
  if (level == 1) {
    generate_sequence();
    
    for (int i = 13; i >= 10; i--) { //flashing leds
      digitalWrite(i, HIGH);
      delay(100);
      digitalWrite(i, LOW);
    }
  }

  if (digitalRead(7) == LOW || level != 1) { //start button == button 1
    show_sequence();
    get_sequence();
  }
}

void generate_sequence() {
  randomSeed(millis()); //true random

  for (int i = 0; i < MAX_LEVEL; i++) {
    sequence[i] = random(10, 14);

    switch (sequence[i]) { //convert color to sound
      case 10:
        note = 349; //Fa
        break;
      case 11:
        note = 329; //Mi
        break;
      case 12:
        note = 293; //Re
        break;
      case 13:
        note = 261; //Do
        break;
    }
    sound[i] = note;
  }
}

void show_sequence() {
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);

  for (int i = 0; i < level; i++) {
    digitalWrite(sequence[i], HIGH);
    tone(3, sound[i]);
    delay(velocity);
    digitalWrite(sequence[i], LOW);
    noTone(3);
    delay(200);
  }
}

void get_sequence() {
  int flag = 0; //flag correct sequence

  for (int i = 0; i < level; i++) {
    flag = 0;

    while (flag == 0) {

      if (digitalRead(7) == LOW) {
        digitalWrite(13, HIGH);
        tone(3, 261); //Do
        delay(velocity);
        noTone(3);
        gamer_sequence[i] = 13;
        flag = 1;
        delay(200);

        if (gamer_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(13, LOW);
      }

      if (digitalRead(6) == LOW) {
        digitalWrite(12, HIGH);
        tone(3, 293); //Re
        delay(velocity);
        noTone(3);
        gamer_sequence[i] = 12;
        flag = 1;
        delay(200);

        if (gamer_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(12, LOW);
      }

      if (digitalRead(5) == LOW) {
        digitalWrite(11, HIGH);
        tone(3, 329); //Mi
        delay(velocity);
        noTone(3);
        gamer_sequence[i] = 11;
        flag = 1;
        delay(200);

        if (gamer_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(11, LOW);
      }

      if (digitalRead(4) == LOW) {
        digitalWrite(10, HIGH);
        tone(3, 349); //Fa
        delay(velocity);
        noTone(3);
        gamer_sequence[i] = 10;
        flag = 1;
        delay(200);

        if (gamer_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(10, LOW);
      }
    }
  }
  right_sequence();
}

void right_sequence() {
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(250);

  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  delay(500);

  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(500);

  if (level < MAX_LEVEL) {
    level++;
  }
  velocity -= 50; //increases difficulty
}

void wrong_sequence() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    tone(3, 233);
    delay(250);

    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    noTone(3);
    delay(250);
  }
  level = 1;
  velocity = 1000;
}
