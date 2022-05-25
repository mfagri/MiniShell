/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:25:32 by mfagri            #+#    #+#             */
/*   Updated: 2022/05/25 18:46:40 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_print_export_error(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return;
}

void ft_print_export(char **t, int i)
{
	int j;
	int k;
	int l;
	
	i  = -1;
	while(t[++i])
	{
		k = 0;
		if (t[i][0])
			write (1, "declare -x ", 12);
		j = -1;
		l = 0;
		while (t[i][++j])
		{
			write(1, &t[i][j], 1);
			if(t[i][j] == '=')
			{
				k = 1;
				if(l == 0)
				{
					l = 1;
					write (1, "\"", 1);
				}
			}
		}
		if(k == 1)
			write (1, "\"", 1);
		write (1, "\n", 1);
	}
}

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122)
		|| (c >= 65 && c <= 90))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int ft_do_nothing(char *arg)
{
	int j;
	int a;
	int n;
	
	a = 0;
	n = 0;
	j = 0;
	while (arg[j])
	{
		if(!(ft_isalpha(arg[j])) && (arg[j] != '_'))
			break;
		if(ft_isalpha(arg[j]))
			a++;
		if(arg[j] == '_')
			n++;
		j++;
	}
	if(n == 2)
		return 0;
	else if(n == 1 && a == 0)
		return 1;
	return 0;
}

char	*final_srt(char *arg,char *name,int i)
{
	char *value;
	char *f;
	int j;

	f = malloc(1);
	f[0] = '\0'; 
	value = malloc(ft_strlen(arg) - i + 1);
	j = 0;
	i++;
	while(arg[i])
		value[j++] = arg[i++];
	value[i] = '\0';
	f = ft_strjoin(f,name);
	if(strchr(arg,'='))
		f = ft_strjoin(f,"=");
	if(value[0])
		f = ft_strjoin(f,value);
	return (f);
}

void set_new_norm(char **env,char *name,char *f)
{
	int i;
	int j;
	
	i = -1;
	while(env[++i])
		if(!ft_strncmp(env[i],name,ft_strlen(name)))
		{
			j = 123456;
			if(strchr(f,'='))
				env[i] = cpy (env[i], f);
		}
	if(j != 123456)
	{
		env[i] = cpy (env[i], f);
		i++;
	}
	env[i] = NULL;
	return;
}

void	set_new(char *arg,char **env)
{
	int i;
	char *name;
	char *f;
	int j;

	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	name = malloc(i + 1);
	i =-1;
	while (arg[++i] != '=' && arg[i])
		name[i] = arg[i];
	name[i] = '\0';
	f = final_srt(arg,name,i);
	set_new_norm(env,name,f);
	return ;
}

char *final_srt_add(char *value,char *name)
{
	char *f;
	
	f = malloc(1);
	f[0] = '\0';
	f = ft_strjoin(f,name);
	f = ft_strjoin(f,"=");
	f = ft_strjoin(f,value);
	return (f);
}

void	add_to_env_norm(char *name,char *value,char *f,char **env)
{
	int i;
	int j;
	
	i = -1;
	while(env[++i])
		if(!ft_strncmp(env[i],name,ft_strlen(name)))
		{
			j = 123456;
			if(strchr(env[i],'='))
				env[i] = ft_strjoin(env[i],value);
			else
			{
				env[i] = ft_strjoin(env[i],"=");
				env[i] = ft_strjoin(env[i],value);	
			}
		}
	if(j != 123456)
	{
		env[i] = cpy (env[i], f);
		i++;
	}
	env[i] = NULL;
	return ;
}

void	add_to_env(char *arg,char **env)
{
	int i;
	char *name;
	char *value;
	char *f;
	int j;

	i = 0;
	while (arg[i] != '+')
		i++;
	name = malloc(i + 1);
	i =-1;
	while (arg[++i] != '+')
		name[i] = arg[i];
	name[i] = '\0'; 
	value = malloc(ft_strlen(arg) - i + 1);
	j = 0;
	i++;
	if(arg[i] == '=')
		i++;
	while(arg[i])
		value[j++] = arg[i++];
	value[i] = '\0';
	f = final_srt_add(value,name);
	add_to_env_norm(name,value,f,env);
	return;
}

void check_arg_export(char *arg,char **env)
{
	int j;
	
	if(!(ft_isalpha(arg[0])) && arg[0] != '_')
		return(ft_print_export_error(arg));
	j = 0;
	while((ft_isalpha(arg[j])) || arg[j] == '_')
		j++;
	if(ft_do_nothing(arg))
		return ;
	else
		if(arg[j] == '+')
		{
			if(arg[j+1] == '+' || arg[j+1] != '=')
				return(ft_print_export_error(arg));
			add_to_env(arg,env);
		}
		else if (arg[j] == '=')
			set_new(arg,env);
		else if (!(strchr(arg,'=')) && !(strchr(arg,'+')))
			set_new(arg,env);
	return ;
}

char	**ft_sort_env(char **env)
{
	char **t;
	int i;
	int k;
	int j;
	
	i = 0;
	while(env[i])
		i++;
	t = malloc(sizeof(char *) * (i + 1));
	t[i] = NULL;
	i = -1;
	while(env[++i])
	{
		j = -1;
		k = 0;
		while(env[++j])
			if(ft_strncmp(env[i],env[j],ft_strlen(env[i])) > 0)
				k++;
		t[k] = cpy(t[k], env[i]);
	}
	return (t);
}

void	ft_export(char **env,char **arg)
{
	int i;
	char **t;
	t = ft_sort_env(env);
	i = 1;
	if(!arg[i])
		ft_print_export(t,-1);
	else
		while(arg[i])
			check_arg_export(arg[i++],env);
}