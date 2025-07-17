void tft_init()
{
  tft.reset();
  uint16_t identifier = tft.readID();

  // Print raw identifier to Serial Monitor
  Serial.print("TFT identifier: 0x  ");
  Serial.println(identifier, HEX); // print in hexadecimal

  if (identifier == 0x101){
    identifier = 0x9341;
  }

  Serial.println("TFT initialized!!");
  tft.begin(identifier);

  tft.setRotation(3);
  screenStatus = 0;
  startScreen();
}


void printText(int curX, int curY, int textSize, String text)
{
  tft.fillScreen(BLACK);
  tft.setCursor(curX, curY);
  tft.setTextColor(RED);
  tft.setTextSize(textSize);
  tft.println(text);
}

void startScreen()
{
  tft.fillScreen(BLACK);
  tft.setCursor(25, 40);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");
  tft.setCursor(150, 130);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("By");
  tft.setCursor(45, 160);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("Prasun");
  tft.setCursor(20, 220);
  tft.setTextColor(RED);  tft.setTextSize(2);
  tft.println("Touch anywhere to START");

}

void modeScreen()
{
  tft.fillScreen(BLACK);

  tft.setCursor(25, 1);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");

  tft.setCursor(60, 60);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("Select Mode");

  buttons[0].initButton(&tft, 150, 120, 160, 40, BLACK, BLUE, WHITE, "Auto", 4);
  buttons[0].drawButton();

  buttons[1].initButton(&tft, 150, 180, 160, 40, BLACK, YELLOW, BLACK, "Manual", 4);
  buttons[1].drawButton();

}

void autoScreen()
{
  tft.fillScreen(BLACK);

  tft.setCursor(25, 1);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");

  tft.setCursor(20, 60);
  tft.setTextColor(YELLOW);  tft.setTextSize(3);
  tft.println("Auto Search Mode");

  tft.setCursor(30, 120);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Select Number of Pins");

  buttons[0].initButton(&tft, 70, 180, 140, 40, WHITE, CYAN, BLACK, "14 Pins", 3);
  buttons[0].drawButton();

  buttons[1].initButton(&tft, 250, 180, 140, 40, WHITE, YELLOW, BLACK, "16 Pins", 3);
  buttons[1].drawButton();

}

void autoSearchResult(int mode, String number = "", String name = "", int count = 0)
{
  tft.fillScreen(BLACK);

  tft.setCursor(25, 1);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");

  tft.setCursor(60, 55);
  tft.setTextColor(YELLOW);  tft.setTextSize(3);
  tft.println("Auto Search");

  tft.setTextColor(YELLOW);
  tft.setCursor(90, 80);
  tft.println("Complete");
  //*************************************************************
  if (mode != 0)
  {
    number = "IC-" + number;

    tft.setTextColor(CYAN); tft.setTextSize(3);
    tft.setCursor(0, 130);
    tft.println(number);

    tft.setTextColor(WHITE); tft.setTextSize(2);
    tft.println(name);
    tft.println();


  }
  else
  {
    for (int i = 0; i < 3; i++)
    {
      tft.setCursor(40, 140);
      tft.setTextColor(BLACK);  tft.setTextSize(3);
      tft.print("NO MATCH FOUND");
      delay(500);
      tft.setCursor(40, 140);
      tft.setTextColor(RED);  tft.setTextSize(3);
      tft.print("NO MATCH FOUND");
      delay(500);

    }
  }
  //*************************************************************
  tft.setCursor(40, 220);
  tft.setTextColor(RED);  tft.setTextSize(2);
  if (mode == 0 || count == 0)
  {
    tft.println("Touch for MAIN MENU");
    getTouch();
    resetFunc();
  }
  else
  {
    tft.println("Touch to CONTINUE");
    getTouch();
  }
}

void searching(int i)
{
  if (i == 1)
  {
    tft.setTextColor(BLACK);
    tft.setCursor(70, 150);
    tft.println("Testing...");
    tft.setTextColor(MAGENTA);
    tft.setCursor(70, 150);
    tft.println("Testing.");


  }
  else if (i == 2)
  {
    tft.setTextColor(MAGENTA);
    tft.setCursor(70, 150);
    tft.println("Testing..");

  }
  else if (i == 3)
  {
    tft.setTextColor(MAGENTA);
    tft.setCursor(70, 150);
    tft.println("Testing...");

  }
  else if (i == -1)
  {
    tft.setTextColor(BLACK);
    tft.setCursor(70, 150);
    tft.println("Testing...");


  }

}

void manualScreen()
{
  tft.fillScreen(BLACK);

  tft.setCursor(25, 1);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");

  tft.setCursor(45, 60);
  tft.setTextColor(YELLOW);  tft.setTextSize(3);
  tft.println("Manual Search");
  tft.setCursor(125, 85);
  tft.println("Mode");

  tft.setCursor(60, 135);
  tft.setTextColor(WHITE);  tft.setTextSize(2);
  tft.println("Enter IC Number:");

  buttons[0].initButton(&tft, 200, 180, 200, 50, BLACK, BLUE, WHITE, "ENTER >", 4);
  buttons[0].drawButton();

}

void manualSearchResult(String number, String name, int status)
{

  tft.fillScreen(BLACK);
  tft.setCursor(25, 1);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");

  tft.setCursor(45, 55);
  tft.setTextColor(YELLOW);  tft.setTextSize(3);
  tft.println("Manual Search");

  tft.setTextColor(YELLOW);
  tft.setCursor(90, 80);
  tft.println("Complete");

  number = "IC-" + number;

  tft.setTextColor(CYAN); tft.setTextSize(3);
  tft.setCursor(0, 130);
  tft.println(number);

  if (status != -1)
  {
    tft.setTextColor(WHITE); tft.setTextSize(2);
    tft.println(name);
    tft.println();
  }
  for (int i = 0; i < 2; i++)
  {
    delay(500);
    tft.setCursor(0, 130);
    tft.setTextColor(BLACK); tft.setTextSize(3);
    tft.setCursor(0, 130);
    tft.println(number);
    delay(400);
    switch (status)
    {
      case 0 : tft.setTextColor(RED); tft.setTextSize(3);

        break;
      case 1 : tft.setTextColor(GREEN); tft.setTextSize(3);

        break;
      case -1 : tft.setTextColor(MAGENTA); tft.setTextSize(3);

        break;
    }
    tft.setCursor(0, 130);
    tft.println(number);
  }

  if (status == -1)
  {
    tft.setTextColor(RED);
    tft.println("IC NOT FOUND");

  }

  tft.setCursor(40, 220);
  tft.setTextColor(RED);  tft.setTextSize(2);
  tft.println("Touch for MAIN MENU");

  getTouch();
  resetFunc();
}

