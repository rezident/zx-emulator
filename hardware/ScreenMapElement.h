//
// Created by yuri on 15.06.15.
//

#ifndef ZX_EMULATOR_SCREENMAPELEMENT_H
#define ZX_EMULATOR_SCREENMAPELEMENT_H

#include "Memory.h"

/**
 * Описание точки на карте экрана
 */
struct ScreenMapElement {

    /**
     * Указывает на адрес памяти, откуда берутся данные
     */
    void *pointerData;

    /**
     * Маска, по которой определяется, включен ли бит в pointerData
     */
    byte dataMask;

    /**
     * Указывает на адрес памяти, откуда берется цвет цернил и бумаги
     */
    void *pointerColor;

    /**
     * Количество тактов Z80, которое нужно подождать после вывода текущего пикселя
     */
    int tactsWait;

    /**
     * Использовать предыдущую точку
     */
    bool usePrevious;
};

#endif //ZX_EMULATOR_SCREENMAPELEMENT_H
