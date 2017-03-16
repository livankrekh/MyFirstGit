/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_w.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:53:59 by liabanzh          #+#    #+#             */
/*   Updated: 2017/03/16 16:54:00 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			wild_len(wchar_t wchar)
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

void			unicode_to_utf8_subf(wchar_t c, unsigned char **b)
{
	**b++ = (unsigned char)(((c >> 18)) | 0xF0);
	**b++ = (unsigned char)(((c >> 12) & 0x3F) | 0x80);
	**b++ = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
	**b++ = (unsigned char)((c & 0x3F) | 0x80);
	return ;
}

const char		*unicode_to_utf8(wchar_t c)
{
	static unsigned char	b_static[5];
	unsigned char			*b;

	b = b_static;
	if (c < (1 << 7))
		*b++ = (unsigned char)(c);
	else if (c < (1 << 11))
	{
		*b++ = (unsigned char)((c >> 6) | 0xC0);
		*b++ = (unsigned char)((c & 0x3F) | 0x80);
	}
	else if (c < (1 << 16))
	{
		*b++ = (unsigned char)(((c >> 12)) | 0xE0);
		*b++ = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
		*b++ = (unsigned char)((c & 0x3F) | 0x80);
	}
	else if (c < (1 << 21))
		unicode_to_utf8_subf(c, &b);
	*b = '\0';
	return (const char*)b_static;
}

char			*create_w(const wchar_t *str)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	if (str == NULL)
		return ("(null)");
	res = ft_strnew(ft_strlen((char*)str) * 6);
	while (str[i] != '\0')
	{
		tmp = (char*)unicode_to_utf8(str[i]);
		ft_strncat(res, tmp, wild_len(str[i]));
		ft_strclr(tmp);
		i++;
	}
	return (res);
}
