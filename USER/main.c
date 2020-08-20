#include "nRF24L01P.h"
#include "delay.h"


/* ������ָʾ�ƹܽŶ��� */
#define KEY1		P30
#define KEY2		P31
#define LED3		P16
#define LED4		P35

/* ������ں��� */
void main(void)
{
	
	KEY1 = 1;							/* ���� */
	KEY2 = 1;							/* ���� */
	
	nRF24L01P_Init();			/* nRF interface init */
	nRF24L01P_RX_Mode();	/* nRF goto rx mode */
	
	
	while(1)							/* while 1 */
	{
		u8 buf[32] = {0};		/* payload max len */
		
		KEY1 = 1;
		KEY2 = 1;
		
		if(!KEY1 || !KEY2)	/* �ж��Ƿ��а������� */
		{
			delay_ms(10);
			
			if(!KEY1)					/* ����KEY1���£��͵�ƽ��Ч */
			{
				buf[0] = 0x55;
				nRF24L01P_TX_Mode();
				nRF24L01P_TxPacket(buf);
				delay_ms(200);
			}
			
			if(!KEY2)					/* ����KEY2���£��͵�ƽ��Ч */
			{
				buf[0] = 0xAA;
				nRF24L01P_TX_Mode();
				nRF24L01P_TxPacket(buf);
				delay_ms(200);
			}
			
			buf[0] = 0;				/* ���ݰ�������ϣ���ջ��� */
			
			nRF24L01P_RX_Mode();
		}	
		
		if(!nRF24L01P_RxPacket(buf))
		{
			switch(buf[0])
			{
				case 0x55:			/* Ŀ�갴��KEY1���� */
					LED3 = 0;			/* ����LED3���͵�ƽ��Ч */
					delay_ms(100);
					LED3 = 1;			/* �ر�LED3���͵�ƽ��Ч */
					delay_ms(100);
					break;
				
				case 0xAA:			/* Ŀ�갴��KEY2���� */
					LED4 = 0;			/* ����LED4���͵�ƽ��Ч */
					delay_ms(100);
					LED4 = 1;			/* �ر�LED4���͵�ƽ��Ч */
					delay_ms(100);
					break;
				
				default:
					break;
			}
			
			buf[0] = 0;				/* ���ݰ�������Ϻ���ջ��� */
		}
		
	}
}

