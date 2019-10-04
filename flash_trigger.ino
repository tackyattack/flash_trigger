int threshold = 30;
int delay_amount_ms = 10;

int arm_button = 3;
int trigger_pin = 4;
int trigger_level = 0;
int sensor_value = 0;
int incoming = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(arm_button, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(trigger_pin, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
  Serial.setTimeout(0);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_value = analogRead(A0);
  Serial.println(sensor_value);
  if(Serial.available()) 
  {
    incoming = Serial.parseInt();
    threshold = incoming;
    Serial.print("Threshold set at: ");
    Serial.println(threshold);
    delay(1000);
    while(Serial.read() != -1);
  }
  delay(100);
  
  if(digitalRead(arm_button))
  {
    Serial.println("Change delay ms? Set now.");
    delay(5000);
    if(Serial.available()) 
    {
      delay_amount_ms = Serial.parseInt();
      Serial.print("Delay set at: ");
      Serial.println(delay_amount_ms);
      while(Serial.read() != -1);
    }
    
    delay(1000);
    trigger_level = analogRead(A0);
    sensor_value = trigger_level;
    Serial.print("ARMED AT: ");
    Serial.print(trigger_level);
    Serial.print("    delaying flash for: ");
    Serial.print(delay_amount_ms);
    Serial.println("ms");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    while(!digitalRead(arm_button) && (sensor_value < trigger_level+threshold) && (sensor_value > trigger_level-threshold))
    {
      sensor_value = analogRead(A0);
    }

    delay(delay_amount_ms);
    digitalWrite(trigger_pin, HIGH);
    delay(100);
    digitalWrite(trigger_pin, LOW);

    while(digitalRead(arm_button)) delay(25);
  }

  digitalWrite(LED_BUILTIN, LOW);
  
  
}
