

#define TRIGGER_DEBOUNCE_MICRO 200
#define PRE_FLASH_DELAY_MICRO 0
#define PRE_FLASH_DELAY_MILLI 200


#define SOFTRESET_DEBOUNCE_MICRO 10000

#define CLOSE_TO_FLASH  true
#define FLASH_ON_DELAY 500

#define FLASH_ON_RESET true

#define STATUSLED_ON_WHILE_READY true
#define STATUSLED 11
#define SIGIN 1 
#define FLASH 0 
#define SOFTRESET 21





void init(){
  char blink=0;
  pinMode(STATUSLED,OUTPUT);
  pinMode(FLASH,OUTPUT);
  digitalWrite(SIGIN,HIGH);
  digitalWrite(SOFTRESET,HIGH);
  while(digitalRead(SIGIN)!= CLOSE_TO_FLASH){
    blink=!blink;
    delay(100);
    digitalWrite(STATUSLED,blink);
  }
  digitalWrite(STATUSLED,STATUSLED_ON_WHILE_READY);  
}



void wait_for_trigger(){
  unsigned long currentMicros = micros();
  do{
    if(digitalRead(SIGIN) == CLOSE_TO_FLASH){
      currentMicros = micros();
    }

  }
  while(currentMicros + TRIGGER_DEBOUNCE_MICRO > micros());

}

void wait_for_softreset(){
  unsigned long currentMicros = micros();
  char blink=0;
  int count=0;
  do{
    if(digitalRead(SOFTRESET) ){
      currentMicros = micros();

      if(count == 10000){
        blink=!blink;
        digitalWrite(STATUSLED,blink);
        count=0;
      }
      count++;
    }

  }
  while(currentMicros + SOFTRESET_DEBOUNCE_MICRO > micros());


}

void flash(){
  digitalWrite(STATUSLED,!STATUSLED_ON_WHILE_READY);
  delay(PRE_FLASH_DELAY_MILLI);
  delayMicroseconds(PRE_FLASH_DELAY_MICRO);
  digitalWrite(FLASH,HIGH);
  delay(FLASH_ON_DELAY);
  digitalWrite(FLASH,LOW);
}
void exit(){
  while(1){
  }
}

void setup(){
  init();


}
void loop(){
  wait_for_trigger();
  flash();
  wait_for_softreset();
  init();
  if(FLASH_ION_RESET){
    flash();
    init();
  }
}












