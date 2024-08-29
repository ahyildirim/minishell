#include "../../includes/minishell.h"

char	*is_meta_char(char *command, t_data *data)
{
	char **meta_chars;

	if(!command)
		return (NULL);
	meta_chars = data->metachars;
	while(meta_chars && *meta_chars)
	{
		if((*command == **meta_chars && !*(meta_chars + 1)) || (*command == **meta_chars && *(*meta_chars + 1) == *(command + 1)))
			return (*meta_chars);
		meta_chars++;
	}
	return (NULL);
}