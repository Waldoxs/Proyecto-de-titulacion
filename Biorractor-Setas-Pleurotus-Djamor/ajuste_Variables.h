//////////////////////[BOMBA]//////////////////////
//void ajuste_Bomba() {
//  int Pot_Bomba0 = 0;
//  if (estadoBomba) {// Verificar si ha pasado el tiempo de encendido o apagado
//
//    if (Time_actual5 - tiempoAntes_Bomba >= tiempoEncendido_Bomba) { // Verificar si ha pasado el tiempo de encendido
//      estadoBomba = !estadoBomba;   // Invertir el estado de la bomba
//      tiempoAntes_Bomba += tiempoEncendido_Bomba;
//    }
//
//  } else {
//
//    if (Time_actual5 - tiempoAntes_Bomba >= tiempoApagado_Bomba) {   // Verificar si ha pasado el tiempo de apagado
//      estadoBomba = !estadoBomba;     // Invertir el estado de la bomba
//      tiempoAntes_Bomba += tiempoApagado_Bomba;
//    }
//  }
//
//  // Establecer el estado de la bomba
//  if (estadoBomba) {
//
//    if (iaqSensor.humidity <= (sp_H - rango_H)) {
//
//      valor_5 = map(Pot_Bomba, 0, 100, 0 , 255 ); // On
//      dim.write(2, valor_5);
//
//    }
//    else {
//      valor_5 = map(Pot_Bomba0, 0, 100, 0 , 255 ); // Off
//      dim.write(2, valor_5);
//
//    }
//  }
//  else {
//    valor_5 = map(Pot_Bomba0, 0, 100, 0 , 255 ); // Off
//    dim.write(2, valor_5);
//
//  }
//}

void ajuste_Bomba2() {
  int Pot_Bomba0 = 0;
  if (estadoBomba) {// Verificar si ha pasado el tiempo de encendido o apagado

    if (Time_actual5 - tiempoAntes_Bomba >= tiempoEncendido_Bomba) { // Verificar si ha pasado el tiempo de encendido
      estadoBomba = !estadoBomba;   // Invertir el estado de la bomba
      tiempoAntes_Bomba += tiempoEncendido_Bomba;
    }

  } else {

    if (Time_actual5 - tiempoAntes_Bomba >= tiempoApagado_Bomba) {   // Verificar si ha pasado el tiempo de apagado
      estadoBomba = !estadoBomba;     // Invertir el estado de la bomba
      tiempoAntes_Bomba += tiempoApagado_Bomba;
    }
  }

  // Establecer el estado de la bomba
  if (estadoBomba) {
    valor_5 = map(Pot_Bomba, 0, 100, 0 , 255 ); // On
    dim.write(2, valor_5);
  }
  else {
    valor_5 = map(Pot_Bomba0, 0, 100, 0 , 255 ); // Off
    dim.write(2, valor_5);

  }
}

