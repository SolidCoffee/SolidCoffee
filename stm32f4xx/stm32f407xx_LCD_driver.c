/*
 * stm32f407xx_LCD_driver.c
 *
 *  Created on: Jan 9, 2023
 *      Author: gianl
 */

#include "stm32f407xx_LCD_driver.h"

static void write_4_bits(uint8_t value);
//static void write_8_bits(uint8_t value);
static void lcd_enable(void);
//static void mdelay(uint32_t cnt);
//static void udelay(uint32_t cnt);
//static void lcd_enable_8_bit(void);

void lcd_print_data(uint8_t data)
{
	/* RS=1 for LCD user data */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, ENABLE);

	/*R/nW = 0, for write */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, DISABLE);

	write_4_bits((data >> 4)&0x0F);  /*Higher nibble*/
	write_4_bits(data & 0x0F); /*Lower nibble*/

}

void lcd_send_command(uint8_t cmd)
{
	/* RS=0 for LCD command */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, DISABLE);

	/*R/nW = 0, for write */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, DISABLE);

	write_4_bits((cmd >> 4)&0x0F);
	write_4_bits(cmd & 0x0F);

}

void lcd_print_string(char *message)
{

      do
      {
          lcd_print_data((uint8_t)*message++);
      }
      while (*message != '\0');

}

void lcd_set_cursor(uint8_t row, uint8_t column)
{
  column--;
  switch (row)
  {
    case 1:
      /* Set cursor to 1st row address and add index*/
      lcd_send_command((column |= 0x80));
      break;
    case 2:
      /* Set cursor to 2nd row address and add index*/
        lcd_send_command((column |= 0xC0));
      break;
    default:
      break;
  }
}

/*void lcd_send_data_8_bit(uint8_t data)
{
	// RS=1 for LCD user data
	GPIO_WriteToOutputPin(LCD_CONTROL_PORT, LCD_GPIO_RS, ENABLE);
	//R/nW = 0, for write
	GPIO_WriteToOutputPin(LCD_CONTROL_PORT, LCD_GPIO_RW, DISABLE);
	write_8_bits(data);
}*/

/*void lcd_print_string_8_bit(char *message)
{
      do
      {
    	  lcd_send_data_8_bit((uint8_t)*message++);
      }
      while (*message != '\0');
}*/

void lcd_init(void)
{
	//configure the gpio pins which are used for LCD connections

	BasicTIM_Handler_t LCD_timer;

	LCD_timer.pTIMx = TIM6;
	LCD_timer.TIM_Config.Buffer=0;
	LCD_timer.TIM_Config.Interrupt=0;
	LCD_timer.TIM_Config.MMS=2;
	LCD_timer.TIM_Config.Mode=0;
	LCD_timer.TIM_Config.Prescaler=16-1;

	BASIC_TIMCLKEnable(TIM6, ENABLE);

	BasicTIM_INIT(&LCD_timer);

	StopTimerDelay(TIM6, 50000);

	GPIO_Handler_t lcd_signal;

	lcd_signal.pGPIOx = LCD_GPIO_PORT;
	lcd_signal.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	lcd_signal.GPIO_PinConfig.GPIO_PinSpeed = FAST;
	lcd_signal.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
	lcd_signal.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_E;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
	GPIO_Init(&lcd_signal);

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_E, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, DISABLE);


	//LCD initialization
	StopTimerDelay(TIM6, 50000); // 50 ms > 40ms
	//mdelay(40);

	//GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, DISABLE);
	//GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, DISABLE);

	//lcd_send_command(LCD_4_BIT_INIT);
	write_4_bits(LCD_4_BIT_INIT);

	StopTimerDelay(TIM6, 5000); // 5 ms > 4.1 ms
	//mdelay(5);

	//lcd_send_command(LCD_4_BIT_INIT);
	write_4_bits(LCD_4_BIT_INIT);

	StopTimerDelay(TIM6, 1000); // 200 microsecond > 100 microsecond
	//udelay(150);

	//lcd_send_command(LCD_4_BIT_INIT);
	write_4_bits(LCD_4_BIT_INIT);

	StopTimerDelay(TIM6, 10000);

	//lcd_send_command(0x20);
	write_4_bits(0x2);

	StopTimerDelay(TIM6, 10000);

	//information for screen (command not data) function set
	lcd_send_command(LCD_CMD_4DL_2N_5X8F);

	StopTimerDelay(TIM6, 1000);

	//display on and cursor on
	lcd_send_command(0x08);

	StopTimerDelay(TIM6, 1000);

	//display clear
	//lcd_display_clear();
	lcd_send_command(LCD_CMD_DIS_CLEAR);

	StopTimerDelay(TIM6, 1000);

	//entry mode st
	lcd_send_command(LCD_CMD_ENTRY_SET);

	StopTimerDelay(TIM6, 1000);

	lcd_send_command(0x0C);

}

void lcd_send_string (char *str)
{
	while (*str) lcd_print_data (*str++);
}

