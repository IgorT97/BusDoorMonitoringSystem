int botao         = 8;
int led           = 5;
int estado_botao  = 0;
int flag_botao    = 0;
int estado_sinal    = 1;

void setup() { 
  
Serial.begin(9600);                                         // Informa ao micro que vamos usar comunicação serial

pinMode(botao, INPUT);                                      // Informamos que botao(8) é entrada
pinMode(led  , OUTPUT);                                     // Informamos que led (5) é saida


  }// fim setup

void loop() {

  estado_botao = digitalRead(botao);                       // ATRIBUI O PINO DE ENTRADA BOTAO A VARIAVEL estado_botao

  if(( estado_botao == 1 )&&( flag_botao == 0 ))                                  // TESTA A VARIALVEL SE É 1                    
    {
      flag_botao = 1;
      if( estado_sinal== 1)
        {
         estado_sinal=0; 
         
        }
        
      else if( estado_sinal == 0)
        {
         estado_sinal=1;
       
        }
    delay(50);
    }// fim 

  if( estado_botao == 0 )
    {
     flag_botao=0;
     delay(50);  
    }


}// fim do loop



