float sensorR = A0;
float sensorC = A1;
float sensorL = A2;
float sensorP = A3;

float valR = 0;
float valC = 0;
float valL = 0;
float sensingPerson = 0;

float voltR = 0;
float voltC = 0;
float voltL = 0;

float CmR = 0;
float CmC = 0;
float CmL = 0;

float sum = 0;

int person = 0;

float startVal1 = 0;
float startVal2 = 0;
float startVal3 = 0;

void setup() {
  Serial.begin(9600);
  delay(200);
  startVal1 = analogRead(sensorR); // 적외선 센서로부터 처음 측정한 값을 넣어줌
  startVal2 = analogRead(sensorC);
  startVal3 = analogRead(sensorL);

  startVal1 = map(startVal1, 0, 1023, 0, 5000);
  startVal1 = (21.61/(startVal1 - 0.1696)) * 1000;

  startVal2 = map(startVal2, 0, 1023, 0, 5000);
  startVal2 = (21.61/(startVal2 - 0.1696)) * 1000;

  startVal3 = map(startVal3, 0, 1023, 0, 5000);
  startVal3 = (21.61/(startVal3 - 0.1696)) * 1000;
  
  delay(200);
//  Serial.print(startVal1);
//  Serial.print(" ");
//  Serial.print(startVal2);
//  Serial.print(" ");
//  Serial.println(startVal3);
}

void loop() {
  sensingPerson = analogRead(sensorP);
  
  sensingPerson = map(sensingPerson, 0, 1023, 0, 5000);
  sensingPerson = ((21.61/(sensingPerson - 0.1696)) * 1000);
//  Serial.println(sensingPerson);

  if(sensingPerson < 10 || sensingPerson > 75) {
    valR = analogRead(sensorR);
    valC = analogRead(sensorC);
    valL = analogRead(sensorL);
  
    voltR = map(valR, 0, 1023, 0, 5000);
    CmR = ((21.61/(voltR - 0.1696)) * 1000) - startVal1;
  
    voltC = map(valC, 0, 1023, 0, 5000);
    CmC = ((21.61/(voltC - 0.1696)) * 1000) - startVal2;
  
    voltL = map(valL, 0, 1023, 0, 5000);
    CmL = ((21.61/(voltL - 0.1696)) * 1000) - startVal3;
    
//    Serial.print("R = ");
//    Serial.print(CmR);
//    Serial.print("  C = ");
//    Serial.print(CmC);
//    Serial.print("  L = ");
//    Serial.print(CmL);
//    Serial.print("  sum = ");
//      
    sum = CmR + CmC + CmL;
//    Serial.print(sum);
//    Serial.print("  person = ");
//  
    person = int(sum / 0.3);
    Serial.println(person);
    delay(1000); 
  } else { 

  }
}
