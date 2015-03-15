const int pulsador = 2;
const int ledVerde = 3;
const int ledRojo1 = 4;
const int ledRojo2 = 5;
const int LAPSOROJO1 = 300;
const int LAPSOROJO2 = 500;
const int LAPSOPARPADEOMAXIMO = 150;
const int LAPSOPARPADEOMINIMO = 20;
const int NUMEROCLICLOSPARACAMBIAR = 3;
const int MILISEGUNDOSCAMBIOPARPADEO = 10;

int estado = 0;
int time = 0;
int count = 0;
int lapsoParpadeoActual = LAPSOPARPADEOMAXIMO;

bool rojo1Completo = false;
bool rojo2Completo = false;
bool rojo1Encendido = false;
bool acelera = true;

void setup() {
	// put your setup code here, to run once:
	pinMode(ledVerde, OUTPUT);
	pinMode(ledRojo1, OUTPUT);
	pinMode(ledRojo2, OUTPUT);
	pinMode(pulsador, INPUT);
	for (int i = ledVerde; i <= ledRojo2; i++)
	{
		digitalWrite(i, LOW);
	}
	digitalWrite(ledVerde, HIGH);
}

void loop() {
	// put your main code here, to run repeatedly:
	estado = digitalRead(2);

	if (estado == LOW)
	{
		// boton no presionado
		digitalWrite(ledVerde, HIGH);
		digitalWrite(ledRojo1, LOW);
		digitalWrite(5, LOW);

		// seteo variables control para reiniciar ciclo
		rojo1Completo = false;
		rojo2Completo = false;
		rojo1Encendido = false;
		time = 0;
		count = 0;
		lapsoParpadeoActual = LAPSOPARPADEOMAXIMO;
		acelera = true;
	}
	else{
		digitalWrite(ledVerde, LOW);
		// boton presionado
		if (!rojo1Completo){
			digitalWrite(ledRojo1, HIGH);

			if (time >= LAPSOROJO1){
				rojo1Completo = true;
				time = 0;
			}
		}
		else if (rojo1Completo && !rojo2Completo)
		{
			digitalWrite(ledRojo1, LOW);
			digitalWrite(ledRojo2, HIGH);

			if (time >= LAPSOROJO2){
				rojo2Completo = true;
				time = 0;
			}
		}
		else{
			if (rojo1Encendido){
				digitalWrite(ledRojo1, LOW);
				digitalWrite(ledRojo2, HIGH);
			}
			else{
				digitalWrite(ledRojo1, HIGH);
				digitalWrite(ledRojo2, LOW);
			}

			if (time >= lapsoParpadeoActual){
				rojo1Encendido = !rojo1Encendido;
				time = 0;
				count++;

				if (count >= NUMEROCLICLOSPARACAMBIAR)
				{
					if (acelera){
						lapsoParpadeoActual -= MILISEGUNDOSCAMBIOPARPADEO;
					}
					else{
						lapsoParpadeoActual += MILISEGUNDOSCAMBIOPARPADEO;
					}
					count = 0;
				}

				if (lapsoParpadeoActual < LAPSOPARPADEOMINIMO || lapsoParpadeoActual > LAPSOPARPADEOMAXIMO){
					acelera = !acelera;
				}
				
				//if (count >= NUMEROCLICLOSPARAACELERAR)
				//{
				//	lapsoParpadeoActual -= MILISEGUNDOSCAMBIOPARPADEO;
				//	count = 0;

				//	if (lapsoParpadeoActual < LAPSOPARPADEOMINIMO){
				//		lapsoParpadeoActual = LAPSOPARPADEOMAXIMO;
				//	}
				//}
			}
		}

		delay(1);
		time++;
	}
}