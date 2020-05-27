/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 19:47:16 by cclaude           #+#    #+#             */
/*   Updated: 2020/05/27 14:49:02 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTSP_H
# define BTSP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define MISS 0
# define HIT 1
# define SUNK 2
# define BLOCKED 3

typedef struct	s_btsp
{
	char		**map;
	int			**pdm;
}				t_btsp;

#endif
