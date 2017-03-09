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

void	get_width(char *setting, va_list ap, t_arg *arg)
{
	while ((*setting <= '0' || *setting > '9') && *setting != '*' &&
			*setting != '.' && *setting != '\0')
		setting++;
	if (ft_isdigit(*setting) || *setting == '*')
	{
		if (*setting == '*')
			arg->width = va_arg(ap, int);
		else
			arg->width = atoi(setting);
		while (((!ft_isdigit(*(setting + 1)) || *(setting + 1) != '*') ||
				*setting != '.') && *(setting + 1) != '\0')
			setting++;
	}
	else
		arg->width = 0;
	if (*setting == '.' && (ft_isdigit(*(setting + 1)) || *(setting + 1) == '*'))
	{
		if (*(setting + 1) == '*')
			arg->accur = va_arg(ap, int);
		else
			arg->accur = atoi(setting + 1);
	}
	else
		arg->accur = -1;
}

int		valid_setting(char c)
{
	if ((c == '#' || c == '-' || c == ' ' || c == '.' ||
		ft_isdigit(c) || c == '+' || c == '*' ||
		c == 'l'|| c == 'h' || c == 'j' || c == 'z'
		|| c == 'L'))
		return (1);
	return (0);
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
	if (ptr[i] == 'd' || ptr[i] == 'i' || ptr[i] == 'u' || ptr[i] == 'o' ||
		ptr[i] == 'x' || ptr[i] == 'X' || ptr[i] == 'c' || ptr[i] == 'C' ||
		ptr[i] == 's' || ptr[i] == 'S' || ptr[i] == 'p' || ptr[i] == 'O' ||
		ptr[i] == 'U' || ptr[i] == 'D' || ptr[i] == '%')
		ft_strncat(tmp, ptr + i, 1);
	else
		ft_strncat(tmp, ptr + i - 1, 1);
	if (ft_strchr(tmp, 'z'))
		ft_strncat(res, "z", 1);
	else if (ft_strchr(tmp, 'j'))
		ft_strncat(res, "j", 1);
	else if (ft_strstr(tmp, "ll"))
		ft_strncat(res, "ll", 2);
	else
		ft_strcat(res, (ft_strchr(tmp, 'l') ? "l" : (ft_strstr(tmp, "hh") ? "hh" :
			(ft_strchr(tmp, 'h') ? "h" : ""))));
	ft_strncat(res, &tmp[ft_strlen(tmp) - 1], 1);
	return (res);
}

// char	*get_type(char *ptr)
// {
// 	char	*res;
// 	int		count;

// 	while (!ft_isalpha(*ptr))
// 		ptr++;
// 	if (ft_strnstr(ptr, "hh", 2) || ft_strnstr(ptr, "ll", 2))
// 		count = 3;
// 	else if (*ptr == 'h' || *ptr == 'l' || *ptr == 'j' ||
// 				*ptr == 'z' || *ptr == 'L')
// 		count = 2;
// 	else
// 		count = 1;
// 	res = (char*)malloc(sizeof(char) * count + 1);
// 	res[count] = '\0';
// 	return (ft_strncpy(res, ptr, count));
// }

	// while (!ft_isdigit(*setting) && *setting != '.' && *setting != '\0')
	// 	setting++;
	// if (*setting == '0')
	// 	setting++;
	// if (ft_isdigit(*setting))
	// 	arg->width = ft_atoi(setting);
	// else if (*setting == '*')
	// 	arg->width = va_arg(ap, int);
	// else
	// 	arg->width = 0;
	// if (ft_strchr(setting, '.'))
	// {
	// 	setting = ft_strchr(setting, '.') + 1;
	// 	if (ft_isdigit(*setting))
	// 		arg->accur = ft_atoi(setting);
	// 	else if (*setting == '*')
	// 		arg->accur = va_arg(ap, int);
	// 	else
	// 		arg->accur = -1;
	// }
	// else
	// 	arg->accur = -1;
	// *setting = '\0';