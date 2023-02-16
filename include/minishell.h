/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:41:10 by sleon             #+#    #+#             */
/*   Updated: 2023/02/16 18:06:20 by sleon            ###   ########.fr       */
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

/////\ ENV \//////
t_env	**handle_env(char **env, char *add, char *delete);
t_env	**get_env(void);
void	del_from_env(char *delete);
void	add_to_env(char *add);
void	store_env(char **env);
t_env	*init_env2(char *env, t_env *env_s);
t_env	*ft_last_env(t_env **data);
t_env	*init_env(char **env);

void	print_list(t_val *data);

int		main(int ac, char **av, char **envp);

/////\ PARSING \//////
// --parsing_recursive utils--
void	check_token(t_val *data);

// --parsing_recursive utils--
t_val	*ft_last(t_val **data);
int		set_val_tab(char *str, t_val **data);
int		word_end(char *line, int start);
int		word_start(char *line);
// --parsing_recursive--
void	split_pars(char *buf);

/////\ exec \//////
void	add_word(t_pipex **exec, t_val **data);
void	add_redir(t_pipex **exec, t_val **data);
t_pipex	*ft_last_cmd(t_pipex **data);
int		init_cmd(t_pipex **cmd);
void	exec(t_val	*data);

void	set_redir_in(t_pipex *cmd);
void	set_redir_out(t_pipex *cmd);
void	set_redir_append(t_pipex *cmd);

void	setup_redir(t_pipex *cmd);
void	setup_pipe(t_pipex *cmd);

/////\ BUILTINS \//////

/////\ UTILS \//////
//free
void	free_lst(t_val	*data);
void	free_tab(char **tab);
//substr
char	*ft_substr(char *s, unsigned int start, size_t len);
//utils2
char	*ft_strdup(const char *s);
char	*word_replacing(int start, int end, char *content, char *new_word);
char	*var_replacing(int start, int end, char *content);
char	*ft_strndup(const char *s, int size);
int		ft_strcmp(const char *s1, const char *s2);

//utils
int		ft_strchr(const char *str, int c);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen( char *str);
void	msg(char *str);
char	*ft_itoa(int n);

// expand
int		quote_treatment(t_val *data);
t_val	*ft_lstnew_token(void *content, t_val *next);
int		quote_parsing(char *content, t_val *data);
int		is_var(char *content, int i, t_val *data);
int		expand_space(char *content, t_val *data);

#endif
