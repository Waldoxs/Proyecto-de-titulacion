TaskHandle_t Tarea3;
TaskHandle_t Tarea4;
TaskHandle_t Tarea5;

/* NOTAS DE FREERTOS
  Prioridad  Descripción
  0          Prioridad más baja
  1          Prioridad baja
  2          Prioridad media
  3          Prioridad alta
  4          Prioridad más alta
*/

/////////////[DIMMER AC]////////////
DimmerBresMulti<3> dim;

////////[Memoria EEPROM]////////
Preferences preferences;

////////[BME680]////////
Bsec iaqSensor;

////////[NEOPIXEL]////////
Adafruit_NeoPixel pixels(1, 48, NEO_GRB + NEO_KHZ800);

////////[Telegram Notificaciones]////////               [No modificar]
unsigned long Time_actual2 = 0;
static unsigned long ultimaNotificacion = 0; // Guarda el tiempo de la última notificación
unsigned long valor_N_time = 3600000;  //Periodo_muestreo de n_tiempo
//[ESPERA]
unsigned long Time_previo_Espera = 0;
unsigned long Time_actual_Espera = 0;
const unsigned long valor_Espera = 1000 * 60 * 30;

////////[CONTADOR DIAS Y HORAS]////////               [No modificar]
unsigned long Time_actual3 = 0;
unsigned long Time_previo_3 = 0;

const unsigned long valor_1_hr = 3600000;  //Periodo_muestreo de 1 hora
unsigned int dias;
unsigned int horas;

////////[CONTADOR PARA AJUSTE_EXTRA Y AJUSTE_PV]////////                   [No modificar]
//[EXTRA]
unsigned long Time_previo_4 = 0;
unsigned long Time_actual4 = 0;
//[PV]
unsigned long Time_previo_5 = 0;
unsigned long Time_actual5 = 0;

const unsigned long valor_1_sg = 1000;

////////[CONTADOR DIAS FRUCTIFICACIÓN Y HORAS ON/OFF]////////                   [Si modificar]
unsigned int dias_Fructificacion = 15;
volatile bool estadoFocos = false;

////////[CONTADOR DE BOMBA]////////                   [Si modificar]
unsigned long tiempoEncendido_Bomba = 1000 * 4;     //4 segundos
unsigned long tiempoApagado_Bomba = 1000 * 60 * 480; //1000 * 60 * 15;  //15  minutos
unsigned long tiempoAntes_Bomba = 0;
volatile bool estadoBomba = false;

////////[CONTADOR EXTRACTOR 1]////////                [Si modificar]
unsigned long tiempoEncendido_Trabajo = 1000 * 15;    //1000 * 60 * 2;  //2 minutos
unsigned long tiempoApagado_Trabajo = 1000 * 60 * 6; //1000 * 60 * 2;    // minutos
unsigned long tiempoAntes_Trabajo = 0;
volatile bool estado_Trabajo = false;

///////[CONTADOR RESISTENCIA]////////                [Si modificar, No operando]
unsigned long tiempoEncendido_Trabajo_R = 1000 * 60 * 2;
unsigned long tiempoApagado_Trabajo_R = 1000 * 60 * 2;
unsigned long tiempoAntes_Trabajo_R = 0;
volatile bool estado_Trabajo_R = false;

////////[VARIABLES para TELEGRAM]////////             [No modificar]
//Banderas de notificaciones nftS -> notificationSent
bool nftS_Dias1 = false;
bool nftS_Dias2 = false;

bool nftS_Horas1 = false;
bool nftS_Horas2 = false;

////////[SETPOINTS VARIABLES A MEDIR]////////         [Si modificar]
float sp_T;
float sp_H;
float sp_G;

float rango_H = 4.5;   //sp_H +- rango   USO EN EXTR1[+] y BOMBA [-]
float rango_T = 3.5;   //sp_H +- rango   USO EN EXTR1[+]   //3.0
float rango_G = 70.0;  //sp_H +- rango   USO EN EXTR1[+]
//salidas minimas y maximas
int val_min_Resis = 5; 
int val_max_Resis = 20; 
int val_min_HTG = 85; //posible 95 para extractor
int val_max_HTG = 100;

/////////////////////////////////////////CONTROLADORES//////////////////////////////////////////////////////////////////////////////

/////////////[LC_PI_Temperatura (RESISTENCIA) ]////////////   [Si modificar solo Ganancias]
int valor_1 = 0;
float Pot_Resis = 0;

float cv_Resis;
float cv1_Resis;
float error_Resis;
float error1_Resis;
float error2_Resis; //PID
float Tm_Resis = valor_1_sg / 1000.0;//1.0

/*  Kp = Kc | Ki = Kc/Tao_i | Kd = Kc(Td)  */
float Kp_Resis = 13.6106;  //0.37804;  //281.472
float Ki_Resis = 0.61672;  //0.00067; //0.01419
float Kd_Resis = 7.517;    //3.7884;

/////////////[LC_PI_EXTRACTOR_ENTRA_AIRE]////////////         [Si modificar solo Ganancias]

///////////////////////////////////////[HUMEDAD]///////////////////////////////////////

int valor_2 = 0;
float Pot_Hum = 0;

