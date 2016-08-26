#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int LED = 6;
int butA = 9;
int butB = 5;
int butC = 3;
int butD = 8;
int bluetooth = 12;
int done;
int back;
int back2;
int option;
int milis;
int second;
int minute;
int hour;
int steps;
//////////////////////////////////////////////////////////////////////////////////////////////////////////


void mainmenu() {
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("    Menu Principal\n \n A:AJUSTES   B:APPS");
  display.display();
}


int checkbutton() {
  done = 0;
  while (done == 0) {

    if (digitalRead(butA) == HIGH) {
      return (1);
      done++;
    }
    if (digitalRead(butB) == HIGH) {
      return (2);
      done++;
    }
    if (digitalRead(butC) == HIGH) {
      return (3);
      done++;
    }
    if (digitalRead(butD) == HIGH) {
      return (4);
      done++;
    }

  }
}

void waitforback() {
  while (checkbutton() != 4) {}
}
void waitforlow() {
  while (digitalRead(butA) == HIGH || digitalRead(butB) == HIGH || digitalRead(butC) == HIGH  || digitalRead(butD) == HIGH) {}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(bluetooth, OUTPUT);
  pinMode(butA, INPUT);
  pinMode(butB, INPUT);
  pinMode(butC, INPUT);
  pinMode(butD, INPUT);

  digitalWrite(bluetooth, LOW);
}

