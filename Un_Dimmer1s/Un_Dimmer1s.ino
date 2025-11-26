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
                        PLACA 2
  ----------------------------------------------------
    Resist  |  PD_R-2  PCZ-39          |  si |    | si |
  ----------------------------------------------------
*/

//Para hacer los delays con millis()
unsigned long Time_actual = 0;

////////[CONTADOR DE MUESTREO]////////
unsigned long Time_previo_4 = 0;
const unsigned long valor_1_sg = 1000;  //Periodo_muestreo de 1 segundo

const int Pzc = 39;   //13;   //MOC 425
const int Pd = 2;     //11;    //MOC 3021
float Pot;
int valor;

#include <GyverDimmer.h>
DimmerBres<Pd> dim;

void setup() {
  attachInterrupt(Pzc, isr, RISING);
  Serial.begin(115200); // Inicializa la comunicación serial para monitorear
}

void isr() {
  dim.tick();
}

void loop() {
  // 0-255
  Time_actual = millis();

  if (Time_actual - Time_previo_4 >= valor_1_sg) {
    Time_previo_4 += valor_1_sg;

    int cv = 55;

    cv = constrain(cv, 0, 100);   //salida maxima sera el 30%
    Pot = cv;   //Asignacion a la entrada de la planta.

    valor = map(Pot, 0, 100, 0 , 255 );

    Serial.print("PWM: ");
    Serial.println(valor);

    dim.write(valor);

  }
}
