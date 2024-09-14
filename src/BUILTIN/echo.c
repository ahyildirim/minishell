#include "../../includes/minishell.h"

void	com_echo(t_cmdlist *cmd)
{
	char	**path;
	int		is_n;

	is_n = 0;
	path = &cmd->path[1];
	if (*path && ft_strcmp(*path, "-n"))
	{
		is_n = 1;
		path++;
	}
	while (*path)
	{
		if (*path)
			ft_putstr_fd(*path, cmd->output_file);
		if (*(++path))
			ft_putstr_fd(" ", cmd->output_file);
	}
	if (!is_n)
		ft_putstr_fd("\n", cmd->output_file);
	
}
