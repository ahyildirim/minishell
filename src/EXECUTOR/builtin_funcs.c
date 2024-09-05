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
		printf("ECHO");
	else if (builtin == CD)
		printf("CD");
	else if (builtin == PWD)
		printf("PWD");
	else if (builtin == EXPORT)
		printf("EXPORT");
	else if (builtin == UNSET)
		printf("UNSET");
	else if (builtin == ENV)
		com_env(cmd, data);
	else if (builtin == EXIT)
		printf("EXIT");
}
