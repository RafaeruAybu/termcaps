#include <stdio.h>		//simple output
#include <sys/ioctl.h>	//termcaps
#include <signal.h>		//to get signals
#include <unistd.h>		//for sleep()
#include "tc.h"			//some defines(colors etc...)

/*
*	Get size of window.
*/
void tc_get_cols_rows(int *cols, int *rows)
{
	struct winsize size;
	ioctl(1, TIOCGWINSZ, &size);
	*cols = size.ws_col;
	*rows = size.ws_row;
}

/*
*	Change the alligment of the txt.
*/
void change_text_allignment()
{
	int cols = 0;
	int rows = 0;

	tc_get_cols_rows(&cols, &rows);
	tc_clear_screen();
	tc_move_cursor(cols/2, rows/2);
}

/*
*	Draws the buff to the terminal. Used as a callback function.
*/
void draw_the_buff()
{
	char *buf = "Hello world!";
	change_text_allignment();
	printf("%s%s%s\n", TC_BG_YEL, buf, TC_BG_NRM);
}

int main()
{
	draw_the_buff();
	signal(SIGWINCH, &draw_the_buff);
	while (1)
	{
		sleep(1);
	}
	return 0;
}

