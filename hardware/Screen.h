#define SYNCHRO_TOP_LINES       16
#define SYNCHRO_LEFT_TICKS      32
#define BORDER_TOP_LINES        64
#define BORDER_BOTTOM_LINES     48
#define BORDER_LEFT_PIXELS      72
#define BORDER_RIGHT_PIXELS     56

#define SCREEN_X_PIXELS         256
#define SCREEN_Y_LINES          192

#define FLASH_FREQUENCY         1.565

#define WINDOW_WIDTH (BORDER_LEFT_PIXELS+SCREEN_X_PIXELS+BORDER_RIGHT_PIXELS)*SCREEN_SCALE
#define WINDOW_HEIGHT (BORDER_TOP_LINES+SCREEN_Y_LINES+BORDER_BOTTOM_LINES)*SCREEN_SCALE
#define FLASH_CHANGE_EVERY_INT (INT_PER_SECOND/FLASH_FREQUENCY)

#define SCREEN_SCALE 3

#ifndef ZX_EMULATOR_SCREEN_H
#define ZX_EMULATOR_SCREEN_H

#include <SDL_video.h>
#include "signals/int/UsesINT.h"
#include "Memory.h"
#include "Frequency.h"
#include "signals/int/INT.h"
#include "ScreenMapElement.h"

class Screen: public UsesINT {
public:
    Screen(Memory *memory);

    /**
     * Устанавливает цвет бордера
     */
    void setBorder(byte border);

private:

    /**
     * Память компьютера ZX
     */
    Memory *memory;

    /**
     * Окно, в котором размещается экран
     */
    SDL_Window *window;

    /**
     * Пиксельная карта экрана
     */
    SDL_Surface *surface;

    /**
     * Частотный генератор
     */
    Frequency *frequency = new Frequency;

    /**
     * Поток, в котором идет обновление экрана
     */
    SDL_Thread *thread;

    /**
     * Цвет Border
     */
    byte border = 0;

    /**
     * Цвет Border так, если бы это был аттрибут экрана
     */
    byte borderAttribute;

    /**
     * Цвет Border так, если бы это были данные экрана
     */
    byte borderData = 255;

    /**
     * Поток, обновляющий экран
     */
    static int updateScreenThread(void *screen);

    /**
     * Флаг, указывающий на то, нужно ли менять местами чернила и бумагу (мерцание)
     */
    bool flashInverted = false;

    /**
     * Счетчик мерцания
     */
    int flashCounter = 0;

    /**
     * Палитра цветов ZX
     */
    Uint32 palette[16];

    /**
     * Обработчик счетчика мерцания
     */
    void flashHandler();

    /**
     * Инициализирует палитру цветов ZX
     */
    void initPalette();

    /**
     * Карта окна для вывода изображения
     */
    ScreenMapElement screenMap[WINDOW_WIDTH*WINDOW_HEIGHT+1];

    void buildScreenMap();
};

#endif //ZX_EMULATOR_SCREEN_H

