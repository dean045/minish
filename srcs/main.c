/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:25 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 00:17:12 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_all all;

void	init_all()
{
	all.g_mem = NULL;
}

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
	all.utils->can_run = 0;
	all.utils->on_here_doc = 0;
	all.utils->err = 130;
}

void	handle_sig()
{
	if (all.utils->on_here_doc == 1)
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
	all.utils = init_exec(envp);
	while (1)
	{
		handle_sig();
		ret = readline("\001\033[0;35m\002minishell\001\033[0m\033[0;32m ✗\033[0m\002 ");
		if (!ret)
		{
			printf("exit\n");
			ft_free_all();
			exit(0);
		}
		else if (ft_strlen(ret) != 0)
		{
			token = manage_cmd(ret, all.utils->envp);
			if (ret && *ret)
				add_history(ret);
			ft_free(ret);
			refresh(token, all.utils);
			if ( all.utils && all.utils->can_run == 1)
				exec(token, all.utils);
			clean( all.utils);
		}
	}
	return (0);
}
