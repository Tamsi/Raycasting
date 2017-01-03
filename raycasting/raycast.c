/*
** raycast.c for   in /home/tbesson/raytest/raycasting
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Mon Jan  2 15:02:06 2017 Tamsi Besson
** Last update Tue Jan  3 15:41:41 2017 Tamsi Besson
*/

#include "my.h"

void raycast(t_my_framebuffer *pixels, pdir camera, sfVector2f plan)
{
  int   x = 0;

  while (x < SCREEN_WIDTH)
    {
      int		hit = 0;
      int		stepX, stepY;
      int		side;
      sfVector2i	my_map;
      sfVector2i	from;
      sfVector2i	to;
      pdir		ray;
      double		perpWallDist;
      double		camReduc;

      coo   sideDist;
      coo   deltaDist;

      //rays + reduction orthonormée
      camReduc = ((2 * x) / (double)SCREEN_WIDTH - 1);
      ray.pos.y = camera.pos.y;
      ray.pos.x = camera.pos.x;
      ray.dir.x = camera.dir.x + plan.x * camReduc;
      ray.dir.y = camera.dir.y + plan.y * camReduc;

      //DDA
      my_map.x = (int)ray.pos.x;
      my_map.y = (int)ray.pos.y;
      deltaDist.x = sqrt(1 + (ray.dir.y * ray.dir.y) / (ray.dir.x * ray.dir.x));
      deltaDist.y = sqrt(1 + (ray.dir.x * ray.dir.x) / (ray.dir.y * ray.dir.y));
      if (ray.dir.x < 0)
        {
          stepX = -1;
          sideDist.x = (ray.pos.x - my_map.x) * deltaDist.x;
        }
      else
        {
          stepX = 1;
          sideDist.x = (my_map.x + 1.0 - ray.pos.x) * deltaDist.x;
        }
      if (ray.dir.y < 0)
        {
          stepY = -1;
          sideDist.y = (ray.pos.y - my_map.y) * deltaDist.y;
        }
      else
        {
          stepY = 1;
          sideDist.y = (my_map.y + 1.0 - ray.pos.y) * deltaDist.y;
        }
      while (hit == 0)
        {
          if (sideDist.x < sideDist.y)
            {
              sideDist.x += deltaDist.x;
              my_map.x += stepX;
              side = 0;
            }
          else
            {
              sideDist.y += deltaDist.y;
              my_map.y += stepY;
              side = 1;
            }
          if (map[my_map.x][my_map.y] > 0)
            hit = 1;
        }
      if (side == 0)
        perpWallDist = (my_map.x - ray.pos.x + (1 - stepX) / 2) / ray.dir.x;
      else
        perpWallDist = (my_map.y - ray.pos.y + (1 - stepY) / 2) / ray.dir.y;

      int line_h;
      int draw_start, draw_end;

      line_h = (int)(SCREEN_HEIGHT / perpWallDist);

      draw_start = SCREEN_HEIGHT / 2 - line_h / 2;
      if (draw_start < 0)
        draw_start = 0;
      draw_end = SCREEN_HEIGHT / 2 + line_h / 2;
      if (draw_end >= SCREEN_HEIGHT)
        draw_end = SCREEN_HEIGHT - 1;

      sfColor color;
      int y = 0;

      from.x = x;
      to.x = SCREEN_WIDTH;
      from.y = 0;
      to.y = draw_start;
      color = sfBlack;
      my_draw_line(pixels, from, to, color);
      from.y = draw_start;
      to.y = draw_end;
      if (map[my_map.x][my_map.y] == 1)
	color = sfBlue;
      else if (map[my_map.x][my_map.y] == 2)
	color = sfRed;
      my_draw_line(pixels, from, to, color);
      from.y = draw_end;
      to.y = SCREEN_HEIGHT;
      color = sfBlack;
      my_draw_line(pixels, from, to, color);
      x++;
    }
}
