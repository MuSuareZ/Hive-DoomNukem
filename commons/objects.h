/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:17:53 by krusthol          #+#    #+#             */
/*   Updated: 2021/01/25 18:04:39 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "doom-nukem.h"

enum 	e_sprite_categories { FRONT_ATTACK };

typedef struct 			s_doom t_doom;

typedef struct 			s_point
{
	int 				x;
	int 				y;
}						t_point;

typedef struct			s_coord
{
	double				x;
	double				y;
}						t_coord;

typedef struct 			s_tri_sides
{
	double				a;
	double 				b;
	double				c;
}						t_tri_sides;

typedef struct 			s_health
{
	int 				max;
	int 				cur;
}						t_health;

typedef struct 			s_weapon
{
	int 				type_id;
	int 				dmg;
	int 				ammo_cur;
	int					ammo_res;
	int 				ammo_max;
	int					do_own;
	int 				cooldown;
	int 				reload_time;
	struct SDL_Surface	*weap_img;
	struct Mix_Chunk 	*fire_sound;
	struct Mix_Chunk	*reload_sound;
}						t_weapon;

typedef struct 			s_player
{
	double				rot_horizontal;
	double				rot_vertical;
	double 				x;
	double 				y;
	int 				rot;
	int					height;
	int					is_jumping;
	int					is_crouching;
	int					is_running;
	int					mov_speed;
	int					max_speed;
	int					min_speed;
	int					run_lock;
	int					crouch_lock;
	int					rot_speed;
	int					shoot_cd;
	int					reload_time;
	int					weap_id;
	int					shooting;
	struct SDL_Surface	*hud_num[10];
	struct s_coord		bullet_pos;
	struct s_weapon		weap_arr[10];
	struct s_point		tail;
	struct s_health		hp;
	struct s_weapon		wep;
}						t_player;

typedef struct          s_ai
{
	int                 type_id;
	int                 min_dis;
	int                 max_dis;
	int                 aggro;
	int                 mov_speed;
	int                 dmg;
}                       t_ai;

typedef struct			s_animation
{
	SDL_Surface 		**surfaces;
	int 				frames;
	int 				current;
	int					done;
}						t_animation;

typedef struct 			s_enemy
{
	int 				id;
	int 				x;
	int 				y;
	int 				rot;
	int					did_shoot;
	int					who_shot;
	int					shoot_cd;
	int					anim_phase;
	uint32_t			ray_color;
	struct s_ai			ai;
	struct s_coord		bullet_pos;
	struct s_point		tail;
	struct s_health		hp;
	struct s_weapon		wep;
	struct s_enemy		*next;
	struct s_animation	anim;
	struct SDL_Surface	*active_sprite;
}						t_enemy;

typedef struct 			s_wall
{
	struct s_point		start;
	struct s_point		end;
	int 				id;
	struct s_wall		*next;
}						t_wall;

typedef struct 			s_room
{
	struct s_wall		*first_wall;
	int 				first_wall_id;
	int 				id;
	int 				wall_count;
	int 				floor_height;
	int 				roof_height;
	t_point 			visual;
	struct s_room		*next;
}						t_room;

enum	e_pickup_flavors { PICKUP_HEALTH, PICKUP_AMMO, PICKUP_WEAPON };
# define PICKING_RADIUS 10

typedef struct 			s_pickup
{
	int 				id;
	struct s_point		loc;
	int 				flavor;
	int 				weapon_type_id;
	struct s_pickup		*next;
}						t_pickup;

typedef struct 			s_sounds
{
	struct Mix_Chunk 	*mcThunder;
	struct Mix_Chunk 	*mcSteam;
	struct Mix_Chunk	*mcPlop;
	struct Mix_Chunk	*mcSword;
	struct Mix_Chunk	*mcPistolRld;
	struct Mix_Chunk	*mcAssaultRld;
	struct Mix_Chunk	*mcSmgRld;
	struct Mix_Chunk	*mcSmgShot;
	struct Mix_Chunk	*mcPistolShot;
	struct Mix_Chunk	*mcAssaultShot;
	struct Mix_Chunk	*mcWalking;
	struct Mix_Chunk	*mcRunning;
	struct Mix_Chunk	*mcCrouching;
	struct Mix_Chunk	*mcEnemyDeath;
	struct Mix_Chunk	*mcHealthPickup;
	struct Mix_Chunk	*mcAmmoPickup;
	struct Mix_Chunk	*mcWeaponPickup;
	int					footstep_delay;
}						t_sounds;

typedef struct 			s_sprites
{
	// Underlying data holders, invididually named for readability
	struct SDL_Surface	*txt_ranged_front_attack;
	struct SDL_Surface	*txt_ranged_front_idle;
	struct SDL_Surface	**txt_ranged_front_walk;
	struct SDL_Surface	*txt_ranged_side_attack;
	struct SDL_Surface	*txt_ranged_side_idle;
	struct SDL_Surface	**txt_ranged_side_walk;
	struct SDL_Surface	**txt_ranged_death;

	struct SDL_Surface	**txt_melee_front_attack;
	struct SDL_Surface	**txt_melee_front_walk;
	struct SDL_Surface	**txt_melee_side_attack;
	struct SDL_Surface	**txt_melee_side_walk;
	struct SDL_Surface	*txt_melee_front_idle;
	struct SDL_Surface	*txt_melee_side_idle;
	struct SDL_Surface	**txt_melee_death;

	struct SDL_Surface	**txt_boss_front_attack;
	struct SDL_Surface	**txt_boss_front_walk;
	struct SDL_Surface	**txt_boss_side_attack;
	struct SDL_Surface	**txt_boss_side_walk;
	struct SDL_Surface	*txt_boss_front_idle;
	struct SDL_Surface	*txt_boss_side_idle;
	struct SDL_Surface	**txt_boss_death;
}						t_sprites;

typedef struct			s_menu
{
	int 				selected;
	struct s_animation	ani_thunder;
	int 				esc_lock;
	struct SDL_Surface	*alphabet[128];
	int 				alphabet_scale;
	SDL_Surface			*thunder;
	struct s_doom		*parent;
}						t_menu;

typedef struct 			s_line
{
	int					x1;
	int 				x2;
	int 				y1;
	int 				y2;
	int 				fx;
	int 				fy;
	int 				px;
	int 				py;
	uint32_t 			color;
	uint32_t 			avoid[4];
	struct SDL_Surface 	*buff;
	struct s_doom		*doom;
}						t_line;

typedef struct			s_image
{
	void				*ptr;
	int					*data;
	int					width;
	int					height;
	int					bpp;
	int					line;
	int					endian;
}						t_image;


/*
 * from alphabet.c
 * */

