/**
 * Максимальное количество слушателей сигнала INT
 */
#define MAX_INT_OBSERVERS 10

/**
 * Количество сигналов INT в секунду
 */
#define INT_PER_SECOND 50

#include <SDL_thread.h>
#include "UsesINT.h"
#include "../../Frequency.h"

#ifndef ZX_EMULATOR_INT_H
#define ZX_EMULATOR_INT_H

/**
 * Сигнал INT
 */
class INT {
public:

    /**
     * Добавляет слушателя сигнала INT
     */
    static void addObserver(UsesINT *observer);
private:

    /**
     * Поток, который уведомляет слушателей о пришедшем сигнале INT
     */
    static int INTThread(void *);

    /**
     * Массив слушателей сигнала INT
     */
    static UsesINT *observers[MAX_INT_OBSERVERS];

    /**
     * Указатель на поток
     */
    static SDL_Thread *thread;

    /**
     * Текущее количество слушателей сигнала INT в потоке
     */
    static int count;

    /**
     * Объект Frequency
     */
    static Frequency *frequency;
};

#endif //ZX_EMULATOR_INT_H
