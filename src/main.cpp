#include <Arduino.h>

// Morseova abeceda pro znaky A-Z 
const char* morseCode[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", // A-J
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",   // K-T
  "..-", "...-", ".--", "-..-", "-.--", "--..",                           // U-Z
};

const int ledPin = 12; // Pin pro LED 

// Časy pro Morseovku
const int dotDuration = 150;    
const int dashDuration = 300;   
const int morseSpace = 200;    
const int letterSpace = 400;    
const int wordSpace = 800;     

// Funkce pro blikání LED dle morseovky
void Morse(const char* morse) {
  for (int i = 0; morse[i] != '\0'; i++) {
    if (morse[i] == '.') {
      digitalWrite(ledPin, HIGH);
      delay(dotDuration);   // Tečka
    } else if (morse[i] == '-') {
      digitalWrite(ledPin, HIGH);
      delay(dashDuration);  // Čárka
    }
    digitalWrite(ledPin, LOW);
    delay(morseSpace);     // Mezera mezi tečkami a čárkami
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Zadej text pro převod na morseovku:");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.toUpperCase();  // Převod textu na velká písmena

    // Výpis původního vstupu
    Serial.print("Vstupní text: ");
    Serial.println(input);

    // Výpis převodu na Morseovu abecedu
    Serial.print("Morseovka: ");
    
    for (int i = 0; i < input.length(); i++) {
      char c = input.charAt(i);
      
      if (c >= 'A' && c <= 'Z') {
        // Morseovka pro písmena A-Z
        Serial.print(morseCode[c - 'A']);
        Serial.print(" ");  // Oddělíme jednotlivé znaky mezerou
        Morse(morseCode[c - 'A']);
      } else if (c == ' ') {
        delay(wordSpace); // Mezera mezi slovy
        Serial.print(" / ");  // Zobrazíme mezery mezi slovy jako lomítko
      }
      
  
    }

    Serial.println();  // Nový řádek po skončení Morseovy abecedy
  }
}
