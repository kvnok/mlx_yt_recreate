#include "../include/stuff.h"

/*
	float 			px;
	float 			py;
	float			pdx;
	float			pdy;
	float			pa;
}	t_player;
*/

void drawRays2D(t_data *data) {
	int map[]= {
		1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,1,0,0,0,1,
		1,0,1,0,1,0,0,1,
		1,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
	};
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	int side;

	float vx;
	float vy;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;
	float disV;
	float disH; 
	
	ra=fix_angle((data->player->pa)+30);//ray set back 30 degrees
	
	for (r=0; r<60; r++) {
		//---Vertical--- 
		dof=0;
		side=0;
		disV=100000;
		float Tan=tan(degrees_to_radians(ra));
		if (cos(degrees_to_radians(ra))> 0.001) {
			rx=(((int)(data->player->px)>>6)<<6)+64;
			ry=((data->player->px)-rx)*Tan+(data->player->py);
			xo= 64;
			yo=-xo*Tan;
		}//looking left
		else if (cos(degrees_to_radians(ra))<-0.001) {
			rx=(((int)(data->player->px)>>6)<<6) -0.0001;
			ry=((data->player->px)-rx)*Tan+(data->player->py);
			xo=-64;
			yo=-xo*Tan;
		}//looking right
		else {
			rx=(data->player->px);
			ry=(data->player->py);
			dof=8;
		}//looking up or down. no hit  

		while(dof<8) { 
			mx=(int)(rx)>>6;
			my=(int)(ry)>>6;
			mp=my*mapX+mx;

			if (mp>0 && mp<mapX*mapY && map[(int)mp]==1) {
				dof=8;
				disV=cos(degrees_to_radians(ra))*(rx-(data->player->px))-sin(degrees_to_radians(ra))*(ry-(data->player->py));
			}//hit
			else {
				rx+=xo;
				ry+=yo;
				dof+=1;
			}//check next horizontal
		} 
		vx=rx;
		vy=ry;

		//---Horizontal---
		dof=0;
		disH=100000;
		Tan=1.0/Tan;

		if (sin(degrees_to_radians(ra))> 0.001) {
				ry=(((int)(data->player->py)>>6)<<6) -0.0001;
				rx=((data->player->py)-ry)*Tan+(data->player->px);
				yo=-64;
				xo=-yo*Tan;
		}//looking up 
		else if (sin(degrees_to_radians(ra))<-0.001) {
			ry=(((int)(data->player->py)>>6)<<6)+64;
			     rx=((data->player->py)-ry)*Tan+(data->player->px);
			yo= 64;
			xo=-yo*Tan;
		}//looking down
		else {
			rx=(data->player->px);
			ry=(data->player->py);
			dof=8;
		}//looking straight left or right
	
		while(dof<8) { 
			mx=(int)(rx)>>6;
			my=(int)(ry)>>6;
			mp=my*mapX+mx;
			if (mp>0 && mp<mapX*mapY && map[(int)mp]==1) {
				dof=8;
				disH=cos(degrees_to_radians(ra))*(rx-(data->player->px))-sin(degrees_to_radians(ra))*(ry-(data->player->py));
			}//hit
			else {
				rx+=xo;
				ry+=yo;
				dof+=1;
			}//check next horizontal
		} 

		// glColor3f(0,0.8,0);
		data->color = green;
		if (disV<disH) {
			rx=vx;
			ry=vy;
			disH=disV;
			// glColor3f(0,0.6,0);
			data->color = green;
		}//horizontal hit first
		// glLineWidth(2);
		// // glBegin(GL_LINES);
		// glVertex2i(px,py);
		// glVertex2i(rx,ry);
		// glEnd();//draw 2D ray
		int px = data->player->px;
		int py = data->player->py;
		data->bres->x1 = px;
		data->bres->y1 = py;
		data->bres->x2 = rx;
		data->bres->y2 = ry;
		data->bres->color = data->color;
		bres_draw_line(data);
		// printf("rx:%f, ry:%f\n", rx, ry);
		int ca=fix_angle((data->player->pa)-ra);
		disH=disH*cos(degrees_to_radians(ca));
		//fix fisheye 
		int lineH = (mapS*320)/(disH);
		if (lineH>320) {
			lineH=320;
		}//line height and limit
		int lineOff = 160 - (lineH>>1);//line offset
		// glLineWidth(8);
		// // glBegin(GL_LINES);
		// glVertex2i(r*8+530,lineOff);
		// glVertex2i(r*8+530,lineOff+lineH);
		// glEnd();//draw vertical wall
		data->bres->x1 = r*8+530;
		data->bres->y1 = lineOff;
		data->bres->x2 = r*8+530;
		data->bres->y2 = lineOff+lineH;
		data->bres->color = blue;
		bres_draw_line(data);
		ra=fix_angle(ra-1);
		//go to next ray
	}
}
