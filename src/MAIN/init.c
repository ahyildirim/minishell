#include "../../includes/minishell.h"

void	init_metachars(t_data *data)
{
	char	**meta_chars;

	meta_chars = (char **)malloc(sizeof(char *) * (METACHAR_NUM + 1));
	data->metachars = meta_chars;
	*(meta_chars++) = ft_strdup(DOUBLE_GREAT);
	*(meta_chars++) = ft_strdup(DOUBLE_LESS);
	*(meta_chars++) = ft_strdup(SINGLE_LESS);
	*(meta_chars++) = ft_strdup(SINGLE_GREAT);
	*(meta_chars++) = ft_strdup(PIPE);
	*(meta_chars++) = NULL;
}