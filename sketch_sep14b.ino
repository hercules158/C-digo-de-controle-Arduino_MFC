#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // definicao dos pinos do Display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                // configurando os pinos

float pot = 0; //Variável que recebe o valor lido do potenciômetro
float sp = 0;  //Variável que recebe o cálculo do fluxo no Set Point
float flow = 0; //Variável que recebe o valor de fluxo lido do MFC
float GCF = 0;  //Gas Correction Factor  *OBS: Gases com GCF > 1 terão fluxo maior que o fluxo máximo em Nitrogênio
int pushbotton = 0; 

#define potenciometro A0  //Define potenciometro como A0
#define MFC A1            //Define MFC como A1

//float potenciometro = A0;
//float MFC = A1;

void setup()
     {
       Serial.begin(9600);
  
       pinMode(potenciometro, INPUT); //Declaração da variável que recebe a leitura do potenciômetro como variável de entrada
       pinMode(MFC, INPUT);           //Declaração da variável que recebe a leitura de fluxo do MFC como variável de entrada
       pinMode(2, INPUT);             //Define o pino 2 do arduino como um pino de entrada
       pinMode(11, OUTPUT);           //Define o pino 11 do arduino como um pino de saída
  
       lcd.begin(16,2);      //Inicializa o display LCD 16x2
       lcd.setCursor(0,0);  //Coloca o cursor para escrita na posição coluna 0 linha 0
       lcd.print("SP:");    //Imprime na tela do display LCD o setpoint como SP:
  
       lcd.setCursor(0,1); 
       lcd.print("FL:"); //Imprime na tela do display LCD o fluxo como FL:

       analogWrite(11,0); //Define o pino do Setpoint no inicio do programa para uma saída de 0V
       
       GCF = 1.39;  //Fator de correção do gás

    }

void loop() 
     {
           pot = map(analogRead(potenciometro),0,1023,0,255);  //Lê o valor do potenciômetro e comprime o valor lido num intervalo entre 0 e 255 min = 0 max = 255
           sp = pot*GCF*200/255;  //Calcula o valor do SP para ser mostrado no display Ex: GCF Arg. = 1.39 quer dizer que 5V da um fluxo de (200 sccm de Nitrogenio)*1.39 = 278 sccm no Arg.
  
           lcd.setCursor(3,0); //Posiciona o cursor do display LCD
           lcd.print(sp);      //Imprime no display o valor de Fluxo desejado
  
           lcd.setCursor(8,0); 
           lcd.print(" sccm");  //Posiciona o cursor na posição 8x0 e escreve sccm
  
           pushbotton = digitalRead(2); //Lê o pino 2 do Push Button para saber se o usuário pressionou o botão
  
           if(pushbotton == HIGH) //Verifica se a variável contém o valor verdadeiro e se contiver executa o codido entre chaves
              {
                 analogWrite(11,pot); // Envia o valor de PWM calculado para o pino digital 11
              }

           flow = analogRead(MFC)*GCF*200/1023; //Faz a leitura analógica do pino de entrada A1 do arduino, o sinal vem do MFC
           
           lcd.setCursor(0,1);
           lcd.print("FL");
           
           lcd.setCursor(3,1);
           lcd.print(flow);
           
           lcd.setCursor(8,1); 
           lcd.print(" sccm");
          
           delay(30); //Aguarda 30ms
  
   
    }
