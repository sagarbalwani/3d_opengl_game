#include<iostream>
#include<cmath>
#include<GL/glut.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int _cameraview=0;// 0=tower view, 1=First person view, 2=Static View, 3=Third person view, 4=helicoptor view,
int _pause=0;

#include "enemyrobot.h"
#include "text.h"
#include "helicopter.h"
#include "text2.h"

using namespace std;


#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
float _windowwidth=0;
float _windowheight=0;

//coordinates of the camera for the helicopter view... the camera will be initialized at the center of the world initially....
float _helicamx=0;
float _helicamy=20;
float _helicamz=0;
//looking at the center of the stage or in the direction of the mouse coordinates
float _helicamlookx=0;
float _helicamlooky=0;
float _helicamlookz=0;
//up is in the -z direction initially and then can be changed 
float _helicamupx=0;
float _helicamupy=0;
float _helicamupz=-1;
int _mouseflag=0;

int cheat=0;
int _tilei=9;
int _tilej=0;
float _tileangle=270;
int _dimsky=0;

int s_remaincoin=10;

float _camangle3=90;//camera angle for third person view...

float _howfar=20;//tells how far is the camera behind the robot in third person view

// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void myMouseclick(int button, int state, int x, int y);
void jump(int value);

void drawhuman(int);

void scroll(int button,int b,int c,int d);

int main(int argc, char **argv) {
	srand(time(NULL));
	
	strcpy(quote[0],"Click here for level 1");
	strcpy(quote[1],"Click here for level 2");
	strcpy(quote[2],"Click here for level 3");
	strcpy(quote[3],"Click here for Controls");
	numberOfQuotes=4;
	
	//enemyrobo2._jincy=15;
	//enemyrobo1._jincy=15;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	_windowwidth = glutGet(GLUT_SCREEN_WIDTH);
	_windowheight = glutGet(GLUT_SCREEN_HEIGHT);
	s_a=glutGet(GLUT_SCREEN_WIDTH);
	s_b=glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowSize(_windowwidth, _windowheight);
	glutInitWindowPosition(0,0);
	
	glutCreateWindow("Making of a game :p");  // Setup the window
	initRendering();
	
	// Register callbacks
	glutDisplayFunc(drawScene);
	//glLineWidth(2);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(myMouseclick);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);
	glutMotionFunc(handlemousemovementclick);
	glutPassiveMotionFunc(handlemousemovement);
//	glutMouseFunc(scroll);
	//glutTimerFunc(10, fallblocks, 0);
	
	glutMainLoop();
	return 0;
}

void scroll(int button,int state,int c,int d){
}

float _radius=100;
int _justonce=0;

void adjustjump(int level,int by){
	if(level==2 && by==1)//by==1 means by tile
	{
		robo._jincxz=20.0;
		robo._jincy=16.0;					
	}
	else if(level==2 && by==0)//by==1 means by jump func
	{
		robo._jincxz=15.0;
		robo._jincy=15.0;					
	}
	else if(level==1 && by==1)//by==1 means by tile
	{
		robo._jincxz=20.0;
		robo._jincy=16.0;					
	}
	else if(level==1 && by==0)//by==1 means by jump
	{
		robo._jincxz=10.0;
		robo._jincy=15.0;					
	}
}

//sagar
float coin_rad=1.7;
int collectcoins(){
	int x;
	for(x=0;x<10;x++)
	{
		if (cheat==5)
		{
			s_coin[x].draw=0;
			s_remaincoin=0;
		}
		if (robo._centery+6.25*robo._radface>blocks[s_coin[x].blocki][s_coin[x].blockj].a.y+4*robo._radface-coin_rad && 
			robo._centery-4*robo._radface< blocks[s_coin[x].blocki][s_coin[x].blockj].a.y+4*robo._radface+coin_rad &&
			robo._centerx + 1.35*robo._radface > (blocks[s_coin[x].blocki][s_coin[x].blockj].a.x+blocks[s_coin[x].blocki][s_coin[x].blockj].c.x)/2-coin_rad  && 
			robo._centerx - 1.35*robo._radface < (blocks[s_coin[x].blocki][s_coin[x].blockj].a.x+blocks[s_coin[x].blocki][s_coin[x].blockj].c.x)/2+coin_rad && 
			robo._centerz + 1.35*robo._radface > (blocks[s_coin[x].blocki][s_coin[x].blockj].a.z+blocks[s_coin[x].blocki][s_coin[x].blockj].c.z)/2-coin_rad && 
			robo._centerz - 1.35*robo._radface < (blocks[s_coin[x].blocki][s_coin[x].blockj].a.z+blocks[s_coin[x].blocki][s_coin[x].blockj].c.z)/2+coin_rad && s_coin[x].draw==1)
		{
			//printf("collected coin\n");
			s_coin[x].draw=0;
			s_remaincoin--;
		}
	}
	
	x=10;
	if (robo._centery+6.25*robo._radface>blocks[s_coin[x].blocki][s_coin[x].blockj].a.y+4*robo._radface-coin_rad && 
		robo._centery-4*robo._radface< blocks[s_coin[x].blocki][s_coin[x].blockj].a.y+4*robo._radface+coin_rad &&
		robo._centerx + 1.35*robo._radface > (blocks[s_coin[x].blocki][s_coin[x].blockj].a.x+blocks[s_coin[x].blocki][s_coin[x].blockj].c.x)/2-coin_rad  && 
		robo._centerx - 1.35*robo._radface < (blocks[s_coin[x].blocki][s_coin[x].blockj].a.x+blocks[s_coin[x].blocki][s_coin[x].blockj].c.x)/2+coin_rad && 
		robo._centerz + 1.35*robo._radface > (blocks[s_coin[x].blocki][s_coin[x].blockj].a.z+blocks[s_coin[x].blocki][s_coin[x].blockj].c.z)/2-coin_rad && 
		robo._centerz - 1.35*robo._radface < (blocks[s_coin[x].blocki][s_coin[x].blockj].a.z+blocks[s_coin[x].blocki][s_coin[x].blockj].c.z)/2+coin_rad && s_coin[x].draw==1)
	{
		//printf("collected coin\n");
		s_coin[x].draw=0;
		_pauseenemyrobo=1;
	}
}
//sagar
void placecoins(){
	int x;
	for (x=0;x<10;x++)
	{		
		if (s_coin[x].draw==1)
		{
		drawcoin(coin_rad,0.5,(blocks[s_coin[x].blocki][s_coin[x].blockj].a.x+blocks[s_coin[x].blocki][s_coin[x].blockj].c.x)/2,blocks[s_coin[x].blocki][s_coin[x].blockj].a.y+4*robo._radface,(blocks[s_coin[x].blocki][s_coin[x].blockj].a.z+blocks[s_coin[x].blocki][s_coin[x].blockj].c.z)/2,_textureId5);
		}
	}

}



