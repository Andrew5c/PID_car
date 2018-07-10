#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include "stm32f10x.h"

//红外遥控 红外接收器数据线,外部中断 PC6
#define IRIN_PIN         GPIO_Pin_6
#define IRIN_GPIO        GPIOC
#define IRIN_CLK         RCC_APB2Periph_GPIOC
#define IRIN_PORTSOURCE  GPIO_PortSourceGPIOC
#define IRIN_PINSOURCE   GPIO_PinSource6
#define IRIN_EXITLINE    EXTI_Line6
#define IRIN_IRQCH       EXTI9_5_IRQn
#define IRIN             GPIO_ReadInputDataBit(IRIN_GPIO, IRIN_PIN)


//超声波控制 外部中断返回 PA8
#define Echo_PIN         GPIO_Pin_8
#define Echo_GPIO        GPIOA
#define Echo_CLK         RCC_APB2Periph_GPIOA
#define Echo_PORTSOURCE  GPIO_PortSourceGPIOA
#define Echo_PINSOURCE   GPIO_PinSource8
#define Echo_EXITLINE    EXTI_Line8
#define Echo_IRQCH       EXTI15_10_IRQn
#define Echo             GPIO_ReadInputDataBit(Echo_GPIO, Echo_PIN)
//触发IO PC7
#define Trig_PIN         GPIO_Pin_7
#define Trig_GPIO        GPIOC
#define Trig_CLK         RCC_APB2Periph_GPIOC
#define Trig_RESET       GPIO_SetBits(Trig_GPIO , Trig_PIN)
#define Trig_SET         GPIO_ResetBits(Trig_GPIO , Trig_PIN)//5转3.3做了一次反相 modfied by LC 2015.09.20 10:18


//舵机控制IO PC8
#define Servo_PIN         GPIO_Pin_8
#define Servo_GPIO        GPIOC
#define Servo_CLK         RCC_APB2Periph_GPIOC
#define Servo_SET         GPIO_SetBits(Servo_GPIO , Servo_PIN)
#define Servo_RESET       GPIO_ResetBits(Servo_GPIO , Servo_PIN)


//LCD1602
#define LCDCS_PIN         GPIO_Pin_10
#define LCDCS_GPIO        GPIOC
#define LCDCS_CLK         RCC_APB2Periph_GPIOC
#define LCDCS_SET         GPIO_SetBits(LCDCS_GPIO , LCDCS_PIN)
#define LCDCS_RESET       GPIO_ResetBits(LCDCS_GPIO , LCDCS_PIN)

#define LCDRST_PIN         GPIO_Pin_12
#define LCDRST_GPIO        GPIOC
#define LCDRST_CLK         RCC_APB2Periph_GPIOC
#define LCDRST_SET         GPIO_SetBits(LCDRST_GPIO , LCDRST_PIN)
#define LCDRST_RESET       GPIO_ResetBits(LCDRST_GPIO , LCDRST_PIN)

#define LCDRS_PIN         GPIO_Pin_1
#define LCDRS_GPIO        GPIOD
#define LCDRS_CLK         RCC_APB2Periph_GPIOD
#define LCDRS_SET         GPIO_SetBits(LCDRS_GPIO , LCDRS_PIN)
#define LCDRS_RESET       GPIO_ResetBits(LCDRS_GPIO , LCDRS_PIN)

#define LCDSCL_PIN         GPIO_Pin_3
#define LCDSCL_GPIO        GPIOD
#define LCDSCL_CLK         RCC_APB2Periph_GPIOD
#define LCDSCL_SET         GPIO_SetBits(LCDSCL_GPIO , LCDSCL_PIN)
#define LCDSCL_RESET       GPIO_ResetBits(LCDSCL_GPIO , LCDSCL_PIN)

#define LCDSID_PIN         GPIO_Pin_5
#define LCDSID_GPIO        GPIOD
#define LCDSID_CLK         RCC_APB2Periph_GPIOD
#define LCDSID_SET         GPIO_SetBits(LCDSID_GPIO , LCDSID_PIN)
#define LCDSID_RESET       GPIO_ResetBits(LCDSID_GPIO , LCDSID_PIN)

