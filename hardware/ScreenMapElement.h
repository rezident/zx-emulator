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
     * Указатель на точку, в которую отображается текущий символ
     * Равен NULL, если точку ставить не нужно
     */
    Uint32 *pointerWin;

    /**
     * Указывает на адрес памяти, откуда берутся данные
     */
    byte *pointerData;

    /**
     * Маска, по которой определяется, включен ли бит в pointerData
     */
    byte dataMask;

    /**
     * Указывает на адрес памяти, откуда берется цвет цернил и бумаги
     */
    byte *pointerAttribute;

    /**
     * Количество тактов Z80, которое нужно подождать после вывода текущего пикселя
     */
    int tactsWait;

    /**
     * Использовать предыдущую точку
     */
    bool usePreviousPixel;

    /**
     * Использовать предыдущий аттрибут
     */
    bool usePreviousAttribute;
};

#endif //ZX_EMULATOR_SCREENMAPELEMENT_H
