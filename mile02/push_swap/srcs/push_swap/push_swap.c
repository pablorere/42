/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:39:36 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/09/14 14:17:26 by silvertape       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Resumen: programa push_swap: lee args, valida y ordena con operaciones. */
/* Requiere: libft, utilidades de parsing y operaciones de pila */

#include "../../includes/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;

	a = ft_parse(argc, argv);
	if (!a || ft_checkdup(a))
	{
		ft_free(&a);
		ft_error();
	}
	if (!ft_checksorted(a))
		ft_sort(&a);
	ft_free(&a);
	return (0);
}
