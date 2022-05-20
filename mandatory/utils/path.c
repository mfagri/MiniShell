#include "../minishell.h"

char    *get_alloc_2(char **env, char *cmd, int *i)
{
    char	*ret;
	char	*tmp;
	int		k;
	int		j;

	(*i) = 0;
	k = -1;
    while (env[(*i)])
	{
		if (!ft_strncmp(env[(*i)], "PWD=", 4))
			break ;
		i++;
	}
	tmp = remove_pwd(env, (*i));
	ret = malloc (sizeof (char) * (ft_strlen(cmd) + ft_strlen(tmp) + 1));
    return (ret);
}


char	*get_new_path(char **env, char *cmd)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		k;
	int		j;

    ret = get_alloc_2(env, cmd, &i);
	tmp = remove_pwd(env, i);
	while (cmd[i])
	{
		if (i == 0 && cmd[i] == '.' && cmd[i + 1] == '/')
		{
			while (tmp[++k])
			{
				ret[j] = tmp[k];
				j++;
			}
			i++;
		}
		if (i == 0 && cmd[i] == '.' && cmd[i + 1] == '.' && cmd[i + 2] == '/')
		{
			while (tmp[++k])
			{
				ret[j] = tmp[k];
				j++;
			}
			while (ret[--j] != '/')
				ret[j] = '\0';
			j++;
			i = i + 2;
		}
		if (cmd[i])
			ret[j++] = cmd[i];
		i++;
	}
	ret[j] = '\0';
	if (!access(ret, F_OK))
		return (ret) ;
	free (ret);
	return (NULL);
}