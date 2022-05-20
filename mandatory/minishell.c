/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:40:16 by aaitoual          #+#    #+#             */
/*   Updated: 2022/05/20 09:40:17 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


int	get_t(char *tmp, int t)
{
	while (tmp[++t])
	{
		if (tmp[t] == ' ')
			break ;
	}
	return (t);
}

		// if (((tmp[i] == ' ' && tmp[i + 1] != ' ') || (tmp[i - 1] == '|')) || ((tmp[i - 1] == '>' || tmp[i - 1] == '<' || tmp[i - 1] == '|') && (tmp[i] != ' ' && tmp[i] != '>' && tmp[i] != '<'))
		// 	|| (((tmp[i - 1] == '>' && tmp[i] == '>') || (tmp[i - 1] == '<' && tmp[i] == '<')) && tmp[i + 1] != ' '))
		// {
		// 	if (((tmp[i - 1] == '<' && tmp[i] == '<') || (tmp[i - 1] == '>' && tmp[i] == '>')) && tmp[i + 1] != ' ')
		// 		i++;
		// 	if (!r && i != 0)
		// 	{
		// 		printf ("--------%c+%c\n", tmp[i - 1], tmp[i]);
		// 		ret[k++] = get_arg(tmp, i, t);
		// 		if (t != -1)
		// 			t = get_t(tmp, t);
		// 		else
		// 			t = i;
		// 	}
		// }
char	**get_command(char **env, int fd)
{
	char	*command;
	char	*tmp;
	char	*tmp2;
	char	**ret;
	int		i;
	int		k;
	char	r;
	int		t;

	k = 0;
	i = 0;
	t = -1;
	r = '\0';
	
	tmp = readline("minishell=>");
	if (!tmp)
		return (NULL);
	add_history(tmp);
	write (fd, "\n", 1);
	write (fd, tmp, ft_strlen(tmp));
	ret = malloc (sizeof(char*) * (get_spaces(tmp) + 1));
	tmp2 = cpy(tmp2, tmp);
	free (tmp);
	tmp = sep(tmp2, 0, 0);
	free (tmp2);
	i = -1;
	i = 0;
	while (tmp[i])
	{
		r = get_q_1(tmp, i, r);
		if ((tmp[i] == ' ' && tmp[i + 1] != ' ' && tmp[i + 1]))
		{
			if (!r)
			{
				ret[k++] = get_arg(tmp, i, t);
				t = i;
				i++;
				if (tmp[i] == 34 || tmp[i] == 39)
				{
					if (r && tmp[i] == r)
						r = '\0';
					else
						r = tmp[i];
				}
			}
		}
		if (!tmp[i])
			break ;
		i++;
	}
	if (i - t - 1 > 0 && tmp[t + 1])
		ret[k++] = get_arg(tmp, i, t);
	ret[k] = NULL;
	k = -1;
	// while (ret[++k])
	// 	printf ("%s-\n", ret[k]);
	// puts ("yoooo");
	ret = edit_var(ret, env);
	ret = edit_qu(ret);
	free (tmp);
	return (ret);
}

void	child_exec(char ***splited, char *path, int t, struct termios terminal2, char **env)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
	execve(path, splited[t], env);
	exit(0);
}

int	remove_path_2(char *str)
{
	if (str[0] == '/' || str[0] == '.')
		return (1);
	return (0);
}

char	*remove_pwd(char **env, int i)
{
	char	*ret;
	int		k;

	k = 3;
	ret = malloc (sizeof(char) * (ft_strlen(env[i]) - 2));
	while(env[i][++k])
	{
		ret[k - 4] = env[i][k];
	}
	ret[k - 4] = '\0';
	return (ret);
}

int	check_splited(char ***str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!(ft_strncmp(str[i][j], "|", ft_strlen(str[i][j]))))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	exec(int fd, char **env, struct termios terminal2)
{
	int		r;
	int		k;
	int		t;
	int		stdout;
	int		stdin;
	int		pi;
	int		st = 1;
	char	**pr;
	int		fdd[2];
	char	***splited;
	char	*command;
	char	*path;

	path = malloc (1);
	pr = get_command(env, fd);
	if (!pr)
	{
		write (1, "\033[1A\033[11Cexit\n", 14);
		return (0);
	}
	if (!ft_strncmp("(null)", pr[0], ft_strlen(pr[0])))
	{
		return (1);
	}
	splited = split_pr(pr, 0, 0, '\0');
	t = 0;
	pi = 1;
	stdin = dup(0);
	stdout = dup(1);
	r = -1;
	while (pr[++r])
		free (pr[r]);
	if (!check_splited(splited))
	{
		printf ("%s\n", "syntax error");
		return (1);
	}
	while (splited[t])
	{
		k = 1;
		if (splited[pi])
			pipe(fdd);
		free (path);
		path = get_path(env, splited[t][0]);
		if (remove_path_2(splited[t][0]))
		{
			free (path);
			path = get_new_path(env, splited[t][0]);
		}
		if (!path)
		{
			printf ("minishell: %s: command not found\n", splited[t][0]);
			get_glo(0);
			if (!splited[pi])
				break ;
			k = 0;
		}
		r = fork();	
		if (!r)
		{
			if (!k)
				exit (0);
			if (splited[pi])
			{
				dup2(fdd[1], 1);
				close(fdd[0]);
				close(fdd[1]);
			}
			else
				dup2(stdout, 1);
			child_exec(splited, path, t, terminal2, env);
		}
		else if (!splited[pi])
		{
			get_glo(1);
			waitpid(r, NULL, 0);
			remove_ctlc();
		}
		if (splited[pi] && k)
		{
			dup2(fdd[0], 0);
			close(fdd[0]);
			close(fdd[1]);
			dup2(stdout, 1);
		}
		else
			dup2(stdin, 0);
		t++;
		pi++;
	}
	free (pr);
	r = 0;
	t = 0;
	while (splited[r])
	{
		t = 0;
		while(splited[r][t])
		{
			free (splited[r][t]);
			t++;
		}
		free (splited[r]);
		r++;
	}
	free (splited);
	dup2(stdout, 1);
	dup2(stdin, 0);
	return (1);
}

// int	exec(int fd, char **env, struct termios terminal2)
// {
// 	int		r;
// 	int		k;
// 	char	**pr;
// 	char	*command;
// 	// char	**paths;
// 	char	*path;
// 	path = malloc (1);

// 	pr = get_command(env, fd);
// 	free (path);
// 	if (pr)
// 	{
// 		path = get_path(env, pr[0]);
// 		if (!path)
// 		{
// 			printf ("minishell=> %s: command not found\n", pr[0]);
// 			get_glo(0);
// 		}
// 		r = fork();	
// 		if (!r)
// 		{
// 			//g_globle.i = 0;
// 			tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
// 			// if(strcmp("echo",pr[0]) == 0)
// 			// {
// 			// 	ft_echo(pr);
// 			// }
// 			// else if(strcmp("pwd",pr[0]) == 0)
// 			// 	ft_pwd();
// 			// else if(strcmp("cd",pr[0]) == 0)
// 			// 	ft_cd(pr);
// 			// else
// 				execve(path, pr, NULL);
// 			exit(0);
// 		}
// 		else
// 		{
// 			//g_globle.i = 1;
// 			get_glo(1);
// 			waitpid(r, NULL, 0);
// 			remove_ctlc();
// 			//sleep(10);
// 		}
// 		r = -1;
// 		while (pr[++r])
// 			free (pr[r]);
// 		free (pr);
// 	}
// 	else
// 	{
// 		tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
// 		get_tt();
// 		//printf("\bexit\n");
// 		return (0);
// 	}
// 	return (1);
// }

int	main(int ac, char **av, char **env)
{
	t_main	i;
	int		r;
	int k;
	char	**pr;
	char	*command;
	char	*path;
	int		fd;
	struct termios terminal2;

	path = malloc (1);
	fd = get_history();
	terminal2 = remove_ctlc();
	signal(SIGINT, ft_sig);
	signal(SIGQUIT,ft_sig);
	r = 1;
	//waitpid(l, NULL, 0);
	k = 1;
	while (k)
	{
		//g_globle.i = 0;
		get_glo(0);
		k = exec(fd, env, terminal2);
	}
	if(k == 0)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
		exit(0);
	}
	free (path);
}
