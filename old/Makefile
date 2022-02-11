# Source files directory
S		= srcs/
# Object files directory
O		= objs/
# Include files directory
I		= incs/ incs/testers/ incs/utils incs/iterators
# Dependency files directory
D		= deps/

# Name of your program
NAME	= ft_containers

# list of your source files
SRCS	= main.cpp \
		  regularTests/mapRegularTests.cpp regularTests/stackRegularTests.cpp \
		  regularTests/vectorRegularTests.cpp \
		  speedTests/mapSpeedTests.cpp speedTests/stackSpeedTests.cpp \
		  speedTests/vectorSpeedTests.cpp \
		  utilitaries.cpp

# Compiler
CC		= clang++
# Compiler flags
CFLAGS	+= -Wall -Wextra -g -std=c++98 # -g is for gdb
# Linker flags
LDFLAGS	=

# The rest is automatic

CFLAGS	+= $(addprefix -I,$I)

SRCS	:= $(addprefix $S,$(SRCS))
OBJS	:= $(SRCS:$S%=$O%.o)
DEPS	:= $(SRCS:$S%=$D%.d)
DFLAGS	= -MT $(@:$O%.o=$S%) -MMD -MP -MF $(@:$O%.o=$D%.d)

RM		= /bin/rm -rf

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)"
	$(CC) $^ -o $@

# Object directory generation
$O:
	@mkdir $O

# Dependency directory generation
$D:
	@mkdir $D

# Object files generation
$(OBJS): $O%.o:$S% | $O $D
	@mkdir -p $(@D)
	@mkdir -p $(@D:$O%=$D%)
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) $(DFLAGS) -c $(@:$O%.o=$S%) -o $@

.PHONY: clean
clean:
	@echo "Cleaning up..."
	@$(RM) $D $O

.PHONY: fclean
fclean: clean
	@echo "Everything!"
	@$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: run
run: $(NAME)
	./$(NAME)
