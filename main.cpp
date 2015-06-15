#define PRODUCTION false

#include <iostream>
#include <libgen.h>
#include <unistd.h>
#include "hardware/Frequency.h"
#include "hardware/Memory.h"
#include "hardware/Screen.h"

using namespace std;


int main(int argc, char *argv[]) {
    if(!PRODUCTION) {
        chdir(dirname(strdup(__FILE__)));
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL Init error: \"" << SDL_GetError() << "\"" << endl;
        return 1;
    }

    Memory *memory = new Memory();
    Screen *screen = new Screen(memory);
    cout << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << endl << FLASH_CHANGE_EVERY_INT;
    getchar();
    return 0;
}

