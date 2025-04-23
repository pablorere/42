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

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define UPBASE "0123456789ABCDEF"
# define LOWBASE "0123456789abcdef"

int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnb(long n, int base, int boo, int len);
int	ft_printf(const char *input, ...);

#endif
