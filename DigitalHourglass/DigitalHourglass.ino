const int switchPin = 8;

unsigned long previousTime = 0;
unsigned long previousBlinkTime = 0;

int switchState = 0;
int prevSwitchState = 0;
int led = 2;
long interval = 500;
int blinkInterval = 200;
bool blinkPair = true;


void setup()
{
	Serial.begin(9600);
	for (int i = 2; i < 8; i++)
	{
		pinMode(i, OUTPUT);
	}

	pinMode(switchPin, INPUT);
}

void loop()
{
	unsigned currentTime = millis();

	if (currentTime - previousTime > interval)
	{
		previousTime = currentTime;

		if (led <= 7)
		{
			digitalWrite(led, HIGH);
			led++;
		}
	}

	if (led > 7 && currentTime - previousBlinkTime > blinkInterval)
	{
		previousBlinkTime = currentTime;
		if (blinkPair)
		{
			digitalWrite(2, HIGH);
			digitalWrite(4, HIGH);
			digitalWrite(6, HIGH);
			digitalWrite(3, LOW);
			digitalWrite(5, LOW);
			digitalWrite(7, LOW);
		}
		else{
			digitalWrite(2, LOW);
			digitalWrite(4, LOW);
			digitalWrite(6, LOW);
			digitalWrite(3, HIGH);
			digitalWrite(5, HIGH);
			digitalWrite(7, HIGH);
		}
		blinkPair = !blinkPair;
	}

	switchState = digitalRead(switchPin);
	if (switchState != prevSwitchState)
	{
		Serial.println(switchState);
		for (int i = 2; i < 8; i++)
		{
			digitalWrite(i, LOW);
		}

		led = 2;
		previousTime = currentTime;
		previousBlinkTime = currentTime;
	}

	prevSwitchState = switchState;
}
