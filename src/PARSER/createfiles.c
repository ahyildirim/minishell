/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:38 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/20 15:24:56 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	fd_control(int fd, t_data *data)
{
	if (fd == -1)
	{
		data->last_output = 1;
		return (-1);
	}
	if (fd == SSTDERR)
	{
		data->last_output = 1;
		return (2);
	}
	return (0);
}

static int	check_file_error(t_filelist *file, int *fd)
{
	int	error_flag;

	error_flag = 0;
	if (!file->file_name)
		error_flag = 1;
	if (!error_flag && *file->file_name == '\"')
	{
		error_flag = 1;
		print_error("-bash: No such file or directory\n", NULL, NULL);
	}
	else if (!error_flag && *file->file_name == '$')
	{
		error_flag = 1;
		print_error("-bash: ", file->file_name, ": ambiguous redirect\n");
	}
	if (!error_flag)
		return (error_flag);
	file->fd = SSTDERR;
	*fd = file->fd;
	return (error_flag);
}

static void	create_outfile(t_cmdlist *cmd_table, t_filelist *file, t_data *data)
{
	char	*outfile_path;
	char	buf[256];

	if (check_file_error(file, &cmd_table->output_file))
		return ;
	outfile_path = NULL;
	ft_strjoin(&outfile_path, (char *)getcwd(buf, 256));
	str_append_char(&outfile_path, '/');
	ft_strjoin(&outfile_path, file->file_name);
	if (file->meta_char[1] == DOUBLE_GREAT[1])
		file->fd = open(outfile_path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		file->fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file->fd == -1)
	{
		perror("minishell");
		data->last_output = 1;
		file->fd = SSTDERR;
	}
	cmd_table->output_file = file->fd;
	free(outfile_path);
}

static void	create_infile(t_cmdlist *cmd_table, t_filelist *file, t_data *data)
{
	char	*infile_path;
	char	buf[256];

	if (file->meta_char[1] == DOUBLE_LESS[1])
	{
		cmd_table->input_file = HERADOC;
		return ;
	}
	if (check_file_error(file, &cmd_table->input_file))
		return ;
	infile_path = NULL;
	ft_strjoin(&infile_path, (char *)getcwd(buf, 256));
	str_append_char(&infile_path, '/');
	ft_strjoin(&infile_path, file->file_name);
	if (access(infile_path, F_OK) == 0)
		file->fd = open(infile_path, O_RDONLY, 0777);
	if ((file->fd <= SSTDERR && file->fd != HERADOC))
	{
		perror("minishell");
		data->last_output = 1;
		file->fd = SSTDERR;
	}
	cmd_table->input_file = file->fd;
	free(infile_path);
}

void	create_files(t_cmdlist *cmd_table, t_data *data)
{
	t_filelist	*tmp;

	if (!cmd_table)
		return ;
	run_heradoc(cmd_table, data);
	if (data->output || !cmd_table)
		return ;
	while (cmd_table)
	{
		tmp = cmd_table->files;
		while (tmp)
		{
			if (*tmp->meta_char == *SINGLE_GREAT)
				create_outfile(cmd_table, tmp, data);
			else
				create_infile(cmd_table, tmp, data);
			if (fd_control(tmp->fd, data) == -1)
				return ;
			else if (fd_control(tmp->fd, data) == 2)
				break ;
			tmp = tmp->next;
		}
		cmd_table = cmd_table->next;
	}
}
