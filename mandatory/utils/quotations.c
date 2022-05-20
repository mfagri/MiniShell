#include "../minishell.h"

int	check_next_qu(char *str, char c, int i)
{
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	remove_qu_utils_1(char *str, int *k, int i, char u)
{
	if ((str[i] == 39 || str[i] == 34))
	{
		if (u && str[i] == u)
			(*k)++;
		else if (!u && check_next_qu(str, str[i], i + 1))
		{
			u = str[i];
			(*k)++;
		}
	}
	return (u);
}

char	*remove_qu(char *str)
{
	int		i;
	int		k;
	int		j;
	char	u;
	char	*tmp;

	k = 0;
	j = 0;
	i = -1;
	u = '\0';
	tmp = malloc (ft_strlen(str) - 1);
	while (str[++i])
	{
		u = remove_qu_utils_1(str, &k, i, u);
		if (k < 2)
		{
			if ((!u || (u && str[i] != u)) && ++j)
				tmp[j - 1] = str[i];
		}
		if (k >= 2)
		{
			u = '\0';
			k = 0;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}