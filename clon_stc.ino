
const int pin_display_a = 6;
const int pin_display_b = 7;
const int pin_display_c = 2;
const int pin_display_d = A3;
const int pin_display_e = 0;
const int pin_display_f = 5;
const int pin_display_g = 3;
const int pin_display_status = 4;
const int pin_display_dig0 = A2;
const int pin_display_dig1 = 1;

const int pin_up = 8;
const int pin_down = 10;
const int pin_set = 9;

const int pin_ntc1 = A0;
const int pin_ntc2 = A1;

const int pin_out1 = A5;
const int pin_out2 = A4;

unsigned int dato =0;
unsigned long time;
unsigned int segundos = 0;

const float TPto1 = 0; //Temperatura en ºC punto 1
const float RPto1 = 32960; // Ohms en punto 1
const float TPto2 = 100; // Temp. punto 2
const float RPto2 = 674; // Ohms en punto 2
const float resistor = 10000; //El valor en ohmnios de la resistencia del termistor a 25ºC
const float voltage = 5; // El voltaje real en el punto 5Vcc de tu placa Arduino
const float K= 273.15; //Para pasar a grados Kelvin
const float e = 2.718281828459045; //Constante matemática 
const float B = log(RPto2/RPto1)/(1/(TPto2+K)-(1/(TPto1+K))); //Valor Beta de tu termistor
const float unodivr = 1/(resistor * pow(e,(-B/298.15))); //Con pow elevamos e al resultado

float T = 0; //Declaramos la variable Temperatura
float tmedia; //Variable para calcular media
int cnt; //temperatura media y contador
int grados, decimas; //Para ponerle coma al resultado (en español)
int sensorValue = 0; // Aquí almacenamos el valor del sensor

byte output_status = 0;

byte val_SP = 5;  //set point
byte val_HI = 4;  //histeresis
byte val_DL = 5;  //delay; tiempo minimo de permanencia de estado

void setup() {
  
  pinMode(pin_display_a, OUTPUT);
  pinMode(pin_display_b, OUTPUT);
  pinMode(pin_display_c, OUTPUT);
  pinMode(pin_display_d, OUTPUT);
  pinMode(pin_display_e, OUTPUT);
  pinMode(pin_display_f, OUTPUT);
  pinMode(pin_display_g, OUTPUT);
  pinMode(pin_display_status, OUTPUT);
  pinMode(pin_display_dig0, OUTPUT);
  pinMode(pin_display_dig1, OUTPUT);
  
  pinMode(pin_up, INPUT);
  pinMode(pin_down, INPUT);
  pinMode(pin_set, INPUT);
  
  pinMode(pin_out1, OUTPUT);
  pinMode(pin_out2, OUTPUT);
  
  output_status = 0;
  segundos = 60*(val_DL-1);
  time=millis();
}


void loop() { 
  
  /*
  en modo normal:
  -lee temperatura [c/2 seg]
    -actualiza salidas en concecuencia
  
  -si presiono por menos de 3 seg SET entra en modo programacion de SET POINT
  -si presiono por mas de 5 seg entro en modo programacion de todos los parametros
    
  
  */
  
  if (millis() - time >1000){
    segundos++;
    read_temp();
    
    byte new_status = output_status;
    if(grados <= val_SP){
      new_status = false;
    }
    else if( grados >= ( val_SP + val_HI ) ){
      new_status = true;
    }
    
    if( (new_status != output_status) &&  segundos > (60*val_DL)){
      output_status = new_status;
      if(output_status)
        digitalWrite(pin_out1, HIGH);
      else
        digitalWrite(pin_out1, LOW);
      
      segundos = 0;
    }
    time=millis();
  }
  update_display(grados);
}

void read_inputs(){
  if(digitalRead(pin_set)==HIGH)
    dato=0;
  else if(digitalRead(pin_up)==HIGH)
    dato++;
  else if(digitalRead(pin_down)==HIGH)
    dato--;
}

void update_display(int value){
   
  int decena = value / 10;
  int unidad = value - (decena*10);
      
  update_segment_pins(decena);
   digitalWrite(pin_display_dig1, HIGH);
   delayMicroseconds(3000);
   digitalWrite(pin_display_dig1, LOW);
             
   update_segment_pins(unidad);
   digitalWrite(pin_display_dig0, HIGH);
   delayMicroseconds(3000);
   digitalWrite(pin_display_dig0, LOW);
}

