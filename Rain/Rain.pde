ArrayList <Drop> drops;
ArrayList <Splash> splashy;

void setup(){
  fullScreen();
  drops = new ArrayList <Drop>();
  splashy = new ArrayList <Splash>();
}

int rectHeight = 20;
float time = 0;

void draw(){
  
  //background(8, 24, 60);
  background(85, 90, 95);
  saturation(255);
  frameRate(60);
  
  fill(20);
  rect(0, height, width, -rectHeight);
  
  if(millis() - time >= 70){
    time = millis();
    drops.add(new Drop());
  }
  
  for(int i = 0; i < drops.size(); i++){
    Drop drop = drops.get(i);
    drop.display();
    drop.refresh();
    drop.ground();
    if(drop.died()){
      drops.remove(i);
    }
  }
  
  for(int I = 0; I < splashy.size(); I++){
    Splash splash = splashy.get(I);
    splash.refresh();
    splash.display();
    if(splash.bounce()){
      splash.speedY *= -1;
      splash.speedY *= 0.4;
    }
    if(splash.count >= 5){
      splashy.remove(I);
    }
  }
  
}