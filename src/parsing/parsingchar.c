/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:33:17 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 18:33:17 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/// @brief it loops through the input string and checks for double quotes,
///        dollar signs and spaces
/// @param shell 
/// @return 
int	parse_double_quotes(t_shell *shell)
{
	shell->i++;
	while (shell->input[shell->i] && shell->input[shell->i] != '\"')
	{
		append_checker(shell);
		if (shell->input[shell->i] == '$' && shell->input[shell->i + 1] != ' '
			&& shell->input[shell->i + 1] != '\"' )
			parse_dollar(shell);
		shell->i++;
	}
	shell->typeflag = DQUOTES;
	return (1);
}

/// @brief it loops through the input string and checks for single quotes
int	parse_single_quotes(t_shell *shell)
{
	shell->i++;
	while (shell->input[shell->i] && shell->input[shell->i] != '\'')
	{
		append_checker(shell);
		shell->i++;
	}
	shell->typeflag = SQUOTES;
	return (1);
}

/// @brief it loops through the input string and checks for '<<' and '<'
///         and adds the token to the tokens list
int	parse_in(t_shell *shell)
{
	shell->checker[ft_strlen(shell->checker) - 1] = '\0';
	if (shell->i > 0 && ft_strlen(shell->checker) != 0
		&& shell->input[shell->i - 1] != ' ' && shell->input[shell->i - 1] != '\t')
		add_token_from_checker(shell, WORD, &shell->checker);
	if (shell->input[shell->i + 1] == '<')
	{
		shell->i++;
		if (shell->checker)
			free(shell->checker);
		shell->checker = ft_strdup("<<");
		add_token_from_checker(shell, HEREDOC, &shell->checker);
	}
	else
	{
		if (shell->checker)
			free(shell->checker);
		shell->checker = ft_strdup("<");
		add_token_from_checker(shell, FD_IN, &shell->checker);
	}
	return (1);
}

/// @brief it loops through the input string and checks for '>>' and '>'
int	parse_out(t_shell *shell)
{
	shell->checker[ft_strlen(shell->checker) - 1] = '\0';
	if (shell->i > 0 && ft_strlen(shell->checker) != 0
		&& shell->input[shell->i - 1] != ' ' && shell->input[shell->i - 1] != '\t')
		add_token_from_checker(shell, WORD, &shell->checker);
	if (shell->input[shell->i + 1] == '>')
	{
		shell->i++;
		if (shell->checker)
			free(shell->checker);
		shell->checker = ft_strdup(">>");
		add_token_from_checker(shell, APPEND, &shell->checker);
	}
	else
	{
		if (shell->checker)
			free(shell->checker);
		shell->checker = ft_strdup(">");
		add_token_from_checker(shell, FD_OUT, &shell->checker);
	}
	return (1);
}

/// @brief it loops through the input string and checks for spaces
int	parse_space(t_shell *shell)
{
	if (ft_strlen(shell->checker) == 1
		&& (ft_strrchr(shell->checker, ' ') || ft_strrchr(shell->checker, '\t')))
	{
		if (shell->checker)
			free(shell->checker);
		shell->checker = ft_strdup("");
		return (0);
	}
	if (ft_strlen(shell->input) - 1 > shell->i || shell->input[shell->i] == ' '
		|| shell->input[shell->i] == '\t')
		shell->checker[ft_strlen(shell->checker) - 1] = '\0';
	return (1);
}
