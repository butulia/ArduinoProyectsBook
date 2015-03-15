const int keyPin = A0;
const int piezoPin = 8;

int notes[] = { 262, 294, 330, 349 }; //Notas C, D, E y F respectivamente

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	int keyVal = analogRead(keyPin);
	Serial.println(keyVal);

	if (keyVal == 1023)
	{
		tone(piezoPin, notes[0]);
	}
	else if (keyVal < 1023 && keyVal >= 990)
	{
		tone(piezoPin, notes[1]);
	}
	else if (keyVal < 990 && keyVal >= 505)
	{
		tone(piezoPin, notes[2]);
	}
	else if (keyVal < 505 && keyVal >= 3)
	{
		tone(piezoPin, notes[3]);
	}
	else
	{
		noTone(piezoPin);
	}
	delay(10);
}
