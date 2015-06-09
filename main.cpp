#define PRODUCTION false

#include <iostream>
#include <libgen.h>
#include <unistd.h>
#include "hardware/Frequency.h";
#include "hardware/Memory.h"

using namespace std;


int main(int argc, char *argv[]) {
    if(!PRODUCTION) {
        chdir(dirname(strdup(__FILE__)));
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL Init error: \"" << SDL_GetError() << "\"" << endl;
        return 1;
    }

    return 0;
}

