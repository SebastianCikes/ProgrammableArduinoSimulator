class JGUIText extends JGUIComponent<JGUIText> {
  private String textValue;
  private int textSize;
  private String alignment;

  public JGUIText(int x, int y, int s, String txt, String all) {
    setPos(x+25, y-3);
    textSize = s;
    textValue = txt;
    alignment = all;
  }

  public void draw() {
    fill(0);
    textSize(textSize);
    if (alignment == "c") {
      textAlign(CENTER, CENTER);
    } else if (alignment == "l") {
      textAlign(LEFT, CENTER);
    } else if (alignment == "r") {
      textAlign(RIGHT, CENTER);
    }

    text(textValue, getPos().x, getPos().y);
  }

  public void handle() {
  }
}
