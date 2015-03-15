
String frase;

void setup()
{
	Serial.begin(9600);  // open a serial port

	/* add setup code here */

}

void loop()
{
	if (Serial.available() > 0)
	{
		frase = Serial.readStringUntil('\n');
		//frase = Serial.readString();
		Serial.print("Ha escrito: ");
		Serial.println(frase);
	}
}