const int tacho = 2;                // Tachometer signal pin
volatile unsigned int pulse = 0;    // Pulse counter
unsigned long past_time = 0;

void setup() {
  Serial.begin(9600);
  pinMode(tacho, INPUT_PULLUP);
  
  // Trigger interrupt on every FALLING edge of tachometer signal
  attachInterrupt(digitalPinToInterrupt(tacho), pulse_count, FALLING);

  Serial.println("Counting pulses, calculating RPS & RPM...");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - past_time >= 1000) {  // 1 second passed
    past_time = currentTime;

    noInterrupts();
    unsigned int pulseThisSecond = pulse; // Copy pulse count
    pulse = 0;                            // Reset for next second
    interrupts();

    // Calculate revolutions per second and per minute
    float rps = pulseThisSecond / 2.0;         // 2 pulses per revolution
    float rpm = (pulseThisSecond * 60.0) / 2.0;

    // Display results
    Serial.print("Pulses/sec: ");
    Serial.print(pulseThisSecond);
    Serial.print(" | RPS: ");
    Serial.print(rps, 2);
    Serial.print(" | RPM: ");
    Serial.println(rpm, 2);
  }
}

// Interrupt Service Routine
void pulse_count() {
  pulse++;
}

