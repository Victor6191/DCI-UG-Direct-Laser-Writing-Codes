#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_MotorShield AFMS2(0x61);
Adafruit_MotorShield AFMS1(0x60);
Adafruit_StepperMotor *Motorx = AFMS1.getStepper(200,1);
Adafruit_StepperMotor *Motory = AFMS1.getStepper(200,2);
Adafruit_StepperMotor *Motorz = AFMS2.getStepper(200,2);
Adafruit_StepperMotor *Motorshoot = AFMS2.getStepper(200,1);

void forwardstep1() {  
  Motorx->onestep(FORWARD,MICROSTEP);
}
void backwardstep1() {  
  Motorx->onestep(BACKWARD,MICROSTEP);
}
// wrappers for the second motor!
void forwardstep2() {  
  Motory->onestep(FORWARD,MICROSTEP);
}
void backwardstep2() {  
  Motory->onestep(BACKWARD,MICROSTEP);
}

AccelStepper Motorx1(forwardstep1,backwardstep1);
AccelStepper Motory1(forwardstep2,backwardstep2);

char val; // Determines which action is gone to happen
char _stop; //Stop any movement
byte vel; //Char releated to general speed
byte ste[5]; //Char related to general no. steps

int _speed = 12;    // initial speed and no. steps
long int steps = 80;  // Can change with correct entries
byte lensteparray;
int l; 

//Variables for lines method, use the general speed assign in master window
char nolin;    //Char related to number of lines
char separat;  //Char related to gap
byte leng;     //Char related to length of the lines
int nol;       //Number of lines
int sep;       //Gap between lines
byte leg[5];
int le;        //Length of lines
int len;
byte repeti;
int rep;

//Variables for horizontal lines method
char nolinho;    //Char related to number of lines
char separatho;  //Char related to gap
byte lengho;     //Char related to length of the lines
int nolho;       //Number of lines
int sepho;       //Gap between lines
byte legho[5];
int leho;        //Length of lines
int lenho;
byte repetiho;
int repho;

//Variables for square method, use general speed assign in master window
byte side;
int sid;
byte si[5];
int lsi;
byte repsq;
int rsq;

//Variables for rectangle method, use general speed assign in master window
byte widt;
int wid;
byte lengrect;
int lenrect;
byte wirec[5];
int wir;
byte lerect[5];
int ler;
byte reprect;
int repr;

// Variables for point method
byte hopoints;
int hopoi;
byte vepoints;
int vepoi;
byte timepoints;
int timepoi;
byte hpoin[5];
int hpo;
byte vpoin[5];
int vpo;
byte tpoin[6];
unsigned long tpo;
byte lehosep;
int lehos;
byte levesep;
int leves;
byte sephor[5];
int seph;
byte sepve[5];
int sepv;

//Flag for knowing if the shooter is open or close
bool shoot = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(28800);
  AFMS1.begin();
  AFMS2.begin();
  Motorshoot->setSpeed(255);
  Motorx1.setMaxSpeed(60.0);
  Motorx1.setAcceleration(5.0);
  //Motorx1.move(400);
  Motory1.setMaxSpeed(100.0);
  Motory1.setAcceleration(10.0);
  //Motory1.move(600);
}

