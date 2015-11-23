
#define trigPin 12
#define echoPin 13
#define pinBotao 7

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pinBotao, INPUT_PULLUP);
}
boolean botao;
int i=0;
float t1;
float t2;
float maiorDistancia = 0;
void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  //Serial.println(distance);
  
  botao = digitalRead(pinBotao);  
  if(!botao){
    Serial.println("Solte a bolinha junto com o botão"); 
    while(!botao){
      botao = digitalRead(pinBotao);
      delay(10);   
        digitalWrite(trigPin, LOW);  // Added this line
        delayMicroseconds(2); // Added this line
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10); // Added this line
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        distance = (duration/2) / 29.1;
    }
    i=0;
    t2 = millis();
    maiorDistancia = distance;    
    Serial.print("Distância máxima = ");
    Serial.println(maiorDistancia);
  } 

  if(distance < maiorDistancia){
    while(distance < maiorDistancia && botao){
      digitalWrite(trigPin, LOW);  // Added this line
      delayMicroseconds(2); // Added this line
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); // Added this line
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration/2) / 29.1;
      botao = digitalRead(pinBotao);
      delayMicroseconds(50);
    }
    
    t1 = t2;
    t2 = millis();
    if(t2-t1 > 100){
      i++;
      Serial.print("deltaT(");
      Serial.print(i);
      Serial.print(") = ");
      Serial.print((t2-t1));
      Serial.println(" ms");
    }
  }
  delay(10);
}
