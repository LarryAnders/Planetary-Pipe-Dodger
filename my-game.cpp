// Game Name: Planetary Pipe Dodger!!!!!
// Written by: Larry Anderson
// Date: 11/16/2022
//
// Instructions: In this game, the player will be a ball, and will have to 
// dodge pipes that are moving toward them. The player will move by pressing "G" to invert gravity
//


#include "graphics.h"
#include <string>
#include <random>
#include <list>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int BACKGROUND_COLOR = BLACK;
const int TEXT_COLOR = RED;

struct PipeCoordinates {
	double x1;
	double x2;
	double y1;
	double y2;
};

//Random Engine
//random_device myEngine;
//uniform_real_distribution<double> randomReal(0.0, 1.0);

void drawPipes(PipeCoordinates topPipe, PipeCoordinates botPipe, int color);
void showScore(int sc);
void welcomeScreen();


int main()
{
	bool keepGoing = true;   // Keep running while this is true
	bool alive = true;       // keep creating pipes while alive
	bool gravityOn = false;      // turn on gravity, which changes velocity

	char keyPressed;
	int i, j, k;					// for loops
	int color = GREEN;

	double pointX1, pointY1; // Current position of point 1
	double prevX1, prevY1;   // Previous position of point 1
	double yVel1;     // Velocity of point 1

	double xTopVel1, xTopVel2;   // Velocity of Top pipe
	double xBotVel1, xBotVel2;   // Velocity of Bottom pipe

	PipeCoordinates topPipe[50];   // Create 50 top pipes
	PipeCoordinates botPipe[50];   // Create 50 bot pipes
	PipeCoordinates prevtopPipe[50];
	PipeCoordinates prevbotPipe[50];

	int score = 0;

	// Set Initial Position of player
	pointX1 = 750;
	pointY1 = 425;

	// Set Initial Velocity
	yVel1 = 3.4;
	xTopVel1 = -4.0;
	xTopVel2 = -4.0;
	xBotVel1 = -4.0;
	xBotVel2 = -4.0;


	initwindow(1500, 850, (char*) "!!!PLANETARY PIPE DODGER!!!", 10, 10);

	welcomeScreen();

	bool playAgain = true;

	while (playAgain) {
		// Main Game

		for (i = 0; i < 50; i++) {      // Reset pipes initial coordinates if user plays again

			topPipe[i].x1 = 0;
			topPipe[i].x2 = 0;
			topPipe[i].y1 = 0;
			topPipe[i].y2 = 0;

			botPipe[i].x1 = 0;
			botPipe[i].x2 = 0;
			botPipe[i].y1 = 0;
			botPipe[i].y2 = 0;

		}

		for (i = 0, k = 1550; i < 50; i++, k += 175) {      // Set pipes initial coordinates
			j = 20 + (rand() % 306);

			topPipe[i].x1 = k;
			topPipe[i].x2 = k + 30;
			topPipe[i].y1 = -10;
			topPipe[i].y2 = j;

			botPipe[i].x1 = k;
			botPipe[i].x2 = k + 30;
			botPipe[i].y1 = 860;
			botPipe[i].y2 = j + 250;

		}
		score = 0;
		showScore(score);

		while (keepGoing) {
			delay(50);

			//Call drawPipes funtion to draw all pipes at once
			
			for (i = 0; i < 50; i++) {
				drawPipes(topPipe[i], botPipe[i], color);
				color = ((color + 1) % 15) + 1;
			}


			// -------------- Move and Control the Point Positions ---------------

			// Remember previous player position so we can erase it later
			prevX1 = pointX1;
			prevY1 = pointY1;

			// Remember previous pipe positions so we can erase them later

			for (i = 0; i < 50; i++) {

				prevtopPipe[i] = topPipe[i];
				prevbotPipe[i] = botPipe[i];
			}

			// Calculate distance between objects at any given moment
			double distanceTop[50];
			double distanceBot[50];

			for (i = 0; i < 50; i++) {

				distanceTop[i] = sqrt((pow(pointX1 - topPipe[i].x2, 2) + pow(pointY1 - topPipe[i].y2, 2)));
				distanceBot[i] = sqrt((pow(pointX1 - botPipe[i].x2, 2) + pow(pointY1 - botPipe[i].y2, 2)));
			}


			// Move the position (Add Velocity to Position)

			pointY1 += yVel1;

			// Move pipe position (Add Velocity to Pipes)

			for (i = 0; i < 50; i++) {

				topPipe[i].x1 += xTopVel1;
				topPipe[i].x2 += xTopVel2;
				botPipe[i].x1 += xBotVel1;
				botPipe[i].x2 += xBotVel2;
			}

			// If there's gravity, add to y velocity
			if (gravityOn) {
				yVel1 += 5.0;
			}
			if (!gravityOn) {
				yVel1 += -5.0;
			}


			setcolor(BLACK);
			setfillstyle(SOLID_FILL, BLACK);
			fillellipse((int)prevX1, (int)prevY1, 20, 20);


			// Erase old pipes
			for (i = 0; i < 50; i++) {

				setcolor(BLACK);
				setfillstyle(SOLID_FILL, BLACK);
				bar(prevtopPipe[i].x1, prevtopPipe[i].y1, prevtopPipe[i].x2, prevtopPipe[i].y2);
				bar(prevbotPipe[i].x1, prevbotPipe[i].y1, prevbotPipe[i].x2, prevbotPipe[i].y2);

				setcolor(GREEN);
				setfillstyle(SOLID_FILL, GREEN);
				bar(topPipe[i].x1, topPipe[i].y1, topPipe[i].x2, topPipe[i].y2);
				bar(botPipe[i].x1, botPipe[i].y1, botPipe[i].x2, botPipe[i].y2);
			}

			// -------------- Check to see if a key has been pressed ---------------------
			if (kbhit()) {
				keyPressed = getch();

				// KEY: Q or ESC pressed
				if (keyPressed == 'q' || keyPressed == 'Q' || keyPressed == 0x1b) {  // q - quit, 0x1b is ESC key
					setbkcolor(RED);
					keepGoing = false;
				}// end if (Q)

				// Toggle Gravity with G key
				//    This illustrates a shorter way to toggle
				if (keyPressed == 'g' || keyPressed == 'G')
					gravityOn = !gravityOn;

			}//end if kbhit()


			// -------------- Draw Object in new Position ---------------

			// Draw object in new position
			// Draw filled in circle at pointX1, pointY1
			fillellipse((int)pointX1, (int)pointY1, 20, 20);

			// Bounce off walls by reversing velocity if it's near edge

			// Bounce off top/bottom walls
			if (pointY1 > 865.0 && prevY1 < 865.0) {
				pointY1 = 0.0;
				//yVel1 *= -1.0; // another way to multiply by -1

				setcolor(BLUE);
				setfillstyle(SOLID_FILL, BLUE);
				bar((int)pointX1 - 5, (int)pointY1 - 5, (int)pointX1 + 5, (int)pointY1 + 5);
			}

			if (pointY1 < -10.0 && prevY1 > -10.0) {
				pointY1 = 850.0;
				//yVel1 *= -1.0;

				setcolor(BLUE);
				setfillstyle(SOLID_FILL, BLUE);
				bar((int)pointX1 - 5, (int)pointY1 - 5, (int)pointX1 + 5, (int)pointY1 + 5);
			}

			for (i = 0; i < 50; i++) {

				if (topPipe[i].x2 < 740 && topPipe[i].x2 > 735) {
					score += 1;
					showScore(score);
				}
			}

			if (yVel1 > 40 || yVel1 < -40) {
				yVel1 /= 2;
			}

			for (i = 0; i < 50; i++) {

				//Check if player comes in contact with top pipes
				if ((pointY1 +20) < topPipe[i].y2 && (pointX1 + 20) >= topPipe[i].x1 && (pointX1 + 20) <= (topPipe[i].x1 + 30)) {    
					
					keepGoing = false;
				}

				if ((pointY1 - 20) < topPipe[i].y2 && (pointX1 - 20) >= topPipe[i].x1 && (pointX1 - 20) <= (topPipe[i].x1 + 30)) {

					keepGoing = false;
				}

				//Check if player came in contact with bottom pipes
				if ((pointY1 + 25) > botPipe[i].y2 && (pointX1 + 20) >= botPipe[i].x2 && (pointX1 + 20) <= (botPipe[i].x2 + 30)) {

					keepGoing = false;
				}

				if ((pointY1 - 25) > botPipe[i].y2 && (pointX1 - 20) >= botPipe[i].x2 && (pointX1 - 20) <= (botPipe[i].x2 + 30)) {

					keepGoing = false;
				}

			}
			
		} // end while kbhit

		// After while(keepGoing), the game is over


			// Game has ended

		outtextxy(10, 10, (char*)"GAME OVER, Play Again (Y/N)");
		showScore(score);
		keyPressed = getch();
		if (keyPressed == 'y' || keyPressed == 'Y') {
			welcomeScreen();
			cleardevice();
			keepGoing = true;
		}
		else if (keyPressed == 'n' || keyPressed == 'N') {
			playAgain = false;
		}

	}  // Main "Play Again" loop

	return 0;
} // end main()

