#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//////////////////////////////////////////////////////////////////////////////////////////////////////////

int LED = 6;
int butA = 9;
int butB = 5;    //Pin definitions and variables
int butC = 3;
int butD = 8;
int bluetooth = 12;
byte select = 0;
byte exitloop = 0;
byte back;
byte intro;
int timer[4] = {0, 0, 0, 0};
int steps;
char phone[10] = {"000000000"};
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void menuselect(int lines) {

  back = 0;
  exitloop = 0;
  intro = 0;
  while (exitloop == 0) {

    if (digitalRead(butA) == HIGH) {
      intro++;
      exitloop++;
      waitforlow();
    }

    if (digitalRead(butB) == HIGH) {
      select++;
      if (select > lines) {
        select = 0;
      }
      exitloop++;
      waitforlow();
      display.startscrollleft(0x01, 0x07);
      display.display();
      delay(200);
      display.stopscroll();
    }

    if (digitalRead(butC) == HIGH) {
      select--;
      if (select > lines) {
        select = lines;
      }
      exitloop++;
      waitforlow();
      display.startscrollright(0x01, 0x07);
      display.display();
      delay(200);
      display.stopscroll();
    }
    if (digitalRead(butD) == HIGH) {
      back++;
      exitloop++;
      waitforlow();
    }

    if (Serial.available()) {

      if (Serial.find("Phone_Call")) {
        delay(100);
        for (int v = 0; v < 9; v++) {
          phone[v] = Serial.read();
        }
        display.clearDisplay();
        display.display();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("  Incoming call");
        display.setCursor(0, 15);
        display.setTextSize(2);
        for (int v = 0; v < 9; v++) {
          display.print(phone[v]);
        }

        display.setTextSize(1);
        display.display();
        delay(5000);

      }
      
      
          exitloop++;

    }

  }

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


  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("   Menu principal");  //Ajustes
  display.setCursor(0, 15);
  display.setTextSize(1);
  display.print("<");
  display.setTextSize(2);
  display.print(" AJUSTES ");
  display.setTextSize(1);
  display.print(">");
  display.display();

}

