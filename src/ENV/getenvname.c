#include "../../includes/minishell.h"

static size_t	get_env_len(char *content)
{
	size_t len;

	len = 0;
	while(content && *content && *content != '=')
	{
		len++;
		content++;
	}
	return (len);
}

char	*get_env_name(char *content)
{
	int		len;
	char	*name;
	char	*tmp;

	len = get_env_len(content);
	if(!len)
		return (NULL);
	name = (char *)malloc(len + 1);
	tmp = name;
	while(content && *content && *content != '=')
		*(tmp++) = *(content++);
	tmp = 0;
	return (name);
}
