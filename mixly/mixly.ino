void _E5_89_8D_E8_BF_9B() {
  pinMode(A0, OUTPUT);
  digitalWrite(A0,HIGH);
  pinMode(A2, OUTPUT);
  digitalWrite(A2,HIGH);
  pinMode(A0, OUTPUT);
  digitalWrite(A0,LOW);
  pinMode(A3, OUTPUT);
  digitalWrite(A3,LOW);
  analogWrite(3,150);
  analogWrite(5,150);
}

void _E5_90_91_E5_B7_A6_E8_BD_AC() {
  pinMode(A0, OUTPUT);
  digitalWrite(A0,HIGH);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,LOW);
  pinMode(A3, OUTPUT);
  digitalWrite(A3,LOW);
  pinMode(A2, OUTPUT);
  digitalWrite(A2,LOW);
  analogWrite(3,140);
}

void _E5_BF_AB_E9_80_9F_E5_90_91_E5_B7_A6() {
  pinMode(A2, OUTPUT);
  digitalWrite(A2,LOW);
  pinMode(A0, OUTPUT);
  digitalWrite(A0,HIGH);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,LOW);
  pinMode(A3, OUTPUT);
  digitalWrite(A3,LOW);
  analogWrite(3,180);
}

void _E5_81_9C_E6_AD_A2() {
  pinMode(A0, OUTPUT);
  digitalWrite(A0,LOW);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,LOW);
  pinMode(A2, OUTPUT);
  digitalWrite(A2,LOW);
  pinMode(A3, OUTPUT);
  digitalWrite(A3,LOW);
}

void _E5_90_91_E5_8F_B3_E8_BD_AC() {
  pinMode(A0, OUTPUT);
  digitalWrite(A0,LOW);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,LOW);
  pinMode(A3, OUTPUT);
  digitalWrite(A3,LOW);
  pinMode(A2, OUTPUT);
  digitalWrite(A2,HIGH);
  analogWrite(5,140);
}

void _E5_BF_AB_E9_80_9F_E5_90_91_E5_8F_B3() {
  pinMode(A2, OUTPUT);
  digitalWrite(A2,HIGH);
  pinMode(A0, OUTPUT);
  digitalWrite(A0,LOW);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,LOW);
  pinMode(A3, OUTPUT);
  digitalWrite(A3,LOW);
  analogWrite(5,180);
}

void setup(){
  pinMode(12, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
}

void loop(){
  if (digitalRead(12) == LOW) {
    if ((digitalRead(6) == LOW && digitalRead(7) == HIGH) && (digitalRead(8) == LOW && digitalRead(9) == LOW)) {
      _E5_90_91_E5_B7_A6_E8_BD_AC();

    } else if ((digitalRead(6) == LOW && digitalRead(7) == LOW) && (digitalRead(8) == HIGH && digitalRead(9) == LOW)) {
      _E5_90_91_E5_8F_B3_E8_BD_AC();
    } else if ((digitalRead(6) == HIGH && digitalRead(7) == LOW) && (digitalRead(8) == LOW && digitalRead(9) == LOW)) {
      _E5_BF_AB_E9_80_9F_E5_90_91_E5_B7_A6();
    } else if ((digitalRead(6) == LOW && digitalRead(7) == LOW) && (digitalRead(8) == LOW && digitalRead(9) == HIGH)) {
      _E5_BF_AB_E9_80_9F_E5_90_91_E5_8F_B3();
    }

  } else {
    _E5_89_8D_E8_BF_9B();

  }

}