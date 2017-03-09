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

t_arg	*include(const char *format, va_list ap, int count, int *i)
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
		map[index].setting = get_setting(ptr + 1, map[index].type);
		get_width(ptr + 1, ap, &(map[index]));
		get_data(ap, map[index].type, &(map[index]));
		ptr = ft_strchr(ptr, map[index].type[ft_strlen(map[0].type) - 1]) + 1;
		index++;
	}
	*i = index;
	return (map);
}

// int		count_arg(const char *format)
// {
// 	int		res;
// 	char	*ptr;

// 	res = 0;
// 	ptr = format;
// 	while (ptr != NULL)
// 	{
// 		ptr = ft_strchr(ptr, '%') + 1;
// 		while (valid_setting(ptr) || ft_isdigit(ptr))
// 			ptr++;
// 		if (ptr == '%')
// 		{
// 			ptr++;
// 			res++;
// 		}
// 		else
// 		{

// 		}
// 	}
// }

int		ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	ap;
	t_arg	*map;

	i = 0;
	count = 0;
	//count = count_arg(format);
	while (format[i] != '\0')
		count += (format[i++] == '%');
	va_start(ap, format);
	map = include(format, ap, count, &count);
	va_end(ap);
	return (print_string(map, format, count));
}
