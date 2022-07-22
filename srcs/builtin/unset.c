/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:34:45 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 00:21:35 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset(char *var, t_exec *utils)
{
	int		size;
	t_env	*tmp;
	t_env	*tmp_lst;
	
	if (!check_parsing(var))
	{
		size = ft_strlen(var);
		if (!utils->envp_lst)
		{
			utils->envp_lst = init_lst_env(utils->envp, utils);
			utils->envp = lst_to_char(utils->envp_lst);
		}
		tmp_lst = utils->envp_lst;
		while (tmp_lst)
		{
			if (tmp_lst->next && !strncmp(tmp_lst->next->content, var, size))
			{
				tmp = tmp_lst->next->next;
				ft_free(tmp_lst->next);
				tmp_lst->next = NULL;
				tmp_lst->next = tmp;
				break ;
			}
			tmp_lst = tmp_lst->next;
		}
		free_env(utils->envp, size_tab(utils->envp));
		utils->envp = lst_to_char(utils->envp_lst);
		return (0);
	}
	return (0);
}