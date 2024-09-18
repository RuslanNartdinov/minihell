/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:04:42 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 12:04:42 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_code = 0;

/// @brief it handles the signal SIGINT
/// @param signal_number 
void	signal_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 1;
	}
}

/// @brief it closes the standard input, output and error
/// @param  
void	close_std(void)
{
	close(0);
	close(1);
	close(2);
}

/// @brief it adds the input to the history and initializes the shell,
///			then it parses the input, sets the type of
///         the tokens and executes the line
///  		after that it clears the shell
/// @param shell 
void	minishell(t_shell *shell)
{
	add_history(shell->input);
	data_init(shell);
	parser(shell);
	set_type(shell);
	exec_line(shell);
	free_split_from(shell->env_str, 0);
	ft_lstclear(shell);
}

/// @brief it initializes the shell and starts the main loop
/// @signals are used to ignore the signals SIGQUIT and SIGINT
/// @param argc 
/// @param argv 
/// @param envp it is the environment variables
/// @return 
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	pre_init(&shell, envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	while (1)
	{
		shell.input = readline("\033[31m" "minihell$ " "\033[0m");
		if (!shell.input)
			break ;
		if (shell.input[0] != 0)
			minishell(&shell);
		else
		{
			shell.status = g_exit_code;
			set_exitstatus(&shell);
		}
	}
	ft_envclear(&shell.enviro);
	ft_lstclear(&shell);
	printf("exit\n");
	return (0);
}
