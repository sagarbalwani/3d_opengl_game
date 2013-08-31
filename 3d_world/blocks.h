#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include<string.h>
#include<time.h>

int _noofblocks=100;
int _noofstatic=46;

int _noofmovingy=10;
int _noofmovingz=5;
int _noofmovingx=5;

int _nooffalling=20;
int _nooftrampoline=2;
int _noofteleportor=2;

int _movingblocks[20];
int _movingblocksx[20];
int _movingblocksz[20];

int _fallingblocks[40];
int _trampolineblocks[4];
int _teleportorblocks[4];

int _updown[10];//tells the initial starting direction of the movement of blocks...
float _distance[10];//tells the distance by which the blocks should move randomly..
float _distance2[10];//tells the distance by which the blocks should move randomly..
int _updownx[5];//tells the initial starting direction of the movement of blocks...
float _distancex[5];//tells the distance by which the blocks should move randomly..
float _distancex2[5];//tells the distance by which the blocks should move randomly..
int _updownz[5];//tells the initial starting direction of the movement of blocks...
float _distancez[5];//tells the distance by which the blocks should move randomly..
float _distancez2[5];//tells the distance by which the blocks should move randomly..

typedef struct block{
	cor a,b,c,d,e,f,g,h;
	int flag;//tells which kind of block is it.../0 means not assigned,1 means static, 2 moving, 3 falling, 4 tranpoline, 5 teleportor, 6 voidic, 7 means have stone over them
	int _updown;//tells the initial starting direction of the movement of blocks...
	int _distance;//tells the distance by which the blocks should move randomly..
}block;

block blocks[10][10];

// Global Variables
float _initializepoint=100;//initial length of the box..

float mulvalue=2;//you can change this value to add space in between the tiles 
// should be b/w 1 and 2

