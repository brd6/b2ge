DEBUG_CFLAGS	=	-g3 -DDEBUG

RELEASE_CFLAGS	=	-W -Wall -Wextra -Werror

CXX 		= 	g++

RM		= 	rm -f

NAME		=	example

SRCS		= 	main.cpp \

OBJS		= 	$(SRCS:.cpp=.o)

CXXFLAGS 	+= 	-std=c++14
CXXFLAGS	+=	-I./lib

LDFLAGS 	+= 	-L./lib -lb2ge

all: CXXFLAGS+=$(RELEASE_CFLAGS)
all: $(NAME)

debug: CXXFLAGS+=$(DEBUG_CFLAGS)
debug : $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean, re, all, fclean
