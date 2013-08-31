#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
#include <GL/glut.h>
#include<iostream>
using namespace std;

char quote2[20][80];
int numberOfQuotes2=7;

void RenderToDisplay2()
{

	strcpy(quote2[0],"Use arrow keys to move the robot");
	strcpy(quote2[1],"Use key <space> to jump the robot");
	strcpy(quote2[2],"Use a,d,w,s,q,e keys to move the helicoptor camera");
	strcpy(quote2[3],"Use m key to change to mouse viewing in helicoptor mode");
	strcpy(quote2[4],"Use j,l,i,k keys to move the tile view camera");
	strcpy(quote2[5],"Use u,i,o,p keys to rotate the tile view camera");
	strcpy(quote2[6],"Use n key to change the camera mode");
	strcpy(quote2[7],"Use key 1 to pause the game");

	int l,lenghOfQuote, i;
	for(  l=0;l<numberOfQuotes2;l++)
	{
		lenghOfQuote = (int)strlen(quote2[l]);
		glPushMatrix();
		glTranslatef(0,500,0);
		glTranslatef(-1000,500-l*400, 1.0);
		for (i = 0; i < lenghOfQuote; i++)
		{
			glColor3f(255,255,255);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, quote2[l][i]);
		}
		double a,b,c;
		glPopMatrix();	
		//drawboxfortext(-1000,500-l*400, 0.0,lenghOfQuote);
	}
	glPopMatrix();
}



