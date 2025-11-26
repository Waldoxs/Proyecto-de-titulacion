/*  NOTA:
       Solo modificar en caso que se quieran habilitar los PID
*/

///////////////[PID_Temperatura (Resistencia) ]//////////// PID
void LC_PI_RESIS() {

  error_Resis = (sp_T + 0.3) - iaqSensor.temperature; //Calculo del error

  //----- ECUACION DE DIFERENCIAS (PID) -----
  //cv_Resis = cv1_Resis + (Kp_Resis + Kd_Resis / Tm_Resis) * error_Resis + (-Kp_Resis + Ki_Resis * Tm_Resis - 2 * Kd_Resis / Tm_Resis) * error1_Resis + (Kd_Resis / Tm_Resis) * error2_Resis;

  // ----- ECUACION DE DIFERENCIAS (PI) -----
  cv_Resis = cv1_Resis + (Kp_Resis + Ki_Resis * Tm_Resis) * error_Resis - (Kp_Resis - Ki_Resis * Tm_Resis) * error1_Resis;

  //Recursividad
  cv1_Resis = cv_Resis;
  error2_Resis = error1_Resis;  //PID
  error1_Resis = error_Resis; //PI
  /*  NOTA:
       para PI solo se usa la linea de: error1 = error; //PI
       mientras que para el PID: error2 = error1;  error1 = error;
  */

  // Limite de salida del controlador    cv_Resis = constrain(cv, 0, 100);
  cv_Resis = constrain(cv_Resis, val_min_Resis, val_max_Resis);    
  Pot_Resis = cv_Resis;   //Asignacion a la entrada de la planta.

  valor_1 = map(Pot_Resis, 0, 100, 0 , 255 );
  dim.write(0, valor_1);
}

//////////////////////[EXTRACTOR - SALE AIRE]//////////////////////
void LC_PI_HUM() {

  error_Hum = iaqSensor.humidity - sp_H;//Calculo del error

  //----- ECUACION DE DIFERENCIAS (PID) -----
  cv_Hum = cv1_Hum + (Kp_Hum + Kd_Hum / Tm_Hum) * error_Hum + (-Kp_Hum + Ki_Hum * Tm_Hum - 2 * Kd_Hum / Tm_Hum) * error1_Hum + (Kd_Hum / Tm_Hum) * error2_Hum;

  // ----- ECUACION DE DIFERENCIAS (PI) -----
  // cv_Hum = cv1_Hum + (Kp_Hum + Ki_Hum * Tm_Hum) * error_Hum - (Kp_Hum - Ki_Hum * Tm_Hum) * error1_Hum;

  //Recursividad
  cv1_Hum = cv_Hum;
  error2_Hum = error1_Hum;  //PID
  //error1_Hum = error_Hum; //PI
  /*  NOTA:
       para PI solo se usa la linea de: error1 = error; //PI
       mientras que para el PID: error2 = error1;  error1 = error;
  */

  // Limite de salida del controlador
  cv_Hum = constrain(cv_Hum, val_min_HTG, val_max_HTG);    //salida maxima sera el 100%
  Pot_Hum = cv_Hum;   //Asignacion a la entrada de la planta.

  valor_2 = map(Pot_Hum, 0, 100, 0 , 255 );
  dim.write(1, valor_2);
}


////////////////////////////////////////////////CONTROLADOR TEMP_EXT////////////////////////////////////////////
void LC_PI_TEMP() {

  error_Temp = iaqSensor.temperature - sp_T;//Calculo del error

  //----- ECUACION DE DIFERENCIAS (PID) -----
  cv_Temp = cv1_Temp + (Kp_Temp + Kd_Temp / Tm_Temp) * error_Temp + (-Kp_Temp + Ki_Temp * Tm_Temp - 2 * Kd_Temp / Tm_Temp) * error1_Temp + (Kd_Temp / Tm_Temp) * error2_Temp;

  // ----- ECUACION DE DIFERENCIAS (PI) -----
  // cv_Temp = cv1_Temp + (Kp_Temp + Ki_Temp * Tm_Temp) * error_Temp - (Kp_Temp - Ki_Temp * Tm_Temp) * error1_Temp;

  //Recursividad
  cv1_Temp = cv_Temp;
  error2_Temp = error1_Temp;  //PID
  //error1_Temp = error_Temp; //PI
  /*  NOTA:
       para PI solo se usa la linea de: error1 = error; //PI
       mientras que para el PID: error2 = error1;  error1 = error;
  */

  // Limite de salida del controlador
  cv_Temp = constrain(cv_Temp, val_min_HTG, val_max_HTG);
  Pot_Temp = cv_Temp;   //Asignacion a la entrada de la planta.

  valor_3 = map(Pot_Temp, 0, 100, 0 , 255 );
  dim.write(1, valor_3);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////CONTROLADOR CO2//////////////////////////////

void LC_PI_CO2() {

  error_CO2 = iaqSensor.co2Equivalent - sp_G;//Calculo del error

  //----- ECUACION DE DIFERENCIAS (PID) -----
  //cv_CO2 = cv1_CO2 + (Kp_CO2 + Kd_CO2 / Tm_CO2) * error_CO2 + (-Kp_CO2 + Ki_CO2 * Tm_CO2 - 2 * Kd_CO2 / Tm_CO2) * error1_CO2 + (Kd_CO2 / Tm_CO2) * error2_CO2;

  // ----- ECUACION DE DIFERENCIAS (PI) -----
  cv_CO2 = cv1_CO2 + (Kp_CO2 + Ki_CO2 * Tm_CO2) * error_CO2 - (Kp_CO2 - Ki_CO2 * Tm_CO2) * error1_CO2;

  //Recursividad
  cv1_CO2 = cv_CO2;
  //error2_CO2 = error1_CO2;  //PID
  error1_CO2 = error_CO2; //PI
  /*  NOTA:
       para PI solo se usa la linea de: error1 = error; //PI
       mientras que para el PID: error2 = error1;  error1 = error;
  */

  // Limite de salida del controlador
  cv_CO2 = constrain(cv_CO2, val_min_HTG, val_max_HTG);
  Pot_CO2 = cv_CO2;   //Asignacion a la entrada de la planta.

  valor_4 = map(Pot_CO2, 0, 100, 0 , 255 );
  dim.write(1, valor_4);
}
