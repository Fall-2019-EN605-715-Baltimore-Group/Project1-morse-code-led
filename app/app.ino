/*
 * Blink the built-in LED once with an input for wait time in MS
 */
void blink(unsigned wait) {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(wait);                       // wait 
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(wait);  
}

void blink_dot(void) {
    blink(250);
}

void blink_dash(void) {
    blink(500);
}

void char_to_morse(char c) {}

/*
 * Main Setup
 */
void setup() {
	// initialize the LED Pin for output
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

/* 
 * The Main Loop
 */
void loop() {
    // S
    blink_dot();
    blink_dot();
    blink_dot();
    Serial.print("S");

    // O
    blink_dash();
    blink_dash();
    blink_dash();
    Serial.print("O");

    // S
    blink_dot();
    blink_dot();
    blink_dot();
    Serial.print("S");

    Serial.println("");
    delay(1500);
}
