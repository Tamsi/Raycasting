/*
** raycast.c for   in /home/tbesson/raytest/raycasting
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Mon Jan  2 15:02:06 2017 Tamsi Besson
** Last update Wed Jan  4 21:19:10 2017 Tamsi Besson
*/

#include "my.h"

//float raycast(sfVector2f pos, float direction, int **map, sfVector2i mapSize)
float raycast(t_my_framebuffer *framebuffer, t_pdir camera, sfVector2f plan)
{
  int   x;
  //float line_h;

  x = 0;
  while (x < SCREEN_WIDTH)
    {
      int		hit = 0;
      int		side;
      sfVector2i  step;
      sfVector2i	my_map;
      t_pdir		ray;
      double		perpWallDist;
      double		camReduc;
      t_coo   sideDist;
      t_coo   deltaDist;

      //rays + reduction orthonormée
      camReduc = ((2 * x) / (double)SCREEN_WIDTH - 1);
      ray.pos.y = camera.pos.y;
      ray.pos.x = camera.pos.x;
      ray.dir.x = camera.dir.x + plan.x * camReduc;
      ray.dir.y = camera.dir.y + plan.y * camReduc;

      my_map.x = (int)ray.pos.x;
      my_map.y = (int)ray.pos.y;
      deltaDist.x = sqrt(1 + (ray.dir.y * ray.dir.y) / (ray.dir.x * ray.dir.x));
      deltaDist.y = sqrt(1 + (ray.dir.x * ray.dir.x) / (ray.dir.y * ray.dir.y));
      if (ray.dir.x < 0)
        {
          step.x = -1;
          sideDist.x = (ray.pos.x - my_map.x) * deltaDist.x;
        }
      else
        {
          step.x = 1;
          sideDist.x = (my_map.x + 1.0 - ray.pos.x) * deltaDist.x;
        }
      if (ray.dir.y < 0)
        {
          step.y = -1;
          sideDist.y = (ray.pos.y - my_map.y) * deltaDist.y;
        }
      else
        {
          step.y = 1;
          sideDist.y = (my_map.y + 1.0 - ray.pos.y) * deltaDist.y;
        }
      while (hit == 0)
        {
          if (sideDist.x < sideDist.y)
            {
              sideDist.x += deltaDist.x;
              my_map.x += step.x;
              side = 0;
            }
          else
            {
              sideDist.y += deltaDist.y;
              my_map.y += step.y;
              side = 1;
            }
          if (map[my_map.x][my_map.y] > 0)
            hit = 1;
        }
      if (side == 0)
        perpWallDist = (my_map.x - ray.pos.x + (1 - step.x) / 2) / ray.dir.x;
      else
        perpWallDist = (my_map.y - ray.pos.y + (1 - step.y) / 2) / ray.dir.y;

      float line_h;
      line_h = (float)(SCREEN_HEIGHT / perpWallDist);
      draw_vert(x, (int)line_h, framebuffer, my_map);
      x++;
    }
}

void  draw_vert(int x, int line_h, t_my_framebuffer *framebuffer, sfVector2i my_map)
{
  int draw_start;
  int draw_end;
  sfVector2i  from;
  sfVector2i  to;
  sfColor color;

  draw_start = SCREEN_HEIGHT / 2 - line_h / 2;
  if (draw_start < 0)
    draw_start = 0;
  draw_end = SCREEN_HEIGHT / 2 + line_h / 2;
  if (draw_end >= SCREEN_HEIGHT)
    draw_end = SCREEN_HEIGHT - 1;
  from.x = x;
  to.x = SCREEN_WIDTH;
  from.y = 0;
  to.y = draw_start;
  my_draw_line(framebuffer, from, to, sfBlack);
  from.y = draw_start;
  to.y = draw_end;
  if (map[my_map.x][my_map.y] == 1)
    color = sfBlue;
  else if (map[my_map.x][my_map.y] == 2)
    color = sfRed;
  my_draw_line(framebuffer, from, to, color);
  from.y = draw_end;
  to.y = SCREEN_HEIGHT;
  my_draw_line(framebuffer, from, to, sfBlack);
}