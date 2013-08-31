#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include<string.h>
#include<time.h>

using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

class robots{
	
public :
	
	float _radface;
	float _centerx,_centery,_centerz;//human stomach's position
	
	int _curdir;//1 means px,2 means nx,3 means pz,4 means nz
	int _newdir;//tells what the new direction of the robot should be
	float _humanangle;
	float _angleofrot;
	int _blocktillrotate;
	
	
	int _flaglefthand;//means that the left hand is backwards
	int _flagleftleg;//means that the left leg is backwards
	float _handangle;//means that the left hand is backwards by angle 45 degrees
	float _legangle;//means that the left hand is backwards by angle 45 degrees
	float _inc;//it is the increment factor for the robot to move in the x,z direction
	int _precision;//tells the required precision during motion... :)
	
	int noofjumps;
	int _icanjump;
	int _stopjumping;//0 means jumping can continue 1 means jumping has to stop because it has landed on a moving tile
	
	
	int nooftimesleft;
	int nooftimesright;
	int nooftimesdown;
	int nooftimesup;
	int nooftimesrotate;
	
	int _icanteleport;
	float _jincxz;
	float _jincy;
	
	robots(){
		
		_radface=0.5;
		_centerx=0,_centery=0,_centerz=0;//human stomach's position
		
		_curdir=1;//1 means px,2 means nx,3 means pz,4 means nz
		_newdir=1;//tells what the new direction of the robot should be
		_humanangle=90;
		_angleofrot=0;
		_blocktillrotate=0;
		
		
		_flaglefthand=0;//means that the left hand is backwards
		_flagleftleg=0;//means that the left leg is backwards
		_handangle=45;//means that the left hand is backwards by angle 45 degrees
		_legangle=-45;//means that the left hand is backwards by angle 45 degrees
		_inc=2.5;//it is the increment factor for the robot to move in the x,z direction
		_precision=10;//the required precision should in powers of 2 or 5 
		
		noofjumps=0;
		_icanjump=1;
		_stopjumping=0;//0 means jumping can continue 1 means jumping has to stop because it has landed on a moving tile
		
		
		nooftimesleft=0;
		nooftimesright=0;
		nooftimesdown=0;
		nooftimesup=0;
		nooftimesrotate=0;
		
		_icanteleport=1;
		_jincxz=15.0;
		_jincy=15.0;
	}
	
	
	void rotatehead(){
		nooftimesrotate++;
		_humanangle+=_angleofrot/_precision;
	}
	
	void dohand(){
		if(_handangle==45){
			_flaglefthand=0;
		}
		else if(_handangle==-45){
			_flaglefthand=1;
		}
		if(_flaglefthand==1){
			_handangle+=90.0/_precision;
		}
		else if(_flaglefthand==0){
			_handangle-=90.0/_precision;
		}
	}
	
	void doleg(){
		if(_legangle==45){
			_flagleftleg=0;
		}
		else if(_legangle==-45){
			_flagleftleg=1;
		}
		if(_flagleftleg==1){
			_legangle+=90.0/_precision;
		}
		else if(_flagleftleg==0){
			_legangle-=90.0/_precision;
		}
	}
	
	void jump(int value){
		
		if(noofjumps<_precision/2){
			dohand();
			doleg();
			_centery+=_jincy/_precision;
		}
		else{
			if(_precision%2==1 && noofjumps==_precision/2){
				printf("??????????yes\n");
			}
			else{
				_centery-=_jincy/_precision;
			}
		}
		if(_curdir==1){
			_centerx+=_jincxz/_precision;
		}
		else if(_curdir==2){
			_centerx-=_jincxz/_precision;
		}
		else if(_curdir==3){
			_centerz+=_jincxz/_precision;
		}
		else if(_curdir==4){
			_centerz-=_jincxz/_precision;
		}
		noofjumps++;
	}
	
	
	void goleft(int value){
		dohand();
		doleg();
		_centerx-=_inc/_precision;
		nooftimesleft++;
	}
	void goright(int value){
		dohand();
		doleg();
		_centerx+=_inc/_precision;
		nooftimesright++;
	}
	void goup(int value){
		dohand();
		doleg();
		_centerz-=_inc/_precision;
		nooftimesup++;
	}
	void godown(int value){
		dohand();
		doleg();
		_centerz+=_inc/_precision;
		nooftimesdown++;
	}
	
};
