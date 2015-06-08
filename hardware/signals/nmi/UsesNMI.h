#ifndef ZX_EMULATOR_USESNMI_H
#define ZX_EMULATOR_USESNMI_H

class UsesNMI {
public:
    /**
     * Устанавливает признак того, что пришел сигнал NMI
     */
    virtual void setNMI();

    /**
     * Сбрасывает признак того, что пришел сигнал NMI
     */
    void resetNMI();

    /**
     * Возвращает признак того, что пришел сигнал NMI
     */
    bool isComeNMI();

private:
    /**
     * Указывает на то, что пришел сигнал NMI
     */
    bool comeNMI = false;
};


#endif //ZX_EMULATOR_USESNMI_H
