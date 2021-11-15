#include <stddef.h>
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include <stdio.h>


void output(unsigned char *word)
{
  unsigned char *msg ;
  msg = word;
  int i = 0;
  while (msg[i] != '\0')
   {
     USART_sendC(msg[i]);
     i++;
   }

}
void USART_sendC(unsigned char c)
{
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
  USART_SendData(USART1,(unsigned char) c); 
}

unsigned char USART_getC()
{
  while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==RESET);
  return(USART_ReceiveData(USART1)); 
}

void null_array(unsigned char *a, size_t size)
{ 
   for(int i = 0; i < size; i++) 
      a[i] = 0; 
} 

int main(void)
{
  int i = 0;
  // Define variable type GPIO
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStructure;
  unsigned char sData=0x20;
  unsigned char *msg ;

  unsigned char *msg_con1 ;
  unsigned char *A_1 ;
  A_1 ="Why me";
  unsigned char *A_2 ;
  A_2 ="What must we do today";
  unsigned char *A_3 ;
  A_3 ="What is the topic";
  unsigned char *A_4 ;
  A_4="Do you know nothing right";
  unsigned char *A_5 ;
  A_5="How many points that we should get today";
  unsigned char *A_6 ;
  A_6="0/";

  unsigned char msg_con[45] ;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
  GPIO_InitStruct.GPIO_Pin= GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//50Mhz
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;// Configure PA as push-pull output
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin= GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//50Mhz
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;// Configure PA as push-pull output
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  USART_Cmd(USART1, ENABLE);
  USART_InitStructure.USART_BaudRate = 19200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
  /* Infinite loop */
  USART_sendC('\n');
  USART_sendC('\r');
  msg =  "Hello World\0";
  output(msg);
  USART_sendC('\n');
  USART_sendC('\r');
  msg =  "Nice to meet you\0";
  output(msg);
  USART_sendC('\n');
  USART_sendC('\r');
  msg =  "I can chat with you\0";
  output(msg);
  USART_sendC('\n');
  USART_sendC('\r');
  USART_sendC('>');
  while(1)
  {
      sData = 0x20;
      i = 0;
      null_array(msg_con,45);
      while(1)
      {
          sData = USART_getC();     
          if(sData== '\n' ||sData == '\r')
          {
        	  //USART_sendC('\n');
        	  //USART_sendC('\r');
        	  			 //USART_sendC('>');
            //USART_sendC(sData);
            //output(msg_con);
            i = 0;
            if(memcmp(msg_con,A_1,8) == 0)
            {
              USART_sendC('\n');
              USART_sendC('\r');
              msg_con1 = "You are unlucky.\0";
              output(msg_con1);
              null_array(msg_con,45);
              //output(msg_con);

            }
            else if(memcmp(msg_con,A_2,23) == 0)
            {
              USART_sendC('\n');
              USART_sendC('\r');
              msg =  "You must present\0";
              output(msg);
              null_array(msg_con,45);
            }
            else if(memcmp(msg_con,A_3,19) == 0)
            {
              USART_sendC('\n');
              USART_sendC('\r');
              msg =  "I don't know either.\0";
              output(msg);
              null_array(msg_con,45);
            }
            else if(memcmp(msg_con,A_4,28) == 0)
            {
              USART_sendC('\n');
              USART_sendC('\r');
              msg =  "Yes my brain is completely emtry.\0";
              output(msg);
              null_array(msg_con,45);
            }

            else if(memcmp(msg_con,A_5,42) == 0)
            {
              USART_sendC('\n');
              USART_sendC('\r');
              msg = "We think it should be full\0";
              output(msg);
              null_array(msg_con,45);
            }
	    else if( (memcmp(msg_con,A_6,15) > 0 ))
	    {
	      USART_sendC('\n');
	      USART_sendC('\r');
	      msg = "I don't understand\0";
	      output(msg);
	      null_array(msg_con,15);
	    }

			 USART_sendC('\n');
			 USART_sendC('\r');
			 USART_sendC('>');



          null_array(msg_con,15);
          }
          else
          {
            USART_sendC(sData);
            //unsigned char *msd = sData
            msg_con[i] = sData;
            i++;
          }

      }

  }
}

    

  


