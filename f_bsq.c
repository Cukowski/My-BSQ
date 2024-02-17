#include "my_bsq.h"

int check_fd(char *filename, int X, int Y);
int preprocessing(int fd, char *line, int line_length, char *parser, short *square_size, short *start, int X);
int processing(int fd, char *line, int line_length, char *parser, short *square_size, short *start, short *values,int X, int Y, int* largest_found, int* coordinateX, int* coordinateY);
int find_biggest_square(char *filename, int X, int Y);
int process(char *line, char *parser, short *square_size, int Y, int *largest_found, int *coordinateX, int *coordinateY, int iteration);

int check_fd(char *filename, int X, int Y)
{
    int fd = open(filename, O_RDONLY);
    if ((Y = process_firstline(fd)) == -1) {
        return -1;
    } else if ((X = process_secondline(fd)) <= 0) {
        return -1;
    }
    close(fd);

    fd = open(filename, O_RDONLY);
    
    return fd;
}

int preprocessing(int fd, char *line, int line_length, char *parser, short *square_size, short *start, int X)
{
    if (read(fd, line, line_length) != line_length || line[X] != '\n') {
        return -1;
    }
    line[X] = '\0';
    parser = line;
    square_size = start--;
    while (true) {
        switch (*parser++) {
            case '\0':
                break;
            case 'o':
                *square_size++ = 0;
                continue;
            case '.':
                *square_size++ = 1;
                continue;
            default:
                return -1;
        }
        break;
    }
    return 1;
}

int processing(int fd, char *line, int line_length, char *parser, short *square_size, short *start, short *values,int X, int Y, int* largest_found, int* coordinateX, int* coordinateY)
{

    for (int iteration = Y - 1; iteration--; )
    {
        // A. Process current lane
        if (read(fd, line, line_length) != line_length || line[X] != '\n') {
            printf("Wrong map!\n"); // invalid line size
            return -1;
        }
        line[X] = '\0';
        parser = line;
        square_size = start--;

        // Process
        if (process(line, parser, square_size, Y, largest_found, coordinateX, coordinateY, iteration) != 1)
            return -1;
        
    }
    if (read(fd, line, 1) != 0) {
        return -1;
    }
    free(line);
    free(values);
    
    return 1;
}

int process(char *line, char *parser, short *square_size, int Y, int *largest_found, int *coordinateX, int *coordinateY, int iteration){
    switch (*parser) {
        case 'o':
            *square_size++ = 0;
            break;
        case '.': 
            *square_size++ = 1;
            break;
        default:
            return -1;
    }
    while (true){
        switch (*++parser) {
            case '\0':
                break;
            case 'o':
                *square_size++ = 0;
                if (*parser == '.') {
                    *square_size++ = 1;
                    parser++;
                }
                continue;
            case '.':
                *square_size = (*square_size < square_size[-1])?
                    (*square_size < square_size[1])?
                        1 + *square_size: 
                        1 + square_size[1]:
                    (square_size[-1] < square_size[1])?
                        1 + square_size[-1]:
                        ((1 + square_size[1] > *largest_found)? 
                            (*largest_found = 1 + *square_size,
                            *coordinateX = parser - line + 1,
                            *coordinateY = Y - iteration): 0,
                        1 + square_size[1]);
                square_size++;
                continue;
            default:
                printf("Wrong map!\n"); // invalid char
                return -1;
        }
        break;
    }
    return 1;
}

int find_biggest_square(char *filename, int X, int Y)
{
    int fd = check_fd(filename, X, Y);
    process_firstline(fd);

    int line_length = X + 1;
    short *values = malloc((2*X) * sizeof(short));
    short *start = values+X;
    short *square_size = NULL;
    char *line = malloc((line_length) *sizeof(char));
    char *parser = line;

    if (preprocessing(fd, line, line_length, parser, square_size, start, X) != 1)
        return -1;

    int largest_found = 0;
    int coordinateX = 0;
    int coordinateY = 0;
    
    if (processing(fd, line, line_length, parser, square_size, start, values, X, Y, &largest_found, &coordinateX, &coordinateY) != 1)
        return -1;

    print_result(filename, largest_found, coordinateX, coordinateY, X, Y);

    return 0;
}