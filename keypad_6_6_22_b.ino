// libraries
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Keypad.h>
#include <Encoder.h>
#include <Bounce2.h>
#include "HID-Project.h"
#include <Fonts/Org_01.h>
// defines
#define SCREEN_WIDTH 128	// OLED display width, in pixels
#define SCREEN_HEIGHT 32	// OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1	// Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Keypad buttons
int R1 = 6;
int R2 = 5;
int R3 = 21;
int R4 = 20;
int C1 = 7;
int C2 = 8;
int C3 = 9;
const byte ROWS = 4;
const byte COLS = 3;
char keys[COLS][ROWS] = {  // define keypad matrix
	{'X','7','4','1'},
	{'*','8','5','2'},
	{'-','9','6','3'}
};
byte rowPins[ROWS] = {R1, R2, R3, R4};
byte colPins[COLS] = {C1, C2, C3};
Keypad kpd = Keypad( makeKeymap(keys), colPins, rowPins, COLS, ROWS);
//State LED pins
int S1 = 15;
int S2 = 14;
int S3 = 16;
int S4 = 10;
const int numStates = 4;
const int States[numStates] = {S1, S2, S3, S4};
int currentState = 0;
int lastDebounceTime = 0;
const int debounceTime = 50;
//Encoder
int SW = 19;
int DT = 2;
int CLK = 18;
Encoder volumeKnob(DT,CLK);
Bounce encoderButton = Bounce(SW,10);
int timeLimit = 500;
long oldPosition = -999;
// user defined functions
void modeLEDDisplay()	{
	digitalWrite(States[currentState], HIGH);
	}
