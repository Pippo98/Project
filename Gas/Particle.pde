class Particle{
  
  float x, y, speedX, speedY;
  boolean bounce = false;
   
  Particle(){
    x = random(percent, width - percent);
    y = random(percent, height - percent);
    speedX = random(-4, 4);
    speedY = random(-4, 4);
  }
  
  void bounce(){
    
    if(x < percent || x > width - percent)
    speedX *= -1;
    
    if(y < percent || y > height - percent)
    speedY *= -1;
    
  }
  
  void refresh(){
    
    x += speedX;
    y += speedY;
  
  }
  
  void display(){
  
    fill(255);
    ellipse(x, y, 5, 5);
    
  }
}