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

        this->mainCommands[0x11] = &Z80::opt0x11;
        this->mainCommands[0x3E] = &Z80::opt0x3E;
        this->mainCommands[0x47] = &Z80::opt0x47;
        this->mainCommands[0xAF] = &Z80::opt0xAF;
        this->mainCommands[0xC3] = &Z80::opt0xC3;
        this->mainCommands[0xD3] = &Z80::opt0xD3;
        this->mainCommands[0xF3] = &Z80::opt0xF3;
    }

    int opt0x11();      // LD DE,NN
    int opt0x3E();      // LD A,N
    int opt0x47();      // LD B,A
    int opt0xAF();      // XOR A
    int opt0xC3();      // JP NN
    int opt0xD3();      // OUT (N),A
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
