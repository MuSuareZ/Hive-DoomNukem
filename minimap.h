/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 21:42:16 by msuarez-          #+#    #+#             */
/*   Updated: 2020/09/20 21:54:56 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "doom_nukem.h"
# define MINIMAP_WIN_WIDTH 400
# define MINIMAP_WIN_HEIGHT 400

typedef struct		s_minimap
{
	struct SDL_Window	*win;
	struct SDL_Surface	*buff;
	double				scale;
}					t_minimap;

void		init_minimap(t_doom *doom);

#endif