void reinitialize(){
	
	_cameraview=0;// 0=tower view, 1=First person view, 2=Static View, 3=Third person view, 4=helicoptor view,
	_pause=0;
	_windowwidth=0;
	_windowheight=0;
	
	//coordinates of the camera for the helicopter view... the camera will be initialized at the center of the world initially....
	_helicamx=0;
	_helicamy=20;
	_helicamz=0;
	//looking at the center of the stage or in the direction of the mouse coordinates
	_helicamlookx=0;
	_helicamlooky=0;
	_helicamlookz=0;
	//up is in the -z direction initially and then can be changed 
	_helicamupx=0;
	_helicamupy=0;
	_helicamupz=-1;
	_mouseflag=0;
	
	
	_tilei=9;
	_tilej=0;
	_tileangle=270;
	
	_camangle3=90;//camera angle for third person view...
	
	_howfar=20;//tells how far is the camera behind the robot in third person view
	cheat=0;
	_pause=0;
	_pauseenemyrobo=0;
	
}
int _justjustonce=0;
void drawScene() {
	//{{{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(_level==0){
		if (_level2==4){
			glClear(GL_COLOR_BUFFER_BIT);
			glPushMatrix();
			glTranslatef(0,0,-6100);
			RenderToDisplay2();
			glPopMatrix();
		}
		else{
			glClear(GL_COLOR_BUFFER_BIT);
			glPushMatrix();
			glTranslatef(0,0,-6100);
			RenderToDisplay();
			glPopMatrix();
		}
	}
	

	else{
		if(_justonce==0){
			if(_justjustonce==0){
				updateenemy(0);
				updateenemy2(0);
				killingcount=0;				
				_justjustonce=1;
			}
			reinitialize();
			//printf("i have come in justonce\n");			
			generateblocks(robo,_level);
			moveblocks();
			robo._centerx=(blocks[9][0].a.x+blocks[9][0].b.x)/2;//-45
			robo._centery=0;
			robo._centerz=(blocks[9][0].a.z+blocks[9][0].d.z)/2;//45
			
			enemyrobo1._centerx=(blocks[5][0].a.x+blocks[5][0].b.x)/2;//45135;
			enemyrobo2._centerx=(blocks[5][9].a.x+blocks[5][9].b.x)/2;//45-45;
			
			enemyrobo1._centerz=(blocks[5][0].a.z+blocks[5][0].d.z)/2;//45-45;
			enemyrobo2._centerz=(blocks[5][9].a.z+blocks[5][9].d.z)/2;//45-45;
			_justonce=1;
			s_remaincoin=10;
			killingcount=0;
			generatecoins();
		}
		if(_cameraview==4){//Helicoptor view
			gluLookAt(s_eyex,s_eyey,s_eyez,s_centerx,s_centery,s_centerz,s_upx,s_upy,s_upz);
		}
		else if(_cameraview==0){//view is static
			if(_level==2 || _level==3){
				_camangle3=90;
				gluLookAt(50, 30,260, 50, 0, 10,0.0, 1.0, 0);
			}
			else if(_level==1){
				_camangle3=90;
				gluLookAt(0, 30,120, 0, 0, 0,0.0, 1.0, 0);
			}
		}
		else if(_cameraview==1){
			float lookx,lookz;		
			lookx=robo._centerx+10*sin((robo._humanangle)*PI/180);
			lookz=robo._centerz+10*cos((robo._humanangle)*PI/180);
			gluLookAt(robo._centerx,robo._centery+robo._radface*4 + robo._radface/4 + 2*robo._radface + 6,robo._centerz-robo._radface-robo._radface/5, 
				lookx, 0.0,lookz,
				0, 1,0);
		}
		else if(_cameraview==2){//tile view
			if(blocks[_tilei][_tilej].flag==6){
				gluLookAt(_tilej*10-45,10,_tilei*10-45,
					_tilei*10-45+1000*cos(DEG2RAD(_tileangle)),10,_tilej*10-45+1000*sin(DEG2RAD(_tileangle)),
					0, 1,0);
			}
			else{
				gluLookAt(_tilej*10-45,blocks[_tilei][_tilej].a.y+10,_tilei*10-45,
					_tilei*10-45+1000*cos(DEG2RAD(_tileangle)),blocks[_tilei][_tilej].a.y+10,_tilej*10-45+1000*sin(DEG2RAD(_tileangle)),
					0, 1,0);
			}
		}
		else if(_cameraview==3){
			
			float lookx,lookz;
			float howx,howz;
			
			lookx=robo._centerx+100*sin((robo._humanangle)*PI/180);
			lookz=robo._centerz+100*cos((robo._humanangle)*PI/180);
			
			howx=robo._centerx-_howfar*sin((robo._humanangle)*PI/180);
			howz=robo._centerz-_howfar*cos((robo._humanangle)*PI/180);
			
			gluLookAt(howx,robo._centery+robo._radface*4 + robo._radface/4 + 2*robo._radface + _howfar/3 ,howz, 
				lookx, 0.0,lookz,
				0, 1.0,0);
		}
		//Add ambient light
		GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
		
		
		
		//Add positioned light spotlight
		GLfloat lightColor0[] = {255, 255, 255, 1.0f}; //Color (0.5, 0.5, 0.5)
		GLfloat lightPos0[] = {robo._centerx, 60.0f, robo._centerz, 1.0f}; //Positioned at (4, 0, 8)

		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);
		GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);

		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		
		//positioned
		GLfloat lightColor1[] = {255, 255, 255, 1.0f}; //Color (0.5, 0.5, 0.5)
		GLfloat lightPos1[] = {_sunx+50,_suny-400,_sunz, 1.0f}; //Positioned at (4, 0, 8)
		
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 75.0);
		GLfloat spot_direction1[] = {-(_sunx+50),-(_suny-400),-_sunz};
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);		
		
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
		
		
		//GLfloat lightColor2[] = {255, 255, 255, 1.0f}; //Color (0.5, 0.5, 0.5)
		//GLfloat lightPos2[] = {0,50,0}; //Positioned at (4, 0, 8)

		//glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10.0);
		//GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
		//glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);

		//glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
		//glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
		
		glEnable(GL_TEXTURE_2D);
		
		if(_level==3){
			glBindTexture(GL_TEXTURE_2D, _textureId10);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glColor3f(1,1,1);
			glBegin(GL_QUADS);
			glNormal3f(0,1,0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-1000,-100,-1000);
			glTexCoord2f(7, 0.0);
			glVertex3f(1000,-100,-1000);
			glTexCoord2f(7, 7);
			glVertex3f(1000,-100,1000);
			glTexCoord2f(0, 7);
			glVertex3f(-1000,-100,1000);
			glEnd();
		        glDisable(GL_TEXTURE_2D);

			
		}
		else{
			glBindTexture(GL_TEXTURE_2D, _textureId1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glColor3f(1,1,1);
			glBegin(GL_QUADS);
			glNormal3f(0,1,0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-1000,-100,-1000);
			glTexCoord2f(1, 0.0);
			glVertex3f(1000,-100,-1000);
			glTexCoord2f(1, 1);
			glVertex3f(1000,-100,1000);
			glTexCoord2f(0, 1);
			glVertex3f(-1000,-100,1000);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			
		}
		//Bottom
		
		drawhuman(robo._newdir);
		drawenemyhuman(&enemyrobo1,enemyrobo1._newdir);
		drawenemyhuman(&enemyrobo2,enemyrobo2._newdir);
		drawBlocks();
		drawSun(_sunsize,_sunx,_suny,_sunz);//radius of trajectory will be 200
		//drawPoint(_dpx,_dpy,_dpz);
		placecoins();
		if(s_coin[10].draw==1){
			drawPower((blocks[s_coin[10].blocki][s_coin[10].blockj].a.x+blocks[s_coin[10].blocki][s_coin[10].blockj].c.x)/2,blocks[s_coin[10].blocki][s_coin[10].blockj].a.y+4*robo._radface,(blocks[s_coin[10].blocki][s_coin[10].blockj].a.z+blocks[s_coin[10].blocki][s_coin[10].blockj].c.z)/2,coin_rad);
		}
		glColor3f(1,1,1);
		if(_level==1){
			if(_dimsky==1){
				glColor3f(255,255,255);			
				drawSphere(800,0,0,0,_textureId8,0); //the radius of the face is 14
			}
			else if(_dimsky==0){
				glColor3f(255,255,255);
				drawSphere(800,0,0,0,_textureId7,1); //the radius of the face is 14
			}
		}
		else if(_level==2){
			glColor3f(255,255,255);			
			drawSphere(800,0,0,0,_textureId8,0); //the radius of the face is 14
		}
		else if(_level==3){
			glColor3f(255,255,255);
			drawSphere(800,0,0,0,_textureId8,0); //the radius of the face is 14
		}
	}
	glutSwapBuffers();
	//}}}
}

