#include "../../includes/minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	if(!str1 || !str2)
		return (0);
	while(*str1)
	{
		if(*str1 != *str2)
			break;
		str1++;
		str2++;
	}
	if (*str1 != 0 || *str2 != 0)
		return (0);
	return (1);
}