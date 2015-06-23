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
     * Набор расширенных комманд процессора (ED)
     */
    Z80Command extendedCommands[256];

    /**
     * Инициализация таблиц машинных кодов
     */
    void init() {
        for(int i = 0; i < 256; i++) {
            this->mainCommands[i] = NULL;
        }

        for(int i = 0; i < 256; i++) {
            this->extendedCommands[i] = NULL;
        }

        this->mainCommands[0x00] = &Z80::opt0x00;
        this->mainCommands[0x11] = &Z80::opt0x11;
        this->mainCommands[0x2B] = &Z80::opt0x2B;
        this->mainCommands[0x36] = &Z80::opt0x36;
        this->mainCommands[0x3E] = &Z80::opt0x3E;
        this->mainCommands[0x47] = &Z80::opt0x47;
        this->mainCommands[0x62] = &Z80::opt0x62;
        this->mainCommands[0x6B] = &Z80::opt0x6B;
        this->mainCommands[0xAF] = &Z80::opt0xAF;
        this->mainCommands[0xBC] = &Z80::opt0xBC;
        this->mainCommands[0xC3] = &Z80::opt0xC3;
        this->mainCommands[0xD3] = &Z80::opt0xD3;
        this->mainCommands[0xED] = &Z80::opt0xED;
        this->mainCommands[0xF3] = &Z80::opt0xF3;

        this->extendedCommands[0x47] = &Z80::opt0xED47;
    }

    int opt0x00();      // NOP
    int opt0x11();      // LD DE,NN
    int opt0x2B();      // DEC HL
    int opt0x36();      // LD (HL),N
    int opt0x3E();      // LD A,N
    int opt0x47();      // LD B,A
    int opt0x62();      // LD H,D
    int opt0x6B();      // LD L,E
    int opt0xAF();      // XOR A
    int opt0xBC();      // CP H
    int opt0xC3();      // JP NN
    int opt0xD3();      // OUT (N),A
    int opt0xED();      // Extended instructions
    int opt0xF3();      // DI


    int opt0xED47();    // LD I,A



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

    Z80Command getCommandMethod(Z80Command *commandsSet, const char *prefix);
};


#endif //ZX_EMULATOR_Z80_H
