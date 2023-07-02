String writeCmd(String cmdToWrite) {
  String cmdTXT = "";
  Boolean error = false;

  String[] numbers = cmdToWrite.split(" ");
  int[] parsedNumbers = new int[numbers.length];

  for (int i = 0; i < numbers.length; i++) {
    parsedNumbers[i] = Integer.parseInt(numbers[i]);
  }

  cmdTXT+="Quando ";

  switch(parsedNumbers[0]) {
  case 0:
    cmdTXT += "D";
    break;
  case 1:
    cmdTXT += "A";
    break;
  default:
    error = true;
    break;
  }

  switch(parsedNumbers[1]) {
  case -1:
    error = true;
    break;
  default:
    cmdTXT += parsedNumbers[1];
    break;
  }

  cmdTXT+=" ";

  switch(parsedNumbers[2]) {
  case 0:
    cmdTXT += "!=";
    break;
  case 1:
    cmdTXT += "==";
    break;
  case 2:
    cmdTXT += "<=";
    break;
  case 3:
    cmdTXT += "<";
    break;
  case 4:
    cmdTXT += ">=";
    break;
  case 5:
    cmdTXT += ">";
    break;
  default:
    error = true;
    break;
  }

  cmdTXT+=" ";

  switch(parsedNumbers[3]) {
  case -1:
    error = true;
    break;
  default:
    cmdTXT += parsedNumbers[3];
    break;
  }

  cmdTXT+=" imposta ";

  switch(parsedNumbers[4]) {
  case 0:
    cmdTXT += "D";
    break;
  case 1:
    cmdTXT += "A";
    break;
  default:
    error = true;
    break;
  }

  switch(parsedNumbers[5]) {
  case -1:
    error = true;
    break;
  default:
    cmdTXT += parsedNumbers[5];
    break;
  }

  cmdTXT+=" a ";

  switch(parsedNumbers[6]) {
  case -1:
    error = true;
    break;
  default:
    cmdTXT += parsedNumbers[6];
    break;
  }

  cmdTXT+=" dopo ";

  switch(parsedNumbers[7]) {
  case -1:
    error = true;
    break;
  default:
    cmdTXT += parsedNumbers[7];
    break;
  }

  cmdTXT+=" ms ";

  if (error) {
    cmdTXT = "Errore di scrittura, eliminare questa riga";
  }

  return cmdTXT;
}
