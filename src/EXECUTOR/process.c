#include "../../includes/minishell.h"

void	run_process(t_data *data, t_cmdlist *cmd, int *fd, int fd_index)
{
	if (cmd->input_file != SSTDERR && cmd->output_file != SSTDERR)
		exec_command(data, cmd, fd, fd_index);
	else
		clear_pipe(fd);
	free_loop(data);
	free_core(data);
	exit(data->last_output);
}

void	wait_all(t_data *data)
{
	t_cmdlist	*cmd_list;

	cmd_list = data->cmd_table;
	while (cmd_list)
	{
		if (!cmd_list->next)
			waitpid(cmd_list->pid, &data->last_output, 0);
		else
			waitpid(cmd_list->pid, 0, 0);
		cmd_list = cmd_list->next;
	}
	data->last_output = WEXITSTATUS(data->last_output);
}
