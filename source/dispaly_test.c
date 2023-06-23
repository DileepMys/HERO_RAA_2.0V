/*
 * dispaly_test.c
 *
 *  Created on: 23-Mar-2022
 *      Author: Admin
 */
#include "peripherals.h"

#define RED (((0xff & 0xf8) << 8) + ((0 & 0xfc) << 3) + (0 >> 3));
#define GREEN (((0 & 0xf8) << 8) + ((0xff & 0xfc) << 3) + (0 >> 3));
#define BLUE (((0x00 & 0xf8) << 8) + ((0 & 0xfc) << 3) + (0xff >> 3));


void CBAR(uint16_t frameBuffer[LCDIF_PANEL_HEIGHT][LCDIF_PANEL_WIDTH]) {
	uint8_t red = 0x0;
	uint8_t green = 0x0;
	uint8_t blue = 0x0;
	uint16_t i;
	uint16_t j;

	uint16_t Rgb565 = 0;

	Rgb565 = (((red & 0xf8) << 8) + ((green & 0xfc) << 3) + (blue >> 3));

	for (i = 0; i < LCDIF_PANEL_HEIGHT; i++) {
		for (j = 0; j < LCDIF_PANEL_WIDTH; j++) {

//			frameBuffer[i][j] = Rgb565;
			if (j <= 80) {
				frameBuffer[i][j] = RED
				;
			} else if ((j > 80) && (j <= 160)) {
				frameBuffer[i][j] = BLUE
				;
			} else {
				frameBuffer[i][j] = GREEN
				;
			}

		}
	}
}

void APP_FillFrameBuffer(uint16_t frameBuffer[LCDIF_PANEL_HEIGHT][LCDIF_PANEL_WIDTH]) {
	/* Background color. */
	static uint16_t bgColor = 0;
	/* Foreground color. */
	static uint8_t fgColorIndex = 0U;
	static const uint16_t fgColorTable[] = { 0x00FFU, 0x0FF0, 0xFFFFU, 0x0FF0U,
			0xF0F0U, 0x7777U, 0x2222U };
	uint16_t fgColor = fgColorTable[fgColorIndex];

	/* Position of the foreground rectangle. */
	static uint16_t upperLeftX = 0U;
	static uint16_t upperLeftY = 0U;
	static uint16_t lowerRightX = (LCDIF_PANEL_WIDTH - 1U) / 2U;
	static uint16_t lowerRightY = (LCDIF_PANEL_HEIGHT - 1U) / 2U;

	static int8_t incX = 1;
	static int8_t incY = 1;

	/* Change color in next forame or not. */
	static bool changeColor = false;

	uint32_t i, j;

	/* Background color. */
	for (i = 0; i < LCDIF_PANEL_HEIGHT; i++) {
		for (j = 0; j < LCDIF_PANEL_WIDTH; j++) {
			frameBuffer[i][j] = bgColor;
			//bgColor = bgColor + 1;
		}
	}
#if 1
	/* Foreground color. */
	for (i = upperLeftY; i < lowerRightY; i++) {
		for (j = upperLeftX; j < lowerRightX; j++) {
			frameBuffer[i][j] = fgColor;
		}
	}

	/* Update the format: color and rectangle position. */
	upperLeftX += incX;
	upperLeftY += incY;
	lowerRightX += incX;
	lowerRightY += incY;

	changeColor = false;

	if (0U == upperLeftX) {
		incX = 1;
		changeColor = true;
	} else if (LCDIF_PANEL_WIDTH - 1 == lowerRightX) {
		incX = -1;
		changeColor = true;
	}

	if (0U == upperLeftY) {
		incY = 1;
		changeColor = true;
	} else if (LCDIF_PANEL_HEIGHT - 1 == lowerRightY) {
		incY = -1;
		changeColor = true;
	}

	if (changeColor) {
		fgColorIndex++;

		if (ARRAY_SIZE(fgColorTable) == fgColorIndex) {
			fgColorIndex = 0U;
		}
	}
#endif
}
