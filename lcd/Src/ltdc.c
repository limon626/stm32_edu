#include "ltdc.h"
extern volatile uint32_t RGB565_480x272[65280];
extern LTDC_HandleTypeDef hltdc;
uint16_t X_SIZE = 480;
uint16_t Y_SIZE = 272;
//LCD_DrawPropTypeDef lcdprop;
//const uint8_t *ch;

void TFT_FillScreen(uint16_t color) {
	uint32_t i;
	uint32_t n = hltdc.LayerCfg[0].ImageHeight * hltdc.LayerCfg[0].ImageWidth;
	for (i = 0; i < n; i++) {
		*(__IO uint16_t*) (hltdc.LayerCfg[0].FBStartAdress + (i*2)) =
						color;
		//*(__IO uint16_t*) (hltdc.LayerCfg[0].FBStartAdress + i) =
		//						(uint16_t) color;
	}
	HAL_Delay(100);
}

void TFT_FillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t color) {
	uint32_t xpos, ypos;
	if (x1 > x2)
		swap(x1, x2);
	if (y1 > y2)
		swap(y1, y2);

	for (ypos = y1; ypos <= y2; ypos++) {
		for (xpos = x1; xpos <= x2; xpos++) {
			*(__IO uint16_t*) (hltdc.LayerCfg[0].FBStartAdress
					+ (2 * (ypos * hltdc.LayerCfg[0].ImageWidth + xpos))) =
					(uint16_t) color;
		}
	}
}

void TFT_FillLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t color) {

	int x_err = 0, y_err = 0, d = 0;		//функции погрешностей по х и у
	int dx = x2 - x1;
	int dy = y2 - y1; // приращения по х и у на всем отрезке
	int incX = 0;
	int incY = 0; //шаги приращения по х и у =0
	if (dx > 0) {
		incX = 1;
	} else if (dx != 0) {
		incX = -1;
	} //шаг приращения по х
	if (dy > 0) {
		incY = 1;
	} else if (dy != 0) {
		incY = -1;
	}
// шаг приращения по у
	dx = abs(dx);
	dy = abs(dy);
	if (dx > dy) {
		d = dx;
	} else {
		d = dy;
	} //выбор max(dx,dy)в качестве тестовой величины
	int x = x1, y = y1;
	TFT_DrawPixel(x, y, (uint16_t) 0x009933);

	for (int i = 1; i <= d; i++) {
		x_err += dx;
		y_err += dy;  //приращение ошибки при перемещении на пиксель
		if (x_err >= d) {
			x += incX;
			x_err -= d;
		}  // условие шага по х
		if (y_err >= d) {
			y += incY;
			y_err -= d;
		}  // условие шага по у(+0.5d,-0.5d)!!!
		TFT_DrawPixel(x, y, color);
	}
	TFT_DrawPixel(x, y, (uint16_t) 0x0000ff);
}

/*void TFT_FontsIni(void)
{
	lcdprop.BackColor = LCD_COLOR_BLACK;
	lcdprop.TextColor = LCD_COLOR_GREEN;
	lcdprop.pFont = &Font16;
}

void TFT_SetFont(sFONT *fonts)
{
	lcdprop.pFont = fonts;
}

void TFT_SetTextColor(uint32_t color)
{
	lcdprop.TextColor = color;
}

void TFT_SetBackColor(uint32_t color)
{
	lcdprop.BackColor = color;
}

void TFT_DrawChar(uint16_t x, uint16_t y, const uint8_t c)
{
	uint32_t i=0, j=0;
	uint16_t height, width;
	uint8_t offset;
	uint8_t *pchar;
	uint32_t line;
	ch = &lcdprop.pFont->table[c-' ' * lcdprop.pFont->Height *
		((lcdprop.pFont->Width + 7) / 8)];
	height = lcdprop.pFont->Height;
	width = lcdprop.pFont->Width;
	offset = 8 * ((width + 7)/8) - width;
	for (i=0; i < height; i++)
	{
		pchar = ((uint8_t *)ch + (width + 7)/8 * i);
		switch ((width + 7)/8) {
			case 1:
				line = pchar[0];
				break;
			case 2:
				line = (pchar[0]<<8) | pchar[1];
				break;
			case 3:
				line = (pchar[0]<<16) | (pchar[1]<<8) | pchar[2];
				break;
			default:
				break;
		}
		for (j=0; j < width; j++)
		{
			if (line & (1 << (width - j + offset - 1)))
			{
				TFT_DrawPixel((x+j), y, lcdprop.TextColor);
			} else {
				TFT_DrawPixel((x+j), y, lcdprop.BackColor);
			}
		}
		y++;
	}
	}
*/

void TFT_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint16_t color){
	*(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(2*(Ypos*hltdc.LayerCfg[0].ImageWidth+Xpos)))=(uint16_t) color;
//	*(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(2*(Ypos+Xpos)))=(uint16_t) color;
}


