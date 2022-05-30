/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 04:30:33 by mfagri            #+#    #+#             */
/*   Updated: 2022/05/29 19:35:26 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_check_n(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if ((!s1 || !s2))
		return (1);
	if (s1[i] == '-')
	{
		i++;
		while (s1[i])
		{
			if (s1[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

void	ft_echo(char **pr)
{
	int		i;
	int		n_option;

	i = 1;
	n_option = 0;
	while (pr[i] && ft_check_n(pr[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (pr[i])
	{
		ft_putstr_fd(pr[i], 1);
		if (pr[i + 1] && pr[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
}

void	ft_pwd(char **arg)
{
	char	s[1024];

	if(arg[1])
		return(ft_putstr_fd("pwd: too many arguments\n",2));
	getcwd(s, sizeof(s));
	printf("%s\n", s);
}

void	ft_unset(char **arg, char **env)
{
	int	i;

	i = 0;
	while (arg[++i])
		remove_from_env(arg[i], env, 0);
}

int ft_count_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void ft_home(char **env)
{
	int i;
	char *path;
	
	i = 0;
	while(ft_strncmp(env[i],"HOME",ft_strlen("HOME")))
		i++;
	if(env[i][4] == '=')
	{
		path = ft_strrchr(env[i],'=');
		path++;
	}
	else
		path = NULL;
	if(chdir(path) == -1)
		ft_putstr_fd("minishell: cd: HOME not set\n",2);
}
void	ft_oldpwd(char **env)
{
	int i;
	char *s;
	
	i = -1;
	while(env[++i])
		if(!strncmp("OLDPWD",env[i],ft_strlen("OLDPWD")))
		{
			ft_putstr_fd(&env[i][7],1);
			write(1,"\n",1);
			s = ft_strrchr(env[i],'=');
			s++;
			if(chdir(s) == -1)
				ft_putstr_fd("minishell: cd: OLDPWD not set\n",2);
			return ;
		}
	ft_putstr_fd("minishell: cd: OLDPWD not set\n",2);
	return ;
}
char *ft_take_pwd_old(char p[])
{
	char pwd[1000000];
	char *path;
	
	getcwd(pwd,sizeof(pwd));
	path = malloc(1);
	path[0] ='\0';
	path = ft_strjoin(path,p);
	path = ft_strjoin(path,pwd);
	return (path);
}
void ft_cd_norm(char **env,char *path,char s[])
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while(env[++i])
	{
		if(!strncmp(s,env[i],ft_strlen(s)))
		{
			j = 1;
			env[i] = cpy(env[i],path);
		}
	}
	if(j != 1)
	{
		env[i] = cpy(env[i],path);
		i++;
	}
	env[i] = NULL;
}
void ft_cd(char **arg,char **env)
{
	char *oldpath;
	char *newpath;

	oldpath = ft_take_pwd_old("OLDPWD=");
	if(!arg[1])
		ft_home(env);
	else
	{
		if(!strncmp("-",arg[1],ft_strlen("-")))
			ft_oldpwd(env);
		else if (ft_count_args(arg) > 2)
				return (ft_putstr_fd("minishell: cd: too many arguments\n", 2));
		else
			if(chdir(arg[1]) == -1)
				printf("minishell: cd: %s : No such file or directory\n",arg[1]);
	}
	newpath = ft_take_pwd_old("PWD=");
	ft_cd_norm(env,oldpath,"OLDPWD");
	ft_cd_norm(env,newpath,"PWD");
	free(oldpath);
	free(newpath);
}

void ft_exit(char **arg,char **env)
{
	int i;
	int t;

	t = 0;
	i = 0;
	while(arg[i])
		i++;
	ft_putstr_fd("exit\n",1);
	if(i > 2)
		printf("minishell: exit: too many arguments\n");
	if(arg[1] && i <= 2)
		t = atoi(arg[1]);
	i = 0;
	while(env[i++])
		free(env[i]);
	exit(t);
	
}