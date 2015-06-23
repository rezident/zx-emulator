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
     * Устанавливает флаг переполнения/четности "PV"
     */
    void setPV();

    /**
     * Сбрасывает флаг переполнения/четности "PV"
     */
    void resetPV();

    /**
     * Возвращает признак того, что флаг "PV" установлен
     */
    bool isPV();

    /**
     * Устанавливает флаг сложения/вычитания "N"
     */
    void setN();

    /**
     * Сбрасываеи флаг сложения/вычитания "N"
     */
    void resetN();

    /**
     * Возвращает признак того, что флаг "N" установлен
     */
    bool isN();

    /**
     * Устанавливает флаг полупереноса "H"
     */
    void setH();

    /**
     * Сбрасываеи флаг полупереноса "H"
     */
    void resetH();

    /**
     * Возвращает признак того, что флаг "H" установлен
     */
    bool isH();

    /**
     * Вычисляет флаг четности по аккумулятору
     */
    void parityCalc();

    /**
     * Вычисляет флаг нуля
     */
    void ZCalc(byte result);

    /**
     * Вычисляет флаг нуля
     */
    void ZCalc(doubleByte result);

    /**
     * Вычисляет флаг знака
     */
    void SCalc(byte result);

    /**
     * Вычисляет флаг знака
     */
    void SCalc(doubleByte result);

    /**
     * Вычисляет флаг переполнения "V"
     */
    void VCalc(bool isAdd, byte operand1, byte operand2);

    /**
     * Вычисляет флаг переноса C
     */
    void CCalc(bool isAdd, doubleByte operand1, doubleByte operand2);

    /**
     * Вычисляет флаг переноса C
     */
    void CCalc(bool isAdd, byte operand1, byte operand2);

    /**
     * Вычисляет флаг полупереноса H
     */
    void HCalc(bool isAdd, doubleByte operand1, doubleByte operand2);

    /**
     * Вычисляет флаг полупереноса H
     */
    void HCalc(bool isAdd, byte operand1, byte operand2);

    /**
     * Вычисляет флаг сложения/вычитания
     */
    void NCalc(bool isAdd);

private:
    Register *af;
};


#endif //ZX_EMULATOR_FLAG_H
