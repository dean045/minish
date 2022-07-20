/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:33:41 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/20 21:20:06 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	here_doc(char *limiter, t_node *node, int i)
{
	char	*buff;
	char	*num_str;
	int		x;

	num_str = ft_itoa(i);
	node->here_doc = ft_strjoin(".here_doc_tmp", num_str);
	free(num_str);
	node->here_doc_fd = open(node->here_doc, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (node->here_doc_fd == -1)
		return ;
	x = dup(0);
	while (1 && utils->can_run == 1)
	{
		buff = readline("> ");
		if (!buff && utils->can_run != 0)
		{
			write(2, "warning: here-document delimited by end-of-file.\n", 49);
			break;
		}
		if (utils->can_run == 0)
		{
			dup2(x, 0);
			break ;
		}
		if (!ft_strcmp(buff, limiter))
			break ;
		else
		{
			write(node->here_doc_fd, buff, ft_strlen(buff));
			write(node->here_doc_fd, "\n", 1);
		}
	}
	//close(node->here_doc_fd);
	free(buff);
}

void here_doc_init(t_node *node, t_token *token)
{
	int	i;

	i = 1;
	utils->on_here_doc = 1;
	handle_sig();
	while (token && token->type != PIPE && ++i && utils->can_run == 1)
	{
		if (token && token->type == DR_IN && token->next && token->next->type == LIMITOR)
		{
			if (node->here_doc_fd > 0)
			{
				close(node->here_doc_fd);
				unlink(node->here_doc);
			}
			here_doc(token->next->word, node, i);
		}
		token = token->next;
	}
	utils->on_here_doc = 0;
	handle_sig();
}