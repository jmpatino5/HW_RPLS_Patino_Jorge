//Tarea 01
//Jorge Mario Patiño Taborda
//08.08.2014
//Sistemas digitales avanzados


#include "EEPROM.h";
const char* opciones[] = {"Rock", "Paper", "Scisorss", "Lizard", "Spock"};

//Se define una clase que es computer, el cual guarda aen dos variables las victorias y las derrotas, así como tres métodos 
class computer
{
	public:
    computer();
	uint8_t victories;
	uint8_t loses;
	float ratio();
	uint8_t juegopc();
};

//Se inicializan las variables del metodo computer
computer::computer()
{
	victories = 0;
	loses = 0;
}

//Se describe el método juegopc de la clase computer, devuelve un entero con la selección del computador
uint8_t computer::juegopc()
{
	uint8_t pc_select = random(0, 4.99);
	Serial.print("Yor foe has selected... ");
	Serial.println(opciones[pc_select]);
	return pc_select;
}



computer AI = computer();

//Esta funcion se encarga de pedirle al usuario la cantidad de partidas y guarda el dato como un int
uint8_t num_matches()
{

	Serial.print("Input the number of matches (one, two or five)");
	uint8_t intmatches = 1;
	
	while(Serial.available())
	{
		String matches = leeropcion();
	    if(matches == "1")
	    {
	       intmatches = 1; 
	    } 
	    if(matches == "3")
	    {
	     intmatches = 3;   
	    }
	    if (matches == "5")
	    {
	    	intmatches ==5;
	    }
	}
	return intmatches;
}

//Se setea la comunicación serial
void setup()
{
	Serial.begin(115200);
	AI.victories = EEPROM.read(10);
	AI.loses = EEPROM.read(11);
}

//Esta función se encarga de preguntar por el movimiento
String preguntar()
{
	Serial.print("make your choice");
	String play = "";
	while(play=="")
	{
	  play = leeropcion(); 
	}
	return play;
}

//Esta función se encarga de recibir y concatenar el input del usuario y devuelve esto en un string
String leeropcion()
{
	String movement = "";
	while(Serial.available())                        
	{                    
	   movement.concat(char(Serial.read()));                   
	   delay(10);
	}
	return movement;
}


//Esta función devuelve el status del usuario en caso de que este lo solicite, o ejecuta el juego dependiendo de su input y la jugada del pc
int winloss()                                   
{
	String usuario = preguntar();

	if(usuario=="status")
	{
	Serial.println("You score is:");  
	Serial.println("the number of total matches is:  totalmatches");
	Serial.println("The number of victories " + String(EEPROM.read(10)));
	Serial.println("The number of loses is: " + String(EEPROM.read(11)));
	Serial.print("\n");
	}
	else
	{
	uint8_t pc = AI.juegopc();
	

if (usuario=="Rock")
 {
 	if ((pc==2)||(pc==3))
 	{
 		Serial.println ("You won!");
 		return 1;
 	}
 	if (pc==0)
 	{
 		Serial.println ("The game is tie!");
 		return 0;
 	}
 	else
 	{
 		Serial.println ("You lose!");
 		return -1;
 	}
 }
  else if (usuario=="Paper")
 {
 	if ((pc==0)||(pc==4))
 	{
 		Serial.println ("You won!");
 		return 1;
 	}
 	if (pc==1)
 	{
 		Serial.println ("The game is tie!");
 		return 0;
 	}
 	else
 	{
 		Serial.println ("You lose!");
 		return -1;
 	}
 }
   else if (usuario=="Scisorss")
 {
 	if ((pc==1)||(pc==3))
 	{
 		Serial.println ("You won!");
 		return 1;
 	}
 	if (pc==2)
 	{
 		Serial.println ("The game is tie!");
 		return 0;
 	}
 	else
 	{
 		Serial.println ("You lose!");
 		return -1;
 	}
 }
   else if (usuario=="Lizard")
 {
 	if ((pc==1)||(pc==4))
 	{
 		Serial.println ("You won!");
 		return 1;
 	}
 	if (pc==3)
 	{
 		Serial.println ("The game is tie!");
 		return 0;
 	}
 	else
 	{
 		Serial.println ("You lose!");
 		return -1;
 	}
 }
    else if (usuario=="spock")
 {
 	if ((pc==0)||(pc==2))
 	{
 		Serial.println ("You won!");
 		return 1;
 	}
 	if (pc==4)
 	{
 		Serial.println ("The game is tie!");
 		return 0;
 	}
 	else
 	{
 		Serial.println ("You lose!");
 		return -1;
 	}
 }

}
}

void loop()
{

uint8_t cont = 0;
uint8_t matches_quantity = num_matches();
bool playing = true;
while (playing == true)
{

	int resultado = winloss();

	if(resultado==1)
	{
	   AI.victories++;
	   cont++;
	   EEPROM.write(10, AI.victories);
	}    
	else if (resultado==-1)
	{
		AI.loses++;
		cont++;
		 EEPROM.write(11, AI.loses);
	}

if(cont == matches_quantity)
{
   playing = false; 
}
}
}