void GetOGLPos(int x, int y,double *a,double *b,double *c)
{//{{{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
	
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );
	
	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
	
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	//printf("%lf %lf %lf",posX,posY,posZ);
	*a=posX;
	*b=posY;
	*c=posZ;
	//}}}
}

void drawsubhuman(float angle){
	//{{{
	glPushMatrix();
	glTranslatef(robo._centerx,robo._centery,robo._centerz);
	glRotatef(angle,0,1,0);
	
	drawFace(robo._radface,0,robo._radface*4 + robo._radface/4 + robo._radface,0);
	
	drawNeck(robo._radface,0,robo._radface*4,0);
	
	drawStomach2(robo._radface,0,0,0);
	
	drawluarm(robo._radface,-robo._radface*1.35,robo._radface*4,0,robo._flaglefthand,robo._handangle);
	
	drawruarm(robo._radface,robo._radface*1.35,robo._radface*4,0,robo._flaglefthand,robo._handangle);
	
	drawluleg(robo._radface,-robo._radface*1.35,0,0,robo._flagleftleg,robo._legangle);
	
	drawruleg(robo._radface,robo._radface*1.35,0,0,robo._flagleftleg,robo._legangle);
	
	glPopMatrix();
	//}}}
}


int _flagrot=0;

void rotatehead(int value){
	//{{{ 
	if(robo.nooftimesrotate==robo._precision){
		robo.nooftimesrotate=0;
		//printf("yes\n");
		robo._blocktillrotate=0;
	}
	else{
		robo.rotatehead();
		glutTimerFunc(25,rotatehead,0);
	} //}}}
	
}

void drawhuman(int dir){
	//{{{ 
	if(dir!=robo._curdir){
		robo._blocktillrotate=1;
		robo._angleofrot=getangle(&robo._curdir,robo._curdir,dir);
		glutTimerFunc(10,rotatehead,0);
		//robo._humanangle+=robo._angleofrot;
	}
	if(robo._humanangle>=360){
		robo._humanangle-=360;
	}
	else if(robo._humanangle<0){
		robo._humanangle+=360;
	}
	drawsubhuman(robo._humanangle);
	//}}}
}


