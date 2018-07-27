#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

int maximo = 1;
//char uids[2][11];
String s[2];
int count = 0;
int j = 0;
 
void setup() 
{
  
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600); // Inicia a serial
  SPI.begin(); // Inicia  SPI bus
  mfrc522.PCD_Init(); // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();

}
 
void loop(){

  if ( ! mfrc522.PICC_IsNewCardPresent()){
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()){
    return;
  }
  
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  
  for (byte i = 0; i < mfrc522.uid.size; i++){
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  conteudo.toUpperCase();
  Serial.println(conteudo);

  if(count == 0){
    count++;
    s[0] = conteudo;
    Serial.println("Usuário Master Cadastrado");
  }

  for(int i = 0; i < count; i++){

    if(s[i].equals(conteudo)){
      Serial.println("Entrada permitida");
      j=1;
      break;
    }
    
    if(i == count-1 && count < maximo){
      s[i] = conteudo;
      Serial.println("Cadastrado");
      count++;
      break;
    }
    else if(i == count-1 && count == maximo){
      Serial.println("Entrada não permitida");
      break;
    }
  }

  if(j == 1){
    digitalWrite(4, HIGH);
    delay(2000);
    digitalWrite(4, LOW);
    
    for(int i = 0; i < 10; i++){
      digitalWrite(5, HIGH);
      delay(1);
      digitalWrite(5, LOW);
    }
  }
  else{
    digitalWrite(3, HIGH);
    delay(2000);
    digitalWrite(3, LOW);
  }

  j=0;
  delay(1000);
 
} 
