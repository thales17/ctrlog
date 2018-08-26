#include <stdio.h>
#include <SDL2/SDL.h>

float normalizeAxisValue(Sint16 value);

int main(int argc, char *argv[]) {
  SDL_GameController *controller;
  if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }
  
  for (int i = 0; i < SDL_NumJoysticks(); i++) {
    if (SDL_IsGameController(i)) {
      controller = SDL_GameControllerOpen(i);
      if (controller) {
        char *mapping;
        printf("Controller %d opened!\n", i);
        mapping = SDL_GameControllerMapping(controller);
        printf("Mapping: %s\n", mapping);
        SDL_free(mapping);
        break;
      } else {
        printf("Could not open gamecontroller %d, %s\n", i, SDL_GetError());
      }
    }
  }
  
  SDL_Event event;
  while (1) {
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      } else if (event.type == SDL_CONTROLLERBUTTONDOWN ||
                 event.type == SDL_CONTROLLERBUTTONUP) {
        SDL_ControllerButtonEvent *buttonEvent = (SDL_ControllerButtonEvent*)&event;
        printf("%d%d,%d\n", buttonEvent->which, buttonEvent->button, buttonEvent->state);
      } else if (event.type == SDL_CONTROLLERAXISMOTION) {
        SDL_ControllerAxisEvent *axisEvent = (SDL_ControllerAxisEvent*)&event;
        printf("%d%d,%.2f\n", axisEvent->which, axisEvent->axis, normalizeAxisValue(axisEvent->value));
      }
    }
  }

  SDL_GameControllerClose(controller);

  SDL_Quit();
  return 0;
}

float normalizeAxisValue(Sint16 value) {
  float normalized = value;
  return normalized / 32767;
}
