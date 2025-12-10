NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_SRCS =\
	ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_strlen.c\
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_strlcpy.c\
	ft_strlcat.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strncmp.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_strnstr.c\
	ft_atoi.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_split.c\
	ft_itoa.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\

LIST_SRCS =\
	ft_lstnew_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstadd_back_bonus.c\
	ft_lstdelone_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstiter_bonus.c\
	ft_lstmap_bonus.c\

PRINTF_SRCS =\
	ft_printf.c\
	convert_type.c\
	type_conversion/convert_c.c\
	type_conversion/convert_s.c\
	type_conversion/convert_p.c\
	type_conversion/convert_d_i.c\
	type_conversion/convert_d_i_utils.c\
	type_conversion/convert_u.c\
	type_conversion/convert_lower_x.c\
	type_conversion/convert_lower_x_utils.c\
	type_conversion/convert_upper_x.c\
	type_conversion/convert_upper_x_utils.c\
	type_conversion/convert_percent.c\
	utils/ft_puthexa.c\
	utils/count_digits.c\
	utils/ft_putunbr.c\
	utils/ft_putspaces.c\
	utils/ft_putzeros.c\
	utils/handle_num_sign.c\
	utils/ft_putchar.c\
	utils/ft_putstr.c\

GNL_SRCS =\
	get_next_line.c\
	get_next_line_utils.c\

LIBFT_DIR = libft
LIST_DIR = list
PRINTF_DIR = ft_printf ft_printf/type_conversion ft_printf/utils
GNL_DIR = get_next_line
OBJ_DIR = obj
HEADER_DIR = header

LIBFT_OBJS = $(addprefix $(OBJ_DIR)/, $(LIBFT_SRCS:.c=.o))
LIST_OBJS = $(addprefix $(OBJ_DIR)/, $(LIST_SRCS:.c=.o))
PRINTF_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(PRINTF_SRCS:.c=.o)))
GNL_OBJS = $(addprefix $(OBJ_DIR)/, $(GNL_SRCS:.c=.o))

vpath %.c $(LIBFT_DIR) $(LIST_DIR) $(PRINTF_DIR) $(GNL_DIR)

all: $(NAME)

$(NAME): $(LIBFT_OBJS) $(LIST_OBJS) $(PRINTF_OBJS) $(GNL_OBJS)
	ar rcs $(NAME) $(LIBFT_OBJS) $(LIST_OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I./$(HEADER_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
