#define LED 6
#define LED_GREEN 5

#define BUZZER 7
#define BUTTOM 8

//#define LED_ON 13


// setting time limit (Min)
double time1 = 15;
double time2 = 20;

boolean stop = 1;
boolean stop_while_timer = 0;
boolean initial = 1;

double delay_time = time2; // mins

// function
void delayTime100(int);

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTOM, INPUT);

  // led on
  //pinMode(LED_ON, OUTPUT);
  delay(100);
  //digitalWrite(LED_ON, HIGH);

  // mins -> seconds
  delay_time = delay_time*60;
  if((int)time1==-1 && (int)time2==-1){
    time1 = 99999999*60;
    time2 = 99999999*60;
  }
  else{
    if((int)time1==-1)
  	  time1 = time2*60;
    else
  	  time1 *= 60;
    if((int)time2==-1)
  	  time2 = time1*60;
    else
  	  time2 *= 60;
  }

  

}

void loop() {
  // put your main code here, to run repeatedly:
  boolean tri;
  if(initial){
    initial = 0;
    tri = 1;
  }
  else{
    tri = digitalRead(BUTTOM);
  }
  //Serial.println(tri);
  if(tri==1 && stop==1){
    //Serial.println(delay_time);
    //Serial.println(time2);    
    if(delay_time==time2) digitalWrite(LED, HIGH);
    else digitalWrite(LED_GREEN, HIGH);
    // wait release
    while(digitalRead(BUTTOM));
    delay(100);
    stop = 0;


    //Serial.print("Wait time: ");
    //Serial.println(delay_time);
    for(int i=0; i< delay_time; i++){
      //Serial.println(i);
      if(digitalRead(BUTTOM)){
        stop_while_timer = 1;

        
        digitalWrite(LED, LOW);
        digitalWrite(LED_GREEN, LOW);
        // wait release
        while(digitalRead(BUTTOM));
        delay(100);
        
        break;
      }
      delayTime100(10);
    }
    if(stop_while_timer){

      stop_while_timer = 0;
      stop = 1;
      // switch time limit
      if(delay_time==time1) delay_time = time2;
      else delay_time = time1;      
    }
    else{
      digitalWrite(BUZZER, HIGH);

    }
    // wait release
    while(digitalRead(BUTTOM));
    delay(100);
  }
  else if(tri==1 && stop==0){
    digitalWrite(LED, LOW);
    digitalWrite(LED_GREEN, LOW);    
    stop = 1;
    digitalWrite(BUZZER, LOW);
    delay(200);
    // wait release
    while(digitalRead(BUTTOM));    
    delay(100);

    // switch time limit
    if(delay_time==time1) { delay_time = time2;}
    else {delay_time = time1; initial=1;}
  }
  if(delay_time==time1){
    // buzzer is working
    if(digitalRead(BUZZER)==HIGH){
        if(digitalRead(LED)==HIGH){ 
          digitalWrite(LED, LOW); 
          delayTime100(5);
        }
        else{ 
          digitalWrite(LED, HIGH); 
          delayTime100(5);
        }    
    }
  }
  else{
    // buzzer is working
    if(digitalRead(BUZZER)==HIGH){
        if(digitalRead(LED_GREEN)==HIGH){ 
          digitalWrite(LED_GREEN, LOW); 
          delayTime100(5);
        }
        else{ 
          digitalWrite(LED_GREEN, HIGH); 
          delayTime100(5);
        }    
    }    
  }
  
}

void delayTime100(int time=1){
  time*=2;
  for(int i=0; i<time; i++){
    if(digitalRead(BUTTOM)==HIGH){
      //while(digitalRead(BUTTOM)==HIGH);
      break;
    }
    delay(50);
  }
}
