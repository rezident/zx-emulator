#ifndef ZX_EMULATOR_USESINT_H
#define ZX_EMULATOR_USESINT_H

class UsesINT {
public:
    /**
     * Устанавливает признак того, что пришел сигнал INT
     */
    virtual void setINT();

    /**
     * Сбрасывает признак того, что пришел сигнал INT
     */
    void resetINT();

    /**
     * Возвращает признак того, что пришел сигнал INT
     */
    bool isComeINT();

private:
    /**
     * Указывает на то, что пришел сигнал INT
     */
    bool comeINT = false;
};


#endif //ZX_EMULATOR_USESINT_H
