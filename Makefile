# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 09:59:44 by mstracke          #+#    #+#              #
#    Updated: 2024/08/05 18:25:59 by mpeshko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#declarations
#variables
CUR_DIR = $(shell pwd)
LIBFT_PATH = $(CUR_DIR)/libft
NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -Iinclude -Isrcs -Ireadline
RLFLAG = -lreadline

#sources
#VPATH = sources:include
#INCLUDES = minishell.h
SRCS =	main.c \
		error_handling.c \
		ft_split_quotes.c \
		lexer.c \
		extra_prompt.c \
		str_spaces_trimer.c
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

#%.o rule will compile one .c file to its correspondig object (.o) file: without this rule it would not update correctly
#automatic variables: $@ = the file name of the target of the rule, $< = the name of the prerequisite
#-p (parent option): This option tells mkdir to create the directory and any necessary parent directories if they do not already exist. It also suppresses error messages if the directory already exists.
$(OBJS): obj/%.o : srcs/%.c 
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@ && printf "Compiling: $(notdir $<)"

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
