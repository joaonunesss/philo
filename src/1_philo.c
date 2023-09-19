/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:35 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/19 15:41:13 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
	here is the function that starts the program
	1) we check if the arguments are correct
		- the arguments must be numbers
		- there must be 4 or 5 arguments
	2) we initialize the variables of the project structure
		- in ft_initialize_thread we create the threads that make the program work
	3) lastly, we free everything that we have allocated
*/

void	check_args(int ac, char *av[])
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		printf("Number of arguments not valid\n");
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
				exit_error("Error: Arguments must be numbers\n", NULL, 0);
		}
	}
}

int	main(int ac, char *av[])
{
	t_project	project;

	check_args(ac, av);
	initialize_project(&project, ac, av);
	initialize_philo(&project);
	initialize_mtxs(&project);
	initialize_thread(&project);
	free_mtxs(&project);
}
