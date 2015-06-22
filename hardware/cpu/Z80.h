//
// Created by yuri on 21.06.15.
//

#ifndef ZX_EMULATOR_Z80_H
#define ZX_EMULATOR_Z80_H


#include "../Register.h"
#include "../Interrupt.h"
#include "../Frequency.h"
#include "../Flag.h"


/**
 * Класс процессора
 */
class Z80 {
typedef int (Z80::*Z80Command)();
public:
    Z80(Memory *memory);

    /**
     * Обработчик машинных кодов
     */
    void process();

private:

    /**
     * Набор главных комманд процессора
     */
    Z80Command mainCommands[256];

    /**
     * Инициализация таблиц машинных кодов
     */
    void init() {
        for(int i = 0; i < 256; i++) {
            this->mainCommands[i] = NULL;
        }

        this->mainCommands[0xAF] = &Z80::opt0xAF;
        this->mainCommands[0xF3] = &Z80::opt0xF3;
    }

    int opt0xAF();      // XOR A
    int opt0xF3();      // DI

    Register *AF;
    Register *BC;
    Register *DE;
    Register *HL;
    Register *IX;
    Register *IY;
    Register *PC;
    Register *SP;
    Register *IR;

    Interrupt *interrupt;
    Frequency *frequency;
    Memory *memory;
    Flag *flag;
    SDL_Thread *thread;

    /**
     * Поток процессора
     */
    static int cpuThread(void *);

};


#endif //ZX_EMULATOR_Z80_H
