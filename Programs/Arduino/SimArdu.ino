/*
   @files SimArdu.ino
   @author Sebastian Cikes <cikes.sebastian@gmail.com>
   @version 1.0

   @section LICENSE

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   General Public License for more details at
   https://www.gnu.org/copyleft/gpl.html
*/

/*
   Analog output: PWM 960Hz
   4, 13, 9, 10
   Analog output: PWM 490Hz
   2, 3, 5, 6, 7, 8

   Analog input
   A0, A1, A8, A9, A10, A11, A12, A13, A14, A15

   Digital output
   22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52

   Digital output
   23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53
*/

const int AO[10] = {4, 13, 9, 10, 2, 3, 5, 6, 7, 8};
const int AI[10] = {A0, A1, A8, A9, A10, A11, A12, A13, A14, A15};
const int DO[16] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
const int DI[16] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53};

int INtype[45] = {};
int IN[45] = {};
int CONDITION[45] = {};
int INvalue[45] = {};
int OUTtype[45] = {};
int OUT[45] = {};
int OUTvalue[45] = {};
double DELAY[45] = {};
double DELAYlast[45] = {};
bool debounce[45] = {};

String cmd = "";
String cmdSingle[45] = {};
int index = 0;

double now = 0;

bool stato = false;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 10; i++) {
    pinMode(AO[i], OUTPUT);
    pinMode(AI[i], INPUT);
  }
  for (int i = 0; i < 16; i++) {
    pinMode(DO[i], OUTPUT);
    pinMode(DI[i], INPUT);
  }
}

void loop() {
  if (Serial.available())  { // Lettura comandi da seriale (Processing)
    cmd = Serial.readString();
    cmd.trim();

    if (cmd.equals("Start")) {
      stato = true;
      reset();
    } else if (cmd.equals("Stop")) {
      stato = false;
      reset();
    } else {
      cmdExtraction();  // Estrazione comandi singoli
      pinExtraction();  // Estrazione pin IO da cmd singoli
    }
  }

  if (stato) {
    manageIO();     // Manager input output
  }
}

void cmdExtraction() {
  int startIndex = 0;
  int commaIndex;

  commaIndex = cmd.indexOf(',');
  while (commaIndex != -1)  {
    String subString = cmd.substring(startIndex, commaIndex);
    cmdSingle[index] = subString;

    startIndex = commaIndex + 2; // Incrementa per saltare sia la virgola che lo spazio successivo
    commaIndex = cmd.indexOf(',', startIndex);
    index++;
  }

  // Gestisci l'ultima subString fuori dal ciclo
  cmdSingle[index] = cmd.substring(startIndex);

  /*for (int i = 0; i <= index; i++) {
    Serial.println(cmdSingle[i]);
    }*/
}

void pinExtraction () {
  // Primi 2 valori di cmdSingle[] dicono il pin interessato -> abbinamento comando a pin

  for (int i = 0; i <= index; i++) {  // Per ogni riga di comando

    // Estrazione dati
    // Array per contenere i valori convertiti
    int values[8];

    // Copia la stringa di input in una stringa di lavoro
    char inputBuffer[cmdSingle[i].length() + 1];
    cmdSingle[i].toCharArray(inputBuffer, sizeof(inputBuffer));

    // Inizializza il puntatore al primo token
    char* token = strtok(inputBuffer, " ");

    // Utilizza strtok per ottenere i valori successivi fino a quando non viene restituito NULL
    for (int j = 0; j < 8 && token != NULL; j++) {
      // Converte il token in un intero e lo assegna all'array
      values[j] = atoi(token);

      // Ottieni il token successivo
      token = strtok(NULL, " ");
    }

    // Trasformazione in comandi reali
    switch (values[0]) {            // Pin input
      case 0: // Digitale
        IN[i] = DI[values[1]];
        INtype[i] = 0;
        break;
      case 1: //Analogico
        IN[i] = AI[values[1]];
        INtype[i] = 1;
        break;
    }

    CONDITION[i] = values[2];   // Condition

    switch (values[4]) {            // Pin output
      case 0: // Digitale
        OUT[i] = DO[values[5]];
        OUTtype[i] = 0;
        break;
      case 1: //Analogico
        OUT[i] = AO[values[5]];
        OUTtype[i] = 1;
        break;
    }

    INvalue[i] = values[3];
    OUTvalue[i] = values[6];
    DELAY[i] = values[7];
  }
}

