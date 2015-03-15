const int RedLEDPin = 11;
const int GreenLEDPin = 9;
const int BlueLEDPin = 10;
const int RedSensorPin = A0;
const int GreenSensorPin = A1;
const int BlueSensorPin = A2;
const int LogRefreshFrecuency = 2000;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;
int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

int count = 0;

void setup()
{
	Serial.begin(9600);

	pinMode(RedLEDPin, OUTPUT);
	pinMode(GreenLEDPin, OUTPUT);
	pinMode(BlueLEDPin, OUTPUT);
}

void loop()
{
	redSensorValue = analogRead(RedSensorPin);
	delay(5);
	greenSensorValue = analogRead(GreenLEDPin);
	delay(5);
	blueSensorValue = analogRead(BlueLEDPin);

	redValue = redSensorValue / 4;
	greenValue = greenSensorValue / 4;
	blueValue = blueSensorValue / 4;

	ActualizarLedRGB();

	count += 10;
	if (count >= LogRefreshFrecuency)
	{
		PrintSensorValues();
		PrintMappedValues();
		Serial.println();
		count = 0;
	}
}

void ActualizarLedRGB()
{
	analogWrite(RedLEDPin, redValue);
	analogWrite(GreenLEDPin, greenValue);
	analogWrite(BlueLEDPin, blueValue);
}

void PrintSensorValues()
{
	Serial.print("Raw Sensor Values \t Red: ");
	Serial.print(redSensorValue);
	Serial.print("\t Green: ");
	Serial.print(greenSensorValue);
	Serial.print("\t Blue: ");
	Serial.println(blueSensorValue);
}
void PrintMappedValues()
{
	Serial.print("Mapped Sensor Values \t Red: ");
	Serial.print(redValue);
	Serial.print("\t Green: ");
	Serial.print(greenValue);
	Serial.print("\t Blue: ");
	Serial.println(blueValue);
}