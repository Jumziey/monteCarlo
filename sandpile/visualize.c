#include <unistd.h>
#include <stdio.h>
#include <g2.h>
#include <g2_X11.h>

int winID;

void 
visInit() {
	int id;
	
	id = g2_open_X11(1024, 1024);
	g2_set_auto_flush(id, 0);		// Disable auto flush
	g2_pen(id,0);
	g2_filled_rectangle(id,0,0,1024,1024);
	
	winID = id;
}

void 
visClose() {
	g2_close(winID);
}

void visualize(int *m, int size) {
	int id, i, j;
  int pix;
  int col = 1;
  double x1,x2,x3;
  double y1,y2,y3;
  
  id = winID;
  g2_pen(id,0);
	g2_filled_rectangle(id,0,0,1024,1024);
	
  pix = 1024/size;
	for(i=0; i<size; i++) {
		for(j=0; j<size; j++) {
			//Rectangle to draw on
			x1 = j*pix; y1 = (size-1-i)*pix;
			x2 = (j+1)*pix; y2 = (size-i)*pix;
			switch(m[i*size+j]) {
				case 0:
					g2_pen(id,0);
					break;
				case 1:
					g2_pen(id,9);
					break;
				case 2:
					g2_pen(id,6);
					break;
				case 3:
					g2_pen(id,3);
					break;
				case 4:
					g2_pen(id,2);
					break;
				default:
					g2_pen(id,1);
			}
			g2_filled_rectangle(id,x1,y1,x2,y2);
		}
	}
	g2_flush(id);
  usleep(10);
}
