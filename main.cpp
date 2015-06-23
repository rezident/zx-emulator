#define PRODUCTION false

#include <iostream>
#include <libgen.h>
#include <unistd.h>
#include "hardware/Frequency.h"
#include "hardware/Memory.h"
#include "hardware/Screen.h"
#include "hardware/cpu/Z80.h"
#include "hardware/ports/PortsPool.h"
#include "hardware/ports/PortWriter_FE.h"

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


    PortsPool::init();
    PortsPool::addWriter(0xFE, new PortWriter_FE(screen));
    Z80 *cpu = new Z80(memory);

    getchar();
    return 0;
}

