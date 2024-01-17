#include "header.h"

void	rotate_left(t_game *game, double rotation_angle)
{
	double	oldDirX = game->rc.dir.x;
	double	oldPlaneX = game->rc.plane.x;

	game->rc.dir.x = game->rc.dir.x * cos(rotation_angle) - game->rc.dir.y * sin(rotation_angle);
	game->rc.dir.y = oldDirX * sin(rotation_angle) + game->rc.dir.y * cos(rotation_angle);
	game->rc.plane.x = game->rc.plane.x * cos(rotation_angle) - game->rc.plane.y * sin(rotation_angle);
	game->rc.plane.y = oldPlaneX * sin(rotation_angle) + game->rc.plane.y * cos(rotation_angle);
}

void	rotate_right(t_game *game, double rotation_angle)
{
	double	oldDirX = game->rc.dir.x;
	double	oldPlaneX = game->rc.plane.x;

	game->rc.dir.x = game->rc.dir.x * cos(-rotation_angle) - game->rc.dir.y * sin(-rotation_angle);
	game->rc.dir.y = oldDirX * sin(-rotation_angle) + game->rc.dir.y * cos(-rotation_angle);
	game->rc.plane.x = game->rc.plane.x * cos(-rotation_angle) - game->rc.plane.y * sin(-rotation_angle);
	game->rc.plane.y = oldPlaneX * sin(-rotation_angle) + game->rc.plane.y * cos(-rotation_angle);
}

void	get_starting_direction(t_game *game)
{
	if (game->map.starting_direction == 'N')
		return ;
	else if (game->map.starting_direction == 'S')
		rotate_right(game, PI);
	else if (game->map.starting_direction == 'E')
		rotate_right(game, PI / 2);
	else if (game->map.starting_direction == 'W')
		rotate_left(game, PI / 2);
}