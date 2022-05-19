# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

int	ft_strlen(char *c)
{
	int	i;

	i = 0;
	while (c && c[i] != '\0')
		i++;
	return (i);
}

static size_t	lenp(const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*cpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	dest = malloc (sizeof (char) * (ft_strlen(src) + 1));
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	check(char *src, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] != c && (src[i + 1] == c || src[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static int	ft_mal(char *str, int k, char c)
{
	int	i;

	i = 0;
	while (str[k++] != c && str[k] != '\0')
		i++;
	return (i);
}

static int	makeit(char	**a, char *str, char c)
{
	int	k;
	int	j;
	int	i;

	k = 0;
	i = 0;
	while (str[k])
	{
		j = 0;
		if (str[k] != c)
		{
			a[i] = (char *)malloc (sizeof(char) * ft_mal(str, k, c) + 1);
			if (a[i] == NULL)
				return (1);
			while (str[k] != c && str[k] != '\0')
				a[i][j++] = str[k++];
			a[i][j] = '\0';
			i++;
		}
		else
			k++;
	}
	return (0);
}

static	void	ft_free(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		free (a[i++]);
	free (a);
}

char	**ft_split(char const *s, char c)
{
	char	**a;
	int		ln;
	int		i;

	if (s == NULL)
		return (NULL);
	ln = check((char *)s, c);
	i = 0;
	a = (char **)malloc(sizeof(char *) * (ln + 1));
	if (a == NULL)
		return (NULL);
	i = makeit(a, (char *)s, c);
	if (i == 1)
	{
		ft_free (a);
		return (NULL);
	}
	a[ln] = NULL;
	return (a);
}

static int	len(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		k;
	int		j;
	char	*a;

	if (!s1 || !s2)
		return (NULL);
	i = len(s1) + len(s2);
	j = 0;
	k = 0;
	a = malloc(i + 1);
	if (a == 0)
		return (0);
	while (s1[j] != '\0')
	{
		a[j] = s1[j];
		j++;
	}
	while (s2[k] != '\0')
		a[j++] = s2[k++];
	a[j] = '\0';
	return (a);
}

char	*remove_path(char *str)
{
	int		i;
	char	*tmp;
	
	i = 5;
	tmp = malloc (strlen(str) + 1);
	while (str[i])
	{
		tmp[i - 5] = str[i];
		i++;
	}
	return (tmp);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	char	**env2;
	char	*command;
	char	**comd;
	char	**comd2;
	char	*tmp;
	int		fd;

	// while(1)
	// {
		// command = readline("minitest->");
		// add_history(command);
		// i = 0;
		// while (env[i])
		// {
		// 	if (!strncmp(env[i], "PATH", 4))
		// 		break;
		// 	i++;
		// }
		// tmp = remove_path(env[i]);
		// env2 = ft_split(tmp, ':');
		// comd = ft_split(command, ' ');
		// i = 0;
		// while (env2[i])
		// {
		// 	env2[i] = ft_strjoin(env2[i], "/");
		// 	env2[i] = ft_strjoin(env2[i], comd[0]);
		// 	i++;
		// }
		// // i = 0;
		// // while (env2[i])
		// // 	printf ("%s\n", env2[i++]);
		// i = 0;
		// while (env2[i])
		// {
		// 	if (!access(env2[i], F_OK))
		// 		break ;
		// 	i++;
		// }
		// printf ("---------------------%s\n", env2[i]);
	// }
		tmp = cpy (tmp, "/Users/aaitoual/Desktop/push/minishell");
		comd = malloc (sizeof (char *) * 2);
		comd[0] = cpy(comd[0], "minishell");
		comd[1] = NULL;
		fd = fork();
		if (!fd)
		{
			printf ("%s\n", comd[0]);
			execve(tmp, comd, NULL);
		}
		else
			waitpid(fd, NULL, 0);
}