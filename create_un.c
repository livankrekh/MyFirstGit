/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_un.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:57:37 by liabanzh          #+#    #+#             */
/*   Updated: 2017/03/16 16:57:38 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		norm(t_arg arg)
{
	int		norm;

	norm = 0;
	if ((ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X')) &&
			ft_strchr(arg.setting, '#'))
		norm = 2;
	else
		norm = (ft_strchr(arg.setting, '#') &&
			(ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O')) ? 1 : 0);
	return (norm);
}

void	dop_un1(t_arg arg, char *n, char **res, int len)
{
	int		accur;

	accur = arg.accur;
	if (ft_strchr(arg.setting, '#') && (ft_strchr(arg.type, 'x') ||
			ft_strchr(arg.type, 'X') || ft_strchr(arg.type, 'o') ||
			ft_strchr(arg.type, 'O')))
	{
		if ((ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X')) &&
				arg.undata != 0)
			ft_strncat(*res, "0x", 2);
		else
			ft_strncat(*res, (ft_strchr(arg.type, 'o') ||
					ft_strchr(arg.type, 'O') ? "0" : ""), 1);
	}
	while (arg.accur-- > len + norm(arg))
		ft_strncat(*res, "0", 1);
	if (!ft_strchr(arg.setting, '.') || arg.accur > 0 || arg.undata != 0)
		ft_strcat(*res, n);
	while (arg.width-- + (arg.accur <= 0 && arg.undata == 0) >
			((accur > len) ? accur : len) + norm(arg))
		ft_strncat(*res, " ", 1);
}

void	dop_un2(t_arg arg, char *n, char **res, int len)
{
	if (ft_strchr(arg.setting, '0') && arg.undata != 0 && arg.accur == -1 &&
			ft_strchr(arg.setting, '#') && (ft_strchr(arg.type, 'x') ||
			ft_strchr(arg.type, 'X') || ft_strchr(arg.type, 'o') ||
			ft_strchr(arg.type, 'O')))
		ft_strncat(*res, ft_strchr(arg.type, 'x') ||
					ft_strchr(arg.type, 'X') ? "0x" : "0", 2);
	while (arg.width-- + (arg.accur <= 0 && arg.undata == 0) >
			((arg.accur > len) ? arg.accur : len) + norm(arg))
		ft_strncat(*res, (ft_strchr(arg.setting, '0') && arg.accur == -1)
					? "0" : " ", 1);
	if (!ft_strchr(arg.setting, '0') && ft_strchr(arg.setting, '#') &&
			(ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X') ||
			ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O')))
	{
		if ((ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X'))
				&& arg.undata != 0)
			ft_strncat(*res, "0x", 2);
		else
			ft_strncat(*res, (ft_strchr(arg.type, 'o')
				|| ft_strchr(arg.type, 'O') ? "0" : ""), 1);
	}
	while (arg.accur-- > len)
		ft_strncat(*res, "0", 1);
	if (!ft_strchr(arg.setting, '.') || arg.accur > 0 || arg.undata != 0)
		ft_strcat(*res, n);
}

void	dop_un3(t_arg arg, char *n, char **res)
{
	int		accur;

	accur = arg.accur;
	if ((ft_strchr(arg.setting, '#') && (arg.undata != 0 ||
			(ft_strchr(arg.setting, '.') && arg.accur <= 0))) &&
			(ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X') ||
			ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O')))
	{
		if ((ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X'))
				&& arg.undata != 0)
			ft_strncat(*res, "0x", 2);
		else
			ft_strncat(*res, (ft_strchr(arg.type, 'o') ||
				ft_strchr(arg.type, 'O') ? "0" : ""), 2);
	}
	if (!ft_strchr(arg.setting, '.') || arg.accur > 0 || arg.undata != 0)
		ft_strcat(*res, n);
}

char	*create_un(t_arg arg, int base)
{
	char			*res;
	char			*n;
	int				len;
	int				size;

	size = 0;
	n = ft_itoa_base_u(arg.undata, base);
	len = ft_strlen(n);
	if (arg.width >= arg.accur && arg.width >= len)
		size = arg.width + (ft_strchr(arg.setting, '#') ? 2 : 0);
	else
		size = (arg.accur >= len ? arg.accur : len) +
				(ft_strchr(arg.setting, '#') != NULL ? 2 : 0);
	res = ft_strnew(size);
	if (arg.width > len || arg.accur > len)
	{
		if (ft_strchr(arg.setting, '-'))
			dop_un1(arg, n, &res, len);
		else
			dop_un2(arg, n, &res, len);
	}
	else
		dop_un3(arg, n, &res);
	free(n);
	return (res);
}