//this part from here deals with lines the robot motions and collision detections
//find bot is going to be the most important functions now... :) going to replace
//where is bot.. :)

void iftrampoline(){
	int _oti=-1,_otj=-1;
	int i,j;
	int yes=0;
	int flag=0;//it does nothing as of now
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			yes=tellme(blocks[i][j].a,blocks[i][j].b,blocks[i][j].c,blocks[i][j].d,robo._centerx,robo._centerz);
			if(yes==1){
				_oti=i;
				_otj=j;
				break;
			}
		}
		if(yes==1){
			break;
		}
	}
	if(_oti==-1 or _otj==-1);
	else{
		int k;
		if(flag==0){
			//printf("till here is correct\n");
			//printf("%f %f\n",robo._centery-4*robo._radface,blocks[_oti][_otj].a.y);
			for(k=0;k<_nooftrampoline;k++){
				if(_trampolineblocks[2*k]==_oti && _trampolineblocks[2*k+1]==_otj && robo._centery-4*robo._radface==blocks[_oti][_otj].a.y){//(robo._centery-4*robo._radface>blocks[_oti][_otj].a.y-0.001 && robo._centery-4*robo._radface<blocks[_oti][_otj].a.y+0.001)){
					printf("this is the second check point\n");
					if(_level==2 || _level==3){
						adjustjump(2,1);
					}
					else if(_level==1){
						adjustjump(1,1);
					}
					robo._icanjump=0;
					jump(0);
				}
			}
		}
	}
}

int _oti=0,_otj=9;//on i,j tile... -1 tells that it's on no tile..

void findbot(float a,float b,float c,float d,float e,float f,int *nooftimes,int flag){//this function is for motion of the bot
	int i,j;
	//a,b,c tells the initial location of the bot
	//d,e,f tells the final location of the bot
	int yes=0;
	_oti=-1;
	_otj=-1;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			yes=tellme(blocks[i][j].a,blocks[i][j].b,blocks[i][j].c,blocks[i][j].d,d,f);
			if(yes==1){
				_oti=i;
				_otj=j;
				break;
			}
		}
		if(yes==1){
			break;
		}
	}
	if(_oti==-1 or _otj==-1);//printf("yes i am on a wrong tile\n");
	else{
		//printf("yes %f %f %f %d\n",robo._centery-4*robo._radface,blocks[i][j].a.y,blocks[i][j].e.y,robo.noofjumps);
		if(e-robo._radface*4>=blocks[_oti][_otj].a.y){//this condition will see if the bot is at an allowed positon
			//precisely legs above the tiles directly above a tile ... :) 
			
		}
		else if(e + robo._radface*4 + robo._radface/4 + 2*robo._radface < blocks[_oti][_otj].e.y){//if head below the tile
		}
		else{//this means that the robot is going to access a wrong location that it is not supposed to so donot allow it do so....
			//printf("yes i have gone in else and should not go here...\n");
			if(flag==1){
				robo._centerx=a+2*robo._inc/robo._precision;
				robo._centery=b;
			}
			else if(flag==2){
				robo._centerx=a-2*robo._inc/robo._precision;
				robo._centery=b;
			}
			else if(flag==3){
				robo._centerz=c+2*robo._inc/robo._precision;
				robo._centery=b;
			}
			else if(flag==4){
				robo._centerz=c-2*robo._inc/robo._precision;
				robo._centery=b;
			}
			else if(flag==0){
				robo._centerx=a;
				robo._centery=b;
				robo._centerz=c;
			}
			yes=0;
			d=robo._centerx;
			e=robo._centery;
			f=robo._centerz;
			for(i=0;i<10;i++){
				for(j=0;j<10;j++){
					yes=tellme(blocks[i][j].a,blocks[i][j].b,blocks[i][j].c,blocks[i][j].d,d,f);
					if(yes==1){
						_oti=i;
						_otj=j;
						break;
					}
				}
				if(yes==1){
					break;
				}
			}
			*nooftimes=robo._precision;
		}
	}
}

void findbotupdate(float d,float e,float f,int *g,int *h){//this function is for motion of the bot
	int i,j;
	*g=-1;
	*h=-1;
	//d,e,f tells the final location of the bot
	int yes=0;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			yes=tellme(blocks[i][j].a,blocks[i][j].b,blocks[i][j].c,blocks[i][j].d,d,f);
			if(yes==1){
				*g=i;
				*h=j;
				break;
			}
		}
		if(yes==1){
			break;
		}
	}
}


int _flagleft=0,_flagright=0,_flagup=0,_flagdown=0;

int _howmanytimescanigoinaparticulardirection=10;

void goleft(int value){
	float a,b,c,d,e,f;//they store the initial and final coordinates of the robot
	if(robo.nooftimesleft==robo._precision){
		robo.nooftimesleft=0;
		_flagleft--;
	}
	else{
		a=robo._centerx;
		b=robo._centery;
		c=robo._centerz;
		robo.goleft(0);
		d=robo._centerx;
		e=robo._centery;
		f=robo._centerz;		
		findbot(a,b,c,d,e,f,&robo.nooftimesleft,1);
		glutTimerFunc(50,goleft,0);
	}
}

void goright(int value){
	float a,b,c,d,e,f;//they store the initial and final coordinates of the robot
	
	if(robo.nooftimesright==robo._precision){
		robo.nooftimesright=0;
		_flagright--;
	}
	else{
		a=robo._centerx;
		b=robo._centery;
		c=robo._centerz;
		robo.goright(0);
		d=robo._centerx;
		e=robo._centery;
		f=robo._centerz;		
		findbot(a,b,c,d,e,f,&robo.nooftimesright,2);
		glutTimerFunc(50,goright,0);
	}
}

