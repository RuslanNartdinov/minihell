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
	shell->iter++;
	while (shell->input[shell->iter] && shell->input[shell->iter] != '\"')
	{
		append_checker(shell);
		if (shell->input[shell->iter] == '$'
			&& shell->input[shell->iter + 1] != ' '
			&& shell->input[shell->iter + 1] != '\"' )
			parse_dollar(shell);
		shell->iter++;
	}
	shell->type_flag = 19;
	return (1);
}

/// @brief it loops through the input string and checks for single quotes
int	parse_single_quotes(t_shell *shell)
{
	shell->iter++;
	while (shell->input[shell->iter] && shell->input[shell->iter] != '\'')
	{
		append_checker(shell);
		shell->iter++;
	}
	shell->type_flag = 20;
	return (1);
}

/// @brief it loops through the input string and checks for '<<' and '<'
///         and adds the token to the tokens list
int	parse_in(t_shell *shell)
{
	shell->checker[ft_strlen(shell->checker) - 1] = '\0';
	if (shell->iter > 0 && ft_strlen(shell->checker) != 0
		&& shell->input[shell->iter - 1] != ' '
		&& shell->input[shell->iter - 1] != '\t')
		add_token_from_checker(shell, 0, &shell->checker);
	if (shell->input[shell->iter + 1] == '<')
	{
		shell->iter++;
		if (shell->checker)
			free(shell->checker);
		shell->checker = ft_strdup("<<");
		add_token_from_checker(shell, 15, &shell->checker);
	}
	else
	{
		if (shell->checker)
			free(shell->checker);
		shell->checker = ft_strdup("<");
		add_token_from_checker(shell, 12, &shell->checker);
	}
	return (1);
}

/// @brief it loops through the input string and checks for '>>' and '>'
int	parse_out(t_shell *shell)
{
	shell->checker[ft_strlen(shell->checker) - 1] = '\0';
	if (shell->iter > 0 && ft_strlen(shell->checker) != 0
		&& shell->input[shell->iter - 1] != ' '
		&& shell->input[shell->iter - 1] != '\t')
		add_token_from_checker(shell, 0, &shell->checker);
	if (shell->input[shell->iter + 1] == '>')
	{
		shell->iter++;
		if (shell->checker)
			free(shell->checker);
		shell->checker = ft_strdup(">>");
		add_token_from_checker(shell, 14, &shell->checker);
	}
	else
	{
		if (shell->checker)
			free(shell->checker);
		shell->checker = ft_strdup(">");
		add_token_from_checker(shell, 13, &shell->checker);
	}
	return (1);
}

/// @brief it loops through the input string and checks for spaces
int	parse_space(t_shell *shell)
{
	if (ft_strlen(shell->checker) == 1
		&& (ft_strrchr(shell->checker, ' ')
			|| ft_strrchr(shell->checker, '\t')))
	{
		if (shell->checker)
			free(shell->checker);
		shell->checker = ft_strdup("");
		return (0);
	}
	if (ft_strlen(shell->input) - 1 > shell->iter
		|| shell->input[shell->iter] == ' '
		|| shell->input[shell->iter] == '\t')
		shell->checker[ft_strlen(shell->checker) - 1] = '\0';
	return (1);
}
