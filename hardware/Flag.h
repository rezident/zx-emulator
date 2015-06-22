//
// Created by yuri on 22.06.15.
//

#ifndef ZX_EMULATOR_FLAG_H
#define ZX_EMULATOR_FLAG_H


#include "Register.h"

class Flag {
public:
    Flag(Register *af);

    /**
     * Устанавливает флаг переноса "C"
     */
    void setC();

    /**
     * Сбрасывает флаг переноса "C"
     */
    void resetC();

    /**
     * Возвращает признак того, что флаг "C" установлен
     */
    bool isC();

    /**
     * Устанавливает флаг нуля "Z"
     */
    void setZ();

    /**
     * Сбрасывает флаг нуля "Z"
     */
    void resetZ();

    /**
     * Возвращает признак того, что флаг "Z" установлен
     */
    bool isZ();

    /**
     * Устанавливает флаг знака "S"
     */
    void setS();

    /**
     * Сбрасывает флаг знака "S"
     */
    void resetS();

    /**
     * Возвращает признак того, что флаг "S" установлен
     */
    bool isS();

    /**
     * Устанавливает флаг переполнения/четности "PO"
     */
    void setPO();

    /**
     * Сбрасывает флаг переполнения/четности "PO"
     */
    void resetPO();

    /**
     * Возвращает признак того, что флаг "PO" установлен
     */
    bool isPO();


private:
    Register *af;
};


#endif //ZX_EMULATOR_FLAG_H
