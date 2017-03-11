/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 13:26:12 by liabanzh          #+#    #+#             */
/*   Updated: 2017/02/13 13:26:13 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct		s_arg
{
	char			*type;
	char			*setting;
	char			*data;
	wchar_t			*unidata;
	intmax_t		data_numb;
	uintmax_t		undata;
	long double		float_data;
	int				width;
	int				accur;
}					t_arg;

int					ft_printf(const char *format, ...);
void				get_data(va_list ap, char *type, t_arg *arg);
char				*get_setting(char *ptr, char *type);
char				*get_type(char *ptr);
void				get_width(char *setting, va_list ap, t_arg *arg);
int					print_string(t_arg *map, const char *format, int count);
char				*create_s(t_arg arg);
char				*create_d(t_arg arg);
char				*create_un(t_arg arg, int base);
char				*create_pointer(t_arg arg);
char				*create_c(t_arg arg);
int					valid_setting(char c);
int					valid_type(char c);
char				*repoint(char *ptr);

#endif
