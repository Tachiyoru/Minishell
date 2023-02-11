/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:25:35 by sleon             #+#    #+#             */
/*   Updated: 2023/02/11 13:04:02 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strlen2( char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr(const char *str, int c)
{
	char	*s;

	s = (char *)str;
	if (*s == '\0')
		return (0);
	while (*s != (char)c)
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	return (0);
}

void	msg(char *str)
{
	int	i;

	i = 0;
	i = ft_strlen2(str);
	write(2, str, i);
	write(2, "\n", 1);
}

void	*ft_memset(void *a, int i, int count)
{
	int				s;
	unsigned char	*ptr;

	s = 0;
	ptr = (unsigned char *)a;
	while (s < count)
		ptr[s++] = (unsigned char)i;
	return (a);
}

//MEMO simplife calloc et memset en 1 si possible

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*mem;

	mem = malloc(size * nmemb);
	if (!mem)
		return (NULL);
	ft_memset(mem, 0, nmemb * size);
	return (mem);
}