void loop() {
  // put your main code here, to run repeatedly:
   //If case that determines which action or method is going to do
   if(Serial.available()){
    val = Serial.read();
   }
  //Moving x motor inside platform
  if(val == '1'){
    for(int i=0;i<steps;i++){
      //Motorx->setSpeed(_speed);
      Motorx->step(1,FORWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
    }
    val = 0;
  }
  //Moving x moto outside platform
  if(val == '2'){
    for(int i=0;i<steps;i++){
      //Motorx->setSpeed(_speed);
      Motorx->step(1,BACKWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
    }
    val = 0;
  }
   if(val == '3'){
    for(int i=0;i<steps;i++){
      //Motory->setSpeed(_speed);
      Motory->step(1,FORWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
    }
    val = 0;
  }
  
   if(val == '4'){
    for(int i=0;i<steps;i++){
      //Motory->setSpeed(_speed);
      Motory->step(1,BACKWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
    }
    val = 0;
  }
  //Set general speed
  if(val == '5'){
   vel = Serial.parseInt();
   _speed = (int)vel;
   Motorx->setSpeed(_speed);
   Motory->setSpeed(_speed);
   Motorz->setSpeed(_speed);
   val = 0;
  }
  //Set general no. of steps
  if(val == '6'){
   /*ste = Serial.parseInt();
   steps = (int)ste;
   val = 0;*/
   lensteparray = Serial.parseInt();
   l = (int)lensteparray;
   steps = 0;
   for(int i=0;i<l;i++){
     ste[i] = Serial.parseInt();
     steps+= (int)ste[i]*pow(10,l-1-i);
   }
   steps+=1;
   val = 0;
  }
  //Moving z motor up
  if(val == '7'){
   for(int i=0;i<steps;i++){
      //Motorz->setSpeed(_speed);
      Motorz->step(1,FORWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
    }
    val = 0;
  }
  //Moving z motor down
  if(val == '8'){
   for(int i=0;i<steps;i++){
      //Motorz->setSpeed(_speed);
      Motorz->step(1,BACKWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
    }
    val = 0;
  }
  //Draw lines
  if(val == '9'){
    /*if(shoot != true){
    Motorshoot->step(65,BACKWARD,DOUBLE); 
    }*/
    nolin = Serial.parseInt();
    separat = Serial.parseInt();
    leng = Serial.parseInt();
    repeti = Serial.parseInt();
    nol = (int)nolin;
    sep = (int)separat;
    le = (int)leng;
    rep = (int)repeti;
    len = 0;
    for(int k=0;k<le;k++){
     leg[k] = Serial.parseInt();
     len+= (int)leg[k]*pow(10,le-1-k);
    }
    len += 1;
    for(int j=0;j<nol;j++){
      for(int q=0;q<rep;q++){
      for(int i=0;i<len;i++){
      Motorx->setSpeed(_speed);
      Motorx->step(1,FORWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
     }
     Motorshoot->step(65,FORWARD,DOUBLE); 
     for(int i=0;i<len;i++){
      Motorx->setSpeed(255);
      Motorx->step(1,BACKWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
     }
     Motorshoot->step(65,BACKWARD,DOUBLE);
     }
     Motorshoot->step(65,FORWARD,DOUBLE);
     for(int i=0;i<sep;i++){
      Motory->setSpeed(_speed);
      Motory->step(1,BACKWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
     }
     Motorshoot->step(65,BACKWARD,DOUBLE); 
     Motorx->setSpeed(_speed);
   }
   Motorshoot->step(65,FORWARD,DOUBLE); 
   Motorx->setSpeed(_speed);
   shoot = false;
   val = 0;
  }
  //Draw square
  if(val == 'a'){
    side = Serial.parseInt();
    repsq = Serial.parseInt();
    sid = (int)side;
    rsq = (int)repsq;
    lsi = 0;
    for(int i=0;i<sid;i++){
      si[i] = Serial.parseInt();
      lsi+= (int)si[i]*pow(10,sid-1-i);
    }
    lsi+=1;
    for(int q=0;q<rsq;q++){
    for(int i=0;i<lsi;i++){
      //Motorx->setSpeed(_speed);
      Motorx->step(1,FORWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
    }
    for(int i=0;i<lsi;i++){
      //Motory->setSpeed(_speed);
      Motory->step(1,BACKWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
   }
   for(int i=0;i<lsi;i++){
      //Motorx->setSpeed(_speed);
      Motorx->step(1,BACKWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
   }
   for(int i=0;i<lsi;i++){
      //Motory->setSpeed(_speed);
      Motory->step(1,FORWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
   }
   }
   Motorshoot->step(65,FORWARD,DOUBLE); 
   shoot = false;
   val = 0;
 }
 //Draw rect
 if(val == 'b'){
    widt = Serial.parseInt();
    lengrect = Serial.parseInt();
    reprect = Serial.parseInt();
    wid = (int)widt;
    lenrect = (int)lengrect;
    repr = (int)reprect;
    wir = 0;
    ler = 0;
    for(int q=0;q<wid;q++){
      wirec[q] = Serial.parseInt();
      wir+= (int)wirec[q]*pow(10,wid-1-q);
    }
    for(int w=0;w<lenrect;w++){
      lerect[w] = Serial.parseInt();
      ler+= (int)lerect[w]*pow(10,lenrect-1-w);
    }
    wir+=1;
    ler+=1;
    for(int p=0;p<repr;p++){
    for(int i=0;i<wir;i++){
      //Motorx->setSpeed(_speed);
      Motorx->step(1,FORWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
    }
    for(int i=0;i<ler;i++){
      //Motory->setSpeed(_speed);
      Motory->step(1,BACKWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
   }
   for(int i=0;i<wir;i++){
      //Motorx->setSpeed(_speed);
      Motorx->step(1,BACKWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
   }
   for(int i=0;i<ler;i++){
      //Motory->setSpeed(_speed);
      Motory->step(1,FORWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
   }
   }
    Motorshoot->step(65,FORWARD,DOUBLE); 
   shoot = false;
   val = 0;
 }

 //Close shooter
 if(val=='c'){
  if(shoot != false){
  Motorshoot->step(65,FORWARD,DOUBLE); 
  val = 0;
  shoot = false;
  }
 }

 //Open shooter
 if(val=='d'){
  if(shoot != true){
  Motorshoot->step(65,BACKWARD,DOUBLE); 
  val = 0;
  shoot = true;
  }
 }

//Draw horizontal lines
  if(val == 'e'){
    nolinho = Serial.parseInt();
    separatho = Serial.parseInt();
    lengho = Serial.parseInt();
    repetiho = Serial.parseInt();
    nolho = (int)nolinho;
    sepho = (int)separatho;
    leho = (int)lengho;
    repho = (int)repetiho;
    lenho = 0;
    for(int k=0;k<leho;k++){
     legho[k] = Serial.parseInt();
     lenho+= (int)legho[k]*pow(10,leho-1-k);
    }
    lenho += 1;
    for(int j=0;j<nolho;j++){
      for(int q=0;q<repho;q++){
      for(int i=0;i<lenho;i++){
      Motory->setSpeed(_speed);
      Motory->step(1,BACKWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
     }
     Motorshoot->step(65,FORWARD,DOUBLE); 
     for(int i=0;i<lenho;i++){
      Motory->setSpeed(255);
      Motory->step(1,FORWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
     }
     Motorshoot->step(65,BACKWARD,DOUBLE);
      }
      Motorshoot->step(65,FORWARD,DOUBLE);
     for(int i=0;i<sepho;i++){
      Motorx->setSpeed(_speed);
      Motorx->step(1,BACKWARD,MICROSTEP); 
      _stop = Serial.read();
      if(_stop == '0'){
        break;
      }
     }
     Motorshoot->step(65,BACKWARD,DOUBLE); 
     Motory->setSpeed(_speed);
   }
   Motorshoot->step(65,FORWARD,DOUBLE); 
   Motory->setSpeed(_speed);
   shoot = false;
   val = 0;
  }

//Points method
  if(val == 'f')
  {
    hopoints = Serial.parseInt();
    vepoints = Serial.parseInt();
    timepoints = Serial.parseInt();
    lehosep = Serial.parseInt();
    levesep = Serial.parseInt();
    hopoi = (int)hopoints;
    vepoi = (int)vepoints;
    timepoi = (int)timepoints;
    lehos = (int)lehosep;
    leves = (int)levesep;
    hpo = 0;
    vpo = 0;
    tpo = 0;
    seph = 0;
    sepv = 0;
    for(int q=0;q<hopoi;q++){
      hpoin[q] = Serial.parseInt();
      hpo+= (int)hpoin[q]*pow(10,hopoi-1-q);
    }
    for(int w=0;w<vepoi;w++){
      vpoin[w] = Serial.parseInt();
      vpo+= (int)vpoin[w]*pow(10,vepoi-1-w);
    }
    for(int t=0;t<timepoi;t++){
      tpoin[t] = Serial.parseInt();
      tpo+= (int)tpoin[t]*pow(10,timepoi-1-t);
    }
    for(int y=0;y<lehos;y++){
      sephor[y] = Serial.parseInt();
      seph+= (int)sephor[y]*pow(10,lehos-1-y);
    }
    for(int x=0;x<leves;x++){
      sepve[x] = Serial.parseInt();
      sepv+= (int)sepve[x]*pow(10,leves-1-x);
    }
    hpo+=1;
    vpo+=1;
    tpo+=1;
    seph+=1;
    sepv+=1;

    for(int j=0;j<vpo;j++){ 
      for(int i=0;i<hpo;i++){
        if(shoot != true){
           Motorshoot->step(65,BACKWARD,DOUBLE);
        }
        delay(tpo);
        Motorshoot->step(65,FORWARD,DOUBLE);
        Motory->setSpeed(255);
        Motory->step(seph,BACKWARD,MICROSTEP); 
      }
      Motorshoot->step(65,FORWARD,DOUBLE);
      Motory->step((hopoi+1)*seph,FORWARD,MICROSTEP);
      Motorx->setSpeed(255);
      Motorx->step(sepv,FORWARD,MICROSTEP);
      //Motorshoot->step(65,BACKWARD,DOUBLE); 
    }
    Motorx->setSpeed(_speed);
    Motory->setSpeed(_speed);
    Motorshoot->step(65,FORWARD,DOUBLE);
    shoot = false;
    val = 0;
  }
  if(val == 'g')
  {
    /*Motorx1.runToPosition();
    Motory1.runToPosition();
    Motorx1.setCurrentPosition(0);
    Motory1.setCurrentPosition(0);
    val = 0;
    Motorx1.setMaxSpeed(60.0);
    Motorx1.setAcceleration(5.0);
    Motorx1.move(400);  
    Motory1.setMaxSpeed(100.0);
    Motory1.setAcceleration(10.0);
    Motory1.move(600);*/ //se mueve secuencial
    while (!Motorx1.run() || !Motory1.run()){
      Motorx1.moveTo(100);
      Motory1.moveTo(240);
    }
    Motorx1.setCurrentPosition(0);
    Motory1.setCurrentPosition(0);
    Motorx1.moveTo(0);
    Motory1.moveTo(0);
    
  }
  
}