void goup(int value){
	float a,b,c,d,e,f;//they store the initial and final coordinates of the robot
	
	if(robo.nooftimesup==robo._precision){
		robo.nooftimesup=0;
		_flagup--;
	}
	else{
		a=robo._centerx;
		b=robo._centery;
		c=robo._centerz;
		robo.goup(0);
		d=robo._centerx;
		e=robo._centery;
		f=robo._centerz;		
		findbot(a,b,c,d,e,f,&robo.nooftimesup,3);
		glutTimerFunc(50,goup,0);
	}
}

void godown(int value){
	float a,b,c,d,e,f;//they store the initial and final coordinates of the robot
	
	if(robo.nooftimesdown==robo._precision){
		robo.nooftimesdown=0;
		_flagdown--;
	}
	else{
		a=robo._centerx;
		b=robo._centery;
		c=robo._centerz;
		robo.godown(0);
		d=robo._centerx;
		e=robo._centery;
		f=robo._centerz;		
		findbot(a,b,c,d,e,f,&robo.nooftimesdown,4);
		glutTimerFunc(50,godown,0);
	}
}

void handleKeypress2(int key, int x, int y) {
	if(_level!=0){
		if(_pause==0){
			if(robo._blocktillrotate==0){
				if (key == GLUT_KEY_LEFT){
					if(_flagleft>_howmanytimescanigoinaparticulardirection){}
					else{
						if(_cameraview==3 || _cameraview==1){
							if(robo._curdir==1){
								robo._newdir=4;
							}
							else if(robo._curdir==2){
								robo._newdir=3;
							}
							else if(robo._curdir==3){
								robo._newdir=1;
							}
							else if(robo._curdir==4){
								robo._newdir=2;
							}
						}
						else{
							robo._newdir=2;
							_flagleft++;
							goleft(0);
						}
					}
				}
				else if (key == GLUT_KEY_RIGHT){
					if(_flagright>_howmanytimescanigoinaparticulardirection){}
					else{
						if(_cameraview==3 || _cameraview==1){
							if(robo._curdir==1){
								robo._newdir=3;
							}
							else if(robo._curdir==2){
								robo._newdir=4;
							}
							else if(robo._curdir==3){
								robo._newdir=2;
							}
							else if(robo._curdir==4){
								robo._newdir=1;
							}
						}
						else{
							robo._newdir=1;
							_flagright++;
							goright(0);
						}
					}
				}
				else if (key == GLUT_KEY_UP){
					if(_flagup>_howmanytimescanigoinaparticulardirection){}
					else{
						if(_cameraview==3 || _cameraview==1){
							if(robo._curdir==1){
								if(_flagright<1+_howmanytimescanigoinaparticulardirection){
									goright(0);
									_flagright++;
								}
							}
							else if(robo._curdir==2){
								if(_flagleft<1+_howmanytimescanigoinaparticulardirection){
									goleft(0);
									_flagleft++;
								}
							}
							else if(robo._curdir==3){
								if(_flagdown<1+_howmanytimescanigoinaparticulardirection){
									godown(0);
									_flagdown++;
								}
							}
							else if(robo._curdir==4){
								if(_flagup<1+_howmanytimescanigoinaparticulardirection){
									goup(0);
									_flagup++;
								}
							}
						}
						else{
							robo._newdir=4;
							goup(0);
							_flagup++;
						}
					}
				}
				else if (key == GLUT_KEY_DOWN){
					if(_flagdown>_howmanytimescanigoinaparticulardirection){}
					else{
						if(_cameraview==3 || _cameraview==1){
							if(robo._curdir==1){
								robo._newdir=2;
							}
							else if(robo._curdir==2){
								robo._newdir=1;
							}
							else if(robo._curdir==3){
								robo._newdir=4;
							}
							else if(robo._curdir==4){
								robo._newdir=3;
							}
						}
						else{
							robo._newdir=3;
							godown(0);
							_flagdown++;
						}
					}
				}
			}
		}
	}
}

void jump(int value){
	int a,b,c,d,e,f;
	if(robo.noofjumps==robo._precision){
		robo.noofjumps=0;
		iftrampoline();
		//printf("yes jumping done\n");
	}
	else{
		a=robo._centerx;
		b=robo._centery;
		c=robo._centerz;
		robo.jump(0);
		d=robo._centerx;
		e=robo._centery;
		f=robo._centerz;
		findbot(a,b,c,d,e,f,&robo.noofjumps,0);	
		glutTimerFunc(50,jump,0);
	}
}

