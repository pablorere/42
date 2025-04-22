/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:43:42 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/04/22 21:32:13 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_print_base(unsigned long str, int i);
int	ft_print_char(char c);
int	ft_print_str(char *str);
int	ft_print_nbr(int nbr);
int	ft_print_nbr_2(unsigned int nbr);
int	ft_printf_p(char *a);
int	ft_printf(const char *input, ...);

#endif
