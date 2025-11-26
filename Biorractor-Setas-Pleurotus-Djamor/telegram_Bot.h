// Initialize Telegram BOT
#define BOTtoken "7888208609:AAH0tIGH7MxWQGA-eU0iLtdRNiE1_foL8wU"     //Bot Token (por Botfather)
//----------------------------------------------------------------
//#define BOTtoken "7357597851:AAEvP5cGZU1WgwyC46uFIY12ynqgF1-SrGY"   // pruebas 

#define CHAT_ID_1 "1097777759"
#define CHAT_ID_2 "1097777759" //ID PRUEBAS

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void manejo_Mjs(int Msj_new) {
  for (int i = 0; i < Msj_new; i++) {

    //Validación de ID de chat
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID_1 && chat_id != CHAT_ID_2) {
      bot.sendMessage(chat_id, F("Usuario no autorizado..."), "");
      continue;
    }

    String text = bot.messages[i].text;
    //Serial.println(text);
    String from_name = bot.messages[i].from_name;

    float Sensor_T = iaqSensor.temperature;
    float Sensor_H = iaqSensor.humidity;
    float Sensor_G = iaqSensor.co2Equivalent;

    // Comando menú principal
    if (text == F("/start")) {
      String welcome = "Bienvenid@, " + from_name + ".\n";
      welcome += F("Sistema de monitoreo del hábitat.\n\n");
      welcome += F("/Estado del hábitat\n");
      welcome += F("/WiFi estado\n");
      welcome += F("/options\n");
      bot.sendMessage(chat_id, welcome, "");
    }

    // Comando para cambiar el setpoints
    if (text == F("/options")) {
      String welcome2 = "Bienvenid@, " + from_name + ".\n";
      welcome2 += F("Opciones para modificar los parámetros del hábitat.\n\n");
      welcome2 += F("/ejemplos para modificar parámetros\n");
      welcome2 += F("/SetTemp \n");
      welcome2 += F("/SetHum \n");
      welcome2 += F("/SetCO2 \n");

      welcome2 += F("/SetDia \n");
      welcome2 += F("/SetHora \n\n");

      welcome2 += F("/Reiniciar\n");
      welcome2 += F("/CambioRed \n\n");

      welcome2 += F("/paro de emergencia\n\n");
      welcome2 += F("/arranque para reanudar operación\n\n");

      //welcome2 += F("/desarrolladores \n");

      bot.sendMessage(chat_id, welcome2, "");
    }

    // Comando para ver el estado del interior del hábitat
    if (text == F("/Estado")) {

      // Estado del hábitat
      String bot_Estado = "Temperatura: " + String(Sensor_T, 2) + " °C \n";
      bot_Estado += "Setpoint temperatura: " + String(sp_T, 2) + " °C \n";
      bot_Estado += "HR: " + String(Sensor_H, 2) + " % \n";
      bot_Estado += "Setpoint HR: " + String(sp_H, 2) + " % \n";
      bot_Estado += "CO2: " + String(Sensor_G, 1) + " ppm \n";
      bot_Estado += "Setpoint CO2: " + String(sp_G, 1) + " ppm \n";
      bot_Estado += "Tiempo transcurrido: " + String(dias) + " días con " + String(horas) + " horas\n";
      if (estadoFocos) {
        bot_Estado += "Fotoperiodo: On\n";
      } else {
        bot_Estado += "Fotoperiodo: Off\n";
      }
      /////
      bot.sendMessage(chat_id, bot_Estado);
    }

    // Comando para ver el estado del wifi
    if (text == F("/WiFi")) {

      long rssi = WiFi.RSSI();
      String rssi_0 = F("Excelente señal: ");
      String rssi_1 = F("Buena señal: ");
      String rssi_2 = F("Débil señal: ");
      String rssi_3 = F("Pobre señal: ");
      String rssi_4 = F("Sin señal: ");

      if (rssi >= -30.0) {
        rssi_0 += String(rssi) + " dBm \n";
        bot.sendMessage(chat_id, rssi_0);

      } else if (rssi >= -70.0) {
        rssi_1 += String(rssi) + " dBm \n";
        bot.sendMessage(chat_id, rssi_1);

      } else if (rssi >= -80.0) {
        rssi_2 += String(rssi) + " dBm \n";
        bot.sendMessage(chat_id, rssi_2);

      } else if (rssi >= -90.0) {
        rssi_3 += String(rssi) + " dBm \n";
        bot.sendMessage(chat_id, rssi_3);

      } else {
        rssi_4 += String(rssi) + " dBm \n";
        bot.sendMessage(chat_id, rssi_4);
      }

      IPAddress ip = WiFi.localIP();
      String wifi = "IP: " + ip.toString() + " \n";
      bot.sendMessage(chat_id, wifi);
    }

    // Comando para ver ejemplos de como se opera
    if (text == F("/ejemplos")) {
      String informacion = "Ejemplo de como asignar valores con Telegram.\n\n";
      informacion += F("Asignación a una nueva temperatura.\n");
      informacion += F("Ejem: /SetTemp 18.8\n\n");
      informacion += F("Asignación a una nueva humedad relativa.\n");
      informacion += F("Ejem: /SetHum 60.0\n\n");
      informacion += F("Asignación del CO2.\n");
      informacion += F("Ejem: /SetCO2 700.0 \n\n");
      informacion += F("Asignar días transcurridos.\n");
      informacion += F("Ejem: /SetDia 2\n\n");
      informacion += F("Asignar horas transcurridas en el día.\n");
      informacion += F("Ejem: /SetHora 14\n\n");
      informacion += F("Es importante que se escriba la instrucción con '/' y que indique el valor a asignar tal como en cada ejemplo para evitar algún error.\n");

      bot.sendMessage(chat_id, informacion);
    }

    // Comando para ajustes finos
    if (text == F("/desarrolladores")) {
      String informacion2 = "Ejemplo de como asignar valores con Telegram.\n\n";
      informacion2 += F("Para visualizar los valores asignados.\n");
      informacion2 += F("/Asignaciones\n\n");
      informacion2 += F("Asignación de ganancia Kp resistencia.\n");
      informacion2 += F("Ejem: /Kp 24.12345 \n\n");
      informacion2 += F("Asignación de ganancia Ki resistencia.\n");
      informacion2 += F("Ejem: /Ki 0.12345 \n\n");
      informacion2 += F("Asignación de ganancia Kd resistencia.\n");
      informacion2 += F("Ejem: /Kd 0.12345 \n\n");

      informacion2 += F("Asignar de tiempo on bomba (segundos).\n");
      informacion2 += F("Ejem: /tbOn 3 \n\n");
      informacion2 += F("Asignar de tiempo off bomba (min).(s).\n");
      informacion2 += F("Ejem: /tbOff 10.4 \n\n");

      informacion2 += F("Asignación de día de inicio para fructificación.\n");
      informacion2 += F("Ejem: /D_FRC 10 \n\n");
      informacion2 += F("Asignación temperatura de fructificación.\n");
      informacion2 += F("Ejem: /FRC_T 28.0 \n\n");
      informacion2 += F("Asignación humedad relativa de fructificación.\n");
      informacion2 += F("Ejem: /FRC_H 90.0 \n\n");
      informacion2 += F("Asignación CO2 de fructificación.\n");
      informacion2 += F("Ejem: /FRC_G 1000.0 \n\n");

      informacion2 += F("Asignar de tiempo on extractor (min).(s)\n");
      informacion2 += F("Ejem: /ExtOn 3.2 \n\n");
      informacion2 += F("Asignar de tiempo off extractor (min).(s)\n");
      informacion2 += F("Ejem: /ExtOff 5.1 \n\n");

      informacion2 += F("Asignar de tiempo de notificación (horas).(min)\n");
      informacion2 += F("Ejem: /Tntf 1.15 \n\n");

      informacion2 += F("Asignar de tiempo on resistencia (min).(s)\n");
      informacion2 += F("Ejem: /ResOn 2.2 \n\n");
      informacion2 += F("Asignar de tiempo off resistencia (min).(s)\n");
      informacion2 += F("Ejem: /ResOff 3.1 \n\n");

      informacion2 += "Comando para potencias: /ComandoPot \n";
      informacion2 += "Estado de potencias: /Potencias \n";

      informacion2 += F("Es importante que se escriba la instrucción con '/' y que indique el valor a asignar tal como en cada ejemplo para evitar algún error.\n");

      bot.sendMessage(chat_id, informacion2);
    }

    // Comando para cambiar el setpoint de temperatura
    if (text.startsWith(F("/SetTemp "))) {
      float newSetpoint = text.substring(9).toFloat(); // Extrae el nuevo setpoint del mensaje
      lcd.setCursor(3, 0);
      lcd.print("     ");
      sp_T = newSetpoint;// Asigna el nuevo setpoint

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
      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Setpoint de temperatura actualizado a: " + String(sp_T) + " °C");
    }

    // Comando para cambiar el setpoint de humedad
    if (text.startsWith(F("/SetHum "))) {
      lcd.setCursor(4, 1);
      lcd.print("     ");
      float newSpHR = text.substring(8).toFloat(); // Extrae el nuevo setpoint del mensaje
      sp_H = newSpHR;// Asigna el nuevo setpoint

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

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Setpoint de humedad relativa actualizado a: " + String(sp_H) + " %");
    }

    // Comando para cambiar el setpoint de CO2
    if (text.startsWith(F("/SetCO2 "))) {
      lcd.setCursor(5, 2);
      lcd.print("     ");
      float newSpCO2 = text.substring(8).toFloat(); // Extrae el nuevo setpoint del mensaje
      sp_G = newSpCO2;// Asigna el nuevo setpoint

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

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Setpoint de CO2 actualizado a: " + String(sp_G, 1) + " ppm");
    }
    if (sp_G >= 3000.0) {
      sp_G = 3000.0;
    } else if (sp_G <= 600.0) {
      sp_G = 600.0;
    }

    // Comando para cambiar el setpoint de dia
    if (text.startsWith(F("/SetDia "))) {
      int newDAY = text.substring(8).toInt(); // Extrae el nuevo setpoint del mensaje

      lcd.setCursor(11, 3);
      lcd.print(F("  "));//lcd.print(F("   "));
      dias = 0;
      dias = newDAY;// Asigna el nuevo setpoint

      // Reinicia los contadores de tiempo
      Time_actual3 = millis();
      Time_previo_3 = Time_actual3;

      Time_actual2 = millis();
      ultimaNotificacion = Time_actual2;

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Día actualizado a: " + String(dias));
    }

    // Comando para cambiar el setpoint de hora
    if (text.startsWith(F("/SetHora "))) {
      int newHOURS = text.substring(9).toInt(); // Extrae el nuevo setpoint del mensaje

      lcd.setCursor(17, 3);
      lcd.print(F("  "));

      horas = 0;
      horas = newHOURS;// Asigna el nuevo setpoint

      // Reinicia los contadores de tiempo
      Time_actual3 = millis();
      Time_previo_3 = Time_actual3;

      Time_actual2 = millis();
      ultimaNotificacion = Time_actual2;

      if (horas >= 24) {
        horas = 0;
        dias++;

        // Envía un mensaje de confirmación
        bot.sendMessage(chat_id, "Día actualizado a: " + String(dias) + "\nHoras actualizado a: " + String(horas) + " horas \n");
      } else {
        // Envía un mensaje de confirmación
        bot.sendMessage(chat_id, "Horas actualizado a: " + String(horas) + " horas \n");
      }

    }

    // Comando para reiniciar contador de dias y horas
    if (text == F("/Reiniciar")) {

      lcd.setCursor(11, 3);
      lcd.print(F("   "));
      lcd.setCursor(17, 3);
      lcd.print(F("  "));

      // Asigna el nuevo valor
      dias = 0;
      horas = 0;

      // Reinicia los contadores de tiempo
      Time_actual3 = millis();
      Time_previo_3 = Time_actual3;

      Time_actual2 = millis();
      ultimaNotificacion = Time_actual2;

      bot.sendMessage(chat_id, "Días reiniciados: " + String(dias) + " \nHoras reiniciadas: " + String(horas) + " \n");
    }

    // Cambiar de red de forma local no remota(recomendación)
    if (text == F("/CambioRed")) {

      Time_actual_Alarma = millis(); // Actualizar currentTime con el tiempo actual

      // Reinicia los contadores de tiempo
      Inicio_Time = Time_actual_Alarma;
      ultimaAlarma_T_HH = ultimaAlarma_T_LL = Time_actual_Alarma;
      ultimaAlarma_H_HH = ultimaAlarma_H_LL = Time_actual_Alarma;
      ultimaAlarma_G = Time_actual_Alarma;
      ultimaAlarma_Resis = Time_actual_Alarma;

      bot.sendMessage(chat_id, "Cambia de red de Wi-Fi...\n");
      wm.resetSettings();
      wm.setConfigPortalBlocking(true);
      wm.setConfigPortalTimeout(180);

      if (wm.autoConnect("Monitoreo_Setas")) {
        Serial.println("Conectado a la red :)");
      }
      else {
        Serial.println("Configportal running");
      }
    }

    // Paro de emergencia
    if (text == F("/paro")) {
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

      bot.sendMessage(chat_id, "Paro de emergencia...\n");

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

    // Arranque y asignación de ultimas potencias registradas
    if (text == F("/arranque")) {
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

      String back_Estado = "Reanudando operación...\n";
      back_Estado += "Potencia de resistencia min: " + String(val_min_Resis) + " % \n";
      back_Estado += "Potencia de resistencia max: " + String(val_max_Resis) + " % \n";
      back_Estado += "Potencia de extractor min: " + String(val_min_HTG) + " % \n";
      back_Estado += "Potencia de extractor max: " + String(val_max_HTG) + " % \n";
      back_Estado += "Potencia de bomba: " + String(Pot_Bomba) + " % \n";
      back_Estado += "Verificar los tiempos en: /Asignaciones \n";
      bot.sendMessage(chat_id, back_Estado);
    }

    //////////////////////////////////
    // Comando para cambiar la potencia máxima de operacion del extractor
    if (text.startsWith(F("/MaxExtr "))) {
      int newMax_Extr = text.substring(9).toInt(); // Extrae el nuevo setpoint del mensaje

      val_max_HTG = newMax_Extr;

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Potencia máxima del extractor actualizado a: " + String(val_max_HTG) + " %");
    }

    // Comando para cambiar la potencia mínima de operacion del extractor
    if (text.startsWith(F("/MinExtr "))) {
      int newMin_Extr = text.substring(9).toInt(); // Extrae el nuevo setpoint del mensaje

      val_min_HTG = newMin_Extr;

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Potencia mínima del extractor actualizado a: " + String(val_min_HTG) + " %");
    }

    if (text.startsWith(F("/MaxBom "))) {
      int newMax_Bomb = text.substring(8).toInt(); // Extrae el nuevo setpoint del mensaje

      Pot_Bomba = newMax_Bomb;

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Potencia máxima de la bomba actualizado a: " + String(Pot_Bomba) + " %");
    }

    // Comando para cambiar la potencia máxima de operacion de la resistencia
    if (text.startsWith(F("/PotR "))) {
      int newMax_Resis = text.substring(6).toInt(); // Extrae el nuevo setpoint del mensaje

      if (newMax_Resis > 85) {
        val_max_Resis = 55;
      } else {
        val_max_Resis = newMax_Resis;
      }

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Potencia máxima de resistencia actualizado a: " + String(val_max_Resis) + " %");
    }

    if (text.startsWith(F("/PotRmin "))) {
      int newMin_Resis = text.substring(9).toInt(); // Extrae el nuevo setpoint del mensaje

      val_min_Resis = newMin_Resis;

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Potencia mínima de resistencia actualizado a: " + String(val_min_Resis) + " %");
    }

    if (text == F("/Potencias")) {

      String potencias = "Potencia máxima de la bomba: " + String(Pot_Bomba) + " % \n";

      potencias += "Potencia mínima del extractor: " + String(val_min_HTG) + " % \n";
      potencias += "Potencia máxima del extractor: " + String(val_max_HTG) + " % \n";

      potencias += "Potencia mínima de la resistenciar: " + String(val_min_Resis) + " % \n";
      potencias += "Potencia máxima de la resistencia: " + String(val_max_Resis) + " % \n";
      bot.sendMessage(chat_id, potencias);
    }

    if (text == F("/ComandoPot")) {

      String potencias2 = "Potencia máxima de la bomba: /MaxBom \n";

      potencias2 += "Potencia mínima del extractor: /MinExtr\n";
      potencias2 += "Potencia máxima del extractor: /MaxExtr \n";

      potencias2 += "Potencia mínima de la resistenciar: /PotRmin \n";
      potencias2 += "Potencia máxima de la resistencia: /PotR \n";
      potencias2 += "Estado de potencias: /Potencias \n";
      bot.sendMessage(chat_id, potencias2);
    }
    //////////////////////////////////


    // Comando para cambiar la ganancia proporcional de la resistencia
    if (text.startsWith(F("/Kp "))) {
      float newKp_Resis = text.substring(4).toFloat(); // Extrae el nuevo setpoint del mensaje
      Kp_Resis = newKp_Resis;

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Ganancia actualizada Kp : " + String(newKp_Resis, 5));
    }

    // Comando para cambiar la ganancia integral de la resistencia
    if (text.startsWith(F("/Ki "))) {
      float newKi_Resis = text.substring(4).toFloat(); // Extrae el nuevo setpoint del mensaje
      Ki_Resis = newKi_Resis;

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Ganancia actualizada Ki: " + String(Ki_Resis, 5));
    }

    // Comando para cambiar la ganancia derivativa de la resistencia
    if (text.startsWith(F("/Kd "))) {
      float newKd_Resis = text.substring(4).toFloat(); // Extrae el nuevo setpoint del mensaje
      Kd_Resis = newKd_Resis;// Asigna el nuevo setpoint

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Ganancia actualizada Kd: " + String(Kd_Resis, 5));
    }

    // Comando para cambiar el tiempo On de bomba
    if (text.startsWith(F("/tbOn "))) {
      int newBombaOn = text.substring(6).toInt(); // Extrae el nuevo setpoint del mensaje
      tiempoEncendido_Bomba = 1000 * newBombaOn;

      int valTime1 = tiempoEncendido_Bomba / 1000;  //De milis a seg

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Tiempo de bomba on actualizado: " + String(valTime1) + " s");
    }

    // Comando para cambiar el tiempo Off de bomba
    if (text.startsWith(F("/tbOff "))) {
      float newtbOff = text.substring(7).toFloat(); // Extrae el nuevo setpoint del mensaje como float
      int mintbOff = (int)newtbOff; // Obtiene la parte entera (minutos)
      float segtbOff = (newtbOff - mintbOff) * 100; // Obtiene los segundos correctamente
      segtbOff = constrain(round(segtbOff), 0, 59);
      tiempoApagado_Bomba = (mintbOff * 60 * 1000) + (round(segtbOff) * 1000);

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Tiempo de bomba off actualizado: " + String(mintbOff) + " min y " + String(round(segtbOff), 0) + " s");
    }

    // Comando para cambiar el día de fructificación
    if (text.startsWith(F("/D_FRC "))) {
      int newDias_Fructificacion = text.substring(7).toInt(); // Extrae el nuevo setpoint del mensaje
      dias_Fructificacion = newDias_Fructificacion;// Asigna el nuevo setpoint

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Días de fructificación actualizado:" + String(dias_Fructificacion) + " días");
    }

    // Comando para cambiar la temperatura de fructificación
    if (text.startsWith(F("/FRC_T "))) {
      float newFRC_T = text.substring(7).toFloat(); // Extrae el nuevo setpoint del mensaje
      FRC_T = newFRC_T;// Asigna el nuevo setpoint

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Temperatura de fructificación actualizado: " + String(FRC_T, 2) + " °C");
    }

    // Comando para cambiar la HR de fructificación
    if (text.startsWith(F("/FRC_H "))) {
      float newFRC_H = text.substring(7).toFloat(); // Extrae el nuevo setpoint del mensaje
      FRC_H = newFRC_H;// Asigna el nuevo setpoint

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Humedad relativa de fructificación actualizado: " + String(FRC_H, 2) + " %");
    }

    // Comando para cambiar el CO2 de fructificación
    if (text.startsWith(F("/FRC_G "))) {
      float newFRC_G = text.substring(7).toFloat(); // Extrae el nuevo setpoint del mensaje
      FRC_G = newFRC_G;// Asigna el nuevo setpoint

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "CO2 de fructificación actualizado: " + String(FRC_G, 1) + " ppm");
    }

    // Comando para cambiar el tiempo On del extractor
    if (text.startsWith(F("/ExtOn "))) {
      float newExtOn = text.substring(7).toFloat(); // Extrae el nuevo setpoint del mensaje como float
      int minExtOn = (int)newExtOn; // Obtiene la parte entera (minutos)
      float segExtOn = (newExtOn - minExtOn) * 100; // Obtiene los segundos correctamente
      segExtOn = constrain(round(segExtOn), 0, 59);
      tiempoEncendido_Trabajo = (minExtOn * 60 * 1000) + (round(segExtOn) * 1000);

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Tiempo de extractor on actualizado: " + String(minExtOn) + " min y " + String(round(segExtOn), 0) + " s");
    }

    // Comando para cambiar el tiempo Off del extractor
    if (text.startsWith(F("/ExtOff "))) {
      float newExtOff = text.substring(8).toFloat(); // Extrae el nuevo setpoint del mensaje como float
      int minExtOff = (int)newExtOff; // Obtiene la parte entera (minutos)
      float segExtOff = (newExtOff - minExtOff) * 100; // Obtiene los segundos correctamente
      segExtOff = constrain(round(segExtOff), 0, 59);
      tiempoApagado_Trabajo = (minExtOff * 60 * 1000) + (round(segExtOff) * 1000);

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Tiempo de extractor off actualizado: " + String(minExtOff) + " min y " + String(round(segExtOff), 0) + " s");
    }

    ////////////////////////////////////////////////////////////////////////////////////
    // Comando para cambiar el tiempo On de la resistencia
    if (text.startsWith(F("/ResOn "))) {
      float newResOn = text.substring(7).toFloat(); // Extrae el nuevo setpoint del mensaje como float
      int minResOn = (int)newResOn; // Obtiene la parte entera (minutos)
      float segResOn = (newResOn - minResOn) * 100; // Obtiene los segundos correctamente
      segResOn = constrain(round(segResOn), 0, 59);
      tiempoEncendido_Trabajo_R = (minResOn * 60 * 1000) + (round(segResOn) * 1000);

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Tiempo de la resistencia on actualizado: " + String(minResOn) + " min y " + String(round(segResOn), 0) + " s");
    }

    // Comando para cambiar el tiempo Off de la resistencia
    if (text.startsWith(F("/ResOff "))) {
      float newResOff = text.substring(8).toFloat(); // Extrae el nuevo setpoint del mensaje como float
      int minResOff = (int)newResOff; // Obtiene la parte entera (minutos)
      float segResOff = (newResOff - minResOff) * 100; // Obtiene los segundos correctamente
      segResOff = constrain(round(segResOff), 0, 59);
      tiempoApagado_Trabajo_R = (minResOff * 60 * 1000) + (round(segResOff) * 1000);

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Tiempo de la resistencia off actualizado: " + String(minResOff) + " min y " + String(round(segResOff), 0) + " s");
    }
    ////////////////////////////////////////////////////////////////////////////////////

    // Comando para cambiar el tiempo de notificaciones de estado
    if (text.startsWith(F("/Tntf "))) {
      float newTntf = text.substring(6).toFloat(); // Extrae el nuevo setpoint del mensaje como float
      int hrsTntf = (int)newTntf; // Obtiene la parte entera (horas)
      float minTntf = (newTntf - hrsTntf) * 100; // Obtiene los minutos correctamente
      minTntf = constrain(round(minTntf), 0, 59);
      valor_N_time = (hrsTntf * 60 * 60 * 1000) + (round(minTntf) * 60 * 1000);

      Time_actual2 = millis();
      ultimaNotificacion = Time_actual2;

      // Envía un mensaje de confirmación
      bot.sendMessage(chat_id, "Tiempo de notificación actualizado: " + String(hrsTntf) + " horas y " + String(round(minTntf), 0) + " min");
    }

    if (text == F("/InfoRed")) {

      String wifi = "SSID: " + String(WiFi.SSID()) + " \n";
      wifi = + "pass: " + String(WiFi.psk()) + " \n";

      bot.sendMessage(chat_id, wifi);
    }

    // Comando para enviar mensaje del estado de asignaciones actuales
    if (text == F("/Asignaciones")) {
      int valTime1 = tiempoEncendido_Bomba / 1000;  //De milis a seg

      int valTime2_min = tiempoApagado_Bomba / (1000 * 60);  // De milis a mins
      int valTime2_sec = (tiempoApagado_Bomba % (1000 * 60)) / 1000;  // De milis a secs

      int valTime3_min = tiempoEncendido_Trabajo / (1000 * 60);  // De milis a mins
      int valTime3_sec = (tiempoEncendido_Trabajo % (1000 * 60)) / 1000;  // De milis a secs

      int valTime33_min = tiempoEncendido_Trabajo_R / (1000 * 60);  // De milis a mins
      int valTime33_sec = (tiempoEncendido_Trabajo_R % (1000 * 60)) / 1000;  // De milis a secs

      int valTime4_min = tiempoApagado_Trabajo / (1000 * 60);  // De milis a mins
      int valTime4_sec = (tiempoApagado_Trabajo % (1000 * 60)) / 1000;  // De milis a secs

      int valTime44_min = tiempoApagado_Trabajo_R / (1000 * 60);  // De milis a mins
      int valTime44_sec = (tiempoApagado_Trabajo_R % (1000 * 60)) / 1000;  // De milis a secs

      int valTime5_hrs = valor_N_time / (1000 * 60 * 60); // De milis a horas
      int valTime5_mins = (valor_N_time % (1000 * 60 * 60)) / (1000 * 60); // De milisa mins

      // Estado de los valores asignados
      String bot_Estado2 = "Asignación de valores actuales.\n\n";
      bot_Estado2 += "Potencia máxima de resistencia: " + String(val_max_Resis) + " %\n";
      bot_Estado2 += "Kp resistencia: " + String(Kp_Resis, 5) + " \n";
      bot_Estado2 += "Ki resistencia: " + String(Ki_Resis, 5) + " \n";
      bot_Estado2 += "Kd resistencia: " + String(Kd_Resis, 5) + " \n";

      bot_Estado2 += "Inicio de día para fructificación: " + String(dias_Fructificacion) + " días \n";
      bot_Estado2 += "Temperatura de fructificación: " + String(FRC_T, 2) + " °C \n";
      bot_Estado2 += "HR de fructificación: " + String(FRC_H, 2) + " % \n";
      bot_Estado2 += "CO2 de fructificación: " + String(FRC_G, 1) + " ppm \n";

      bot_Estado2 += "Tiempo de bomba on: " + String(valTime1) + " s\n";
      bot_Estado2 += "Tiempo de bomba off: " + String(valTime2_min) + " min y " + String(valTime2_sec) + " s\n";

      bot_Estado2 += "Tiempo de extractor on: " + String(valTime3_min) + " min y " + String(valTime3_sec) + " s\n";
      bot_Estado2 += "Tiempo de extractor off: " + String(valTime4_min) + " min y " + String(valTime4_sec) + " s\n";

      bot_Estado2 += "Tiempo de la resistencia on: " + String(valTime33_min) + " min y " + String(valTime33_sec) + " s\n";
      bot_Estado2 += "Tiempo de la resistencia off: " + String(valTime44_min) + " min y " + String(valTime44_sec) + " s\n";

      bot_Estado2 += "Tiempo de notificación: " + String(valTime5_hrs) + " horas y " + String(valTime5_mins) + " min\n";

      bot.sendMessage(chat_id, bot_Estado2);
    }
  }
}
