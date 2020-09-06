//
//  kb_helper.h
//  SnakeCpp
//
//  Created by mac on 01/09/2020.
//  Copyright © 2020 mac. All rights reserved.
//

#ifndef kb_helper_h
#define kb_helper_h

#ifdef _WIN32 // WINDOWS OS ====================================================
#include <windows.h>
#include <conio.h>

void delay_ms(int milisec) { Sleep(milisec); }
void clear_src(void) { system("cls"); }
int  __kbhit(void) { return kbhit(); }
char __getch(void) { return getch(); }


#else // NOT WINDOWS OS ========================================================

/** Remake some funtions of windows' <conio.h> for *Nix system */
#include <iostream>
#include <sys/select.h>
#include <unistd.h>
#include <termios.h>

void delay_ms(int milisec) { usleep(useconds_t(milisec * 1000)); }
void clear_src(void) { system("clear"); }

/// replicate kbhit() from windows' <conio.h>
int kbhit(void) {
    struct timeval tv;
    fd_set read_fd;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);
    if (select(1, &read_fd, NULL, NULL, &tv) == -1) return 0;
    if (FD_ISSET(0, &read_fd)) return 1;
    return 0;
}

/// replicate kbhit() from windows' <conio.h>
char getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int  __kbhit(void) { return kbhit(); }
char __getch(void) { return getch(); }

#endif


#endif /* kb_helper_h */
