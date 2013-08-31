#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
#include <GL/glut.h>
#include<iostream>
using namespace std;

char quote[6][80];
int numberOfQuotes=0;

void printToConsoleWindow()
{
	int l,lenghOfQuote, i;

	for(  l=0;l<numberOfQuotes;l++)
	{
		lenghOfQuote = (int)strlen(quote[l]);

		for (i = 0; i < lenghOfQuote; i++)
		{
			cout<<quote[l][i];
		}
		cout<<endl;
	}

}

void RenderToDisplay()
{
	int l,lenghOfQuote, i;

	glTranslatef(0.0, -100, UpwardsScrollVelocity);
	glRotatef(-20, 1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);



	for(  l=0;l<numberOfQuotes;l++)
	{
		lenghOfQuote = (int)strlen(quote[l]);
		glPushMatrix();
		glTranslatef(-(lenghOfQuote*37), -(l*200), 0.0);
		for (i = 0; i < lenghOfQuote; i++)
		{
			glColor3f((UpwardsScrollVelocity/10)+300+(l*10),(UpwardsScrollVelocity/10)+300+(l*10),0.0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
		}
		glPopMatrix();
	}

}

void myDisplayFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 30.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	RenderToDisplay();
	glutSwapBuffers();
}

