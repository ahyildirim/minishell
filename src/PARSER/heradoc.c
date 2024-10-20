/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heradoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:43 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:25:44 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_heradoc_values(t_cmdlist *cmd_table, int *fd, t_data *data)
{
	char	buf[1];

	if (cmd_table->heradoc_values)
	{
		free(cmd_table->heradoc_values);
		cmd_table->heradoc_values = NULL;
	}
	while (read(fd[0], buf, 1))
		str_append_char(&cmd_table->heradoc_values, *buf);
	close(fd[0]);
	str_append_char(&data->input, '\n');
	ft_strjoin(&data->input, cmd_table->heradoc_values);
}

static char	*get_heradoc_values(char *eof)
{
	char	*line;
	char	*new_line;
	int		*is_started;

	line = NULL;
	is_started = 0;
	signal(SIGINT, handle_sigint);
	while (1)
	{
		new_line = readline("> ");
		if (ft_strcmp(eof, new_line) || new_line == NULL)
		{
			free(new_line);
			break ;
		}
		else if (is_started++)
			str_append_char(&line, '\n');
		ft_strjoin(&line, new_line);
		if (new_line)
			free(new_line);
	}
	if (line)
		str_append_char(&line, '\n');
	return (line);
}

static void	fill_heradoc(char *eof, int *fd, t_data *data)
{
	char	*lines;

	close(fd[0]);
	lines = get_heradoc_values(eof);
	if (lines)
		write(fd[1], lines, ft_strlen(lines));
	close(fd[1]);
	free(lines);
	free_loop(data);
	free_utils(data);
	exit(EXIT_SUCCESS);
}

static int	read_heradoc_value(t_cmdlist *cmd_table, char *eof, t_data *data)
{
	int	pid;
	int	fd[2];
	int	ret;

	g_sig = 2;
	pipe(fd);
	pid = fork();
	data->is_reading = 1;
	if (pid == 0)
		fill_heradoc(eof, fd, data);
	close(fd[1]);
	waitpid(pid, &ret, 0);
	data->is_reading = 0;
	ret = WEXITSTATUS(ret);
	if (ret == SIGNAL_C)
	{
		close(fd[0]);
		free(cmd_table->heradoc_values);
		cmd_table->heradoc_values = NULL;
		return (0);
	}
	set_heradoc_values(cmd_table, fd, data);
	return (1);
}

void	run_heradoc(t_cmdlist *cmd_table, t_data *data)
{
	t_filelist	*tmp;

	if (!cmd_table)
		return ;
	while (cmd_table)
	{
		tmp = cmd_table->files;
		if (!tmp)
			return ;
		while (tmp)
		{
			if (tmp->meta_char[1] == DOUBLE_LESS[1])
			{
				if (!read_heradoc_value(cmd_table, tmp->file_name, data))
					return ;
				tmp->fd = HERADOC;
			}
			tmp = tmp->next;
		}
		cmd_table = cmd_table->next;
	}
	g_sig = 0;
}
