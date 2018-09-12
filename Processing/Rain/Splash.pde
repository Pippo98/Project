class Splash{
  
  int x, y;
  float speedX, speedY;
  float gravity = 0.25;
  float r1, r2;
  int count;
  
  Splash(int Sx, int Sy, float SSpeedX, float SSpeedY){
    SSpeedY += 1;
    SSpeedY += random(0, 4);
    r1 = random(2, 4);
    
    x = Sx;
    y = Sy;
    speedX = SSpeedX;
    speedY = SSpeedY;
    
  }
  
  void display(){
    ellipse(x, y, r1, r1);
  }
  
  void refresh(){
    speedY += gravity;
    y += speedY;
    x += speedX;
  }
  
  boolean bounce(){
    if(y > height - (rectHeight + 5)){
      count ++;
      return true;
    }
    else
    return false;
  }
  
  boolean died(){
    if(y > height - (rectHeight + 5)){
      return true;
    }
    else
    return false;
  }
  
  
}