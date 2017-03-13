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

char	*create_d(t_arg arg)
{
	char			*res;
	char			*n;
	int				size;
	int				accur;

	n = ft_itoa_base(arg.data_numb, 10);
	accur = arg.accur;
 	size = (arg.width > arg.accur) ? arg.width : (arg.accur >= (int)ft_strlen(n)
 			? arg.accur : ft_strlen(n) + ((ft_strchr(arg.setting, '+') ||
			ft_strchr(arg.setting, ' ') || n[0] == '-')));
	res = ft_strnew(size);
	if (arg.width > (int)ft_strlen(n) || arg.accur > (int)ft_strlen(n))
	{
		if (ft_strchr(arg.setting, '-'))
		{
			if (ft_strchr(arg.setting, ' ') && !ft_strchr(arg.setting, '+') &&
				n[0] != '-')
				*res = ' ';
			if (ft_strchr(arg.setting, '+') || n[0] == '-')
				*res = (*n == '-') ? *n : '+';
			while (arg.accur-- > (int)ft_strlen(n))
				ft_strncat(res, "0", 1);
			if (!ft_strchr(arg.setting, '.') || arg.accur > 0 || arg.data_numb != 0)
				ft_strcat(res, (n[0] == '-' ? n + 1 : n));
			while (arg.width-- + (arg.accur <= 0 && arg.data_numb == 0) >
				(int)(ft_strlen((n[0] == '-') ? n + 1 : n) + (ft_strchr(arg.setting, '+')
				|| ft_strchr(arg.setting, ' ') || n[0] == '-') +
				(((int)ft_strlen(n) >= accur) ? 0 : (accur - ft_strlen(n)))))
				ft_strncat(res, " ", 1);
		}
		else
		{
			accur += (ft_strchr(arg.setting, '+') || n[0] == '-' ||
				ft_strchr(arg.setting, ' ')) && (!ft_strchr(arg.setting, '0') ||
				arg.accur != -1) ? 1 : 0;
			if ((ft_strchr(arg.setting, '+') || n[0] == '-' ||
				ft_strchr(arg.setting, ' '))
				&& (ft_strchr(arg.setting, '0') && arg.accur == -1))
				ft_strncat(res, (n[0] == '-') ? "-" : (ft_strchr(arg.setting, '+')
					? "+" : " "), 1);
			while (arg.width + (arg.accur <= 0 && arg.data_numb == 0) > accur &&
				arg.width-- + (arg.accur <= 0 && arg.data_numb == 0) > (int)ft_strlen((n[0] == '-')
				? n + 1 : n) + ((ft_strchr(arg.setting, '+') || ft_strchr(arg.setting, ' ')
					|| n[0] == '-') && accur <= (int)ft_strlen(n) + (n[0] == '-')))
				ft_strncat(res, (ft_strchr(arg.setting, '0') && arg.accur == -1 ?
					"0" : " "), 1);
			if ((ft_strchr(arg.setting, '+') || n[0] == '-' ||
				ft_strchr(arg.setting, ' '))
				&& (!ft_strchr(arg.setting, '0') || arg.accur != -1))
				ft_strncat(res, (n[0] == '-') ? "-" :
					(ft_strchr(arg.setting, '+') ? "+" : " "), 1);
			while (accur-- > (int)ft_strlen((n[0] == '-') ? n + 1 : n) +
				(ft_strchr(arg.setting, '+') || ft_strchr(arg.setting, ' ') || n[0] == '-'))
				ft_strncat(res, "0", 1);
			if (!ft_strchr(arg.setting, '.') || arg.accur > 0 || arg.data_numb != 0)
				ft_strcat(res, (n[0] == '-') ? n + 1 : n);
		}
	}
	else
	{
		if (ft_strchr(arg.setting, '+') || n[0] == '-' ||
			ft_strchr(arg.setting, ' '))
			ft_strncat(res, (n[0] == '-') ? "-" : (ft_strchr(arg.setting, '+')
				? "+" : " "), 1);
		if (!ft_strchr(arg.setting, '.') || arg.accur > 0 || arg.data_numb != 0)
			ft_strcat(res, (n[0] == '-' ? n + 1 : n));
	}
	free(n);
	return (res);
}

char	*create_s(t_arg arg)
{
	char			*res;
	int				accur;

	if (arg.data == NULL)
		ft_strncpy((arg.data = ft_strnew(6)), "(null)", 6);
	accur = (arg.accur < 0 || arg.accur > (int)ft_strlen(arg.data))
			? ft_strlen(arg.data) : arg.accur;
	res = ft_strnew(((int)ft_strlen(arg.data) >= arg.width) ?
			(int)ft_strlen(arg.data) : arg.width);
	if (arg.width > accur)
	{
		if (ft_strchr(arg.setting, '-'))
		{
			ft_strncat(res, arg.data, accur);
			while (arg.width-- > accur)
				ft_strncat(res, " ", 1);
		}
		else
		{
			while (arg.width-- > accur)
				ft_strncat(res, (ft_strchr(arg.setting, '0') ? "0" : " "), 1);
			ft_strncat(res, arg.data, accur);
		}
	}
	else
		ft_strncpy(res, arg.data, accur);
	return (res);
}

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
	ft_strncat(n, "0x", 2);
	ft_strcat(n, ft_itoa_base(arg.data_numb, 16));
	res = ft_strnew((arg.width > (int)ft_strlen(n)) ? arg.width : ft_strlen(n));
	if (arg.width <= (int)ft_strlen(n))
		return (n);
	else
	{
		if (ft_strchr(arg.setting, '-'))
		{
			if (arg.data_numb != 0 || arg.accur > 0)
				ft_strcat(res, n);
			while (arg.width-- > (int)ft_strlen(n))
				ft_strncat(res, " ", 1);
		}
		else
		{
			while (arg.width-- > (int)ft_strlen(n))
				ft_strncat(res, " ", 1);
			if (arg.data_numb != 0 || arg.accur > 0)
				ft_strcat(res, n);
		}
	}
	free(n);
	return (res);
}

size_t	wild_len(wchar_t wchar)
{
	if (wchar > 0 && wchar < 127)
		return (1);
	else if (wchar > 128 && wchar < 2047)
		return (2);
	else if (wchar > 2048 && wchar < 65535)
		return (3);
	else if (wchar > 65536 && wchar < 2097151)
		return (4);
	else if (wchar > 2097152 && wchar < 67108863)
		return (5);
	else
		return (6);
}

char	*wild(wchar_t wchar)
{
	char	*s;
	size_t	len;
	size_t	n;

	len = wild_len(wchar);
	s = ft_strnew(len + 1);
	if (len == 1)
	{
		*s = (char)wchar;
		return (s);
	}
	n = len;
	while (n)
	{
		if (n != 1)
		{
			*(s + (n - 1)) = wchar % 64 + 128;
			wchar >>= 6;
		}
		n--;
	}
	*s = ft_power(2, 8) - ft_power(2, 8 - len) + wchar;
	return (s);
}

char	*create_w(wchar_t *str)
{
	char	*res;
	int 	i;
	char	*tmp;

	res = ft_strnew(ft_strlen((const char*)str));
	i = 0;
	while (str[i] != 0)
	{
		tmp = wild(str[i]);
		ft_strcat(res, tmp);
		i++;
	}
	return (res);
}
