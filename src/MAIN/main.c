#include "../../includes/minishell.h"

int	g_sig = 0;

int main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	handle_signal();
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error: Memory allocation error\n", 2), EXIT_FAILURE);
	//init
	//parse
	//shell_loop
	return (0);
}
