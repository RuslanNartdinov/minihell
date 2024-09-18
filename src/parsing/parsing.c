/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:33:09 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 18:33:09 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/// @brief it parses the input string, it checks for quotes, spaces,
///        pipes, redirections and dollar signs
/// @param shell 
void	parser(t_shell *shell)
{
	while (shell->input[shell->i])
	{
		if (shell->input[shell->i] == '\"')
			parse_double_quotes(shell);
		else if (shell->input[shell->i] == '\'')
			parse_single_quotes(shell);
		else
		{
			append_checker(shell);
			if (check_string(shell))
				add_token_from_checker(shell, shell->typeflag, &shell->checker);
		}
		shell->i++;
	}
	add_token_from_checker(shell, shell->typeflag, &shell->checker);
	if (shell->checker)
		free(shell->checker);
}

/// @brief it appends the current character to the checker
void	append_checker(t_shell *shell)
{
	size_t	checker_len;
	size_t	new_size;

	checker_len = ft_strlen(shell->checker);
	new_size = checker_len + 2;
	shell->temp = malloc(new_size);
	if (!shell->temp)
	{
		perror("malloc");
		exit(1);
	}
	ft_strcpy(shell->temp, shell->checker);
	shell->temp[checker_len] = shell->input[shell->i];
	shell->temp[checker_len + 1] = 0;
	if (shell->checker)
		free(shell->checker);
	shell->checker = shell->temp;
}
/// @brief it adds the current token to the tokens list 
/// @param shell 
/// @param type 
/// @param str 
void	add_token_from_checker(t_shell *shell, int type, char **str)
{
	t_token	*curr;

	if (ft_strlen(*str) > 0)
	{
		curr = ft_lstnew(*str);
		curr->type = type;
		ft_lstadd_back(&shell->tokens, curr);
		if (*str)
			free(*str);
		*str = ft_strdup("");
		shell->typeflag = 0;
	}
}

/// @brief it appends the current character to the checker
void	append_checker_char(t_shell *shell, int c)
{
	size_t	checker_len;
	size_t	new_size;

	checker_len = ft_strlen(shell->checker);
	new_size = checker_len + 2;
	shell->temp = malloc(new_size);
	if (!shell->temp)
	{
		perror("malloc");
		exit(1);
	}
	ft_strcpy(shell->temp, shell->checker);
	shell->temp[checker_len] = c;
	shell->temp[checker_len + 1] = 0;
	if (shell->checker)
		if (shell->checker)
			free(shell->checker);
	shell->checker = shell->temp;
}

/// @brief it checks the current character and returns the type of the token
int	check_string(t_shell *shell)
{
	if (shell->input[shell->i] == '<')
		return (parse_in(shell));
	else if (shell->input[shell->i] == '>')
		return (parse_out(shell));
	else if (shell->input[shell->i] == '|')
		return (parse_pipe(shell));
	else if (shell->input[shell->i] == '$')
		return (parse_dollar(shell));
	else if (shell->input[shell->i] == ' ' || shell->input[shell->i] == '\t'
		|| ft_strlen(shell->input) - 1 <= shell->i)
		return (parse_space(shell));
	return (0);
}
