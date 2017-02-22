#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include<stdio.h>  
#include<sys/types.h>  
#include<sys/stat.h>  
#include<fcntl.h>  
#include<sys/select.h>  
#include<unistd.h>  
#include<signal.h>  
#include<string.h>  
#include<pthread.h> 
#include <semaphore.h>
#include <time.h>
#include "../lib/common.h"
#include "commu.h"//����ϵͳͨ�����ݽṹ����ַ

#define DEV_RS485 "/dev/ttyO1"

#define CHARGER_ADDR 0x1
#define SWITCHER_ADDR 0x3

#define _TIMER_INTERVAL 20000 /*[us]*/
#define _200MSEC_CNT (100000/_TIMER_INTERVAL) /*200ms*/
#define _ONESEC_CNT (1000000/_TIMER_INTERVAL)
#define _TWOSEC_CNT (2000000/_TIMER_INTERVAL)
#define _TENSEC_CNT (10000000/_TIMER_INTERVAL)
//#define _BDSEND_CNT (60*_ONESEC_CNT)/*����ͨ��ÿ60��һ��*/
#define _UDPSEND_PERIOD 100000 //[ms]
#define _UDPSEND_CNT (_UDPSEND_PERIOD/_TIMER_INTERVAL)

typedef struct tagGblState{
	unsigned char switcher_enable;//
	unsigned char charger_enable;
	unsigned char charger_quary_ok;
	unsigned char charger_GCS_stop_charge;//1:stop charge
	//unsigned char charger_work_chan_now;//charging channel, or chaennel charge finished but doesn't begin discharge:0,1,2
	//unsigned char chargering_channel;//the charging channel, can't be switched to.
	unsigned int charge_time;//[2s] from the start of charge
	unsigned short att_to_rkt;//���������̬����������=1:�����������̬����;=0:ֹͣ������̬����
	unsigned short recv_rkt_data;//=1:��ʼ���ջ��̽������;=0:ֹͣ���ա�Ŀǰ���ã�ֻҪ�յ�̽�����ݾͱ��档
}T_GBL_DATA;

typedef struct tagSysRec
{
	T_DATETIME _datatime;
	T_GBL_DATA gblState;
}T_SYS_REC;

typedef struct tagSysConfig
{
	T_GBL_DATA gblState;
}T_SYS_CONFIG;

extern T_SYS_CONFIG sys_config;
extern T_DATETIME datetime_now;//��ǰ�����ں�ʱ�䣬��ȷ���롣�����߳���ÿ�����һ�Σ���������ֱ��ʹ�ü��ɡ�
extern struct tm *gbl_time_val;//ȫ��ʱ�������������ʱ�䶼������ȡ
extern T_GBL_DATA gblState;
extern T_M2S m2s;
extern T_S2M s2m;
extern char logmsg[300];//��־��Ϣ������

#endif//_GLOBAL_H_