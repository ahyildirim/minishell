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

void	run_builtin(t_data *data, t_cmdlist *cmd, int builtin, int *fd, int fd_index)//TODO
{	
	if (fd)
		create_dup(cmd, data, fd, fd_index);
	if (builtin == ECHO)
		com_echo(cmd);
	else if (builtin == CD)
		com_cd(data, cmd);
	else if (builtin == PWD)
		com_pwd();
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
