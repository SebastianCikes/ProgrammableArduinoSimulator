/*
 * @files drop_puls.pde, ClasseFactory.pde, CommandExtraction.pde, Init.pde, JGUIText.pde, SerialEvents.pde, WriteCmd.pde
 * @author Sebastian Cikes <cikes.sebastian@gmail.com>
 * @version 2.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * https://www.gnu.org/copyleft/gpl.html
 *
 * The GUI is based on JGUILib, made by Davide Messori
 * https://github.com/davidemesso/JGUILib
 */

import processing.serial.*;

// Variabili GUI
JGUIController controller;
ArrayList<JGUIDropdown> dropdowns = new ArrayList<>();
ArrayList<JGUITextfield> textfields = new ArrayList<>();
ArrayList<JGUIText> text = new ArrayList<>();
JGUIText t;
JGUIDropdown ddSerial;
JGUIButton buttons;
ArrayList<JGUIText> txtCmd = new ArrayList<>();

// Variabili conunicazione seriale
Serial port;
ArrayList<String> availableCOM = new ArrayList<>();
String actualCOM = "";
int countCOM = 0;
ArrayList<String> dataToSend = new ArrayList<>();

// Altre variabili
ArrayList<String> cmd = new ArrayList<>();
int countCmd = 0;
int nDD = 3;
int nTF = 5;

void setup() {
  size(1280, 720);
  frameRate(60);
  background(255);

  controller = new JGUIController();  // Controller GUI

  init();                             // Inizializzazione
}

void draw() {
  background(255);
  controller.handle();          // Controllo GUI
  serialCOM();                  // Controllo COM seriale

  dataToSend = extraction();    // Estrazione comandi
}


Callback addCallback = new CallbackFunction() {    // Callback pulsante Add
  void call() {
    if (countCmd < 45)
      countCmd++;
  }
};

Callback delCallback = new CallbackFunction() {    // Callback pulsante Del
  void call() {
    if (countCmd > 0)
      countCmd--;
  }
};

Callback startCallback = new CallbackFunction() {  // Callback pulsante Start
  void call() {
    serialWrite("Start");
  }
};

Callback stopCallback = new CallbackFunction() {   // Callback pulsante Stop
  void call() {
    serialWrite("Stop");
  }
};

Callback loadCallback = new CallbackFunction() {   // Callback pulsante Load
  void call() {
    for (int i = 0; i < dataToSend.size(); i++) {
      serialWrite(dataToSend.get(i));
    }
  }
};