void generateblocks(robots robo,int level){
	int i,j;
	float xstart=_initializepoint/2,zstart=_initializepoint/2;
	int inc=10;
	int flag=0;
	if(level==2 || level==3){
		mulvalue=2;
		_noofmovingz=5;
		_noofmovingx=5;
	}
	else if(level==1){
		mulvalue=1;
		_noofmovingz=0;
		_noofmovingx=0;
	}
	int countmoving=0;//every row will have any 3 moving blocks...
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			float up=0.0;
			if(i<5 && level==2){
				up=10.0;
			}
			else if(i<3 && level==3){
				up=20.0;
			}
			else if(i<7 && i>=3 && level==3){
				up=10.0;
			}
			blocks[i][j].a.x=-xstart+mulvalue*j*inc;
			blocks[i][j].a.y=-robo._radface*4+up;
			blocks[i][j].a.z=-zstart+mulvalue*i*inc;
			
			blocks[i][j].b.x=-xstart+mulvalue*j*inc+inc;
			blocks[i][j].b.y=-robo._radface*4+up;
			blocks[i][j].b.z=-zstart+mulvalue*i*inc;
			
			blocks[i][j].c.x=-xstart+mulvalue*j*inc+inc;
			blocks[i][j].c.y=-robo._radface*4+up;
			blocks[i][j].c.z=-zstart+mulvalue*i*inc+inc ;
			
			blocks[i][j].d.x=-xstart+mulvalue*j*inc;
			blocks[i][j].d.y=-robo._radface*4+up;
			blocks[i][j].d.z=-zstart+mulvalue*i*inc+inc;
			
			blocks[i][j].e.x=-xstart+mulvalue*j*inc;
			blocks[i][j].e.y=-robo._radface*4-3+up;
			blocks[i][j].e.z=-zstart+mulvalue*i*inc;
			
			blocks[i][j].f.x=-xstart+mulvalue*j*inc+inc;
			blocks[i][j].f.y=-robo._radface*4-3+up;
			blocks[i][j].f.z=-zstart+mulvalue*i*inc;
			
			blocks[i][j].g.x=-xstart+mulvalue*j*inc+inc;
			blocks[i][j].g.y=-robo._radface*4-3+up;
			blocks[i][j].g.z=-zstart+mulvalue*i*inc+inc ;
			
			blocks[i][j].h.x=-xstart+mulvalue*j*inc;
			blocks[i][j].h.y=-robo._radface*4-3+up;
			blocks[i][j].h.z=-zstart+mulvalue*i*inc+inc;
			//printf("%f %f\n",blocks[i][j].a.z,blocks[i][j].d.z);
			
			blocks[i][j].flag=0;
			if((i==0 && j==9) || (i==9 && j==0)){
				blocks[i][j].flag=1;//does not do anything have to be static...
			}
		}
		countmoving=0;
		while(countmoving!=1){//moving up down blocks....
			int randomblockno=rand()%10;//selects a block randomly			
			if(blocks[i][randomblockno].flag==0){
				blocks[i][randomblockno].flag=2;
				_movingblocks[i*2+countmoving*2]=i;
				_movingblocks[i*2+countmoving*2+1]=randomblockno;

				countmoving++;
			}
			
		}
		if(level==2 || level==3){
			if(i%2==0){
				//printf("%d value of i in x\n",i);
				countmoving=0;
				while(countmoving!=1){//moving left right in x blocks....
					int randomblockno=rand()%10;//selects a block randomly			
					if(blocks[i][randomblockno].flag==0){
						//printf("%d %dvalue of i in x\n",i,randomblockno);			
						blocks[i][randomblockno].flag=10;
						_movingblocksx[i*2+countmoving*2]=i;
						_movingblocksx[i*2+countmoving*2+1]=randomblockno;
						countmoving++;
					}
					
				}
			}
			
			else if(i%2==1){
				//printf("%d value of i in z\n",i);
				countmoving=0;
				while(countmoving!=1){//moving up down in z blocks....
					int randomblockno=rand()%10;//selects a block randomly					
					if(blocks[i][randomblockno].flag==0){
						//printf("%d %dvalue of i in z\n",i,randomblockno);					
						blocks[i][randomblockno].flag=11;
						_movingblocksz[i*2+countmoving*2]=i;
						_movingblocksz[i*2+countmoving*2+1]=randomblockno;
						countmoving++;
					}
					
				}
			}
		}
		countmoving=0;
		while(countmoving!=2){//falling blocks...
			int randomblockno=rand()%10;//selects a block randomly
			if(blocks[i][randomblockno].flag==0){
				blocks[i][randomblockno].flag=3;
				_fallingblocks[i*4+countmoving*2]=i;
				_fallingblocks[i*4+countmoving*2+1]=randomblockno;
				countmoving++;
			}
		}
		countmoving=0;
		while(countmoving!=1){
			int randomblockno=rand()%10;//selects a block randomly
			int randomblockproperty=rand()%2;//if 1 then block is voidic if 0 then block is having stone
			if(level==2 || level==3){
				randomblockproperty=0;
			}
			if(blocks[i][randomblockno].flag==0 && randomblockproperty==1){
				if((i==1 && j==9) || (i==0 && j==8) || (i==8 && j==0) || (i==9 && j==1));
				else{
					blocks[i][randomblockno].flag=6;//tile is voidic
					blocks[i][randomblockno].a.y=-300;//tile is voidic
					blocks[i][randomblockno].b.y=-300;//tile is voidic
					blocks[i][randomblockno].c.y=-300;//tile is voidic
					blocks[i][randomblockno].d.y=-300;//tile is voidic
					blocks[i][randomblockno].e.y=-400;//tile is voidic
					blocks[i][randomblockno].f.y=-400;//tile is voidic
					blocks[i][randomblockno].g.y=-400;//tile is voidic
					blocks[i][randomblockno].h.y=-400;//tile is voidic
					countmoving++;
				}
			}
			else if(blocks[i][randomblockno].flag==0 && randomblockproperty==0){
				blocks[i][randomblockno].flag=7;//tells that the block has stone over it
				blocks[i][randomblockno].a.y+=2;
				blocks[i][randomblockno].b.y+=2;
				blocks[i][randomblockno].c.y+=2;
				blocks[i][randomblockno].d.y+=2;
				countmoving++;
			}
		}
		
		for(j=0;j<10;j++){
			if(blocks[i][j].flag==0){
				blocks[i][j].flag=1;
			}
		}
	}
	
	countmoving=0;
	while(countmoving!=2){//8 for teleporter blocks
		int randomblockno=rand()%10;//selects a block randomly
		i=rand()%10;//selects a block randomly
		if((i==0 && randomblockno==9) || (i==9 && randomblockno==0));
		else{
			if(blocks[i][randomblockno].flag==1){
				blocks[i][randomblockno].flag=8;
				_teleportorblocks[2*countmoving]=i;
				_teleportorblocks[2*countmoving+1]=randomblockno;
				countmoving++;
			}
		}
	}
	
	countmoving=0;
	while(countmoving!=2){//9 for trampoline blocks
		int randomblockno=rand()%10;//selects a block randomly
		i=rand()%10;//selects a block randomly
		if((i==0 && randomblockno==9) || (i==9 && randomblockno==0));
		else{
			if(blocks[i][randomblockno].flag==1){
				blocks[i][randomblockno].flag=9;
				_trampolineblocks[2*countmoving]=i;
				_trampolineblocks[2*countmoving+1]=randomblockno;
				countmoving++;
			}
		}
	}
}


void drawBlocks(){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if(blocks[i][j].flag==6);
			else if (i==0 && j==9)
			{
				drawflag((blocks[i][j].a.x+blocks[i][j].c.x)/2,blocks[i][j].a.y,(blocks[i][j].a.z+blocks[i][j].c.z)/2);
				drawCube(blocks[i][j].a,blocks[i][j].b,blocks[i][j].c,blocks[i][j].d,blocks[i][j].e,blocks[i][j].f,blocks[i][j].g,blocks[i][j].h,blocks[i][j].flag,1);
			}
			else{
				drawCube(blocks[i][j].a,blocks[i][j].b,blocks[i][j].c,blocks[i][j].d,blocks[i][j].e,blocks[i][j].f,blocks[i][j].g,blocks[i][j].h,blocks[i][j].flag,0);
				}
		}
	}
}

