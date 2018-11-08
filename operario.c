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
void andar(int esquerda,int direita);
void curva(char sentido);
void emFrente();
void stopAllMotors();

bool caminhar = true;
int estado = PARADO;

task main(){
StartTask(controle);
  for(;;){
    if(caminhar){
      switch(estado){
        case PARADO:
          stopAllMotors();
          nxtDisplayString(1,"PARADO");
        break;
        case FRENTE:
          stopAllMotors();
          nxtDisplayString(1,"FRENTE");
          emFrente();
        break;
        case CURVA_DIR:
          stopAllMotors();
          nxtDisplayString(1,"CURVA DIREITA");
          curva('D');
        break;
        case CURVA_ESQ:
          stopAllMotors();
          nxtDisplayString(1,"CURVA ESQUERDA");
          curva('E');
        break;
        case BIFURCA:
          stopAllMotors();
          nxtDisplayString(1,"BIFURCA");
        break;
        case OBSTACULO:
          stopAllMotors();
          nxtDisplayString(1,"OBSTACULO");
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
  for(;;){
    luzEsq = obterCor(SensorValue[sensorLuzDir]);
    luzDir = obterCor(SensorValue[sensorLuzEsq]);
    if(luzEsq == BRANCO && luzDir == BRANCO)
      estado = FRENTE;
    else if (luzDir == PRETO && luzEsq == BRANCO)
      estado = CURVA_DIR;
    else if (luzDir == BRANCO && luzEsq == PRETO)
      estado = CURVA_ESQ;
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

void andar(int esquerda, int direita){
  motor[motorEsq] = VELOCIDADE/esquerda;
  motor[motorDir] = VELOCIDADE/direita;

  wait1Msec(500);
}

void curva(char sentido){
  if(sentido == 'D'){
    andar(1,2);
    nxtDisplayString(2,sentido);
  }
  else if(sentido == 'E'){
    nxtDisplayString(2,sentido);
    andar(2,1);
  }
}

void emFrente(){
  andar(1,1);
}

void stopAllMotors(){
  motor[motorA] = 0;
  motor[motorB] = 0;
  wait1Msec(50);
}