//电机驱动IO定义 
#define MOTOR_GPIO        GPIOF
#define MOTOR_CLK         RCC_APB2Periph_GPIOF

#define FRONT_LEFT_F_PIN         GPIO_Pin_0
#define FRONT_LEFT_F_SET         GPIO_SetBits(MOTOR_GPIO , FRONT_LEFT_F_PIN)
#define FRONT_LEFT_F_RESET       GPIO_ResetBits(MOTOR_GPIO , FRONT_LEFT_F_PIN)

#define FRONT_LEFT_B_PIN         GPIO_Pin_1
#define FRONT_LEFT_B_SET         GPIO_SetBits(MOTOR_GPIO , FRONT_LEFT_B_PIN)
#define FRONT_LEFT_B_RESET       GPIO_ResetBits(MOTOR_GPIO , FRONT_LEFT_B_PIN)

#define FRONT_RIGHT_F_PIN         GPIO_Pin_7
#define FRONT_RIGHT_F_SET         GPIO_SetBits(MOTOR_GPIO , FRONT_RIGHT_F_PIN)
#define FRONT_RIGHT_F_RESET       GPIO_ResetBits(MOTOR_GPIO , FRONT_RIGHT_F_PIN)

#define FRONT_RIGHT_B_PIN         GPIO_Pin_6
#define FRONT_RIGHT_B_SET         GPIO_SetBits(MOTOR_GPIO , FRONT_RIGHT_B_PIN)
#define FRONT_RIGHT_B_RESET       GPIO_ResetBits(MOTOR_GPIO , FRONT_RIGHT_B_PIN)

#define BEHIND_LEFT_F_PIN         GPIO_Pin_3
#define BEHIND_LEFT_F_SET         GPIO_SetBits(MOTOR_GPIO , BEHIND_LEFT_F_PIN)
#define BEHIND_LEFT_F_RESET       GPIO_ResetBits(MOTOR_GPIO , BEHIND_LEFT_F_PIN)

#define BEHIND_LEFT_B_PIN         GPIO_Pin_2
#define BEHIND_LEFT_B_SET         GPIO_SetBits(MOTOR_GPIO , BEHIND_LEFT_B_PIN)
#define BEHIND_LEFT_B_RESET       GPIO_ResetBits(MOTOR_GPIO , BEHIND_LEFT_B_PIN)

#define BEHIND_RIGHT_F_PIN         GPIO_Pin_4
#define BEHIND_RIGHT_F_SET         GPIO_SetBits(MOTOR_GPIO , BEHIND_RIGHT_F_PIN)
#define BEHIND_RIGHT_F_RESET       GPIO_ResetBits(MOTOR_GPIO , BEHIND_RIGHT_F_PIN)

#define BEHIND_RIGHT_B_PIN         GPIO_Pin_5
#define BEHIND_RIGHT_B_SET         GPIO_SetBits(MOTOR_GPIO , BEHIND_RIGHT_B_PIN)
#define BEHIND_RIGHT_B_RESET       GPIO_ResetBits(MOTOR_GPIO , BEHIND_RIGHT_B_PIN)

//循迹光电对管
#define SEARCH_M_PIN         GPIO_Pin_4
#define SEARCH_M_GPIO        GPIOE
#define SEARCH_M_CLK         RCC_APB2Periph_GPIOE
#define SEARCH_M_IO          GPIO_ReadInputDataBit(SEARCH_M_GPIO, SEARCH_M_PIN)

#define SEARCH_R_PIN         GPIO_Pin_6
#define SEARCH_R_GPIO        GPIOE
#define SEARCH_R_CLK         RCC_APB2Periph_GPIOE
#define SEARCH_R_IO          GPIO_ReadInputDataBit(SEARCH_R_GPIO, SEARCH_R_PIN)

#define SEARCH_L_PIN         GPIO_Pin_13
#define SEARCH_L_GPIO        GPIOC
#define SEARCH_L_CLK         RCC_APB2Periph_GPIOC
#define SEARCH_L_IO          GPIO_ReadInputDataBit(SEARCH_L_GPIO, SEARCH_L_PIN)
#define BLACK_AREA 1
#define WHITE_AREA 0