float cv_Hum;
float cv1_Hum;
float error_Hum;
float error1_Hum;
float error2_Hum; //PID
float Tm_Hum = valor_1_sg / 1000.0;//1.0

/*  Kp = Kc | Ki = Kc/Tao_i | Kd = Kc(Td)  */
float Kp_Hum = 2.8;
float Ki_Hum = 4.6;
float Kd_Hum = 2.2;

///////////////////////////////////////[TEMPERATURA]///////////////////////////////////////

int valor_3 = 0;
float Pot_Temp = 0;

float cv_Temp;
float cv1_Temp;
float error_Temp;
float error1_Temp;
float error2_Temp; //PID
float Tm_Temp = valor_1_sg / 1000.0;//1.0

/*  Kp = Kc | Ki = Kc/Tao_i | Kd = Kc(Td)  */
float Kp_Temp = 51.6 ;
float Ki_Temp = 17.5;
float Kd_Temp = 22.4;

///////////////////////////////////////[CO2]///////////////////////////////////////

int valor_4 = 0;
float Pot_CO2 = 0;

float cv_CO2;
float cv1_CO2;
float error_CO2;
float error1_CO2;
//float error2_CO2; PID
float Tm_CO2 = valor_1_sg / 1000.0;//1.0

/*  Kp = Kc | Ki = Kc/Tao_i | Kd = Kc(Td)  */
float Kp_CO2 = 42.621;
float Ki_CO2 = 4.627;
//float Kd_CO2 = 0.0;

////////////////////////////////////////////////////////////////////////////////////////FIN////////////////////////////////////////////////////////

////////[INTERRUPCIONES EXTERNAS]////////                       [Si modificar]
//Pines de control AC
const int Pd_Resis = 11;    //Resistencia
const int Pd_Ext1 = 12;     //Extractor 1
const int Pd_Bomba = 15;    //Bomba

//Pines de interrupciones AC
const int Pzc = 13;         // Pin de cruce por cero

////////[BOMBA ON/OFF POTENCIA REGULADA]////////                [Si modificar]
int Pot_Bomba = 60; //55;         //Asignar [0-100%]

int valor_5 = 0;

////////[FOCO_A ON/OFF]////////          [Si modificar]
const int Pin_FocoA = 47;    //Focos paralelo

////////[VALORES DE FRUCTIFICACIÓN]////////                     [Si modificar EXCLUSIVAMENTE EN CASO DE SER NECESARIO]
float FRC_T = 24.0;
float FRC_H = 85.0;
float FRC_G = 2200.0;

////////[VALORES DE INCUBACIÓN]////////                     [Si modificar EXCLUSIVAMENTE EN CASO DE SER NECESARIO]
float INC_T = 28.0;
float INC_H = 65.0;
float INC_G = 1800.0;

////////[TIEMPO NOTIFICACIONES ALARMAS]////////                     [No modificar]
unsigned long Inicio_Time = millis();
unsigned long Time_actual_Alarma = 0;
const unsigned long valor_30_mins = 35 * 60 * 1000; //Periodo_muestreo de 35 mins

const unsigned long valor_5_mins = 30 * 60 * 1000; //Periodo_muestreo de 35 mins      //5 * 60 * 1000;  //Periodo_muestreo de 5 mins
//unsigned long time_2_ciclos = (tiempoApagado_Trabajo * 2) + (tiempoEncendido_Trabajo * 2); //Periodo_muestreo

//[EXCEL]
unsigned long Inicio_Time_Excel = millis();
unsigned long Time_actual_Excel = 0;
static unsigned long ultimoRegistro = 0; // Guarda el tiempo del ultimo registro
const unsigned long valor_10_mins = 10 * 60 * 1000; //Periodo_muestreo de 10 mins
const unsigned long valor_6_mins = 6 * 60 * 1000; //Periodo_muestreo de 6 mins

//[ALARMA][T]
static unsigned long ultimaAlarma_T_HH = 0; // Guarda el tiempo de la última notificación
static unsigned long ultimaAlarma_T_LL = 0; // Guarda el tiempo de la última notificación

//[ALARMA][H]
static unsigned long ultimaAlarma_H_HH = 0; // Guarda el tiempo de la última notificación
static unsigned long ultimaAlarma_H_LL = 0; // Guarda el tiempo de la última notificación

//[ALARMA][G]
static unsigned long ultimaAlarma_G = 0; // Guarda el tiempo de la última notificación

//[ALARMA][Resis]
static unsigned long ultimaAlarma_Resis = 0; // Guarda el tiempo de la última notificación

////////[VALORES DE RESPALDO]////////                     [No modificar]
int back_1;
int back_1_1;
int back_2;
int back_2_2;
int back_3;

unsigned long back_ExtrOn;
unsigned long back_ExtrOff;
unsigned long back_bOn;
unsigned long back_bOff;

////////[CHECK SENSOR]////////                     [No modificar]
String output;

///////[Wi-Fi]/////
unsigned long tiempoAnterior = 0;
const unsigned long intervaloReconexion = 5000; // Intervalo de 5 segundos

const char* ssid1 = "TP-Link_E358";
const char* password1 = "45920189";
const char* ssid2 = "HOME-ROOT";
const char* password2 = "QTE1Mjk0NjExYQ==1";
