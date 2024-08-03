#include <unistd.h>

size_t	trim_left_spaces(char **command)
{
	size_t	len;

	len = 0;
	if(!*command)
		return (len);
	while(**command == 32)
	{
		len++;
		(*command)++;
	}
	return (len);
}