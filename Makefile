# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 17:48:01 by lcollong          #+#    #+#              #
#    Updated: 2025/02/25 09:50:24 by amonfret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
BUILTIN = builtins
ENV = env_expand
UTILS = utils
EXEC = execution
PARS = parsing
SIG = signals

OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

SRCS=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/$(ENV)/environment.c \
		$(SRC_DIR)/$(ENV)/env_list_utils.c \
		$(SRC_DIR)/$(ENV)/env_utils.c \
		$(SRC_DIR)/$(ENV)/expand.c \
		$(SRC_DIR)/$(ENV)/expand_utils.c \
		$(SRC_DIR)/$(ENV)/process_dollar.c \
		$(SRC_DIR)/$(ENV)/process_limiter.c \
		$(SRC_DIR)/$(PARS)/syntax.c \
		$(SRC_DIR)/$(PARS)/syntax_chev_pipe.c \
		$(SRC_DIR)/$(PARS)/tokens.c \
		$(SRC_DIR)/$(PARS)/token_handle_string.c \
		$(SRC_DIR)/$(PARS)/tokens_utils.c \
		$(SRC_DIR)/$(PARS)/store_token.c \
		$(SRC_DIR)/$(PARS)/parser.c \
		$(SRC_DIR)/$(PARS)/parser_utils.c \
		$(SRC_DIR)/$(PARS)/remove_quotes.c \
		$(SRC_DIR)/$(PARS)/remove_quotes_utils.c \
		$(SRC_DIR)/$(EXEC)/heredoc.c \
		$(SRC_DIR)/$(EXEC)/heredoc_utils.c \
		$(SRC_DIR)/$(EXEC)/redirection.c \
		$(SRC_DIR)/$(EXEC)/find_path.c \
		$(SRC_DIR)/$(EXEC)/execution.c \
		$(SRC_DIR)/$(EXEC)/execution_utils.c \
		$(SRC_DIR)/$(EXEC)/error.c \
		$(SRC_DIR)/$(EXEC)/pipes_utils.c \
		$(SRC_DIR)/$(EXEC)/pipes_cleanup.c \
		$(SRC_DIR)/$(UTILS)/utils_strings.c \
		$(SRC_DIR)/$(UTILS)/utils_characters.c \
		$(SRC_DIR)/$(UTILS)/utils_arrays.c \
		$(SRC_DIR)/$(UTILS)/utils_command_list.c \
		$(SRC_DIR)/$(UTILS)/utils_command_info.c \
		$(SRC_DIR)/$(UTILS)/utils_redirect_list.c \
		$(SRC_DIR)/$(UTILS)/utils_memory_management.c \
		$(SRC_DIR)/$(BUILTIN)/builtins.c \
		$(SRC_DIR)/$(BUILTIN)/env_exit.c \
		$(SRC_DIR)/$(BUILTIN)/export.c \
		$(SRC_DIR)/$(BUILTIN)/export_utils.c \
		$(SRC_DIR)/$(BUILTIN)/unset.c \
		$(SRC_DIR)/$(BUILTIN)/pwd_cd.c \
		$(SRC_DIR)/$(BUILTIN)/echo.c \
		$(SRC_DIR)/$(SIG)/signals.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR)
LIBFT = $(LIBFT_DIR)/libft.a
LIBRARIES = -L$(LIBFT_DIR) -lft

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBRARIES) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
