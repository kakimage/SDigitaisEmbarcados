#include "i2c_software.h"
#include "digital.h"
#include "delay.h"

uint32_t PINO_DADOS;
uint32_t PINO_CLOCK;


void _DADOS_LOW (void)
{
		pinMode(PINO_DADOS, OUTPUT);
		digitalWrite(PINO_DADOS, LOW);
}
void _DADOS_HIGH (void)
{
		pinMode(PINO_DADOS, INPUT);
}
void _CLOCK_LOW (void)
{
		pinMode(PINO_CLOCK, OUTPUT);
		digitalWrite(PINO_CLOCK, LOW);
}
void _CLOCK_HIGH (void)
{
	pinMode(PINO_CLOCK, INPUT);
}
void i2c_configura (uint32_t pino_dados, uint32_t pino_clock)
{
	PINO_DADOS = pino_dados;
	PINO_CLOCK = pino_clock;
	_DADOS_HIGH();
	_CLOCK_HIGH();
	delay_ms(1);
}

void i2c_start (void)
{
	_CLOCK_HIGH();
	delay_us(10);
	_DADOS_HIGH();
	delay_us(10);
	_DADOS_LOW();
	delay_us(10);
	_CLOCK_LOW();
 	delay_us(10);  
}
void i2c_stop (void)
{
	_DADOS_LOW();
	  delay_us(5);
	_CLOCK_LOW();
      delay_us(5);
	_CLOCK_HIGH();
	  delay_us(5);
	_DADOS_HIGH();
	  delay_us(5);
	
}
uint8_t i2c_le_bit (void)
{
    uint8_t valor;

	_DADOS_HIGH();
    delay_us(10);
    _CLOCK_HIGH();
    valor=digitalRead(PINO_DADOS);
    delay_us(10);
    _CLOCK_LOW();
    return valor;
}
uint8_t i2c_envia_byte (uint8_t dados)
{
	int8_t x;

	for (x=7;x>=0;x--)
	{
		_CLOCK_LOW();
		delay_us(50);
		if (  ( (dados >> x) & 1) ) _DADOS_HIGH();
		else _DADOS_LOW();
		 delay_us(10);
 	   _CLOCK_HIGH();
    	delay_us(10);

		//deixa preparado para o proximo
	   _CLOCK_LOW();
       _DADOS_HIGH();
		
		
	}
	return i2c_le_bit();
	
}

void i2c_memoria_escreve (uint16_t end, uint8_t v)
{

  	i2c_start();
		i2c_envia_byte (0xA0 );
		i2c_envia_byte ( end >> 8 );
		i2c_envia_byte ( end );
		i2c_envia_byte ( v );
	i2c_stop();

	// verifica se terminou a gravacao
	while(1)
	{
		i2c_start();
		if (i2c_envia_byte (0xA0 | 0 )==0) break;
	}
	i2c_stop();

}
void i2c_bit (uint8_t valor_bit)
{
    if (valor_bit) _DADOS_HIGH();
    else _DADOS_LOW();
    delay_us(10);
    _CLOCK_HIGH();
    delay_us(10);
    _CLOCK_LOW();
    _DADOS_HIGH();
}
uint8_t i2c_read_ACK (uint8_t v)
{

	uint8_t valor=0,x;
	
	for (x = 0; x < 8; x++) valor = (valor << 1) | i2c_le_bit();
	i2c_bit(v);
    return valor;
}
uint8_t i2c_memoria_le (uint16_t end)
{

    uint8_t valor;
    i2c_start ( );
	i2c_envia_byte (0xA0 );// comeca como um write
	i2c_envia_byte ( end >> 8 );
	i2c_envia_byte ( end );

	// read inicia neste ponto
	i2c_start ( );
		i2c_envia_byte (0xA1 );// comeca como um write
		valor =  i2c_read_ACK(1);
	i2c_stop();
    return valor;
}
void i2c_memoria_le_bytes( uint8_t buffer[], uint16_t end,  uint16_t qtd)
{

	uint16_t x;

	i2c_start();
	i2c_envia_byte(0xA0);  // comeca como write
	i2c_envia_byte ( end >> 8 );
	i2c_envia_byte ( end );
	i2c_start ( );
	i2c_envia_byte (0xA1 );// comeca como um read

	for (x=0;x<qtd-1;x++)  buffer[x] = i2c_read_ACK(0);
	buffer[x] = i2c_read_ACK(1);
	i2c_stop();
}



void i2c_escreve_bytes (uint8_t buffer[], uint16_t end_atual, uint16_t ler )
{

	uint16_t x;
	i2c_start();
		i2c_envia_byte (0xA0 );
		i2c_envia_byte ( end_atual >> 8 );
		i2c_envia_byte ( end_atual );
		for (x=0;x<ler;x++) 	i2c_envia_byte ( buffer[x] );
	i2c_stop();
	while(1)
	{
		i2c_start();
		if (i2c_envia_byte (0xA0 | 0 )==0) break;
	}
	i2c_stop();
	
}
void i2c_memoria_escreve_bytes( uint8_t buffer[], uint16_t end, uint16_t qtd)
{
	uint16_t end_atual = end;
	uint8_t pagina,ler;
	
	while (end_atual < end + qtd)
	{
		pagina = end_atual / TAMANHO_PAGINA;
		ler = ((pagina + 1 ) * TAMANHO_PAGINA)-end_atual;
		ler = min(min(TAMANHO_PAGINA,(end+qtd)-end_atual),ler);

		i2c_escreve_bytes (buffer, end_atual, ler );
		end_atual += ler;
		buffer    += ler;
	}	

}

