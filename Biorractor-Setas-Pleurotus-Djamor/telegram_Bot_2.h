void ntf_Dias() {
  // Llama a la función para verificar y enviar la notificación
  unsigned int ref_Dias1 = 0;
  unsigned int ref_Dias2 = dias_Fructificacion;

  if (dias == ref_Dias1 && !nftS_Dias1) {
    String message = "Día: " + String(dias) + ", inicia la incubación.";
    bot.sendMessage(CHAT_ID_1, message);
    bot.sendMessage(CHAT_ID_2, message);
    nftS_Dias1 = true; // Marca la notificación como enviada
  }
  // Restablece la bandera si el valor de la variable
  if (dias < ref_Dias1) {
    nftS_Dias1 = false;
  }

  if (dias == ref_Dias2 && !nftS_Dias2) {
    String message = "Día: " + String(dias) + ", ya inician los fotoperiodos.";
    bot.sendMessage(CHAT_ID_1, message);
    bot.sendMessage(CHAT_ID_2, message);
    nftS_Dias2 = true; // Marca la notificación como enviada
  }
  // Restablece la bandera si el valor de la variable
  if (dias < ref_Dias2) {
    nftS_Dias2 = false;
  }
}

void ntf_Horas() {
  // Llama a la función para verificar y enviar la notificación
  unsigned int ref_Horas1 = 8;
  unsigned int ref_Horas2 = 22;
  String message = "Recuerda rociar las bolsas de los micelios C; ";

  if (horas == ref_Horas1 && !nftS_Horas1) {    //if (horas >= ref_Horas1 && !nftS_Horas1) {
    bot.sendMessage(CHAT_ID_1, message);
    bot.sendMessage(CHAT_ID_2, message);
    nftS_Horas1 = true; // Marca la notificación como enviada
  }

  // Restablece la bandera si el valor de la variable vuelve a estar por debajo
  if (horas < ref_Horas1) {
    nftS_Horas1 = false;
  }

  //////2da hora
  if (horas == ref_Horas2 && !nftS_Horas2) {  //if (horas >= ref_Horas2 && !nftS_Horas2) {
    bot.sendMessage(CHAT_ID_1, message);
    bot.sendMessage(CHAT_ID_2, message);
    nftS_Horas2 = true; // Marca la notificación como enviada
  }

  // Restablece la bandera si el valor de la variable vuelve a estar por debajo
  if (horas < ref_Horas2) {
    nftS_Horas2 = false;
  }
}

void ntf_Aj() {
  Time_actual2 = millis();

  // Estado de variables
  float Sensor_T = iaqSensor.temperature;
  float Sensor_H = iaqSensor.humidity;
  float Sensor_G = iaqSensor.co2Equivalent;
  String bot_Estado = "Temperatura: " + String(Sensor_T, 2) + " °C \n";
  bot_Estado += "Setpoint temperatura: " + String(sp_T, 2) + " °C \n";
  bot_Estado += "HR: " + String(Sensor_H, 2) + " % \n";
  bot_Estado += "Setpoint HR: " + String(sp_H, 2) + " % \n";
  bot_Estado += "CO2: " + String(Sensor_G, 1) + " ppm \n";
  bot_Estado += "Setpoint CO2: " + String(sp_G, 1) + " ppm \n";
  bot_Estado += "Tiempo transcurrido: " + String(dias) + " días con " + String(horas) + " horas \n";
  if (estadoFocos) {
    bot_Estado += "Fotoperiodo: On\n";
  } else {
    bot_Estado += "Fotoperiodo: Off\n";
  }

  if (Time_actual2 - ultimaNotificacion >= valor_N_time) {
    bot.sendMessage(CHAT_ID_1, bot_Estado);
    bot.sendMessage(CHAT_ID_2, bot_Estado);
    ultimaNotificacion = Time_actual2; // Actualiza el tiempo de la última notificación
  }
}

