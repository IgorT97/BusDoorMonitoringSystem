/*
Obs: usamos o modulo I2C para display LCD, com intuito de reduzir a quantidade de jumpers, 
portanto é preciso baixar e realizar o uploud da biblioteca LiquidCrystal_I2C
 
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
int botao         = 8;
int led           = 5;
int estado_botao  = 0;
int flag_botao    = 0;
int estado_porta   = 1;
float altura_porta = 12;
int flag_obs = 0;
//servo

/*Variavel servo*/
Servo myservo; // direita
Servo myservo2; //esquerdaa
/*Posição servo*/
int pos = 0; //direita
int pos2=0; //esquerda

#define trig 7  //Pino 9 do Arduino será a saída de trigger
#define echo 6   //Pino 8 do Arduino será a entrada de echo


void trigPuls();  //Função que gera o pulso de trigger

float pulse;     //Variável que armazena o tempo de duração do echo
float dist_cm;   //Variável que armazena o valor da distância em centímetros



// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

void setup() { 
  

lcd.begin(16, 2);
pinMode(botao, INPUT);                                      // Informamos que botao(8) é entrada
pinMode(led  , OUTPUT);                                     // Informamos que led (5) é saida
  pinMode(trig, OUTPUT);   //Pino de trigger será saída digital
  pinMode(echo, INPUT);    //Pino de echo será entrada digital
  
  digitalWrite(trig, LOW); //Saída trigger inicia em nível baixo
 myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);
  myservo.write(100);
  myservo2.write(20);
          lcd.setCursor(1,1);
        lcd.print("PORTA ABERTA!");
Serial.begin(9600);                                         // Informa ao micro que vamos usar comunicação serial
  }// fim setup

void loop() {
  Calcula1();
  estado_botao = digitalRead(botao);                       // ATRIBUI O PINO DE ENTRADA BOTAO A VARIAVEL estado_botao


  if(( estado_botao == 1 )&&( flag_botao == 0 ) && ( dist_cm > altura_porta))                                  // TESTA A VARIALVEL SE É 1                    
    {
      flag_botao = 1;
      if( estado_porta == 1 )
        {
         estado_porta=0; 
         digitalWrite( led, HIGH );
         lcd.clear(); 
         Serial.println("PORTA FECHADA!");
         lcd.setCursor(1,1);
         lcd.print("PORTA FECHADA!");
                  for (pos2 = 20,pos = 100; pos2 <= 120, pos >= 0; pos2 += 1,pos -= 1) { // goes from 180 degrees to 0 degrees
                    Calcula1();
  verifica_obstaculo2();
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
      
     myservo2.write(pos2);   
     
    delay(15);                       // waits 15ms for the servo to reach the position
  }
         
        }
        
      else if( estado_porta == 0 )
        {
         estado_porta=1;
         digitalWrite( led, LOW );
         delay(15);
         verifica_obstaculo();
         lcd.clear(); 
         Serial.println("PORTA ABERTA!");   
         lcd.setCursor(1,1);
         lcd.print("PORTA ABERTA!");
           for (pos2 = 120,pos =0; pos2 >= 20, pos <= 100; pos2 -= 1,pos += 1) { // goes from 0 degrees to 180 degrees
              myservo.write(pos);              // tell servo to go to position in variable 'pos'
              myservo2.write(pos2);   
              delay(15);                       // waits 15ms for the servo to reach the position
  }     
        }
    delay(50);
    }// fim 

  if( estado_botao == 0 )
    {
       
     flag_botao=0;
     delay(50);  
    }

    verifica_obstaculo();

}// fim do loop



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
   delay(50);  
}

void verifica_obstaculo(){
 while (dist_cm < altura_porta)   {
    Calcula1();
    lcd.clear();
    lcd.setCursor(1,0);
    Serial.println("OBSTACULO NA PORTA");
    lcd.print("OBSTACULO");
    lcd.setCursor(1,1);
    lcd.print("NA PORTA!");
    delay(500);
    
      if (dist_cm > altura_porta)   {
          lcd.clear();
          lcd.setCursor(1,1);
          lcd.print("PORTA LIBERADA!");
   }
    
  }

}

void verifica_obstaculo2(){
 while (dist_cm < altura_porta)   {
    Calcula1();
    lcd.clear();
    lcd.setCursor(1,0);
    Serial.println("OBSTACULO NA PORTA");
    lcd.print("OBSTACULO");
    lcd.setCursor(1,1);
    lcd.print("NA PORTA!");
    delay(500);
    
      if (dist_cm > altura_porta)   {
          lcd.clear();
          lcd.setCursor(1,1);
          lcd.print("PORTA FECHADA!");
          delay(1000);
          loop();
   }
  myservo.write(100);
  myservo2.write(20);
  
  }

 
}

