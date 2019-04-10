#include <LiquidCrystal.h> // inclui a biblioteca para uso do Display LCD
#include "DHT.h"
// inicializa um objeto nos pinos para acesso as funções do LCD
const int RS = 12, EN = 11, D4 = 10, D5 = 9, D6 = 8, D7 = 7;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
const int pino_dht = 3; // pino onde o sensor DHT está conectado
float temperatura; // variável para armazenar o valor de temperatura
float umidade; // variável para armazenar o valor de umidade
DHT dht(pino_dht, DHT11); // define o pino e o tipo de DHT

// Caractere personalizado
byte customChar[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup(){
  // Cria um novo caractere personalizado
  lcd.createChar(0, customChar);
  
  // Configura o LCD com os número de colunas e linhas
  lcd.begin(16, 2); // 16 colunas e 2 linhas

  // Inicia e configura a Serial
  Serial.begin(9600); // 9600bps

  dht.begin(); // inicializa o sensor DHT

  // Limpa o LCD
  lcd.clear();
  
}

void loop(){
  while(1) {
  temperatura = dht.readTemperature(); // lê a temperatura em Celsius
  umidade = dht.readHumidity(); // lê a umidade

  // Se ocorreu alguma falha durante a leitura
  if (isnan(umidade) || isnan(temperatura)) {
    lcd.setCursor(0, 1);
    lcd.print("Carregando...");
  } else { // Se não
    // Imprime o valor de temperatura no LCD
    // posiciona o cursor do LCD
    lcd.clear();
    lcd.setCursor(0, 0); // (coluna 0, linha 0)
    lcd.print("Temperatura:"); // Imprime mensagem  
    lcd.setCursor(0, 1);
    lcd.print(temperatura);
    lcd.write((uint8_t)0);
    lcd.print("C");
    
    // Imprime o valor de temperatura no monitor serial  
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" *C ");    
    Serial.print("\t"); // tabulação    
    Serial.println(); // nova linha
    delay(10000);

    // Imprime o valor de umidade no LCD
    // posiciona o cursor do LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Umidade:");
    lcd.setCursor(0, 1);
    lcd.print(umidade);
    lcd.print("%");

    // Imprime o valor de umidade
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.print(" %\t"); 
    Serial.print("\t"); // tabulação    
    Serial.println(); // nova linha
    delay(5000);   
    
  }
}
}
