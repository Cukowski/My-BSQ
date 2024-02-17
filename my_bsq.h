#ifndef MY_BSQ_H
#define MY_BSQ_H

// Header files:
#include <stdio.h>      /* printf()                     */
#include <stdlib.h>     /* malloc(), free()             */
#include <unistd.h>     /* read(), write(), close()     */
#include <fcntl.h>      /* open()                       */

#include <stdbool.h>
#include <time.h>

/* Public Functions.  */

// p_bsq.c Functions
int process_firstline(int fd); 
int process_secondline(int fd);
void print_result(char *filename, int size, int coorX, int coorY, int sizeX, int sizeY);

// f_bsq.c Functions
int find_biggest_square(char *filename, int X, int Y);

// s_bsq.c Functions
int get_size(char *filename);


#endif