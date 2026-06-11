CXX = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
NAME = btc
SRC = main.cpp BitcoinExchange.cpp
SRC_DIR = .
SRCS=$(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

debug:
	g++ $(SRC) -o $(NAME) -g

.cpp.o:
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
