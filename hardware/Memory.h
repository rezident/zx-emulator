typedef unsigned char byte;

#ifndef ZX_EMULATOR_MEMORY_H
#define ZX_EMULATOR_MEMORY_H


class Memory {
public:
    /**
     * Конструктор. Загружает ROM
     */
    Memory();
private:
    /**
     * Хранит образ памяти
     */
    byte *memory[65536];
};


#endif //ZX_EMULATOR_MEMORY_H