void handleKeypress1(unsigned char key, int x, int y) {
	
	if (key == 27) {
		if(_level!=0){
			_level=0;
			_justonce=0;
			_level2=0;
		}
		else{
			if(_level2==4){
				_level2=0;
			}
			else{
				exit(0);
			}// escape key is pressed
		}
	}
	else if(key=='1'){
		if(_pause==0){
			_pause=1;
		}
		else if(_pause==1){
			_pause=0;
		}
	}
	if(_level!=0){
		if(key=='n'){//changes the camera view
			_cameraview=(_cameraview+1)%5;
		}
		else if(key==' '){
			if(_pause==0){
				//printf("%d %d\n",robo.noofjumps,robo._icanjump);
				if(robo.noofjumps==0 &&  robo._icanjump==1){
					//printf("%d %d\n",robo.noofjumps,robo._icanjump);
					if(_level==2 || _level==3){
						adjustjump(2,0);
					}
					else if(_level==1){
						adjustjump(1,0);
					}
					robo._icanjump=0;
					jump(0);
				}
			}
		}
		//{{{
		if(_cameraview==2){
			if(key=='i'){
				_tileangle=270;
				if(_tilei>0){
					_tilei--;
				}
			}
			else if(key=='k'){
				_tileangle=270;
				if(_tilei<9){
					_tilei++;
				}
			}
			else if(key=='j'){
				_tileangle=270;
				if(_tilej>0){
					_tilej--;
				}
			}
			else if(key=='l'){
				_tileangle=270;
				if(_tilej<9){
					_tilej++;
				}
			}
			else if(key=='p'){
				_tileangle+=5;
				if(_tileangle>=360){
					_tileangle-=360;
				}
			}
			else if(key=='o'){
				_tileangle-=5;
				if(_tileangle<0){
					_tileangle+=360;
				}
			}
		}
		else if(_cameraview==4){
			//printf("%d\n",s_vertical);		
			if (key=='m'){
				printf("%d\n",s_vertical);
				if (s_vertical==1){
					s_vertical=0;
				}
				else if(s_vertical==0){
					s_vertical=1;
				}
			}
			else if (key=='w'){
				s_eyey+=5;
			}
			else if (key=='s'){
				s_eyey-=5;
			}
			else if (key=='a'){
				s_eyex-=5;
			}
			else if (key=='d'){
				s_eyex+=5;
			}
			else if (key=='q'){
				s_eyez-=5;
			}
			else if (key=='e'){
				s_eyez+=5;
			}			
		}
		if (key=='c')
		{
			if(cheat==0)
				cheat=1;
			else
				cheat=0;
		}
		else if (key=='o')
		{
			if(cheat==1)
				cheat=2;
			else
				cheat=0;
		}
		else if (key=='i')
		{
			if(cheat==2)
				cheat=3;
			else
				cheat=0;
		}
		else if (key=='n')
		{
			if(cheat==3)
				cheat=4;
			else
				cheat=0;
		}
		else if (key=='s')
		{
			if(cheat==4)
				cheat=5;
			else
				cheat=0;
		}
		/* else if(key=='p'){
			if(_pauseenemyrobo==0){
				_pauseenemyrobo=1;
			}
			else if(_pauseenemyrobo==1){
				_pauseenemyrobo=0;
			}
		} */
		else{
			cheat=0;
		}
	}
	//}}}
	
}

void letsee2(int x,int y,double *f,double *g,double *h){
	double a,b,c;
	double modelview[16];
	int i,j;

	//glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, modelview );

	GetOGLPos(x,y,f,g,h);
	//printf("x=%d y=%d a=%lf b=%lf c=%lf\n",x,y,*f,*g,*h);
}

void myMouseclick(int button, int state, int xx, int yy) {	
	double x,y,z;
	double tempx,tempy,tempz;
	letsee2(xx,yy,&tempx,&tempy,&tempz);
	x=tempx;y=tempy;z=tempz;
	if(_level==0){
		if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
//			int x=xx,y=yy;

			int a=-1000,b=1250,c=500,d=400,e=150;			
			if(x<b && x>a  && y<c+e && y>c-e ){
				//printf("level 1\n");
				_level=1;
			}
			else if(x<b && x>a  && y<c+e-d && y>c-e-d ){
				//printf("level 2\n");
				_level=2;
			}
			else if(x<b && x>a  && y<c+e-2*d && y>c-e-2*d ){
				//printf("level 3\n");
				_level=3;
			}
			else if(x<b && x>a  && y<c+e-3*d && y>c-e-3*d ){
				//printf("level 4\n");
				_level=0;
				_level2=4;
			}		
 		}
	}
	else{
		if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
/* 			_dpx=0;_dpy=0;_dpz=0;			
			_dpx=x;_dpy=y;_dpz=z;
			if(_dpx<2 && _dpx>-2 && _dpy<2 && _dpy>-2){
				printf("fire\n");
			}
			printf("%lf %lf %lf %lf %lf %lf %lf\n",_dpx,_dpy,_dpz,enemyrobo1._centerx+enemyrobo1._radface*1.35,enemyrobo1._centerx-enemyrobo1._radface*1.35,enemyrobo1._centery+enemyrobo1._radface*6,enemyrobo1._centery);
			if(_dpx<enemyrobo1._centerx+enemyrobo1._radface*1.35 && _dpx>enemyrobo1._centerx-enemyrobo1._radface*1.35 && _dpy<enemyrobo1._centery+enemyrobo1._radface*6 && _dpy>enemyrobo1._centery){
				printf("1111111111fire\n");
			}
			else if(_dpx<enemyrobo2._centerx+enemyrobo2._radface*1.35 && _dpx>enemyrobo2._centerx-enemyrobo2._radface*1.35 && _dpy<enemyrobo2._centery+enemyrobo2._radface*7 && _dpy>enemyrobo2._centery){
				printf("222222222fire\n");
			}
 */		}			
		if (_cameraview==4)
		{// Wheel repors_ts as button 3(scroll up) and button 4(scroll down)

			if (button == 3) // It's a wheel event
			{
				if (state == GLUT_UP) return; // Disregard redundant GLUT_UP evens_ts
				s_hd-=0.2;
				s_eyey-=0.4;
			}
			else if (button == 4)
			{  
				s_hd+=0.2;
				s_eyey+=0.4;
			}
			if(s_hhelangle>=0 && s_hhelangle<90)
			{
				s_eyez =0+ s_hd*s_ts*cos(d2r(s_hhelangle));
				s_eyex =0-  s_hd*s_ts*sin(d2r(s_hhelangle));
			}
			else if(s_hhelangle>=90 && s_hhelangle<180)
			{
				s_eyez=0 - s_hd*s_ts*fabs(cos(d2r(s_hhelangle)));
				s_eyex=0 - s_hd*s_ts*fabs(sin(d2r(s_hhelangle)));
			}
			else if(s_hhelangle>=180 && s_hhelangle<270)
			{
				s_eyez=0 - s_hd*s_ts*fabs(cos(d2r(s_hhelangle)));
				s_eyex=0 + s_hd*s_ts*fabs(sin(d2r(s_hhelangle)));
			}
			else
			{
				s_eyez=0 + s_hd*s_ts*fabs(cos(d2r(s_hhelangle)));
				s_eyex=0 + s_hd*s_ts*fabs(sin(d2r(s_hhelangle)));
			}
		}
	}
}
// Initializing some openGL 3D rendering options
void initRendering() {
	//{{{ 
	
	//glEnable(GL_DEPTH);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
	
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_LIGHT2); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH); //Enable smooth shading
	
	Image* image = loadBMP("tiletest.bmp");
	_textureId = loadTexture(image);
	delete image;
	
	Image* image1 = loadBMP("water2.bmp");
	_textureId1 = loadTexture(image1);
	delete image1;
	
	Image* image5 = loadBMP("coin.bmp");
	_textureId5 = loadTexture(image5);
	delete image5;
	
	Image* image6 = loadBMP("sun.bmp");
	_textureId6 = loadTexture(image6);
	delete image6;

	Image* image7 = loadBMP("sky.bmp");
	_textureId7 = loadTexture(image7);
	delete image7;
	
	Image* image8 = loadBMP("night.bmp");
	_textureId8 = loadTexture(image8);
	delete image8;

	Image* image9 = loadBMP("moon.bmp");	
	_textureId9 = loadTexture(image9);
	delete image9;

	Image* image10 = loadBMP("fire.bmp");	
	_textureId10 = loadTexture(image10);
	delete image10;
	//}}}
}

