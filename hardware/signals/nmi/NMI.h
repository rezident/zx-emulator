/**
 * Максимальное количество слушателей сигнала NMI
 */
#define MAX_NMI_OBSERVERS 0

/**
 * Количество сигналов NMI в секунду
 */
#define NMI_PER_SECOND 50

#include <SDL_thread.h>
#include "UsesNMI.h"
#include "../../Frequency.h"

#ifndef ZX_EMULATOR_NMI_H
#define ZX_EMULATOR_NMI_H

/**
 * Сигнал NMI
 */
class NMI {
public:

    /**
     * Добавляет слушателя сигнала NMI
     */
    static void addObserver(UsesNMI *observer);
private:

    /**
     * Поток, который уведомляет слушателей о пришедшем сигнале NMI
     */
    static int NMIThread(void *);

    /**
     * Массив слушателей сигнала NMI
     */
    static UsesNMI *observers[MAX_NMI_OBSERVERS];

    /**
     * Указатель на поток
     */
    static SDL_Thread *thread;

    /**
     * Текущее количество слушателей сигнала NMI в потоке
     */
    static int count;

    /**
     * Объект Frequency
     */
    static Frequency *frequency;
};

#endif //ZX_EMULATOR_NMI_H
