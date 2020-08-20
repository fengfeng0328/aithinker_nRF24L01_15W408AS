#include "nRF24L01P.h"
#include "delay.h"


/* 按键及指示灯管脚定义 */
#define KEY1		P30
#define KEY2		P31
#define LED3		P16
#define LED4		P35

/* 程序入口函数 */
void main(void)
{
	
	KEY1 = 1;							/* 拉高 */
	KEY2 = 1;							/* 拉高 */
	
	nRF24L01P_Init();			/* nRF interface init */
	nRF24L01P_RX_Mode();	/* nRF goto rx mode */
	
	
	while(1)							/* while 1 */
	{
		u8 buf[32] = {0};		/* payload max len */
		
		KEY1 = 1;
		KEY2 = 1;
		
		if(!KEY1 || !KEY2)	/* 判断是否有按键按下 */
		{
			delay_ms(10);
			
			if(!KEY1)					/* 按键KEY1按下，低电平有效 */
			{
				buf[0] = 0x55;
				nRF24L01P_TX_Mode();
				nRF24L01P_TxPacket(buf);
				delay_ms(200);
			}
			
			if(!KEY2)					/* 按键KEY2按下，低电平有效 */
			{
				buf[0] = 0xAA;
				nRF24L01P_TX_Mode();
				nRF24L01P_TxPacket(buf);
				delay_ms(200);
			}
			
			buf[0] = 0;				/* 数据包发送完毕，清空缓存 */
			
			nRF24L01P_RX_Mode();
		}	
		
		if(!nRF24L01P_RxPacket(buf))
		{
			switch(buf[0])
			{
				case 0x55:			/* 目标按键KEY1按下 */
					LED3 = 0;			/* 点亮LED3，低电平有效 */
					delay_ms(100);
					LED3 = 1;			/* 关闭LED3，低电平有效 */
					delay_ms(100);
					break;
				
				case 0xAA:			/* 目标按键KEY2按下 */
					LED4 = 0;			/* 点亮LED4，低电平有效 */
					delay_ms(100);
					LED4 = 1;			/* 关闭LED4，低电平有效 */
					delay_ms(100);
					break;
				
				default:
					break;
			}
			
			buf[0] = 0;				/* 数据包处理完毕后，清空缓存 */
		}
		
	}
}

