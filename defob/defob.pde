import processing.serial.*;
  
ArrayList obstaculo, obstaculos; //de vertices
PVector v1,v2,v3,v4; //ponto 1 e ponto 2 pra formar uma linha
int estado; //para controlar cada leitura, ponto 1 ou 2

void setup(){
  obstaculos = new ArrayList<ArrayList>();
  estado = 0;
  background(255);
  size(1104, 900);
  cursor(CROSS);
}

void draw() {
}

/*
Exibe os pontos dos cliques para formar a linha
cada clique salva o ponto em uma variavel diferente
esse metodo so captura os vertices da linha ou 
obstaculo que vai ser formado
*/
void mouseClicked() {
  if(estado == 0){
    v1 = new PVector(mouseX, mouseY);
    estado = 1;
    print("Ponto 1: "+ v1 +"\n");
  }else if(estado == 1){
    v2 = new PVector(mouseX, mouseY);
    estado = 2;
    print("Ponto 2: "+ v2 +"\n");
  }else if(estado == 2){
    v3 = new PVector(mouseX, mouseY);
    estado = 3;
    print("Ponto 3: "+ v1 +"\n");
  }else if(estado == 3){
    v4 = new PVector(mouseX, mouseY);
    estado = 0;
    print("Ponto 4: "+ v2 +"\n");
    
    fill(100);
    quad(v1.x,v1.y,v2.x,v2.y,v3.x,v3.y,v4.x,v4.y);
    
    obstaculo = new ArrayList<PVector>();
    obstaculo.add(v1);
    obstaculo.add(v2);
    obstaculo.add(v3);
    obstaculo.add(v4);
    obstaculos.add(obstaculo);
  }
  //print("Estado: "+ estado + "\n");
}

/*
exibe o obstaculo em forma de linha 
e salva os vertices em uma lista
nao pressionar p sem ter certeza dos
pontos ou vertices que querem formar
*/
void keyPressed(){
  if(key == 'P' || key == 'p'){
    fill(100);
    quad(v1.x,v1.y,v2.x,v2.y,v3.x,v3.y,v4.x,v4.y);
    
    obstaculo = new ArrayList<PVector>();
    obstaculo.add(v1);
    obstaculo.add(v2);
    obstaculo.add(v3);
    obstaculo.add(v4);
    obstaculos.add(obstaculo);
  }
  print("Lista dos vertices: "+ obstaculo + "\n");
}
