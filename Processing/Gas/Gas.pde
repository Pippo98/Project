ArrayList <Particle> particles;
float percent = 100;
int count = 0;

void setup(){
  
  size(700, 700);
  particles = new ArrayList <Particle>();
  particles.add(new Particle());
  
}

void draw(){
  
  background(0);
  stroke(255);
  noFill();
  rect(percent, percent, width - 2*percent, height - 2*percent);
  
  for(Particle p : particles){
    
    p.bounce();
    p.refresh();
    p.display();
    
  }
  
  if(count <= 100){
    particles.add(new Particle());
    count++;
  }
  
}