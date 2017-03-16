/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 17:06:52 by liabanzh          #+#    #+#             */
/*   Updated: 2017/03/16 17:06:54 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		delete_all(t_arg *map, char *ptr, int res, int count)
{
	ft_putstr(ptr);
	res += ft_strlen(ptr);
	delete_data(map, count);
	free(map);
	return (res);
}

void	delete_data(t_arg *map, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		if (ft_strchr(map[i].type, 's'))
		{
			if (map[i].data)
				free(map[i].data);
		}
		if (ft_strchr(map[i].type, 'S') || ft_strnstr(map[i].type, "ls", 3))
		{
			if (map[i].unidata)
				free(map[i].unidata);
		}
		if (ft_strlen(map[i].type))
			free(map[i].type);
		if (ft_strlen(map[i].setting))
			free(map[i].setting);
		i++;
	}
}
