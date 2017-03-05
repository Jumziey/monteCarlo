#include <unistd.h>
#include <g2.h>
#include <g2_X11.h>

#include "ising.h"

int winID;

void visInit() {
	int id;
	
	id = g2_open_X11(1024, 1024);
	g2_set_auto_flush(id, 0);		// Disable auto flush
	g2_pen(id,0);
	g2_filled_rectangle(id,0,0,1024,1024);
	
	winID = id;
}

void visClose() {
	g2_close(winID);
}

void visualize(int size, int* spin) {
	int id, i, j;
  int pix;
  int col = 1;
  double x1,x2,x3;
  double y1,y2,y3;
  double tx1,tx2,tx3;
  double ty1,ty2,ty3;
  double rx1,rx2,rx3;
  double ry1,ry2,ry3;
  
  id = winID;
  g2_pen(id,0);
	g2_filled_rectangle(id,0,0,1024,1024);
	
  pix = 1024/size;
	for(i=0; i<size; i++) {
		for(j=0; j<size; j++) {
			
			//Rectangle to draw on
			x1 = j*pix; y1 = (size-1-i)*pix;
			x2 = (j+1)*pix; y2 = (size-i)*pix;
			
			if(spin[i*size+j]==1) {//Up Arrow
				g2_pen(id,7);
				//triangle
				tx1 = x1+pix/4; ty1 = y1+pix/2;
				tx2 = x2-pix/4; ty2 = y1+pix/2;
				tx3 = x1+pix/2; ty3 = y2;
			
				//base
				rx1 = x2-pix*10/21; ry1 = y1+pix/2;
				rx2 = x1+pix*10/21; ry2=y1;
			
			} else {//Down Arrow
				g2_pen(id,3);
				//triangle
				tx1 = x1+pix/2; ty1 = y1;
				tx2 = x2-pix/4; ty2 = y1+pix/2;
				tx3 = x1+pix/4; ty3 = y1+pix/2;
			
				//base
				rx1 = x1+pix*10/21; ry1 = y1+pix/2;
				rx2 = x2-pix*10/21; ry2 = y2;
			}
			g2_filled_triangle(id,tx1,ty1,tx2,ty2,tx3,ty3);
			g2_filled_rectangle(id,rx1,ry1,rx2,ry2);
		}
	}
	g2_flush(id);
  sleep(1);
}
