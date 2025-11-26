/////////////[IMPRIMIR VALORES]////////////
void imprimir_MonitorSerie() {              //Salida de datos en monitor serial y asignación de setpoints en memoria EEPROM
  float Sensor_T = iaqSensor.temperature;
  float Sensor_H = iaqSensor.humidity;
  float Sensor_G = iaqSensor.co2Equivalent;

  String coma = F((" , ")), gradosC = F((" °C")), errorDe = F(("Error de: ")), porcentaje = F((" %")), gas_Uni = F((" PPM")), HORAS = F((" Hrs")), DIAS = F(("Dia: "));

  String string_T = String(sp_T, 2) + gradosC + coma;
  String string_H = String(sp_H, 2) + porcentaje + coma;
  String string_G = String(sp_G, 1) + gas_Uni + coma;

  String string_sT = String(Sensor_T, 2) + gradosC + coma;
  String string_sH = String(Sensor_H, 2) + porcentaje + coma;
  String string_sG = String(Sensor_G, 1) + gas_Uni + coma;

  String string_Day = DIAS + String(dias) + coma;
  String string_Hrs = String(horas) + HORAS;

  preferences.begin("my-app", false);
  //preferences.clear();

  Serial.print(string_T);
  Serial.print(string_sT);

  Serial.print(string_H);
  Serial.print(string_sH);

  Serial.print(string_G);
  Serial.print(string_sG);

  Serial.print(string_Day);

  Serial.print(string_Hrs);

  //  if (horas >= 24) {
  //    horas = 0;
  //    dias++;
  //  }

  ///////////
  //  Serial.print(", ");
  //  Serial.print(valor_5);      //Bomba
  //  Serial.print(", ");
  //
  //  Serial.print(Pot_Resis);    //Resistencia
  //  Serial.print(", ");
  //  Serial.print(valor_1);
  //  Serial.print(", ");
  //
  //  Serial.print(Pot_Hum);      //Extr1
  //  Serial.print(", ");
  //  Serial.print(valor_2);
  //  Serial.print(", ");
  //
  //  Serial.print(Pot_Temp);     //Extr1
  //  Serial.print(", ");
  //  Serial.print(valor_3);
  //  Serial.print(", ");
  //
  //  Serial.print(Pot_CO2);      //Extr1
  //  Serial.print(", ");
  //  Serial.print(valor_4);
  //
  Serial.print(", ");
  Serial.print(val_max_Resis);

  Serial.print(", ");
  Serial.print(String(Kp_Resis, 5));
  Serial.print(", ");
  Serial.print(String(Ki_Resis, 5));
  Serial.print(", ");
  Serial.print(String(Kd_Resis, 5));

  Serial.print(", ");
  Serial.print(FRC_T);
  Serial.print(", ");
  Serial.print(FRC_H);
  Serial.print(", ");
  Serial.print(FRC_G);

  Serial.print(", ");
  Serial.print(INC_T);
  Serial.print(", ");
  Serial.print(INC_H);
  Serial.print(", ");
  Serial.print(INC_G);

  Serial.print(", ");
  Serial.print(tiempoEncendido_Bomba);
  Serial.print(", ");
  Serial.print(tiempoApagado_Bomba);

  Serial.print(", ");
  Serial.print(tiempoEncendido_Trabajo);
  Serial.print(", ");
  Serial.print(tiempoApagado_Trabajo);

  Serial.print(", ");
  Serial.print(tiempoEncendido_Trabajo_R);
  Serial.print(", ");
  Serial.print(tiempoApagado_Trabajo_R);

  Serial.print(", ");
  Serial.print(valor_N_time);

  Serial.print(", ");
  Serial.print(back_1);
  Serial.print(", ");
  Serial.print(back_1_1);
  Serial.print(", ");
  Serial.print(back_2);
  Serial.print(", ");
  Serial.print(back_2_2);
  Serial.print(", ");
  Serial.print(back_3);

  Serial.print(", ");
  Serial.print(back_ExtrOn);
  Serial.print(", ");
  Serial.print(back_ExtrOff);
  Serial.print(", ");
  Serial.print(back_bOn);
  Serial.print(", ");
  Serial.print(back_bOff);


  Serial.print(", ");
  Serial.print(Pot_Bomba);
  Serial.print(", ");
  Serial.print(val_max_HTG);
  Serial.print(", ");
  Serial.print(val_min_HTG);
  Serial.print(", ");
  Serial.print(val_min_Resis);

  ///////////
  preferences.putUInt("days", dias);
  preferences.putUInt("hours", horas);

  preferences.putFloat("temperature", sp_T);
  preferences.putFloat("humidity", sp_H);
  preferences.putFloat("gases", sp_G);

  preferences.putUInt("Resis", val_max_Resis);
  preferences.putUInt("ResisMin", val_min_Resis);
  preferences.putUInt("potBomb", Pot_Bomba);
  preferences.putUInt("extrMin", val_min_HTG);
  preferences.putUInt("extrMax", val_max_HTG);

  preferences.putFloat("kpResis", Kp_Resis);
  preferences.putFloat("kiResis", Ki_Resis);
  preferences.putFloat("kdResis", Kd_Resis);

  preferences.putUInt("d_frc", dias_Fructificacion);
  preferences.putFloat("frcT", FRC_T);
  preferences.putFloat("frcH", FRC_H);
  preferences.putFloat("frcG", FRC_G);

  preferences.putFloat("incT", INC_T);
  preferences.putFloat("incH", INC_H);
  preferences.putFloat("incG", INC_G);

  preferences.putULong("OnBomba", tiempoEncendido_Bomba);
  preferences.putULong("OffBomba", tiempoApagado_Bomba);

  preferences.putULong("OnExt", tiempoEncendido_Trabajo);
  preferences.putULong("OffExt", tiempoApagado_Trabajo);

  preferences.putULong("OnRes", tiempoEncendido_Trabajo_R);
  preferences.putULong("OffRes", tiempoApagado_Trabajo_R);

  preferences.putULong("nTime", valor_N_time);

  //Backup

  preferences.putUInt("b1", back_1);
  preferences.putUInt("b11", back_1_1);
  preferences.putUInt("b2", back_2);
  preferences.putUInt("b22", back_2_2);
  preferences.putUInt("b3", back_3);

  preferences.putULong("bExtOn", back_ExtrOn);
  preferences.putULong("bExtOff", back_ExtrOff);
  preferences.putULong("bomOn", back_bOn);
  preferences.putULong("bomOff", back_bOff);

  //1ra opcion  Remove the counter key    //preferences.remove("days"); //Serial.println("days preference removed.");
  //2da opcion  Clear all preferences     //preferences.clear();        //Serial.println("All preferences cleared.");

  preferences.end();
  Serial.println();
}

