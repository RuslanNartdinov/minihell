/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_comm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:23:47 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 16:32:57 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	b_unset_del(t_shell *shell, t_env *prev, t_env *curr)
{
	if (!ft_strcmp(shell->enviro->key, curr->key))
		shell->enviro = shell->enviro->next;
	if (prev)
		prev->next = curr->next;
	free(curr->key);
	free(curr->value);
	free(curr);
}

void	b_unset(t_shell *shell, char **cmd)
{
	t_env	*curr;
	t_env	*prev;
	t_env	*temp;
	int		iter;

	iter = 1;
	while (cmd[iter])
	{
		curr = shell->enviro;
		prev = NULL;
		while (curr)
		{
			if (curr->key && !ft_strcmp(curr->key, cmd[iter])
				&& curr->key[0] != '?')
			{
				temp = curr;
				curr = curr->next;
				b_unset_del(shell, prev, temp);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		iter++;
	}
}

void	b_cd_oldpwd(t_shell *shell, char **temp, char **curr_pwd)
{
	*temp = get_pwd();
	*curr_pwd = ft_strjoin("OLDPWD=", *temp);
	add_to_env(shell, ft_strdup(*curr_pwd), 0, 1);
	free(*temp);
	free(*curr_pwd);
}

void	b_cd(t_shell *shell, char **cmd)
{
	char	*home;
	char	*curr_pwd;
	char	*temp;

	b_cd_oldpwd(shell, &temp, &curr_pwd);
	home = get_env_value(shell, "HOME");
	if (!cmd[1] || !ft_strncmp(cmd[1], "~", 2))
	{
		if (!home)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else
			chdir(home);
	}
	else if (!ft_strncmp(cmd[1], "~", 1))
		cd_home_path(home, cmd[1], shell);
	else if (chdir(cmd[1]) == -1)
	{
		perror("cd");
		shell->shell_flag = 2;
	}
	temp = get_pwd();
	curr_pwd = ft_strjoin("PWD=", temp);
	add_to_env(shell, ft_strdup(curr_pwd), 0, 1);
	free(curr_pwd);
	free(temp);
}

void	b_declare(t_shell *shell, char **cmd)
{
	int	iter;
	int	valid;

	valid = 1;
	iter = 0;
	while (cmd[iter] && valid)
	{
		if (!((ft_strrchr(cmd[iter], '=') && ft_strlen(cmd[iter]) > 1
					&& cmd[iter][0] != '=' && is_valid_key(cmd[iter]))))
			valid = 0;
		iter++;
	}
	if (valid)
	{
		iter--;
		add_to_env(shell, ft_strdup(cmd[iter]), 1, 0);
	}
}