void manageIO() {
  for (int k = 0; k < index + 1; k++) {
    now = millis();

    switch (CONDITION[k]) {
      case 0:                                               // !=
        switch (INtype[k]) {
          case 0:
            switch (OUTtype[k]) {
              case 0:
                if (digitalRead(IN[k]) != INvalue[k]) {     // IN digitale, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (digitalRead(IN[k]) != INvalue[k]) {     // IN digitale, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
          case 1:
            switch (OUTtype[k]) {
              case 0:
                if (analogRead(IN[k]) != INvalue[k]) {     // IN analogico, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (analogRead(IN[k]) != INvalue[k]) {     // IN analogico, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
        }
        break;
      case 1:                                               // ==
        switch (INtype[k]) {
          case 0:
            switch (OUTtype[k]) {
              case 0:
                //Serial.println(INvalue[k]);
                if (digitalRead(IN[k]) == INvalue[k]) {     // IN digitale, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (digitalRead(IN[k]) == INvalue[k]) {     // IN digitale, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
          case 1:
            switch (OUTtype[k]) {
              case 0:
                if (analogRead(IN[k]) == INvalue[k]) {     // IN analogico, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (analogRead(IN[k]) == INvalue[k]) {     // IN analogico, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
        }
        break;
      case 2:                                               // <=
        switch (INtype[k]) {
          case 0:
            switch (OUTtype[k]) {
              case 0:
                if (digitalRead(IN[k]) <= INvalue[k]) {     // IN digitale, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (digitalRead(IN[k]) <= INvalue[k]) {     // IN digitale, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
          case 1:
            switch (OUTtype[k]) {
              case 0:
                if (analogRead(IN[k]) <= INvalue[k]) {     // IN analogico, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (analogRead(IN[k]) <= INvalue[k]) {     // IN analogico, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
        }
        break;
      case 3:                                              // <
        switch (INtype[k]) {
          case 0:
            switch (OUTtype[k]) {
              case 0:
                if (digitalRead(IN[k]) < INvalue[k]) {     // IN digitale, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (digitalRead(IN[k]) < INvalue[k]) {     // IN digitale, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
          case 1:
            switch (OUTtype[k]) {
              case 0:
                if (analogRead(IN[k]) < INvalue[k]) {     // IN analogico, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (analogRead(IN[k]) < INvalue[k]) {     // IN analogico, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
        }
        break;
      case 4:                                               // >=
        switch (INtype[k]) {
          case 0:
            switch (OUTtype[k]) {
              case 0:
                if (digitalRead(IN[k]) >= INvalue[k]) {     // IN digitale, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (digitalRead(IN[k]) >= INvalue[k]) {     // IN digitale, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
          case 1:
            switch (OUTtype[k]) {
              case 0:
                if (analogRead(IN[k]) >= INvalue[k]) {     // IN analogico, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (analogRead(IN[k]) >= INvalue[k]) {     // IN analogico, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
        }
        break;
      case 5:                                              // >
        switch (INtype[k]) {
          case 0:
            switch (OUTtype[k]) {
              case 0:
                if (digitalRead(IN[k]) > INvalue[k]) {     // IN digitale, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (digitalRead(IN[k]) > INvalue[k]) {     // IN digitale, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
          case 1:
            switch (OUTtype[k]) {
              case 0:
                if (analogRead(IN[k]) > INvalue[k]) {     // IN analogico, OUT digitale
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    digitalWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
              case 1:
                if (analogRead(IN[k]) > INvalue[k]) {     // IN analogico, OUT analogico
                  if (!debounce[k]) {
                    DELAYlast[k] = now;
                    debounce[k] = true;
                  }
                  if (now - DELAYlast[k] >= DELAY[k]) {
                    analogWrite(OUT[k], OUTvalue[k]);
                    debounce[k] = false;
                  }
                }
                break;
            }
            break;
        }
        break;
    }
  }
}

void reset() {
  for (int i = 0; i < 16; i++) {
    digitalWrite(DO[i], LOW);
  }
  for (int i = 0; i < 10; i++) {
    analogWrite(AO[i], 0);
  }
  for (int i = 0; i < 45; i++) {
    debounce[i] = false;
  }
}
