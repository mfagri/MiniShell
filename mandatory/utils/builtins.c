/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 04:30:33 by mfagri            #+#    #+#             */
/*   Updated: 2022/05/25 15:43:52 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
int     ft_check_n(const char *s1, const char *s2)
{
    size_t i;
    i = 0;
    if ((!s1 || !s2))
        return (1);
	if (s1[i] == '-')
	{
		i++;
		while (s1[i])
		{
			if (s1[i] != 'n')
				return 1;
			i++;
		}
		return (0);
	}
    return (1);
}
void ft_echo(char **pr)
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
		ft_putstr_fd(pr[i],1);
		if (pr[i + 1] && pr[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
}
void ft_pwd()
{
	char s[1024];
	getcwd(s, sizeof(s));
	printf("%s\n",s);
}

void ft_cd(char **arg,char **env)
{
	int i;
	
	i = chdir(arg[1]);
	printf("%d\n",i);
}
void ft_print_env(char **env)
{
	int i;
	
	i = 0;
	while(env[i])
	{
		if(strchr(env[i],'='))
		{
		ft_putstr_fd(env[i],1);
		write(1,"\n",1);
		}
		i++;
	}
}
void remove_from_env(char *arg,char **env)
{
	int i;
	int j;
	int l;
	
	l = 0;
	i = 0;
	j = 0;
	if(!(ft_isalpha(arg[0])) && arg[0] != '_' && strchr(arg,'=') && strchr(arg,'+'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	i = 0;
	while(env[i])
	{
		j = i + 1;
		if(!ft_strncmp(env[i], arg, ft_strlen(arg)))
		{
			free (env[i]);
			l = 1;
			while(env[j])
			{
				env[i] = env[j];
				j++;
				i++;
			}
		}
		i++;
	}
	if(l)
		env[i-1] = NULL;
}
void ft_unset(char **arg,char **env)
{
	int i;
	i = 0;
	while (arg[++i])
		remove_from_env(arg[i],env);
}