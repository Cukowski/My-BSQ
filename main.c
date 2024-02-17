#include "my_bsq.h"

int main(int argc, char **argv)
{
    if (argc >= 3) {
        return EXIT_FAILURE;
    }
    if (argc <= 1) {
        printf("Usage: ./my_bsq [map]\n");
    } 

    int size = get_size(argv[1]);

    find_biggest_square(argv[1], size, size);

    return 0;
}
