TARGET = my_bsq
OBJ    = main.c p_bsq.c s_bsq.c f_bsq.c
CFLAGS = -Wall -Werror -Wextra
CC     = gcc

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
clean:
	rm -f *.o
fclean: clean
	rm -f $(TARGET)
re: fclean all
