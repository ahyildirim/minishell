#include "../../includes/minishell.h"

void	clear_pipe(int *fd)
{
	int i;

	if (fd)
	{
		i = -1;
		while (++i < 6)
		{
			if (fd[i])
				close(fd[i]);
		}
		free(fd);
	}
}

void	create_dup(t_cmdlist *cmd, t_data *data, int *fd, int fd_index)
{
	int	new_fd[2];

	if (cmd->input_file == HERADOC)
	{
		pipe(new_fd);
		write(new_fd[1], cmd->heradoc_values, ft_strlen(cmd->heradoc_values));
		dup2(new_fd[0], STDIN_FILENO);
		close(new_fd[1]);
		close(new_fd[0]);
	}
	else if (cmd->input_file > SSTDERR)
		dup2(cmd->input_file, STDIN_FILENO);
	else if (fd && cmd != data->cmd_table)
		dup2(fd[fd_index -2], STDIN_FILENO);
	if (cmd->output_file > SSTDERR)
		dup2(cmd->output_file, STDOUT_FILENO);
	else if (fd && cmd ->next)
		dup2(fd[fd_index + 1], STDOUT_FILENO);
	if (fd_index >= 0)
		clear_pipe(fd);
}
