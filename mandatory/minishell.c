# include "minishell.h"

char	*get_first(char	*str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str && str[i] && str[i] != ' ')
		i++;
	ret = malloc (sizeof (char) * (i + 1));
	i = 0;
	while (str && str[i] && str[i] != ' ')
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

int	get_spaces(char *str)
{
	int		i;
	int		k;
	int		j;
	char	qu;

	j = 0;
	i = 0;
	k = 1;
	qu = 0;
	while (str[i])
	{
		if (str[i] == ' ' && i != 0 && str[i + 1] && k && str[i + 1] != 39 && str[i + 1] != 34)
			j++;
		if ((str[i] == 39 || str[i] == 34) && k)
		{
			k = 0;
			qu = str[i];
		}
		i++;
		if (!k && str[i] == qu)
		{
			j++;
			i++;
			k = 1;
		}
	}
	return (j + 1);
}

char	*get_arg(char *str, int i, int t)
{
	int		j;
	int		r;
	char	*ret;
	
	j = t;
	r = 0;
	ret = malloc (sizeof(char) * (i - t + 1));
	while (++j < i)
	{
		ret[r] = str[j];
		r++;
	}
	ret[r] = '\0';
	return (ret);
}

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

char	*remove_qu(char *str)
{
	int		i;
	int		k;
	int		j;
	char	u;
	char	*tmp;

	k = 0;
	j = 0;
	i = 0;
	u = 0;
	tmp = malloc (ft_strlen(str) - 1);
	while (str[i])
	{
		if ((str[i] == 39 || str[i] == 34))
		{
			if (u && str[i] == u)
				k++;
			else if (!u && check_next_qu(str, str[i], i + 1))
			{
				u = str[i];
				k++;
			}
		}
		if (k < 2)
		{
			if (!u || (u && str[i] != u))
			{
				tmp[j] = str[i];
				j++;
			}
		}
		if (k >= 2)
		{
			k = 0;
			u = 0;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	**edit_qu(char **str)
{
	int		i;
	int		j;
	char	r;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		j = 0;
		r = 0;
		while (str[i][j])
		{
			if ((str[i][j] == 34 || str[i][j] == 39) && !r)
				r = str[i][j];
			else if (r && str[i][j] == r)
			{
				tmp = cpy(tmp, str[i]);
				free (str[i]);
				str[i] = remove_qu(tmp);
				free (tmp);
				break ;
			}
			j++;
		}
		i++;
	}
	return (str);
}

char	*get_var_2(char *str, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*ret;
	char	*tmp;
	
	i = 0;
	j = 0;
	k = fork();
	if (!k)
		exit (0);
	if (!ft_strncmp(str, "$", ft_strlen(str)))
	{
		ret = ft_itoa(k);
		return (ret);
	}
	k = 0;
	tmp = cpy(tmp, str);
	str = ft_strjoin(tmp, "=");
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	while (env[i][j++] != '=');
	ret = malloc (sizeof (char) * (ft_strlen(env[i]) - j + 1));
	while (env[i][j])
		ret[k++] = env[i][j++];
	ret[k] = '\0';
	return (ret);
}

char	*get_var(char *str, char **env, int j)
{
	char	*tmp;
	char	*ret;
	char	*tmp2;
	int		i;
	int		k;

	i = 0;
	tmp = malloc (j + 1);
	while (str[i] && str[i] != '$')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	k = i + 1;
	while (str[i] != 34 && str[i])
	{
		i++;
		j++;
	}
	ret = cpy(ret, tmp);
	tmp2 = malloc (sizeof (char) * j);
	i = 0;
	while (str[k] && (ft_isalnum(str[k]) || str[k] == '$'))
	{
		tmp2[i++] = str[k++];
		if (ft_isdigit(str[k - i]) || str[k - 1] == '$')
			break ;
	}
	tmp2[k] = '\0';
	ret = ft_strjoin(ret, get_var_2(tmp2, env));
	free (tmp2);
	i = k;
	while (str[i++]);
	tmp2 = malloc(i - k);
	i = 0;
	while (str[k])
		tmp2[i++] = str[k++];
	tmp2[i] = '\0';
	ret = ft_strjoin(ret, tmp2);
	return (ret);
}

char	**edit_var(char **ret, char **env)
{
	char	*tmp;
	char	*var;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 1;
	while (ret[i])
	{
		j = 0;
		while (ret[i][j])
		{
			if (k && ret[i][j] == 39)
				k = 0;
			else if (!k && ret[i][j] == 39)
				k = 1;
			if (ret[i][j] == 34 && check_next_qu(ret[i], 34, j) && !k)
				k = 0;
			if (k && ret[i][j] == '$')
			{
				ret[i] = get_var(ret[i], env, j);
			}
			j++;
		}
		i++;
	}
	return (ret);
}

char	**get_command(char **env, int fd)
{
	char	*command;
	char	*tmp;
	char	**ret;
	int		i;
	int		k;
	char	r;
	int		t;

	k = 0;
	i = 0;
	t = -1;
	r = 0;
	tmp = readline("minishell=>");
	if (!tmp)
		return (NULL);
	add_history(tmp);
	write (fd, tmp, ft_strlen(tmp));
	write (fd, "\n", 1);
	ret = malloc (sizeof(char*) * (get_spaces(tmp) + 2));
	while (tmp[i])
	{
		if (tmp[i] == 34 || tmp[i] == 39)
		{
			if (r && tmp[i] == r)
				r = 0;
			else
				r = tmp[i];
		}
		if (tmp[i] == ' ')
		{
			if (!r)
			{
				ret[k++] = get_arg(tmp, i, t);
				t = i;
			}
		}
		i++;
	}
	if (i - t - 1 > 0)
		ret[k++] = get_arg(tmp, i, t);
	ret[k] = NULL;
	ret = edit_var(ret, env);
	ret = edit_qu(ret);
	free (tmp);
	return (ret);
}

void	exec(int fd, char **env)
{
	int		r;
	int		k;
	char	**pr;
	char	*command;
	// char	**paths;
	char	*path;
	path = malloc (1);

	pr = get_command(env, fd);
	// if(pr == NULL)
	// {
	// 	write(2,"exit\n",5);
	// 	exit(0);
	// }
		free (path);
		if (pr)
		{
			path = get_path(env, pr[0]);
		// if (!path)
		// {
		// 	printf ("minishell=> %s: command not found\n", pr[0]);
		// }
		r = fork();
		if (!r)
		{
			execve(path, pr, NULL);
			exit(0);
		}
		else
			waitpid(r, NULL, 0);
		r = -1;
		while (pr[++r])
			free (pr[r]);
		free (pr);
	}
	else
	{
		rl_replace_line("", -1);
		write (1, "exit\n", 5);
		rl_on_new_line();
		exit (0);
	}
}

void ft(int signum)
{
	if(signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(2,"\n",1);
		write (2, "minishell=>", 11);
	}
	return ;
}

int	main(int ac, char **av, char **env)
{
	t_main	i;
	int		r;
	int		k;
	char	**pr;
	char	*command;
	// char	**paths;
	char	*path;
	int		fd;

	fd = get_history();
	path = malloc (1);
	k = 2;
	signal(SIGINT, ft);
	while (k)
	{
		exec(fd, env);
	}
	r = -1;
	free (path);
	while (pr[++r])
		free (pr[r]);
	free (pr);
	// free (command);
}
