#include <stm32f0xx.h>                    
#include <stm32f0xx_rcc.h>            
#include <stm32f0xx_gpio.h>            
#include "lcd_lib.h"


#define DS_GPIO		GPIOB

#define DS_I2C		I2C2
#define DS_ADDR		(0x68<<1)

//DS1307 Registers
#define DS_SECS		0x00
#define DS_MINS		0x01
#define DS_HOUR		0x02
#define DS_DAY		0x03
#define DS_DATE		0x04
#define DS_MNTH		0x05
#define DS_YEAR		0x06
#define DS_CTRL		0x07

volatile unsigned int count=0;
uint8_t data[7]={0};
volatile uint8_t giay=55, phut=50, gio=10;
volatile uint8_t day=1, ngay=6,thang=4,nam=17;
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->ODR ^= GPIO_Pin;
}
uint8_t Dec_BCD(uint8_t Dec){
	uint8_t temp,H,L;
	L=(Dec%10);
	H=(Dec/10)<<4;
	
	return (H+L);
}

uint8_t BCD_Dec(uint8_t BCD){
	uint8_t L,H;
	L=BCD&0x0F;
	H=(BCD>>4)*10;
	return (H+L);	
}

/*the function write data onto ds1307-----------------------*/
void I2C_WrReg(uint8_t Reg, uint8_t Dat){
	while(I2C_GetFlagStatus(DS_I2C, I2C_FLAG_BUSY) == SET);//if busy_flag=1 then last transmit was completed and next data is transmit

	I2C_TransferHandling(DS_I2C, DS_ADDR, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);//start condition include slave'addresss
	while(I2C_GetFlagStatus(DS_I2C, I2C_FLAG_TXIS) == RESET);//wait TXIS=1

	I2C_SendData(DS_I2C, Reg);//send register's address need to be write in the ds1307
	while(I2C_GetFlagStatus(DS_I2C, I2C_FLAG_TCR) == RESET);//TCR_FLAG=1 to keep transfering data

	I2C_TransferHandling(DS_I2C, DS_ADDR, 1, I2C_AutoEnd_Mode, I2C_No_StartStop);
	while(I2C_GetFlagStatus(DS_I2C, I2C_FLAG_TXIS) == RESET);//wait data in I2Cx_TXDR register is empty(TXIS=1) 

	I2C_SendData(DS_I2C, Dat);//send data to ds1307
	while(I2C_GetFlagStatus(DS_I2C, I2C_FLAG_STOPF) == RESET); //wait STOP flag =1
	I2C_ClearFlag(DS_I2C, I2C_FLAG_STOPF);//finish transmit's progress
}
/*---------------------------------------------------------*/
 
