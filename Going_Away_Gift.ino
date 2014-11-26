/*
  Going away gift for one of my co-workers.
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
//Pins for the RGB LED
int redPin = 11;
int greenPin = 9;
int bluePin = 10;
#define COMMON_ANODE // common anode LED in use;

//Button contained behind the RMO
int ButtonPin = 2;

//Counter to use for varying light color;
int counter=6;
int color=0;

//Message to transmit to my co-worker
String message="Dave,    In your too short time here, you've made a huge diference moving the mission forward.  Your departure leaves a hole in our office not easily filled.  Thanks for being a hard worker, dedicated mentor, and, above all else, a good friend.  Good luck in all your future endeavors, we're sure you'll do great.  Keep in touch.    --The SEU Technical Team";


void setup() {                
  // initialize the RGB LED PWM pins as outputs.
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  
  //Initialize the Button Pin
  pinMode(ButtonPin, INPUT_PULLUP);  
  
  //seed random number generator
  randomSeed(analogRead(13));
}

// the loop routine runs over and over again forever:
void loop() {  
    if (color !=0 ){
        switch(counter){
            case 6 : //only happens on startup
                for (int i=0; i<=255; i++){
                    setColor(i,0,0);
                    checkdelay(25,counter);
                }
                break;
            case 1 : //red
                setColor(255,0,0);
                checkdelay(3000,counter);
                break;
            case 2 : //transition to white
                for (int i=1; i<=255; i++){
                    setColor(255,i,i);
                    checkdelay(8,counter);
                } 
                break;
            case 3 : //white
                setColor(255,255,255);
                checkdelay(3000,counter);
                break;          
            case 4 : //transition to blue
                for (int i=255; i>=0; i--){
                    setColor(i,i,255);
                    checkdelay(8,counter);
                }
                break;
            case 5 : //blue
                setColor(0,0,255);
                checkdelay(3000,counter);
                break;
            case 0 : //transition to red
                for (int i=255; i>=0; i--){
                    setColor(255-i,0,i);
                    checkdelay(8,counter);
                }
                randomChance();
                break;
            default :
                setColor(0,0,0);
                checkdelay(1000,counter);
        }
        counter++;
        counter=counter % 6;
    }
    else {
      switch(counter){
        case 0:
            for (int i=0; i<=255; i++){
              setColor(i,i,i);
              checkdelay(4,10);
            }
            break;;
        case 1:
            setColor(255,255,255);
            checkdelay(1000,10);
            break;;
        case 2:
            for (int i=255; i>=0; i--){
              setColor(i,i,i);
              checkdelay(4,10);
            }
            break;;
        case 3:
            setColor(0,0,0);
            checkdelay(1000,10);
            randomChance();
            break;;
      }
      counter++;
      if (color == 0){
          counter = counter % 4;
      }
      else {
          counter = 6;
      }
    }
}

void checkdelay(int time,int action){
  for (int c=1; c<=time; c++){
    checkButton(action);
    delay(1);
  }
}

void randomChance(){
  int choice=random(100);
  if (choice <= 10){
    randomMischief();
  }
}

void randomMischief(){
  int choice=random(12);
  
  switch(choice){
    case 1:
        changeWindow();
        break;;
    case 2:
        send_CTRL_ALT_DEL();
        break;;
    case 3:
        send_ENTER();
        break;;
    case 4:
        lock_Screen();
        break;;
    case 5:
        send_CTRL_ALT_F2();
        break;;
    case 6:
        Mouse_Upper_Left();
        break;;
    case 7:
        Mouse_Upper_Right();
        break;;
    case 8:
        Mouse_Lower_Left();
        break;;
    case 9:
        Mouse_Lower_Right();
        break;;
    case 10:
        Mouse_Box();
        break;;
    case 11:
        Mouse_Click();
        break;;
  }
}

void checkButton(int action){
  if (digitalRead(ButtonPin) == LOW){
       switch(action){
         case 1:
             randomMischief();
             counter--;
             break;;
             
         case 3:
             setColor(0,0,0);
             delay(2000);
             color=0;
             counter=0;
             break;;
         case 5:
             sendMessage();
             break;;
         case 10:
             setColor(0,0,0);
             delay(2000);
             color=1;
             counter=5;
             break;;
         default:
             colorWheel();
             break;;
       }
  }
}

void sendMessage(){
    setColor(0,0,0);
    print_Morse(message);         
}

void changeWindow(){
  Keyboard.begin();
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_TAB);
  Keyboard.releaseAll();
  Keyboard.end();
}

void send_CTRL_ALT_DEL(){
  Keyboard.begin();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_DELETE);
  Keyboard.releaseAll();
  Keyboard.end();
}

void send_ENTER(){
  Keyboard.begin();
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.end();
}

void lock_Screen(){
  Keyboard.begin();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_DELETE);
  Keyboard.releaseAll();
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.end();
}

void send_CTRL_ALT_F2(){
  Keyboard.begin();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F2);
  Keyboard.releaseAll();
  Keyboard.end();
}

void Mouse_Upper_Left(){
    Mouse.begin();
    for (int i=0; i < 5000; i++){
        Mouse.move(-1,-1,0);
    }
    Mouse.end();
}

void Mouse_Upper_Right(){
    Mouse.begin();
    for (int i=0; i < 5000; i++){
        Mouse.move(1,-1,0);
    }
    Mouse.end();
}

void Mouse_Lower_Left(){
    Mouse.begin();
    for (int i=0; i < 5000; i++){
        Mouse.move(-1,1,0);
    }
    Mouse.end();
}

void Mouse_Lower_Right(){
    Mouse.begin();
    for (int i=0; i < 5000; i++){
        Mouse.move(1,1,0);
    }
    Mouse.end();
}

void Mouse_Box(){
    Mouse.begin();
    for (int i=0; i < 200; i++){
        Mouse.move(1,0,0);
    }
    for (int i=0; i < 200; i++){
        Mouse.move(0,1,0);
    }
    for (int i=0; i < 200; i++){
        Mouse.move(-1,0,0);
    }
    for (int i=0; i < 200; i++){
        Mouse.move(0,-1,0);
    }

    Mouse.end();
}

void Mouse_Click(){
  Mouse.begin();
  Mouse.click();
  Mouse.end();
}


void colorWheel(){
  
  setColor(0,0,0);
  delay(5000);
  
  for (int x=0; x<=255; x++){
      setColor(x,0,0);
      delay(4);
  }
  
  setColor(255, 0, 0);  // red
  delay(1000);
  
  for (int x=0; x<=165; x++){
      setColor(255,x,0);
      delay(6);
  }
  
  setColor(255,165,0); //orange
  delay(1000);
  
  for (int x=165; x<=255; x++){
      setColor(255,x,0);
      delay(11);
  }
  
  setColor(255,255,0); //yellow
  delay(1000);
  
  for (int x=255; x>=0; x--){
      setColor(x,255,0);
      delay(4);
  }
  
  setColor(0, 255, 0);  // green
  delay(1000);
  
  for (int x=255; x>=0; x--){
      setColor(0,255-x,x);
      delay(4);
  }
  
  setColor(0, 0, 255);  // blue
  delay(1000);

  for (int x=0; x<=255; x++){
      setColor(x,0,255);
      delay(4);
  }
  
  setColor(255,0,255);
  delay(1000);
  
  for (int x=255; x>=0; x--){
      setColor(x,0,x);
      delay(4);
  }
  
  setColor(0,0,0);
  delay(5000);

}


void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void dot(){
  setColor(255,255,255);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  setColor(0,0,0);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}

void dash(){
  setColor(255,255,255);   // turn the LED on (HIGH is the voltage level)
  delay(300);               // wait for a second
  setColor(0,0,0);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}

void print_Morse_char(char c){
    switch(c){
      case 'A':
          dot();dash();
          break;
      case 'B':
          dash();dot();dot();dot();
          break;
      case 'C':
          dash();dot();dash();dot();
          break;
      case 'D':
          dash();dot();dot();
          break;
      case 'E':
          dot();
          break;
      case 'F':
          dot();dot();dash();dot();
          break;
      case 'G':
          dash();dash();dot();
          break;
      case 'H':
          dot();dot();dot();dot();
          break;
      case 'I':
          dot();dot();
          break;
      case 'J':
          dot();dash();dash();dash();
          break;
      case 'K':
          dash();dot();dash();
          break;
      case 'L':
          dot();dash();dot();dot();
          break;
      case 'M':
          dash();dash();
          break;
      case 'N':
          dash();dot();
          break;
      case 'O':
          dash();dash();dash();
          break;
      case 'P':
          dot();dash();dash();dot();
          break;
      case 'Q':
          dash();dash();dot();dash();
          break;
      case 'R':
          dot();dash();dot();
          break;
      case 'S':
          dot();dot();dot();
          break;
      case 'T':
          dash();
          break;
      case 'U':
          dot();dot();dash();
          break;
      case 'V':
          dot();dot();dot();dash();
          break;
      case 'W':
          dot();dash();dash();
          break;
      case 'X':
          dash();dot();dot();dash();
          break;
      case 'Y':
          dash();dot();dash();dash();
          break;
      case 'Z':
          dash();dash();dot();dot();
          break;
      case '1':
          dot();dash();dash();dash();dash();
          break;
      case '2':
          dot();dot();dash();dash();dash();
          break;
      case '3':
          dot();dot();dot();dash();dash();
          break;
      case '4':
          dot();dot();dot();dot();dash();
          break;
      case '5':
          dot();dot();dot();dot();dot();
          break;
      case '6':
          dash();dot();dot();dot();dot();
          break;
      case '7':
          dash();dash();dot();dot();dot();
          break;
      case '8':
          dash();dash();dash();dot();dot();
          break;
      case '9':
          dash();dash();dash();dash();dot();
          break;
      case '0':
          dash();dash();dash();dash();dash();
          break;
      default:
          delay(500);
          break;
    }
    delay (200);
}

void print_Morse(String mesg){
  String mesg_copy=mesg;
  
  mesg.toUpperCase();
  Keyboard.begin();
  Keyboard.print("#");  
  
  for (int i=0; i<mesg.length(); i++){
    Keyboard.print(mesg_copy.charAt(i));
    print_Morse_char(mesg.charAt(i));
  }
  
  Keyboard.println("");
  Keyboard.end();
}
