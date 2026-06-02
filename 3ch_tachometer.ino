const int tacho1 = 2;
const int tacho2 = 3;
const int tacho3 = 18;

volatile unsigned int pulse1 = 0;
volatile unsigned int pulse2 = 0;
volatile unsigned int pulse3 = 0;

unsigned long past_time = 0;

void setup() {
  Serial.begin(9600);

  pinMode(tacho1, INPUT_PULLUP);
  pinMode(tacho2, INPUT_PULLUP);
  pinMode(tacho3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(tacho1), pulse_count1, FALLING);
  attachInterrupt(digitalPinToInterrupt(tacho2), pulse_count2, FALLING);
  attachInterrupt(digitalPinToInterrupt(tacho3), pulse_count3, FALLING);

  Serial.println("3-Channel RPM Measurement");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - past_time >= 1000) {   // Update every 1 second
    past_time = currentTime;

    noInterrupts();
    unsigned int p1 = pulse1;
    unsigned int p2 = pulse2;
    unsigned int p3 = pulse3;

    pulse1 = 0;
    pulse2 = 0;
    pulse3 = 0;
    interrupts();

    // Assuming 2 pulses per revolution
    float rpm1 = (p1 * 60.0) / 2.0;
    float rpm2 = (p2 * 60.0) / 2.0;
    float rpm3 = (p3 * 60.0) / 2.0;

    Serial.print("RPM1: ");
    Serial.print(rpm1, 0);

    Serial.print(" | RPM2: ");
    Serial.print(rpm2, 0);

    Serial.print(" | RPM3: ");
    Serial.println(rpm3, 0);
  }
}

// Interrupt Service Routines
void pulse_count1() {
  pulse1++;
}

void pulse_count2() {
  pulse2++;
}

void pulse_count3() {
  pulse3++;
}