void 					print_glyph_str(const char *str, SDL_Surface *buff, int x, int y);

/*
 * from debug_console.c
 * */

void 					debug_model_player(void);
void		 			debug_model_enemies(void);
void 					debug_model_walls(void);
void					debug_model_rooms(void);
void					debug_model_portals(void);
void					debug_model_pickups(void);

/*
 * from texture.c
 * */

uint32_t 				get_exact_pixel(SDL_Surface *surface, int x, int y);
SDL_Surface				*xpm2surface(char *path);
SDL_Surface				*load_texture(t_doom *doom, char *path);

/*
 * from line.c and line_safe.c
 * */

void					render_line_safe(t_line *l);
void 					render_line(t_line *l);
void					careful_render_line(t_line *l);
void					preserve_render_line(t_line *l);
void					unpreserve_render_line(t_line *l);

/*
 * from pixel.c
 * */

void					flood_buffer(SDL_Surface *buff, uint32_t color);
void					set_protected_color(uint32_t color);
int 					set_pixel_safe(SDL_Surface *buff, int x, int y, uint32_t color);
void 					set_pixel(SDL_Surface *buff, int x, int y, uint32_t color);

/*
 * from rotation_math.c
 */

int			 			tail_degree_rot(t_point location, t_point *tail);

#endif
