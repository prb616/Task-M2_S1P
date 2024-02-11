//Name : Prabhjot Singh
//Roll No. : 2210994884

// Define the LED pin number (digital pin 13)
const byte LED_PIN = 13;

// Define the meter pin number (analog input A4)
const byte METER_PIN = A4;

// Function prototype for startTimer()
void startTimer(double timerFrequency);

void setup()  // Arduino setup function
{
 // Set the LED pin as an output
 pinMode(LED_PIN, OUTPUT);

 // Set the meter pin as an input
 pinMode(METER_PIN, INPUT);

 // Initialize serial communication with a baud rate of 9600
 Serial.begin(9600);

 // Define the desired frequency for the timer (0.5 Hz)
 double desiredFrequency = 0.5;

 // Call the startTimer() function with the desired frequency
 startTimer(desiredFrequency);
}

void loop()  // Arduino loop function
{
 // Main program loop
}

void startTimer(double timerFrequency)  // Function to start the timer with a given frequency
{
 // Disable all interrupts
 cli();

 // Calculate the required OCR1A value based on the desired frequency
 unsigned long ocrValue = (F_CPU / 1024 / timerFrequency) - 1;

 // Ensure the calculated OCR1A value is within range
 if (ocrValue < 65536)
 {
   // Set CTC mode (Clear Timer on Compare Match)
   TCCR1A = 0;
   TCCR1B = 0;
   TCNT1 = 0;  // Initialize counter value to 0

   // Set compare match register for desired frequency
   OCR1A = ocrValue;

   // Enable compare match interrupt
   TIMSK1 |= (1 << OCIE1A);

   // Set prescaler 1024 and start the timer
   TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
 }
 else
 {
   // The desired frequency is out of range for Timer1
   Serial.println("Desired frequency is out of range for Timer1");
 }

 // Enable all interrupts
 sei();
}

// Interrupt Service Routine (ISR) for TIMER1_COMPA_vect
ISR(TIMER1_COMPA_vect)
{
 // Toggle the LED state
 digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}
