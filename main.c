#include "muon.h"

int main(int argc, char **argv) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL_Init Failed!");
		return -1;
	}

	map.windw = 640;
	map.windh = 480;


	SDL_WM_SetCaption("Muon", NULL);
	if ((context = SDL_SetVideoMode(map.windw, map.windh, 24, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		printf("SDL_SetVideoMode Failed!");
		return -1;
	}
	
	objectTemplateArray_Init();
	
	
	map.gamemode = 1;
	
	Map_init();
	
	map.width = 20;
	map.height = 10;
	
	/*objectArray_Add(3, 0, 0, 1);
	objectArray_Add(3, 0, map.height, 2);
	objectArray_Add(3, map.width, 0, 3);
	objectArray_Add(3, map.width, map.height, 4);*/
	Map_load("data/maps/testmap");
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
		drawHud();

		SDL_Flip(context);

		SDL_FillRect(context, &context->clip_rect, SDL_MapRGB(context->format, 0x00, 0x00, 0x00));

		if (Timer_getTicks(fps) < 1000 / 75)
			SDL_Delay((1000 / 75) - Timer_getTicks(fps));
	}

	SDL_Quit();
	return 0;
}
