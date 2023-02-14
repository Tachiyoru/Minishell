/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:41:10 by sleon             #+#    #+#             */
/*   Updated: 2023/02/14 15:57:01 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <signal.h>
# include <wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

extern int					g_error;

typedef struct s_pipex		t_pipex;
typedef enum e_fd			t_fd;
typedef struct s_val		t_val;
typedef struct s_env		t_env;

enum e_token
{
	WORD,
	R_IN,
	FD,
	R_OUT,
	LIMITOR,
	HEREDOC = 6,
	APPEND = 8,
	PIPE = 10,
};

struct s_env{
	char	*key;
	char	*val;
	t_env	*next;
};

struct s_val{
	char	*val;
	int		token;
	t_val	*next;
};

struct s_pipex
{
	pid_t	pid;
	int		fd[2];
	t_val	*cmd;
	t_val	*redir;
	t_pipex	*next;
};

void	print_list(t_val *data);

int		main(int ac, char **av, char **envp);

/////\ PARSING \//////
// --parsing_recursive utils--
void	check_token(t_val *data);

// --parsing_recursive utils--
int		set_val_tab(char *str, t_val **data);
int		word_end(char *line, int start);
int		word_start(char *line);
// --parsing_recursive--
void	split_pars(char *buf);

/////\ BUILTINS \//////

/////\ UTILS \//////
//free
void	free_lst(t_val	*data);
void	free_tab(char **tab);
//substr
char	*ft_substr(char const *s, unsigned int start, size_t len);
//utils2
char	*ft_strdup(const char *s);
char	*word_replacing(int start, int end, char *content, char *new_word);
char	*var_replacing(int start, int end, char *content, t_env *env);
//utils
int		ft_strchr(const char *str, int c);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen( char *str);
void	msg(char *str);

#endif
