#pragma config(Sensor, S1, sensorLuzEsq, sensorLightActive)
#pragma config(Sensor, S2, sensorLuzDir, sensorLightActive)
#pragma config(Sensor, S3, sonar, sensorSONAR)
#pragma config(Motor, motorA, motorEsq, tmotorNormal, PIDControl, encoder)
#pragma config(Motor, motorB,  motorDir, tmotorNormal, PIDControl, encoder)
#pragma platform(NXT)

#define PARADO 0
#define FRENTE 1
#define CURVA_DIR 2
#define CURVA_ESQ 3
#define BIFURCA 4
#define OBSTACULO 5

#define B_DIREITA 1
#define B_ESQUERDA 2
#define B_LARANJA 3

#define VELOCIDADE 50

#define PRATA 75
#define BRANCO 55
#define PRETO 25

task controle();

int obterCor(int sensor);
void andar(int direita,int esquerda);
void curva(char sentido);
void emFrente();
void parar();
void desviar();

bool caminhar = true;
int estado = PARADO;

task main(){
StartTask(controle);
  for(;;){
    if(caminhar){
      switch(estado){
        case PARADO:
          nxtDisplayString(1,"PARADO");
          parar();
        break;
        case FRENTE:
          nxtDisplayString(1,"FRENTE");
          emFrente();
        break;
        case CURVA_DIR:
          nxtDisplayString(1,"CURVA DIREITA");
          curva('D');
        break;
        case CURVA_ESQ:
          nxtDisplayString(1,"CURVA ESQUERDA");
          curva('E');
        break;
        case BIFURCA:
          nxtDisplayString(1,"BIFURCA");
          curva('E');
        break;
        case OBSTACULO:
          nxtDisplayString(1,"OBSTACULO");
          StopTask(controle);
          desviar();
        break;
        default:
          nxtDisplayString(1,"ERRO");
      }
    }
  }
}

task controle(){
	int luzEsq;
	int luzDir;
	int distancia;
  for(;;){
    luzEsq = obterCor(SensorValue[sensorLuzEsq]);
    luzDir = obterCor(SensorValue[sensorLuzDir]);
    distancia = SensorValue[sonar];
    if(distancia < 10)
      estado = OBSTACULO;
    else
	    if(luzEsq == BRANCO && luzDir == BRANCO)
	      estado = FRENTE;
	    else if (luzDir == PRETO && luzEsq == BRANCO)
	      estado = CURVA_DIR;
	    else if (luzDir == BRANCO && luzEsq == PRETO)
	      estado = CURVA_ESQ;
	    else if(luzDir == PRETO && luzEsq == PRETO)
	      estado = BIFURCA;
	    else
	      estado = PARADO;
  }
}

int obterCor(int sensor){
  if(sensor < PRATA)
    if(sensor > BRANCO)
      return BRANCO;
    else if(sensor > PRETO)
      return PRETO;
    else
       return -1;
  else
    return PRATA;
}

void desviar(){
  /*TODO
  Girar 90 graus pra esquerda
  Girar 90 graus pra direita
  Girar 90 graus pra direita denovo
  */
  StartTask(controle);
}

void curva(char sentido){
  if(sentido == 'D')
    andar(-2,1);
  else if(sentido == 'E')
    andar(1,-2);
}

void emFrente(){
    andar(1,1);
}

void parar(){
  motor[motorDir] = 0;
  motor[motorEsq] = 0;
}

void andar(int direita, int esquerda){
  motor[motorDir] = VELOCIDADE/direita;
  motor[motorEsq] = VELOCIDADE/esquerda;
}
