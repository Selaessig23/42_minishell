
#declarations
#variables
CUR_DIR = $(shell pwd)
LIBFT_PATH = $(CUR_DIR)/libft
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -g -Iinclude -Isrcs -Ireadline
RLFLAG = -lreadline -lncurses -ltinfo

#sources
#VPATH = sources:include
#INCLUDES = minishell.h
SRCS =	main.c \
		ascii_graphic.c \
		error_handling.c \
		lexer/ft_split_quotes.c \
		lexer/lexer.c \
		lexer/lexer_cleaner.c \
		lexer/extra_prompt.c \
		lexer/str_spaces_trimer.c \
		tokenizer/tokenizer.c \
		tokenizer/tokenizer_utils.c \
		tokenizer/tokenizer_strings.c \
		tokenizer/tokenizer_operators.c \
		syntax_analyzer/syntax.c \
		syntax_analyzer/syntaxerrors.c \
		testprints.c \
		t_big_and_env_copy.c \
		expander/expander.c \
		expander/expander_quotes.c \
		expander/expander_env.c \
		expander/expander_env_yes.c \
		expander/expander_env_no.c \
		expander/expander_exit.c \
		expander/expander_pid.c \
		expander/expander_utils.c \
		expander/expander_q.c \
		command_creation/command_list.c \
		command_creation/command_utils.c \
		command_creation/command_reader.c \
		command_creation/file_creator.c \
		command_creation/_check_def_env_paths.c \
		builtins/builtin_check.c \
		builtins/exit.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/pwd.c \
		builtins/cd.c \
		builtins/export_1.c \
		builtins/export_2.c \
		builtins/export_sort.c \
		builtins/unset.c \
		heredoc.c \
		builtins/help.c \
		signals.c \
		execution/execute_0.c \
		execution/execute_1.c \
		execution/execute_2.c \
		execution/minishell_executer.c \
		execution/execute_built-ins.c \
		utils_strings/utils_string.c
#		inputcheck.c \
#		exe.c \
#		utils.c
#		image_creation.c \
#		hooks.c \
#		utils.c

#libraries
#add pathes of lib to cflags to find headers easily
LIBFT = libft.a
LIBFT_LIBRARY = $(CUR_DIR)/libft/libft.a
LIBFT_CREATE = libft.a
CFLAGS += -Ilibft

#variable substitution		
OBJS = $(SRCS:%.c=obj/%.o)

#This target depends on $(NAME), making it the default target to build everything.
all: $(NAME)

#to create a program:
$(NAME): $(OBJS) $(LIBFT_LIBRARY)
	$(CC) $(CFLAGS) $^ -o $@ $(RLFLAG)
	@echo -- prog created, try it by using ./minishell

# %.o rule will compile one .c file to its correspondig object (.o) file: without this rule it would not update correctly
# automatic variables: $@ = the file name of the target of the rule, $< = the name of the prerequisite
# -p (parent option): This option tells mkdir to create the directory and any necessary parent directories if they do not already exist. It also suppresses error messages if the directory already exists.
# $(@D) is a special variable: if target is a file located in some directory, $(@D) will extract just the directory path from the target, 
# otherwise If the target doesn’t include a directory (i.e., it's in the current directory), $(@D) expands to . (representing the current directory).
$(OBJS): obj%.o : srcs%.c 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

#The -C option is used to change the directory to the specified path before executing make. In this context, it ensures that make operates in the subfolder, not the current directory.
$(LIBFT_LIBRARY): $(LIBFT_CREATE)
	make -C $(LIBFT_PATH)

#!important to note: if the program can't find any of the dependencies it will do all
#I have two options: use timestamp and compare
$(LIBFT_CREATE):
#	make -C $(LIBFT_PATH)
#	@echo -- UPDATE

#clean: This target removes the object files ($(OFILES)).
#f: "force" -->prevents the command from prompting for confirmation
clean:
	@rm -rf obj
	@make -C $(LIBFT_PATH) clean
	@echo -- Deleting All .o

# fclean: this target depends on clean. Once all object files are deleted, this rule will delete the created executable / the compiled binary ('$(NAME)') 
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@echo -- Deleting executables

#This target depends on fclean and all, effectively cleaning and rebuilding the project.
re: fclean all

#This line specifies that the listed targets (all, clean, fclean, re) are phony targets, meaning they don't represent actual files, and should always be considered out-of-date, triggering their recipes to be executed.
.PHONY: all clean fclean re
