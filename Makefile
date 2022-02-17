# Source files directory
S		= srcs/
# Object files directory
O		= objs/
# Include files directory
I		= incs/ incs/iterators incs/RBTree incs/utils
# Dependency files directory
D		= deps/

# Name of your program
NAME	= ft_containers

# list of your source files
SRCS	= main.cpp set_tests.cpp map_tests.cpp vector_tests.cpp stack_tests.cpp

# Compiler stuff
CC		= clang++
CFLAGS	+= -Wall -Wextra -g -std=c++98 # -g is for gdb
LDFLAGS	=

# Usage of cpputest, write YES to use
CPPUTEST	= YES

# The rest is automatic

ifeq ($(CPPUTEST), YES)
	CPPUTEST_HOME	 = $(HOME)/.brew/Cellar/cpputest/4.0
	CPPUTEST_HOME 	 = $(HOME)/Documents/42/cpputest
	CFLAGS			+= -I$(CPPUTEST_HOME)/include/
	CFLAGS			+= -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
	LDFLAGS			 = -L$(CPPUTEST_HOME)/lib/ -lCppUTest -lCppUTestExt
	LDFLAGS			 = -L$(CPPUTEST_HOME)/cpputest_build/lib/ -lCppUTest -lCppUTestExt
endif

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
	@$(CC) $^ -o $@ $(LDFLAGS)

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
re: fclean
	@$(MAKE) all

.PHONY: run
run: $(NAME)
	./$(NAME)
