/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:25 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/22 01:13:19 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec *utils = NULL;

void ctrl_c(int test)
{
	(void)(test);
	write(2, "\n", 1);
    rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void    ctrl_c_here(int sig)
{
    (void)sig;
    write(2, "\n", 1);
	close(0);
	utils->can_run = 0;
	utils->on_here_doc = 0;
	utils->err = 130;
}

void	handle_sig()
{
	if (utils->on_here_doc == 1)
		signal(SIGINT, &ctrl_c_here);
	else
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*ret;
	(void)	av;
	t_token	*token;

	if (ac != 1)
	{
		printf("Error:	to many arguments.\n");
		return (1);
	}
	utils = init_exec(envp);
	while (1)
	{
		handle_sig();
		ret = readline("\033[0;35mminishell\033[0m\033[0;32m$>\033[0m ");
		if (!ret)
		{
			printf("exit\n");
			exit(0);
		}
		else if (ft_strlen(ret) != 0)
		{
			token = manage_cmd(ret, utils->envp);
			if (ret && *ret)
				add_history(ret);
			free(ret);
			refresh(token, utils);
			if (utils && utils->can_run == 1)
				exec(token, utils);
			clean(utils);
		}
	}
	return (0);
}
