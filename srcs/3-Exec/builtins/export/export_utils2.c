/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:46:38 by ajeanne           #+#    #+#             */
/*   Updated: 2023/03/22 17:24:39 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rem_whitespace_export(char *value)
{
	int		i;
	int		j;
	char 	*dest;
	
	if (!value)
		return (NULL);
	i = 0;
	j = ft_strlen(value) - 1;
	while (value && value[i] && (value[i] == '9' || value[i] == 32))
		i++;
	while (value && value[j] && (value[j] == '9' || value[j] == 32))
		j--;
	dest = ft_substr(value, i, j - i + 1);
	if (!dest)
		return (NULL);
	return (dest);
}