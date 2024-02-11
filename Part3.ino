// Name : Prabhjot Singh
// Roll No. : 2210994884

// Define the LED_PIN constant with a value of 13, which corresponds to the on-board LED pin on Arduino Uno
const byte LED_PIN = 13;

// Define the METER_PIN constant with a value of A4, which corresponds to the analog input pin A4 on Arduino Uno
const byte METER_PIN = A4;

// Declare the startTimer function with a double parameter timerFrequency
void startTimer(double timerFrequency);

// Setup function that runs once at the beginning
void setup() {
 // Set the LED_PIN as an output
 pinMode(LED_PIN, OUTPUT);
 
 // Set the METER_PIN as an input
 pinMode(METER_PIN, INPUT);
 
 // Initialize the serial communication with a baud rate of 9600
 Serial.begin(9600);
}

// Loop function that runs repeatedly
void loop() {
 // Read the analog value from the potentiometer connected to the METER_PIN
 int sensorValue = analogRead(METER_PIN);
 
 // Map the sensor value to a desired frequency range (e.g., from 0.1 Hz to 10 Hz)
 double desiredFrequency = map(sensorValue, 0, 1023, 1, 100) / 10.0; // Scale the sensor value to the desired frequency range
 
 // Output the desired frequency to the Serial Monitor for debugging
 Serial.print("Desired frequency: ");
 Serial.print(desiredFrequency);
 Serial.println(" Hz");
 
 // Start the timer with the desired frequency
 startTimer(desiredFrequency);
 
 // Delay for 1 second for stability
 delay(1000);
}

// startTimer function that sets up the Timer1 with the desired frequency
void startTimer(double timerFrequency) {
 // Disable all interrupts to ensure the timer setup is not interrupted
 cli();
 
 // Calculate the required value for OCR1A based on the desired frequency
 unsigned long ocrValue = (F_CPU / 1024 / timerFrequency) - 1;
 
 // Ensure the calculated OCR1A value is within the range of 16-bit register (0-65535)
 if (ocrValue < 65536) {
   // Set CTC mode (Clear Timer on Compare Match)
   TCCR1A = 0;
   TCCR1B = 0;
   TCNT1 = 0;  // Initialize counter value to 0
 
   // Set compare match register for the desired frequency
   OCR1A = ocrValue;
 
   // Enable compare match interrupt
   TIMSK1 |= (1 << OCIE1A);
 
   // Set prescaler 1024 and start the timer
   TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
 } else {
   // The desired frequency is too low or too high, cannot set the timer
   Serial.println("Desired frequency is out of range for Timer1");
 }
 
 // Enable all interrupts after setting up the timer
 sei();
}

// Interrupt Service Routine (ISR) for the Timer1 Compare Match A interrupt
ISR(TIMER1_COMPA_vect) {
 // Toggle the LED state on each interrupt
 digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

