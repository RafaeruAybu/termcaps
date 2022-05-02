#include <stdio.h>		//simple output
#include <sys/ioctl.h>	//to use io terminal defines
#include <signal.h>		//to get signals
#include <unistd.h>		//for sleep()
#include <termios.h>	//to control the terminal
#include "tc.h"			//some defines(colors etc...)

//defines
void init_programm();
void tc_get_cols_rows(int *cols, int *rows);
void change_text_allignment();
void hide_cursor();
void show_cursor();
void draw_the_buff();
void tc_echo_off();
void tc_echo_on();
void tc_canon_off();
void tc_canon_on();
void exit_programm();

//global var
int f_exit = 0;

int main()
{
	init_programm();
	draw_the_buff();
	while (!f_exit)
	{
		sleep(1);
	}
	return 0;
}

void init_programm()
{
	signal(SIGWINCH, &draw_the_buff);
	signal(SIGINT, &exit_programm);
	tc_echo_off();
	hide_cursor();
}

/*
*	Set cursor and exits.
*/
void exit_programm()
{
	tc_echo_on();
	show_cursor();
	f_exit = 1;
}

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

void hide_cursor()
{
	printf("%s", "\e[?25l");
}

void show_cursor()
{
	printf("%s", "\e[?25h");
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

void tc_echo_off()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag &= ~ECHO;
	tcsetattr(1, TCSANOW, &term);
}

void tc_echo_on()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag |= ECHO;
	tcsetattr(1, TCSANOW, &term);
}

/*
*	For more info read termios.h(ICANON)
*/
void tc_canon_off()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag &= ~ICANON;
	tcsetattr(1, TCSANOW, &term);
}

void tc_canon_on()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag |= ICANON;
	tcsetattr(1, TCSANOW, &term);
}

