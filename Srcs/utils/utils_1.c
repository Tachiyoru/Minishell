/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:25:35 by sleon             #+#    #+#             */
/*   Updated: 2023/02/08 18:51:06 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strncmp(char *a, char *b, size_t l)
{
	size_t	i;

	i = 0;
	while ((a[i] || b[i]) && i < l)
	{
		if (a[i] != b[i])
			return (((unsigned char *)a)[i] - ((unsigned char *)b)[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen( char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	msg(char *str)
{
	size_t	i;

	i = 0;
	i = ft_strlen(str);
	write(2, str, i);
	write(2, "\n", 1);
}

void	*ft_memset(void *a, int i, size_t count)
{
	size_t			s;
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
