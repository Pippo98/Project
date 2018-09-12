class Drop {

  int x, y;
  float gravity = 0.05;
  float speedY = -0.5;
  float SpeedX = 0;
  boolean died = false;
  float rnd = 0;

  Drop() {
    x = int(random(0, width));
    y = -10;
    speedY += gravity;
  }

  void display() {
    fill(255);
    ellipse(x, y, 5, 6);
  }

  void refresh() {
    speedY += gravity;
    y += speedY;
  }

  void ground() {

    if (y > height - rectHeight) {
      y = height - rectHeight;
      SpeedX = random(0, 2);
      splashy.add(new Splash(x, y, SpeedX, -speedY/0.9));
      SpeedX = random(-2, 0);
      splashy.add(new Splash(x, y, SpeedX, -speedY/0.9));
      died = true;
    }
  }

  boolean died() {
    if (died)
      return true;
    else
      return false;
  }
}