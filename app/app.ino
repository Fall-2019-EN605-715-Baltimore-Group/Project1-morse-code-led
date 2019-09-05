/*
 * Blink the built-in LED once with an input for wait time in MS
 */
void blink(unsigned wait) {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(wait);                       // wait 
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(wait);  
}

void dot(unsigned repeats) {
  for (unsigned i = 0; i < repeats; i++) 
    blink(250);
}

void dash(unsigned repeats) {
  for (unsigned i = 0; i < repeats; i++) 
    blink(500);
}

// Blink out the morse code for a single input character. 
void char_to_morse(char c) {
  Serial.print("outputing morse code for '");
  Serial.print(c);
  Serial.println("'");
  
  switch(c) {
    case ' ': delay(500);
    case 'a': dot(1); dash(1); break;
    case 'b': dash(1); dot(3); break;
    case 'c': dash(1); dot(1); dash(1); dot(1); break;
    case 'd': dash(1); dot(2); break;
    case 'e': dot(1); break;
    case 'f': dot(2); dash(1); dot(1); break;
    case 'g': dash(2); dot(1); break;
    case 'h': dot(4); break;
    case 'i': dot(2); break;
    case 'j': dot(1); dash(3); break;
    case 'k': dash(1); dot(1); dash(1); break;
    case 'l': dot(1); dash(1); dot(2); break;
    case 'm': dash(2); break;
    case 'n': dash(1); dot(1); break;
    case 'o': dash(3); break;
    case 'p': dot(1); dash(2); dot(1); break;
    case 'q': dash(2); dot(1); dash(1); break;
    case 'r': dot(1); dash(1); dot(1); break;
    case 's': dot(3); break;
    case 't': dash(1); break;
    case 'u': dot(2); dash(1); break;
    case 'v': dot(3); dash(1); break;
    case 'w': dot(1); dash(2); break;
    case 'x': dash(1); dot(2); dash(1); break;
    case 'y': dash(1); dot(1); dash(2); break;
    case 'z': dash(2); dot(2); break;
    case '1': dot(1); dash(4); break;
    case '2': dot(2); dash(3); break;
    case '3': dot(3); dash(2); break;
    case '4': dot(4); dash(1); break; 
    case '5': dot(5);  break;
    case '6': dash(1); dot(4); break;
    case '7': dash(2); dot(3); break;
    case '8': dash(3); dot(2); break;
    case '9': dash(4); dot(1); break;
    case '0': dash(5); break;
    default:
      Serial.print("Received an invalid character!: [");
      Serial.print(c);
      Serial.println("]");
  }
}

/*
 * Main Setup
 */
void setup() {
	  // initialize the LED Pin for output
    pinMode(LED_BUILTIN, OUTPUT);
    
    // initialize the serial port - to capture input
    Serial.begin(9600);

    Serial.println("Setup Complete!");
}

/* 
 * The Main Loop
 */
void loop() {
  //Serial.setTimeout(20000); // Set input timeout to 20 seconds (really long)
  Serial.println("Enter a string to output in morse code (a-z, 0-9): ");
  String input_string = Serial.readString();
  Serial.print("Got string: ");
  Serial.println(input_string);
  Serial.println("Outputing String... press ctrl-z to exit.");

  Serial.setTimeout(1500);
  unsigned input_char = (unsigned)0;
  // Start over on Control-Z
  while (input_char != 0x1A) { 
    // Iterate over input string
    for (int char_index = 0; char_index < input_string.length(); char_index++) {
      // blink morse code for each character
      char_to_morse(input_string.charAt(char_index));
    }
    input_char = Serial.read();
  }
}
