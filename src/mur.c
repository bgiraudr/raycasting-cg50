#include <gint/display.h>
#include <openlibm.h>

double record = 1000000;
int recx = 0;
int recy = 0;
double recu = 0; 
	
void create_wall(int x1, int y1, int x2, int y2) {
	dline(x1,y1,x2,y2,C_RED);
	dline(x1-1,y1,x2-1,y2,C_RED);
	dline(x1+1,y1,x2+1,y2,C_RED);
}

void draw_ray(int px, int py) {
	int inx = px + recu*(recx-px);
	int iny = py + recu*(recy-py);
	dline(px, py, inx, iny, C_WHITE);
	record = 1000000;
}

char check_wall(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	double dist;
	
	double den = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
	
	if(den == 0) {
		return 0;
	} else {
		//Line line intersection
		double t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4)); // =t*den
		double u = -((x1-x2)*(y1-y3)-(y1-y2)*(x1-x3)); // =u*den

		if(den<0) {
			t*=-1;
			u*=-1;
			den*=-1;
		}

		if(t > 0.0 && t < den && u > 0.0) {
			double ux = u*(x4-x3);
			double uy = u*(y3-y3);
			dist = (ux*ux + uy*uy) / (den * den);
			if(dist<record) {
				record = dist;
				recx = x4;
				recy = y4;
				recu = u/den;
			}
		}
	}
	return 1;
}
