#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- PIN DEFINITIONEN ---
const int PIN_STEP   = 2; 
const int PIN_DIR    = 3; 
const int PIN_BUTTON = 4; 
const int PIN_ENABLE = 5; 
const int PIN_POTI   = A0; 

// --- DISPLAY KONFIGURATION ---
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// --- MOTOR CONFIGURATON ---
const int SCHRITTE_PRO_UMDREHUNG = 200; 

// --- VARIABLEN ---
volatile bool motorAktiv = false; 
bool letzterTasterStatus = HIGH;
unsigned long letzterDebounceZeitpunkt = 0;
const unsigned long debounceVerzoegerung = 50; 

int letzterPotiWert = -99;
const int POTI_SCHWELLENWERT = 3; 
long zielRpm = 0;
long aktuelleRpm = 0; 

// Variablen für die Beschleunigungsrampe
unsigned long letzteRampeZeit = 0;
const unsigned long rampeIntervall = 4; 

// Variablen für das Display-Update
unsigned long letzteDisplayAktion = 0;
const unsigned long displayIntervall = 30; 
int displaySchritt = 0;
long rpmFuerDisplay = 0;

// Variablen für den Hardware-Timer
volatile unsigned int timerZaehler = 60000;

void setup() {
  pinMode(PIN_STEP, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
  pinMode(PIN_ENABLE, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  
  digitalWrite(PIN_ENABLE, HIGH); 
  digitalWrite(PIN_DIR, HIGH);
  
  // --- HARDWARE-TIMER1 INITIALISIEREN ---
  cli(); 
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 2000;            
  TCCR1B |= (1 << WGM12);  
  TCCR1B |= (1 << CS11);   
  TIMSK1 |= (1 << OCIE1A); 
  sei(); 

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Magnetruehrer");
  lcd.setCursor(0, 1);
  lcd.print("Bereit...");
  delay(1500);
  lcd.clear();
  
  // Neues Layout mit mehr Platz für die Einheit
  lcd.setCursor(0, 0);
  lcd.print("Status: AUS");
  lcd.setCursor(0, 1);
  lcd.print("Rpm:       0 U/min"); // Start-Layout vordefiniert
}

// --- INTERRUPT SERVICE ROUTINE ---
ISR(TIMER1_COMPA_vect) {
  if (motorAktiv && aktuelleRpm > 0) {
    PORTD |= (1 << PD2);  
    delayMicroseconds(2);
    PORTD &= ~(1 << PD2); 
    
    OCR1A = timerZaehler; 
  }
}

void loop() {
  // 1. TASTER AUSLESEN & ENTPRELLEN
  int tasterLesen = digitalRead(PIN_BUTTON);
  if (tasterLesen != letzterTasterStatus) {
    letzterDebounceZeitpunkt = millis();
  }

  if ((millis() - letzterDebounceZeitpunkt) > debounceVerzoegerung) {
    if (tasterLesen == LOW && !motorAktiv) {
      motorAktiv = true;
      digitalWrite(PIN_ENABLE, LOW); 
      letzterPotiWert = -99; 
      aktuelleRpm = 10; 
    } else if (tasterLesen == LOW && motorAktiv) {
      motorAktiv = false;
      digitalWrite(PIN_ENABLE, HIGH); 
      aktuelleRpm = 0;
    }
  }
  letzterTasterStatus = tasterLesen;

  // 2. POTI AUSLESEN
  int potiWert = analogRead(PIN_POTI);
  
  if (abs(potiWert - letzterPotiWert) > POTI_SCHWELLENWERT) {
    letzterPotiWert = potiWert;
    zielRpm = map(potiWert, 0, 1023, 10, 850);
  }

  // 3. BESCHLEUNIGUNGSRAMPE
  if (motorAktiv && (millis() - letzteRampeZeit > rampeIntervall)) {
    letzteRampeZeit = millis();
    
    if (aktuelleRpm < zielRpm) {
      aktuelleRpm++; 
    } else if (aktuelleRpm > zielRpm) {
      aktuelleRpm--; 
    }
    
    if (aktuelleRpm > 0) {
      timerZaehler = 600000 / aktuelleRpm;
      if (timerZaehler < 550) timerZaehler = 550; 
    }
  }

  // 4. DISPLAY HÄPPCHENWEISE AKTUALISIEREN
  if (millis() - letzteDisplayAktion > displayIntervall) {
    letzteDisplayAktion = millis();
    rpmFuerDisplay = motorAktiv ? zielRpm : 0; 

    switch (displaySchritt) {
      case 0:
        lcd.setCursor(8, 0);
        if (motorAktiv) lcd.print("AN ");
        else            lcd.print("AUS");
        displaySchritt++;
        break;
      case 1:
        // Die Zahl startet jetzt zwei Stellen weiter links (Stelle 6 statt 8)
        lcd.setCursor(6, 1);
        displaySchritt++;
        break;
      case 2:
        if (rpmFuerDisplay < 1000) lcd.print(" ");
        else lcd.print(rpmFuerDisplay / 1000);
        displaySchritt++;
        break;
      case 3:
        if (rpmFuerDisplay < 100) lcd.print(" ");
        else lcd.print((rpmFuerDisplay % 1000) / 100);
        displaySchritt++;
        break;
      case 4:
        if (rpmFuerDisplay < 10) lcd.print("0");
        else lcd.print((rpmFuerDisplay % 100) / 10);
        displaySchritt++;
        break;
      case 5:
        lcd.print(rpmFuerDisplay % 10);
        displaySchritt++;
        break;
      case 6:
        // Schreibt die Einheit mit ausreichend Platz dahinter
        lcd.print(" U/min  "); 
        displaySchritt = 0; 
        break;
    }
  }
}