void estatico_SPI_LCD() {              //Salida de datos estáticos en LCD 20x4
  lcd.setCursor(0, 0);
  lcd.print(F("sT:"));
  lcd.setCursor(8, 0);
  lcd.print(F("\337C"));

  lcd.setCursor(11, 0);
  lcd.print(F("T:"));
  lcd.setCursor(18, 0);
  lcd.print(F("\337C"));

  lcd.setCursor(0, 1);
  lcd.print(F("sHR:"));
  lcd.setCursor(9, 1);
  lcd.print(F("%"));

  lcd.setCursor(11, 1);
  lcd.print(F("HR:"));
  lcd.setCursor(19, 1);
  lcd.print(F("%"));

  lcd.setCursor(0, 2);
  lcd.print(F("sCO2:"));
  lcd.setCursor(11, 2);
  lcd.print(F("CO2:"));

  lcd.setCursor(0, 3);
  lcd.print(F("P:"));
  lcd.setCursor(4, 3);
  lcd.print(F("%"));

  lcd.setCursor(9, 3);
  lcd.print(F("D:"));
  lcd.setCursor(15, 3);
  lcd.print(F("H:"));
}

void imprimir_pantalla_LCD() {              //Salida de datos dinámicos en LCD 20x4

  lcd.setCursor(3, 0);
  lcd.print(sp_T);
  lcd.setCursor(13, 0);
  lcd.print(iaqSensor.temperature);

  lcd.setCursor(4, 1);
  lcd.print(sp_H);

  if (iaqSensor.humidity >= 100.0) {
    lcd.setCursor(14, 1);
    lcd.print(F("99.99"));
  } else if (iaqSensor.humidity < 100.0) {
    lcd.setCursor(14, 1);
    lcd.print(iaqSensor.humidity);
  }

  lcd.setCursor(5, 2);
  lcd.print(String(sp_G, 0));
  lcd.setCursor(15, 2);
  lcd.print(String(iaqSensor.co2Equivalent, 0));

  lcd.setCursor(2, 3);
  lcd.print(val_max_Resis);

  lcd.setCursor(11, 3);
  lcd.print("  ");
  lcd.setCursor(11, 3);
  lcd.print(dias);

  if (horas < 10) {
    lcd.setCursor(17, 3);
    lcd.print(F("  "));
    lcd.setCursor(17, 3);
    lcd.print(horas);
  }
  else {
    lcd.setCursor(17, 3);
    lcd.print(horas);
  }
}