// Welcome Screen Function
void welcomeScreen() {
	setbkcolor(BACKGROUND_COLOR);
	cleardevice();

	setcolor(BLACK);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
	outtextxy(550, 150, (char*) "Welcome to ");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
	setcolor(RED);
	outtextxy(150, 250, (char*) "!!!PLANETARY PIPE DODGER!!!");
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
	outtextxy(10, 350, (char*)"*************************************************************");
	setcolor(GREEN);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	outtextxy(290, 400, (char*)"WARNING!!!! YOUR PLANET WAS SUCKED INTO A PIPE FILLED WORM HOLE");
	outtextxy(225, 450, (char*)"DO YOUR BEST TO DODGE THEM ALL AND KEEP YOUR PLANET'S INHABITANTS ALIVE!!!!");
	setcolor(BROWN);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	outtextxy(300, 800, (char*)"*Forgive the wacky colors, I'm colorblind, but they look cool to me*");
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
	outtextxy(250, 500, (char*)"Controls : Press - G - to invert gravity");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	outtextxy(220, 540, (char*)"Objective : Steer your planet from touching the pipes by inverting gravity.");

	getch();
	cleardevice();
}



// Draw Pipes to dodge
void drawPipes(PipeCoordinates topPipe, PipeCoordinates botPipe, int color) {
	setcolor(color);
	setfillstyle(SOLID_FILL, color);
	bar(topPipe.x1, topPipe.y1, topPipe.x2, topPipe.y2);
	bar(botPipe.x1, botPipe.y1, botPipe.x2, botPipe.y2);
	
}

void showScore(int sc)
{
	char s[20]; // An array of char, which is a string
	sprintf_s(s, "Score: %d", sc); // "print" 400 into a string

	setcolor(WHITE);
	outtextxy(20, 50, &s[0]); // Draw that string in the graphics window
}