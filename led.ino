// -----------------------------------
// Controlling LEDs over the Internet
// -----------------------------------

// curl https://api.particle.io/v1/devices/dorito/led \
//  -d access_token=xxx \
//  -d params=l1,HIGH

// name the pins
int led1 = D0;
int led2 = D7;
String ledStatus = "off";

// This routine runs only once upon reset
void setup() {
   //Register our Particle function here
   Particle.function("led", ledControl);

   // Configure the pins to be outputs
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);

   // Initialize both the LEDs to be OFF
   digitalWrite(led1, LOW);
   digitalWrite(led2, LOW);

   //Register Particle variable
   Particle.variable("ledStatus", ledStatus);
}


// This routine loops forever
void loop() {
   // Nothing to do here
}

// This function gets called whenever there is a matching API request
// the command string format is l<led number>,<state>
// for example: l1,HIGH or l1,LOW
//              l2,HIGH or l2,LOW

int ledControl(String command) {
   int state = 0;
   //find out the pin number and convert the ascii to integer
   int pinNumber = (command.charAt(1) - '0');
   //Sanity check to see if the pin numbers are within limits
   if (pinNumber < 0 || pinNumber > 7) return -1;

   // find out the state of the led
   if (command.substring(3,7) == "HIGH") {
     state = 1;
     ledStatus = "on";
   } else if (command.substring(3,6) == "LOW") {
     state = 0;
     ledStatus = "off";
   }
   else return -1;

   // write to the appropriate pin
   digitalWrite(pinNumber, state);
   return 1;
}
