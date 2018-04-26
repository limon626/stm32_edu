#include "ltdc.h"
//----------------------------------------
extern volatile uint32_t RGB565_480x272[65280];
extern LTDC_HandleTypeDef hltdc;
//----------------------------------------
LCD_DrawPropTypeDef lcdprop;
const uint8_t *ch;

//----------------------------------------
void TFT_FillScreen(uint32_t color)
{
	uint32_t i;
	uint32_t n = hltdc.LayerCfg[0].ImageHeight*hltdc.LayerCfg[0].ImageWidth;
	for(i=0;i<n;i++)
	{
		*(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(i*2))=(uint16_t) color;
	}
}
//----------------------------------------
void TFT_FillRectangle(uint16_t x1, uint16_t y1,
											uint16_t x2, uint16_t y2, uint16_t color)
{
	uint32_t xpos,ypos;
	if(x1>x2) swap(x1,x2);
	if(y1>y2) swap(y1,y2);
	for(ypos=y1;ypos<=y2;ypos++)
	{
		for(xpos=x1;xpos<=x2;xpos++)
		{
			*(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(2*(ypos*hltdc.LayerCfg[0].ImageWidth+xpos)))=(uint16_t) color;
		}
	}
}
//----------------------------------------
void TFT_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t color)
{
	*(__IO uint16_t*)(hltdc.LayerCfg[0].FBStartAdress+(2*(Ypos*hltdc.LayerCfg[0].ImageWidth+Xpos)))=(uint16_t) color;
}
//----------------------------------------
void TFT_DrawLine(uint16_t x1, uint16_t y1,
											uint16_t x2, uint16_t y2, uint16_t color)
{
	int steep = abs(y2-y1)>abs(x2-x1);
	if(steep)
	{
		swap(x1,y1);
		swap(x2,y2);
	}
	if(x1>x2)
	{
		swap(x1,x2);
		swap(y1,y2);
	}
	int dx,dy;
	dx=x2-x1;
	dy=abs(y2-y1);
	int err=dx/2;
	int ystep;
	if(y1<y2) ystep=1;
	else ystep=-1;
	for(;x1<=x2;x1++)
	{
		if(steep) TFT_DrawPixel(y1,x1,color);
		else TFT_DrawPixel(x1,y1,color);
		err-=dy;
		if(err<0)
		{
			y1 += ystep;
			err=dx;
		}
	}
}

		void TFT_FontsIni(void)
	{
	  lcdprop.BackColor=LCD_COLOR_BLACK;
	  lcdprop.TextColor=LCD_COLOR_GREEN;
	  lcdprop.pFont=&Font16;
	}
//----------------------------------------

void TFT_SetFont(sFONT *fonts)
{
 lcdprop.pFont=fonts;
}
//----------------------------------------
void TFT_SetTextColor(uint32_t color)
{
 lcdprop.TextColor=color;
}
//----------------------------------------
void TFT_SetBackColor(uint32_t color)
{
 lcdprop.BackColor=color;
}
//----------------------------------------
	void TFT_DrawChar(uint16_t x, uint16_t y, const uint8_t c) {
		uint32_t i = 0, j = 0;
		uint16_t height, width;
		uint8_t offset;
		uint8_t *pchar;
		uint32_t line;

		ch = &lcdprop.pFont->table[(c - ' ') * lcdprop.pFont->Height * ((lcdprop.pFont->Width + 7) / 8)];
		height = lcdprop.pFont->Height;
		width = lcdprop.pFont->Width;
		offset = 8 * ((width + 7) / 8) - width;

		for (i = 0; i < height; i++) {
			pchar = ((uint8_t *) ch + (width + 7) / 8 * i);
			switch ((width + 7) / 8) {
			case 1:
				line = pchar[0];
				break;
			case 2:
				line = (pchar[0] << 8) | pchar[1];
				break;
			case 3:
			default:
				line = (pchar[0] << 16) | (pchar[1] << 8) | pchar[2];
				break;
			}
			for (j = 0; j < width; j++) {
				if (line & (1 << (width - j + offset - 1))) {
					TFT_DrawPixel((x + j), y, lcdprop.TextColor);
				} else {
					TFT_DrawPixel((x + j), y, lcdprop.BackColor);
				}
			}
			y++;
		}
	}


