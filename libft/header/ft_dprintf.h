/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:54:28 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/19 14:42:26 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

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
	int	fd;
}	t_flag;

int		ft_dprintf(int fd, const char *format, ...);
void	_check_type_sign(const char **format, va_list args, int *counter,
			int fd);
void	_convert_c(va_list args, int *counter, t_flag flag_lst);
void	_convert_s(va_list args, int *counter, t_flag flag_lst);
void	_convert_percent(int *counter, int fd);
void	_convert_p(va_list args, int *counter, t_flag flag_lst);
void	_convert_d_i(va_list args, int *counter, t_flag flag_lst);
void	_convert_u(va_list args, int *counter, t_flag flag_lst);
void	_convert_lower_x(va_list args, int *counter, t_flag flag_lst);
void	_convert_upper_x(va_list args, int *counter, t_flag flag_lst);
void	_ft_puthexa_lower(unsigned int u_num, int fd);
void	_ft_puthexa_upper(unsigned int u_num, int fd);
void	_ft_putunbr(unsigned int u_num, int fd);
void	_ft_putspaces(int num, int *counter, int fd);
void	_ft_putzeros(int num, int *counter, int fd);
int		_count_decimal_digits(unsigned int num);
int		_count_hexa_digits(unsigned long long ull_num);
void	_handle_num_sign(int num, int *counter, t_flag flag_lst);
void	_check_width_d_i_leftindent(int num, int num_digits,
			int *counter, t_flag flag_lst);
void	_check_width_d_i_rightindent(int num, int num_digits,
			int *counter, t_flag flag_lst);
void	_d_i_space_zero_leftindent(int num, int num_digits,
			int *counter, t_flag flag_lst);
void	_d_i_space_zero_rightindent(int num, int num_digits,
			int *counter, t_flag flag_lst);
void	_exception_zero_d_i(int *counter, t_flag flag_lst);
void	_check_width_lower_x_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_flag flag_lst);
void	_check_width_lower_x_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_flag flag_lst);
void	_lower_x_space_zero_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_flag flag_lst);
void	_lower_x_space_zero_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_flag flag_lst);
void	_exception_zero_lower_x(int *counter, t_flag flag_lst);
void	_check_width_upper_x_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_flag flag_lst);
void	_check_width_upper_x_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_flag flag_lst);
void	_upper_x_space_zero_leftindent(unsigned int u_num, int num_digits,
			int *counter, t_flag flag_lst);
void	_upper_x_space_zero_rightindent(unsigned int u_num, int num_digits,
			int *counter, t_flag flag_lst);
void	_exception_zero_upper_x(int *counter, t_flag flag_lst);

#endif
