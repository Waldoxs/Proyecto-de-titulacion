/*NOTA: Desconectar la fuente de alimentacion de 5v antes de realizar cualquier prueba*/
/////////////[PINES DE CONEXION]////////////////////
/*--------------------------------------------------
  Dispos  |       PINES               |3.3v | 5v | GND
  ----------------------------------------------------
  BME680  |   SDA-8    SCL-9          |  si |    | si |0X77 Conectado [si SDO esta conectado a GND = 0x76]
  ----------------------------------------------------
  Bomba   |  PD_B-15  PCZ-13          |  si |    | si |
  ----------------------------------------------------
  Resist  |  PD_R-11  PCZ-13          |  si |    | si |
  ----------------------------------------------------
  Ext1    |  PD_E1-12  PCZ-13         |  si |    | si |
  ----------------------------------------------------
  Foco_A  |  Pin_FA-47                |  si |    | si |
  ----------------------------------------------------
*/

//Para hacer los delays con millis()
unsigned long Time_actual = 0;

////////[CONTADOR DE MUESTREO]////////
unsigned long Time_previo_4 = 0;
const unsigned long valor_1_sg = 1000;  //Periodo_muestreo de 1 segundo

const int Pd_1 = 11;  //Resistencia
const int Pd_2 = 15;  //Bomba
const int Pzc = 13;

float Pot_1;
int valor_1;

float Pot_2;
int valor_2;

#include <GyverDimmer.h>
DimmerBresMulti<2> dim;

void setup() {

  attachInterrupt(Pzc, isr, RISING);  
  Serial.begin(115200); // Inicializa la comunicación serial para monitorear

  dim.attach(0, Pd_1);  //Resistencia
  dim.attach(1, Pd_2);  //Bomba
}

void isr() {
  dim.tick(); 
}

void loop() {
  Time_actual = millis();

  if (Time_actual - Time_previo_4 >= valor_1_sg) {
    Time_previo_4 += valor_1_sg;

    int cv_1 = 20;  //Resistencia
    int cv_2 = 55;  //Bomba

    cv_1 = constrain(cv_1, 0, 20);    //salida maxima sera el 12%
    cv_2 = constrain(cv_2, 0, 55);    //salida maxima sera el 80%

    Pot_1 = cv_1;   //Asignacion a la entrada de la planta.
    Pot_2 = cv_2;

    valor_1 = map(cv_1, 0, 100, 0 , 255 );
    valor_2 = map(cv_2, 0, 100, 0 , 255 );

    Serial.print("V1 pwm: ");
    Serial.print(valor_1);
    Serial.print(", V2 pwm: ");
    Serial.println(valor_2);

    dim.write(0, valor_1);
    dim.write(1, valor_2);

  }
}
