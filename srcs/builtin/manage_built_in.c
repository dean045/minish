/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 01:50:59 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 19:39:13 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_env(t_exec *utils, char **envp)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*temp;

	if (!(*envp))
	{
		tmp = ft_malloc(sizeof(t_env));
		temp = ft_malloc(sizeof(char ) * 1024);
		tmp->content = getcwd(temp, sizeof(temp));
		tmp->next = NULL;
		tmp2 = ft_malloc(sizeof(t_env));
		tmp2->content = "SHLVL=1";
		tmp2->next = tmp;
		utils->envp_lst = tmp2;
		utils->envp = lst_to_char(utils->envp_lst);
	}
	else if (utils && envp)
	{
		utils->envp_lst = init_lst_env(envp, utils);
		utils->envp = lst_to_char(utils->envp_lst);
	}
	return (0);
}

int	is_built_in(t_token *token)
{
	if (!ft_strcmp(token->word, "cd")
		|| !ft_strcmp(token->word, "export") || !ft_strcmp(token->word, "unset")
		|| !ft_strcmp(token->word, "exit")
		|| !ft_strcmp(token->word, "env") || !ft_strcmp(token->word, "echo")
		|| !ft_strcmp(token->word, "pwd"))
		return (1);
	else
		return (-1);
}

int	manage_built_in(t_token *token, t_exec *utils)
{
	if (manage_built_in1(token))
		return (0);
	else if (manage_built_in2(token))
		return (1);
	else if (manage_built_in3(token, utils))
		return (1);
	else if (manage_built_in4(token))
		return (1);
	else if (!ft_strcmp(token->word, "exit"))
		ft_exit(g_all.utils);
	return (1);
}

int	is_last(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == ARG)
			return (0);
		token = token->next;
	}
	return (1);
}
