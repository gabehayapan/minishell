NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =\
	./src/main.c\
	./src/env_var/env_var.c\
	./src/env_var/env_var_utils.c\
	./src/env_var/env_module/env_lookup.c\
	./src/env_var/init_env_list.c\
	./src/env_var/convert_to_envp.c\
	./src/builtin/cd.c\
	./src/builtin/cd_utils.c\
	./src/builtin/echo.c\
	./src/builtin/env.c\
	./src/builtin/export.c\
	./src/builtin/export_utils.c\
	./src/builtin/exit.c\
	./src/builtin/pwd.c\
	./src/builtin/unset.c\
	./src/builtin/terminal0142.c\
	./src/builtin/google.c\
	./src/execution/execution.c\
	./src/handle_input/handle_input.c\
	./src/handle_input/tokenizer/tokenizer.c\
	./src/handle_input/tokenizer/tokenizer_utils.c\
	./src/handle_input/tokenizer/tokenize_keywords.c\
	./src/handle_input/tokenizer/tokenize_quote.c\
	./src/handle_input/tokenizer/syntax_error.c\
	./src/handle_input/tokenizer/syntax_error_utils.c\
	./src/handle_input/tokenizer/ft_isspace.c\
	./src/handle_input/tokenizer/ft_realloc.c\
	./src/handle_input/parser/parser.c\
	./src/handle_input/parser/parser_utils.c\
	./src/handle_input/parser/shell_var.c\
	./src/handle_input/parser/init.c\
	./src/handle_input/parser/init_utils.c\
	./src/handle_input/parser/init_tokens.c\
	./src/handle_input/parser/free.c\
	./src/handle_input/parser/free_all.c\
	./src/handle_input/parser/counter.c\
	./src/handle_input/parser/get_redirect_file.c\
	./src/handle_input/parser/get_redirect_file_utils.c\
	./src/handle_input/parser/print_redirection_error.c\
	./src/handle_input/parser/expand_specials.c\
	./src/handle_input/parser/expand_specials_utils.c\
	./src/handle_input/parser/replace_command.c\
	./src/handle_input/parser/init_wildcard.c\
	./src/handle_input/parser/wildcard_retrieve.c\
	./src/handle_input/parser/wildcard_retrieve_utils.c\
	./src/handle_input/parser/handle_exit_status.c\
	./src/handle_input/parser/join_word.c\
	./src/handle_input/parser/get_command.c\
	./src/handle_input/parser/exec_nodes.c\
	./src/handle_input/parser/exec_ast.c\
	./src/handle_input/parser/add_path.c\
	./src/execution/execute.c\
	./src/execution/redirect.c\
	./src/execution/pipe.c\
	./src/execution/exec.c\
	./src/execution/fork.c\
	./src/execution/wait.c\
	./src/execution/helper.c\
	./src/signal/signal.c\

OBJ_DIR = obj/
OBJS =\
	./obj/main.o\
	./obj/env_var.o\
	./obj/env_var_utils.o\
	./obj/env_lookup.o\
	./obj/init_env_list.o\
	./obj/convert_to_envp.o\
	./obj/cd.o\
	./obj/cd_utils.o\
	./obj/echo.o\
	./obj/env.o\
	./obj/export.o\
	./obj/export_utils.o\
	./obj/exit.o\
	./obj/pwd.o\
	./obj/unset.o\
	./obj/terminal0142.o\
	./obj/google.o\
	./obj/execution.o\
	./obj/handle_input.o\
	./obj/tokenizer.o\
	./obj/tokenizer_utils.o\
	./obj/tokenize_keywords.o\
	./obj/tokenize_quote.o\
	./obj/syntax_error.o\
	./obj/syntax_error_utils.o\
	./obj/ft_isspace.o\
	./obj/ft_realloc.o\
	./obj/parser.o\
	./obj/parser_utils.o\
	./obj/shell_var.o\
	./obj/init.o\
	./obj/init_utils.o\
	./obj/init_tokens.o\
	./obj/free.o\
	./obj/free_all.o\
	./obj/counter.o\
	./obj/get_redirect_file.o\
	./obj/get_redirect_file_utils.o\
	./obj/print_redirection_error.o\
	./obj/expand_specials.o\
	./obj/expand_specials_utils.o\
	./obj/replace_command.o\
	./obj/init_wildcard.o\
	./obj/wildcard_retrieve.o\
	./obj/wildcard_retrieve_utils.o\
	./obj/handle_exit_status.o\
	./obj/join_word.o\
	./obj/get_command.o\
	./obj/exec_nodes.o\
	./obj/exec_ast.o\
	./obj/add_path.o\
	./obj/execute.o\
	./obj/redirect.o\
	./obj/pipe.o\
	./obj/exec.o\
	./obj/fork.o\
	./obj/wait.o\
	./obj/helper.o\
	./obj/signal.o\

HEADERS =\
	./include/minishell.h\
	./include/tokenizer.h\
	./include/parser.h\
	./include/env_var.h\
	./include/execution.h\
	./include/pipe.h\
	./include/builtin.h\

LIBFT_DIR = libft/
LIBFT = libft.a

vpath %.c ./src/ ./src/env_var/ ./src/env_var/export/ ./src/env_var/unset/ ./src/env_var/env_module/ ./src/handle_input/ ./src/handle_input/tokenizer/ ./src/handle_input/parser/ ./src/execution/ ./src/signal/ ./src/builtin/

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)$(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_DIR)$(LIBFT) -lcurses -lreadline

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

obj/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I./include/ -I./libft/header/

$(LIBFT_DIR)$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(LIBFT_DIR)$(LIBFT)

re: fclean all

.PHONY: all clean fclean re
