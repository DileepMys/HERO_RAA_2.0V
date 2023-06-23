/*
 * display_test.h
 *
 *  Created on: 23-Mar-2022
 *      Author: Admin
 */

#ifndef DISPLAY_TEST_H_
#define DISPLAY_TEST_H_

#include "peripherals.h"

void CBAR(uint16_t frameBuffer[LCDIF_PANEL_HEIGHT][LCDIF_PANEL_WIDTH]);
void APP_FillFrameBuffer(uint16_t frameBuffer[LCDIF_PANEL_HEIGHT][LCDIF_PANEL_WIDTH]);

#endif /* DISPLAY_TEST_H_ */
