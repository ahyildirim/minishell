/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:27:51 by euc               #+#    #+#             */
/*   Updated: 2024/10/20 16:19:36 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

void	handle_sigint(int sig)
{
	(void)sig;
	exit(SIGNAL_C);
}

void	ctrl_c(int sig)
{
	(void)sig;
	if (g_sig == 2)
		write(1, "\n", 1);
	else if (g_sig == 3)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_sig = 1;
}

void	handle_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
