#include "../../includes/minishell.h"

size_t	ft_numlen(long n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 9 && ++len)
		n = n / 10;
	return (len + 1);
}

char	*ft_strrev(char *s)
{
	size_t	i;
	size_t	len;
	char	tmp;

	i = 0;
	len = ft_strlen(s);
	if (s[0] == '-')
	{
		i++;
		len++;
	}
	while (s[i] && i < len / 2)
	{
		tmp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = tmp;
		i++;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nn;
	size_t	i;

	nn = (long)n;
	i = 0;
	str = (char *)malloc(sizeof(char) * ft_numlen(nn) + 1);
	if (!str)
		return (NULL);
	if ((n == 0 || n == -0) && ++i)
		str[0] = '0';
	if (nn < 0)
	{
		nn = -nn;
		str[0] = '-';
		i++;
	}
	while (nn > 0)
	{
		str[i++] = nn % 10 + '0';
		nn /= 10;
	}
	str[i] = '\0';
	ft_strrev(str);
	return (str);
}