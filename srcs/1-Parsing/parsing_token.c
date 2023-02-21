/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:05:48 by sleon             #+#    #+#             */
/*   Updated: 2023/02/21 16:27:37 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// WORD = Si c'est pas autre choses c'est un mot
// FD = always after < > << >>
// LIMITOR = Cat du HDOC le mot apres et le limiteur || voir si autre cas
// R_IN = Redirection in donc <
// HDOC (HEREDOC)= Redirection << [LIMITEUR]
// R_OUT = redirection out donc >
// APPEND = >>
// PIPE = |

void	token_error(char *val)
{
	g_error = 2;
	msg("syntax error near unexpected token `");
	msg(val);
	msg("'\n");
}

/**
 * @brief check if the parsing is correct and possible
 *
 * @param data linkchain
 * @return 0 if problem else 1
 */
int	good_parsing(t_val *data, int pre)
{
	t_val	*prev;

	prev = data;
	while (data)
	{
		if (prev->token == HEREDOC && data->token != LIMITOR)
			return (token_error(data->val), 0);
		if ((prev->token == R_OUT || prev->token == APPEND)
			&& data->token != FD)
			return (token_error(data->val), 0);
		if (data->token == PIPE && (prev->token == PIPE || prev->token == R_IN
				|| prev->token == APPEND || prev->token == HEREDOC))
			return (token_error(data->val), 0);
		if (data->token == PIPE && pre == -1)
			return (token_error(data->val), 0);
		pre = 0;
		prev = data;
		data = data->next;
	}
	if (!data)
		if (prev->token == PIPE || prev->token == R_IN || prev->token == R_OUT
			|| prev->token == APPEND || prev->token == HEREDOC)
			return (token_error(prev->val), 0);
	return (1);
}

/**
 * @brief determinate what the kind of token
 *
 * @param str the token
 * @param prev used for special case like limitor and fd
 * @return the matching one
 */
int	what_token(char *str, int prev)
{
	size_t	size;

	size = ft_strlen(str);
	if (size == 1)
	{
		if (*str == '<')
			return (R_IN);
		else if (*str == '>')
			return (R_OUT);
		else if (*str == '|')
			return (PIPE);
	}
	if (str[0] == '>' && str[1] == '>')
		return (APPEND);
	else if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else if (prev == HEREDOC)
		return (LIMITOR);
	else if (prev == APPEND || prev == R_OUT || prev == R_IN)
		return (FD);
	return (WORD);
}

void	print_list(t_val *data)
{
	while (data)
	{
		printf("%s - token = %d\n", data->val, data->token);
		data = data->next;
	}
}

/**
 * @brief go trhough the linkchain et set what kind of token it is
 *
 * @param data the linkchain
 */
void	check_token(t_val *data)
{
	t_val	*head;
	int		prev;

	prev = 0;
	head = data;
	while (head)
	{
		head->token = what_token(head->val, prev);
		prev = head->token;
		head = head->next;
	}
	if (!good_parsing(data, -1))
	{
		free_lst(data);
		return ;
	}
	quote_treatment(data);
}
