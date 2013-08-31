#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include<string.h>
#include<time.h>

#include "human.h"

#include "robot.h"

#include "blocks.h"

robots robo;//this is the player robo...

robots enemyrobo1;
robots enemyrobo2;

void drawenemysubhuman(robots enemy1,float angle){
	//{{{
	glPushMatrix();
	glTranslatef(enemy1._centerx,enemy1._centery,enemy1._centerz);
	glRotatef(angle,0,1,0);
	
	drawFace(enemy1._radface,0,enemy1._radface*4 + enemy1._radface/4 + enemy1._radface,0);
	
	drawNeck(enemy1._radface,0,enemy1._radface*4,0);
	
	drawStomach2(enemy1._radface,0,0,0);
	
	drawluarm(enemy1._radface,-enemy1._radface*1.35,enemy1._radface*4,0,enemy1._flaglefthand,enemy1._handangle);
	
	drawruarm(enemy1._radface,enemy1._radface*1.35,enemy1._radface*4,0,enemy1._flaglefthand,enemy1._handangle);
	
	drawluleg(enemy1._radface,-enemy1._radface*1.35,0,0,enemy1._flagleftleg,enemy1._legangle);
	
	drawruleg(enemy1._radface,enemy1._radface*1.35,0,0,enemy1._flagleftleg,enemy1._legangle);
	
	glPopMatrix();
	//}}}
}

void drawenemyhuman(robots *enemy1,int dir){
	//{{{
	if(dir!=enemy1->_curdir){
		enemy1->_blocktillrotate=1;
		enemy1->_angleofrot=getangle(&enemy1->_curdir,enemy1->_curdir,dir);
		//glutTimerFunc(100,rotatehead,0);
		enemy1->_humanangle+=enemy1->_angleofrot;
	}
	if(enemy1->_humanangle>=360){
		enemy1->_humanangle-=360;
	}
	else if(enemy1->_humanangle<0){
		enemy1->_humanangle+=360;
	}
	drawenemysubhuman(*enemy1,enemy1->_humanangle);
	//}}}
}

int whererobowishestogo(robots robo){
	int a[4];
	a[0]=robo.nooftimesleft;
	a[1]=robo.nooftimesright;
	a[2]=robo.nooftimesup;
	a[3]=robo.nooftimesdown;
	int max=0;
	int index=-1;
	int i;
	for(i=0;i<4;i++){
		//	printf("max=%f a[i]=%f\n",max,a[i]);
		if(max<a[i]){
			max=a[i];
			index=i;
		}
	}
	return index;
}

int tellme2(float a,float b,float c,float d,float botx,float botz){//tells whether the bot is on this particular tile or not
	if(botx >= a && botx < b && botz >= c && botz < d){
		return 1;
	}
	else{
		return 0;
	}
}

int tellme(cor a,cor b,cor c,cor d,float botx,float botz){//tells whether the bot is on this particular tile or not
	if(botx >= a.x && botx < b.x && botz >= a.z && botz < d.z){
		return 1;
	}
	else{
		return 0;
	}
}

void findenemybot(robots *enemy1,robots *enemy2,float d,float e,float f){//this function is for motion of the bot
	int i,j;
	int yes=0;
	
	int oti=-1,otj=-1;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			yes=tellme(blocks[i][j].a,blocks[i][j].b,blocks[i][j].c,blocks[i][j].d,d,f);
			if(yes==1){
				oti=i;
				otj=j;
				break;
			}
		}
		if(yes==1){
			break;
		}
	}
	if(oti==-1 or otj==-1){
		if(enemy1->noofjumps==enemy1->_precision){
			printf("i was here\n");
			enemy1->noofjumps=0;
		}
		else{
			enemy1->jump(0);
		}
	}
	else{
		if(blocks[oti][otj].flag==6){
			printf("jumping %d\n",enemy1->noofjumps);
			if(enemy1->noofjumps==enemy1->_precision){
				printf("i was here\n");
				//exit(0);
				enemy1->noofjumps=0;
			}
			else{
				enemy1->jump(0);
			}
		}
		else{
			enemy1->noofjumps=0;
			enemy1->_centery=blocks[i][j].b.y+enemy1->_radface*4;
		}
	}
}