//红外避障
#define VOID_R_PIN         GPIO_Pin_2
#define VOID_R_GPIO        GPIOE
#define VOID_R_CLK         RCC_APB2Periph_GPIOE
#define VOID_R_IO          GPIO_ReadInputDataBit(VOID_R_GPIO, VOID_R_PIN)

#define VOID_L_PIN         GPIO_Pin_15
#define VOID_L_GPIO        GPIOC
#define VOID_L_CLK         RCC_APB2Periph_GPIOC
#define VOID_L_IO          GPIO_ReadInputDataBit(VOID_L_GPIO, VOID_L_PIN)
#define BARRIER_Y 0 //有障碍物
#define BARRIER_N 1  //无障碍物

//测速
#define FRONT_RIGHT_S_PIN         GPIO_Pin_5
#define FRONT_RIGHT_S_GPIO        GPIOE
#define FRONT_RIGHT_S_CLK         RCC_APB2Periph_GPIOE
#define FRONT_RIGHT_S_IO          GPIO_ReadInputDataBit(FRONT_RIGHT_S_GPIO, FRONT_RIGHT_S_PIN)

#define FRONT_LEFT_S_PIN         GPIO_Pin_3
#define FRONT_LEFT_S_GPIO        GPIOE
#define FRONT_LEFT_S_CLK         RCC_APB2Periph_GPIOE
#define FRONT_LEFT_S_IO          GPIO_ReadInputDataBit(FRONT_LEFT_S_GPIO, FRONT_LEFT_S_PIN)

//左前
#define FRONT_LEFT_GO    FRONT_LEFT_F_SET; FRONT_LEFT_B_RESET//前进
#define FRONT_LEFT_BACK  FRONT_LEFT_F_RESET; FRONT_LEFT_B_SET//后退
#define FRONT_LEFT_STOP  FRONT_LEFT_F_RESET; FRONT_LEFT_B_RESET//停止

//右前
#define FRONT_RIGHT_GO     FRONT_RIGHT_F_SET;  FRONT_RIGHT_B_RESET
#define FRONT_RIGHT_BACK   FRONT_RIGHT_F_RESET;FRONT_RIGHT_B_SET
#define FRONT_RIGHT_STOP   FRONT_RIGHT_F_RESET;FRONT_RIGHT_B_RESET

//左后
#define BEHIND_LEFT_GO     BEHIND_LEFT_F_SET;BEHIND_LEFT_B_RESET
#define BEHIND_LEFT_BACK   BEHIND_LEFT_F_RESET;BEHIND_LEFT_B_SET
#define BEHIND_LEFT_STOP   BEHIND_LEFT_F_RESET;BEHIND_LEFT_B_RESET

//右后
#define BEHIND_RIGHT_GO    BEHIND_RIGHT_F_SET;BEHIND_RIGHT_B_RESET
#define BEHIND_RIGHT_BACK  BEHIND_RIGHT_F_RESET;BEHIND_RIGHT_B_SET
#define BEHIND_RIGHT_STOP  BEHIND_RIGHT_F_RESET;BEHIND_RIGHT_B_RESET

#define SPEED_DUTY 40//默认占空比 按1ms最小分辨率 周期50ms计算

//指令定义
#define COMM_STOP  'S'//停止
#define COMM_UP    'U'//前进
#define COMM_DOWN  'D'//后退
#define COMM_RIGHT 'R'//右转
#define COMM_LEFT  'L'//左转
#define COMM_ADD   'A'//加速
#define COMM_SUB   'B'//减速


extern unsigned char tick_5ms;//5ms计数器，作为主函数的基本周期
extern unsigned char tick_1ms;//1ms计数器，作为电机的基本计数器
extern unsigned int speed_count;//占空比计数器 50次一周期

void delay_init(void);
void Delayms(u32 Nms);
void Delay_us(u32 Nus);
void LEDToggle(uint16_t Led);

void IRIN_Configuration(void);
void Sound_Configuration(void);
void TIM2_Init(void);
void RedRayInit(void);
void ServoInit(void);
#endif

