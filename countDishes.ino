// 적외선 센서 3개로 식판의 높이를 재고, 3개의 적외선 센서로 측정된 식판 높이의 합이 낮아지는지를 측정하여 낮아진수치 만큼의 식사통과인원을 파악함  
// 식판 높이의 측정은 식판 거치대에 설치된 적외선 센서 앞에 사람이 없을 때 실시함  
// 센서 오차로 인한 결과치의 변화를 보정하기 위해 평균필터법을 사용  


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

float sumPerson = 0; // 사람수 측정값 5회치가 누적되는 변수  
float avrPerson = 0; // 사람수 측정값 누적치를 누적횟수로 나눠서 나온 평균값  
int divideVal = 5; //평균값을 뽑기 위해 누적시켜 나누고자 하는 횟수를 입력, 오차를 줄이려면 이 수치를 올려주세요.  
int count = 0; // 누적되는 횟수를 카운트  

float startVal1 = 0;
float startVal2 = 0;
float startVal3 = 0;

void setup() {
  Serial.begin(9600);
  delay(200);
  startVal1 = analogRead(sensorR); // 적외선 센서로부터 리셋 후 처음 측정한 값을 넣어줌  
  startVal2 = analogRead(sensorC);
  startVal3 = analogRead(sensorL);

  startVal1 = map(startVal1, 0, 1023, 0, 5000); // 측정한값을 Cm단위로 변환함  
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
    sensingPerson = analogRead(sensorP); // 식판거치대 앞에 사람이 있는지 확인하기 위해 값을 추출함  
    
    sensingPerson = map(sensingPerson, 0, 1023, 0, 5000); //Cm 단위로 환산  
    sensingPerson = ((21.61/(sensingPerson - 0.1696)) * 1000);
  //  Serial.println(sensingPerson);
  
    if(sensingPerson < 10 || sensingPerson > 75) { // 10~75Cm   없으면
      valR = analogRead(sensorR); //센서 R, C, L을 측정해 변수에 넣음  
      valC = analogRead(sensorC);
      valL = analogRead(sensorL);
    
      voltR = map(valR, 0, 1023, 0, 5000); //측정값을 Cm단위로 환산  
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
      sum = CmR + CmC + CmL; // 세 적외선 센서의 측적값을 더함  
  //    Serial.print(sum);
  //    Serial.print("  person = ");
  //  
      person = int(sum / 0.3); // 측정값을 식판 두께로 나눠 사람 수를 구함  

      sumPerson += person; //평균필터를 적용하기 위해 사람 수를 누적시킴  
//      Serial.print(person);
//      Serial.print("  ");
//      Serial.println(sumPerson);
      delay(100); 

      count += 1; // 평균치를 구할 인원 수가 되었는지 확인하기 위해 카운트 함  
    } else { 
      
    }
    if (count == divideVal) { // 카운트가 평균치를 구할 인원 수가 되면  
      avrPerson = sumPerson / divideVal;  // 누적된 인원 수를 평균치를 구할 인원 수로 나눠줌  
//      Serial.print(" avrPerson : ");
      Serial.println(int(avrPerson)); // 실수자료를 정수형으로 바꿔서 블루투스로 송신함  
      sumPerson = 0; // 누적 인원수를 초기화 함  
      count = 0; // 카운트를 초기화 함  
    }
}
