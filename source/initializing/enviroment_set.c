/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:32:53 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 18:32:53 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/// @brief sets the exit status of the shell to the environment variable
/// @param shell 
void	set_exitstatus(t_shell *shell)
{
	char	*status_str;
	char	*exit_status;
	char	*temp;

	status_str = ft_itoa(shell->status);
	temp = ft_strjoin("?", "=");
	exit_status = ft_strjoin(temp, status_str);
	free(status_str);
	free(temp);
	add_to_env(shell, exit_status, 1, 0);
}

/// @brief it sets the PWD environment variable
/// @param shell 
void	set_pwd(t_shell *shell)
{
	char	*str;
	char	*finalstr;
	char	*temp;

	str = getcwd(NULL, PATH_MAX);
	temp = ft_strjoin("PWD", "=");
	finalstr = ft_strjoin(temp, str);
	free(str);
	free(temp);
	add_to_env(shell, finalstr, 0, 0);
}

/// @brief it increments the SHLVL environment variable
///        The SHLVL environment variable is used to track
///        the number of nested shell invocations
/// @param shell 
void	incr_shlvl(t_shell *shell)
{
	char	*shlvl_str;
	char	*new_shlvl_str;
	int		shlvl;
	char	*value;

	value = get_env_value(shell, "SHLVL");
	if (!value)
		shlvl = 1;
	else
		shlvl = ft_atoi(value) + 1;
	shlvl_str = ft_itoa(shlvl);
	new_shlvl_str = ft_strjoin("SHLVL=", shlvl_str);
	add_to_env(shell, new_shlvl_str, 0, 0);
	if (shlvl_str)
		free(shlvl_str);
}

/// @brief it sets the environment variables, and a
/// @param shell 
void	env_init(t_shell *shell)
{
	if (shell->enviro)
		return ;
	shell->enviro = NULL;
	while (shell->envp[shell->iter])
	{
		ft_envadd_back(&shell->enviro, shell->envp[shell->iter], 0);
		shell->iter++;
	}
	shell->iter = 0;
}

/// @brief it checks if there are any duplicates in the environment variables
///  	   if there are it will remove the old one and add the new one
/// @param shell 
/// @param string
/// @param hide 
/// @param sethide 
void	add_to_env(t_shell *shell, char *string, int hide, int sethide)
{
	if (check_env_dupes(shell, string, sethide))
		ft_envadd_back(&shell->enviro, string, hide);
	if (string)
		free (string);
}
