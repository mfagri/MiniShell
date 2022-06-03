#include "../minishell.h"

int	check_pr(char **str)
{
	int		i;
	int		j;
	char	q;
	int		u;

	i = -1;
	i = 0;
	u = 0;
	q = '\0';
	if (str[0][0] == ' ')
		i = 1;
	if ((str[i][0] == '|' || str[i][0] == '>' || str[i][0] == '<'))
		return (0);
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			q = get_q(str, i, j, q);
		if (!(ft_strncmp(str[i], "|", 1)) && !q)
		{
			if (str[i + 1])
			{
				if (!(ft_strncmp(str[i + 1], "|", ft_strlen(str[i + 1]))))
					return (0);
			}
			else
				return (0);
		}
	}
	i = -1;
	q = '\0';
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			q = get_q(str, i, j, q);
	}
	if (q)
		return (0);
	i = -1;
	u = 0;
	i = - 1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if ((str[i][j] == '<' && str[i][j + 1] != '<') || (str[i][j] == '>' && str[i][j + 1] != '>'))
			{
				if (u)
					return (0);
				else
					u = 1;
			}
			if (str[i][j] != '|' && str[i][j] != '<' && str[i][j] != '>' && str[i][j] != '<' && str[i][j] && str[i][j] != ' ')
				u = 0;
		}
	}
	if (u)
		return (0);
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if ((str[i][j] == '<' && str[i][j + 1] == '<'  && str[i][j + 2] != '<') || (str[i][j] == '>' && str[i][j + 1] == '>'  && str[i][j + 2] != '>'))
			{
				if (u)
					return (0);
				else if (!u)
					u = 1;
			}
			if (str[i][j] != '|' && str[i][j] != '<' && str[i][j] != '>' && str[i][j] != '<' && str[i][j] && str[i][j] != ' ')
				u = 0;
		}
	}
	if (u)
		return (0);
	return (1);
}