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

char	*create_un(t_arg arg, int base)
{
	char			*res;
	char			*n;
	int				len;
	int				accur;

	n = ft_itoa_base_u(arg.undata, base);
	len = ft_strlen(n);
	res = ft_strnew(((arg.width >= arg.accur && arg.width >= len) ?
				arg.width : (arg.accur >= len) ? arg.accur : len) +
				(ft_strchr(arg.setting, '#') ? 2 : 0));
	accur = arg.accur;
	if (arg.width > len || arg.accur > len)
	{
		if (ft_strchr(arg.setting, '-'))
		{
			if (ft_strchr(arg.setting, '#') && (ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X') || ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O')))
 				ft_strncat(res, (ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X')) && arg.undata != 0 ? "0x" : (ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O') ? "0" : ""), 2);
			while (arg.accur-- > len + ((ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X')) && ft_strchr(arg.setting, '#') ? 2 : (ft_strchr(arg.setting, '#') && (ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O')) ? 1 : 0)))
				ft_strncat(res, "0", 1);
			if (!ft_strchr(arg.setting, '.') || arg.accur > 0 || arg.undata != 0)
				ft_strcat(res, n);
			while (arg.width-- + (arg.accur <= 0 && arg.undata == 0) > ((accur > len) ? accur : len) + ((ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X')) && ft_strchr(arg.setting, '#') ? 2 : (ft_strchr(arg.setting, '#') && (ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O')) ? 1 : 0)))
				ft_strncat(res, " ", 1);
		}
		else
		{
			if (ft_strchr(arg.setting, '0') && arg.undata != 0 && accur == -1 && ft_strchr(arg.setting, '#') && (ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X') || ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O')))
				ft_strncat(res, ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X') ? "0x" : "0", 2);
			while (arg.width-- + (arg.accur <= 0 && arg.undata == 0) > ((accur > len) ? accur : len) + ((ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X')) && ft_strchr(arg.setting, '#') ? 2 : (ft_strchr(arg.setting, '#') && (ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O')) ? 1 : 0)))
				ft_strncat(res, (ft_strchr(arg.setting, '0') && accur == -1) ? "0" : " ", 1);
			if (!ft_strchr(arg.setting, '0') && ft_strchr(arg.setting, '#') && (ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X') || ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O')))
 				ft_strncat(res, (ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X')) && arg.undata != 0 ? "0x" : (ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O') ? "0" : ""), 2);
			while (arg.accur-- > len)
				ft_strncat(res, "0", 1);
			if (!ft_strchr(arg.setting, '.') || arg.accur > 0 || arg.undata != 0)
				ft_strcat(res, n);
		}
 	}
 	else
 	{
 		if ((ft_strchr(arg.setting, '#') && (arg.undata != 0 || (ft_strchr(arg.setting, '.') && arg.accur <= 0))) && (ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X') || ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O')))
 			ft_strncat(res, (ft_strchr(arg.type, 'x') || ft_strchr(arg.type, 'X')) && arg.undata != 0 ? "0x" : (ft_strchr(arg.type, 'o') || ft_strchr(arg.type, 'O') ? "0" : ""), 2);
 		if (!ft_strchr(arg.setting, '.') || arg.accur > 0 || arg.undata != 0)
			ft_strcat(res, n);
 	}
 	free(n);
	return (res);
}
