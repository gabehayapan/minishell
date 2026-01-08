/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:54:28 by hanakamu          #+#    #+#             */
/*   Updated: 2025/11/28 16:22:42 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPRINTF_H
# define FTPRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

typedef struct s_flag
{
	int	is_sharp;
	int	is_space;
	int	is_plus;
	int	is_zero;
	int	is_minus;
	int	width;
	int	is_dot;
	int	prec;
	int	write_error;
}	t_flag;

int		ft_printf(const char *format, ...);
int		check_type_sign(const char **format, va_list args, int *counter);
void	convert_c(va_list args, int *counter, t_flag *flag_lst);
void	convert_s(va_list args, int *counter, t_flag *flag_lst);
void	convert_percent(int *counter, t_flag *flag_lst);
void	convert_p(va_list args, int *counter, t_flag *flag_lst);
void	convert_d_i(va_list args, int *counter, t_flag *flag_lst);
void	convert_u(va_list args, int *counter, t_flag *flag_lst);
void	convert_lower_x(va_list args, int *counter, t_flag *flag_lst);
void	convert_upper_x(va_list args, int *counter, t_flag *flag_lst);
void	ft_puthexa_lower(unsigned int u_num, int *counter, t_flag *flag_lst);
void	ft_puthexa_upper(unsigned int u_num, int *counter, t_flag *flag_lst);
void	ft_putunbr(unsigned int u_num, int *counter, t_flag *flag_lst);
void	ft_putspaces(int num, int *counter, t_flag *flag_lst);
void	ft_putzeros(int num, int *counter, t_flag *flag_lst);
void	ft_putchar(char c, int *counter, t_flag *flag_lst);
void	ft_putstr(const char *s, int *counter, t_flag *flag_lst);
void	ft_putnstr(const char *s, int *counter, t_flag *flag_lst, int n);
int		count_decimal_digits(unsigned int num);
int		count_hexa_digits(unsigned long long ull_num);
void	handle_num_sign(int num, int *counter, t_flag *flag_lst);
void	check_width_d_i_leftindent(int num, int num_digits,
			int *counter, t_flag *flag_lst);
void	check_width_d_i_rightindent(int num, int num_digits,
			int *counter, t_flag *flag_lst);
void	d_i_space_zero_leftindent(int num, int num_digits,
			int *counter, t_flag *flag_lst);
void	d_i_space_zero_rightindent(int num, int num_digits,
			int *counter, t_flag *flag_lst);
void	exception_zero_d_i(int *counter, t_flag *flag_lst);
void	check_width_lower_x_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst);
void	check_width_lower_x_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst);
void	lower_x_space_zero_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst);
void	lower_x_space_zero_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst);
void	exception_zero_lower_x(int *counter, t_flag *flag_lst);
void	check_width_upper_x_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst);
void	check_width_upper_x_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst);
void	upper_x_space_zero_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst);
void	upper_x_space_zero_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_flag *flag_lst);
void	exception_zero_upper_x(int *counter, t_flag *flag_lst);

#endif