void mapLayer1()	{
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(1);
	display.setFont(&Org_01);
	display.setCursor(15, 5);
	display.println("F3");
	display.setCursor(55, 5);
	display.println("SAP");
	display.setCursor(102, 5);
	display.println("F8");
	display.setCursor(6, 15);
	display.println("SLEEP");
	display.setCursor(49, 15);
	display.println("LOGIN");
	display.setCursor(92, 15);
	display.println("FILES");
	display.setCursor(9, 25);
	display.println("SWAP");
	display.setCursor(49, 25);
	display.println("STOCK");
	display.setCursor(90, 25);
	display.println("H-UNIT");
	display.drawLine(0, 8, 128, 8, 1);
	display.drawLine(42, 0, 42, 26, 1);
	display.drawLine(84, 0, 84, 26, 1);
	display.drawLine(0, 18, 128, 18, 1);
	display.display();
}
void fileFunction()	{
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(2);
	display.setFont(&Org_01);
	display.setCursor(34, 8);
	display.println("File");
	display.drawRect(0, 12, 128, 4, 1);
	display.setCursor(28, 26);
	display.println("Explorer");
	display.display();
	delay(500);
}
void passwordFunction()	{
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(2);
	display.setFont(&Org_01);
	display.setCursor(34, 8);
	display.println("Access");
	display.drawRect(0, 12, 128, 4, 1);
	display.setCursor(28, 26);
	display.println("Granted");
	display.display();
	delay(500);
}
void huFunction()	{
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(2);
	display.setFont(&Org_01);
	display.setCursor(10, 14);
	display.println(F("HU Labels"));
	display.display();
}
void sleepFunction()  {
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(5);
	display.setFont(&Org_01);
	display.setCursor(8, 20);
	display.println("Sleep");
	display.display();
	delay(500);
}
void f8Function()	{
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(6);
	display.setFont(&Org_01);
	display.setCursor(30, 24);
	display.println("F8");
	display.display();
}
void f3Function()	{
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(6);
	display.setFont(&Org_01);
	display.setCursor(30, 24);
	display.println("F3");
	display.display();
}
void inventoryFunction()	{
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(3);
	display.setFont(&Org_01);
	display.setCursor(2, 16);
	display.println("inventory");
	display.fillCircle(3, 24, 2, 1);
	display.fillCircle(15, 22, 2, 1);
	display.fillCircle(27, 24, 2, 1);
	display.fillCircle(39, 22, 2, 1);
	display.fillCircle(51, 24, 2, 1);
	display.fillCircle(63, 22, 2, 1);
	display.fillCircle(75, 24, 2, 1);
	display.fillCircle(87, 22, 2, 1);
	display.fillCircle(99, 24, 2, 1);
	display.fillCircle(111, 22, 2, 1);
	display.fillCircle(123, 24, 2, 1);
	display.display();
	delay(500);
}
void switchFunction()	{
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(2);
	display.setFont(&Org_01);
	display.setCursor(4, 11);
	display.println("Switch");
	display.setCursor(22, 27);
	display.println("Applications");
	display.fillTriangle(70, 8, 78, 12, 78, 4, 1);
	display.fillTriangle(120, 8, 112, 12, 112, 4, 1);
	display.fillRect(79, 7, 33, 3, 1);
	display.display();
	delay(500);
}
void sapFunction()	{
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(2);
	display.setFont(&Org_01);
	display.setCursor(0, 10);
	display.setTextWrap(0);
	display.setCursor(47, 10);
	display.println("SAP");
	display.setTextWrap(0);
	display.setCursor(27, 24);
	display.println("Unlocked");
	display.display();
	delay(500);
}
void left2rightLEDFunction()	{
	int waitTime = 50;
	digitalWrite(S1, HIGH);
	delay(waitTime);
	digitalWrite(S2, HIGH);
	delay(waitTime);
	digitalWrite(S3, HIGH);
	delay(waitTime);
	digitalWrite(S4, HIGH);
	delay(waitTime);
	digitalWrite(S1, LOW);
	delay(waitTime);
	digitalWrite(S2, LOW);
	delay(waitTime);
	digitalWrite(S3, LOW);
	delay(waitTime);
	digitalWrite(S4, LOW);
	delay(waitTime);
	modeLEDDisplay();
}
void right2leftLEDFunction()	{
	int waitTime = 50;
	digitalWrite(S4, HIGH);
	delay(waitTime);
	digitalWrite(S3, HIGH);
	delay(waitTime);
	digitalWrite(S2, HIGH);
	delay(waitTime);
	digitalWrite(S1, HIGH);
	delay(waitTime);
	digitalWrite(S4, LOW);
	delay(waitTime);
	digitalWrite(S3, LOW);
	delay(waitTime);
	digitalWrite(S2, LOW);
	delay(waitTime);
	digitalWrite(S1, LOW);
	delay(waitTime);
	modeLEDDisplay();
}
void LEDslowdownFunction()	{
	digitalWrite(S1, HIGH);
	delay(200);
	digitalWrite(S1, LOW);
	digitalWrite(S2, HIGH);
	delay(300);
	digitalWrite(S2, LOW);
	digitalWrite(S3, HIGH);
	delay(500);
	digitalWrite(S3, LOW);
	digitalWrite(S4, HIGH);
	delay(1000);
	digitalWrite(S4, LOW);
	modeLEDDisplay();
}
void LEDspeedupFunction()	{
	digitalWrite(S1, HIGH);
	delay(800);
	digitalWrite(S1, LOW);
	digitalWrite(S2, HIGH);
	delay(500);
	digitalWrite(S2, LOW);
	digitalWrite(S3, HIGH);
	delay(300);
	digitalWrite(S3, LOW);
	digitalWrite(S4, HIGH);
	delay(200);
	digitalWrite(S4, LOW);
	modeLEDDisplay();
}
void blinkLED1()  {
	digitalWrite(S1, HIGH);
	delay(150);
	digitalWrite(S1, LOW);
	delay(150);
	modeLEDDisplay();
}
void blinkLED2()  {
	digitalWrite(S2, HIGH);
	delay(150);
	digitalWrite(S2, LOW);
	delay(150);
	modeLEDDisplay();
}
void blinkLED3()  {
	digitalWrite(S3, HIGH);
	delay(150);
	digitalWrite(S3, LOW);
	delay(150);
	modeLEDDisplay();
}
void blinkLED4()  {
	digitalWrite(S4, HIGH);
	delay(150);
	digitalWrite(S4, LOW);
	delay(150);
	modeLEDDisplay();
}
void scrollFunction()	{
	display.startscrollright(0x00, 0x0F);
	delay(100);
	display.startscrollleft(0x00, 0x0F);
	delay(100);
	display.startscrollright(0x00, 0x0F);
	delay(100);
	display.startscrollleft(0x00, 0x0F);
	delay(100);
	display.startscrollright(0x00, 0x0F);
	delay(100);
	display.startscrollleft(0x00, 0x0F);
	delay(100);
	display.startscrollright(0x00, 0x0F);
	delay(100);
	display.stopscroll();
	display.display();
}
void setup()	{  // put your setup code here, to run once ........................................SETUP
	Serial.begin(9600);
	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))	{ // Address 0x3D for 128x64
		Serial.println(F("SSD1306 allocation failed"));
	for(;;);
	}
	display.setRotation(2);
	delay(500);
	for(int i = 0; i < numStates; i++)	{
		pinMode(States[i], OUTPUT);
		digitalWrite(States[i], LOW);
	}
	pinMode(CLK, INPUT_PULLUP);
	Keyboard.begin();
