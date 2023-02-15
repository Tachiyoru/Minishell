/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:06:40 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/15 23:24:49 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>

static long	absolute_maker(long n)
{
	if (n < 0)
		n = n * -1;
	return (n);
}

static void	transformation(long nb, int len, char *dest)
{
	while (nb > 9)
	{
		dest[len] = (nb % 10) + 48;
		nb = nb / 10;
		len--;
	}
	dest[len] = (nb % 10) + 48;
}

char	*ft_itoa(int n)
{
	char	*dest;
	long	nb;
	int		len;

	len = 0;
	nb = absolute_maker((long)n);
	while (nb > 9)
	{
		nb /= 10;
		len++;
	}
	len++;
	if (n < 0)
		len++;
	dest = malloc(sizeof(*dest) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	nb = absolute_maker((long)n);
	transformation(nb, len - 1, dest);
	if (n < 0)
		dest[0] = '-';
	return (dest);
}