//////////////////////[TIEMPO DE TRABAJO: EXTRACTOR]//////////////////////
void time_Trabajo_Ext1() {
  if (estado_Trabajo) {// Verificar si ha pasado el tiempo de encendido o apagado

    if (Time_actual5 - tiempoAntes_Trabajo >= tiempoEncendido_Trabajo) { // Verificar si ha pasado el tiempo de encendido
      estado_Trabajo = !estado_Trabajo;   // Invertir el estado del extractor 1
      tiempoAntes_Trabajo += tiempoEncendido_Trabajo;
    }

  } else {

    if (Time_actual5 - tiempoAntes_Trabajo >= tiempoApagado_Trabajo) {   // Verificar si ha pasado el tiempo de apagado
      estado_Trabajo = !estado_Trabajo;     // Invertir el estado del extractor 1
      tiempoAntes_Trabajo += tiempoApagado_Trabajo;
    }
  }

  // Establecer el estado del extractor 1
  if (estado_Trabajo) {//1
    //LC_PI_RESIS();

    if (iaqSensor.humidity >= (sp_H + rango_H)) {
      LC_PI_HUM();
      //Serial.println("PID_H");

    } else if (iaqSensor.temperature >= (sp_T + rango_T)) {
      LC_PI_TEMP();
      //Serial.println("PID_T");

    } else if (iaqSensor.co2Equivalent >= (sp_G + rango_G)) {
      LC_PI_CO2();
      //Serial.println("PID_CO2");

    } else {  //Solo para ventilar al % minimo
      int enCaso = 0;

      enCaso = map(val_min_HTG, 0, 100, 0 , 255 );
      dim.write(1, enCaso);

      //Serial.println("Caso neutro");
    }
  } else {  //0 En caso que el estado sea 0 descansar extr1 y resis [opcional]
    //Serial.println("Caso 0");
    //valor_1 = 0;    //Resistencia alambre
    valor_2 = 0;    //Ext1 - Hum
    valor_3 = 0;    //Ext1 - Temp
    valor_4 = 0;    //Ext1 - CO2
    //Pot_Resis = 0;
    Pot_Hum = 0;
    Pot_Temp = 0;
    Pot_CO2 = 0;
    dim.write(1, 0);          //Extractor en general
    //dim.write(0, valor_1);    //Resistencia alambre
  }
}

//////////////////////[TIEMPO DE TRABAJO: FOCO AZUL ]//////////////////////
void time_FOCO_A() {
  if (dias >= dias_Fructificacion && horas >= 0 && horas < 8) {
    digitalWrite(Pin_FocoA, HIGH); // Prende
    //Serial.println("F_on");
    estadoFocos = true;
    RemoteXY.stateFotoperiodo = 2;

  } else {
    digitalWrite(Pin_FocoA, LOW); // Apaga
    //Serial.println("F_off");
    estadoFocos = false;
    RemoteXY.stateFotoperiodo = 1;
  }
}

//////////////////////[CAMBIO DE ETAPA]//////////////////////
void Etapas() {
  if (dias >= dias_Fructificacion) {
    //Serial.println(F("Etapa 2"));
    sp_T = FRC_T;
    sp_H = FRC_H;
    sp_G = FRC_G;

  }
  else {
    //Serial.println(F("Etapa 1"));
    sp_T = INC_T;
    sp_H = INC_H;
    sp_G = INC_G;
  }
}

//////////////////////[TIEMPO DE TRABAJO: RESISTENCIA]//////////////////////  [Fuera de operación]
void time_Trabajo_Resis() {   //NOTA: Esta funcion no es util una vez que la resistencia este en el extractor
  if (estado_Trabajo_R) {     // Verificar si ha pasado el tiempo de encendido o apagado

    if (Time_actual5 - tiempoAntes_Trabajo_R >= tiempoEncendido_Trabajo_R) { // Verificar si ha pasado el tiempo de encendido
      estado_Trabajo_R = !estado_Trabajo_R;   // Invertir el estado de la resistencia
      tiempoAntes_Trabajo_R += tiempoEncendido_Trabajo_R;
    }

  } else {

    if (Time_actual5 - tiempoAntes_Trabajo_R >= tiempoApagado_Trabajo_R) {   // Verificar si ha pasado el tiempo de apagado
      estado_Trabajo_R = !estado_Trabajo_R;     // Invertir el estado de la resistencia
      tiempoAntes_Trabajo_R += tiempoApagado_Trabajo_R;
    }
  }

  // Establecer el estado de la resistencia
  if (estado_Trabajo_R) {//1
    LC_PI_RESIS();

  } else {  //0 En caso que el estado sea 0 descansar resis

    Pot_Resis = 0;   //Asignacion a la entrada de la planta.
    valor_1 = map(Pot_Resis, 0, 100, 0 , 255 );
    dim.write(0, valor_1);

  }
}
