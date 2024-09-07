#include "../../includes/minishell.h"

void	com_pwd(void)
{
	char	pwd[4096];
	char	*path;

	path = getcwd(pwd, 4096);
	if (!path)
		return (perror("minishell: pwd: "));
	printf("%s\n", path);
}
