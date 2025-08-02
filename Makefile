
#declarations
#variables
CUR_DIR = $(shell pwd)
LIBFT_PATH = $(CUR_DIR)/libft
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -Isrcs -Ireadline
RLFLAG = -lreadline -lncurses -ltinfo

#sources
#VPATH = sources:include
#INCLUDES = minishell.h
SRCS =	main.c \
		01_pre_prompt/pre_prompt.c \
		error/error_and_exit.c \
		02_sig/signals.c \
		02_sig/signals_reset.c \
		03_pars/parsing_1.c \
		03_pars/parsing_2.c \
		03_pars/incomplete_input.c \
		04_lex/ft_split_ms.c \
		04_lex/ft_split_specials.c \
		04_lex/lexer_cleaner.c \
		04_lex/lexer_op_check.c \
		04_lex/lexer_str_utils.c \
		05_tokenizer/tokenizer.c \
		05_tokenizer/tokenizer_utils.c \
		05_tokenizer/tokenizer_strings.c \
		05_tokenizer/tokenizer_operators.c \
		05_tokenizer/tokenizer_qwords.c \
		06_syntax/syntax.c \
		06_syntax/syntaxerrors.c \
		07_expand/expander.c \
		07_expand/expander_quotes.c \
		07_expand/expander_env.c \
		07_expand/expander_env_yes.c \
		07_expand/expander_env_no.c \
		07_expand/expander_exit.c \
		07_expand/expander_utils.c \
		07_expand/expander_q.c \
		07_expand/llist_to_string.c \
		08_cmd_creat/command_list.c \
		08_cmd_creat/initiate_comm_infos.c \
		08_cmd_creat/handle_redirections.c \
		08_cmd_creat/file_creator.c \
		08_cmd_creat/heredoc.c \
		08_cmd_creat/create_argv_of_cmds.c \
		08_cmd_creat/command_utils.c \
		08_cmd_creat/check_def_env_paths.c \
		09_builtin/builtin_check.c \
		09_builtin/builtin_exit.c \
		09_builtin/exit.c \
		09_builtin/echo.c \
		09_builtin/env.c \
		09_builtin/pwd.c \
		09_builtin/cd.c \
		09_builtin/cd_error.c \
		09_builtin/export_1.c \
		09_builtin/export_2.c \
		09_builtin/export_3.c \
		09_builtin/export_sort.c \
		09_builtin/unset.c \
		09_builtin/help.c \
		10_exec/command_reader_01.c \
		10_exec/command_reader_02.c \
		10_exec/command_reader_print_err_01.c \
		10_exec/command_reader_print_err_02.c \
		10_exec/exe_binary.c \
		10_exec/exe_built-ins.c \
		10_exec/exe_binary_child_0.c \
		10_exec/exe_binary_child_1.c \
		10_exec/exe_child_fd_setup_cleanup.c \
		10_exec/minishell_executer.c \
		10_exec/exe_error_handling.c \
		10_exec/exe_utils.c \
		utils_strings/utils_string.c \
		utils_binary_path/binary_path.c \
		free/free.c

#test_and_debug/test_and_debug.c
#test_and_debug/testprints.c

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
