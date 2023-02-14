/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:25:35 by sleon             #+#    #+#             */
/*   Updated: 2023/02/14 16:09:45 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief print a message in stderror
 *
 * @param str
 */
void	msg(char *str)
{
	int	i;

	i = 0;
	i = ft_strlen(str);
	write(STDERR_FILENO, str, i);
	write(STDERR_FILENO, "\n", 1);
}

/**
 * @brief calculate he size of the string
 *
 * @param str string to  be mesured
 * @return the size
 */
int	ft_strlen( char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/**
 * @brief look for the char c in the string str
 *
 * @param str
 * @param c
 * @return 1 if the char is found in the str else 0
 */
int	ft_strchr(const char *str, int c)
{
	char	*s;

	s = (char *)str;
	if (*s == '\0')
		return (0);
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return (1);
	return (0);
}

/**
 * @brief set ever allocated space to 0
 *
 * @param a
 * @param i
 * @param count
 * @return void*
 */
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

/**
 * @brief allocate size spaces of nmemb size
 *
 * @param nmemb
 * @param size
 * @return void*
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*mem;

	mem = malloc(size * nmemb);
	if (!mem)
		return (NULL);
	ft_memset(mem, 0, nmemb * size);
	return (mem);
}
