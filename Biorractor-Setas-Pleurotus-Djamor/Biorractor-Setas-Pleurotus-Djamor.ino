/////////////[PINES DE CONEXION]////////////////////
/*--------------------------------------------------
  Dispos  |       PINES               |3.3v | 5v | GND
  ----------------------------------------------------
  AHT_10  |   SDA-8    SCL-9          |  si |    | si |0X38 o 0x39 No conectado
  ----------------------------------------------------
  BME680  |   SDA-8    SCL-9          |  si |    | si |0X77 Conectado [si SDO esta conectado a GND = 0x76]
  ----------------------------------------------------
  SPI_OLED|SDA-13;SCK-18;DC-12;REST-14|  si |    | si |No conectado
  ----------------------------------------------------
  I2C_LCD |   SDA-8    SCL-9          |     | si | si |0X27 conectado
  ----------------------------------------------------
  Bomba   |  PD_B-15  PCZ-13          |  si |    | si |Conectado
  ----------------------------------------------------
  Resist  |  PD_R-11  PCZ-13          |  si |    | si |Conectado
  ----------------------------------------------------
  Ext1    |  PD_E1-12  PCZ-13         |  si |    | si |Conectado
  ----------------------------------------------------
  Ext2*   |  PD_E2-XX  PCZ-13         |  si |    | si |No conectado [PENDIENTE]
  ----------------------------------------------------
  Foco_A  |  Pin_FA-47                |  si |    | si |Conectado
  ----------------------------------------------------
*/

#include "librerias.h"

void isr() {
  dim.tick();
}

void setup() {
  Serial.begin(115200);
  xTaskCreatePinnedToCore(Cuenta_Dias, "Tarea3", 8192 , NULL, 1, NULL, 1);  // Core 1
  xTaskCreatePinnedToCore(Ajuste_Extras, "Tarea4", 8192 , NULL, 1, NULL, 1);  // Core 1
  xTaskCreatePinnedToCore(Ajuste_PV, "Tarea5", 8192 , NULL, 1, NULL, 1);  // Core 1

  ////////[Memoria EEPROM]////////
  preferences.begin("my-app", false);

  dias = preferences.getUInt("days", 0);
  horas = preferences.getUInt("hours", 0);

  sp_T = preferences.getFloat("temperature", 0);
  sp_H = preferences.getFloat("humidity", 0);
  sp_G = preferences.getFloat("gases", 0);

  val_max_Resis = preferences.getUInt("Resis", val_max_Resis);
  val_min_Resis = preferences.getUInt("ResisMin", val_min_Resis);
  Pot_Bomba = preferences.getUInt("potBomb", Pot_Bomba);
  val_min_HTG = preferences.getUInt("extrMin", val_min_HTG);
  val_max_HTG = preferences.getUInt("extrMax", val_max_HTG);

  Kp_Resis = preferences.getFloat("kpResis", Kp_Resis);
  Ki_Resis = preferences.getFloat("kiResis", Ki_Resis);
  Kd_Resis = preferences.getFloat("kdResis", Kd_Resis);

  dias_Fructificacion = preferences.getUInt("d_frc", dias_Fructificacion);
  FRC_T = preferences.getFloat("frcT", FRC_T);
  FRC_H = preferences.getFloat("frcH", FRC_H);
  FRC_G = preferences.getFloat("frcG", FRC_G);

  INC_T = preferences.getFloat("incT", INC_T);
  INC_H = preferences.getFloat("incH", INC_H);
  INC_G = preferences.getFloat("incG", INC_G);

  tiempoEncendido_Bomba = preferences.getULong("OnBomba", tiempoEncendido_Bomba);
  tiempoApagado_Bomba = preferences.getULong("OffBomba", tiempoApagado_Bomba);

  tiempoEncendido_Trabajo = preferences.getULong("OnExt", tiempoEncendido_Trabajo);
  tiempoApagado_Trabajo = preferences.getULong("OffExt", tiempoApagado_Trabajo);

  tiempoEncendido_Trabajo_R = preferences.getULong("OnRes", tiempoEncendido_Trabajo_R);
  tiempoApagado_Trabajo_R = preferences.getULong("OffRes", tiempoApagado_Trabajo_R);

  valor_N_time = preferences.getULong("nTime", valor_N_time);

  //Backup
  back_1 = preferences.getUInt("b1", back_1);
  back_1_1 = preferences.getUInt("b11", back_1_1);
  back_2 = preferences.getUInt("b2", back_2);
  back_2_2 = preferences.getUInt("b22", back_2_2);
  back_3 = preferences.getUInt("b3", back_3);

  back_ExtrOn = preferences.getULong("bExtOn", back_ExtrOn);
  back_ExtrOff = preferences.getULong("bExtOff", back_ExtrOff);
  back_bOn = preferences.getULong("bomOn", back_bOn);
  back_bOff = preferences.getULong("bomOff", back_bOff);

  Serial.print(F("Setpoint Dia: "));
  Serial.println(dias);
  Serial.print(F("Setpoint hora: "));
  Serial.println(horas);
  Serial.print(F("Setpoint T: "));
  Serial.println(sp_T);
  Serial.print(F("Setpoint H: "));
  Serial.println(sp_H);
  Serial.print(F("Setpoint G: "));
  Serial.println(String(sp_G, 1));

  preferences.end();

  ////////[Wifi Manager]////////
  WiFi.mode(WIFI_STA);
  //wm.resetSettings();// ACTIVAR AL ULTIMO PARA HACER PRUEBAS FINALES CON REDES DE WIFI

  wm.setConfigPortalBlocking(true); // Configurar el portal de configuración como no bloqueante
  //wm.setConfigPortalBlocking(false);
  wm.setConfigPortalTimeout(90); // Establecer el tiempo de espera del portal de configuración a 5 mins

  if (wm.autoConnect("Monitoreo_Setas")) {
    Serial.println("Conectado a la red :)");
  }
  else {
    Serial.println("Configportal running");
  }

  ////////[BME680]////////
  iaqSensor.begin(BME68X_I2C_ADDR_HIGH, Wire);

  bsec_virtual_sensor_t sensorList[3] = {
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
  };
  iaqSensor.updateSubscription(sensorList, 3, BSEC_SAMPLE_RATE_LP);

  Serial.println(F("CO2 equivalent, comp temp[°C], comp humidity [%]"));

  ////////[Graficos]////////
  RemoteXY_Init();

  ////////[Pantalla SPI LCD]////////
  // Inicializa la comunicación I2C
  lcd.init();
  lcd.backlight();

  // Muestra un mensaje en el LCD
  lcd.setCursor(0, 0);
  lcd.print(F("LCD OK"));
  Serial.println(F("Inicializada Pantalla LCD"));

  ////////[Telegram Bot]////////
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Add root certificate for api.telegram.org

  /////////////[INTERRUPCIONES]////////////
  attachInterrupt(Pzc, isr, RISING);

  dim.attach(0, Pd_Resis);  //RESISTENCIA
  dim.attach(1, Pd_Ext1);   //MOTOR 1
  dim.attach(2, Pd_Bomba);  //BOMBA DE AGUA

  /////////////[FOCO AZUL]////////////
  pinMode(Pin_FocoA, OUTPUT);

  ////////[NEOPIXEL]////////
  pixels.begin(); // INICIALIZA el objeto NeoPixel
  pixels.setBrightness(180); // Ajusta el brillo (0-255)  //120

  estatico_SPI_LCD();
}

