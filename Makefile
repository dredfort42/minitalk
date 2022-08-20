SRV		= server
CLN		= client
HDR		= minitalk.h
SRC_UTL	= utilities.c
SRC_SRV	= server.c server_processes.c
SRC_CLN	= client.c client_processes.c
OBJ_UTL	= $(patsubst %.c, %.o,$(SRC_UTL))
OBJ_SRV	= $(patsubst %.c, %.o,$(SRC_SRV))
OBJ_CLN	= $(patsubst %.c, %.o,$(SRC_CLN))

FLAGS	= -Wall -Wextra -Werror -D CHAR_SIZE=8
FLAGS_B = -Wall -Wextra -Werror -D CHAR_SIZE=32

all : $(SRV) $(CLN)

$(SRV) : $(OBJ_SRV) $(OBJ_UTL) $(HDR)
	gcc $(FLAGS) $(OBJ_SRV) $(OBJ_UTL) -I $(HDR) -o $@

$(CLN) : $(OBJ_CLN) $(OBJ_UTL) $(HDR)
	gcc $(FLAGS) $(OBJ_CLN) $(OBJ_UTL) -I $(HDR) -o $@

%.o : %.c
	gcc $(FLAGS) -I $(HDR) -c $< -o $@

bonus : fclean
	@make FLAGS="$(FLAGS_B)" all

clean :
	@rm -f $(OBJ_SRV) $(OBJ_CLN) $(OBJ_UTL)

fclean : clean
	@rm -f $(SRV) $(CLN)

re : fclean all

.PHONY : all clean fclean re bonus
