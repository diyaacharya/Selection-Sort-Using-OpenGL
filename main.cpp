#include <GL/frglut.h>
#include <string>
#include <vector>
#include <chrono>
#include<bits/stdc++.h>
#include<time.h>
#include<unistd.h>

// Global Variables
// ----------------------------------------------------------------------------
const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;
std::vector<float> arrayElements;
std::vector<bool> isSorted;
int numElements = 10;
int sTime = 10;
int comparisons = 0;
int flag=0;

// Function Prototypes
// ----------------------------------------------------------------------------

void display();
void init();

void draw(int x, int y);
void generate();
void mydisplay();
void displayText(std::string textToDraw, int x, int y);
void displayTitle(std::string textToDraw, int x, int y);
void displayInfo();

void menuFunc(int id);
void createMenu();

void clear();
{
  glColor3f(1.0f,0.9f,0.0f); // sets color of the text
  glRasterPos2f(x, y);// screen coordinate at which text will appear
  int length = s.size();
  // writing charater by charater on the screen
  for(int i=0;i<length;i++)
  {
     glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, s[i]);
  }
}
void myKeyboardFunc( unsigned char key, int x, int y )

{
 switch(key)
 {
 case 13:if(flag==0) //Ascii of 'enter' key is 13
    flag=1;
  break;
       }
    mydisplay();
}
void drawstring(float x,float y,std::string s)
{
  glColor3f(1.0f,0.9f,0.0f); // sets color of the text
  glRasterPos2f(x, y);// screen coordinate at which text will appear
  int length = s.size();
  // writing charater by charater on the screen
  for(int i=0;i<length;i++)
  {
     glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, s[i]);
  }
}
void frontscreen(void)
{

glClearColor(0.0,0.0,0.0,0.1);
 glColor3f(0,0,1);
drawstring(SCREEN_WIDTH/4,0.97*SCREEN_HEIGHT,"VIDYAVARDHAKA COLLEGE OF ENGINNERING ");
 glColor3f(0,0,1); drawstring(0,0.96*SCREEN_HEIGHT,"-------------------------------------------------------------------------------------------------------------------------------------- ");

 drawstring(SCREEN_WIDTH/5,0.90*SCREEN_HEIGHT,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
 glColor3f(0,0,1);
drawstring(SCREEN_WIDTH/3,0.85*SCREEN_HEIGHT,"A MINI PROJECT ON SELECTION SORT");

 glColor3f(0,0,1);
 drawstring(1,0.75*SCREEN_HEIGHT,"Computer Graphics & Visualization Laboratory with Mini Project 18CSL67");

  glColor3f(0,0,1);
 drawstring(5,0.70*SCREEN_HEIGHT,"SUBMITED BY:");
 glColor3f(0,0,1);
 drawstring(40,0.65*SCREEN_HEIGHT,"Deepashree V.         (4VV20CS404)");
 drawstring(40,0.60*SCREEN_HEIGHT,"Diya Acharya         (4VV19CS188)");
 drawstring(40,0.55*SCREEN_HEIGHT,"Jyothsna MS.         (4VV19CS063)");
 glColor3f(0,0,1);
 drawstring(5,0.50*SCREEN_HEIGHT,"FACULTY INCHARGE:");
 glColor3f(0,0,1);
 drawstring(40,0.45*SCREEN_HEIGHT,"Prof. Arpitha MS");
 drawstring(40,0.40*SCREEN_HEIGHT,"Prof. Harshitha K");

 drawstring(SCREEN_WIDTH/1.5,0.35*SCREEN_HEIGHT,"PRESS ENTER TO START---->");
 glFlush();
}
void mydisplay()
{
 
 glClearColor(0.2,0.2,0.2,0);
 if(flag==0)
   frontscreen ();
 if(flag==1)
  display(); 
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sorting Algorithm Visualizer");
	glutKeyboardFunc (myKeyboardFunc);
	init();
	glutDisplayFunc(mydisplay);
	createMenu();
	glutMainLoop();

	return 0;
}
void swap(float* a, float* b) {
	float t = *a;
	*a = *b;
	*b = t;
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	generate();
}

void displayText(std::string textToDraw, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < textToDraw.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, textToDraw[i]);
}

void displayTitle(std::string textToDraw, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < textToDraw.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, textToDraw[i]);
}

void displayInfo()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	std::string title = "Sorting Visualizer";
	displayTitle(title, SCREEN_WIDTH * .4, 0.85 * SCREEN_HEIGHT);
	glColor3f(1.0f, 1.0f, 1.0f);
	std::string info = "Values: " + std::to_string(numElements) + "    Delay: " + std::to_string(sTime) + " ms delay";
	displayText(info, 5, 0.97 * SCREEN_HEIGHT);
}

