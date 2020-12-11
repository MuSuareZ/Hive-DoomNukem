#include "doom-nukem.h"

void			edt_mouse_motion(t_doom *doom)
{
	t_state		*state;

	state = get_state();
	if (state->gui->has_motion)
		state->gui->motion(doom->event.motion.x, doom->event.motion.y);
}

void			edt_mouse_down(t_doom *doom)
{
	t_state		*state;

	state = get_state();
	if (doom->event.type == SDL_MOUSEWHEEL)
	{
		edt_swap_mode(state);
		return ;
	}
	if (doom->event.button.button == SDL_BUTTON_LEFT)
		state->gui->left_click(doom->event.button.x, doom->event.button.y);
	if (doom->event.button.button == SDL_BUTTON_MIDDLE)
		state->gui->middle_click(doom->event.button.x, doom->event.button.y);
	if (doom->event.button.button == SDL_BUTTON_RIGHT)
		state->gui->right_click(doom->event.button.x, doom->event.button.y);
}

void			edt_keystate_input(t_doom *doom)
{
	static int	lock_w = 0;
	static int	lock_e = 0;
	static int	lock_z = 0;
	static int	lock_x = 0;
	static int	lock_s = 0;

	handle_keyboard_scrolling(doom);

	if (lock_w && !doom->keystates[SDL_SCANCODE_W])
		lock_w = 0;
	else if (doom->keystates[SDL_SCANCODE_W] && !lock_w)
	{
		debug_model_walls();
		lock_w = 1;
	}

	if (lock_e && !doom->keystates[SDL_SCANCODE_E])
		lock_e = 0;
	else if (doom->keystates[SDL_SCANCODE_E] && !lock_e)
	{
		debug_model_enemies();
		debug_model_player();
		lock_e = 1;
	}

	if (lock_z && !doom->keystates[SDL_SCANCODE_Z])
		lock_z = 0;
	else if (doom->keystates[SDL_SCANCODE_Z] && !lock_z)
	{
		edt_inward_zoom();
		lock_z = 1;
	}

	if (lock_x && !doom->keystates[SDL_SCANCODE_X])
		lock_x = 0;
	else if (doom->keystates[SDL_SCANCODE_X] && !lock_x)
	{
		edt_outward_zoom();
		lock_x = 1;
	}

	if (lock_s && !doom->keystates[SDL_SCANCODE_S])
		lock_s = 0;
	else if (doom->keystates[SDL_SCANCODE_S] && !lock_s)
	{
		edt_swap_mode(get_state());
		lock_s = 1;
	}
}

