//////////////////////[BOMBA]//////////////////////
void ajuste_Bomba() {

  if (estadoBomba) {// Verificar si ha pasado el tiempo de encendido o apagado

    if (Time_actual - tiempoAntes_Bomba >= tiempoEncendido_Bomba) { // Verificar si ha pasado el tiempo de encendido
      estadoBomba = !estadoBomba;   // Invertir el estado del motor
      tiempoAntes_Bomba += tiempoEncendido_Bomba;
    }

  } else {

    if (Time_actual - tiempoAntes_Bomba >= tiempoApagado_Bomba) {   // Verificar si ha pasado el tiempo de apagado
      estadoBomba = !estadoBomba;     // Invertir el estado del motor
      tiempoAntes_Bomba += tiempoApagado_Bomba;
    }
  }

  // Establecer el estado de la bomba
  if (estadoBomba) {


    if (iaqSensor.humidity <= (90.0 - 1.0)) {
      cv_2 = constrain(cv_2, 0, 55);    //salida maxima sera el 55%
      valor_2 = map(cv_2, 0, 100, 0 , 255 ); // Prende
      dim.write(1, cv_2);
    }
    else {
      cv_2 = 0;
      dim.write(1, cv_2);
    }

  } else {
    cv_2 = 0;
    dim.write(1, cv_2);
  }
  Serial.print(", V2 pwm: ");
  Serial.println(valor_2);
}


void time_Trabajo() {
  if (estado_Trabajo) {// Verificar si ha pasado el tiempo de encendido o apagado

    if (Time_actual - tiempoAntes_Trabajo >= tiempoEncendido_Trabajo) { // Verificar si ha pasado el tiempo de encendido
      estado_Trabajo = !estado_Trabajo;   // Invertir el estado del extractor 1
      tiempoAntes_Trabajo += tiempoEncendido_Trabajo;
    }

  } else {

    if (Time_actual - tiempoAntes_Trabajo >= tiempoApagado_Trabajo) {   // Verificar si ha pasado el tiempo de apagado
      estado_Trabajo = !estado_Trabajo;     // Invertir el estado del extractor 1
      tiempoAntes_Trabajo += tiempoApagado_Trabajo;
    }
  }

  // Establecer el estado del extractor 1
  if (estado_Trabajo) {//1
    //Posibilidad de poner aqui el LC_PI_RESIS(); para un tiempo de trabajo

    if (iaqSensor.humidity >= (sp_H + rango_H)) {
      LC_PI_HUM();
      Serial.println("PID_H");

    } else if (iaqSensor.temperature >= (sp_T + rango_T)) {
      LC_PI_TEMP();
      Serial.println("PID_T");

    } else if (iaqSensor.co2Equivalent >= (sp_G + rango_G)) {
      LC_PI_CO2();
      Serial.println("PID_CO2");

    } else {  //Solo para ventilar al % minimo
      int enCaso = 0;

      enCaso = map(val_min_HTG, 0, 100, 0 , 255 );
      dim.write(1, enCaso);
      Serial.println("Caso0");
    }
  } else {  //0 En caso que el estado sea 0 descansar extr1 y resis [opcional]
    dim.write(1, 0);
    Serial.println("Caso1");
  }
}