//Consumer.begin();
	Serial.print("Ready");
	StartAnimation();
	digitalWrite(States[currentState], HIGH);
}
void StartAnimation()	{
	left2rightLEDFunction();
	right2leftLEDFunction();
	left2rightLEDFunction();
	right2leftLEDFunction();
	left2rightLEDFunction();
	right2leftLEDFunction();
	return;
}
void ChangeState()	{
	digitalWrite(States[currentState], LOW);
	currentState++;
	if (currentState == numStates)	{
		currentState = 0;
	}
	left2rightLEDFunction();
	right2leftLEDFunction();
	digitalWrite(States[currentState], HIGH);
	Serial.print("State Changed. Current State: ");
	Serial.println(currentState);
	delay(100);
	return;
}
void Layout1(char button)	{	//layout 1 of 4
	switch(button)	{
//button col 1 row 4 mode 1
		case '1':
//light LED 2
			blinkLED2();
//keystrokes
			Keyboard.press(KEY_LEFT_ALT);
			Keyboard.press(KEY_TAB);
			Keyboard.releaseAll();
//display button id
			switchFunction();
//return to key legend
			mapLayer1();
			break;
//button col 2 row 4 mode 1
		case '2':
//light LED 3
			blinkLED3();
//keystrokes
			Keyboard.press(KEY_F3);
			Keyboard.releaseAll();
			delay(300);
			Keyboard.press(KEY_LEFT_CTRL);
			Keyboard.print('/');
			Keyboard.releaseAll();
			delay(300);
			Keyboard.print('M');
			Keyboard.print('D');
			Keyboard.print('0');
			Keyboard.print('4');
			delay(600);
			Keyboard.press(KEY_ENTER);
			Keyboard.releaseAll();
//display button id
			inventoryFunction();
//return to key legend
			mapLayer1();
			break;
//button col 3 row 4 mode 1
		case '3':
//light LED 4
			blinkLED4();
//keystrokes
			Keyboard.press(KEY_F3);
			Keyboard.releaseAll();
			delay(300);
			Keyboard.press(KEY_LEFT_CTRL);
			Keyboard.print('/');
			Keyboard.releaseAll();
			delay(300);
			Keyboard.print('Z');
			Keyboard.print('H');
			Keyboard.print('U');
			Keyboard.print('L');
			Keyboard.print('B');
			Keyboard.print('L');
			delay(600);
			Keyboard.press(KEY_ENTER);
			Keyboard.releaseAll();
			delay(4000);
			Keyboard.press(KEY_TAB);
			Keyboard.releaseAll();
			delay(400);
			Keyboard.press(KEY_TAB);
			Keyboard.releaseAll();
			Keyboard.print('1');
			delay(300);
			Keyboard.press(KEY_F8);
			Keyboard.releaseAll();
			delay(300);
			Keyboard.press(KEY_F3);
			Keyboard.releaseAll();
			delay(300);
//display button id
			huFunction();
// Scroll
			scrollFunction();
//return to key legend
			mapLayer1();
			break;
//button col 1 row3 mode 1
		case '4':
//light LED 2
			blinkLED2();
//keystrokes
			Keyboard.press(KEY_LEFT_GUI);
			Keyboard.print('l');
			Keyboard.releaseAll();
//display button id
			sleepFunction();
//return to key legend
			mapLayer1();
			break;
//button col 2 row 3 mode 1
		case '5':
//light LED 3
			blinkLED3();
//keystrokes
			Keyboard.print("@lphaT3ch");
			delay(100);
			Keyboard.press(KEY_RETURN);
			Keyboard.releaseAll();
//display button id
			passwordFunction();
//return to key legend
			mapLayer1();
			break;
//button col 3 row 3 mode 1
		case '6':
//light LED 4
			blinkLED4();
//keystrokes
			Keyboard.press(KEY_LEFT_GUI);
			Keyboard.print('e');
			Keyboard.releaseAll();
//display button id
			fileFunction();
//return to key legend
			mapLayer1();
			break;
//button col 1 row 2 mode 1
		case '7':
//light LED 2
			blinkLED2();
//Keystrokes
			Keyboard.press(KEY_F3);
			Keyboard.releaseAll();
//display button id
			f3Function();
//scroll
			scrollFunction();
//return to key legend
			mapLayer1();
			break;
//button col 2 row 2 mode 1
		case '8':
//light LED 3
			blinkLED3();
//keystrokes
			Keyboard.print("xrandellr");
			delay(100);
			Keyboard.press(KEY_TAB);
			delay(100);
			Keyboard.print("Sap2l0gin=");
			delay(100);
			Keyboard.press(KEY_RETURN);
			Keyboard.releaseAll();
//display button id
			sapFunction();
//return to key legend
			mapLayer1();
			break;
//button col 3 row 2 mode 1
		case '9':
//light LED 4
			blinkLED4();
//keystrokes
			Keyboard.press(KEY_F8);
			Keyboard.releaseAll();
//display button id
			f8Function();
//scroll
			scrollFunction();
//return to main menu
			mapLayer1();
			break;
	};
}
void Layout2(char button)	{	//layout 2 of 4
	switch(button)	{
		case '1':
			Keyboard.print('1');
			break;
		case '2':
			Keyboard.print('2');
			break;
		case '3':
			Keyboard.print('3');
			break;
		case '4':
			Keyboard.print('4');
			break;
		case '5':
			Keyboard.print('5');
			break;
		case '6':
			Keyboard.print('6');
			break;
		case '7':
			Keyboard.print('7');
			break;
		case '8':
			Keyboard.print('8');
			break;
		case '9':
			Keyboard.print('9');
			break;
	};
}
void Layout3(char button)	{	//layout 3 of 4
	switch(button)	{
		case '1':
			Keyboard.print('7');
			break;
		case '2':
			Keyboard.print('8');
			break;
		case '3':
			Keyboard.print('9');
			break;
		case '4':
			Keyboard.print('4');
			break;
		case '5':
			Keyboard.print('5');
			break;
		case '6':
			Keyboard.print('6');
			break;
		case '7':
			Keyboard.print('1');
			break;
		case '8':
			Keyboard.print('2');
			break;
		case '9':
			Keyboard.print('3');
			break;
	};
}
void Layout4(char button)	{	//layout 4 of 4
	switch(button)	{
		case '1':
			Keyboard.print('1');
			break;
		case '2':
			Keyboard.print('2');
			break;
		case '3':
			Keyboard.print('3');
			break;
		case '4':
			Keyboard.print('4');
			break;
		case '5':
			Keyboard.print('5');
			break;
		case '6':
			Keyboard.print('6');
			break;
		case '7':
			Keyboard.print('7');
			break;
		case '8':
			Keyboard.print('8');
			break;
		case '9':
			Keyboard.print('9');
			break;
	};
}
void loop()	{	// code that loops ...............................................................LOOP
//check the key matrix first
	char key = kpd.getKey();
	if(key)	{
		switch(key)	{
			case '-':
				ChangeState();
				break;
			case '*':
				Keyboard.press(KEY_RIGHT_CTRL);
				Keyboard.press('s');
				delay(10);
				Keyboard.releaseAll();
				break;
			default:
		switch(currentState) {
			case 0:
				Layout1(key);
				break;
			case 1:
				Layout2(key);
				break;
			case 2:
				Layout3(key);
				break;
			case 3:
				Layout4(key);
				break;
			}
		}
	}
//check the encoder button
	if(encoderButton.update())	{
		if(encoderButton.fallingEdge())	{
			int fall = millis();
			while(!encoderButton.update())	{
				if(encoderButton.risingEdge())	{
					int rise = millis();
//Serial.println(rise - fall);
					if(rise - fall > timeLimit)	{
						Consumer.write(MEDIA_NEXT);
						Serial.print("Next");
						LEDspeedupFunction();
					} 
					else	{
						Consumer.write(MEDIA_PLAY_PAUSE);
						Serial.print("Play/Pause");
						LEDslowdownFunction();
					}
				}
				Keyboard.releaseAll();
			}
		}
	}
//check encoder rotation
	long newPosition = volumeKnob.read();
	if(newPosition != oldPosition)	{
		Serial.print(newPosition);
    if((newPosition - oldPosition) > 0)	{
//volumeup
			Serial.println("volume up");
			Consumer.write(MEDIA_VOLUME_UP);
			left2rightLEDFunction();
    } 
    else	{
//volumedown
			Serial.println("volume down");
			Consumer.write(MEDIA_VOLUME_DOWN);
			Consumer.write(MEDIA_VOLUME_DOWN);
			Consumer.write(MEDIA_VOLUME_DOWN);
			right2leftLEDFunction();
    }
		oldPosition = newPosition;
		Keyboard.releaseAll();
    delay(200); //a delay of 200 seems to be the sweet spot for this encoder.	
	}
}
