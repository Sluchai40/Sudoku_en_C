NAME			:= ./sudoku

SRCS_DIR			:= .

SRCS_RAW			:= mainu.c	\
					case_vide.c \
					solver_Sudoku.c \
					strsplit.c	\
					test_chiffre.c	\
					shuffle_range.c \
					remove.c	\
					gridass.c 	\
					idiot_solver.c 	\
					celib_nu.c 	\
					celib_cache.c 	\
					segment.c 	\

SRCS				:= $(SRCS_RAW:%.c=$(SRCS_DIR)/%.c)

			
OBJS			:= $(SRCS:.c=.o)

CC			:= gcc

CFLAGS			:= -Wall -Wextra

RM			:= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

test: $(NAME)
	$(NAME) sudokufile/sudoku_grill

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all