void Alarma_T_HH() {
  Time_actual_Alarma = millis();

  float Sensor_T = iaqSensor.temperature;
  String bot_Estado1 = "Alerta por temperatura: " + String(Sensor_T, 2) + " °C alta \n";

  String bot_Estado2 = "Alerta por temperatura: " + String(Sensor_T, 2) + " °C muy alta \n";
  bot_Estado2 += "Potencia de resistencia máxima reducida a: " + String(val_max_Resis) + " % \n";

  String bot_Estado3 = "Potencia de resistencia mínima reducida a: " + String(val_min_Resis) + " % \n";

  // Esperar 30 minutos antes de comenzar a verificar
  if (Time_actual_Alarma - Inicio_Time >= valor_30_mins) {

    // Verificar cada 35 minutos si se cumple la condición
    if (Time_actual_Alarma - ultimaAlarma_T_HH >= valor_30_mins) {

      if ((Sensor_T >= (sp_T + 2.0)) && (Sensor_T <= (sp_T + 4.0))) {
        bot.sendMessage(CHAT_ID_1, bot_Estado1);
        bot.sendMessage(CHAT_ID_2, bot_Estado1);
      } else if (Sensor_T > (sp_T + 4.0)) {
        val_max_Resis = (int)(val_max_Resis * (2.0 / 3.0));

        bot.sendMessage(CHAT_ID_1, bot_Estado2);
        bot.sendMessage(CHAT_ID_2, bot_Estado2);
      }

      if (val_max_Resis <= val_min_Resis) {
        val_min_Resis = (int)(val_min_Resis * (1.0 / 3.0));

        bot.sendMessage(CHAT_ID_1, bot_Estado3);
        bot.sendMessage(CHAT_ID_2, bot_Estado3);
      }



      ultimaAlarma_T_HH = Time_actual_Alarma; // Actualiza el tiempo de la última notificación
    }
  }
}

void Alarma_T_LL() {
  Time_actual_Alarma = millis();

  float Sensor_T = iaqSensor.temperature;
  String bot_Estado1 = "Alerta por temperatura: " + String(Sensor_T, 2) + " °C baja \n";
  String bot_Estado2 = "Alerta por temperatura: " + String(Sensor_T, 2) + " °C muy baja \n";

  // Esperar 30 minutos antes de comenzar a verificar
  if (Time_actual_Alarma - Inicio_Time >= valor_30_mins) {

    // Verificar cada 5 minutos si se cumple la condición
    if (Time_actual_Alarma - ultimaAlarma_T_LL >= valor_5_mins) {

      if ((Sensor_T >= (sp_T - 4.0)) && (Sensor_T <= (sp_T - 2.0))) {
        bot.sendMessage(CHAT_ID_1, bot_Estado1);
        bot.sendMessage(CHAT_ID_2, bot_Estado1);

      } else if (Sensor_T < (sp_T - 4.0)) {
        bot.sendMessage(CHAT_ID_1, bot_Estado2);
        bot.sendMessage(CHAT_ID_2, bot_Estado2);
      }
      ultimaAlarma_T_LL = Time_actual_Alarma; // Actualiza el tiempo de la última notificación
    }
  }
}

void Alarma_H_HH() {
  Time_actual_Alarma = millis();
  float Sensor_H = iaqSensor.humidity;

  String bot_Estado1 = "Alarma de HR: " + String(Sensor_H, 2) + " % alta \n";
  String bot_Estado2 = "Alarma de HR: " + String(Sensor_H, 2) + " % muy alta \n";

  // Esperar 30 minutos antes de comenzar a verificar
  if (Time_actual_Alarma - Inicio_Time >= valor_30_mins) {

    // Verificar cada 5 minutos si se cumple la condición
    if (Time_actual_Alarma - ultimaAlarma_H_HH >= valor_5_mins + 100) {

      if ((Sensor_H >= (sp_H + 15.0)) && (Sensor_H <= (sp_H + 20.0))) {
        bot.sendMessage(CHAT_ID_1, bot_Estado1);
        bot.sendMessage(CHAT_ID_2, bot_Estado1);

      } else if (Sensor_H > (sp_H + 20.0)) {
        bot.sendMessage(CHAT_ID_1, bot_Estado2);
        bot.sendMessage(CHAT_ID_2, bot_Estado2);
      }

      ultimaAlarma_H_HH = Time_actual_Alarma; // Actualiza el tiempo de la última notificación
    }
  }
}

void Alarma_H_LL() {
  Time_actual_Alarma = millis();
  float Sensor_H = iaqSensor.humidity;

  String bot_Estado1 = "Alarma de HR: " + String(Sensor_H, 2) + " % baja \n";
  String bot_Estado2 = "Alarma de HR: " + String(Sensor_H, 2) + " % muy baja \n";

  // Esperar 30 minutos antes de comenzar a verificar
  if (Time_actual_Alarma - Inicio_Time >= valor_30_mins) {

    // Verificar cada 5 minutos si se cumple la condición
    if (Time_actual_Alarma - ultimaAlarma_H_LL >= valor_5_mins + 100) {

      if ((Sensor_H >= (sp_H - 10.0)) && (Sensor_H <= (sp_H - 5.0))) {
        bot.sendMessage(CHAT_ID_1, bot_Estado1);
        bot.sendMessage(CHAT_ID_2, bot_Estado1);
      } else if (Sensor_H < (sp_H - 10.0)) {
        bot.sendMessage(CHAT_ID_1, bot_Estado2);
        bot.sendMessage(CHAT_ID_2, bot_Estado2);
      }
      ultimaAlarma_H_LL = Time_actual_Alarma; // Actualiza el tiempo de la última notificación
    }
  }
}

