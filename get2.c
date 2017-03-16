/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 19:13:40 by liabanzh          #+#    #+#             */
/*   Updated: 2017/02/16 19:13:41 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_width(char *set, va_list ap, t_arg *arg)
{
	while ((*set <= '0' || *set > '9') && *set != '*' &&
		*set != '.' && *set != '\0' &&
		*set != arg->type[ft_strlen(arg->type) - 1])
		set++;
	if (ft_isdigit(*set) || *set == '*')
	{
		if (*set == '*' || *(set + 1) == '*')
			arg->width = va_arg(ap, int);
		else
			arg->width = ft_atoi(set);
	}
	else
		arg->width = 0;
	while ((*set != '.' || (!ft_isdigit(*(set + 1)) &&
		*(set + 1) != '*')) && *set != '\0')
		set++;
	if (*set == '.' && (ft_isdigit(*(set + 1)) || *(set + 1) == '*'))
	{
		if (*(set + 1) == '*')
			arg->accur = va_arg(ap, int);
		else
			arg->accur = ft_atoi(set + 1);
	}
	else
		arg->accur = -1;
}

int		valid_setting(char c)
{
	if ((c == '#' || c == '-' || c == ' ' || c == '.' ||
		ft_isdigit(c) || c == '+' || c == '*' ||
		c == 'l' || c == 'h' || c == 'j' || c == 'z'
		|| c == 'L'))
		return (1);
	return (0);
}

int		valid_type(char c)
{
	if (c == 'd' || c == 'D' || c == 'i' || c == 'o' || c == 'O' || c == 'u'
		|| c == 'U' || c == 'x' || c == 'X' || c == 'p' || c == 'f' ||
		c == 'F' || c == 'a' || c == 'A' || c == 'g' || c == 'G' ||
		c == 'e' || c == 'E' || c == 'S' || c == 's' || c == 'c' || c == 'C'
		|| c == 'n')
		return (1);
	return (0);
}

void	to_norm(char *tmp, char **res)
{
	if (ft_strchr(tmp, 'z'))
		ft_strncat(*res, "z", 1);
	else if (ft_strchr(tmp, 'j'))
		ft_strncat(*res, "j", 1);
	else if (ft_strstr(tmp, "ll"))
		ft_strncat(*res, "ll", 2);
	else if (ft_strchr(tmp, 'l'))
		ft_strncat(*res, "l", 1);
	else if (ft_strstr(tmp, "hh"))
		ft_strncat(*res, "hh", 2);
	else if (ft_strchr(tmp, 'h'))
		ft_strncat(*res, "h", 1);
}

char	*get_type(char *ptr)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	res = ft_strnew(3);
	tmp = ft_strnew(10);
	while (valid_setting(ptr[i]) && ptr[i] != '\0')
	{
		if (ft_isalpha(ptr[i]))
			ft_strncat(tmp, ptr + i, 1);
		i++;
	}
	if (valid_type(ptr[i]) || ptr[i] == '%')
		ft_strncat(tmp, ptr + i, 1);
	else if (*ptr != ptr[i])
		ft_strncat(tmp, ptr + i - 1, 1);
	to_norm(tmp, &res);
	if (ft_strlen(tmp) > 0)
		ft_strncat(res, &tmp[ft_strlen(tmp) - 1], 1);
	free(tmp);
	return (res);
}
