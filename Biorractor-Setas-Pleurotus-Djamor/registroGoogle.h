const char* serverName = "https://script.google.com/macros/s/AKfycbzMQmKlQxtFup0F93hIsfLRK7sg6xFr_LlXjkSXPBsriNCOozFQMvKZc310mPeUQgBETg/exec";

/*Asignarle un tiempo de espera en lo que el sensor se recalibra siendo un total de 30 minutos minimos, para posteorior a este tiempo se pueda
  enviar los datos al Excel de Google*/

void registroExcel() {
  Time_actual_Excel = millis();
  // Esperar 10 minutos para recalibrar el sensor
  if (Time_actual_Excel - Inicio_Time_Excel >= valor_10_mins) {

    // Enviar cada 6 minutos el dato a excel
    if (Time_actual_Excel - ultimoRegistro >= valor_6_mins) {

      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverName);
        http.addHeader("Content-Type", "application/json");

        String jsonData = "{\"dia\":\"" + String(dias) + "\", \"hora\":\"" + String(horas) + "\", \"st_temp\":\"" + String(sp_T) + "\", \"temp\":\"" + String(iaqSensor.temperature) + "\", \"st_hum\":\"" + String(sp_H) + "\", \"hum\":\"" + String(iaqSensor.humidity) + "\", \"st_gas\":\"" + String(sp_G) + "\", \"gas\":\"" + String(iaqSensor.co2Equivalent) + "\", \"potResist\":\"" + String(val_max_Resis) + "\"}";

        int httpResponseCode = http.POST(jsonData);

        //        if (httpResponseCode > 0) {
        //          String response = http.getString();
        //          //Serial.println(httpResponseCode);
        //          //Serial.println(response);
        //        } else {
        //          //Serial.print("Wrong request POST: ");
        //          //Serial.println(httpResponseCode);
        //        }

        http.end();
      }
      ultimoRegistro = Time_actual_Excel; // Actualiza el tiempo de la última notificación
    }
  }
}
