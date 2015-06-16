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
    for(int i = 0; i<8;i++){
        screen->setBorder(i);
        SDL_Delay(200);
    }
    getchar();
    return 0;
}

