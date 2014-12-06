#include "stm32f10x.h"
#include "USART.h"
#include "sys.h"
#include "delay.h"
/**********************************************************
** ������: main(void)
** ��������: ���ڻ���������printf��ʽ������
** �������: ��
** �������: ��
** ˵����
***********************************************************/
/******3200����Ϊ1�ȣ���ʱΪ32ϸ��**********/
#define SPEED 20
void GPIO_Configuration()
{
  RCC->APB2ENR|=1<<3;

  GPIOB->CRL&=0xffffff00;
  GPIOB->CRL|=0x00000088;

  RCC->APB2ENR|=1<<2;
  GPIOA->CRL&=0xffffff00;
  GPIOA->CRL|=0x00000033;

  GPIOB->ODR|=1<<0;
  GPIOB->ODR|=1<<1;

  GPIOA->ODR|=1<<0;

}
int main(void)
{
  	//u16 data=13424;
  	//float fl=3.141592653589;
	unsigned char temp;
	long int i,j;
	int range=0;
  	SystemInit(); //ϵͳʱ�ӳ�ʼ��
	Usart_Configuration(9600);//���ڳ�ʼ������
    delay_init(72);
    GPIO_Configuration();
	while(1)
	{

	while((USART1->SR&0x20)==0)
	{
	   if(PBin(0)==0)
	   {  
		     PAout(1)=0;
			 //USART1_Putc('1');
		     for(i=0;i<100;i++)
			   {
			    PAout(0)=0;
			    delay_us(SPEED);
		        PAout(0)=1;
		        delay_us(SPEED);
			   }
		  
		}
	   else if(PBin(1)==0)
		{ 
		     PAout(1)=1;
			// USART1_Putc('1');
		     for(i=0;i<100;i++)
			   {
			    PAout(0)=0;
			    delay_us(SPEED);
		        PAout(0)=1;
		        delay_us(SPEED);
			   }
		  
		}

	}	
	
	PAout(1)=1;


	/*while((USART1->SR&0x20)==0);
	temp=USART1->DR;
	USART1_Putc(temp);
	for(i=0;i<32000;i++)
	     {
		     PAout(0)=0;
			 delay_us(SPEED);
		     PAout(0)=1;
		     delay_us(SPEED);
		 }
	  while(1);	 */
	temp=USART1->DR;
	//while((USART1->SR&0x20)==0);
	//temp=USART1->DR;
	USART1_Putc(temp);
	range=160*(int)(temp-'0');
	
    
		PAout(0)=0;
	    while(1)
	    {
	      while((USART1->SR&0x20)==0);
	      temp=USART1->DR;
		  if(temp=='2')
		       break;

	      for(i=0;i<range;i++) //320 ----0.1��  �� 160----0.05��
	     {
		     PAout(0)=0;
			 delay_us(SPEED);
		     PAout(0)=1;
		     delay_us(SPEED);
		 }
	      PAout(0)=0; 	
	   
	      USART1_Putc(temp);
		}
	  
	 }	  
	  
}
