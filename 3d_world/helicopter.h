#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include<string.h>
#include<time.h>
using namespace std;


#define pi 3.141592653589
#define d2r(deg) (deg * pi / 180)

//declare s_ts is the tile size s_hd is 12.0
float s_ts=10.0,s_hhelangle=0,s_hcamangle=0,s_vcamangle=0,s_hdis=14*s_ts,s_hd=12;
int s_mousex=500,s_mousey=0;
float s_eyex=0,s_eyey=10,s_eyez=s_hd*s_ts;
float s_centerx=0,s_centery=0,s_centerz=0;
float s_upx=0,s_upy=1,s_upz=0;
int s_vertical=0;
int s_a;
int s_b;

void letsee2(int x,int y,double *f,double *g,double *h);
double _dpx=0,_dpy=0,_dpz=0;
void handlemousemovement(int x,int y)
{
	if(_level==0){
		//letsee(x,y);
	}
	else if(_level!=0){
		//_dpx=0;_dpy=0;_dpz=0;		
		//letsee2(x,y,&_dpx,&_dpy,&_dpz);
		if(_cameraview==4)
		{
			s_hcamangle=x*360/s_a;
			s_vcamangle=y*360/s_b;
			if (s_vertical==0)
			{
				if(s_hcamangle>=0 && s_hcamangle<90)
				{
					s_centerz =s_eyez + s_hdis*cos(d2r(s_hcamangle));
					s_centerx =s_eyex -  s_hdis*sin(d2r(s_hcamangle));
				}
				else if(s_hcamangle>=90 && s_hcamangle<180)
				{
					s_centerz =s_eyez - s_hdis*fabs(cos(d2r(s_hcamangle)));
					s_centerx =s_eyex - s_hdis*fabs(sin(d2r(s_hcamangle)));
				}
				else if(s_hcamangle>=180 && s_hcamangle<270)
				{
					s_centerz =s_eyez - s_hdis*fabs(cos(d2r(s_hcamangle)));
					s_centerx =s_eyex + s_hdis*fabs(sin(d2r(s_hcamangle)));
				}
				else
				{
					s_centerz =s_eyez + s_hdis*fabs(cos(d2r(s_hcamangle)));
					s_centerx =s_eyex + s_hdis*fabs(sin(d2r(s_hcamangle)));
				}
			}
			else if(s_vertical==1){
				//      printf("vang=%f hang=%f\n",s_vcamangle,s_hhelangle);
				if(s_vcamangle>=0 && s_vcamangle<90)
				{
					s_centery =s_eyey +  s_hdis*sin(d2r(s_vcamangle));
					if(s_hhelangle>=0 && s_hhelangle<90)
					{
						s_centerz =s_eyez + s_hdis*cos(d2r(s_vcamangle))*cos(d2r(s_hhelangle));
						s_centerx =s_eyex -  s_hdis*cos(d2r(s_vcamangle))*sin(d2r(s_hhelangle));
					}
					else if(s_hhelangle>=90 && s_hhelangle<180)
					{
						s_centerz =s_eyez - s_hdis*cos(d2r(s_vcamangle))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex - s_hdis*cos(d2r(s_vcamangle))*fabs(sin(d2r(s_hhelangle)));
					}
					else if(s_hhelangle>=180 && s_hhelangle<270)
					{
						s_centerz =s_eyez - s_hdis*cos(d2r(s_vcamangle))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex + s_hdis*cos(d2r(s_vcamangle))*fabs(sin(d2r(s_hhelangle)));
					}
					else
					{
						s_centerz =s_eyez + s_hdis*cos(d2r(s_vcamangle))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex + s_hdis*cos(d2r(s_vcamangle))*fabs(sin(d2r(s_hhelangle)));
					}
				}
				else if(s_vcamangle>=90 && s_vcamangle<180)
				{
					s_centery =s_eyey + s_hdis*fabs(sin(d2r(s_vcamangle)));
					if(s_hhelangle>=0 && s_hhelangle<90)
					{
						s_centerz =s_eyez - s_hdis*fabs(cos(d2r(s_vcamangle)))*cos(d2r(s_hhelangle));
						s_centerx =s_eyex +  s_hdis*fabs(cos(d2r(s_vcamangle)))*sin(d2r(s_hhelangle));
					}
					else if(s_hhelangle>=90 && s_hhelangle<180)
					{
						s_centerz =s_eyez + s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex + s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(sin(d2r(s_hhelangle)));
					}
					else if(s_hhelangle>=180 && s_hhelangle<270)
					{
						s_centerz =s_eyez + s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex - s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(sin(d2r(s_hhelangle)));
					}
					else
					{
						s_centerz =s_eyez - s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex - s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(sin(d2r(s_hhelangle)));
					}
				}
				else if(s_vcamangle>=180 && s_vcamangle<270)
				{
					s_centery =s_eyey - s_hdis*fabs(sin(d2r(s_vcamangle)));
					if(s_hhelangle>=0 && s_hhelangle<90)
					{
						s_centerz =s_eyez - s_hdis*fabs(cos(d2r(s_vcamangle)))*cos(d2r(s_hhelangle));
						s_centerx =s_eyex +  s_hdis*fabs(cos(d2r(s_vcamangle)))*sin(d2r(s_hhelangle));
					}
					else if(s_hhelangle>=90 && s_hhelangle<180)
					{
						s_centerz =s_eyez + s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex + s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(sin(d2r(s_hhelangle)));
					}
					else if(s_hhelangle>=180 && s_hhelangle<270)
					{
						s_centerz =s_eyez + s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex - s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(sin(d2r(s_hhelangle)));
					}
					else
					{
						s_centerz =s_eyez - s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex - s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(sin(d2r(s_hhelangle)));
					}
				}
				else
				{
					s_centery =s_eyey - s_hdis*fabs(sin(d2r(s_vcamangle)));
					if(s_hhelangle>=0 && s_hhelangle<90)
					{
						s_centerz =s_eyez + s_hdis*fabs(cos(d2r(s_vcamangle)))*cos(d2r(s_hhelangle));
						s_centerx =s_eyex -  s_hdis*fabs(cos(d2r(s_vcamangle)))*sin(d2r(s_hhelangle));
					}
					else if(s_hhelangle>=90 && s_hhelangle<180)
					{
						s_centerz =s_eyez - s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex - s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(sin(d2r(s_hhelangle)));
					}
					else if(s_hhelangle>=180 && s_hhelangle<270)
					{
						s_centerz =s_eyez - s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex + s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(sin(d2r(s_hhelangle)));
					}
					else
					{
						s_centerz =s_eyez + s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(cos(d2r(s_hhelangle)));
						s_centerx =s_eyex + s_hdis*fabs(cos(d2r(s_vcamangle)))*fabs(sin(d2r(s_hhelangle)));
					}
				}
				//      printf("s_centerx=%f s_centery=%f s_centerz=%f\n",s_centerx,s_centery,s_centerz);
			}
		}
		s_mousex=x;s_mousey=y;
	}
}





void handlemousemovementclick(int x,int y)
{
	if(_level!=0){ 
		if(_cameraview==4)
		{ 
			
			if (s_mousex-x>=0){
				s_hhelangle=(s_mousex-x)*360/s_a;
			}
			else{
				s_hhelangle=360+((s_mousex-x)*360/s_a);
			}
			//      printf("s_mousex= %d x= %d ang=%f\n",s_mousex,x,s_hhelangle);
			//      s_vcamangle=y*360/b;
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