void loop() {

  menuselect(4);
  switch (select) {

    case 0:

      display.clearDisplay();
      display.display();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("   Menu principal");  //Ajustes
      display.setCursor(0, 15);
      display.setTextSize(1);
      display.print("<");
      display.setTextSize(2);
      display.print(" AJUSTES ");
      display.setTextSize(1);
      display.print(">");
      display.display();



      break;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 1:
      display.clearDisplay();
      display.display();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("   Menu principal");  //LED
      display.setCursor(0, 15);
      display.setTextSize(1);
      display.print("<");
      display.setTextSize(2);
      display.print("   LED   ");
      display.setTextSize(1);
      display.print(">");
      display.display();



      break;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 2:
      display.clearDisplay();
      display.display();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("   Menu principal");  //Cronometro
      display.setCursor(0, 15);
      display.setTextSize(1);
      display.print("<");
      display.setTextSize(2);
      display.print("  CRONO  ");
      display.setTextSize(1);
      display.print(">");
      display.display();


      break;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 3:
      display.clearDisplay();
      display.display();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("   Menu principal");
      display.setCursor(0, 15);
      display.setTextSize(1);
      display.print("<");
      display.setTextSize(2);                  //Podometro
      display.print("  PASOS  ");
      display.setTextSize(1);
      display.print(">");
      display.display();


      break;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 4:
      display.clearDisplay();
      display.display();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("   Menu principal");  //Mando
      display.setCursor(0, 15);
      display.setTextSize(1);
      display.print("<");
      display.setTextSize(2);
      display.print("  MANDO  ");
      display.setTextSize(1);
      display.print(">");
      display.display();


      break;
      ///////////////////////////////////////////////////////////////////////////////////////////////////////
  } //final del servicio de menu principal
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (intro == 1) {
    intro = 0;
    switch (select) {  //inicio servicio de ejecución de aplicaciones
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      case 0:    //Ajustes App
        display.clearDisplay();
        display.display();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("       Ajustes");  //Airplane Mode
        display.setCursor(0, 15);
        display.setTextSize(1);
        display.print("<");
        display.setTextSize(2);
        display.print(" Airmode ");
        display.setTextSize(1);
        display.print(">");
        display.display();
        select = 0;
        while (back == 0) {
          menuselect(2);
          switch (select) {

            case 0:   // Airplane Mode
              display.clearDisplay();
              display.display();
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.setCursor(0, 0);
              display.print("        Ajustes");  //Airplane Mode
              display.setCursor(0, 15);
              display.setTextSize(1);
              display.print("<");
              display.setTextSize(2);
              display.print(" Airmode ");
              display.setTextSize(1);
              display.print(">");
              display.display();

              break;


            case 1:    //About
              display.clearDisplay();
              display.display();
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.setCursor(0, 0);
              display.print("        Ajustes");  //ABOUT
              display.setCursor(0, 15);
              display.setTextSize(1);
              display.print("<");
              display.setTextSize(2);
              display.print("  ABOUT  ");
              display.setTextSize(1);
              display.print(">");
              display.display();

              break;

            case 2:    //Invert colors
              display.clearDisplay();
              display.display();
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.setCursor(0, 0);
              display.print("        Ajustes");  //INVERT
              display.setCursor(0, 15);
              display.setTextSize(1);
              display.print("<");
              display.setTextSize(2);
              display.print(" INVERT  ");
              display.setTextSize(1);
              display.print(">");
              display.display();
              break;




          }

          waitforlow();
          if (intro == 1) {

            switch (select) {
              ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

              case 0:
                display.clearDisplay();
                display.display();
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.setCursor(0, 0);
                display.print("    Airmode");           //Airmode
                display.setCursor(0, 15);
                display.setTextSize(1);
                display.print("<");
                display.setTextSize(2);
                display.print("    ON   ");
                display.setTextSize(1);
                display.print(">");
                display.display();

                select = 0;
                while (back == 0) {

                  menuselect(1);
                  switch (select) {
                    case 0:
                      display.clearDisplay();
                      display.display();
                      display.setTextSize(1);
                      display.setTextColor(WHITE);
                      display.setCursor(0, 0);
                      display.print("    Airmode");
                      display.setCursor(0, 15);
                      display.setTextSize(1);
                      display.print("<");
                      display.setTextSize(2);
                      display.print("    ON   ");
                      display.setTextSize(1);
                      display.print(">");
                      display.display();
                      break;

                    case 1:
                      display.clearDisplay();
                      display.display();
                      display.setTextSize(1);
                      display.setTextColor(WHITE);                //On off mechanism
                      display.setCursor(0, 0);
                      display.print("       Airmode");
                      display.setCursor(0, 15);
                      display.setTextSize(1);
                      display.print("<");
                      display.setTextSize(2);
                      display.print("   OFF   ");
                      display.setTextSize(1);
                      display.print(">");
                      display.display();
                      break;
                  }
                  if (intro == 1) {
                    back = 0;
                    waitforlow();
                    switch (select) {
                      case 0:
                        digitalWrite(bluetooth, HIGH);
                        break;

                      case 1:
                        digitalWrite(bluetooth, LOW);
                        break;


                    }
                  }
                }

              ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
              case 1:

                display.clearDisplay();
                display.display();
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.setCursor(0, 0);
                display.print("       About \n     PatxiOS 3.0 \n   By Patxielsucio \n      23/9/16");           //About Hay que poner al final la fecha en la que se ha acabado
                display.display();
                while (back == 0) {
                  menuselect(0);
                }
                select = 0;
                break;
              ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
              case 2:
                display.clearDisplay();
                display.display();
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.setCursor(0, 0);
                display.print("    INVERT");           //INVERT
                display.setCursor(0, 15);
                display.setTextSize(1);
                display.print("<");
                display.setTextSize(2);
                display.print("    ON   ");
                display.setTextSize(1);
                display.print(">");
                display.display();

                select = 0;
                while (back == 0) {

                  menuselect(1);
                  switch (select) {
                    case 0:
                      display.clearDisplay();
                      display.display();
                      display.setTextSize(1);
                      display.setTextColor(WHITE);
                      display.setCursor(0, 0);
                      display.print("     INVERT");
                      display.setCursor(0, 15);
                      display.setTextSize(1);
                      display.print("<");
                      display.setTextSize(2);
                      display.print("    ON   ");
                      display.setTextSize(1);
                      display.print(">");
                      display.display();
                      break;

                    case 1:
                      display.clearDisplay();
                      display.display();
                      display.setTextSize(1);
                      display.setTextColor(WHITE);                //On off mechanism
                      display.setCursor(0, 0);
                      display.print("       INVERT");
                      display.setCursor(0, 15);
                      display.setTextSize(1);
                      display.print("<");
                      display.setTextSize(2);
                      display.print("   OFF   ");
                      display.setTextSize(1);
                      display.print(">");
                      display.display();
                      break;
                  }
                  if (intro == 1) {
                    back = 0;
                    waitforlow();
                    switch (select) {
                      case 0:
                        display.invertDisplay(1);
                        break;

                      case 1:
                        display.invertDisplay(0);
                        break;


                    }
                  }
                }
            }
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            display.clearDisplay();
            display.display();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(0, 0);
            display.print("        Ajustes");  //Airplane Mode
            display.setCursor(0, 15);
            display.setTextSize(1);
            display.print("<");
            display.setTextSize(2);
            display.print(" Airmode ");
            display.setTextSize(1);
            display.print(">");
            display.display();
            back = 0;

          }

        }
        display.clearDisplay();
        display.display();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("   Menu principal");  //Ajustes
        display.setCursor(0, 15);
        display.setTextSize(1);
        display.print("<");
        display.setTextSize(2);
        display.print(" AJUSTES ");
        display.setTextSize(1);
        display.print(">");
        display.display();
        back = 0;
        select = 0;
        break;
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      case 1:  //Led App
        display.clearDisplay();
        display.display();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("       LED");
        display.setCursor(0, 15);
        display.setTextSize(1);
        display.print("<");
        display.setTextSize(2);
        display.print("   ON    ");
        display.setTextSize(1);
        display.print(">");
        display.display();


        select = 0;
        while (back == 0) {

          menuselect(1);
          switch (select) {
            case 0:
              display.clearDisplay();
              display.display();
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.setCursor(0, 0);
              display.print("       LED");
              display.setCursor(0, 15);
              display.setTextSize(1);
              display.print("<");
              display.setTextSize(2);
              display.print("   ON    ");
              display.setTextSize(1);
              display.print(">");
              display.display();
              break;

            case 1:
              display.clearDisplay();
              display.display();
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.setCursor(0, 0);
              display.print("       LED");
              display.setCursor(0, 15);
              display.setTextSize(1);
              display.print("<");
              display.setTextSize(2);
              display.print("   OFF   ");
              display.setTextSize(1);
              display.print(">");
              display.display();
              break;


          }
          if (intro == 1) {

            switch (select) {

              case 0:
                digitalWrite(LED, HIGH);
                break;

              case 1:
                digitalWrite(LED, LOW);

                break;





            }

          }
        }

        display.clearDisplay();
        display.display();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("   Menu principal");
        display.setCursor(0, 15);
        display.setTextSize(1);
        display.print("<");
        display.setTextSize(2);
        display.print(" AJUSTES ");
        display.setTextSize(1);
        display.print(">");
        display.display();
        select = 0;
        break;
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      case 2://chrono app
        display.clearDisplay();
        display.display();
        display.setCursor(35, 10);
        display.setTextSize(2);
        display.println("0:0:0");
        back = 0;

        while (back == 0 ) {

          display.setCursor(0, 0);
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.println("A:START B:STOP C:RST"); //Chrono App
          display.display();

          if (digitalRead(butC) == HIGH) {
            timer[0] = 0;
            timer[1] = 0;
            timer[2] = 0;
            timer[3] = 0;
            display.clearDisplay();
            display.display();
            display.setCursor(0, 0);
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.println("A:START B:STOP C:RST");
            display.setTextSize(2);

            display.setTextColor(WHITE);
            display.setCursor(35, 10);
            display.print(timer[3]);
            display.print(":");
            display.print(timer[2]);
            display.print(":");
            display.print(timer[1]);
            display.display();

          }

          if (digitalRead(butD) == HIGH) {
            back++;
          }

          if (digitalRead(butA) == HIGH) {
            display.clearDisplay();
            display.display();
            display.setCursor(0, 0);
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.println("A:START B:STOP C:RST");




            while (digitalRead(butB) != HIGH) {
              delay(1);


              timer[0]++;
              if (timer[0] == 40) {
                display.setTextSize(2);

                display.setTextColor(BLACK);
                display.setCursor(35, 10);
                display.print(timer[3]);
                display.print(":");
                display.print(timer[2]);
                display.print(":");
                display.print(timer[1]);
                display.display();
                timer[1]++;
                timer[0] = 0;

              }
              if (timer[1] == 60) {
                display.setTextSize(2);

                display.setTextColor(BLACK);
                display.setCursor(35, 10);
                display.print(timer[3]);
                display.print(":");
                display.print(timer[2]);
                display.print(":");
                display.print(timer[1]);
                display.display();
                timer[2]++;
                timer[1] = 0;
              }
              if (timer[2] == 60) {
                display.setTextSize(2);

                display.setTextColor(BLACK);
                display.setCursor(35, 10);
                display.print(timer[3]);
                display.print(":");
                display.print(timer[2]);
                display.print(":");
                display.print(timer[1]);
                display.display();
                timer[3]++;
                timer[2] = 0;
              }

              display.setTextSize(2);
              display.setTextColor(WHITE);
              display.setCursor(35, 10);
              display.print(timer[3]);
              display.print(":");
              display.print(timer[2]);
              display.print(":");
              display.print(timer[1]);
              display.display();
            }
          }
        }
        break;
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      case 3:
        display.clearDisplay();
        display.display();
        display.setCursor(0, 0);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.println("  STEPS  B:RESET");
        display.setCursor(55, 10);
        display.setTextSize(2);
        display.println(steps);
        display.display();


        back = 0;
        while (back == 0) {



          if (Serial.available()) {
            if (Serial.read() == 'S') {

              display.setTextColor(BLACK);             //Podometer en un futuro se podria poner con el menuselect y unos calculos de los metros kilometros y demas
              display.setTextSize(2);
              display.setCursor(55, 10);
              display.print(steps);
              display.display();
              steps++;
              display.setTextColor(WHITE);

              display.setCursor(55, 10);
              display.setTextSize(2);
              display.print(steps);
              display.display();
            }
          }
          if (digitalRead(butD) == HIGH) {
            waitforlow();
            back++;
          }
          if (digitalRead(butB) == HIGH) {
            waitforlow();
            display.setTextColor(BLACK);
            display.setTextSize(2);
            display.setCursor(55, 10);
            display.print(steps);
            display.display();
            steps = 0;
            display.setTextColor(WHITE);

            display.setCursor(55, 10);
            display.setTextSize(2);
            display.print(steps);
            display.display();
          }
        }
        display.clearDisplay();
        display.display();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("   Menu principal");
        display.setCursor(0, 15);
        display.setTextSize(1);
        display.print("<");
        display.setTextSize(2);
        display.print(" AJUSTES ");
        display.setTextSize(1);
        display.print(">");
        display.display();
        select = 0;
        break;
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      case 4:
        display.clearDisplay();
        display.display();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("      Remote");
        display.setCursor(0, 15);
        display.setTextSize(1);
        display.print("<");
        display.setTextSize(2);
        display.print(" SEND A ");
        display.setTextSize(1);
        display.print(">");
        display.display();
        select = 0;
        while (back == 0) {
          menuselect(3);
          switch (select) {
            case 0:
              display.clearDisplay();
              display.display();
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.setCursor(0, 0);
              display.print("      Remote");
              display.setCursor(0, 15);
              display.setTextSize(1);
              display.print("<");
              display.setTextSize(2);
              display.print(" SEND A ");
              display.setTextSize(1);
              display.print(">");
              display.display();
              break;

            case 1:
              display.clearDisplay();
              display.display();
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.setCursor(0, 0);
              display.print("      Remote");
              display.setCursor(0, 15);
              display.setTextSize(1);
              display.print("<");
              display.setTextSize(2);
              display.print(" SEND B ");
              display.setTextSize(1);
              display.print(">");
              display.display();
              break;

            case 2:
              display.clearDisplay();
              display.display();
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.setCursor(0, 0);
              display.print("      Remote");
              display.setCursor(0, 15);
              display.setTextSize(1);
              display.print("<");
              display.setTextSize(2);
              display.print(" SEND C ");
              display.setTextSize(1);
              display.print(">");
              display.display();
              break;

            case 3:
              display.clearDisplay();
              display.display();
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.setCursor(0, 0);
              display.print("      Remote");
              display.setCursor(0, 15);
              display.setTextSize(1);
              display.print("<");
              display.setTextSize(2);
              display.print(" SEND D ");
              display.setTextSize(1);
              display.print(">");
              display.display();
              break;


          }
          if (intro == 1) {

            switch (select) {

              case 0:
                Serial.println("A");
                break;

              case 1:
                Serial.println("B");
                break;

              case 2:
                Serial.println("C");
                break;

              case 3:
                Serial.println("D");
                break;





            }

          }
        }
        display.clearDisplay();
        display.display();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("   Menu principal");
        display.setCursor(0, 15);
        display.setTextSize(1);
        display.print("<");
        display.setTextSize(2);
        display.print(" AJUSTES ");
        display.setTextSize(1);
        display.print(">");
        display.display();
        select = 0;
        break;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  }   //final servicio de ejecución de aplicaciones
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}

