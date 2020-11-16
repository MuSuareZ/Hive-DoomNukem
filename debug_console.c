#include "doom-nukem.h"
#include <stdio.h>

void 	debug_model_walls(void)
{
	int		wc;
	t_wall	*wall;

	wc = get_model()->wall_count;
	if (wc == 0)
		return (ft_putendl("Outputting no data to console for models' walls, wall count was 0."));
	printf("Outputting data to console for models' %d walls\n", wc);
	wall = get_model()->wall_first;
	while (wc--)
	{
		printf("Wall id: %d | start: %d %d | end: %d %d",
			   wall->id, wall->start.x, wall->start.y, wall->end.x, wall->end.y);
		if (wall->next == NULL)
			printf(" | next: NULL\n");
		else
		{
			printf(" | next_id: %d\n", wall->next->id);
			if (get_model()->walls == wall->next)
				ft_putendl("Confirmed a link from wall->next to mdl->walls.");
			wall = wall->next;
		}
	}

	printf("mdl->walls: ");
	if (get_model()->walls == NULL)
		printf("NULL\n");
	else
	{
		wall = get_model()->walls;

		printf("Wall id: %d | start: %d %d | end: %d %d\n",
			   wall->id, wall->start.x, wall->start.y, wall->end.x, wall->end.y);
	}
}

void    output_walls(int wall_count, t_wall *walls)
{
    printf("Outputting data to console for %d walls\n", wall_count);
    while (wall_count--)
    {
        printf("Wall id: %d | start: %d %d | end: %d %d\n",
               walls->id, walls->start.x, walls->start.y, walls->end.x, walls->end.y);
        walls = walls->next;
    }
}

void    output_rooms(int room_count, t_room *rooms)
{
    printf("Outputting data to console for %d rooms\n", room_count);
    while (room_count--)
    {
        printf("Room id: %d | first_wall_id: %d | wall_count: %d | floor_height: %d | roof_height: %d\n",
                rooms->id, rooms->first_wall_id, rooms->wall_count, rooms->floor_height, rooms->roof_height);
        rooms = rooms->next;
    }
}