TARGET := sudoku
CC := gcc

SRCS_FOLDER := src
INCLUDE_FOLDER := include
PREREQUISITES_FOLDER := prerequisites
OBJS_FOLDER := objs
BIN_FOLDER := .

SDL_INCLUDE := -I./include

CFLAGS := -Wall -Wextra -flto -O3 -I$(INCLUDE_FOLDER) -I$(PREREQUISITES_FOLDER) -I$(SDL_INCLUDE) -MMD
LDFLAGS := -L./lib/

SRCS_RAW := mainu.c	\
			case_vide.c 	\
			celib_cache.c 	\
			celib_nu.c 	\
			gridass.c 	\
			idiot_solver.c 	\
			mainu.c 	\
			remove.c 	\
			segment_2.c 	\
			segment.c 	\
			shuffle_range.c 	\
			solver_Sudoku.c 	\
			strsplit.c 	\
			test_chiffre.c 	\
			graphics_init.c 	\
			init_grid_surface.c 	\
			police.c 	\

SRCS := $(addprefix $(SRCS_FOLDER)/, $(SRCS_RAW))
OBJS := $(SRCS:$(SRCS_FOLDER)/%.c=$(OBJS_FOLDER)/%.o)
DEPS := $(OBJS:.o=.d)
PREREQUISITES := $(wildcard $(PREREQUISITES_FOLDER)/*.c)

.PHONY: all clean re fclean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN_FOLDER)/$@ $^ -lSDL2 -lSDL2_ttf

$(OBJS_FOLDER)/%.o: $(SRCS_FOLDER)/%.c | $(OBJS_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MF $(@:.o=.d)

-include $(DEPS)

$(OBJS_FOLDER):
	mkdir -p $(OBJS_FOLDER)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(BIN_FOLDER)/$(TARGET)

re: fclean all

test: all
	$(BIN_FOLDER)/$(TARGET) sudoku_grill