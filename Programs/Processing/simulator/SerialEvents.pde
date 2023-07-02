void serialCOM() {
  String[] portNames = Serial.list();

  if (portNames.length > 0) {
    for (int i = 0; i < portNames.length; i++) {          // Creo n° pulsanti per DD in base a n° COM

      if (countCOM != portNames.length) {
        ddSerial.addButton(new JGUIButton(portNames[i]));
        availableCOM.add(portNames[i]);
        countCOM++;
      }
    }

    if (ddSerial.getValue() != -1) {
      if (!actualCOM.equals(portNames[ddSerial.getValue()])) {  // Imposta COM
        if (!actualCOM.equals("")) {
          port.stop();
        }
        actualCOM = portNames[ddSerial.getValue()];
        port = new Serial(this, actualCOM, 9600);
      }
    }
  }
}

void serialWrite(String data) {
  if (!actualCOM.equals("")) {
    println(data);
    port.write(data);
  }
}
