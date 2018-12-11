import processing.serial.*;
  
ArrayList lista; //de vertices
PVector v1,v2; //ponto 1 e ponto 2 pra formar uma linha
int estado; //para controlar cada leitura, ponto 1 ou 2

void setup(){
  lista = new ArrayList<PVector>();
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
    estado = 0;
    print("Ponto 2: "+ v2 +"\n");
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
    line(v1.x,v1.y,v2.x,v2.y);
    lista.add(v1);
    lista.add(v2);
  }
  print("Lista dos vertices: "+ lista + "\n");
}