// Function called when the window is resized
void handleResize(int w, int h) {
	//{{{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 20000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//}}}
}

void movesun(){
	//x^2 + y^2 = r^2;
	float inc=1;
	if(_suny>600){
		inc=0.5;
	}
	if(_suny>_sunr){
		_sundone=1;
	}
	else if(_suny<-_sunr){
		_sundone=0;
	}
	
	if(_suny<300){
		inc=5;
		_dimsky=1;
	}
	else{
		_dimsky=0;
	}
	if(_sundone==0){
		_suny+=inc;
	}
	else{
		_suny-=inc;
	}
	if(_sundone==0){
		_sunx=sqrt(_sunr*_sunr-_suny*_suny);
	}
	if(_sundone==1){
		_sunx=-sqrt(_sunr*_sunr-_suny*_suny);
	}
}
int checkkill(robots *enemy1,robots *enemy2){
	float x=0.5;
	/* printf("z1) %f %f %f\n",enemy1->_centerz-x,robo._centerz,enemy1->_centerz+x);
	printf("z2) %f %f %f\n",enemy2->_centerz-x,robo._centerz,enemy2->_centerz+x);

	printf("x1) %f %f %f\n",enemy1->_centerx-x,robo._centerx,enemy1->_centerx+x);
	printf("x2) %f %f %f\n",enemy2->_centerx-x,robo._centerx,enemy2->_centerx+x);

	printf("y1) %f %f %f\n",enemy1->_centery-x,robo._centery,enemy1->_centery+x);
	printf("y2) %f %f %f\n",enemy2->_centery-x,robo._centery,enemy2->_centery+x); */
	if(enemy1->_centerx-x <= robo._centerx && enemy1->_centerx+x >= robo._centerx &&  enemy1->_centery-x <= robo._centery && enemy1->_centery+x >= robo._centery && enemy1->_centerz-x <= robo._centerz && enemy1->_centerz+x >= robo._centerz){
		//printf("killed bot %d\n",killingcount);
		killingcount++;		
	}
	if(enemy2->_centerx-x <= robo._centerx && enemy2->_centerx+x >= robo._centerx &&  enemy2->_centery-x <= robo._centery && enemy2->_centery+x >= robo._centery && enemy2->_centerz-x <= robo._centerz && enemy2->_centerz+x >= robo._centerz){
		//printf("killed bot %d\n",killingcount);
		killingcount++;		
	}
	return killingcount;
}
int _checkflag=0;
float inc=0.5;
int _diecount=0;//tells that the robot has jumped to low.... :P and now it will die hehe...
int enemypausecount=0;
void whereisbot(){
	if(_pauseenemyrobo==1){
		enemypausecount++;
	}
	if(enemypausecount==200){
		int count=0;
		while(count!=1){
			s_coin[10].draw=1;
			s_coin[10].blocki=rand()%10;
			s_coin[10].blockj=rand()%10;
			if(blocks[s_coin[10].blocki][s_coin[10].blockj].flag==6){
			}
			else{
				count=1;
			}
		}
		_pauseenemyrobo=0;
		enemypausecount=0;
	}
	killingcount=checkkill(&enemyrobo1,&enemyrobo2);
	if(killingcount>0){
		_level=0;
		_justonce=0;
		_level2=0;
	}
	robo._icanjump=0;
	if(_checkflag==1){
		robo._centery+=inc;
	}
	moveblocks1(0);
	coin_angle+=10;
	coin_angle%=360;
	movesun();
	int i,j;
	findbotupdate(robo._centerx,robo._centery,robo._centerz,&i,&j);
	collectcoins();
	int k;
	//printf("%d %d\n",i,j);
	if(i==-1 or j==-1){
		if(robo.noofjumps==0){
			robo._centery-=robo._jincy/robo._precision;
		}
	}
	else{
		if(robo.noofjumps==0){
			
			//printf("%f %f\n",blocks[i][j].a.y+robo._radface*4,robo._centery);
			
			if((blocks[i][j].a.y+robo._radface*4)==robo._centery){
				//printf("why not in this???\n");
				//printf("%d\n",s_remaincoin);
				if(i==0 && j==9 && s_remaincoin==0){
					_level=0;
					_justonce=0;
					_level2=0;
				}
				if(_diecount>20){
					//_cameraview=3;
					//drawdeadrobo(robo._centerx,robo._centery,robo._centerz);
				}
				robo._icanjump=1;			
				for(k=0;k<_nooffalling;k++){
					if(_fallingblocks[2*k]==i && _fallingblocks[2*k+1]==j){
						//printf("yes i am on a falling block\n");
						//fallme(i,j);
						if(blocks[i][j].a.y>-10){
							blocks[i][j].a.y-=0.1;
							blocks[i][j].b.y-=0.1;
							blocks[i][j].c.y-=0.1;
							blocks[i][j].d.y-=0.1;
							blocks[i][j].e.y-=0.1;
							blocks[i][j].f.y-=0.1;
							blocks[i][j].g.y-=0.1;
							blocks[i][j].h.y-=0.1;
							robo._centery=blocks[i][j].a.y+robo._radface*4;
							
						}
					}
				}
				
				for(k=0;k<_noofmovingx;k++){	
					float inc=0.0;
					if(_movingblocksx[4*k]==i && _movingblocksx[4*k+1]==j){
						//printf("i=%d j=%d \n",i,j);
						//printf("%f %f\n",robo._centery,blocks[i][j].a.y+robo._radface*4);
						if(_updownx[k]==0){
							if((blocks[i][j].b.x)<_distancex2[k]){
								inc=0.5;
							}
							else{
								inc=-0.5;
							}
						}
						else if(_updownx[k]==1){
							if((blocks[i][j].a.x)>_distancex[k]){
								inc=-0.5;
							}
							else{
								inc=0.5;
							}
						}
					}
					robo._centerx+=inc;
				}
				
				for(k=0;k<_noofmovingz;k++){	
					float inc=0.0;
					if(_movingblocksz[4*k+2]==i && _movingblocksz[4*k+3]==j){
						//printf("i=%d j=%d \n",i,j);
						//printf("%f %f\n",robo._centery,blocks[i][j].a.y+robo._radface*4);
						if(_updownz[k]==0){
							if((blocks[i][j].d.z)<_distancez2[k]){
								inc=0.5;
							}
							else{
								inc=-0.5;
							}
						}
						else if(_updownz[k]==1){
							if((blocks[i][j].a.z)>_distancez[k]){
								inc=-0.5;
							}
							else{
								inc=0.5;
							}
						}
					}
					robo._centerz+=inc;
				}
				
				int flag=0;//tells whether the robot is no longer on a teleporting tile
				for(k=0;k<_noofteleportor;k++){
					if(_teleportorblocks[2*k]==i && _teleportorblocks[2*k+1]==j){
						flag=1;//i am on a teloportor tile
						if(robo._icanteleport==1){
							int gototile=((k+1)%_noofteleportor);
							robo._centerx=(blocks[_teleportorblocks[2*gototile]][_teleportorblocks[2*gototile+1]].a.x+blocks[_teleportorblocks[2*gototile]][_teleportorblocks[2*gototile+1]].b.x)/2.0;
							robo._centerz=(blocks[_teleportorblocks[2*gototile]][_teleportorblocks[2*gototile+1]].a.z+blocks[_teleportorblocks[2*gototile]][_teleportorblocks[2*gototile+1]].d.z)/2.0;
							robo._centery=(blocks[_teleportorblocks[2*gototile]][_teleportorblocks[2*gototile+1]].a.y+robo._radface*4);							
							printf("%f %f\n",robo._centerx,robo._centerz);
							robo._icanteleport=0;
						}
					}
				}
				if(flag==0){
					robo._icanteleport=1;
				}
				
			}		
			else if((blocks[i][j].e.y>robo._centery+robo._radface*6+robo._radface/4)){//the tile is very high than the robot then the robot should fall... let him be on any tile at all
				robo._centery-=robo._jincy/robo._precision;
			}
			else if((blocks[i][j].a.y + robo._radface*4) < robo._centery){
				//printf("radface=%f\n",robo._radface*4);
				//printf("************%f %f\n",blocks[i][j].a.y,robo._centery-robo._radface*4);
				//this is a very important part.... careful... remember...
				_diecount++;
				robo._centery-=robo._jincy/robo._precision;
				if(robo._centery < blocks[i][j].a.y+robo._radface*4){
					robo._centery=blocks[i][j].a.y+robo._radface*4;
					_diecount=0;
				}
				if(_diecount==20){
					printf("you are dead\n");
				}
				iftrampoline();
			}
			else{
				//robo._centery=blocks[i][j].a.y+robo._radface*4;//very dangerous line.... can destroy the code
				if(robo._centery-4*robo._radface<blocks[i][j].a.y && robo._centery-4*robo._radface>blocks[i][j].e.y){
					robo._centery=blocks[i][j].a.y+4*robo._radface;
					iftrampoline();
				}
				else{
					robo._centery=blocks[i][j].e.y-(robo._radface*6+robo._radface/4);
					robo._centery-=robo._jincy/robo._precision;
				}
			}		
		}	
		
		for(k=0;k<_noofmovingy;k++){	
			if(_movingblocks[2*k]==i && _movingblocks[2*k+1]==j){
				//printf("i=%d j=%d \n",i,j);
				//printf("%f %f\n",robo._centery,blocks[i][j].a.y+robo._radface*4);
				if(robo._centery==blocks[i][j].a.y+robo._radface*4){
					//printf("this is ti\n");
					if(_updown[k]==0){
						//printf("i am at right place\n");
						if((blocks[i][j].a.y)<_distance[k]){
							inc=0.5;
						}
						else{
							inc=-0.5;
						}
					}
					else if(_updown[k]==1){
						//printf("i am here\n");
						if((blocks[i][j].a.y)>-_distance[k]){
							inc=-0.5;
						}
						else{
							inc=0.5;
						}
					}
					_checkflag=1;
					break;
				}
				else if(robo._centery<blocks[i][j].a.y+robo._radface*4){
					_checkflag=0;
				}
				else{
					_checkflag=0;
				}
			}
			else{
				_checkflag=0;
			}
		}
	}
}

void update(int value) {
	if(robo._centery<-30){
		if(_level!=0){
			printf("you are dead\n");
			_level=0;
			_justonce=0;
			_level=0;
			//exit(0);
		}
	}
	else{
		if(_level!=0){
			//printf("yes\n");
			whereisbot();
		}
		glutPostRedisplay();
	}
	glutTimerFunc(50, update, 0);
	
}
