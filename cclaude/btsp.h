/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 19:47:16 by cclaude           #+#    #+#             */
/*   Updated: 2020/05/26 19:50:28 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTSP_H
# define BTSP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct	s_btsp
{
	char		**map;
	int			**pdm;
}				t_btsp;

#endif