void loop() {
  mainmenu();
  waitforlow();

  back = 0;
  while (back == 0) {
    switch (checkbutton()) {
        delay(100);
      case 1:
        while (back == 0) {
          display.clearDisplay();
          display.display();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.print("    Ajustes\n   A:AIRPLANE MODE   \n   B:ABOUT");
          display.display();
          //////////////////////////////////////////////////////////////////////////////////////////////////////////
          waitforlow();

          switch (checkbutton()) {


            case 1:
              display.clearDisplay();
              display.display();
              display.setCursor(0, 0);
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.print(" Airplane Mode\n   A:ON   \n   B:OFF");
              display.display();


              back = 0;

              waitforlow();

              while (back == 0) {
                option = checkbutton();
                if (option == 1) {
                  digitalWrite(bluetooth, HIGH);
                  waitforlow();
                }

                if (option == 2) {
                  digitalWrite(bluetooth, LOW);
                  waitforlow();
                }

                if (option == 4) {
                  back++;
                  waitforlow();
                }

              }
              back = 0;

              break;




            case 2:
              display.clearDisplay();
              display.display();
              display.setCursor(0, 0);
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.print("       ABOUT\n      MADE BY\n    PATXIELSUCIO");
              display.display();
              waitforback();

              break;

            case 4:
              back = 1;
              waitforlow();
              break;
          }

        }


        break;

      //////////////////////////////////////////////////////////////////////////////////////////////////////////




      case 2:
        back = 0;
        while (back == 0) {
          waitforlow();

          display.clearDisplay();
          display.display();
          display.setCursor(0, 0);
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.println("         APPS\n A:LED     B:CHRONO \n C:MORE  D:EXIT");
          display.display();
          back = 0;

          waitforlow();

          option = checkbutton();
          //////////////////////////////////////////////////////////////////////////////////////////////////////////

          if (option == 4) {

            back++;           //salir

          }
          //////////////////////////////////////////////////////////////////////////////////////////////////////////







          if (option == 1) {
            display.clearDisplay();
            display.display();
            display.setCursor(0, 0);
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.println("   LED MENU\n A:ON     B:OFF \n D:EXIT");
            display.display();
            back2 = 0;
            waitforlow();


            while (back2 == 0) {
              //led APP

              option = checkbutton();

              if (option == 1) {
                digitalWrite(LED, HIGH);
              }

              if (option == 2) {
                digitalWrite(LED, LOW);
              }

              if (option == 4) {
                back2++;
                waitforlow();
              }

            }

          }
          ///////////////////////////////////////////////////////////////////////////////////////////////////////

          if (option == 2) {
            display.clearDisplay();
            display.display();
            display.setCursor(35, 10);
            display.setTextSize(2);
            display.println("0:0:0");
            back2 = 0;
            while (back2 == 0 ) {

              display.setCursor(0, 0);
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.println("A:START B:STOP D:EXIT"); //Chrono App

              display.display();

              waitforlow();
              option = checkbutton();

              if (option == 4) {
                back2++;
              }

              if (option == 1) {
                display.clearDisplay();
                display.display();
                display.setCursor(0, 0);
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.println("A:START B:STOP D:EXIT");
                milis = 0;
                second = 0;
                minute = 0;
                hour = 0;
                ///////////////////////////////////////////////////////////////////////////////////////////////////////

                while (digitalRead(butB) != HIGH) {
                  delay(1);


                  milis++;
                  if (milis == 40) {
                    display.setTextSize(2);

                    display.setTextColor(BLACK);
                    display.setCursor(35, 10);
                    display.print(hour);
                    display.print(":");
                    display.print(minute);
                    display.print(":");
                    display.print(second);
                    display.display();
                    second++;
                    milis = 0;

                  }
                  if (second == 60) {
                    display.setTextSize(2);

                    display.setTextColor(BLACK);
                    display.setCursor(35, 10);
                    display.print(hour);
                    display.print(":");
                    display.print(minute);
                    display.print(":");
                    display.print(second);
                    display.display();
                    minute++;
                    second = 0;
                  }
                  if (minute == 60) {
                    display.setTextSize(2);

                    display.setTextColor(BLACK);
                    display.setCursor(35, 10);
                    display.print(hour);
                    display.print(":");
                    display.print(minute);
                    display.print(":");
                    display.print(second);
                    display.display();
                    hour++;
                    minute = 0;
                  }

                  display.setTextSize(2);
                  display.setTextColor(WHITE);
                  display.setCursor(35, 10);
                  display.print(hour);
                  display.print(":");
                  display.print(minute);
                  display.print(":");
                  display.print(second);
                  display.display();
                }
                ///////////////////////////////////////////////////////////////////////////////////////////////////////


              }

            }
          }
          ///////////////////////////////////////////////////////////////////////////////////////////////////////
          if (option == 3) {
            back = 0;
            while (back == 0) {
              waitforlow();

              display.clearDisplay();
              display.display();
              display.setCursor(0, 0);
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.println("         APPS\n A:PODOMETER     \nB:Remote  D:EXIT");
              display.display();

              option = checkbutton();

              if (option == 4) {
                back++;
              }
              if (option == 1) {
                display.clearDisplay();
                display.display();
                display.setCursor(0, 0);
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.println("         Steps");
                display.setCursor(50, 10);
                display.setTextSize(2);
                display.println("0");
                display.display();

                steps = 0;
                back2 = 0;
                while (back2 == 0) {



                  if (Serial.available()) {
                    if (Serial.read() == 'S') {

                      display.setTextColor(BLACK);             //Podometer
                      display.setTextSize(2);
                      display.setCursor(50, 10);
                      display.print(steps);
                      display.display();
                      steps++;
                      display.setTextColor(WHITE);

                      display.setCursor(50, 10);
                      display.setTextSize(2);
                      display.print(steps);
                      display.display();
                    }
                  }
                  if (digitalRead(butD) == HIGH) {
                    back2++;
                  }
                }

              }
              ///////////////////////////////////////////////////////////////////////////////////////////////////////
              if (option == 2) {
                waitforlow();
                display.clearDisplay();
                display.display();
                display.setCursor(0, 0);
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.println("       REMOTE\n A:Send A    B:Send B\nC:Send C  D:EXIT");
                display.display();
                back2 = 0;
                while (back2 == 0) {
                  if (digitalRead(butA) == HIGH) {
                    Serial.print('A');
                    waitforlow();
                  }
                  if (digitalRead(butB) == HIGH) {
                    Serial.print('B');
                    waitforlow();
                  }
                  if (digitalRead(butC) == HIGH) {
                    Serial.print('C');
                    waitforlow();
                  }
                  if (digitalRead(butD) == HIGH) {
                    back2++;
                  }





                }



              }
              ///////////////////////////////////////////////////////////////////////////////////////////////////////









            }

            back = 0;
          }



        }
        break;




    }
  }
}
