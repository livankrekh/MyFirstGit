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

int		accur(t_arg arg)
{
	char *type;

	type = arg.type;
	if (*type == 's')
		return (ft_strlen(arg.data));
	else if (*type == 'c' || !ft_strncmp(type, "hh", 2))
		return (1);
	else if (!ft_strncmp(type, "ls", 2) || !ft_strncmp(type, "lc", 2) ||
		*type == 'S' || *type == 'C')
		return (ft_strlen((char*)arg.unidata));
	else if (!ft_strncmp(type, "d", 3) || !ft_strncmp(type, "i", 3))
		return (ft_strlen(ft_itoa_base(arg.data_numb, 10)));
	else if (!ft_strncmp(type, "o", 3))
		return (ft_strlen(ft_itoa_base(arg.undata, 8)));
	else if (!ft_strncmp(type, "u", 3))
		return (ft_strlen(ft_itoa_base(arg.undata, 10)));
	else if (!ft_strncmp(type, "x", 3) || !ft_strncmp(type, "X", 3))
		return (ft_strlen(ft_itoa_base(arg.undata, 16)));
	else if (*type == 'p')
		return (ft_strlen(ft_itoa_base(arg.data_numb, 16)) + 2);
	else if (*type == 'L' || *type == 'e' || *type == 'E' || *type == 'g' ||
			*type == 'G' || *type == 'f' || *type == 'f' || *type == 'F' ||
			*type == 'a' || *type == 'A')
		return (ft_strlen(ft_itoa_base((intmax_t)arg.float_data, 10)) + 5);
	return (0);
}

char	*res_str(char *ptr, t_arg arg)
{
	if (*(arg.type) == 's')
		return (create_s(arg));
	else if (*(arg.type) == 'c' || *(arg.type) == 'C' || ft_strnstr(ptr, "lc", 2)
		|| *(arg.type) == '%')
		return (create_c(arg));
	else if ((ft_strnstr(arg.type, "d", 3) || ft_strnstr(arg.type, "i", 3) ||
		ft_strchr(arg.type, 'D')) && *(arg.type) != 'z')
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

int		print_string(t_arg *map, const char *format, int count)
{
	char	*str;
	int		size;
	int		i;
	char	*ptr;

	size = ft_strlen(format);
	i = 0;
	while (i < count)
		size += (map[i].width == 0 && map[i].accur == 0) ? accur(map[i++]) : (map[i].width >= map[i].accur ? map[i++].width : map[i++].accur);
	str = ft_strnew(size);
	i = 0;
	while (format[i] != '%' && format[i] != '\0')
		i++;
	ft_strncpy(str, format, i);
	ptr = ft_strchr(format, '%');
	if (ptr == NULL)
	{
		ft_putstr(str);
		return (ft_strlen(str));
	}
	ft_strcat(str, res_str(ptr, map[0])); // SegV there!!!
	ptr = ft_strchr(ptr, map[0].type[ft_strlen(map[0].type) - 1]) + 1;
	i = 1;
	while (i < count)
	{
		ft_strncat(str, ptr, ft_strlen(ptr) - ft_strlen(ft_strchr(ptr, '%')));
		ft_strcat(str, res_str(ptr, map[i]));
		ptr = ft_strchr(ptr, map[i].type[ft_strlen(map[i].type) - 1]) + 1;
		i++;
	}
	ft_strcat(str, ptr);
	ft_putstr(str);
	//printf("WIDTH = %d || ACCURANCE = %d || SIZE = %d || SETTING = %s || TYPE = %s\n", map[0].width, map[0].accur, size, map[0].setting, map[0].type);
	return (ft_strlen(str));
}