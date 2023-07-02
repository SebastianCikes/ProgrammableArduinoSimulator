class JGUITextfield extends JGUIComponent<JGUITextfield> {
  private String textValue;
  private String label;
  private color labelColor;

  private int debounceM;
  private int debounceK;
  private boolean selected;

  public JGUITextfield(int x, int y) {
    setPos(x - 35, y - 16);
    setSize(0, 0);
    textValue = "";
    label = "";
    labelColor = color(0, 0, 0);

    selected = false;
    debounceM = 0;
    debounceK = 0;
  }

  public JGUITextfield setLabel(String lbl) {
    label = lbl;
    return this;
  }

  public JGUITextfield setLabelColor(color col) {
    this.labelColor = col;
    return this;
  }

  public color getLabelColor() {
    return labelColor;
  }

  public void draw() {
    rectMode(CORNER);
    stroke(205);
    fill(getFillColor());
    rect(getPos().x, getPos().y, getSize().x, getSize().y);

    textAlign(LEFT, CENTER);
    textSize(16);
    fill(getTextColor());
    text(textValue, getPos().x + 5, getPos().y + getSize().y/2);

    fill(labelColor);
    text(label, getPos().x + 5, getPos().y + getSize().y+5);
  }

  public void handle() {
    if (mousePressed && abs(mouseX - (getPos().x + getSize().x/2)) <= getSize().x/2
      && abs(mouseY - (getPos().y + getSize().y/2)) <= getSize().y/2 && debounceM == 0) {
      debounceM = 15;
      selected = !selected;
    }

    if (debounceM > 0)
      debounceM--;

    if (selected && keyPressed && debounceK == 0) {
      if (key == BACKSPACE && textValue.length() > 0)
        textValue = textValue.substring(0, textValue.length()-1);
      else if (key >= '0' && key <= '9') {
        textValue += key;
        String firstVal = textValue.substring(0, 1);
        if (Integer.parseInt(textValue) > 10000 || Integer.parseInt(firstVal) < 0)
          textValue = textValue.substring(0, textValue.length()-1);
      }
      debounceK = 15;
    }

    if (debounceK > 0)
      debounceK--;
  }

  public String getText() {
    return textValue;
  }
}
