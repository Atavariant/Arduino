#include <IRLibAll.h>
#include <Servo.h> 
 
// You will have to set these values depending on the protocol
// and remote codes that you are using. These are For the Adafruit
// Mini Remote
#define MY_PROTOCOL NEC
#define RIGHT_ARROW   0x926DF20D //Move several clockwise
#define LEFT_ARROW    0x926DEA15 //Move servo counterclockwise
#define SELECT_BUTTON 0x926DCA35 //Center the servo
#define UP_ARROW      0x926D18E7 //Increased number of degrees servo moves
#define DOWN_ARROW    0x926D08F7 //Decrease number of degrees servo moves
#define BUTTON_0 0x926D20DF  //Pushing buttons 0-9 moves to fixed positions
#define BUTTON_1 0x926DD02F  // each 20 degrees greater
#define BUTTON_2 0x926DE01F
#define BUTTON_3 0x926DC03F
#define BUTTON_4 0x926D50AF
#define BUTTON_5 0x926D609F
#define BUTTON_6 0x926D40BF
#define BUTTON_7 0x926D906F
#define BUTTON_8 0x926DA05F
#define BUTTON_9 0x926D807F
 
IRrecv myReceiver(2); //pin number for the receiver
IRdecode myDecoder;
 
Servo myServo;  // create servo object to control a servo 
int16_t pos;         // variable to store the servo position 
int16_t Speed;       // Number of degrees to move each time a left/right button is pressed
uint32_t Previous;//handles NEC repeat codes
 
void setup() { 
  myServo.attach(9);      // attaches the servo on pin 9 to the servo object 
  pos = 90;               // start at midpoint 90 degrees
  Speed = 3;              // servo moves 3 degrees each time left/right is pushed
  myServo.write(pos);     // Set initial position
  myReceiver.enableIRIn(); // Start the receiver
} 
  
void loop() 
{ 
    if (myReceiver.getResults()) {
       myDecoder.decode();
       if(myDecoder.protocolNum==MY_PROTOCOL) {
         if(myDecoder.value==0xFFFFFFFF)
           myDecoder.value=Previous;
         switch(myDecoder.value) {
            case LEFT_ARROW:    pos=min(180,pos+Speed); break;
            case RIGHT_ARROW:   pos=max(0,pos-Speed); break;
            case SELECT_BUTTON: pos=90; break;
            case UP_ARROW:      Speed=min(10, Speed+1); break;
            case DOWN_ARROW:    Speed=max(1, Speed-1); break;
            case BUTTON_0:      pos=0*20; break;
            case BUTTON_1:      pos=1*20; break;
            case BUTTON_2:      pos=2*20; break;
            case BUTTON_3:      pos=3*20; break;
            case BUTTON_4:      pos=4*20; break;
            case BUTTON_5:      pos=5*20; break;
            case BUTTON_6:      pos=6*20; break;
            case BUTTON_7:      pos=7*20; break;
            case BUTTON_8:      pos=8*20; break;
            case BUTTON_9:      pos=9*20; break;
         }
         myServo.write(pos); // tell servo to go to position in variable 'pos' 
         Previous=myDecoder.value;
       }
       myReceiver.enableIRIn();
    }
}