/*st32 receiver data form slave ds1307*/ 
uint8_t I2C_RdReg(uint8_t Reg){
	uint8_t Dat;
	while(I2C_GetFlagStatus(DS_I2C, I2C_FLAG_BUSY) == SET);

	I2C_TransferHandling(DS_I2C, DS_ADDR, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
	while(I2C_GetFlagStatus(DS_I2C, I2C_FLAG_TXIS) == RESET);

	I2C_SendData(DS_I2C, Reg);
	while(I2C_GetFlagStatus(DS_I2C, I2C_FLAG_TC) == RESET);//TC_flag=1, data have been receivered

	I2C_TransferHandling(DS_I2C, DS_ADDR, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);//one byte data have been receivered and actived read mode 
	while(I2C_GetFlagStatus(DS_I2C, I2C_FLAG_RXNE) == RESET);// RXNE=1, then the received data is copied into the I2Cx_RXDR register

	Dat = I2C_ReceiveData(DS_I2C);

	while(I2C_GetFlagStatus(DS_I2C, I2C_FLAG_STOPF) == RESET);//
	I2C_ClearFlag(DS_I2C, I2C_FLAG_STOPF);// finish receive'progess

	return Dat;
}
void setTimeDate(uint8_t *Dat, uint8_t len){	
uint8_t i;
	for(i=0; i<len; i++){
		I2C_WrReg(i,Dat[i]);
	}
}

void DS_GetTime(uint8_t *Dat, uint8_t len){
	uint8_t i=0;
	for(i=0; i<len; i++){
		Dat[i]=I2C_RdReg(i);
	}
}

void gpio_setup(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    // PORTB
    // LCD_D7 - PB7
    // LCD_D6 - PB6
    // LCD_D5 - PB5
    // LCD_D4 - PB4
  GPIO_InitStructure.GPIO_Pin        = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed    = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType    = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
     // LCD_RS - PC10
     // LCD_RW - PC11
     // LCD_EN - PC12
  GPIO_InitStructure.GPIO_Pin        = GPIO_Pin_12 | GPIO_Pin_11|GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed    = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType    = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	

	
}
//Initialization I2C
void I2C_setup(void){
	I2C_InitTypeDef I;
	GPIO_InitTypeDef G;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	SysTick_Config(SystemCoreClock/1000);
//GPIOB10-SCK     GPIO11-SDA
	G.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	G.GPIO_OType = GPIO_OType_OD;
	G.GPIO_PuPd = GPIO_PuPd_UP;
	G.GPIO_Speed = GPIO_Speed_Level_1;
	G.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(DS_GPIO, &G);
	GPIO_PinAFConfig(DS_GPIO, GPIO_PinSource11, GPIO_AF_1);
	GPIO_PinAFConfig(DS_GPIO, GPIO_PinSource10, GPIO_AF_1);
//configuration I2C
	I.I2C_Ack = I2C_Ack_Enable;
	I.I2C_AcknowledgedAddress = 0x00;
	I.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
	I.I2C_DigitalFilter = 0x00;
	I.I2C_Mode = I2C_Mode_I2C;
	I.I2C_OwnAddress1 = 0x01;
	I.I2C_Timing = 0x10805F87;//refer caculator in the 02_STM32F0 reference manual(page 502)
	I2C_Init(DS_I2C, &I);
	I2C_Cmd(DS_I2C, ENABLE);
}
void timer_setup(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
  /* Time base configuration ,use timer3*/
	//timing 1ms
  TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock)/1000000)-1;     
  TIM_TimeBaseStructure.TIM_Period = 1000 - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM3, ENABLE);
   
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   
  TIM3->DIER=1;
}
void Display(void){
	
	 giay=BCD_Dec(data[0]&0x7F);
	 phut=BCD_Dec(data[1]);
	 gio=BCD_Dec(data[2]&0x1F);// mode 12h
	 
	 ngay=BCD_Dec(data[4]);
	 thang=BCD_Dec(data[5]);
	 nam=BCD_Dec(data[6]);
	 

	 LCD_goto(1,1);
	 lcd_write_string_4d("Time: ");
	 LCD_goto(1,7);
	 printnumber_lcd(gio);
	 LCD_goto(1,9);
	 lcd_write_character_4d(':');
	 LCD_goto(1,10);
	 printnumber_lcd(phut);
	 LCD_goto(1,12);
	 lcd_write_character_4d(':');
	 LCD_goto(1,13);
	 printnumber_lcd(giay);
	 
	 LCD_goto(1,16);
	 if((data[2]&0x10)==0x00) lcd_write_character_4d('A');
	 else lcd_write_character_4d('P');
	 
	 LCD_goto(2,1);
	 lcd_write_string_4d("Date: ");
	 LCD_goto(2,7);
	 printnumber_lcd(ngay);
	 lcd_write_character_4d('-');
	 printnumber_lcd(thang);
	 lcd_write_character_4d('-');
	 printnumber_lcd(nam);
	 
}
int main(void)
{
	uint8_t x;
		
		I2C_setup();
		timer_setup();
    gpio_setup();
		lcd_init_4d();
//setup time to display
		data[0]=Dec_BCD(giay);
		data[1]=Dec_BCD(phut);
		data[2]=Dec_BCD(gio)|(1<<6)|(1<<5);
		data[3]=Dec_BCD(day);
		data[4]=Dec_BCD(ngay);
		data[5]=Dec_BCD(thang);
		data[6]=Dec_BCD(nam);
	
		setTimeDate(data,7);
		delay_ms(2);
		DS_GetTime(data,7);
		Display();
while(1)
    {
    }	

}
		
void TIM3_IRQHandler(void){

  static uint32_t time=0;
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    if(++time>50)//50ms then update data display on textlcd
    {
 								DS_GetTime(data,7);
								delay_ms(1);	
								if(BCD_Dec(data[0]&0x7F)!=giay){
										
										giay=BCD_Dec(data[0]&0x7F);
										LCD_goto(1,13);                                                         
										lcd_write_string_4d("  ");
										LCD_goto(1,13);
										printnumber_lcd(giay);
										if(giay==0) Display();
      time = 0;
    }
}
}
}






