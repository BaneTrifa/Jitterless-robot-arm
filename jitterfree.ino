#include <Servo.h>

// sw pwm rpi
int rpiPin0 = 8;
int rpiPin1 = 9;
int rpiPin2 = 7;
int rpiPin3 = 10;

// servo pins
int servoPin0 = 3;
int servoPin1 = 5;
int servoPin2 = 6;
int servoPin3 = 11;

Servo Servos[4];
int angle[4];
int curr_pulse[4];
int pulse_value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

	Servos[0].attach(servoPin0);
	Servos[1].attach(servoPin1);
	Servos[2].attach(servoPin2);
	Servos[3].attach(servoPin3);

  angle[0] = 0; angle[1] = 0; angle[2] = 0; angle[3] = 0;
  curr_pulse[0] = 0; curr_pulse[1] = 0; curr_pulse[2] = 0; curr_pulse[3] = 0;
  pulse_value = 0;

  pinMode(rpiPin0, INPUT);
  pinMode(rpiPin1, INPUT);
  pinMode(rpiPin2, INPUT);
  pinMode(rpiPin3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    
    pulse_value = pulseIn(rpiPin0, HIGH);
    if(abs(pulse_value - curr_pulse[0] ) > 200) {
      curr_pulse[0] = pulse_value;
      angle[0] = getAngleFromPulse(curr_pulse[0]);
    }

    pulse_value = pulseIn(rpiPin1, HIGH);
    if(abs(pulse_value - curr_pulse[1] ) > 200) {
      curr_pulse[1] = pulse_value;
      angle[1] = getAngleFromPulse(curr_pulse[1]);
    }
    
    pulse_value = pulseIn(rpiPin2, HIGH);
    if(abs(pulse_value - curr_pulse[2] ) > 200) {
      curr_pulse[2] = pulse_value;
      angle[2] = getAngleFromPulse(curr_pulse[2]);
    }

    pulse_value = pulseIn(rpiPin3, HIGH);
    if(abs(pulse_value - curr_pulse[3] ) > 200) {
      curr_pulse[3] = pulse_value;
      angle[3] = getAngleFromPulse(curr_pulse[3]);
    }


		for(int i = 0; i <= 3; ++i) {
		   	
      Serial.print("s");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(angle[i]);
			
		  Servos[i].write(angle[i]); 	 
		}

    delay(1000);
}

int getAngleFromPulse(int pulse) {
  int angle;
  double duty = pulse/200.0;

  angle = ceil((duty - 2.5) / 10 * 180);

  if(angle < 0) 
    angle = 0;
  else if(angle > 180) 
    angle = 180;

  return angle;
}
