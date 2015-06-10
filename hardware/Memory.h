typedef unsigned char byte;
typedef unsigned short doubleByte;

#ifndef ZX_EMULATOR_MEMORY_H
#define ZX_EMULATOR_MEMORY_H


/**
 * Память компьютера
 */
class Memory {
public:
    /**
     * Конструктор. Загружает ROM
     */
    Memory();

    /**
     * Читает один байт из адреса и возвращает его
     */
    byte readN(doubleByte addr);

    /**
     * Читает двухбайтное число и возвращает его
     */
    doubleByte readNN(doubleByte addr);

    /**
     * Записывает один байт по указанному адресу
     */
    void writeN(doubleByte addr, byte data);

    /**
     * Записывает два байта по указанному адресу
     */
    void writeNN(doubleByte addr, doubleByte data);

    /**
     * Возвращает указатель на заданный адрес памяти ZX
     */
    void * getPointer(doubleByte addr);
private:
    /**
     * Хранит образ памяти
     */
    byte memory[65536];
};


#endif //ZX_EMULATOR_MEMORY_H
