void init() {
  t =  // Text, titolo
    new JGUIText(400, 50, 42, "Simulatore programmabile stazioni festo", "c")
    .setTextColor(color(255, 255, 255));
  controller.add(t);

  ddSerial =  // Dropdown, seriale
    new JGUIDropdown("Serial", 1180, 55)
    .setSize(35, 16)
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255));
  controller.add(ddSerial);

  buttons =   // Button, aggiungi riga comando
    new JGUIButton("Add", 1050, 130)
    .setSize(35, 16)
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255))
    .setCallback(addCallback);
  controller.add(buttons);

  buttons =   // Button, elimina riga comando
    new JGUIButton("Del", 1050, 170)
    .setSize(35, 16)
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255))
    .setCallback(delCallback);
  controller.add(buttons);

  buttons =   // Button, start
    new JGUIButton("Start", 970, 55)
    .setSize(35, 16)
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255))
    .setCallback(startCallback);
  controller.add(buttons);

  buttons =   // Button, stop
    new JGUIButton("Stop", 1050, 55)
    .setSize(35, 16)
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255))
    .setCallback(stopCallback);
  controller.add(buttons);

  buttons =   // Button, load
    new JGUIButton("Load", 890, 55)
    .setSize(35, 16)
    .setFillColor(color(20, 20, 128))
    .setTextColor(color(255, 255, 255))
    .setCallback(loadCallback);
  controller.add(buttons);

  insert(50, 130);
}
