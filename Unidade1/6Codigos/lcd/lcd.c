#include "lcd.h"
#include "delay.h"



void LCD_MODO_COMANDO()
{
    digitalWrite(LCD_RS, LOW);
}

void LCD_MODO_DADOS()
{
    digitalWrite(LCD_RS, HIGH);
}

void LCD_envia_byte(char c)
{
	int x;
   digitalWrite(LCD_D0, c & 1);
   digitalWrite(LCD_D1, (c >>1) & 1);
   digitalWrite(LCD_D2, (c >>2) & 1);
   digitalWrite(LCD_D3, (c >>3) & 1);
   digitalWrite(LCD_D4, (c >>4) & 1);
   digitalWrite(LCD_D5, (c >>5) & 1);
   digitalWrite(LCD_D6, (c >>6) & 1);
   digitalWrite(LCD_D7, (c >>7) & 1);
   digitalWrite(LCD_EN, HIGH);
   //delay_us(100);
   for (x=0;x<1000;x++) asm("nop");
   digitalWrite(LCD_EN, LOW);

 

}

int _write (int fd, const void *buf, size_t count)
{
	uint8_t x;
	char *vet = (char *) buf;

	LCD_MODO_DADOS();
	//for (x=0;x<count;x++) LCD_envia_byte(  vet[x]);
	LCD_escreve("ssss");
	return count;
}

int _read (int fd, const void *buf, size_t count)
{
	return 1;
}


void LCD_limpa_tela(void)
{
    LCD_MODO_COMANDO();
    LCD_envia_byte(LCD_DISPLAY_CLEAR);  
    delay_ms(2);
    
}
void LCD_gotoxy(uint8_t coluna, uint8_t linha)
{
   /* LCD_MODO_COMANDO();
    LCD_envia_byte(0x02);  // posiciona o cursor no inicio  
    delay_ms(2);
    qtd = linha*16+coluna;
    for (x=0;x<qtd;x++) 
    {
        LCD_envia_byte(0x14);
        delay_us(40);
    }*/
    
}
void LCD_inicializa(void)
{

    pinMode(LCD_EN, OUTPUT);
    pinMode(LCD_RS, OUTPUT);
    pinMode(LCD_D0, OUTPUT);
    pinMode(LCD_D1, OUTPUT);
    pinMode(LCD_D2, OUTPUT);
    pinMode(LCD_D3, OUTPUT);
    pinMode(LCD_D4, OUTPUT);
    pinMode(LCD_D5, OUTPUT);
    pinMode(LCD_D6, OUTPUT);
    pinMode(LCD_D7, OUTPUT);


    digitalWrite(LCD_EN, LOW);

    delay_ms(50);
    LCD_MODO_COMANDO();
    LCD_envia_byte(0x3C);  // 8 bits, 2 linhas, fonte 5x7
    delay_us(40);
    LCD_envia_byte(0x3C);  // 8 bits, 2 linhas, fonte 5x7
    delay_us(40);
    LCD_envia_byte(0x0F);  // Liga display, liga cursor
    delay_us(40);
    LCD_envia_byte(LCD_DISPLAY_CLEAR);  
    delay_ms(2);
    LCD_envia_byte(LCD_ENTRY_MODE);  
    delay_ms(2);
    
}



void LCD_escreve(char *st)
{
    uint8_t x=0;

    LCD_MODO_DADOS();
    while (st[x] != 0)  LCD_envia_byte(st[x++]);
        
}