void imprimir_WIFI() {              //Estado de la conexión
  long rssi = WiFi.RSSI();

  if (rssi >= -30.0) {          //Excelente señal
    lcd.setCursor(6, 3);
    lcd.print(F("A"));

  } else if (rssi >= -70.0) {   //Buena señal
    lcd.setCursor(6, 3);
    lcd.print(F("B"));

  } else if (rssi >= -80.0) {   //Débil señal
    lcd.setCursor(6, 3);
    lcd.print(F("C"));

  } else if (rssi >= -90.0) {   //Pobre señal
    lcd.setCursor(6, 3);
    lcd.print(F("D"));

  } else {
    lcd.setCursor(6, 3);        //Sin señal
    lcd.print(F("E"));
  }

  switch (WiFi.status()) {
    case 0:                       //Intentando conectar
      lcd.setCursor(7, 3);
      lcd.print(F("0"));
      break;
    case 1:                       //Wifi no disponible
      lcd.setCursor(7, 3);
      lcd.print(F("1"));
      break;
    case 2:                       //Escaneo completo
      lcd.setCursor(7, 3);
      lcd.print(F("2"));
      break;
    case 3:                       //Conectado
      lcd.setCursor(7, 3);
      lcd.print(F("3"));
      break;
    case 4:                       //Conexión fallida
      lcd.setCursor(7, 3);
      lcd.print(F("4"));
      break;
    case 5:                       //Conexión perdida
      lcd.setCursor(7, 5);
      lcd.print(F("5"));
      break;
    case 6:                       //Desconectado
      lcd.setCursor(7, 3);
      lcd.print(F("6"));
      break;
    default:                      //Sin referencia de conexión
      lcd.setCursor(7, 3);
      lcd.print(F("7"));
  }
}

void imprimir_Graficos() {              //Salidas para graficar y asignar valores en los textBox

  RemoteXY.txB_valspT = sp_T;
  RemoteXY.txB_T = iaqSensor.temperature;
  RemoteXY.xy_spT = sp_T;
  RemoteXY.xy_T = iaqSensor.temperature;

  RemoteXY.txB_valspH = sp_H;
  RemoteXY.txB_H = iaqSensor.humidity;
  RemoteXY.xy_spH = sp_H;
  RemoteXY.xy_H = iaqSensor.humidity;

  RemoteXY.txB_valspCO2 = sp_G;
  RemoteXY.txB_CO2 = iaqSensor.co2Equivalent;
  RemoteXY.xy_spCO2 = sp_G;
  RemoteXY.xy_CO2 = iaqSensor.co2Equivalent;

  RemoteXY.txB_Day = dias;

  RemoteXY.txB_Hours = horas;

  RemoteXY.txB_WIFI = WiFi.RSSI();

  if (WiFi.RSSI() >= -30.0) {           //Excelente señal
    RemoteXY.lvl_WIFI = WiFi.RSSI();
    RemoteXY.str_WIFI = 1;

  } else if (WiFi.RSSI() >= -70.0) {    //Buena señal
    RemoteXY.lvl_WIFI = WiFi.RSSI();
    RemoteXY.str_WIFI = 2;

  } else if (WiFi.RSSI() >= -80.0) {    //Débil señal
    RemoteXY.lvl_WIFI = WiFi.RSSI();
    RemoteXY.str_WIFI = 3;

  } else if (WiFi.RSSI() >= -90.0) {    //Pobre señal
    RemoteXY.lvl_WIFI = WiFi.RSSI();
    RemoteXY.str_WIFI = 4;

  } else {                              //Sin señal
    RemoteXY.lvl_WIFI = WiFi.RSSI();
    RemoteXY.str_WIFI = 5;
  }

}

