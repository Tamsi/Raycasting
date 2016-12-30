#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define SCREEN_WIDTH 800

void draw_square(sfUint8* pixels)
{
  int x;
  int y;

  x = 0;
  while (x < 100)
    {
      y = 0;
      while (y < 100)
	{
	  pixels[(100 * y + x) * 4] = sfRed.r;
	  pixels[(100 * y + x) * 4 + 1] = sfRed.g;
	  pixels[(100 * y + x) * 4 + 2] = sfRed.b;
	  pixels[(100 * y + x) * 4 + 3] = sfRed.a;
	  y = y + 1;
	}
      x = x + 1;
    }
}

sfUint8* create_pixel_buffer(int width, int height)
{
  int i;
  sfUint8* pixels;

  pixels = malloc(width * height * 4 * sizeof(*pixels));
  if (pixels == NULL)
    {
      exit(EXIT_FAILURE);
    }
  i = 0;
  while (i < width * height * 4)
    {
      pixels[i] = 0;
      i = i + 1;
    }
  return pixels;
}

int main()
{
  sfVideoMode mode = {800, 600, 32};
  sfRenderWindow* window;
  sfEvent event;
  sfSprite* sprite;
  sfVector2f  position;
  sfTexture* texture;
  sfUint8* pixels;
  int x;

  position.x = 0;
  position.y = 0;
  window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
  sprite = sfSprite_create();
  pixels = create_pixel_buffer(100, 100);
  texture = sfTexture_create(100, 100);
  draw_square(pixels);
  sfSprite_setTexture(sprite, texture, sfTrue);
  sfTexture_updateFromPixels(texture, pixels, 100, 100, 0, 0);
  if (!window)
    return EXIT_FAILURE;
  while (sfRenderWindow_isOpen(window))
    {
      /* Process events */
      while (sfRenderWindow_pollEvent(window, &event))
	{
	  /* Close window : exit */
	  if (event.type == sfEvtClosed)
	    sfRenderWindow_close(window);
	  if (event.type == sfEvtKeyPressed)
	    {
	      if (event.key.code == sfKeyDown)
		position.y++;
	      if (event.key.code == sfKeyUp)
		position.y--;
	    }
	  
	}
      if (position.x + 100 == SCREEN_WIDTH)
	x = -1;
      else if (position.x == 0)
	x = 1;
      sfSprite_setPosition(sprite, position);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
      position.x = position.x + x;
    }
}
