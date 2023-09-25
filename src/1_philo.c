/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:35 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/25 11:34:37 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	check_args(int ac, char *av[])
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		printf(RED"Number of arguments not valid\n"RESET);
		exit (1);
	}
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] == '-')
				j++;
			if (av[i][j] < '0' || av[i][j] > '9')
				exit_error(RED"Error: Arguments must be numbers\n"RESET,
					NULL, 0);
		}
	}
}

int	main(int ac, char *av[])
{
	t_project	project;

	check_args(ac, av);
	init_project(&project, ac, av);
	init_mtxs(&project);
	init_philo(&project);
	init_thread(&project);
	free_mtxs(&project);
}
