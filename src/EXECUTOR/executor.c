/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:27:20 by euc               #+#    #+#             */
/*   Updated: 2024/10/21 13:46:33 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	*create_pipe(void)
{
	int	i;
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 6);
	i = -1;
	while (++i < 6)
		fd[i] = 0;
	return (fd);
}

static void	switch_pipe(int **fd)
{
	int	temp;

	temp = (*fd)[0];
	(*fd)[0] = (*fd)[2];
	(*fd)[2] = temp;
	temp = (*fd)[1];
	(*fd)[1] = (*fd)[3];
	(*fd)[3] = temp;
	temp = (*fd)[5];
	(*fd)[5] = (*fd)[3];
	(*fd)[3] = temp;
	temp = (*fd)[4];
	(*fd)[4] = (*fd)[2];
	(*fd)[2] = temp;
}

static void	run_multiple(t_data *data, t_cmdlist *cmd_list)
{
	int	*fd;

	g_sig = 2;
	fd = create_pipe();
	while (cmd_list)
	{
		switch_pipe(&fd);
		pipe(&fd[2]);
		cmd_list->pid = fork();
		if (cmd_list->pid <= 0)
			run_process(data, cmd_list, fd, 2);
		cmd_list = cmd_list->next;
		if (fd[4] && fd[5])
		{
			close(fd[4]);
			close(fd[5]);
			fd[4] = 0;
			fd[5] = 0;
		}
	}
	clear_pipe(fd);
	wait_all(data);
}

static void	run_single(t_data *data, t_cmdlist *cmd, int *fd)
{
	g_sig = 3;
	if (cmd->input_file != SSTDERR && cmd->output_file != SSTDERR)
		exec_command(data, cmd, fd, -1);
}

void	main_executor(t_data *data)
{
	if (!data->cmd_table)
		return ;
	else if (!data->cmd_table->next)
		run_single(data, data->cmd_table, NULL);
	else
		run_multiple(data, data->cmd_table);
	g_sig = 1;
}