void moveenemy(robots *enemy1,robots *enemy2,robots robo,int primarybotflag){//primarybotflag tells which is the primary robot
	int flag=whererobowishestogo(robo);
	//printf("%d\n",flag);
	int icangothistime=1;
	if(enemy1->noofjumps>0){
		printf("yes\n");
	}
	else{
		if(flag==-1){
			//printf("yes\n");
			if(robo._centerx<enemy1->_centerx){
				enemy1->_newdir=2;
				enemy1->goleft(0);
				icangothistime=0;
				if(primarybotflag==1){
					if(enemy1->_centerx-5<=enemy2->_centerx){
						enemy1->goright(0);
						icangothistime=1;
					}
				}
			}
			else if(robo._centerx>enemy1->_centerx){
				enemy1->_newdir=1;
				enemy1->goright(0);
				icangothistime=0;
				if(primarybotflag==0){
					if(enemy1->_centerx+5>=enemy2->_centerx && robo._centerx>enemy1->_centerx+5){
						enemy1->goleft(0);
						icangothistime=1;
					}
				}
			}
			if(icangothistime==1){
				if(robo._centerz<enemy1->_centerz){
					enemy1->_newdir=4;
					enemy1->goup(0);
				}
				else if(robo._centerz>enemy1->_centerz){
					enemy1->_newdir=3;
					enemy1->godown(0);
				}
			}
		}
		if(flag==0){
			if(robo._centerx<enemy1->_centerx){
				enemy1->_newdir=2;
				enemy1->goleft(0);
				icangothistime=0;
				if(primarybotflag==1){
					if(enemy1->_centerx-5<=enemy2->_centerx){
						enemy1->goright(0);
						icangothistime=1;
					}
				}
			}
			else if(robo._centerx>enemy1->_centerx){
				enemy1->_newdir=1;
				enemy1->goright(0);
				if(primarybotflag==0){
					if(enemy1->_centerx+5>=enemy2->_centerx && robo._centerx>enemy1->_centerx+5){
						enemy1->goleft(0);
						icangothistime=1;
					}
				}			
			}
		}
		else if(flag==1){
			if(robo._centerx<enemy1->_centerx){
				enemy1->_newdir=2;
				enemy1->goleft(0);
				icangothistime=0;
				if(primarybotflag==1){
					if(enemy1->_centerx-5<=enemy2->_centerx){
						enemy1->goright(0);
						icangothistime=1;
					}
				}
			}
			else if(robo._centerx>enemy1->_centerx){
				enemy1->_newdir=1;
				enemy1->goright(0);
				if(primarybotflag==0){
					if(enemy1->_centerx+5>=enemy2->_centerx && robo._centerx>enemy1->_centerx+5){
						enemy1->goleft(0);
						icangothistime=1;
					}
				}

			}
		}
		else if(flag==2 || icangothistime==1){//up going
			if(robo._centerz<enemy1->_centerz){
				enemy1->_newdir=4;
				enemy1->goup(0);
			}
			else if(robo._centerz>enemy1->_centerz){
				enemy1->_newdir=3;
				enemy1->godown(0);
			}
		}
		else if(flag==3 || icangothistime==1){
			if(robo._centerz<enemy1->_centerz){
				enemy1->_newdir=4;
				enemy1->goup(0);
			}
			else if(robo._centerz>enemy1->_centerz){
				enemy1->_newdir=3;
				enemy1->godown(0);
			}
		}
	}
	findenemybot(enemy1,enemy2,enemy1->_centerx,enemy1->_centery,enemy1->_centerz);
}

void seperate(robots *enemy1,robots *enemy2){
	//int yes=tellme2(enemy1->_centerx-5,enemy1->_centerx+5,enemy1->_centerz-5,enemy1->_centerz+5,enemy2->_centerx,enemy2->_centerz);
	if(enemy1->_centerx==enemy2->_centerx && enemy1->_centerz==enemy2->_centerz){
		enemy2->_centerx+=1;
		enemy2->_centerz+=1;
	}	
}

void updateenemy(int value){
	//printf("****yes\n");
	moveenemy(&enemyrobo1,&enemyrobo2,robo,0);
	//seperate(&enemyrobo1,&enemyrobo2);
	glutTimerFunc(50, updateenemy, 0);	
}

void updateenemy2(int value){
	//printf("****yes\n");
	moveenemy(&enemyrobo2,&enemyrobo1,robo,1);
	//seperate(&enemyrobo1,&enemyrobo2);
	glutTimerFunc(50, updateenemy2, 0);	
}
