/*****************************************************
* @Author  :  Fengzhaoliang
* @File    :  main.c
* @Date    :  2017-04-29
* @Function:  UCOSII transplant template
******************************************************/

#include "stm32f4xx.h"
#include "bsp.h"
#include "ucos_ii.h"

#define  TEST_TASK_STK_SIZE                   256
#define  TEST_Idle_STK_SIZE                   256
#define  OSTASK_TEST_PRIO            				  3
#define  OSTASK_Idle_PRIO            				  5

__align(8) static OS_STK Test_Task_STK[TEST_TASK_STK_SIZE];
__align(8) static OS_STK Test_Idle_STK[TEST_TASK_STK_SIZE];

static void  Test_Task(void *p_arg);
static void  Test_Idle(void *p_arg);

void TaskCreateAppTask(void);

static void Test_Task(void *p_arg)
{
	(void)p_arg;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Bsp_Init();
	TaskCreateAppTask();
	
	while(1) 
	{
      Led_On();
      OSTimeDlyHMSM(0,0,1,0);
		  Led_Off();
      OSTimeDlyHMSM(0,0,1,0);
	}
}

static void Test_Idle(void *p_arg)
{
	(void)p_arg;

	while(1) 
	{
     OSTimeDlyHMSM(0,0,1,0);
	}
}

void TaskCreateAppTask(void)
{
   INT8U  err;

	 OSTaskCreateExt(Test_Idle,
								 (void *)0,
								 (OS_STK *)&Test_Idle_STK[TEST_Idle_STK_SIZE-1],
								 OSTASK_Idle_PRIO,
								 OSTASK_Idle_PRIO,
								 (OS_STK *)&Test_Idle_STK[0],
								 TEST_Idle_STK_SIZE,
								 (void *)0,
								 OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
	 OSTaskNameSet(OSTASK_TEST_PRIO,(INT8U *)"Idle",&err);
}

void TaskCreate(void)
{
	 INT8U  err;

   OSTaskCreateExt(Test_Task,
							 (void *)0,
							 (OS_STK *)&Test_Task_STK[TEST_TASK_STK_SIZE-1],
							 OSTASK_TEST_PRIO,
							 OSTASK_TEST_PRIO,
							 (OS_STK *)&Test_Task_STK[0],
							 TEST_TASK_STK_SIZE,
							 (void *)0,
							 OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
		OSTaskNameSet(OSTASK_TEST_PRIO, (INT8U *)"TEST", &err);

}


int main(){

	OSInit();
	/* Create the start task */
	TaskCreate();
	OSStart();
	
	return 0;
}



