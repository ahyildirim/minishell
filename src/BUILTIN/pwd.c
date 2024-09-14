#include "../../includes/minishell.h"

void	com_pwd(t_cmdlist *cmd)
{
	char	pwd[4096];
	char	*path;

	path = getcwd(pwd, 4096);
	if (!path)
		return (perror("minishell: pwd: "));
	ft_putstr_fd(pwd, cmd->output_file);
	ft_putstr_fd("\n", cmd->output_file);
}
