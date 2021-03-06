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
#include "commu.h"//主副系统通信数据结构及地址

#define DEV_RS485 "/dev/ttyO1"

#define CHARGER_ADDR 0x1
#define SWITCHER_ADDR 0x3

#define _TIMER_INTERVAL 20000 /*[us]*/
#define _200MSEC_CNT (100000/_TIMER_INTERVAL) /*200ms*/
#define _ONESEC_CNT (1000000/_TIMER_INTERVAL)
#define _TWOSEC_CNT (2000000/_TIMER_INTERVAL)
#define _TENSEC_CNT (10000000/_TIMER_INTERVAL)
//#define _BDSEND_CNT (60*_ONESEC_CNT)/*北斗通信每60秒一次*/
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
	unsigned short att_to_rkt;//给火箭的姿态数据允许。=1:给火箭发送姿态数据;=0:停止发送姿态数据
	unsigned short recv_rkt_data;//=1:开始接收火箭探空数据;=0:停止接收。目前无用，只要收到探空数据就保存。
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
extern T_DATETIME datetime_now;//当前的日期和时间，精确到秒。在主线程中每秒更新一次，其它程序直接使用即可。
extern struct tm *gbl_time_val;//全局时间变量，其它的时间都从这里取
extern T_GBL_DATA gblState;
extern T_M2S m2s;
extern T_S2M s2m;
extern char logmsg[300];//日志消息缓冲区

#endif//_GLOBAL_H_
