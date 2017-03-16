/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:56:01 by liabanzh          #+#    #+#             */
/*   Updated: 2017/03/16 16:56:02 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dop_d1(t_arg arg, char *n, int accur, char **res)
{
	if (ft_strchr(arg.setting, ' ') && !ft_strchr(arg.setting, '+') &&
		n[0] != '-')
		**res = ' ';
	if (ft_strchr(arg.setting, '+') || n[0] == '-')
		**res = (*n == '-') ? *n : '+';
	while (arg.accur-- > (int)ft_strlen(n))
		ft_strncat(*res, "0", 1);
	if (!ft_strchr(arg.setting, '.') || arg.accur > 0 ||
		arg.data_numb != 0)
		ft_strcat(*res, (n[0] == '-' ? n + 1 : n));
	while (arg.width-- + (arg.accur <= 0 && arg.data_numb == 0) >
			(int)(ft_strlen((n[0] == '-') ? n + 1 : n) +
			(ft_strchr(arg.setting, '+') || ft_strchr(arg.setting, ' ')
			|| n[0] == '-') + (((int)ft_strlen(n) >= accur) ? 0 :
			(accur - ft_strlen(n)))))
		ft_strncat(*res, " ", 1);
}

void	dop_d4(t_arg arg, char *n, int accur, char **res)
{
	if ((ft_strchr(arg.setting, '+') || n[0] == '-' ||
		ft_strchr(arg.setting, ' '))
		&& (!ft_strchr(arg.setting, '0') || arg.accur != -1))
	{
		if (n[0] == '-')
			ft_strncat(*res, "-", 1);
		else
			ft_strncat(*res, (ft_strchr(arg.setting, '+')
						? "+" : " "), 1);
	}
	while (accur-- > (int)ft_strlen((n[0] == '-') ? n + 1 : n) +
			(ft_strchr(arg.setting, '+') || ft_strchr(arg.setting, ' ')
			|| n[0] == '-'))
		ft_strncat(*res, "0", 1);
	if (!ft_strchr(arg.setting, '.') || arg.accur > 0 ||
			arg.data_numb != 0)
		ft_strcat(*res, (n[0] == '-') ? n + 1 : n);
}

void	dop_d2(t_arg arg, char *n, int accur, char **res)
{
	accur += (ft_strchr(arg.setting, '+') || n[0] == '-' ||
		ft_strchr(arg.setting, ' ')) && (!ft_strchr(arg.setting, '0') ||
		arg.accur != -1) ? 1 : 0;
	if ((ft_strchr(arg.setting, '+') || n[0] == '-' ||
		ft_strchr(arg.setting, ' '))
		&& (ft_strchr(arg.setting, '0') && arg.accur == -1))
	{
		if (n[0] == '-')
			ft_strncat(*res, "-", 1);
		else
			ft_strncat(*res, (ft_strchr(arg.setting, '+')
						? "+" : " "), 1);
	}
	while (arg.width + (arg.accur <= 0 && arg.data_numb == 0) > accur &&
			arg.width-- + (arg.accur <= 0 && arg.data_numb == 0) >
			(int)ft_strlen((n[0] == '-') ? n + 1 : n) +
			((ft_strchr(arg.setting, '+') || ft_strchr(arg.setting, ' ')
			|| n[0] == '-') && accur <= (int)ft_strlen(n) + (n[0] == '-')))
		ft_strncat(*res, (ft_strchr(arg.setting, '0') &&
					arg.accur == -1 ? "0" : " "), 1);
	dop_d4(arg, n, accur, res);
}

void	dop_d3(t_arg arg, char *n, char **res)
{
	if (ft_strchr(arg.setting, '+') || n[0] == '-' ||
		ft_strchr(arg.setting, ' '))
	{
		if (n[0] == '-')
			ft_strncat(*res, "-", 1);
		else
			ft_strncat(*res, (ft_strchr(arg.setting, '+')
						? "+" : " "), 1);
	}
	if (!ft_strchr(arg.setting, '.') || arg.accur > 0 || arg.data_numb != 0)
		ft_strcat(*res, (n[0] == '-' ? n + 1 : n));
}

char	*create_d(t_arg arg)
{
	char			*res;
	char			*n;
	int				size;
	int				accur;

	n = ft_itoa_base(arg.data_numb, 10);
	accur = arg.accur;
	if (arg.width > arg.accur)
		size = arg.width;
	else
		size = (arg.accur >= (int)ft_strlen(n)
				? arg.accur : ft_strlen(n) + ((ft_strchr(arg.setting, '+') ||
				ft_strchr(arg.setting, ' ') || n[0] == '-')));
	res = ft_strnew(size);
	if (arg.width > (int)ft_strlen(n) || arg.accur > (int)ft_strlen(n))
	{
		if (ft_strchr(arg.setting, '-'))
			dop_d1(arg, n, accur, &res);
		else
			dop_d2(arg, n, accur, &res);
	}
	else
		dop_d3(arg, n, &res);
	free(n);
	return (res);
}
