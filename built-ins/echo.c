/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:13:25 by mbabayan          #+#    #+#             */
/*   Updated: 2024/08/28 10:34:16 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_flag(char *arg)
{
	int jindex = 2;
	while (arg[jindex] == 'n')
		jindex++;
	if (arg[jindex] != '\0')
		return 0;
	return 1;
}

void print_echo(char **args, int index, int flag)
{
	while (args[index])
	{
		printf("%s", args[index]);
		if (args[index + 1])
			printf(" ");
		index++;
	}
	if (flag == 0)
		printf("\n");
}

int echo(char **args, int index)
{
	int flag;

	flag = 0;
	while (args[index] && args[index][0] == '-' && args[index][1] == 'n')
	{
		if (!check_flag(args[index]))
			break;
		flag = 1;
		index++;
	}
	print_echo(args, index, flag);
	return 0;
}