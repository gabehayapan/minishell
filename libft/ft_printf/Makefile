NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
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
	libft/ft_isalpha.c\
	libft/ft_isdigit.c\
	libft/ft_isalnum.c\
	libft/ft_isascii.c\
	libft/ft_isprint.c\
	libft/ft_strlen.c\
	libft/ft_memset.c\
	libft/ft_bzero.c\
	libft/ft_memcpy.c\
	libft/ft_memmove.c\
	libft/ft_strlcpy.c\
	libft/ft_strlcat.c\
	libft/ft_toupper.c\
	libft/ft_tolower.c\
	libft/ft_strchr.c\
	libft/ft_strrchr.c\
	libft/ft_strncmp.c\
	libft/ft_memchr.c\
	libft/ft_memcmp.c\
	libft/ft_strnstr.c\
	libft/ft_atoi.c\
	libft/ft_calloc.c\
	libft/ft_strdup.c\
	libft/ft_substr.c\
	libft/ft_strjoin.c\
	libft/ft_strtrim.c\
	libft/ft_split.c\
	libft/ft_itoa.c\
	libft/ft_strmapi.c\
	libft/ft_striteri.c\
	libft/ft_putchar_fd.c\
	libft/ft_putstr_fd.c\
	libft/ft_putendl_fd.c\
	libft/ft_putnbr_fd.c\
	libft/ft_lstnew_bonus.c\
	libft/ft_lstadd_front_bonus.c\
	libft/ft_lstsize_bonus.c\
	libft/ft_lstlast_bonus.c\
	libft/ft_lstadd_back_bonus.c\
	libft/ft_lstdelone_bonus.c\
	libft/ft_lstclear_bonus.c\
	libft/ft_lstiter_bonus.c\
	libft/ft_lstmap_bonus.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus:
	make

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
