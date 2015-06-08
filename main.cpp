#include <iostream>
#include "SDL2/SDL.h"

using namespace std;

int main() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL Init error: \"" << SDL_GetError() << "\"" << endl;
        return 1;
    }

    return 0;
}