#include <Servo.h>
Servo servo1, servo2, servo3;
#include <LiquidCrystal.h>
const int rs = 12,en = 11,d4 = 5 ,d5 = 4 ,d6 = 3 ,d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define btn_ok A0
#define btn_back A1
#define btn_up A3
#define btn_down A4

int x=0, y=0, z=0;

void menu(){
  menu_koorX:
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print(">SET KOORD X");
  lcd.setCursor(0, 1);lcd.print(" SET KOORD Y");  
  while(1)
  {
    if (digitalRead(btn_up) == 0){delay(500);}
    else if (digitalRead(btn_down) == 0){delay(500);goto menu_koorY;}
     else if (digitalRead(btn_ok) == 0){delay(500);goto menu_setX;}
      else if (digitalRead(btn_back) == 0){delay(500);}
   }

  menu_koorY:
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print(" SET KOORD X");
  lcd.setCursor(0, 1);lcd.print(">SET KOORD Y");
  while(1)
  {
    if (digitalRead(btn_up) == 0){delay(500);goto menu_koorX;}
    else if (digitalRead(btn_down) == 0){delay(500);goto menu_koorZ;}
     else if (digitalRead(btn_ok) == 0){delay(500);goto menu_setY;  }
      else if (digitalRead(btn_back) == 0){delay(500);}
    }

  menu_koorZ:
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print(">SET KOORD Z");
  lcd.setCursor(0, 1);lcd.print(" RUN IVRS_KNMTK");
  while(1)
  {
    if (digitalRead(btn_up) == 0){delay(500);goto menu_koorY;}
    else if (digitalRead(btn_down) == 0){delay(500);goto menu_run_IK;}
     else if (digitalRead(btn_ok) == 0){delay(500);goto menu_setZ;}
      else if (digitalRead(btn_back) == 0){delay(500);}
  }

  menu_run_IK:
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print(" SET KOORD Z");
  lcd.setCursor(0, 1);lcd.print(">RUN IVRS_KNMTK");
  while(1)
  {
    if (digitalRead(btn_up) == 0){delay(500);goto menu_koorY;}
    else if (digitalRead(btn_down) == 0){delay(500);}
     else if (digitalRead(btn_ok) == 0){delay(500);goto menu_set_run_IK;}
      else if (digitalRead(btn_back) == 0){delay(500);}
    }

  menu_setX:
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print("> ATUR NILAI X");
  lcd.setCursor(0, 1);lcd.print("+ " + String(x));
  lcd.setCursor(15, 1);lcd.print("-");
  while(1)
  {
    if (digitalRead(btn_up) == 0){delay(500);x++;goto menu_setX;}
    else if (digitalRead(btn_down) == 0){delay(500);x--;goto menu_setX;}
     else if (digitalRead(btn_ok) == 0){delay(500);goto menu_koorX;}
      else if (digitalRead(btn_back) == 0){delay(500);goto menu_koorX;}
    }
    
  menu_setY:
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print("> ATUR NILAI Y");
  lcd.setCursor(0, 1);lcd.print("+ " + String(y));
  lcd.setCursor(15, 1);lcd.print("-");
  while(1)
  {
    if (digitalRead(btn_up) == 0){delay(500);y++;goto menu_setY;}
    else if (digitalRead(btn_down) == 0){delay(500);y--;goto menu_setY;}
     else if (digitalRead(btn_ok) == 0){delay(500);goto menu_koorY;}
      else if (digitalRead(btn_back) == 0){delay(500);goto menu_koorY;}
    }

  menu_setZ:
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print("> ATUR NILAI Z");
  lcd.setCursor(0, 1);lcd.print("+ " + String(z));
  lcd.setCursor(15, 1);lcd.print("-");
  while(1)
  {
    if (digitalRead(btn_up) == 0){delay(500);z++;goto menu_setZ;}
    else if (digitalRead(btn_down) == 0){delay(500);z--;goto menu_setZ;}
     else if (digitalRead(btn_ok) == 0){delay(500);goto menu_koorY;}
      else if (digitalRead(btn_back) == 0){delay(500);goto menu_koorZ;}
    }

  menu_set_run_IK:
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print("X,Y,Z:("+String(x)+","+String(y)+","+String(z)+")");
  lcd.setCursor(0, 1);lcd.print("BATAL      OKE");
  while(1)
  {
    if (digitalRead(btn_up) == 0){delay(500);}
    else if (digitalRead(btn_down) == 0){delay(500);}
     else if (digitalRead(btn_ok) == 0){delay(500);run_IK(x,y,x);}
      else if (digitalRead(btn_back) == 0)
      {
        delay(500);
        goto menu_run_IK;
        }
    }
  }

  void run_IK(int x,int y, int z)
  {
    const float cx=3;
    const float fm=7;
    const float tb=9;
    float L, L1, theta1temp1, theta1temp2;
    int theta1, theta2, theta3;

    theta3 = atan(x/y)*RAD_TO_DEG;

    L1 = sqrt(sq(x)+sq(y));
    L = sqrt(sq(L1-cx)+sq(z));
    theta2 = acos((sq(tb)+sq(fm)-sq(L))/(2*tb*fm))*RAD_TO_DEG;;

    theta1temp1 =acos(z/L)*RAD_TO_DEG;;
    theta1temp2 =acos((sq(fm)+sq(L)-sq(tb))/(2*fm*L))*RAD_TO_DEG;;
    theta1 = theta1temp1+theta1temp2;

    servo1.write(theta1);
    servo2.write(theta2);
    servo3.write(theta3);
 }

 void setup(){
  pinMode(btn_ok, INPUT_PULLUP);
  pinMode(btn_back, INPUT_PULLUP);
  pinMode(btn_up, INPUT_PULLUP);
  pinMode(btn_down, INPUT_PULLUP); 

  servo1.attach(10);
  servo2.attach(9);
  servo3.attach(6);

  lcd.begin(16,2);
  lcd.setCursor(0, 0);lcd.print ("GHORBY AL FAUZAN");
  lcd.setCursor(0, 1);lcd.print ("180536633106");
  delay(500);
  lcd.clear();
 }

 void loop()
 {
  menu(); 
 }