void loop() {                 // Salida a 3 segundos por el tiempo de respuesta del sensor para algunas variables como CO2
  wm.process();
  RemoteXY_Handler();

  if (iaqSensor.run()) { // If new data is available

    imprimir_MonitorSerie();      //Activar de ser necesario
    //imprimir_pantalla_LCD();    //LCD   //Activar de ser necesario
    //imprimir_WIFI();            //LCD   //Activar de ser necesario
    registroExcel();
    tele_Bot();
    imprimir_Graficos();  //RemoteXY
    Red_Reconectar();

  } else {
    verificar_Sensor();
  }
}

void Cuenta_Dias(void *parameter) {     //Salida a 1 hora
  while (1) {
    Time_actual3 = millis();

    if (Time_actual3 - Time_previo_3 >= valor_1_hr) {
      Time_previo_3 += valor_1_hr;
      horas++;
      //Mostrar horas

      if (horas >= 24) {
        horas = 0;
        dias++;
        //Mostrar dias
      }
    }
    vTaskDelay(100  / portTICK_PERIOD_MS);
  }
}

void Ajuste_Extras(void *parameter) {  //Salida a 1 segundo
  while (1) {
    Time_actual4 = millis();

    if (Time_actual4 - Time_previo_4 >= valor_1_sg) {
      Time_previo_4 += valor_1_sg;

      time_FOCO_A();        //RemoteXY
      Etapas();             //Incubación/Fructificación
      btn_Graficos();       //RemoteXY
      Red_Inestable();      //RemoteXY
    }
    vTaskDelay(100  / portTICK_PERIOD_MS);
  }
}

void Ajuste_PV(void *parameter) {  //Salida a 1 segundo
  while (1) {
    Time_actual5 = millis();

    if (Time_actual5 - Time_previo_5 >= valor_1_sg) {
      Time_previo_5 += valor_1_sg;

      time_Trabajo_Resis();
      time_Trabajo_Ext1();
      //rociar_general();
      //ajuste_Bomba();
      ajuste_Bomba2();

    }
    vTaskDelay(100  / portTICK_PERIOD_MS);
  }
}