void Alarma_G() {
  Time_actual_Alarma = millis();

  float Sensor_G = iaqSensor.co2Equivalent;

  String bot_Estado1 = "Alarma de CO2: " + String(Sensor_G, 1) + " ppm alto \n";
  String bot_Estado2 = "Alarma de CO2: " + String(Sensor_G, 1) + " ppm muy alto \n";

  // Esperar 30 minutos antes de comenzar a verificar
  if (Time_actual_Alarma - Inicio_Time >= valor_30_mins) {

    // Verificar cada 5 minutos si se cumple la condición
    if (Time_actual_Alarma - ultimaAlarma_G >= valor_5_mins + 110) {

      if (Sensor_G >= sp_G + 200.0 && Sensor_G <= sp_G + 550.0) {
        bot.sendMessage(CHAT_ID_1, bot_Estado1);
        bot.sendMessage(CHAT_ID_2, bot_Estado1);

      } else if (Sensor_G > sp_G + 550.0) {
        bot.sendMessage(CHAT_ID_1, bot_Estado2);
        bot.sendMessage(CHAT_ID_2, bot_Estado2);
      }

      ultimaAlarma_G = Time_actual_Alarma; // Actualiza el tiempo de la última notificación
    }
  }
}

void Alarma_Resis() {

  Time_actual_Alarma = millis();
  // Esperar 30 minutos antes de comenzar a verificar
  if (Time_actual_Alarma >= valor_30_mins) {

    // Verificar cada 5 minutos si se cumple la condición
    if (Time_actual_Alarma - ultimaAlarma_Resis >= valor_5_mins + 120) {

      String bot_Estado1 = "Alerta de resistencia máxima: " + String(val_max_Resis) + " % baja potencia \n/PotR ";
      String bot_Estado2 = "Alerta de resistencia máxima: " + String(val_max_Resis) + " % muy baja potencia \n/PotR ";
      String bot_Estado3 = "Alerta de resistencia mínima: " + String(val_min_Resis) + " % baja potencia \n/PotRmin ";
      String bot_Estado4 = "Alerta de resistencia mínima: " + String(val_min_Resis) + " % muy baja potencia \n/PotRmin ";

      if (val_max_Resis >= 5 && val_max_Resis <= 10) {
        bot.sendMessage(CHAT_ID_1, bot_Estado1);
        bot.sendMessage(CHAT_ID_2, bot_Estado1);
      } else if (val_max_Resis < 5) {
        bot.sendMessage(CHAT_ID_1, bot_Estado2);
        bot.sendMessage(CHAT_ID_2, bot_Estado2);
      }

      if (val_min_Resis >= 2 && val_min_Resis <= 4) {
        bot.sendMessage(CHAT_ID_1, bot_Estado3);
        bot.sendMessage(CHAT_ID_2, bot_Estado3);
      } else if (val_min_Resis < 2) {
        bot.sendMessage(CHAT_ID_1, bot_Estado4);
        bot.sendMessage(CHAT_ID_2, bot_Estado4);
      }

      ultimaAlarma_Resis = Time_actual_Alarma; // Actualiza el tiempo de la última notificación
    }
  }
}

//////////////////////[Mensajes]//////////////////////
void tele_Bot() {
  int Msj_new = bot.getUpdates(bot.last_message_received + 1);

  while (Msj_new) {
    //Serial.println(F("respondiendo"));
    manejo_Mjs(Msj_new);
    Msj_new = bot.getUpdates(bot.last_message_received + 1);
  }

  ntf_Dias();
  ntf_Aj();
  //ntf_Horas();

  //Time_actual_Alarma = millis();
  Alarma_T_HH();
  Alarma_T_LL();

  Alarma_H_HH();
  Alarma_H_LL();

  Alarma_G();
  Alarma_Resis();
}

//void tele_Bot() {
//  int mensajeNuevo = bot.getUpdates(bot.last_message_received + 1);
//
//  if (mensajeNuevo) {
//    manejo_Mjs(mensajeNuevo);
//  }
//
//  ntf_Dias();
//  ntf_Aj();
//  //ntf_Horas();
//
//  //Time_actual_Alarma = millis();
//  Alarma_T_HH();
//  Alarma_T_LL();
//
//  Alarma_H_HH();
//  Alarma_H_LL();
//
//  Alarma_G();
//  Alarma_Resis();
//}
