#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

bool isConnectedDisplayed = false;
bool isTotalDisplayed = false;
bool isPersonnesDisplayed = false;
bool isDecompteDisplayed = false;
bool isAttenteDisplayed = true; // Nouvelle variable pour afficher le message "En attente..." au début
bool isStartupAnimationDisplayed = false;

const int buttonPinMenuTotal = 2;
const int buttonPinMenuPersonnes = 3;
const int buttonPinMenuDecompte = 4;
const int numButtons = 20;
const int buttonPins[numButtons] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41};
int buttonStates[numButtons] = {0};
int lastButtonStates[numButtons] = {0};
int personnesPassant[numButtons] = {0};
int dernierePersonne = 0;
int dernieresPersonnes[10] = {0};

enum MenuState {
  MENU_ATTENTE,
  MENU_TOTAL,
  MENU_PERSONNES,
  MENU_DECOMPTE
};

MenuState menuState = MENU_ATTENTE;

unsigned long decompteDebut = 0;
const unsigned long MILLIS_PER_SECOND = 1000UL;
const unsigned long MILLIS_PER_MINUTE = 60 * MILLIS_PER_SECOND;
const unsigned long MILLIS_PER_HOUR = 60 * MILLIS_PER_MINUTE;
unsigned long decompteDuree = 3 * MILLIS_PER_HOUR;
unsigned long lastDecompteUpdate = 0;
unsigned long lastPassageTime[numButtons] = {0};

int totalTours = 0;

// Déclaration de la broche du buzzer
const int buzzerPin = 9;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Initialise le bus I2C

  // Initialise l'écran LCD
  lcd.init();
  // Active le rétroéclairage
  lcd.backlight();

  pinMode(buttonPinMenuTotal, INPUT_PULLUP);
  pinMode(buttonPinMenuPersonnes, INPUT_PULLUP);
  pinMode(buttonPinMenuDecompte, INPUT_PULLUP);

  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Initialise la broche du buzzer
  pinMode(buzzerPin, OUTPUT);

  decompteDebut = millis();

  displayWaitingForConnection(); // Afficher le message "En attente..." au début
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'c') {
      Serial.println('o');
      isConnectedDisplayed = true;
      menuState = MENU_TOTAL;
      displayConnectedMessage();
    } else if (command == 'd') { // Déconnexion
      isConnectedDisplayed = false;
      isTotalDisplayed = false;
      isPersonnesDisplayed = false;
      isDecompteDisplayed = false;
      menuState = MENU_ATTENTE;
      displayWaitingForConnection();
    } else if (command == 't') { // Lancer le décompte
      isAttenteDisplayed = false;
      isTotalDisplayed = false;
      isPersonnesDisplayed = false;
      isDecompteDisplayed = false;
      menuState = MENU_DECOMPTE;
      decompteDebut = millis();
      displayDecompte();
    }
  }

  updateMenuButtons();
  updatePersonButtons();

  switch (menuState) {
    case MENU_ATTENTE:
      if (!isAttenteDisplayed) {
        isAttenteDisplayed = true;
        displayWaitingForConnection();
      }
      break;
    case MENU_TOTAL:
      if (!isTotalDisplayed) {
        isTotalDisplayed = true;
        displayTotal();
      }
      break;
    case MENU_PERSONNES:
      if (!isPersonnesDisplayed) {
        isPersonnesDisplayed = true;
        displayDernieresPersonnes();
      }
      break;
    case MENU_DECOMPTE:
      unsigned long currentTime = millis();
      if (!isDecompteDisplayed || currentTime - lastDecompteUpdate >= 1000) {
        isDecompteDisplayed = true;
        lastDecompteUpdate = currentTime;
        displayDecompte();
      }
      break;
  }

  // Contrôle du buzzer
  for (int i = 0; i < numButtons; i++) {
    if (buttonStates[i] != lastButtonStates[i]) {
      if (buttonStates[i] == LOW) {
        // Allume le buzzer pendant 100 ms
        digitalWrite(buzzerPin, HIGH);
        delay(100);
        digitalWrite(buzzerPin, LOW);
      }
      lastButtonStates[i] = buttonStates[i];
    }
  }

  delay(20);
}

void displayConnectedMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("+------------------+");
  lcd.setCursor(4, 1); // Centrer le texte "CONNECTE" sur la ligne 1
  lcd.print("CONNECTION");
  lcd.setCursor(6, 2); // Centrer le texte "CONNECTE" sur la ligne 1
  lcd.print("ETABLIE");
  lcd.setCursor(0, 3);
  lcd.print("+------------------+");
  delay(2000); // Afficher le message pendant 2 secondes
  lcd.clear();
}

void displayWaitingForConnection() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("+------------------+");
  lcd.setCursor(3, 1); // Centrer le texte "Attente de connexion" sur la ligne 2
  lcd.print("En attente de");
  lcd.setCursor(4, 2); // Centrer le texte "Attente de connexion" sur la ligne 2
  lcd.print("Connection");
  lcd.setCursor(0, 3);
  lcd.print("+------------------+");
  delay(1000);
}

