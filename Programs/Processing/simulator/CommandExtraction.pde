ArrayList extraction() {
  String[] DDvalue = new String[nDD];
  String[] TXTvalue = new String[nTF];
  int coordX = 0, coordY = 0;

  if (cmd.size() < countCmd) {
    for (int i = 0; i < nDD; i++) {                                    // Estrazione Dropdown
      JGUIDropdown dropdown = dropdowns.get(i);
      DDvalue[i] = Integer.toString(dropdown.getValue());
    }

    for (int i = 0; i < nTF; i++) {                                    // Estrazione Textfield
      JGUITextfield textfield = textfields.get(i);
      TXTvalue[i] = textfield.getText();
      if (TXTvalue[i] == "") {
        TXTvalue[i] = "-1";
      }
    }

    // Composizione comando
    String rigaComando = DDvalue[0] + " " + TXTvalue[0] + " " + DDvalue[1] + " " + TXTvalue[1] + " " +
      DDvalue[2] + " " + TXTvalue[2] + " " + TXTvalue[3] + " " + TXTvalue[4];
    cmd.add(rigaComando);

    if (countCmd > 30) {
      coordX = 830;
      coordY = 30;
    } else if (countCmd > 15) {
      coordX = 430;
      coordY = 15;
    } else {
      coordX = 30;
      coordY = 0;
    }

    // Scrivi comando su GUI
    txtCmd.add(new JGUIText(coordX, 200+((countCmd-coordY)*30), 16, writeCmd(rigaComando), "l")
      .setSize(70, 32)
      .setTextColor(color(255, 255, 255)));

    controller.add(txtCmd.get(countCmd-1));
  } else if (cmd.size() > countCmd) {
    controller.remove(txtCmd.get(countCmd));
    txtCmd.remove(txtCmd.get(countCmd));

    cmd.remove(cmd.size()-1);
  }

  return cmd;
}
