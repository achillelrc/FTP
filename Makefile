##
## EPITECH PROJECT, 2018
## nm/obj makefile
## File description:
## make
##

OB	=	server

CC	=	gcc
RM	=	rm -f
CFLAGS	+=	-W -Wall -Werror -Wextra -I ./srcs/

OB_SRCS	=	./srcs/server.c	\
		./srcs/comms1.c	\
		./srcs/comms2.c	\
		./srcs/comms3.c	\
		./srcs/updown.c

OB_OBJS	=	$(OB_SRCS:.c=.o)

all:	obj
	$(RM) $(OB_OBJS)

obj:	$(OB_OBJS)
	$(CC) $(OB_OBJS) -o $(OB) $(LDFLAG)

clean:
	$(RM) $(OB_OBJS)

fclean: clean
	$(RM) $(OB)

re: fclean all

.PHONY: all clean fclean re
