#include <gint/display.h>
#include <gint/keyboard.h>
#include <openlibm.h>
//#include <libprof.h>
#include <gint/std/stdlib.h>

#include "mur.h"

#define RAYON 400
#define NBWALL 5
#define PRECISION 6 //trace tout les x degrés un rayon

#define SPEED 4

int seed = 1;

int main(void)
{
	dclear(C_BLACK);
	int loop = 1;
	int player_x = 150, player_y = 100;
	
	char set_border = 1;
	
	int nbr_wall = NBWALL;
	if(set_border) nbr_wall += 4;
	int murs[nbr_wall][4];
	
	srand(seed);
	for (int i = 0; i < nbr_wall; i++)
	{
		for (int j = 0; j < 4; j+=2)
		{
			murs[i][j] = fabs(rand()%384);
			murs[i][j+1] = fabs(rand()%200);
		}
	}
	if(set_border) {
		murs[nbr_wall-1][0] = -1;
		murs[nbr_wall-1][1] = -1;
		murs[nbr_wall-1][2] = 400;
		murs[nbr_wall-1][3] = -1;
		
		murs[nbr_wall-2][0] = 400;
		murs[nbr_wall-2][1] = -1;
		murs[nbr_wall-2][2] = 400;
		murs[nbr_wall-2][3] = 250;
		
		murs[nbr_wall-3][0] = 400;
		murs[nbr_wall-3][1] = 250;
		murs[nbr_wall-3][2] = -1;
		murs[nbr_wall-3][3] = 250;
		
		murs[nbr_wall-4][0] = -2;
		murs[nbr_wall-4][1] = -2;
		murs[nbr_wall-4][2] = -2;
		murs[nbr_wall-4][3] = 250;
	}
	
	
	while(loop) {
		dclear(C_BLACK);
		clearevents();
		if(keydown(KEY_SHIFT)) {
			seed++;
			main();
		}
		if(keydown(KEY_EXIT)) {
			loop = 0;
			break;
		}
		if(keydown(KEY_RIGHT) && player_x+SPEED < 388) {
			player_x += SPEED;
		}
		else if(keydown(KEY_LEFT) && player_x-SPEED > 0) {
			player_x -= SPEED;
		}
		else if(keydown(KEY_UP) && player_y-SPEED > 0) {
			player_y -= SPEED;
		}
		else if(keydown(KEY_DOWN) && player_y+SPEED < 212) {
			player_y += SPEED;
		}
		for(int i = 0; i < nbr_wall; i++) {
			create_wall(murs[i][0], murs[i][1], murs[i][2], murs[i][3]);
		}
		for(int angle = 0; angle < 360; angle += PRECISION) {
			for(int i = 0; i < nbr_wall; i++) {
				//prof_t prof = prof_make();
				//prof_enter(prof);
				check_wall(murs[i][0], murs[i][1], murs[i][2], murs[i][3], player_x, player_y, (int)((player_x + RAYON ) * cos(angle)), (int)((player_y + RAYON) * sin(angle)));
				//prof_leave(prof);
				//uint32_t total_function_us = prof_time(prof);
				//dprint(10,10,C_RED, "%d", total_function_us);
				//prof_quit();
			}
			draw_ray(player_x, player_y);
		}
		dupdate();
	}
	return 1;
}