void updateMenuButtons() {
  if (isConnectedDisplayed) {
    if (digitalRead(buttonPinMenuTotal) == LOW) {
      isAttenteDisplayed = false;
      isPersonnesDisplayed = false;
      isDecompteDisplayed = false;
      menuState = MENU_TOTAL;
      delay(200);
    }

    if (digitalRead(buttonPinMenuPersonnes) == LOW) {
      isAttenteDisplayed = false;
      isTotalDisplayed = false;
      isDecompteDisplayed = false;
      menuState = MENU_PERSONNES;
      delay(200);
    }

    if (digitalRead(buttonPinMenuDecompte) == LOW) {
      isAttenteDisplayed = false;
      isTotalDisplayed = false;
      isPersonnesDisplayed = false;
      menuState = MENU_DECOMPTE;
      delay(200);
    }
  }
}

void updatePersonButtons() {
  for (int i = 0; i < numButtons; i++) {
    buttonStates[i] = digitalRead(buttonPins[i]);

    if (buttonStates[i] != lastButtonStates[i]) {
      if (buttonStates[i] == LOW) {
        if (isConnectedDisplayed) {

          //Buzzer
          digitalWrite(buzzerPin, HIGH);
          delay(100);
          digitalWrite(buzzerPin, LOW);
          delay(100);
          digitalWrite(buzzerPin, HIGH);
          delay(100);
          digitalWrite(buzzerPin, LOW);


          personnesPassant[i]++;
          totalTours++;

          // Calculer le temps du tour et l'afficher sur le terminal série
          unsigned long currentTime = millis();
          unsigned long tourTime = currentTime - lastPassageTime[i];
          lastPassageTime[i] = currentTime;

          // Convertir le temps du tour en h:min:sec:millisec
          unsigned long tourHours = tourTime / MILLIS_PER_HOUR;
          unsigned long tourMinutes = (tourTime % MILLIS_PER_HOUR) / MILLIS_PER_MINUTE;
          unsigned long tourSeconds = (tourTime % MILLIS_PER_MINUTE) / MILLIS_PER_SECOND;
          unsigned long tourMilliseconds = tourTime % MILLIS_PER_SECOND;

          dernierePersonne = i;
          for (int j = 9; j > 0; j--) {
            dernieresPersonnes[j] = dernieresPersonnes[j - 1];
          }
          dernieresPersonnes[0] = dernierePersonne;

          // Mettre à jour l'affichage du total des tours et des dernières personnes si nécessaire
          if (menuState == MENU_TOTAL) {
            displayTotal();
          } else if (menuState == MENU_PERSONNES) {
            displayDernieresPersonnes();
          }

          Serial.print("Personne ");
          Serial.print(i + 1);
          Serial.print(" total: ");
          Serial.print(personnesPassant[i]);
          Serial.print(" lap: ");
          Serial.print(tourHours);
          Serial.print(":");
          Serial.print(tourMinutes);
          Serial.print(":");
          Serial.print(tourSeconds);
          Serial.print(":");
          Serial.println(tourMilliseconds);

        }
      }
      lastButtonStates[i] = buttonStates[i];
    }
  }
}



void displayTotal() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("+------------------+");
  lcd.setCursor(1, 1); // Centrer le texte "Total tours:" sur la ligne 2
  lcd.print("Total des tours:");
  lcd.setCursor(1, 2); // Centrer le nombre de tours sur la ligne 3
  lcd.print(totalTours);
  lcd.setCursor(0, 3);
  lcd.print("+------------------+");
}

void displayDernieresPersonnes() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("+------------------+");
  lcd.setCursor(1, 1); // Centrer le texte "Dernieres pers." sur la ligne 2
  lcd.print("Derniers passages.");
  for (int i = 0; i < 6; i++) {
    lcd.setCursor(i * 3 + 1, 2); // Centrer le numéro de personne sur la ligne 3
    lcd.print(dernieresPersonnes[i] + 1);
  }
  lcd.setCursor(0, 3);
  lcd.print("+------------------+");
}

void displayDecompte() {
  unsigned long tempsRestant = decompteDuree - (millis() - decompteDebut);
  int heures = tempsRestant / MILLIS_PER_HOUR;
  int minutes = (tempsRestant % MILLIS_PER_HOUR) / MILLIS_PER_MINUTE;
  int secondes = (tempsRestant % MILLIS_PER_MINUTE) / MILLIS_PER_SECOND;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("+------------------+");
  lcd.setCursor(1, 1); // Centrer le texte "Decompte:" sur la ligne 2
  lcd.print("Temps restant:");
  lcd.setCursor(1, 2); // Centrer l'affichage du temps restant sur la ligne 3
  lcd.print(heures);
  lcd.print("h");
  lcd.print(minutes);
  lcd.print("m");
  lcd.print(secondes);
  lcd.print("s");
  lcd.setCursor(0, 3);
  lcd.print("+------------------+");
}
