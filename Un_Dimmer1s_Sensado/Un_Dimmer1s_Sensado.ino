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

////////[BME680]////////
#include "bsec.h"

////////[BME680]////////
Bsec iaqSensor;

//Para hacer los delays con millis()
unsigned long Time_actual = 0;

////////[CONTADOR DE MUESTREO]////////
unsigned long Time_previo_4 = 0;
const unsigned long valor_1_sg = 1000;  //Periodo_muestreo de 1 segundo

const int Pzc = 13;
const int Pd = 11;
float Pot;
int valor;

#include <GyverDimmer.h>
DimmerBres<Pd> dim;

void setup() {
  attachInterrupt(Pzc, isr, RISING);
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

delay(10000);
}

void isr() {
  dim.tick();
}

void loop() {
  // 0-255
  Time_actual = millis();
  iaqSensor.run();

  if (Time_actual - Time_previo_4 >= valor_1_sg) {
    Time_previo_4 += valor_1_sg;

    int cv = 40;// min 95   97

    cv = constrain(cv, 0, 40);   //salida maxima sera el 30%
    Pot = cv;   //Asignacion a la entrada de la planta.

    valor = map(Pot, 0, 100, 0 , 255 );
    
    Serial.print("PWM: ");
    Serial.print(valor);
    Serial.print(" ,T: ");
    Serial.print(iaqSensor.temperature);
    Serial.print(" ,HR: ");
    Serial.println(iaqSensor.humidity);

    dim.write(valor);

  }
}
