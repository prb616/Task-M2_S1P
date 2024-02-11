//name : Prabhjot Singh
// ROll NO. : 2210994884

// Define the LED pin number (digital pin 13)
const byte LED_PIN = 13;

// Define the meter pin number (analog input pin A4)
const byte METER_PIN = A4;

// Function declaration for startTimer()
void startTimer();

void setup() {
 // Set the LED pin as an output
 pinMode(LED_PIN, OUTPUT);

 // Set the meter pin as an input
 pinMode(METER_PIN, INPUT);

 // Initialize serial communication with a baud rate of 9600
 Serial.begin(9600);

 // Call the startTimer() function
 startTimer();
}

void loop() {
 // Main loop, no code provided
}

// Function definition for startTimer()
void startTimer() {
 // Disable all interrupts
 cli();

 // Set CTC (Clear Timer on Compare Match) mode
 TCCR1A = 0;
 TCCR1B = 0;
 TCNT1 = 0; // Initialize counter value to 0

 // Set compare match register for 2Hz increments
 OCR1A = 15624; // = 16e6 / (2 * 1024) - 1 (we want a 2Hz frequency)

 // Enable compare match interrupt
 TIMSK1 |= (1 << OCIE1A);

 // Set prescaler 1024 and start the timer
 TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);

 // Enable all interrupts
 sei();
}

// Interrupt Service Routine (ISR) for TIMER1_COMPA_vect
ISR(TIMER1_COMPA_vect) {
 // Toggle the LED state
 digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}
