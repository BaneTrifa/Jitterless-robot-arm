
  int min_pulse = 200000;
  int max_pulse = 0;
  int max_delta = 0;
  int min_delta = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pulse_value = pulseIn(7, HIGH);
  

  if(min_pulse > pulse_value && pulse_value > 0)
    min_pulse = pulse_value;

  if(max_pulse < pulse_value)
    max_pulse = pulse_value;

  if(max_pulse - pulse_value > max_delta)
    max_delta = max_pulse - pulse_value;

  if(pulse_value - min_pulse > min_delta)
    min_delta = pulse_value - min_pulse;

  Serial.print("MAX: ");
  Serial.println(max_pulse);

  Serial.print("MIN: ");
  Serial.println(min_pulse);

  Serial.print("CURR: ");
  Serial.println(pulse_value);

  
  Serial.print("MIN DELTA: ");
  Serial.println(min_delta);
  
  Serial.print("MAX DELTA: ");
  Serial.println(max_delta);

  Serial.println("================================");
}