void btn_Graficos() {              //Botones de asignación de variables y datos

  if (RemoteXY.btn_spT == 1) {
    sp_T = RemoteXY.txB_spT;

    if (sp_T >= 40.0) {
      sp_T = 40.0;
    } else if (sp_T <= 20.0) {
      sp_T = 20.0;
    }

    if (dias >= dias_Fructificacion) {
      FRC_T = sp_T ;
    } else {
      INC_T = sp_T ;
    }
  }

  if (RemoteXY.btn_spH == 1) {
    sp_H = RemoteXY.txB_spH;

    if (sp_H >= 95.0) {
      sp_H = 95.0;

    } else if (sp_H <= 50.0) {
      sp_H = 50.0;
    }

    if (dias >= dias_Fructificacion) {
      FRC_H = sp_H ;
    } else {
      INC_H = sp_H ;
    }
  }

  if (RemoteXY.btn_spCO2 == 1) {
    sp_G = RemoteXY.txB_spCO2;

    if (sp_G >= 3000.0) {
      sp_G = 3000.0;
    } else if (sp_G <= 600.0) {
      sp_G = 600.0;
    }

    if (dias >= dias_Fructificacion) {
      FRC_G = sp_G ;
    } else {
      INC_G = sp_G ;
    }
  }

  if (RemoteXY.btn_Day == 1) {
    // Reinicia los contadores de tiempo
    Time_actual3 = millis();
    Time_previo_3 = Time_actual3;

    Time_actual2 = millis();
    ultimaNotificacion = Time_actual2;

    dias = 0;
    dias = RemoteXY.txB_asigDay;
  }

  if (RemoteXY.btn_Hours == 1) {
    // Reinicia los contadores de tiempo
    Time_actual3 = millis();
    Time_previo_3 = Time_actual3;

    Time_actual2 = millis();
    ultimaNotificacion = Time_actual2;

    horas = 0;
    horas = RemoteXY.txB_asigHours;
  }

  if (RemoteXY.btn_ResXY == 1) {
    // Asigna el nuevo valor
    dias = 0;
    horas = 0;

    // Reinicia los contadores de tiempo
    Time_actual3 = millis();
    Time_previo_3 = Time_actual3;

    Time_actual2 = millis();
    ultimaNotificacion = Time_actual2;
  }

  if (RemoteXY.btn_Paro_XY == 1) {
    pixels.clear(); // Apaga todos los píxeles
    pixels.setPixelColor(1, pixels.Color(255, 0, 0)); // Establece el color del píxel a rojo (255, 0, 0)
    pixels.show();   // Envía los colores actualizados al hardware

    back_1 = val_max_Resis;
    back_1_1 = val_min_Resis;
    back_2 = val_min_HTG;
    back_2_2 = val_max_HTG;
    back_3 = Pot_Bomba;

    back_ExtrOn = tiempoEncendido_Trabajo;
    back_ExtrOff = tiempoApagado_Trabajo;
    back_bOn = tiempoEncendido_Bomba;
    back_bOff = tiempoApagado_Bomba;

    val_max_Resis = 0;
    val_min_Resis = 0;
    val_min_HTG = 0;
    val_max_HTG = 0;
    tiempoEncendido_Trabajo = 0;
    tiempoApagado_Trabajo = 0;

    Pot_Bomba = 0;
    tiempoEncendido_Bomba = 0;
    tiempoApagado_Bomba = 0;
  }

  if (RemoteXY.btn_Run_XY == 1) {
    pixels.clear(); // Apaga todos los píxeles
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.show();   // Envía los colores actualizados al hardware

    val_max_Resis = back_1;
    val_min_Resis = back_1_1;
    val_min_HTG = back_2;
    val_max_HTG = back_2_2;
    Pot_Bomba = back_3;

    tiempoEncendido_Trabajo = back_ExtrOn;
    tiempoApagado_Trabajo = back_ExtrOff;
    tiempoEncendido_Bomba = back_bOn;
    tiempoApagado_Bomba = back_bOff;
  }
}


//////////////////////[WIFI]//////////////////////
void Red_Inestable() {              //Cambio de red
  if (RemoteXY.btn_RstWIFI == 1) {

    Time_actual_Alarma = millis(); // Actualizar currentTime con el tiempo actual

    // Reinicia los contadores de tiempo
    Inicio_Time = Time_actual_Alarma;
    ultimaAlarma_T_HH = ultimaAlarma_T_LL = Time_actual_Alarma;
    ultimaAlarma_H_HH = ultimaAlarma_H_LL = Time_actual_Alarma;
    ultimaAlarma_G = Time_actual_Alarma;
    ultimaAlarma_Resis = Time_actual_Alarma;

    wm.resetSettings();
    wm.setConfigPortalBlocking(true);
    wm.setConfigPortalTimeout(90);

    if (wm.autoConnect("Monitoreo_Setas")) {
      Serial.println("Conectado a la red :)");
    }
    else {
      Serial.println("Configportal running");
    }
  }
}

//void Red_Reconectar() {
//  if (WiFi.status() != WL_CONNECTED) {
//    WiFi.begin(); // Intenta reconectar a la última red conocida
//  }
//}
//void Red_Reconectar() {
//  if (WiFi.status() != WL_CONNECTED) {
//    WiFi.begin(ssid, password); // Intenta reconectar a la última red conocida
//  }
//}

void Red_Reconectar() {
  unsigned long tiempoActual = millis();

  // Verifica si es necesario intentar reconectar cada intervalo definido
  if ((WiFi.status() != WL_CONNECTED || WiFi.RSSI() <= -90) && (tiempoActual - tiempoAnterior >= intervaloReconexion)) {
    tiempoAnterior = tiempoActual; // Actualiza el tiempo del último intento

    // Intentar conectar a la primera red
    WiFi.begin(ssid1, password1);
    if (WiFi.status() == WL_CONNECTED && WiFi.RSSI() > -90) {
      return; // Si se conecta correctamente y la señal es aceptable, detiene el proceso
    }

    // Si no se conecta o la señal sigue siendo débil, intenta la segunda red
    WiFi.begin(ssid2, password2);
    if (WiFi.status() == WL_CONNECTED && WiFi.RSSI() > -90) {
      return; // Si se conecta correctamente y la señal es aceptable, detiene el proceso
    }
  }
}
