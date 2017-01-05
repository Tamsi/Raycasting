/*
** raycast.c for   in /home/tbesson/raytest/raycasting
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Mon Jan  2 15:02:06 2017 Tamsi Besson
** Last update Thu Jan  5 11:46:41 2017 Tamsi Besson
*/

#include "my.h"

float raycast(sfVector2f pos, float direction, sfVector2i mapSize)
{
  //degres->radian => degres * (pi / 180)
  int		hit = 0;
  int		side;
  float line_h;
  float perpWallDist;
  sfVector2i  step;
  sfVector2f  dir;
  sfVector2f   sideDist;
  t_coo   deltaDist;

  dir.x = cos(direction);
  // * G_LEN;
  dir.y = sin(direction);
  // * G_LEN;
  //printf(" x = %f, y = %f", dir.x, dir.y);
  deltaDist.x = sqrt(1 + (dir.y * dir.y) / (dir.x * dir.x));
  deltaDist.y = sqrt(1 + (dir.x * dir.x) / (dir.y * dir.y));
  if (dir.x < 0)
    {
      step.x = -1;
      sideDist.x = (pos.x - G_MAP_COO.x) * deltaDist.x;
    }
  else
    {
      step.x = 1;
      sideDist.x = (G_MAP_COO.x + 1.0 - pos.x) * deltaDist.x;
    }
  if (dir.y < 0)
    {
      step.y = -1;
      sideDist.y = (pos.y - G_MAP_COO.y) * deltaDist.y;
    }
  else
    {
      step.y = 1;
      sideDist.y = (G_MAP_COO.y + 1.0 - pos.y) * deltaDist.y;
    }
  while (hit == 0)
    {
      if (sideDist.x < sideDist.y)
        {
          sideDist.x += deltaDist.x;
          G_MAP_COO.x += step.x;
          side = 0;
        }
      else
        {
          sideDist.y += deltaDist.y;
          G_MAP_COO.y += step.y;
          side = 1;
        }
      if (map[G_MAP_COO.x][G_MAP_COO.y] > 0)
        hit = 1;
    }
  if (side == 0)
    perpWallDist = (G_MAP_COO.x - pos.x + (1 - step.x) / 2) / (dir.x);
  else
    perpWallDist = (G_MAP_COO.y - pos.y + (1 - step.y) / 2) / (dir.y);
  line_h = (float)(SCREEN_HEIGHT / perpWallDist);
  return (line_h);
}

/*int my_DDA(t_coo sideDist, t_coo deltaDist)
{
  int hit;
  int side;

  
  return (side);
}*/

void  draw_vert(int x, int line_h, t_my_framebuffer *framebuffer)
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
  my_draw_line(framebuffer, from, to, sfCyan);
  from.y = draw_start;
  to.y = draw_end;
  if (map[G_MAP_COO.x][G_MAP_COO.y] == 1)
    color = sfRed;
  else if (map[G_MAP_COO.x][G_MAP_COO.y] >= 2)
    color = sfBlue;
  my_draw_line(framebuffer, from, to, color);
  from.y = draw_end;
  to.y = SCREEN_HEIGHT;
  my_draw_line(framebuffer, from, to, sfGreen);
}
