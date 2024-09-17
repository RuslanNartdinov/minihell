/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:09:43 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 18:31:05 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h> 
# include <limits.h>
# include <signal.h>
//temp
# include <string.h>
# include <termios.h>

# include "define.h"

/// Aliases
typedef struct s_token	t_token;
typedef struct s_env	t_env;

/// @brief it is the structure of the environment variables
/// @content it is the content of the environment variable
/// @key it is the key of the environment variable
/// @value it is the value of the environment variable
/// @hide it is the flag to hide the environment variable
struct s_env
{
	char			*content;
	char			*key;
	char			*value;
	int				hide;
	struct s_env	*next;
};

/// @brief it is the structure of the tokens
/// @content it is the content of the token
/// @type it is the type of the token
struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
};

/// @brief it is the structure of the shell
/// @input it is the input of the shell
/// @checker it is the checker of the shell
/// @temp it is the temp of the shell
/// @temp2 it is the temp2 of the shell
/// @tempkey it is the tempkey of the shell
/// @tempvalue it is the tempvalue of the shell
/// @j it is the j of the shell
/// @typeflag it is the typeflag of the shell
/// @sflag it is the sflag of the shell
/// @envp it is the environment variables
/// @myenvstr it is the environment variables in array
/// @enviro it is the environment variables in linked list
/// @tokens it is the tokens
/// @currtoken it is the current token
/// @i it is the i of the shell
/// @status it is the status of the shell
typedef struct s_shell
{
	char			*input;
	char			*checker;
	char			*temp;
	char			*temp2;
	char			*tempkey;
	char			*tempvalue;
	int				j;
	int				typeflag;
	int				sflag;
	char			**envp;
	char			**myenvstr;
	t_env			*enviro;
	t_token			*tokens;
	t_token			*currtoken;
	unsigned int	i;
	int				status;
}	t_shell;

/// @brief it is the structure of the commands
/// @command it is the command
/// @fd_in it is the input file descriptor
/// @fd_out it is the output file descriptor
/// @fd_type it is the file descriptor type
/// @is_bcommand it is the flag to check if it is a built-in command
typedef struct s_command
{
	char				**command;
	int					fd_in;
	int					fd_out;
	int					fd_type;
	int					is_bcommand;
	struct s_command	*next;
}	t_command;

//initializing
void	data_init(t_shell *shell);
void	pre_init(t_shell *shell, char **envp);
void	env_init(t_shell *shell);
t_env	*ft_envlast(t_env *env);
t_env	*ft_envnew(char *word, int hide);
int		ft_envsize(t_env *env);
void	ft_envadd_back(t_env **env, char *s, int hide);
void	ft_envclear(t_env **env);
void	set_exitstatus(t_shell *shell);
void	add_to_env(t_shell *shell, char *str, int hide, int sethide);
void	incr_shlvl(t_shell *shell);
void	free_split_from(char **split, int from);
void	set_pwd(t_shell *shell);
char	**env_to_array(t_env *enviro);
void		rl_replace_line(const char *s, int c);
//parsing
void	parser(t_shell *shell);
void	append_checker(t_shell *shell);
void	append_checker_char(t_shell *shell, int c);
int		check_string(t_shell *shell);
void	add_token_from_checker(t_shell *shell, int type, char **str);
void	add_token_to_env(t_shell *shell);
int		check_env_dupes(t_shell *shell, char *str, int sethide);
char	*get_env_value(t_shell *shell, char *key);
int		parse_double_quotes(t_shell *shell);
int		parse_single_quotes(t_shell *shell);
int		parse_in(t_shell *shell);
int		parse_out(t_shell *shell);
int		parse_space(t_shell *shell);
int		parse_pipe(t_shell *shell);
int		parse_dollar(t_shell *shell);
int		is_valid_key(char *str);
void	set_type(t_shell *shell);

//utils
int		ft_isalnum(int c);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
void	ft_strcpy(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
void	*ft_memset(void *str, int x, size_t n);

//lst utils
t_token	*ft_lstnew(char *word);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstclear(t_shell *lst);

//exec
void	exec_line(t_shell *shell);
void	free_args(char **args);
char	*ft_get_cmd_path(char *cmd, char **envp);

//getnext line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;
char	*concatenate_list(t_list **lst);
void	ft_gnlclear(t_list **lst);
void	close_std(void);
void	set_filename(t_token *tokens);

#endif