/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:01:00 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 16:31:30 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_pipe(t_shell *shell)
{
	shell->checker[ft_strlen(shell->checker) - 1] = '\0';
	if (shell->iter > 0 && ft_strlen(shell->checker) != 0
		&& shell->input[shell->iter - 1] != ' '
		&& shell->input[shell->iter - 1] != '\t')
		add_token_from_checker(shell, 0, &shell->checker);
	ft_lstadd_back(&shell->tokens, ft_lstnew("|"));
	return (1);
}

int	check_key(t_shell *shell)
{
	return (shell->input[shell->iter] && (ft_isalnum(shell->input[shell->iter])
			|| shell->input[shell->iter] == '_'
			|| shell->input[shell->iter] == '?'));
}

int	parse_dollar(t_shell *shell)
{
	shell->jter = 0;
	shell->tempkey = malloc(256);
	ft_memset(shell->tempkey, 0, 256);
	shell->iter++;
	shell->checker[ft_strlen(shell->checker) - 1] = '\0';
	while (check_key(shell))
		shell->tempkey[shell->jter++] = shell->input[shell->iter++];
	shell->tempkey[shell->jter] = 0;
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
	shell->iter--;
	shell->type_flag = 21;
	if (shell->tempkey)
		free(shell->tempkey);
	if (shell->input[shell->iter + 1] == ' ')
		return (1);
	return (0);
}
