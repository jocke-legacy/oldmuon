#include "muon.h"

int main(int argc, char **argv) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL_Init Failed!");
		return -1;
	}

	windw = 640;
	windh = 480;


	SDL_WM_SetCaption("Muon", NULL);
	if ((context = SDL_SetVideoMode(windw, windh, 24, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		printf("SDL_SetVideoMode Failed!");
		return -1;
	}
	
	Map_init();
	Map_load("data/maps/testmap");
	//Map_debug();
	//Map_unload();
	
	loadSprites();

	Timer fps;

	int running = 1;
	while (running) {
		Timer_toggleS_ST(&fps);

		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
			running = 0;

		cameraControl();

		objectDrawAll();

		SDL_Flip(context);

		if (Timer_getTicks(fps) < 1000 / 75)
			SDL_Delay((1000 / 75) - Timer_getTicks(fps));

		SDL_FillRect(context, &context->clip_rect, SDL_MapRGB(context->format, 0x00, 0x00, 0x00));
	}

	SDL_Quit();
	return 0;
}
