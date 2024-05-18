##
## EPITECH PROJECT, 2024
## strace
## File description:
## Makefile
##

SRC	=	LowResFilter.cpp \
		../../../Src/Color.cpp

OBJ = $(patsubst Src/%.cpp,build/%.o,$(SRC))

NAME	=	lowresfilter.so

CPPFLAGS	=	-g -std=c++20 -I./../../../Includes -O3 -fPIC -fno-gnu-unique

all: build $(NAME)

build:
	mkdir -p build

$(NAME):	$(OBJ)
	g++ -shared $(OBJ) -o $(NAME) $(CPPFLAGS) -lconfig++
	mkdir -p ../../bin
	mv ./$(NAME) ../../bin/$(NAME)

%.o:	%.cpp
	g++ -c $< -o $@ $(CPPFLAGS)

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)
	rm -f ../../bin/$(NAME)

re: fclean all

.PHONY: all clean fclean re build
