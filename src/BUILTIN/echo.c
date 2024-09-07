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
			printf("%s", *path);
		if (*(++path))
			printf(" ");
	}
	if (!is_n)
		printf("\n");
	
}
