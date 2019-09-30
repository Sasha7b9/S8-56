#include "stdafx.h"
#include "stm32f4xx_hal.h"
#ifdef USE_SDL2
#include <SDL_timer.h>
#endif



uint32_t HAL_GetTick()
{
#ifdef USE_SDL2
    return SDL_GetTicks();
#else
    return 0;
#endif
}


void HAL_Delay(uint32_t time)
{
    volatile uint timeStart = HAL_GetTick();

    while (HAL_GetTick() - timeStart < time) //-V776
    {

    }
}


HAL_StatusTypeDef HAL_Init()
{
    return HAL_ERROR;
}


void HAL_IncTick()
{
}
