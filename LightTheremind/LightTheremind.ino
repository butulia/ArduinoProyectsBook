int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

const int ledPin = 13;
const int sensorPin = A0;
const int piezoPin = 8;
const int minFrec = 50;
const int maxFrec = 4000;
const int noteDuration = 20;
const int delayDuration = 10;

void setup()
{
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, HIGH);

	while (millis() < 5000)
	{
		sensorValue = analogRead(sensorPin);
		if (sensorValue > sensorHigh)
		{
			sensorHigh = sensorValue;
		}
		if (sensorValue < sensorLow)
		{
			sensorLow = sensorValue;
		}
	}

	digitalWrite(ledPin, LOW);
}

void loop()
{
	sensorValue = analogRead(sensorPin);

	int pitch = map(sensorValue, sensorLow, sensorHigh, minFrec, maxFrec);

	tone(piezoPin, pitch, noteDuration);

	delay(delayDuration);
}
