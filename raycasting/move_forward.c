/*
** move_forward.c for  in /home/tbesson/raytest/raycasting
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Tue Jan  3 15:36:38 2017 Tamsi Besson
** Last update Tue Jan  3 16:00:46 2017 Tamsi Besson
*/

#include "my.h"

sfVector2f	move_forward(sfVector2f pos, float direction, float distance)
{
  pos.x += distance;
  pos.y += direction;
  return (pos);
}
