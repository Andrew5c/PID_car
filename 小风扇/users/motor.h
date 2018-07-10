
#ifndef MOTOR_H
#define MOTOR_H

//定义电调上面的信号线
sbit MOTOR_PWM = P0^1;

extern volatile unsigned char is_first_time_blow_nature;
extern volatile unsigned char is_first_time_start;

void TIME0_PWM_Init(void);

void fan_start(unsigned char _duty);
//void fan_close(void);
void fan_blow_nature(void);


#endif
