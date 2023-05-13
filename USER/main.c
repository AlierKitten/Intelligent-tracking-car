#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "pwm.h"
#include "lunzi.h"
#include "led1.h"
#include "stdio.h"
#include "control.h"
#include "lk.h"
//////////////////////////////////////////////////////////////////////////////////	 
//δ��������ɣ��������������κ���;
//STM32f103c8t6��Сϵͳ������
//���ߣ�sfykuer  QQ:475499548
//�޸�����:2019/11/06
//�汾��V2.1
//��Ȩ���У�����ؾ���
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

extern int stopconfig; //����lk.c�����stopconfig��������main.c��ʹ��stopconfig�ñ���
int sensor[9]={0,0,0,0,0,0,0,0,0};   //����һ�����飬���ڴ�����⴫�������ص�ֵ����Ϊ�оŸ������������Զ���������Ԫ�ظ���Ϊ9
int Prestopconfig=0;//����һ���������ŵ�lk.c�ļ�read_sensor������ʶ���յ��ߵ������

int main(void)
{
	SystemInit();  //ϵͳʱ�ӵĳ�ʼ��
	delay_init();  //��ʱʱ�ӵĳ�ʼ��
	LED1_Init();	 //STM32f103c8t6��Сϵͳ���ϵ�LED�Ƶĳ�ʼ��
	lunzi_Init();  //������е�״̬�ĳ�ʼ���������ǰ�����ߺ��ˣ�
  hongwai_Init();  //�Ÿ����⴫����������Сϵͳ���ϵĹܽ�IO�ڵĳ�ʼ��
	
	 uart_init(9600);  //����ͨ�ŵĳ�ʼ����������Ӧ�Ĳ�����9600������USB232������.hex�����ļ�ʱ��
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����жϷ��飬Ҳ���ǳ����Ⱥ�ִ�е����ȼ�
	 TIM2_PWM_Init(7199,0);  //PWM���ĳ�ʼ��������С��������٣�����7199��0��ʹ��PWM��Ƶ��Ϊ10Khz    f=72000000/((7199+1)*(0+1))=10000
	 TIM4_PWM_Init(19999,71);   //PWM���ĳ�ʼ�������ڶ�����٣��������õ�Ƶ��Ϊ50hz  �����ó�������T=1/f=20ms  ��ΪMG90S�����PWM�����ź�Ϊ20ms������޷�����
	 TIM3_Init_Init(99,7199);	  //�жϷ������ĳ�ʼ����Ҳ����PWM���ĳ�ʼ�������������Ϊ10ms��Ҳ����ÿ10ms��ִ��һ��control.c�ļ���TIM3_IRQHandler������Ĳ���
	 		
	    GPIO_SetBits(GPIOB,GPIO_Pin_12);//PB12�ܽ�����ߵ�ƽ	//�����c8t6�������ɵ��ӵ���ģ����ϵ�LED�ƽӵ�IO�ܽž���PB12
			delay_ms(1000);					//��ʱ1000ms=1s					//����������ʹLED��˸
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);//PB12�ܽ�����͵�ƽ
			delay_ms(1000);					//��ʱ1000ms=1s
	    
			while(1) 
		{	
			read_sensor();  //��ȡ���⴫��������ֵ�ĺ�����ʼ��
			if(stopconfig==0)//���stopconfigδ�ı䣬Ҳ���ǵ���0ʱ��С����ǰ��ʻ
			{
			forward();    //С�������ǰ
			GPIO_SetBits(GPIOB,GPIO_Pin_8);  //PB8�ܽ�����ߵ�ƽ������ܽ��ǿ����ҵĵ��������TB6612��ʹ�ܶˣ��ߵ�ƽʱ���������Ż���Ƶ����Ҳ���Ƿ���PWM�����͵�ƽʱ������ֹͣ����
			}	
			else  //���ʶ���յ��ߣ�stopconfig��ֵ��󣬲�����0����ʱʹС��ɲ��
			{
				stop();     //С��������
				delay_ms(280);
				GPIO_ResetBits(GPIOB,GPIO_Pin_8);//PB8�ܽ�����͵�ƽ
				while(1)
				{
				GPIO_SetBits(GPIOB,GPIO_Pin_12);	//����LED����˸����
			  delay_ms(300);
			  GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			  delay_ms(300);
				}
			}
			if(Prestopconfig==0)//��ʼʱPrestopconfig==0�������߾Ͳ���ʶ�𵽣�����С���Ͳ���һ��ʼ��ִ��ɲ��
			{
			delay_ms(400);//��ʱ0.4s���ʹPrestopconfig=1,��ʱС���Ѿ����������ߣ��ܹ��������ߵļ�⣬������һ��ʶ��������(�յ���)��Ҳ����С��������һȦ������ɲ��
			Prestopconfig=1;
			}
		}
		
			 }
			 
			  


			
		



	
		


	
	

