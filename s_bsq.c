#include "my_bsq.h"

// First line value is size
int get_size(char *filename) 
{
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        printf("Error opening the file");
        return -1;
    }

    // Read the first line from the file
    char buffer[256];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));

    close(fd);

    // check for errors
    if (bytesRead == -1) {
        printf("Error reading from file");
        return -1;
    }

    buffer[bytesRead] = '\0';

    int first_line_val = atoi(buffer);

    return first_line_val; 
}