void update_segment_pins(int value){
  switch(value){
    case 0:
      digitalWrite(pin_display_a, HIGH);
      digitalWrite(pin_display_b, HIGH);
      digitalWrite(pin_display_c, HIGH);
      digitalWrite(pin_display_d, HIGH);
      digitalWrite(pin_display_e, HIGH);
      digitalWrite(pin_display_f, HIGH);
      digitalWrite(pin_display_g, LOW);
      break;
    case 1:
      digitalWrite(pin_display_a, LOW);
      digitalWrite(pin_display_b, HIGH);
      digitalWrite(pin_display_c, HIGH);
      digitalWrite(pin_display_d, LOW);
      digitalWrite(pin_display_e, LOW);
      digitalWrite(pin_display_f, LOW);
      digitalWrite(pin_display_g, LOW);
      break;
    case 2:
      digitalWrite(pin_display_a, HIGH);
      digitalWrite(pin_display_b, HIGH);
      digitalWrite(pin_display_c, LOW);
      digitalWrite(pin_display_d, HIGH);
      digitalWrite(pin_display_e, HIGH);
      digitalWrite(pin_display_f, LOW);
      digitalWrite(pin_display_g, HIGH);
      break;
    case 3:
      digitalWrite(pin_display_a, HIGH);
      digitalWrite(pin_display_b, HIGH);
      digitalWrite(pin_display_c, HIGH);
      digitalWrite(pin_display_d, HIGH);
      digitalWrite(pin_display_e, LOW);
      digitalWrite(pin_display_f, LOW);
      digitalWrite(pin_display_g, HIGH);
      break;
    case 4:
      digitalWrite(pin_display_a, LOW);
      digitalWrite(pin_display_b, HIGH);
      digitalWrite(pin_display_c, HIGH);
      digitalWrite(pin_display_d, LOW);
      digitalWrite(pin_display_e, LOW);
      digitalWrite(pin_display_f, HIGH);
      digitalWrite(pin_display_g, HIGH);
      break;
    case 5:
      digitalWrite(pin_display_a, HIGH);
      digitalWrite(pin_display_b, LOW);
      digitalWrite(pin_display_c, HIGH);
      digitalWrite(pin_display_d, HIGH);
      digitalWrite(pin_display_e, LOW);
      digitalWrite(pin_display_f, HIGH);
      digitalWrite(pin_display_g, HIGH);
      break;
    case 6:
      digitalWrite(pin_display_a, HIGH);
      digitalWrite(pin_display_b, LOW);
      digitalWrite(pin_display_c, HIGH);
      digitalWrite(pin_display_d, HIGH);
      digitalWrite(pin_display_e, HIGH);
      digitalWrite(pin_display_f, HIGH);
      digitalWrite(pin_display_g, HIGH);
      break;
    case 7:
      digitalWrite(pin_display_a, HIGH);
      digitalWrite(pin_display_b, HIGH);
      digitalWrite(pin_display_c, HIGH);
      digitalWrite(pin_display_d, LOW);
      digitalWrite(pin_display_e, LOW);
      digitalWrite(pin_display_f, LOW);
      digitalWrite(pin_display_g, LOW);
      break;
    case 8:
      digitalWrite(pin_display_a, HIGH);
      digitalWrite(pin_display_b, HIGH);
      digitalWrite(pin_display_c, HIGH);
      digitalWrite(pin_display_d, HIGH);
      digitalWrite(pin_display_e, HIGH);
      digitalWrite(pin_display_f, HIGH);
      digitalWrite(pin_display_g, HIGH);
      break;
    case 9:
      digitalWrite(pin_display_a, HIGH);
      digitalWrite(pin_display_b, HIGH);
      digitalWrite(pin_display_c, HIGH);
      digitalWrite(pin_display_d, HIGH);
      digitalWrite(pin_display_e, LOW);
      digitalWrite(pin_display_f, HIGH);
      digitalWrite(pin_display_g, HIGH);
      break;
  }
}

void read_temp(){
   
  tmedia=0;
  for ( cnt=0; cnt<5; cnt++)
  {
    sensorValue = analogRead(pin_ntc1);
    tmedia=tmedia+sensorValue;
    //delay(5);
    update_display(grados);
  }
  tmedia=tmedia/cnt; 
  
  float v2 = (voltage*float(tmedia))/1024.0f;
  float r1a = (voltage*float(resistor))/v2;  
  float r1 =r1a - resistor;

  float T = B/log(r1*unodivr);
  T= T-273.15;
  
  grados=(int)T;
  decimas=(T-grados)*10;
}

