/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 15:04:17 by liabanzh          #+#    #+#             */
/*   Updated: 2017/02/13 15:04:22 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		main(void)
{
	// int i1 = 0;
	// int i2 = 0;
	// i1 = ft_printf("STRING - |%+13.10d|%jx|%5%|%-20s|%5c|\n", -1234567, -4294967296, NULL, 63);
	// i2 = printf("STRING - |%+13.10d|%jx|%5%|%-20s|%5c|\n", -1234567, -4294967296, NULL, 63);
	// printf("\nRETURN VALUE = %d\n", i1);
	// printf("RETURN VALUE = %d\n", i2);
	ft_printf("|%Z|\n");
	return (0);
}
