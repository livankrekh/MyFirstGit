/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 14:39:59 by liabanzh          #+#    #+#             */
/*   Updated: 2017/02/16 14:40:03 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_setting(char *ptr, char *type)
{
	char	*res;
	int 	i;

	res = ft_strnew(ft_strlen(ptr) - ft_strlen(ft_strchr(ptr,
		type[ft_strlen(type) - 1]) + 1));
	i = 0;
	while ((ptr[i] == '#' || ptr[i] == '-' || ptr[i] == ' ' || ptr[i] == '.' ||
		ft_isalnum(ptr[i]) || ptr[i] == '+' || ptr[i] == '*') && ptr[i] != '\0')
	{
		if (ptr[i] == '#' || ptr[i] == '-' || ptr[i] == ' ' || ptr[i] == '+' ||
			(ptr[i] == '0' && !ft_isdigit(ptr[i - 1])))
			ft_strncat(res, ptr + i, 1);
		i++;
	}
	return (res);
}

void	*include_data(int size, void *data)
{
	char	*tmp;

	if (data == NULL)
		return (NULL);
	if (size == 0)
		size = ft_strlen((char*)data) + 1;
	tmp = (void*)malloc(size);
	return (ft_memcpy(tmp, data, size));
}

void	dop2(va_list ap, char *type, t_arg *arg)
{
	if (*(type) == 'e' || *(type) == 'E' || *(type) == 'a' ||
		*(type) == 'A' || *(type) == 'f' || *(type) == 'F' ||
		*(type) == 'g' || *(type) == 'G')
		arg->float_data = va_arg(ap, double);
	else if (*type == 'L')
		arg->float_data = va_arg(ap, long double);
	else if (*type == 'p')
		arg->data_numb = (long long)&(*(va_arg(ap, void *)));
	else if (ft_strchr(type, '%'))
		arg->data_numb = (int)'%';
}

void	dop(va_list ap, char *type, t_arg *arg)
{
	if (!ft_strncmp(type, "zd", 2) || !ft_strncmp(type, "zi", 2) ||
		!ft_strncmp(type, "zu", 2) || !ft_strncmp(type, "zo", 2) ||
		!ft_strncmp(type, "zx", 2) || !ft_strncmp(type, "zX", 2))
		arg->undata = va_arg(ap, size_t);
	else if (*type == 'u' || *type == 'o' || *type == 'x' || *type == 'X')
		arg->undata = va_arg(ap, unsigned int);
	else if (!ft_strncmp(type, "hhu", 3) || !ft_strncmp(type, "hho", 3) ||
		!ft_strncmp(type, "hhx", 3) || !ft_strncmp(type, "hhX", 3))
		arg->undata = (unsigned char)va_arg(ap, unsigned int);
	else if (!ft_strncmp(type, "hu", 2) || !ft_strncmp(type, "ho", 2) ||
			!ft_strncmp(type, "hx", 2) || !ft_strncmp(type, "hX", 2))
		arg->undata = (unsigned short int)va_arg(ap, unsigned int);
	else if (!ft_strncmp(type, "llu", 3) || !ft_strncmp(type, "llo", 3) ||
			!ft_strncmp(type, "llx", 3) || !ft_strncmp(type, "llX", 3))
		arg->undata = va_arg(ap, unsigned long long int);
	else if (!ft_strncmp(type, "lu", 2) || !ft_strncmp(type, "lo", 2) ||
			!ft_strncmp(type, "lx", 2) || !ft_strncmp(type, "lX", 2))
		arg->undata = va_arg(ap, unsigned long int);
	else if (!ft_strncmp(type, "ju", 2) || !ft_strncmp(type, "jo", 2) ||
			!ft_strncmp(type, "jx", 2) || !ft_strncmp(type, "jX", 2))
		arg->undata = va_arg(ap, uintmax_t);
	else
		dop2(ap, type, arg);
}

void	get_data(va_list ap, char *type, t_arg *arg)
{
	if (*type == 's')
		arg->data = include_data(0, (void*)va_arg(ap, char*));
	else if (!ft_strncmp(type, "ls", 2) || *type == 'S')
		arg->unidata = include_data(0, (void*)va_arg(ap, wchar_t*));
	else
	{
		if (*type == 'c')
			arg->data_numb = (char)va_arg(ap, int);
		else if (ft_strnstr(type, "lc", 2) || *type == 'C')
			arg->data_numb = (char)va_arg(ap, wchar_t);
		else if (!ft_strncmp(type, "hhd", 3) || !ft_strncmp(type, "hhi", 3))
			arg->data_numb = (signed char)va_arg(ap, int);
		else if (*type == 'd' || *type == 'i')
			arg->data_numb = (int)va_arg(ap, int);
		else if (!ft_strncmp(type, "hd", 2) || !ft_strncmp(type, "hi", 2))
			arg->data_numb = (short int)va_arg(ap, int);
		else if (!ft_strncmp(type, "ld", 2) || !ft_strncmp(type, "li", 2))
			arg->data_numb = va_arg(ap, long int);
		else if (!ft_strncmp(type, "lld", 3) || !ft_strncmp(type, "lli", 3))
			arg->data_numb = va_arg(ap, long long int);
		else if (!ft_strncmp(type, "jd", 2) || !ft_strncmp(type, "ji", 2))
			arg->data_numb = va_arg(ap, intmax_t);
		else
			dop(ap, type, arg);
	}
}

	// char	*res;
	// int		count;

	// count = 0;
	// while (!ft_isalpha(ptr[count]))
	// 	count++;
	// res = (char*)malloc(sizeof(char) * count + 1);
	// res[count] = '\0';
	// ft_strncpy(res, ptr, count);
	// return (res);
