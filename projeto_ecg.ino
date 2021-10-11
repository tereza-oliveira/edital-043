#include "ADS1X15.h"
#include "MCP4725.h"
#include <Wire.h>

// Declarando variáveis do filtro passa-alta
float x1_pa = 0.0;
float x2_pa = 0.0;
float y_pa = 0.0;
float yl_pa = 0.0;
float y2_pa = 0.0;

// Declarando variáveis do filtro passa-alta
float x1_notch = 0.0;
float x2_notch = 0.0;
float y_notch = 0.0;
float yl_notch = 0.0;
float y2_notch = 0.0;

// Declarando variáveis do filtro passa-alta
float x1_pb = 0.0;
float x2_pb = 0.0;
float y_pb = 0.0;
float yl_pb = 0.0;
float y2_pb = 0.0;

void setup() {
  Serial.begin(9600);

  // Conversor analogico digital
  ADS113 ADS(0x48) //conectado ao pino GND
  ADS.begin()
  void setMode(uint8_t 0) //modo contínuo
  void setDataRate(uint8_t 6) //setando datarate para 475

  MCP4725 MCP(0x48);
  
  Fs = 475;
}

void loop() {
  // O sinal eh recebido do conversor, e em seguida sao realizadas as filtragens
  // Filtro passa-alta
  x_adc = int16_t readADC(uint8_t 0);
  x_pa = (float)x_adc;
  y_pa = filter_pa(x_pa);
  // Filtro notch
  x_nt = y_pa;
  y_nt = filter_notch(x_nt);
  // Filtro passa-baixa
  x_pb = y_nt;
  y_pb = filter_pb(x_pb);
  
  // Envio do sinal filtrado para o conversor digital/analogico e, em seguida, sera apresentado em osciloscopio
  MCP.begin();
  MCP.setValue(y_pb);
  
  delay(10);
}

// Filtro passa-alta
float filter_pa(float x){
  y = 1*x + (-2)*x1_pa + 1*x2_pa - 1*yl_pa - (-1.99)*y2_pa - 0.99*y3_pa;
  y2_pa = yl_pa;
  yl_pa = y;
  x2_pa = x1_pa;
  x1_pa = x;
  return y;
}

// Filtro notch
float filter_notch(float x){
  y = 1*x + (-1.46)*x1_notch + 1*x2_notch - 0*yl_notch - (-1.43)*y2_notch - (0.96)*y3_notch;
  y2_notch = yl_notch;
  yl_notch = y;
  x2_notch = x1_notch;
  x1_notch = x;
  return y;
}

// Filtro passa-baixa
float filter_pb(float x){
  y = 1*x + 2*x1_pb + 1*x2_pb - 1*yl_pb - (-0.37)*y2_pb - 0.2*y3_pb;
  y2_pb = yl_pb;
  yl_pb = y;
  x2_pb = x1_pb;
  x1_pb = x;
  return y;
}
