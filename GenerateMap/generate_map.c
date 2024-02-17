#include "my_bsq.h"
#include <time.h>
#include <stdbool.h>
#include <sys/stat.h>

size_t my_strlen(char *string)
{
    char *end = string;
    while (*end++ != '\0') {};
    return end-string-1;
}

void my_strcpy(char *src, char *dst)
{
    while (*src != '\0') {
        *dst++ = *src++;
    }
    *dst = '\0';
}

char** malloc_argv(char* string)
{
    while (*string == ' ') string++;

    /* Count number of arguments */ 
    int argument_count = 0;
    for (char last = ' '; *string != '\n'; last = *string++)
    {
        if (*string != ' ') {
            if (last == ' ') {
                argument_count++;
            }
            if (*string == '\"') {
                while (*++string != '\"' && *string != '\n') {};
                if (*string == '\n') {
                    return NULL;
                }
            }
        }
    }
    return malloc((argument_count+1)*sizeof(char*));
}

char* next_arg(char** current_offset) 
{
    /* Find argument */        
    char* stdin = *current_offset;
    while (*stdin == ' ') *stdin++ = '\0';
    if (*stdin == '\n') {
        *stdin = '\0';
        return NULL;
    }

    /* Move offset to next arg */
    char* argument = stdin;
    while (*stdin != ' ' && *stdin != '\n') {
        if (*stdin == '\"') {
            while (*++stdin != '\"' && *stdin != '\n') {};
        }
        stdin++;
    }
    *current_offset = stdin;
    return argument;
}

void free_input(char **argv)
{
    free(*argv), free(argv);
}

char** process_input(char *buffer)
{
    char **argv = malloc_argv(buffer);
    if (argv == NULL) {
        free(buffer);
        return NULL;
    }

    char *offset = buffer;
    for (int i = 0; (argv[i++] = next_arg(&offset)); ) {};
    if (*argv != NULL) {
        my_strcpy(*argv, buffer);
        *argv = buffer;
    } else {
        free(buffer), free(argv);
        return NULL;
    }
    return argv;  
}

char **request_input(int size)
{
    char *buffer = malloc(size*sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }
    int readsize = read(STDIN_FILENO, buffer, size); 
    if (buffer[readsize-1] != '\n') {
        if (readsize == size) {
            while (read(STDIN_FILENO, buffer, size) == size) {};
            free(buffer);
            return NULL;
        } else {
            printf("\n");
            exit(EXIT_SUCCESS);  
        }
    }
    return process_input(buffer);
}

int argument_count(char **argv)
{
    char **count = argv;
    while (*count++ != NULL) {};
    return count-argv-1;
}

char *malloc_strcpy(char *string)
{
    /* Count string length.  */
    char *end = string;
    while (*end++ != '\0') {};
    
    /* Malloc and copy string.  */
    int size = end-string;
    if ((string = malloc(size)) != NULL) {
        for (string += size; size--; ) {
            *--string = *--end;
        }
    }
    return string;
}

char *malloc_itoa(int integer) 
{
    if (integer == 0) {
        return malloc_strcpy("0");
    }    

    char string[12];
    char *fill = string;
    bool significant = false;
    if (integer < 0) {
        integer *= -1;
        *fill++ = '-';
    }
    for (int power, nth, iteration = 9; (nth = iteration--); ) {
        for (power = 1; --nth; power *= 10) {};
        for (*fill = '0'; power <= integer; (*fill)++) {
            integer -= power;
        }
        if (*fill != '0' || significant) {
            significant = true;
            fill++;
        }
    }
    *fill = '\0';
    return malloc_strcpy(string);
}

int write_integer(int fd, int integer) 
{
    char *string = malloc_itoa(integer);
    int length = my_strlen(string);
    write(fd, string, length);
    free(string);
    return length;
}

int write_string(int fd, char *string)
{
    if (string == NULL) {
        string = "(null)";
    }
    int length = my_strlen(string);
    write(fd, string, length);
    return length;
}

bool wrong_number(char *number)
{
    if (*number == '-') {
        return false;
    }
    char *length = number;
    while (*number != '\0') {
        if (*number < '0' || *number++ > '9') {
            return (*number != '\0');
        }
    }
    return number-length > 9;
}

char **get_input()
{
    char **input;
    for ( ; true; printf("Wrong input!\n")) {
        write(STDIN_FILENO, "> ", 2);
        if ((input = request_input(100)) == NULL) {
        
        } else if (argument_count(input) != 3) {
            free_input(input);
        } else if (wrong_number(input[0]) || wrong_number(input[1])
                   || wrong_number(input[2])) {
            free_input(input);
        } else if (atoi(input[2]) > 100) {
            free_input(input);
        } else {
            break;
        }
    }
    printf("OK\n");
    return input;
}

char *stradd(char *dst, char *src)
{
    while ((*dst++ = *src++) != '\0') {};
    return dst-1;
}

void generate_map()
{
    // part 1: get inputs
    char **argv = get_input();
    int x       = atoi(argv[0]);
    int y       = atoi(argv[1]);
    int density = atoi(argv[2]);

    // part 2: make file
    int fd;
    char filename[256];
    mkdir("map", 00755);
    char *add = stradd(stradd(stradd(stradd(filename, "map/"), argv[0]), "x"), argv[1]);
    while ((fd = open(filename, O_RDONLY)) != -1) {
        add = stradd(add, "+");
        close(fd);
    }
    fd = open(filename, O_CREAT | O_WRONLY, 00644);

    // part 3
    char    buffer[x];
    char    *ptr;
    write_string(fd, argv[1]);
    write(fd, "\n", 1);
    srand(time(NULL));

    float total = x*y;
    float quota = (total*density)/100;
    float chance = (quota*100)/total;
    while (ptr = buffer, y--)
    {
        for (int i = x; i--; )
        {
            if (rand()%100 < chance) {
                *ptr++ = 'o';
                chance = (--quota*100)/--total;
            } else {
                *ptr++ = '.';
                chance = (quota*100)/--total;
            }
        }
        write(fd, buffer, x);
        write(fd, "\n", 1);
    }
    free_input(argv);
}