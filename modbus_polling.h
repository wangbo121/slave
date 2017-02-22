#ifndef _MODBUS_H_
#define _MODBUS_H_

#include <semaphore.h>

#define DEV_MODBUS "/dev/ttyO1"

#define MODBUS_TIMEOUT_MS 500 //[ms]

//��ŵ������
//�ŵ���������ֵ��1.�л����ŵ�������ѹ: > SWITCHER_DISCHARGE_ENA_VOLTAGE_DFT: ���������ŵ�
//                2.�л���ֹͣ�ŵ��ѹ: < SWITCHER_DISCHARGE_DIS_VOLTAGE_DFT: ֹͣ�ŵ�
//�����������ֵ��1.���������������ĵ�ѹ��ֵ�� < REQ_CHARGE_VOLTAGE: �������
//                2.��������ֹ��ѹ; BATTERY_FULL_VOLTAGE && BATTERY_FULL_CURRENT

//changed 20170119 by fei & jia
#define SWITCHER_DISCHARGE_ENA_VOLTAGE_DFT 127 //[V]
#define SWITCHER_DISCHARGE_DIS_VOLTAGE_DFT 105 //[V]

#define CHARGER_VOLTAGE_MAX 145 //[V]
#define CHARGER_VOLTAGE_MIN 130 //[V]
#define CHARGER_VOLTAGE_DFT 145 //[V]

#define CHARGER_CURRENT_MAX 10 //[A]
#define CHARGER_CURRENT_MIN 1 //[A]
#define CHARGER_CURRENT_DFT 10 //[A]

#define BATTERY_FULL_CURRENT 2//[A]
#define BATTERY_FULL_VOLTAGE 145 //[V]

#define REQ_CHARGE_VOLTAGE 138//127 //[V]


typedef struct tagModbusPara
{
	unsigned char recv_addr;//Ԥ�ڽ��մ�վ��ַ
	unsigned char recv_flag;//Ԥ�ڽ��մ�վ���ݰ���־
	unsigned char spare[2];
	int recv_len;//Ԥ�ڽ��յ����ֽ���������CRCУ��������ֽ�
	int recv_cnt;
	int recv_ok;//���յ���ȷ���ݰ�
	int recv_sm;//����״̬��
	int switcher_error_cnt;
	int charger_error_cnt;
	unsigned char buf[100];
}T_MODBUS_PARA;

typedef struct tagSwitcherState
{
	unsigned char voltage[2];
	unsigned char workstate[2];
}T_SWITCHER_DATA;

typedef struct tagSwitcherConfig
{
	unsigned char voltage_llim;
	unsigned char voltage_hlim;
	unsigned char spare[2];
	//unsigned short config;//?�Ƿ���Ҫ�������ã�
}T_SWITCHER_CFG;

typedef struct tagChargerState
{
	unsigned char voltage[2];
	unsigned char current[2];
	unsigned char workstate[2];
	//unsigned short chargestate[2];
	unsigned char work_chan;
	unsigned char spare;
}T_CHARGER_DATA;

typedef struct tagChargerConfig
{
	unsigned char set_voltage;
	unsigned char set_current;
	unsigned char set_channel;//1 or 2
	unsigned char work_chan;
}T_CHARGER_CFG;

typedef struct tagModbusError
{
	int switcher_error_cnt;
	int charger_error_cnt;
}T_MODBUS_ERROR;

extern T_SWITCHER_DATA switcher_state;
extern T_SWITCHER_CFG switcher_config;
extern T_CHARGER_DATA charger_state;
extern T_CHARGER_CFG charger_config;
extern T_MODBUS_ERROR modbus_error;

extern int modbus_init();
extern sem_t sem_modbus;

#endif//_MODBUS_H_