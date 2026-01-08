NAME_TOKENIZER = tokenizer_test
NAME_PARSER = parser_test
NAME_ENV_VAR = env_var_test

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_TOKENIZER =\
	../src/handle_input/tokenizer/tokenizer.c\
	../src/handle_input/tokenizer/tokenizer_utils.c\
	../src/handle_input/tokenizer/tokenize_quote.c\
	../src/handle_input/tokenizer/tokenize_keywords.c\
	../src/handle_input/tokenizer/syntax_error.c\
	../src/handle_input/tokenizer/ft_isspace.c\

SRCS_PARSER =\
	../src/handle_input/parser/parser.c\
	../src/handle_input/parser/parser_utils.c\
	../src/handle_input/parser/get_redirect_file.c\
	../src/handle_input/parser/get_command.c\
	../src/handle_input/parser/print_redirection_error.c\
	../src/handle_input/parser/exec_tree.c\
	../src/handle_input/parser/expand_specials.c\
	../src/env_var/env_var.c\
	../src/env_var/env_var_utils.c\
	../src/env_var/ft_getenv.c\
	../src/env_var/init_env_list.c\

SRCS_ENV_VAR =\
	../src/env_var/env_var.c\
	../src/env_var/env_var_utils.c\
	../src/env_var/init_env_list.c\

OBJS_TOKENIZER =\
	obj/tokenizer.o\
	obj/tokenizer_utils.o\
	obj/tokenize_quote.o\
	obj/tokenize_keywords.o\
	obj/syntax_error.o\
	obj/ft_isspace.o\

OBJS_PARSER =\
	obj/parser.o\
	obj/parser_utils.o\
	obj/get_redirect_file.o\
	obj/get_command.o\
	obj/print_redirection_error.o\
	obj/exec_tree.o\
	obj/expand_specials.o\
	obj/env_var.o\
	obj/env_var_utils.o\
	obj/ft_getenv.o\
	obj/init_env_list.o\

OBJS_ENV_VAR =\
	obj/env_var.o\
	obj/env_var_utils.o\
	obj/init_env_list.o\

LIBFT = ../libft/libft.a

vpath %.c ./ ../src/handle_input/tokenizer/ ../src/handle_input/parser/ ../src/env_var/

tokenizer: $(NAME_TOKENIZER)

$(NAME_TOKENIZER): $(LIBFT) $(OBJS_TOKENIZER) obj/main_tokenizer.o
	$(CC) $(CFLAGS) -o $(NAME_TOKENIZER) obj/main_tokenizer.o $(OBJS_TOKENIZER) $(LIBFT) -lreadline

parser: $(NAME_PARSER)

$(NAME_PARSER): $(LIBFT) $(OBJS_PARSER) $(OBJS_TOKENIZER) obj/main_parser.o
	$(CC) $(CFLAGS) -o $(NAME_PARSER) obj/main_parser.o $(OBJS_PARSER) $(OBJS_TOKENIZER) $(LIBFT) -lreadline

envvar: $(NAME_ENV_VAR)

$(NAME_ENV_VAR): $(LIBFT) $(OBJS_ENV_VAR) obj/main_env_var.o
	$(CC) $(CFLAGS) -o $(NAME_ENV_VAR) obj/main_env_var.o $(OBJS_ENV_VAR) $(LIBFT)

obj/:
	mkdir -p obj/

obj/%.o: %.c | obj/
	$(CC) $(CFLAGS) -o $@ -c $< -I../include/

$(LIBFT):
	make -C ../libft

clean:
	rm -rf obj/
	make clean -C ../libft

fclean: clean
	rm -f $(NAME_TOKENIZER) $(NAME_PARSER) $(NAME_ENV_VAR)
	make fclean -C ../libft

.PHONY: tokenizer parser clean fclean re
