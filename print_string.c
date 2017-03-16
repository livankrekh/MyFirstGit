/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:55:43 by liabanzh          #+#    #+#             */
/*   Updated: 2017/02/16 18:55:44 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*res_str(char *ptr, t_arg arg)
{
	if (*(arg.type) == 's')
		return (create_s(arg));
	else if (*(arg.type) == 'c' || *(arg.type) == 'C' ||
		ft_strnstr(ptr, "lc", 2) || *(arg.type) == '%')
		return (create_c(arg));
	else if (ft_strchr(arg.type, 'S') || ft_strnstr(arg.type, "ls", 3))
		return (create_w(arg.unidata));
	else if ((ft_strnstr(arg.type, "d", 3) || ft_strnstr(arg.type, "i", 3) ||
		ft_strchr(arg.type, 'D')) && !ft_strchr(arg.type, 'z'))
		return (create_d(arg));
	else if (ft_strnstr(arg.type, "u", 3) || ft_strnstr(arg.type, "U", 3) ||
			ft_strnstr(arg.type, "zd", 3) || ft_strnstr(arg.type, "zi", 3))
		return (create_un(arg, 10));
	else if (ft_strnstr(arg.type, "o", 3) || ft_strnstr(arg.type, "O", 3))
		return (create_un(arg, 8));
	else if (ft_strnstr(arg.type, "x", 3))
		return (create_un(arg, 16));
	else if (ft_strnstr(arg.type, "X", 3))
		return (ft_str_toupper(create_un(arg, 16)));
	else if (ft_strnstr(arg.type, "p", 3))
		return (create_pointer(arg));
	return (NULL);
}

int		null_count(t_arg *map, int count)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (i < count)
	{
		if ((ft_strchr(map[i].type, 'c') || ft_strchr(map[i].type, 'C'))
			&& map[i].data_numb == 0)
			res++;
		i++;
	}
	return (res);
}

void	print_null(t_arg arg, int *res)
{
	int		len;
	char	*tmp;

	len = 0;
	tmp = create_c(arg);
	if (ft_strchr(arg.setting, '-'))
	{
		ft_putstr(tmp);
		write(1, "\0", 1);
	}
	else
	{
		write(1, "\0", 1);
		ft_putstr(tmp);
	}
	*res += ft_strlen(tmp) + 1;
	free(tmp);
}

void	stdout_str(t_arg *map, char **ptr, int count, int *res)
{
	char	*tmp;
	int		i;

	i = 1;
	while (i < count)
	{
		write(1, *ptr, ft_strlen(*ptr) - ft_strlen(ft_strchr(*ptr, '%')));
		*res += ft_strlen(*ptr) - ft_strlen(ft_strchr(*ptr, '%'));
		*ptr = ft_strchr(*ptr, '%');
		if ((ft_strchr(map[i].type, 'c') ||
			ft_strchr(map[0].type, 'c')) && map[i].data_numb == 0)
			print_null(map[i], res);
		else
		{
			tmp = res_str(*ptr, map[i]);
			ft_putstr(tmp);
		}
		*res += ft_strlen(tmp);
		free(tmp);
		if (ptr == NULL)
			break ;
		*ptr = repoint(*ptr + 1);
		i++;
	}
}

int		print_string(t_arg *map, const char *format, int count)
{
	int		i;
	char	*ptr;
	int		res;
	char	*tmp;

	i = 0;
	res = 0;
	while (format[i] != '%' && format[i] != '\0')
		i++;
	write(1, format, i);
	res += i;
	if ((ptr = ft_strchr(format, '%')) == NULL)
		return (ft_strlen(format));
	if ((ft_strchr(map[0].type, 'c') || ft_strchr(map[0].type, 'C'))
		&& map[0].data_numb == 0)
		print_null(map[0], &res);
	else
	{
		ft_putstr((tmp = res_str(ptr, map[0])));
		res += ft_strlen(tmp);
	}
	ptr = repoint(ptr + 1);
	stdout_str(map, &ptr, count, &res);
	return (delete_all(map, ptr, res, count));
}
