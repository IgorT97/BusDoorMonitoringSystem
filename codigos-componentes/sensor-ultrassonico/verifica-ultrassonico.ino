#define trig 7  //Pino 9 do Arduino será a saída de trigger
#define echo 6   //Pino 8 do Arduino será a entrada de echo


void trigPuls();  //Função que gera o pulso de trigger

float pulse;     //Variável que armazena o tempo de duração do echo
float dist_cm;   //Variável que armazena o valor da distância em centímetros



void setup() 
{
  pinMode(trig, OUTPUT);   //Pino de trigger será saída digital
  pinMode(echo, INPUT);    //Pino de echo será entrada digital
  
  digitalWrite(trig, LOW); //Saída trigger inicia em nível baixo
  
  Serial.begin(9600);      //Inicia comunicação serial

}

void loop() 
{
Calcula1();

}

void trigPulse()
{
  digitalWrite(trig, HIGH);  //Pulso de trigger em nível alto
  delayMicroseconds(10);     //duração de 10 micro segundos
  digitalWrite(trig, LOW);   //Pulso de trigge em nível baixo
}

void Calcula1(){ 
   Serial.println("calculando distancia");
   trigPulse();                 //Aciona o trigger do módulo ultrassônico   
   pulse = pulseIn(echo, HIGH); //Mede o tempo em que o pino de echo fica em nível alto   
   dist_cm = pulse/58.82;       //Valor da distância em centímetros
   Serial.print("distancia: ");
   Serial.print(dist_cm);     //Imprime o valor na serial
   Serial.println(" cm");
   delay(500);  
}


