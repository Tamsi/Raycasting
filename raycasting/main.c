#include "my.h"

t_my_framebuffer *create_pixel_buffer(int width, int height)
{
  int i;
  sfUint8* pixels;
  t_my_framebuffer *pixelbuffer;

  pixels = malloc(width * height * 4 * sizeof(*pixels));
  pixelbuffer = malloc(width * height * 4 * sizeof(*pixelbuffer));
  if (pixels == NULL)
    exit(EXIT_FAILURE);
  i = 0;
  while (i < width * height * 4)
    {
      pixels[i] = 0;
      i = i + 1;
    }
  pixelbuffer->pixels = pixels;
  pixelbuffer->height = height;
  pixelbuffer->width = width;
  return (pixelbuffer);
}

int     main()
{
  sfVideoMode mode = {SCREEN_WIDTH, SCREEN_HEIGHT, 32};
  sfRenderWindow* window;
  sfEvent event;
  sfSprite* sprite;
  sfTexture* texture;
  //sfUint8*
  t_my_framebuffer *pixels;
  pdir camera;
  sfVector2f plan;
  double moveSpeed = 0.02;
  double rotSpeed = 0.03;
  
  sprite = sfSprite_create();
  pixels = create_pixel_buffer(SCREEN_WIDTH, SCREEN_HEIGHT);

  plan.x = 0;
  plan.y = 0.66;

  camera.pos.x = 12;
  camera.pos.y = 12;
  camera.dir.x = -1;
  camera.dir.y = 0;

  texture = sfTexture_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  sfSprite_setTexture(sprite, texture, sfTrue);
  window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
  if (!window)
    return EXIT_FAILURE;
  while (sfRenderWindow_isOpen(window))
    {
      //if (event.type == sfEvtClosed)
      //sfRenderWindow_close(window);
      if (sfKeyboard_isKeyPressed(sfKeyEscape))
	sfRenderWindow_close(window);
      if (sfKeyboard_isKeyPressed(sfKeyDown))
	{
	  double moveX = camera.dir.x * moveSpeed, moveY = camera.dir.y * moveSpeed;
	  if (map[(int)(camera.pos.x - moveX)][(int)(camera.pos.y - moveY)] == 0)
	    {
	      camera.pos.x -= moveX;
	      camera.pos.y -= moveY;
	    }
	}
      if (sfKeyboard_isKeyPressed(sfKeyUp))
	{
	  float moveX = camera.dir.x * moveSpeed, moveY = camera.dir.y * moveSpeed;
	  if (map[(int)(camera.pos.x + moveX)][(int)(camera.pos.y + moveY)] == 0)
	    {
	      camera.pos = move_forward(camera.pos, moveY, moveX);
	      //camera.pos.x += moveX;
	      //camera.pos.y += moveY;
	    }
	}
      if (sfKeyboard_isKeyPressed(sfKeyRight))
	{
	  double oldDirX = camera.dir.x;
	  camera.dir.x = camera.dir.x * cos(-rotSpeed) - camera.dir.y * sin(-rotSpeed);
	  camera.dir.y = oldDirX * sin(-rotSpeed) + camera.dir.y * cos(-rotSpeed);
	  double oldPlaneX = plan.x;
	  plan.x = plan.x * cos(-rotSpeed) - plan.y * sin(-rotSpeed);
	  plan.y = oldPlaneX * sin(-rotSpeed) + plan.y * cos(-rotSpeed);
	}
      //rotate to the left
      if (sfKeyboard_isKeyPressed(sfKeyLeft))
	{
	  //both camera direction and camera plane must be rotated
	  double oldDirX = camera.dir.x;
	  camera.dir.x = camera.dir.x * cos(rotSpeed) - camera.dir.y * sin(rotSpeed);
	  camera.dir.y = oldDirX * sin(rotSpeed) + camera.dir.y * cos(rotSpeed);
	  double oldPlaneX = plan.x;
	  plan.x = plan.x * cos(rotSpeed) - plan.y * sin(rotSpeed);
	  plan.y = oldPlaneX * sin(rotSpeed) + plan.y * cos(rotSpeed);
	}
      raycast(pixels, camera, plan);
      sfTexture_updateFromPixels(texture, pixels->pixels, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
    }
}
