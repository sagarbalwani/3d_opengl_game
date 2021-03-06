#include<stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include<string.h>

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

int _level=0;
int _level2=0;

typedef struct cor{
	float x,y,z;
}cor;


//working with textures....
#include "imageloader.h"
//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
GLuint _textureId1; //The id of the texture
GLuint _textureId5;//for coins
GLuint _textureId6;//for coins
GLuint _textureId7;//for coins
GLuint _textureId8;//for coins
GLuint _textureId9;//for coins
GLuint _textureId10;//for coins
GLuint _textureId11;//for coins

void drawflag(float x,float y,float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glPushMatrix();
	glRotatef(-90,1,0,0);
	glColor3f(1,0,0);
	gluCylinder(gluNewQuadric(), 0.25,0.25,18, 8, 300);
	glPopMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(0,1,0);
	glVertex3f(0,14,0);
	glVertex3f(0,18,0);
	glVertex3f(2.5,16,0);
	glEnd();
	glPopMatrix();
}
void drawCube(cor a,cor b,cor c,cor d,cor e,cor f,cor g,cor h,int flag,int secondflag){
	//binding texture...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
	
	if(flag==1){//static color yellow
		glColor3f(1,1,1);
	}
	else if(flag==2){//moving color green
		glColor3f(0,1,0);
	}
	else if(flag==3){//falling color red
		glColor3f(1,0,0);
	}
	else if(flag==4){//trampolin color black
		glColor3f(0,0,0);
	}
	else if(flag==5){//teleportor color blue
		glColor3f(0,0,1);
	}
	else if(flag==7){
		glColor3f(0,0,(204.0/255.0));
	}
	else if(flag==8){//for teleportor blocks
		glColor3f(1.0,0.0,0.5);//pink
	}
	else if(flag==9){//for trampline blocks
		glColor3f(1.0,0.5,0.0);//yellowish
	}
	else if(flag==10){//for x moving blocks
		glColor3f(0.0,0.0,0.0);//
	}	
	else if(flag==11){//for z moving blocks
		glColor3f(0.0,0.0,0.0);//
	}
	if (secondflag==1)
	{
		glColor3f(0.1,0.5,0.1);//
	}
	//making the top
	glTexCoord2f(0.0, 0.0);
	glVertex3f(a.x,a.y,a.z);
	glTexCoord2f(2, 0.0);
	glVertex3f(b.x,b.y,b.z);
	glTexCoord2f(2, 2);
	glVertex3f(c.x,c.y,c.z);
	glTexCoord2f(0, 2);
	glVertex3f(d.x,d.y,d.z);
	
	//making the bottom
	glColor3f(0,0,0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(e.x,e.y,e.z);
	glTexCoord2f(2, 0.0);
	glVertex3f(f.x,f.y,f.z);
	glTexCoord2f(2, 2);
	glVertex3f(g.x,g.y,g.z);
	glTexCoord2f(0.0, 2);
	glVertex3f(h.x,h.y,h.z);
	
	//making the front
	glColor3f(0,1,1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(d.x,d.y,d.z);
	glTexCoord2f(2.0, 0.0);
	glVertex3f(c.x,c.y,c.z);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(g.x,g.y,g.z);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(h.x,h.y,h.z);

	//making the right
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(c.x,c.y,c.z);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(b.x,b.y,b.z);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(f.x,f.y,f.z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(g.x,g.y,g.z);

	//making the back
	glColor3f(0,1,1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(a.x,a.y,a.z);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(b.x,b.y,b.z);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(f.x,f.y,f.z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(e.x,e.y,e.z);
	
	//making the left
	glColor3f(0,1,1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(a.x,a.y,a.z);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(d.x,d.y,d.z);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(h.x,h.y,h.z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(e.x,e.y,e.z);

	glEnd();
        glDisable(GL_TEXTURE_2D);

}

void drawluarm(float _radface,float x,float y,float z,int flag,float angle){//getting the upper end of the cylinder
//radius of arm will be radface/4
	//flag==1 move forward so anticlockwise so angle is positive
	glPushMatrix();
	glColor3f(1.0,0.5,0.5);

	glTranslatef(x-_radface/4,y-_radface/4,z);
	
//	if(flag==1){
		glRotatef(angle,1,0,0);
//	}
//	else if(flag==0){
//		glRotatef(-angle,1,0,0);
//	}

	glutSolidSphere( _radface/4, 10.0, 10.0); //the radius of the face is 14
	glTranslatef(0,-_radface/4,0);
	glRotatef(90,1,0,0);
	
	gluCylinder(gluNewQuadric(), _radface/4,_radface/4,4*_radface, 8, 300);//the radius of neck is radface/4 and height of neck is radface/2...
	
	glPopMatrix();

}

void drawruarm(float _radface,float x,float y,float z,int flag,float angle){//flag==1 means move backwards so clockwise so angle is negative
//radius of arm will be radface/4
	glPushMatrix();
	glColor3f(1.0,0.5,0.5);

	glTranslatef(x+_radface/4,y-_radface/4,z);

//	if(flag==1){
		glRotatef(-angle,1,0,0);
//	}
//	else if(flag==0){
//		glRotatef(angle,1,0,0);
//	}

	glutSolidSphere( _radface/4, 10.0, 10.0); //the radius of the face is 14
	glTranslatef(0,-_radface/4,0);
	glRotatef(90,1,0,0);
	gluCylinder(gluNewQuadric(), _radface/4,_radface/4,4*_radface, 8, 300);//the radius of neck is radface/4 and height of neck is radface/2...
	
	glPopMatrix();

}

void drawluleg(float _radface,float x,float y,float z,int flag,float angle){
	glPushMatrix();
	
	glTranslatef(x+_radface*1.35/3,y-_radface/4,z);
	glColor3f(0.5,0.5,0);

	glRotatef(angle,1,0,0);//for moving the legs
	
	glutSolidSphere( _radface/4, 10.0, 10.0); //the radius of the face is 14
	glTranslatef(0,-_radface/4,0);
	glRotatef(90,1,0,0);
	gluCylinder(gluNewQuadric(), _radface/4,_radface/4,4*_radface, 8, 300);//the radius of neck is radface/4 and height of neck is radface/2...

	glPopMatrix();
}

void drawruleg(float _radface,float x,float y,float z,int flag,float angle){

	glPushMatrix();
	
	glTranslatef(x-_radface*1.35/3,y-_radface/4,z);
	glColor3f(0.5,0.5,0);
	glRotatef(-angle,1,0,0);//for moving the legs
	glutSolidSphere( _radface/4, 10.0, 10.0); //the radius of the face is 14
	glTranslatef(0,-_radface/4,0);
	glRotatef(90,1,0,0);
	gluCylinder(gluNewQuadric(), _radface/4,_radface/4,4*_radface, 8, 300);//the radius of neck is radface/4 and height of neck is radface/2...

	glPopMatrix();
}


void drawStomach(float _radface,float sx,float sy,float sz){
	glPushMatrix();

	glTranslatef(sx,sy,sz);

	glColor3f(0.0,0.5,0.5);
	
	glutSolidSphere( 1.35*_radface, 10.0, 10.0); //the radius of the face is 14

	glPopMatrix();
}

void drawStomach2(float _radface,float sx,float sy,float sz){
	glPushMatrix();
	glTranslatef(sx,sy,sz);
	glRotatef(-90.0,1.0,0.0,0.0);

	glBegin(GL_POLYGON);
	
	glColor3f(0.0,0.5,0.5);
	GLUquadricObj *obj = gluNewQuadric();
	gluCylinder(obj, _radface*1.35,1.35*_radface,4*_radface, 8, 300);//the radius of stomach is radface*1.35 and height of neck is radface*4...
	gluDisk(gluNewQuadric(), 0, _radface*1.35, 32, 32);
	glPushMatrix();
	glTranslatef(0.0,0.0,4*_radface);
	gluDisk(gluNewQuadric(), 0, _radface*1.35, 32, 32);
	glPopMatrix();
	glEnd();

	glPopMatrix();
}

void drawNeck(float _radface,float neckx,float necky,float neckz){
	glPushMatrix();

	glTranslatef(neckx,necky,neckz);
	glRotatef(-90.0,1.0,0.0,0.0);

	glBegin(GL_POLYGON);

	glColor3f(12.0,0.5,0);
	GLUquadricObj *obj = gluNewQuadric();

	gluCylinder(obj, _radface/4.0,_radface/4.0,_radface/4, 8, 300);//the radius of neck is radface/4 and height of neck is radface/2...

	glEnd();

	glPopMatrix();
}

void drawFace(float _radface,float facex,float facey,float facez){

	glPushMatrix();
	glTranslatef(facex,facey,facez);
//	glRotatef(-30,1.0,0.0,0.0);
//	glRotatef(-30,0.0,1.0,0.0);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glColor3f(1.0,1.0,1.0);
	glutSolidSphere( _radface, 10.0, 10.0); //the radius of the face is 14

	//making of right eye.. :)
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef(_radface/(2*1.4142),_radface/(2*1.4142), sqrt(_radface*_radface - 2*((_radface/(2*1.4142))*(_radface/(2*1.4142)))));
	glutSolidSphere( _radface/10.0, 10.0, 10.0); 
	glPopMatrix();

	//making of left eye.. :)
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef(-_radface/(2*1.4142),_radface/(2*1.4142), sqrt(_radface*_radface - 2*((_radface/(2*1.4142))*(_radface/(2*1.4142)))));
	glutSolidSphere( _radface/10.0, 10.0, 10.0); 
	glPopMatrix();

	//making of nose...
	glPushMatrix();
	glColor3f(0.0,1.0,0.0);
	glTranslatef(0.0,0.0,_radface);
	glutSolidSphere( _radface/10.0, 10.0, 10.0); 
	glPopMatrix();

	//making of mouth...
	glPushMatrix();
	glColor3f(0.0,0.0,1.0);
	glTranslatef(0,-_radface/(2*1.4142), sqrt(_radface*_radface - ((_radface/(2*1.4142))*(_radface/(2*1.4142)))));
	glBegin(GL_TRIANGLES);
	glVertex3f(_radface/10,0.0,0.0);
	glVertex3f(-_radface/10,0.0,0.0);
	glVertex3f(0.0, -2*_radface*sqrt(3)/2/10  ,0.0);
	glEnd();
	glPopMatrix();


	glPopMatrix();

}

float getangle(int *a,int _curdir,int dir){//tells the angle of the current robot position with respect to required 
	if(dir==1){
		*a=1;
		if(_curdir==1){
			return 0;
		}
		else if(_curdir==2){
			return -180;
		}
		else if(_curdir==3){
			return 90;
		}
		else if(_curdir==4){
			return -90;
		}
	}
	else if(dir==2){
		*a=2;
		if(_curdir==1){
			return -180;
		}
		else if(_curdir==2){
			return 0;
		}
		else if(_curdir==3){
			return -90;
		}
		else if(_curdir==4){
			return 90;
		}
	}
	else if(dir==3){
		*a=3;
		if(_curdir==1){
			return -90;
		}
		else if(_curdir==2){
			return 90;
		}
		else if(_curdir==3){
			return 0;
		}
		else if(_curdir==4){
			return -180;
		}
	}
	else if(dir==4){
		*a=4;
		if(_curdir==1){
			return 90;
		}
		else if(_curdir==2){
			return -90;
		}
		else if(_curdir==3){
			return -180;
		}
		else if(_curdir==4){
			return 0;
		}
	}
}

void drawdeadrobo(float x,float y,float z){
/* 	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(-90.0,1.0,0.0,0.0);

	glBegin(GL_POLYGON);

	glColor3f(0.0,0.5,0.5);
	GLUquadricObj *obj = gluNewQuadric();
	gluCylinder(obj, _radface*1.35,1.35*_radface,4*_radface, 300, 300);//the radius of stomach is radface*1.35 and height of neck is radface*4...
	gluDisk(gluNewQuadric(), 0, _radface*1.35, 32, 32);
	glPushMatrix();
	glTranslatef(0.0,0.0,4*_radface);
	gluDisk(gluNewQuadric(), 0, _radface*1.35, 32, 32);
	glPopMatrix();
	glEnd();

	glPopMatrix();
 */}
 
 //declare
int coin_angle=0;
//done
// in update func;
//done
void drawcoin(float size,float thick,float x,float y,float z,GLuint _id)
{
	GLUquadric *qobj = gluNewQuadric();
	//glColor3f(229.0/255.0,174.0/255.0,22.0/255.0);
        glColor3f(1,1,1);
	gluQuadricTexture(qobj,GL_TRUE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPushMatrix();

        glTranslatef(x,y,z);        
        glRotatef(coin_angle,0,1,0);
        gluDisk(qobj,size/3,size,20,8);
        gluCylinder(qobj,size,size,thick,20,8);
        glTranslatef(0,0,thick);
        gluDisk(qobj,size/3,size,20,8);
        glPopMatrix();
        gluDeleteQuadric(qobj);
        glDisable(GL_TEXTURE_2D);
}

void drawPower(float x,float y,float z,float size){
	//gluQuadricTexture(qobj,GL_TRUE);
	
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef(x,y,z);
	glRotatef(coin_angle,0,1,0);

/* 	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D,_textureId1); */
	glutSolidCube(size);	
/* 	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T); */

	glPopMatrix();

}

void drawSphere(float size,float x,float y,float z,GLuint _id,int flag)
{
	GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	if(flag==0){
		glScalef(10,10,10);
	}
	else if(flag==1){
		glScalef(1,1,500);
	}


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,_id);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();		
	glTranslatef(x,y,z);
	gluSphere(qobj,size,20,20);
	glPopMatrix();
	gluDeleteQuadric(qobj);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	//glScalef(4,2,1);
	glMatrixMode(GL_MODELVIEW);

}

void drawSphere2(float size,float x,float y,float z,GLuint _id)//for drawing sun and moon
{
	GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,_id);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();		
	glTranslatef(x,y,z);
	glColor3f(255,255,255);
	gluSphere(qobj,size,20,20);
	glPopMatrix();
	gluDeleteQuadric(qobj);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	//glScalef(4,2,1);
	glMatrixMode(GL_MODELVIEW);

}

float _sunx=500,_suny=300,_sunz=-500,_sunr=650,_sundone=0,_sunsize=10;
void drawSun(float size,float x,float y,float z){
	glPushMatrix();
	glTranslatef(50,-400,0);
	GLfloat whiteAmbientMaterial[] = {1.0, 1.0, 1.0};	 
//	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,whiteEmissiveMaterial);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteEmissiveMaterial);
//	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,whiteEmissiveMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteAmbientMaterial);
	if(_level==2 || _level==3){
		drawSphere2(size,x,y,z,_textureId9); //the radius of the face is 14
	}
	else{
		drawSphere2(size,x,y,z,_textureId6); //the radius of the face is 14
	}
	glPopMatrix();
}

void drawPoint(float x,float y,float z){
	glPushMatrix();
	glTranslatef(x,y,z);
	glColor3f(0,0,0);
	gluDisk(gluNewQuadric(), 0,1, 10, 10);	
	glPopMatrix();
}

void drawSheet(float x,float y,float z){
	glPushMatrix();
	
	glTranslatef(x,y,z);
	glColor3f(1,0,0);

	glBegin(GL_QUADS);
	glVertex3f(x-2,y-2,z);
	glVertex3f(x+2,y-2,z);
	glVertex3f(x+2,y+2,z);
	glVertex3f(x-2,y+2,z);
	glEnd();
	
	glPopMatrix();	
}

