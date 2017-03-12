/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 14:35:08 by liabanzh          #+#    #+#             */
/*   Updated: 2017/02/12 14:35:10 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*repoint(char *ptr)
{
	while (valid_setting(*ptr) && *ptr != '\0')
		ptr++;
	if (*ptr == '\0')
		return (NULL);
	if (valid_type(*ptr))
		return (ptr + 1);
	else if (*ptr == '%')
		return (ptr + 1);
	return (ptr);
}

t_arg	*include(const char *format, va_list ap, int count)
{
	int		index;
	t_arg	*map;
	char	*ptr;

	index = 0;
	map = (t_arg*)malloc(sizeof(t_arg) * count);
	ptr = ft_strchr(format, '%');
	if (ptr == NULL)
		return (NULL);
	while (index < count && ptr != NULL)
	{
		ptr = ft_strchr(ptr, '%');
		map[index].type = get_type(ptr + 1);
		map[index].setting = get_setting(ptr + 1, map[index].type); // SEGV there
		get_width(ptr + 1, ap, &(map[index]));
		get_data(ap, map[index].type, &(map[index]));
		ptr = repoint(ptr + 1);
		index++;
	}
	return (map);
}

int		count_arg(const char *format)
{
	int		res;
	char	*ptr;

	res = 0;
	ptr = (char*)format;
	while (ptr != NULL)
	{
		ptr = ft_strchr(ptr, '%');
		if (ptr == NULL)
			break ;
		else
			ptr++;
		while (valid_setting(*ptr) && *ptr != '\0')
			ptr++;
		if (*ptr == '%')
		{
			ptr++;
			res++;
		}
		else
			res++;
	}
	return (res);
}

int		ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	ap;
	t_arg	*map;

	i = 0;
	count = count_arg(format);
	va_start(ap, format);
	map = include(format, ap, count);
	return (print_string(map, format, count));
}
