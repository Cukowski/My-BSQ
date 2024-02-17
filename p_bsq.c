#include "my_bsq.h"

int process_firstline(int fd)
{
    char buffer;
    int integer = 0;
    int maxlength = 10;
    while (maxlength-- && read(fd, &buffer, 1) != 0) {
        switch (buffer) {
            case '\n':
                break;
            case '0':
                if (integer == 0) {
                    return -1;
                }
                // fallthrough
            case '1': case '2': case '3':
            case '4': case '5': case '6':
            case '7': case '8': case '9':
                integer = (integer*10)+(buffer-'0');
                continue;
            default:
                return -1;
        }
        break;
    }
    return (maxlength != 0)? integer : -1;
}

#define BUFSIZE 1000
int process_secondline(int fd)
{
    char buffer[BUFSIZE];
    int i;
    int count = 0;
    char *parser;
    while (read(fd, buffer, BUFSIZE) != 0) {
        for (i = BUFSIZE, parser = buffer; i-- && *parser++ != '\n'; ) {};
        if (parser[-1] == '\n') {
            return count + BUFSIZE - i - 1;
        } else {
            count += BUFSIZE;
        }
    }
    return 0;
}

void print_result(char *filename, int size, int coorX, int coorY, int sizeX, int sizeY)
{
    char buffer[sizeX + 1];
    int fd = open(filename, O_RDONLY);
    process_firstline(fd);

    sizeY = sizeY - coorY;
    coorX -= size;
    for (coorY -= size; coorY--; ) {
        read(fd, buffer, sizeX + 1);
        write(STDOUT_FILENO, buffer, sizeX + 1);
    }
    for (int print_square = size; print_square--; ) {
        read(fd, buffer, sizeX + 1);
        write(STDOUT_FILENO, buffer, coorX);
        for (int j = size; j--; ) write(STDOUT_FILENO, "x", 1);
        write(STDOUT_FILENO, buffer+coorX+size, sizeX-coorX-size+1);
    }
    while (sizeY--) {
        read(fd, buffer, sizeX + 1);
        write(STDOUT_FILENO, buffer, sizeX + 1);
    }
}