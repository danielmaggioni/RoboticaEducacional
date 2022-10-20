//*********************************************************************************************** 
// Projeto Agrinho Robotica - Colegio Campina da Lagoa                                          *
// Prgrama sketch desenvolvido para analisar a umidade do solo e coletar os dados               *
// Desenvolvido pelo Prof. Daniel Maggioni de Souza em coloboração com os alunos do Esino Médio *
//***********************************************************************************************

//*************************
#include <DHT.h>
#include <LiquidCrystal.h>
//*************************

//***********************************************************
// Definicao dos pinos do Display                           *
//***********************************************************
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                
int thisChar = 0 ;


//********************
#define sensor A0
#define Solenoide 7
#define DHTTYPE DHT11
#define DHTPIN A1
//********************

//************************
//Definindo as Variaveis *
//************************
int ValorSensor;  
float h,t;
 

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  dht.begin();
  lcd.begin(16, 2);
  Serial.begin(9600);

  
  pinMode(sensor,INPUT);
  pinMode(Solenoide,OUTPUT);
 
}

void imprime()  {                    // imprimindo mensagem no display de lcd
  lcd.clear();                      // limpa a tela
  lcd.setCursor(0, 0);             // selecionando coluna 0 e linha 0
  lcd.print("HUMIDADE:");         // print da mensagem
  lcd.print(h);                  // Print da mensagem
  lcd.setCursor(0,1);           // seleciona a coluna 0 e a linha 1
  lcd.print("TEMP.:");         // imprime mensagem
  lcd.print(t);               // imprime a temperatura lida pelo sensor 
  delay(1000);               // atraso de 1 segundo
}

void loop() {
//**********************************************
// Leitura do sensor de Humidade e temperatura *
//**********************************************
  h = dht.readHumidity();
  t = dht.readTemperature();
//**************************************
//  Chama a função imprime para o LCD  *
//***************************************
  imprime();

  if (isnan(t) || isnan(h))
  {
    Serial.println("Sensor de falhou");
    
  }
  else
  {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
  }

  
//***************************************
// Leitura do sensor de umidade do solo *
//***************************************
  ValorSensor = map(analogRead(sensor), ValorSensor,0,1023,2000);
  Serial.println(ValorSensor);
  
  if (ValorSensor >=1750) 
  {
    digitalWrite(Solenoide,HIGH);
    Serial.println(ValorSensor);
    Serial.println("Solenoide ligado");
    
  }

  if (ValorSensor <=1300)
  {
    digitalWrite(Solenoide,LOW);
    Serial.println("Solenoide Desligado");
  }
  

}
