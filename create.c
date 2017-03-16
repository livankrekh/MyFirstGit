/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 14:08:51 by liabanzh          #+#    #+#             */
/*   Updated: 2017/02/18 14:08:53 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dop_s(t_arg arg, int accur, char **res)
{
	while (arg.width-- > accur)
		ft_strncat(*res, (ft_strchr(arg.setting, '0') ? "0" : " "), 1);
	ft_strncat(*res, arg.data, accur);
}

char	*create_s(t_arg arg)
{
	char			*res;
	int				accur;

	if (arg.data == NULL)
		ft_strncpy((arg.data = ft_strnew(6)), "(null)", 6);
	accur = (arg.accur < 0 || arg.accur > (int)ft_strlen(arg.data))
			? ft_strlen(arg.data) : arg.accur;
	res = ft_strnew((arg.width > accur) ? arg.width : accur);
	if (arg.width > accur)
	{
		if (ft_strchr(arg.setting, '-'))
		{
			ft_strncat(res, arg.data, accur);
			while (arg.width-- > accur)
				ft_strncat(res, " ", 1);
		}
		else
			dop_s(arg, accur, &res);
	}
	else
		ft_strncpy(res, arg.data, accur);
	return (res);
}

char	*create_c(t_arg arg)
{
	char	*res;

	res = ft_strnew((arg.width > 1) ? arg.width : 1);
	if (arg.width > 1)
	{
		if (ft_strchr(arg.setting, '-'))
		{
			res[0] = (char)arg.data_numb;
			while (arg.width-- > 1)
				ft_strncat(res, " ", 1);
		}
		else
		{
			while (arg.width-- > 1)
				ft_strncat(res, (ft_strchr(arg.setting, '0') ? "0" : " "), 1);
			res[ft_strlen(res)] = (char)arg.data_numb;
		}
	}
	else
		res[0] = (char)arg.data_numb;
	return (res);
}

char	*create_pointer(t_arg arg)
{
	char	*res;
	char	*n;

	n = ft_strnew(ft_strlen(ft_itoa_base(arg.data_numb, 16)) + 2);
	ft_strcat(ft_strncat(n, "0x", 2), ft_itoa_base(arg.data_numb, 16));
	res = ft_strnew((arg.width > (int)ft_strlen(n)) ? arg.width : ft_strlen(n));
	if (arg.width <= (int)ft_strlen(n))
		return (n);
	else
	{
		if (ft_strchr(arg.setting, '-'))
		{
			ft_strcat(res, (arg.data_numb != 0 || arg.accur > 0) ? n : "");
			while (arg.width-- > (int)ft_strlen(n))
				ft_strncat(res, " ", 1);
		}
		else
		{
			while (arg.width-- > (int)ft_strlen(n))
				ft_strncat(res, " ", 1);
			ft_strcat(res, (arg.data_numb != 0 || arg.accur > 0) ? n : "");
		}
	}
	free(n);
	return (res);
}