void displayTotalTime(int diff, std::string algorithm)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	std::string info = "Sort Algorithm: " + algorithm + "    Comparisons: " + std::to_string(comparisons);
	displayText(info, 5, 0.93 * SCREEN_HEIGHT);
	std::string totalTime = "Total Time: " + std::to_string(diff) + " ms";
	displayText(totalTime, 5, .89 * SCREEN_HEIGHT);
	glFlush();
}

void draw(int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	float quadSize = (SCREEN_WIDTH - 2 * (numElements + 1.0)) / numElements;
	for (int i = 0; i < numElements; i++)
	{
		if (i == x || i == y)
			glColor3f(1.0f, 0.0f, 0.0f);
		else if (isSorted[i])
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex2f(2 + i * (2 + quadSize), 0);
		glVertex2f(2 + i * (2 + quadSize), arrayElements[i]);
		glVertex2f(2 + i * (2 + quadSize) + quadSize, arrayElements[i]);
		glVertex2f(2 + i * (2 + quadSize) + quadSize, 0);
		glEnd();
	}
	displayInfo();
	glFlush();
}

void generate()
{
	comparisons = 0;
	isSorted.clear();
	arrayElements.clear();
	srand(time(0));
	for (int i = 0; i < numElements; i++)
	{
		arrayElements.push_back((((float)rand() / RAND_MAX) * SCREEN_HEIGHT * 0.8));
		isSorted.push_back(false);
	}
	draw(-1, -1);
}
void delay()
{
	int c=0;
	for(int m=0;m<=100000;m++)
	{
		for(int k=0;k<=10000;k++)
		c+=100;
	}
}
void print_array(){
for (int i = 0; i < numElements ; i++)
{
	std::cout<<arrayElements[i]<<"\n";
}
}
void selectionSort()
{       print_array();
	int i, j, min_index;
	for (i = 0; i < numElements - 1; i++)
	{
		min_index = i;
		for (j = i + 1; j < numElements; j++)
		{
			draw(min_index, j);
			if (arrayElements[j] < arrayElements[min_index])
			{
				min_index = j;
			}
			delay();
			//sleep(sTime);
			comparisons++;
		}
		std::cout<<"swap"<<arrayElements[min_index]<<"<->"<<arrayElements[i]<<std::endl;
		swap(&arrayElements[min_index], &arrayElements[i]);
		isSorted[i] = true;
		draw(-1, -1);
	}
	delay();
	
	//sleep(sTime);
	isSorted[numElements - 1] = true;
	draw(-1, -1);
}

void clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(0);
	glEnd();
	glFlush();
}

void menuFunc(int id)
{
	switch (id)
	{
	case 11: numElements = 10; generate(); break;
	case 12: numElements = 20; generate(); break;
	case 13: numElements = 50; generate(); break;
	case 14: numElements = 100; generate(); break;
	case 15: numElements = 200; generate(); break;
	case 16: numElements = 1000; generate(); break;

	case 21: sTime = 10; draw(-1, -1); break;
	case 22: sTime = 20; draw(-1, -1); break;
	case 23: sTime = 50; draw(-1, -1); break;
	case 24: sTime = 100; draw(-1, -1); break;
	case 25: sTime = 500; draw(-1, -1); break;

	
	case 34: {
		auto start = std::chrono::system_clock::now();
		selectionSort();
		auto stop = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		displayTotalTime(diff.count(), "SelectionSort");
	} break;
	
	case 4:exit(0);
	}
}

void createMenu() {
	int s1 = glutCreateMenu(menuFunc);
	glutAddMenuEntry("10 Numbers", 11);
	glutAddMenuEntry("20 Numbers", 12);
	glutAddMenuEntry("50 Numbers", 13);
	glutAddMenuEntry("100 Numbers", 14);
	glutAddMenuEntry("200 Numbers", 15);
	glutAddMenuEntry("1000 Numbers", 16);

	int s2 = glutCreateMenu(menuFunc);
	glutAddMenuEntry("10", 21);
	glutAddMenuEntry("20", 22);
	glutAddMenuEntry("50", 23);
	glutAddMenuEntry("100", 24);
	glutAddMenuEntry("500", 25);

	int s3 = glutCreateMenu(menuFunc);
	
	glutAddMenuEntry("SelectionSort", 34);
	

	glutCreateMenu(menuFunc);
	glutAddSubMenu("Values", s1);
	glutAddSubMenu("Speed", s2);
	glutAddSubMenu("Sort", s3);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
