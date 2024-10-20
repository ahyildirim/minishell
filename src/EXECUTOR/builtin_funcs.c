/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:27:13 by euc               #+#    #+#             */
/*   Updated: 2024/10/20 15:18:07 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo"))
		return (ECHO);
	else if (ft_strcmp(cmd, "cd"))
		return (CD);
	else if (ft_strcmp(cmd, "pwd"))
		return (PWD);
	else if (ft_strcmp(cmd, "env"))
		return (ENV);
	else if (ft_strcmp(cmd, "exit"))
		return (EXIT);
	else if (ft_strcmp(cmd, "export"))
		return (EXPORT);
	else if (ft_strcmp(cmd, "unset"))
		return (UNSET);
	return (0);
}

void	run_builtin(t_data *data, t_cmdlist *cmd, int builtin, int *fd) //TODO
{
	if (fd)
		create_dup(cmd, data, fd, 2);
	if (builtin == ECHO)
		com_echo(cmd, data);
	else if (builtin == CD)
		com_cd(data, cmd);
	else if (builtin == PWD)
		com_pwd(cmd, data);
	else if (builtin == EXPORT)
		com_export(cmd, data);
	else if (builtin == UNSET)
		com_unset(cmd, data);
	else if (builtin == ENV)
		com_env(cmd, data);
	else if (builtin == EXIT)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		com_exit(cmd, data);
	}
}
