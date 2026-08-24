# Magnetrührer

## ✨ Features
* **Präzise Steuerung**: Jitterfreie Schrittmotor-Ansteuerung über Hardware-Timer 1.
* **Materialschonend**: Sanfter Anlauf und Abbremsen durch integrierte Beschleunigungsrampe.
* **Flackerfreies Display**: Ressourcenschonende, blockierungsfreie LCD-Aktualisierung im Hintergrund.

## 🚀 Bedienung
1. Gewünschte Drehzahl über das **Potentiometer** vorwählen.
2. Den **Taster** einmal kurz drücken, um den Rührvorgang zu starten. Die Drehzahl läuft automatisch rampenförmig an.
3. Erneutes Drücken des Tasters stoppt den Motor sofort.

## 🖼 Bild
<img width="591" height="509" alt="Magnetrührer komplett" src="https://github.com/user-attachments/assets/70977960-3b56-4dfb-a4fd-13aa9e19de33" />


## 📂 Repository-Struktur

* `/firmware` - Enthält den Arduino-Quellcode (`.ino`).
* `/hardware` - Schaltpläne, Platinenlayouts (KiCad-Projektdateien) und Gerber-Dateien.
* `/3d-prints` - STL- oder STEP-Dateien für das Gehäuse.
* `/assets` - Bilder und Grafiken für die Dokumentation.



## 🔌 Pin-Belegung (Arduino Uno)

| Peripherie | Arduino Pin | Funktion |
| :--- | :---: | :--- |
| **Schrittmotor (STEP)** | D2 | Impulsausgabe für Drehzahl |
| **Schrittmotor (DIR)** | D3 | Richtungssteuerung |
| **Taster (Button)** | D4 | Start / Stopp (interner Pull-up) |
| **Treiber (ENABLE)** | D5 | Aktivierung der Motortreiber |
| **Potentiometer** | A0 | Analoge Drehzahleinstellung |



# Material
## 📦 Stückliste (Bill of Materials)

Hier findest du alle elektronischen Komponenten, die für den Aufbau der Platine benötigt werden.

| Status | Bauteil (Designator) | Beschreibung | Menge | Gehäuse / Footprint |
| :---: | :--- | :--- | :---: | :--- |
| 🧠 | **Arduino UNO (A1)** | Steuerzentrale (Mikrocontroller-Board) | 1 | `Arduino_UNO_R2` |
| 🔌 | **DRV8825 (A2, A3)** | Schrittmotortreiber (Pololu-Breakout) | 2 | `Breakout-16_15.2x20.3mm` |
| 🔋 | **L7805 (U1)** | 5V Linear-Spannungsregler | 1 | `TO-220-3_Vertical` |
| ⚡ | **C_Polarized (C1, C2)**| Elektrolytkondensator (Stützkondensator) | 2 | `Radial_D8.0mm_P5.00mm` |
| 📟 | **LCD-Connector (J10)**| Buchsenleiste für das I2C-Display | 1 | `PinSocket_1x04_P2.54mm_V` |
| 🌀 | **Lüfter (J11)** | Stiftleiste für den Gehäuselüfter | 1 | `PinHeader_1x02_P2.54mm_V` |
| ⚙️ | **Microstepping (J2,J3,J6,J7)**| Jumper-Stiftleisten für Schrittauflösung | 4 | `PinHeader_1x03_P2.54mm_V` |
| 🏎️ | **Motor (J1, J5)** | Stiftleiste für Schrittmotor-Anschluss | 2 | `PinHeader_1x04_P2.54mm_V` |
| 🔌 | **Power In (J4)** | Stiftleiste für die Stromversorgung | 1 | `PinHeader_1x02_P2.54mm_V` |
| 🎛️ | **Poti (J8)** | Stiftleiste für Drehzahl-Potentiometer | 1 | `PinHeader_1x03_P2.54mm_V` |
| 🔘 | **Taster (J9)** | Stiftleiste für Start/Stopp-Taster | 1 | `PinHeader_1x02_P2.54mm_V` |

> 💡 **Tipp:** Wenn du die Platine professionell fertigen lassen möchtest (z. B. bei JLCPCB), kannst du die Spalte `LCSC Part #` in deiner EDA-Software (z. B. KiCad) pflegen, um die Bauteile beim Bestellen direkt automatisch bestücken zu lassen (PCBA).


### ⚙️ Microstepping-Konfiguration (Jumper J2, J3, J6, J7)

Der Schrittmotortreiber DRV8825 unterstützt verschiedene Schrittauflösungen. Für eine flüssige Rotation des Magneten wird standardmäßig das **1/32-Stepping** empfohlen.

| Auflösung | Jumper M0 (1) | Jumper M1 (2) | Jumper M2 (3) |
| :--- | :---: | :---: | :---: |
| Vollschritt (Full step) | LOW (off) | LOW (off) | LOW (off) |
| Halbschritt (Half step) | HIGH (on) | LOW (off) | LOW (off) |
| 1/4 Schritt | LOW (off) | HIGH (on) | LOW (off) |
| 1/8 Schritt | HIGH (on) | HIGH (on) | LOW (off) |
| 1/16 Schritt | LOW (off) | LOW (off) | HIGH (on) |
| **1/32 Schritt (Empfohlen)** | **HIGH (on)** | **HIGH (on)** | **HIGH (on)** |


## 🔩 Mechanische Komponenten & Zubehör

| Komponente | Beschreibung | Menge | Detail / Abmessung |
| :--- | :--- | :---: | :--- |
| **Schrittmotor** | NEMA 17 Schrittmotor | 1 | 1.8° Schrittwinkel |
| **Dauermagnete** | Neodym-Magnete (für den Rotor) | 2 | Block- oder Scheibenmagnete (z. B. N52) |
| **3D-Druckteile** | Gehäusebasis, Deckel und Magnet-Halterung | 1 | Eigene STL-Dateien (siehe `/3d-prints`) |
| **Rührfisch** | PTFE-beschichteter Magnet-Rührstab | 1 | Standardlänge (z. B. 25-30 mm) |
| **Schrauben** | Befestigung für Motor und Gehäuse | 1 Satz| M3 / M4 Innensechskant |


## 💻 Software-Installation

1. Installiere die [Arduino IDE](https://arduino.cc).
2. Installiere die benötigte Bibliothek über den Bibliotheksverwalter:
   * `LiquidCrystal_I2C` (von Frank de Brabander).
3. Öffne die Code-Datei im Ordner `/firmware`.
4. Verbinde den Arduino UNO per USB-Kabel mit dem PC.
5. Wähle das richtige Board (**Arduino Uno**) und den **COM-Port** aus.
6. Klicke auf **Hochladen** (Upload).



# Platine
<img width="938" height="877" alt="Magnetrührer oben pcb" src="https://github.com/user-attachments/assets/2b822f4f-a9fa-4fd2-adc6-19ac2734e8f7" />
<img width="942" height="884" alt="Magnetrührer unten pcb" src="https://github.com/user-attachments/assets/9451aca8-5a20-42de-ba81-dc7ef3c4a5d4" />

# Schaltplan
<img width="1327" height="827" alt="Schaltplan groß" src="https://github.com/user-attachments/assets/351a961d-b002-4349-afd0-a5947cd453b0" />

# Code

```
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
```
