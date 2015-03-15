//const int switchPin = 2;
const int potentiometerPin = A0;
const int motorPin = 9;
const int dataRefreshFrequency = 100;

//int switchState = 0;
unsigned long lastMillis = 0;

void setup()
{
	Serial.begin(9600);
	//pinMode(switchPin, INPUT);
	pinMode(motorPin, OUTPUT);
}

void loop()
{
	//switchState = digitalRead(switchPin);
	//digitalWrite(motorPin, switchState);
	int potVal = 1023 - analogRead(potentiometerPin);
	int motorVal = map(potVal, 0, 1023, 0, 255);
	int powerPercent = map(potVal, 0, 1023, 0, 100);

	if (millis() - lastMillis > dataRefreshFrequency)
	{
		PrintData(potVal, motorVal, powerPercent);
		lastMillis = millis();
	}

	analogWrite(motorPin, motorVal);
}

void PrintData(int potVal, int motorVal, int powerPercent)
{
	Serial.print("Pot Val: ");
	Serial.print(potVal);
	Serial.print(" Motor Val: ");
	Serial.print(motorVal);
	Serial.print(" Power: ");
	Serial.print(powerPercent);
	Serial.println(" %");
}