/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:28:00 by krusthol          #+#    #+#             */
/*   Updated: 2020/09/19 04:56:26 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_player	*init_player(t_xyz pos, t_xyz rot, int hp)
{
	t_player *p;

	if ((p = (t_player*)malloc(sizeof(t_player))))
	{
		p->hp.max = hp;
		p->hp.cur = p->hp.max;
		p->pos = pos;
		p->angle = rot;
		ft_memset(&(p->wep), 0, sizeof(t_weapon));
	}
	return (p); // Returns NULL if malloc fails, sets values if succeeds.
}
void 		init_game(t_doom *doom, int argc, char **argv)
{
	doom->game = (t_game*)malloc(sizeof(t_game));
	doom->player = init_player(vec3_zero(), vec3_zero(), 100);
	if (!doom->game || !doom->player)
		ft_die("Fatal error: Mallocing game/player struct failed at init_game.");
	doom->game->parent = doom;
	doom->game->win = SDL_CreateWindow("DoomNukem Play Level", SDL_WINDOWPOS_CENTERED,
									  SDL_WINDOWPOS_CENTERED, GAME_WIN_WIDTH, GAME_WIN_HEIGHT, 0);
	if (!doom->game->win)
		ft_die("Fatal error: SDL_CreateWindow failed at init_game.");
	doom->game->buff = SDL_GetWindowSurface(doom->game->win);
	if (!doom->game->buff)
		ft_die("Fatal error: SDL_GetWindowSurface failed at init_game.");
	if (argc == 2)
		doom->game->map_path = argv[1];
	else
		ft_die("Fatal error: No map specified as argument to load with Play Level.");
	if (0 != SDL_SetRelativeMouseMode(SDL_TRUE))
		ft_die("Fatal error: SDL_SetRelativeMouseMode not supported!");
}

void 		destroy_game(t_doom *doom)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_FreeSurface(doom->game->buff);
	SDL_DestroyWindow(doom->game->win);
	doom->game->win = NULL;
	doom->game->buff = NULL;
	free(doom->game);
	doom->game = NULL;
}

static void show_vec(t_xyz v, const char *name)
{
	printf("'%4.4s' { %8.3f | %8.3f | %8.3f }\n",
		name, v.x, v.y, v.z
	);
}

void 		game_mouse_motion(t_doom *doom)
{
	SDL_MouseMotionEvent	e = doom->event.motion;
	t_euler					*rot = &(doom->player->angle);
	SDL_Surface				*surface = doom->game->buff;
	printf("%d %d %d %d\n", e.x, e.y, e.xrel, e.yrel);

	SDL_memset(surface->pixels, 0, surface->h * surface->pitch);

	// X is the "forward" axis. Rotating around it would barrelroll our camera.

	// Z is the "up" axis. Horizontal mouse movement turns us left/right.
	//	To turn left/right, we must rotate around the up-axis.
	rot->z += e.xrel * 0.5;

	// Y is the "side" (left or right, TBD) axis. Vertical mouse movement turns us up/down.
	//	To turn up/down, we must rotate around the side-axis.
	rot->y += e.yrel * 0.5;

	// Note: Right now, Y is effectively left-handed (towards right)
	//	because of the natural Y direction of screen coordinates.
	//	(Mouse down == Positive screen Y == angle Y + value)
	//	(Mouse up   == Negative screen Y == angle Y - value)

	// Let's keep us in the -180:180 range for now...
	if (rot->z > 180)  rot->z -= 360;
	if (rot->z < -180) rot->z += 360;
	// Except vertical angle should be -90:90 degrees up/down.
	if (rot->y > 90)   rot->y = 90;
	if (rot->y < -90)  rot->y = -90;
	printf("player pitch %f, yaw %f\n", rot->y, rot->z);

	// Create 3 points to form a triangle (or any shape)
	// Note: The center or ORIGIN of the object is {0,0,0}
	t_xyz A = (t_xyz){0, 1, 0};
	t_xyz B = (t_xyz){1, 1, 0};
	t_xyz C = (t_xyz){1, 0, 0};
	t_xyz D = (t_xyz){1.5, 1.5, 0};
	t_xyz TA = A;
	t_xyz TB = B;
	t_xyz TC = C;
	t_xyz TD = D;

	// 1. First rotate the points around their origin
	t_matrix ry = rotate_y(rot->y * DEG_TO_RAD);
	TA = vec3_transform(TA, ry);
	TB = vec3_transform(TB, ry);
	TC = vec3_transform(TC, ry);
	TD = vec3_transform(TD, ry);
	t_matrix rz = rotate_z(rot->z * DEG_TO_RAD);
	TA = vec3_transform(TA, rz);
	TB = vec3_transform(TB, rz);
	TC = vec3_transform(TC, rz);
	TD = vec3_transform(TD, rz);

	// 2. Then translate them into world coordinates
	// Note: this triangle's new origin will be {2,2,0}
	// Note: Points A,B,C,D will be relative to the new origin.
	// Note: This becomes more relevant with other objects.
	t_matrix t = translation(2, 2, 0);
	TA = vec3_transform(TA, t);
	TB = vec3_transform(TB, t);
	TC = vec3_transform(TC, t);
	TD = vec3_transform(TD, t);

	// 3. Finally transform them by the projection matrix
	t_matrix m = perspective(90, 0.1, 1000);
	TA = vec3_transform(TA, m);
	TB = vec3_transform(TB, m);
	TC = vec3_transform(TC, m);
	TD = vec3_transform(TD, m);

	// 4. Scale the NDC space (-1:1) to real pixel coordinates.
	t_matrix s = scale(GAME_MID_X, GAME_MID_Y, 1);
	TA = vec3_transform(TA, s);
	TB = vec3_transform(TB, s);
	TC = vec3_transform(TC, s);
	TD = vec3_transform(TD, s);
	show_vec(TA, "4 TA");
	show_vec(TB, "4 TB");
	show_vec(TC, "4 TC");

	ft_draw(surface->pixels, TA, TB, 0xFF0000);
	ft_draw(surface->pixels, TB, TC, 0x00FF00);
	ft_draw(surface->pixels, TC, TA, 0x0000FF);
	ft_draw(surface->pixels, TB, TD, 0xFF8000);
}

void 		game_mouse_down(t_doom *doom)
{
	uint32_t  color;

	color = 0xff00ff00;
	set_pixel(doom->game->buff, doom->event.motion.x, doom->event.motion.y, color);
	set_pixel(doom->game->buff,doom->event.motion.x+1, doom->event.motion.y+1, color);
	set_pixel(doom->game->buff,doom->event.motion.x+1, doom->event.motion.y-1, color);
	set_pixel(doom->game->buff,doom->event.motion.x-1, doom->event.motion.y+1, color);
	set_pixel(doom->game->buff,doom->event.motion.x-1, doom->event.motion.y-1, color);
}

void 		game_loop(t_doom *doom)
{
	// Random placeholder demo
	static int cooldown = 0;
	if (!cooldown)
	{
		ft_putendl("Game looping!");
		cooldown = 100;
	} else
		cooldown--;
	set_pixel(doom->game->buff,cooldown+1, cooldown+1, 0xffffffff);
	set_pixel(doom->game->buff,cooldown, cooldown, 0xff000000);
}

void		game_render(t_doom *doom)
{
	SDL_UpdateWindowSurface(doom->game->win);
}
