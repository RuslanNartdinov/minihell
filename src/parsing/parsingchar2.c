/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingchar2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:01:00 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 18:33:25 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_pipe(t_shell *shell)
{
	shell->checker[ft_strlen(shell->checker) - 1] = '\0';
	if (shell->i > 0 && ft_strlen(shell->checker) != 0
		&& shell->input[shell->i - 1] != ' ' && shell->input[shell->i - 1] != '\t')
		add_token_from_checker(shell, WORD, &shell->checker);
	ft_lstadd_back(&shell->tokens, ft_lstnew("|"));
	return (1);
}

int	check_key(t_shell *shell)
{
	return (shell->input[shell->i] && (ft_isalnum(shell->input[shell->i])
			|| shell->input[shell->i] == '_' || shell->input[shell->i] == '?'));
}

int	parse_dollar(t_shell *shell)
{
	shell->j = 0;
	shell->tempkey = malloc(256);
	ft_memset(shell->tempkey, 0, 256);
	shell->i++;
	shell->checker[ft_strlen(shell->checker) - 1] = '\0';
	while (check_key(shell))
		shell->tempkey[shell->j++] = shell->input[shell->i++];
	shell->tempkey[shell->j] = 0;
	shell->tempvalue = get_env_value(shell, shell->tempkey);
	if (shell->tempvalue)
	{
		shell->temp2 = shell->tempvalue;
		while (*(shell->temp2))
		{
			append_checker_char(shell, *(shell->temp2));
			shell->temp2++;
		}
	}
	shell->i--;
	shell->typeflag = DOLLAR;
	if (shell->tempkey)
		free(shell->tempkey);
	if (shell->input[shell->i + 1] == ' ')
		return (1);
	return (0);
}
