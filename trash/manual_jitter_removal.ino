// Include the Servo library 
#include <Servo.h> 

typedef volatile unsigned long int t_time;

// Declare the Servo pin 
int servoPin0 = 10;
int servoPin1 = 11;
int servoPin2 = 12;
int servoPin3 = 13; 

// sw pwm rpi
int rpiPin0 = 2;
int rpiPin1 = 3;
int rpiPin2 = 4;
int rpiPin3 = 8;

//margina greske u procentima
float tol = 1;

bool jitter_remove;

t_time t_start[4];
t_time t_duty[4];
t_time T[4];

int sd[4] = {0};

volatile float duty[4];
volatile float new_duty[4];
volatile bool edge[4] = {false};

Servo Servos[4];

 
void setup() { 
	Serial.begin(9600);

	jitter_remove = false;
	
	Servos[0].attach(servoPin0);
	Servos[1].attach(servoPin1);
	Servos[2].attach(servoPin2);
	Servos[3].attach(servoPin3);

	//hw interrupt
	pinMode(rpiPin0, INPUT);
	pinMode(rpiPin1, INPUT);
	attachInterrupt(digitalPinToInterrupt(rpiPin0), pin_ISR0, CHANGE);
	attachInterrupt(digitalPinToInterrupt(rpiPin1), pin_ISR1, CHANGE);
	
	//sw interrupt
	PCMSK0 |= (1 << PCINT0); // PB, pin8
	PCMSK2 |= (1 << PCINT20); // PD, pin4
	PCICR |= B00000101;
}


void loop(){ 

	if(jitter_remove){
	int angle[4];
	
	int i;
	for(i = 0; i <= 3; ++i) {
		if(duty[i] != 0)
			angle[i] = (duty[i] - 2.5) / 10 * 180;
	   	else
	   		angle[i] = 0;
	
	   	if(angle[i] < 0) 
	   		angle[i] = 0;
	
	   	if(angle[i] > 180) 
	   		angle[i] = 180;
	   	
	   	Serial.print("s");
	   	Serial.print(i);
	   	Serial.print(": ");
		Serial.println(angle[i]);
		
	   Servos[i].write(angle[i]); 	   
	}
	jitter_remove = false;
	}
}

void pin_ISR0() {
  if(digitalRead(rpiPin0) == HIGH && sd[0] == 0)
  {
  	if(edge[0] == false){
  		
	  	t_start[0] = micros();
	  	edge[0] = true;
	  	
  	}
  	else
  	{
  		
  		T[0] = micros() - t_start[0];
		new_duty[0] = (float)t_duty[0] / T[0] * 100;

		/*Serial.print("T: ");
		Serial.println(T[0]);
		Serial.print("t_duty: ");
		Serial.println(t_duty[0]);*/
		
		if(abs(duty[0] - new_duty[0]) > tol)
  			duty[0] = new_duty[0];
  			
  		edge[0] = false;

  	}

	
  	sd[0] = 1;
  }

  if(digitalRead(rpiPin0) == LOW && sd[0] == 1)
  {
	unsigned long current = micros();
	if(edge[0] == true && current != t_start[0])
	{
  		t_duty[0] = micros() - t_start[0];
	}
  	
	sd[0] = 0;
  }
  
}

void pin_ISR1() {
	if(digitalRead(rpiPin1) == HIGH && sd[1] == 0)
  {
  	if(edge[1] == false){
  		
	  	t_start[1] = micros();
	  	edge[1] = true;
	  	
  	}
  	else
  	{
  		T[1] = micros() - t_start[1];
		new_duty[1] = (float)t_duty[1] / T[1] * 100;
		
		if(abs(duty[1] - new_duty[1]) > tol)
		{
  			duty[1] = new_duty[1];
  			jitter_remove = true;
		}	
  		edge[1] = false;

  	}

	
  	sd[1] = 1;
  }

  if(digitalRead(rpiPin1) == LOW && sd[1] == 1)
  {
	unsigned long current = micros();
	if(edge[1] == true && current != t_start[1])
	{
  		t_duty[1] = micros() - t_start[1];
	}
  	
	sd[1] = 0;
  }
	
}

ISR(PCINT2_vect) {
	if(digitalRead(rpiPin2) == HIGH && sd[2] == 0)
  {
  	if(edge[2] == false){
  		
	  	t_start[2] = micros();
	  	edge[2] = true;
	  	
  	}
  	else
  	{
 
  		T[2] = micros() - t_start[2];
		new_duty[2] = (float)t_duty[2] / T[2] * 100;
		
		if(abs(duty[2] - new_duty[2]) > tol)
  			duty[2] = new_duty[2];
  			
  		edge[2] = false;

  	}

	
  	sd[2] = 1;
  }

  if(digitalRead(rpiPin2) == LOW && sd[2] == 1)
  {
	unsigned long current = micros();
	if(edge[2] == true && current != t_start[2])
	{
  		t_duty[2] = micros() - t_start[2];
	}
  	
	sd[2] = 0;
  }
	
}

ISR(PCINT0_vect) {
	if(digitalRead(rpiPin3) == HIGH && sd[3] == 0)
  {
  	if(edge[3] == false){
  		
	  	t_start[3] = micros();
	  	edge[3] = true;
	  	
  	}
  	else
  	{
  		T[3] = micros() - t_start[3];
		new_duty[3] = (float)t_duty[3] / T[3] * 100;
		
		if(abs(duty[3] - new_duty[3]) > tol)
  			duty[3] = new_duty[3];
  			
  		edge[3] = false;

  	}

	
  	sd[3] = 1;
  }

  if(digitalRead(rpiPin3) == LOW && sd[3] == 1)
  {
	unsigned long current = micros();
	if(edge[3] == true && current != t_start[3])
	{
  		t_duty[3] = micros() - t_start[3];
	}
  	
	sd[3] = 0;
  }
	
}
