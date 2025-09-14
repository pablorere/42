/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:42:38 by silvertape        #+#    #+#             */
/*   Updated: 2025/09/14 16:33:05 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/* Agrega argumentos a la pila A */
/* Requiere: validaciones y creación de nodos */

// While arguments are valid, we start to add them 
// into stack here one by one with while loop.
// ft_atoi2 takes the number, validates it, and converts it 
// to an integer value with proper error checking.
// With stack new we create a new node for the current 
// argument without linking it to list.
// We make linking stage in ft_add_back call.
void	list_args(char **argv, t_stack **stack_a)
{
	long	i;

	i = 1;
	while (argv[i] != NULL)
	{
		ft_add_back(stack_a, ft_stack_new(ft_atoi2(argv[i])));
		i++;
	}
}
