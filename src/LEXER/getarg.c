/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getarg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:24:56 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:24:57 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_arg(char *str)
{
	char	*tmp;

	if (!str)
		return (0);
	tmp = str;
	trim_left_spaces(&tmp);
	if (!*tmp)
	{
		free(str);
		return (0);
	}
	return (1);
}

static void	read_arg_value(int *fd, t_data *data)
{
	char	*str;

	signal(SIGINT, handle_sigint);
	close(fd[0]);
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
		{
			free(str);
			write(2, "-bash: syntax error unexpected end of file\n", 43);
			exit(EXIT_FAILURE);
		}
		if (!is_valid_arg(str))
			continue ;
		if (str)
			write(fd[1], str, ft_strlen(str));
		close(fd[1]);
		free(str);
		free_loop(data);
		free_utils(data);
		exit(EXIT_SUCCESS);
	}
}

static int	read_arg(int *fd, t_data *data)
{
	int	pid;
	int	ret;

	g_sig = 2;
	pid = fork();
	data->is_reading = 1;
	if (pid == 0)
		read_arg_value(fd, data);
	close(fd[1]);
	waitpid(pid, &ret, 0);
	data->is_reading = 0;
	ret = WEXITSTATUS(ret);
	if (ret == SIGNAL_C)
	{
		close(fd[0]);
		free_loop(data);
		return (0);
	}
	return (1);
}

char	*get_arg(t_data *data)
{
	char	*str;
	int		fd[2];
	char	buf[1];

	if (pipe(fd) == -1)
		return (NULL);
	if (!read_arg(fd, data))
		return (NULL);
	str = NULL;
	while (read(fd[0], buf, 1))
		str_append_char(&str, *buf);
	g_sig = 0;
	close(fd[0]);
	return (str);
}
