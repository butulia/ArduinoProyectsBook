const int SENSORPIN = A0;
const int GREEN1PIN = 2;
const int GREEN2PIN = 3;
const int YELLOW1PIN = 4;
const int YELLOW2PIN = 5;
const int RED1PIN = 6;
const int RED2PIN = 7;
const int BASEINC[] = { 2, 4, 6, 8, 10, 12 };
const int FRECUENCIAMUESTREO = 500;

const float BASELINETEMP = 23.0;

int count = 0;
float mediaSensor = 0.0;

void setup()
{
  Serial.begin(9600);  // open a serial port

  for (int pinNumber = GREEN1PIN; pinNumber <= RED2PIN; pinNumber++)
  {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }

  count = 0;
  mediaSensor = 0.0;
}

void loop()
{
  /*
  // Read the sensor value
  int sensorValue = analogRead(SENSORPIN);
  // Convert the ADC value to voltage
  float sensorVoltage = (sensorValue / 1024.0) * 5.0;
  // Convert the voltage to temperature en degrees
  float temperature = (sensorVoltage - .5) * 100;
  */
  mediaSensor += analogRead(SENSORPIN);
  delay(1);
  count++;

  if (count >= FRECUENCIAMUESTREO) {
    mediaSensor = mediaSensor / count;
    float sensorVoltage = (mediaSensor / 1024.0) * 5.0;
    float temperature = (sensorVoltage - .5) * 100;

    ImprimirSerial(mediaSensor, sensorVoltage, temperature);
    ActualizarLeds(temperature);
    count = 0;
    mediaSensor = 0.0;
  }
}

void ActualizarLeds(float temperature)
{
  if (temperature < BASELINETEMP)
  {
    EnciendeHasta(0);
  }
  else if (temperature >= BASELINETEMP && temperature < BASELINETEMP + BASEINC[0])
  {
    EnciendeHasta(GREEN1PIN);
  }
  else if (temperature >= BASELINETEMP + BASEINC[0] && temperature < BASELINETEMP + BASEINC[1])
  {
    EnciendeHasta(GREEN2PIN);
  }
  else if (temperature >= BASELINETEMP + BASEINC[1] && temperature < BASELINETEMP + BASEINC[2])
  {
    EnciendeHasta(YELLOW1PIN);
  }
  else if (temperature >= BASELINETEMP + BASEINC[2] && temperature < BASELINETEMP + BASEINC[3])
  {
    EnciendeHasta(YELLOW2PIN);
  }
  else if (temperature >= BASELINETEMP + BASEINC[3] && temperature < BASELINETEMP + BASEINC[4])
  {
    EnciendeHasta(RED1PIN);
  }
  else if (temperature >= BASELINETEMP + BASEINC[4])// && temperature < BASELINETEMP + BASEINC[5])
  {
    EnciendeHasta(RED2PIN);
  }
}

void ImprimirSerial(int sensorValue, float voltage, float temperature) {
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(", Volts: ");
  Serial.print(voltage);
  Serial.print(", C: ");
  Serial.println(temperature); 
}

void EnciendeHasta(int pinNumber) {
  for (int pin = GREEN1PIN; pin <= pinNumber; pin++)
  {
    digitalWrite(pin, HIGH);
  }
  for (int pin = pinNumber + 1; pin <= RED2PIN; pin++)
  {
    digitalWrite(pin, LOW);
  }
}
