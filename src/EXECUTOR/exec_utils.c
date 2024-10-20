/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:18:50 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/20 15:21:51 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_types(t_data *data, char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir != NULL)
	{
		closedir(dir);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		data->last_output = 126;
	}
	else if (access(cmd, F_OK) == -1)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		data->last_output = 127;
	}
	else if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		data->last_output = 126;
	}
}

int	type_control(t_data *data, t_cmdlist *cmd, char **envs)
{
	if (ft_strncmp(cmd->command, "./", 2) == 0 || ft_strncmp(cmd->command, "/",
			1) == 0)
	{
		if (execve(cmd->command, cmd->path, envs) == -1)
		{
			set_types(data, cmd->command);
			free(cmd->path);
			return (exit(data->last_output), 0);
		}
	}
	return (1);
}
