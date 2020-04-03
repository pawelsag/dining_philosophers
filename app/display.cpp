#include "display.hpp"
#include<cstring>
using namespace std;

namespace so2
{

    static void curs_print(WINDOW *win, int starty, int startx, int width,const char *string);

    void init_ncurses()
    {
        initscr();			/* Start curses mode 		*/
        if(has_colors() == FALSE)
        {	endwin();
            printf("Your terminal does not support color\n");
            exit(1);
        }

        start_color();			/* Start color 			*/
        init_pair(RED, COLOR_RED, COLOR_BLACK);
        init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    }

    void print_red(int y, int x, const std::string& text)
    {
        attron(COLOR_PAIR(RED));
        curs_print(stdscr, y, x, 0, text.c_str());
        attroff(COLOR_PAIR(RED));
    }

    void print_green(int y, int x, const std::string& text)
    {
     
        attron(COLOR_PAIR(GREEN));
        curs_print(stdscr, y, x, 0, text.c_str());
        attroff(COLOR_PAIR(GREEN));
    }

    static void curs_print(WINDOW *win, int starty, int startx, int width,const char *string)
    {	int length, x, y;
        float temp;

        if(win == NULL)
            win = stdscr;
        getyx(win, y, x);
        if(startx != 0)
            x = startx;
        if(starty != 0)
            y = starty;
        if(width == 0)
            width = 80;

        length = strlen(string);
        temp = (width - length)/ 2;
        x = startx + (int)temp;
        mvwprintw(win, y, x, "%s", string);
        refresh();
    }
}
