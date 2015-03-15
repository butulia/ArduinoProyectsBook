#include <Servo.h>

Servo myServo;

const int PotPin = A0;
const int ServoPin = 11;
const int LapsoMedia = 20;

int potVal;
int angle;
int lastAngle;
int media;
int count;
int mod;

void setup()
{
	myServo.attach(ServoPin);
	Serial.begin(9600);

	count = 0;
	media = 0;
	lastAngle = -1;
}

void loop()
{
	potVal = analogRead(PotPin);
	media += potVal;
	delay(1);
	count++;
	if (count >= LapsoMedia)
	{
		potVal = media / LapsoMedia;
		angle = map(potVal, 0, 1023, 0, 169);
		PrintSerial();
		if (angle != lastAngle){
			myServo.write(angle);
			lastAngle = angle;
		}
		media = 0;
		count = 0;
	}
}

void PrintSerial()
{
	Serial.print("Pot Value: ");
	Serial.print(potVal);
	Serial.print(" , angle: ");
	Serial.println(angle);
}