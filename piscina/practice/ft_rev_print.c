/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:00:59 by ppaula-s          #+#    #+#             */
/*   Updated: 2025/02/28 09:09:47 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_rev_print(char *str)
{
	int count;
	
	count = 0;
	int ultimo;
	while  (str[count])
	{
		count++;
	}

	ultimo = count -1
	while ( ultimo >= 0)
	{
		write(1, &srt[ultimo], 1)
		ultimo--;
	}
	write(1, \n, 1);
	return (str);
}