/*void lcd_init_8_bit(void)
{
	GPIO_Handler_t lcd_signal;
	lcd_signal.pGPIOx = LCD_GPIO_PORT;
	lcd_signal.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D0;
	lcd_signal.GPIO_PinConfig.GPIO_PinSpeed = FAST;
	lcd_signal.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
	lcd_signal.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D1;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D2;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D3;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
	GPIO_Init(&lcd_signal);
	lcd_signal.pGPIOx = LCD_CONTROL_PORT;
	lcd_signal.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	lcd_signal.GPIO_PinConfig.GPIO_PinSpeed = FAST;
	lcd_signal.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
	lcd_signal.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_E;
	GPIO_Init(&lcd_signal);
	GPIO_WriteToOutputPin(LCD_CONTROL_PORT, LCD_GPIO_RS, DISABLE);
	GPIO_WriteToOutputPin(LCD_CONTROL_PORT, LCD_GPIO_RW, DISABLE);
	GPIO_WriteToOutputPin(LCD_CONTROL_PORT, LCD_GPIO_E, DISABLE);
	GPIO_WriteToOutputPort(LCD_GPIO_PORT, DISABLE);
	//2. Do the LCD initialization
	mdelay(200);
	//RS = 0 , For LCD command
	GPIO_WriteToOutputPin(LCD_CONTROL_PORT, LCD_GPIO_RS, DISABLE);
	// RnW = 0, Writing to LCD
	GPIO_WriteToOutputPin(LCD_CONTROL_PORT, LCD_GPIO_RW, DISABLE);
	write_8_bits(LCD_8_BIT_INIT);
	mdelay(200);
	write_8_bits(LCD_8_BIT_INIT);
	mdelay(200);
	write_8_bits(LCD_8_BIT_INIT);
	mdelay(200);
	write_8_bits(0x38); // function set
	mdelay(200);
	write_8_bits(0xF); //Display on
	mdelay(200);
	write_8_bits(0x01); //display clear
	mdelay(200);
	write_8_bits(0x04);//Entry mode set
	mdelay(200);
	//write_8_bits(0xF); //turn display and cursor on
}*/

/*void lcd_init_4_bit(void)
{
	//1. Configure the gpio pins which are used for lcd connections
	GPIO_Handler_t lcd_signal;
	lcd_signal.pGPIOx = LCD_GPIO_PORT;
	lcd_signal.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	lcd_signal.GPIO_PinConfig.GPIO_PinSpeed = FAST;
	lcd_signal.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
	lcd_signal.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_E;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
	GPIO_Init(&lcd_signal);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_E, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, DISABLE);
	//2. Do the LCD initialization
	mdelay(40);
	//RS = 0 , For LCD command
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, DISABLE);
	// RnW = 0, Writing to LCD
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, DISABLE);
	write_4_bits(0x3);
	mdelay(5);
	write_4_bits(0x3);
	udelay(150);
	write_4_bits(0x3);
	write_4_bits(0x2);
	//function set command
	lcd_send_command(LCD_CMD_4DL_2N_5X8F);
	//disply ON and cursor ON
	lcd_send_command(LCD_CMD_DON_CURON);
	lcd_display_clear();
	//entry mode set
	lcd_send_command(LCD_CMD_INCADD);
}*/

/*static void write_8_bits(uint8_t value)
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D0, ((value >> 0) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D1, ((value >> 1) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D2, ((value >> 2) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D3, ((value >> 3) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, ((value >> 4) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, ((value >> 5) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, ((value >> 6) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, ((value >> 7) & 0x1));
	lcd_enable_8_bit();
}*/

static void write_4_bits(uint8_t value)
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT,LCD_GPIO_D4, ((value >> 0) & 0x1) );
	GPIO_WriteToOutputPin(LCD_GPIO_PORT,LCD_GPIO_D5, ((value >> 1) & 0x1) );
	GPIO_WriteToOutputPin(LCD_GPIO_PORT,LCD_GPIO_D6, ((value >> 2) & 0x1) );
	GPIO_WriteToOutputPin(LCD_GPIO_PORT,LCD_GPIO_D7, ((value >> 3) & 0x1) );

	lcd_enable();

}

void lcd_display_clear(void)
{
	lcd_send_command(LCD_CMD_DIS_CLEAR);
	StopTimerDelay(TIM6, 2);
	//mdelay(2);
}

void lcd_return_home(void)
{
	lcd_send_command(LCD_CMD_DIS_RETURN_HOME);
	StopTimerDelay(TIM6, 2000); //> 1.5 ms
	//mdelay(2);
}

/*static void lcd_enable_8_bit(void)
{
	GPIO_WriteToOutputPin(LCD_CONTROL_PORT, LCD_GPIO_E, ENABLE);
	//StopTimerDelay(TIM6, 10);
	udelay(100);
	GPIO_WriteToOutputPin(LCD_CONTROL_PORT, LCD_GPIO_E, DISABLE);
	//StopTimerDelay(TIM6, 100);
	udelay(1000);
}*/


static void lcd_enable(void)
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_E, ENABLE);
	StopTimerDelay(TIM6, 40);
	//udelay(10);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_E, DISABLE);
	StopTimerDelay(TIM6, 40);
	//udelay(100);
}



/*static void mdelay(uint32_t cnt)
{
	for(uint32_t i=0 ; i < (cnt * 1000); i++);
}
static void udelay(uint32_t cnt)
{
	for(uint32_t i=0 ; i < (cnt * 1); i++);
}*/

