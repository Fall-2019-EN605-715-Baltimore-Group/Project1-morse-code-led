#define MORSE_LED 13

/*
 * Blink the built-in LED once with an input for wait time in MS
 */
void blink(unsigned wait) {
  digitalWrite(MORSE_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(wait);                       // wait 
  digitalWrite(MORSE_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(200);  
}

void dot(unsigned repeats) {
  for (unsigned i = 0; i < repeats; i++) 
    blink(200);
}

void dash(unsigned repeats) {
  for (unsigned i = 0; i < repeats; i++) 
    blink(600);
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
      delay(500);
      Serial.print("Received an invalid character!: [");
      Serial.print(c);
      Serial.println("]");
  }
}

/*
 * Main Setup
 */
void setup() {
    // initialize the serial port - to capture input
    Serial.begin(9600);
    delay(50);
    
    // initialize the LED Pin for output
    pinMode(MORSE_LED, OUTPUT);


    while(!Serial) {} 
    
    Serial.println("Setup Complete!");
}

bool validate_string(String s) {
  if (s.length() < 1) {
    Serial.println("Invalid string! Length: 0");
    return false;
  }
  return true;
}

/* 
 * The Main Loop
 */
void loop() {
  bool valid_input = false;
  String input_string = "";
  while (!valid_input) {
    //Serial.setTimeout(20000); // Set input timeout to 20 seconds (really long)
    Serial.println("Enter a string to output in morse code (a-z, 0-9): ");
    input_string = Serial.readString();
    input_string.trim();
    input_string.toLowerCase();
    Serial.print("Got string: ");
    Serial.println(input_string);
    valid_input = validate_string(input_string);
  }
  Serial.println("Outputing String... press ctrl-z to exit.");
  //Serial.setTimeout(1500);
  unsigned input_char = (unsigned)0;
  // Start over on Control-Z
  while (input_char != 0x1A) { 
    // Iterate over input string
    for (int char_index = 0; char_index < input_string.length(); char_index++) {
      // If user input char is sentinal, exit display loop
      if (input_string.charAt(char_index) == 0x1A) {
        break;
      }
      // blink morse code for each character
      char_to_morse(input_string.charAt(char_index));
      input_char = Serial.read();
      Serial.print("checking for ctrl-z... Got val: ");
      Serial.print(input_char);
      Serial.println();
      if (input_char == 0x1A) {
        break;
      }
    }
  }
}