void moveblocks1(int value){
	int i,j;
	for(i=0;i<_noofmovingy;i++){
		float inc;
		if((blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].a.y)>=_distance[i]){
			//printf("%d %d\n",_movingblocks[2*i],_movingblocks[2*i+1]);
			//if(_updown[i]==0){
			//	_updown[i]=0;
			//}
			//else if(_updown[i]==1){
			_updown[i]=1;
			//}
		}
		else if((blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].a.y)<=_distance2[i]){
			_updown[i]=0;
		}
		
		if(_updown[i]==0){
			inc=0.5;
		}
		else if(_updown[i]==1){
			inc=-0.5;
		}
		blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].a.y+=inc;
		blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].b.y+=inc;
		blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].c.y+=inc;
		blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].d.y+=inc;
		blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].e.y+=inc;
		blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].f.y+=inc;
		blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].g.y+=inc;
		blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].h.y+=inc;
	}
	for(i=0;i<_noofmovingx;i++){
		//printf("hey\n");
		float inc;
		if((blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].b.x)>=_distancex2[i]){
			_updownx[i]=1;
		}
		else if((blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].a.x)<=_distancex[i]){
			_updownx[i]=0;
		}
		if(_updownx[i]==0){
			inc=0.5;
		}
		else if(_updownx[i]==1){
			inc=-0.5;
		}
		blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].a.x+=inc;
		blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].b.x+=inc;
		blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].c.x+=inc;
		blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].d.x+=inc;
		blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].e.x+=inc;
		blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].f.x+=inc;
		blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].g.x+=inc;
		blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].h.x+=inc;
	}
	for(i=0;i<_noofmovingz;i++){
		//printf("hi\n");
		float inc;
		if((blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].a.z)<=_distancez[i]){
			_updownz[i]=0;
		}
		else if((blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].d.z)>=_distancez2[i]){
			_updownz[i]=1;
		}
		if(_updownz[i]==0){
			inc=0.5;
		}
		else if(_updownz[i]==1){
			inc=-0.5;
		}
		blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].a.z+=inc;
		blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].b.z+=inc;
		blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].c.z+=inc;
		blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].d.z+=inc;
		blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].e.z+=inc;
		blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].f.z+=inc;
		blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].g.z+=inc;
		blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].h.z+=inc;
	}

}

void moveblocks(){
	int i,j;
	for(i=0;i<_noofmovingy;i++){
		_updown[i]=rand()%2;//if updown flag==0 then up else if flag==1 then down
		_distance[i]=rand()%3;
		if(_distance[i]==0){
			_distance[i]=15+blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].a.y;
			_distance2[i]=-15+blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].a.y;
		}
		else if(_distance[i]==1){
			_distance[i]=15+blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].a.y;
			_distance2[i]=-15+blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].a.y;
		}
		else if(_distance[i]==2){
			_distance[i]=20+blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].a.y;
			_distance2[i]=-20+blocks[_movingblocks[2*i]][_movingblocks[2*i+1]].a.y;
		}
	}
	for(i=0;i<_noofmovingx;i++){
		_updownx[i]=rand()%2;//if updown flag==0 then up else if flag==1 then down
		//_distancex[i]=rand()%3;
		/* 		if(_distance[i]==0){
		_distance[i]=10;
		}
		else if(_distance[i]==1){
		_distance[i]=15;
		}
		else if(_distance[i]==2){
		_distance[i]=20;
		}
		*/
 		_distancex[i]=blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].a.x-(mulvalue-1)*10;
 		_distancex2[i]=blocks[_movingblocksx[4*i]][_movingblocksx[4*i+1]].b.x+(mulvalue-1)*10;
	}
	for(i=0;i<_noofmovingz;i++){
		_updownz[i]=rand()%2;//if updown flag==0 then up else if flag==1 then down
		//_distancez[i]=rand()%3;
		/* 		if(_distance[i]==0){
		_distance[i]=10;
		}
		else if(_distance[i]==1){
		_distance[i]=15;
		}
		else if(_distance[i]==2){
		_distance[i]=20;
		}
		*/ 		
		_distancez[i]=blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].a.z-(mulvalue-1)*10;
		_distancez2[i]=blocks[_movingblocksz[4*i+2]][_movingblocksz[4*i+3]].d.z+(mulvalue-1)*10;
	}
}

typedef struct s_coins{
		int blocki,blockj,draw;
}s_coins;

s_coins s_coin[11];


void generatecoins(){
	int s_count=10,i,s_check;
	while(s_count!=-1)
	{
		s_check=0;
		s_coin[s_count].blocki=rand()%10;			
		s_coin[s_count].blockj=rand()%10;
		if (blocks[s_coin[s_count].blocki][s_coin[s_count].blockj].flag==6 || (s_coin[s_count].blocki==9 && s_coin[s_count].blockj==0))
		{
			s_check=1;                  
		}
		s_coin[s_count].draw=1;
		for(i=10;i>s_count;i--)
		{
			if(s_coin[s_count].blocki==s_coin[i].blocki && s_coin[s_count].blockj==s_coin[i].blockj )
			{s_check=1;
				break;
			}
		}
		if (s_check==1);
		else
			s_count--;
	}
}
