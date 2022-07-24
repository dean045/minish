/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:40:01 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 17:43:23 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_env_dir(t_exec	*utils, char *path)
{
	t_env	*temp;

	if (!utils->envp_lst)
	{
		utils->envp_lst = init_lst_env(utils->envp, utils);
		utils->envp = lst_to_char(utils->envp_lst);
	}
	temp = utils->envp_lst;
	while (temp)
	{
		if (!strncmp(temp->content, "PWD=", 4))
		{
			temp->content = ft_strjoin("PWD=", path);
			return ;
		}
		temp = temp->next;
	}
}

char	*get_home(t_exec *utils)
{
	t_env	*tmp;

	tmp = utils->envp_lst;
	while (tmp)
	{
		if (!strncmp("HOME=", tmp->content, 5))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int	manage_open_cd(char *path, t_exec *utils)
{
	if (opendir(path))
	{
		chdir(path);
		change_env_dir(utils, path);
		utils->err = 0;
		return (0);
	}
	else
	{
		perror("cd");
		utils->err = 1;
	}
	return (1);
}

int	cd(char *path, t_exec *utils)
{
	char	*tmp;

	utils->envp_lst = init_lst_env(utils->envp, utils);
	if (!path)
	{
		tmp = get_home(utils);
		if (tmp)
		{
			chdir(get_home(utils) + 5);
			change_env_dir(utils, get_home(utils) + 5);
			return (0);
		}
		else
		{
			write(2, "cd: HOME not set\n", 17);
			utils->err = 1;
		}
	}
	if (!manage_open_cd(path, utils))
		return (0);
	return (1);
}
