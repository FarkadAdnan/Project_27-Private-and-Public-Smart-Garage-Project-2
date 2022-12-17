/*
 By:Farkad Adnan
 E-mail: farkad.hpfa95@gmail.com
 inst : farkadadnan
 #farkadadnan , #farkad_adnan , فرقد عدنان#
 FaceBook: كتاب عالم الاردوينو
 inst : arduinobook
 #كتاب_عالم_الاردوينو  #كتاب_عالم_الآردوينو 
 */
 #include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <Servo.h>
#include <Servo.h> 
#include <MFRC522.h> 
#include <SPI.h>
#define RST_X 9
#define SS_X 10
byte open_val =70  ;
byte close_val=180 ;
Servo sl ;
MFRC522 mfrc522( SS_X, RST_X) ;
int R = 12 ;

byte card_ID [4] ;
byte First_card_ID1[4]={0x37,0x26,0x21,0x1B}; 
byte First_card_ID2[4]={0xC9,0x4B,0x69,0x99}; 
byte First_card_ID3[4]={0x6C,0x87,0xC3B,0xD9}; 
byte First_card_ID4[4]={0x97,0x71,0x1E,0x1B};  
byte First_card_ID5[5]={0xA3,0xF2,0x76,0x11};  
byte First_card_ID6[6]={0x39,0x75,0x88,0x9C};  
boolean State = false ; 



Servo myservo;
#define ir_enter 2
#define ir_back  4
#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8
#define ir_car5 9
#define ir_car6 10
int S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;
int flag1=0, flag2=0; 
int slot = 6;  
void setup(){
  sl.attach ( 6 );
Serial.begin ( 9600 ) ;
SPI.begin ( ) ;
sl.write (close_val ) ;
mfrc522.PCD_Init ( ) ;
Serial. println ("read my  Card") ;
for (int def=5; def<8; def++){
pinMode (def,  OUTPUT ) ;
pinMode ( R ,    OUTPUT ) ;
 }


Serial.begin(9600);
pinMode(ir_car1, INPUT);
pinMode(ir_car2, INPUT);
pinMode(ir_car3, INPUT);
pinMode(ir_car4, INPUT);
pinMode(ir_car5, INPUT);
pinMode(ir_car6, INPUT);
pinMode(ir_enter, INPUT);
pinMode(ir_back, INPUT);
myservo.attach(11);
myservo.write(90);
lcd.begin(20, 4);  
lcd.setCursor (0,1);
lcd.print("    Car  parking  ");
lcd.setCursor (0,2);
lcd.print("       System     ");
delay (2000);
lcd.clear();   
Read_Sensor();
int total = S1+S2+S3+S4+S5+S6;
slot = slot-total; 
}


void newfuction ( )   {
for (byte i = 0 ; i < mfrc522.uid.size; i++){ 
if (card_ID [ i ] == First_card_ID1 [ i ] || card_ID [ i ] == First_card_ID2 [ i ] || card_ID [ i ] == First_card_ID3 [ i ] || card_ID [ i ] == First_card_ID4 [ i ] || card_ID [ i ] == First_card_ID5 [ i ] || card_ID [ i ] == First_card_ID6 [ i ]){
State = true ;  
}
else {
State = false ;  
i = 5;  
}
} 
}


void loop(){
Read_Sensor();
lcd.setCursor (0,0);
lcd.print("   Have Slot: "); 
lcd.print(slot);
lcd.print("    ");  
lcd.setCursor (0,1);
if(S1==1){lcd.print("S1:Fill ");}
     else{lcd.print("S1:Empty");}
lcd.setCursor (10,1);
if(S2==1){lcd.print("S2:Fill ");}
     else{lcd.print("S2:Empty");}

lcd.setCursor (0,2);
if(S3==1){lcd.print("S3:Fill ");}
     else{lcd.print("S3:Empty");}

lcd.setCursor (10,2);
if(S4==1){lcd.print("S4:Fill ");}
     else{lcd.print("S4:Empty");}
 lcd.setCursor (0,3);
if(S5==1){lcd.print("S5:Fill ");}
     else{lcd.print("S5:Empty");}
lcd.setCursor (10,3);
if(S6==1){lcd.print("S6:Fill ");}
     else{lcd.print("S6:Empty");}    
if(digitalRead (ir_enter) == 0 && flag1==0){
if(slot>0){flag1=1;
if(flag2==0){myservo.write(90); slot = slot-1;}
}else{
lcd.setCursor (0,0);
lcd.print(" Sorry Parking Full ");  
delay(1500);
}   
}
if(digitalRead (ir_back) == 0 && flag2==0){flag2=1;
if(flag1==0){myservo.write(90); slot = slot+1;}
}
if(flag1==1 && flag2==1){
delay (1000);
myservo.write(90);
flag1=0, flag2=0;
}
delay(1);


if ( ! mfrc522.PICC_IsNewCardPresent ( ) ) {
  return ; 
  }
  if ( ! mfrc522.PICC_ReadCardSerial ( ) ) {
  return ; 
   }
Serial. print ("Card UID::") ;
  for (byte i = 0 ; i < mfrc522.uid.size; i++){ 
     card_ID [ i ] =mfrc522.uid.uidByte [ i ] ;
Serial. print (" - ") ;
Serial. print (card_ID [ i ] , HEX) ;
Serial. print (" - "); 
}  
Serial. println ( ) ;
delay ( 500 ) ;
     newfuction ( ) ;
if (State == true) {
Serial. println ( " Accepted, Valid card" ) ;
    digitalWrite(R,0);
sl.write (open_val) ;
delay ( 3000 ) ;
sl.write (close_val) ;
}
if (State == false) {
Serial. println ( " denied! unValid card " ) ;
    digitalWrite(R,1);
sl.write (close_val) ;
delay ( 2000 ) ;
} else{
    digitalWrite(R,1);
}
}
void Read_Sensor(){
S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;
if(digitalRead(ir_car1) == 0){S1=1;}
if(digitalRead(ir_car2) == 0){S2=1;}
if(digitalRead(ir_car3) == 0){S3=1;}
if(digitalRead(ir_car4) == 0){S4=1;}
if(digitalRead(ir_car5) == 0){S5=1;}
if(digitalRead(ir_car6) == 0){S6=1;}  
}
