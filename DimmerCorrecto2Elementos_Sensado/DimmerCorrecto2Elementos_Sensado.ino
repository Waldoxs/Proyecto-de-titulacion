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

////////[CONTADOR DE BOMBA]////////                   [Si modificar]
const unsigned long tiempoEncendido_Bomba = 1000 * 2; //2 segundos
const unsigned long tiempoApagado_Bomba = 1000 * 30;  //30 segundos
unsigned long tiempoAntes_Bomba = 0;
volatile bool estadoBomba = false;

const unsigned long tiempoEncendido_Trabajo = 1000 * 30;  //30 segundos
const unsigned long tiempoApagado_Trabajo = 1000 * 60;    //60 segundos
unsigned long tiempoAntes_Trabajo = 0;
volatile bool estado_Trabajo = false;

    int cv_1 = 17;  //Resistncia
    int cv_2 = 55;  //Bomba
    
////////[BME680]////////
#include "bsec.h"
Bsec iaqSensor;

#include <GyverDimmer.h>
DimmerBresMulti<2> dim;

#include "pruebas.h"

void isr() {
  dim.tick();
}

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serial para monitorear

  ////////[BME680]////////
  Wire.begin();

  iaqSensor.begin(BME68X_I2C_ADDR_HIGH, Wire);

  bsec_virtual_sensor_t sensorList[3] = {
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
  };
  iaqSensor.updateSubscription(sensorList, 3, BSEC_SAMPLE_RATE_LP);
  Serial.println(F("CO2 equivalent, comp temp[°C], comp humidity [%]"));

  /////////////[INTERRUPCIONES]////////////
  attachInterrupt(Pzc, isr, RISING);

  dim.attach(0, Pd_1);  //Resistencia
  dim.attach(1, Pd_2);  //Bomba
}

void loop() {
  Time_actual = millis();

  if (Time_actual - Time_previo_4 >= valor_1_sg) {
    Time_previo_4 += valor_1_sg;

    ajuste_Bomba();
  }
}
