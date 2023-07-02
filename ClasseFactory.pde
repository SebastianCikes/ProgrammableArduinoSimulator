void insert(int x, int y) {
  text.add(new JGUIText(x, y, 16, "Quando", "c")
    .setSize(70, 32)
    .setTextColor(color(255, 255, 255)));

  dropdowns.add(new JGUIDropdown("pinType", x+105, y)
    .setSize(35, 16)
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255))
    .addButton(new JGUIButton("D"))
    .addButton(new JGUIButton("A")));

  textfields.add(new JGUITextfield(x+185, y)
    .setSize(70, 32)
    .setLabel("pinNum")
    .setLabelColor(color(0, 0, 0))
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255)));

  dropdowns.add(new JGUIDropdown("condition", x+265, y)
    .setSize(35, 16)
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255))
    .addButton(new JGUIButton("!="))
    .addButton(new JGUIButton("=="))
    .addButton(new JGUIButton("<="))
    .addButton(new JGUIButton("<"))
    .addButton(new JGUIButton(">="))
    .addButton(new JGUIButton(">")));

  textfields.add(new JGUITextfield(x+345, y)
    .setSize(70, 32)
    .setLabel("value")
    .setLabelColor(color(0, 0, 0))
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255)));

  text.add(new JGUIText(x+400, y, 16, "imposta", "c")
    .setSize(70, 32)
    .setTextColor(color(255, 255, 255)));

  dropdowns.add(new JGUIDropdown("pinType", x+505, y)
    .setSize(35, 16)
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255))
    .addButton(new JGUIButton("D"))
    .addButton(new JGUIButton("A")));

  textfields.add(new JGUITextfield(x+585, y)
    .setSize(70, 32)
    .setLabel("pinNum")
    .setLabelColor(color(0, 0, 0))
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255)));

  text.add(new JGUIText(x+621, y, 16, "a", "c")
    .setSize(70, 32)
    .setTextColor(color(255, 255, 255)));

  textfields.add(new JGUITextfield(x+705, y)
    .setSize(70, 32)
    .setLabel("value")
    .setLabelColor(color(0, 0, 0))
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255)));

  text.add(new JGUIText(x+750, y, 16, "dopo", "c")
    .setSize(70, 32)
    .setTextColor(color(255, 255, 255)));

  textfields.add(new JGUITextfield(x+840, y)
    .setSize(70, 32)
    .setLabel("time")
    .setLabelColor(color(0, 0, 0))
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255)));

  text.add(new JGUIText(x+880, y, 16, "ms", "c")
    .setSize(70, 32)
    .setTextColor(color(255, 255, 255)));

  for (int i = 0; i < nTF; i++) {
    controller.add(textfields.get(i+nTF*countCmd));
  }
  for (int i = 0; i < nDD; i++) {
    controller.add(dropdowns.get(i+nDD*countCmd));
  }
  for (int i = 0; i < 5; i++) {
    controller.add(text.get(i+5*countCmd));
  }
}
