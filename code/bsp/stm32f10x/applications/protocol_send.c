#include <rthw.h>
#include "rs485_decode.h"
#include "includes.h"
#include <string.h>

#define target_id domeNo

extern rt_sem_t	uart1_sem;

rt_err_t rs485_recieve_check(u8 val)
{

	
	if(rt_sem_take(uart1_sem, 30) == RT_EOK)
    {
		if (command_analysis()) 
		{
            switch(command_byte)
		    {
			 	case 0x11://call preset point

					if(Rocket_fir_data == val)
						return RT_EOK;
					break;

             	default:
				break;
	   	    }

		}
	}
	return RT_ERROR;

}


u8 cmd_buff[7];

rt_sem_t rs485_return_sem;

extern rt_err_t rs485_send_data(u8* data,u16 len);

void pelcod_call_pre_packet_send(u8 val)
{
	u8 cnt;
	cmd_buff[0] = 0xff;
	cmd_buff[1] = target_id;
	cmd_buff[2] = 0;
	cmd_buff[3] = 0x07;
	cmd_buff[4] = 0;
	cmd_buff[5] = val;
	
	cmd_buff[6] = cmd_buff[1] + cmd_buff[2] + cmd_buff[3] + cmd_buff[4] + cmd_buff[5];
	rs485_send_data(cmd_buff,7);

//	cnt=3;
//	while(cnt--)
//	{
//		if(RT_EOK == rs485_recieve_check(val))
//			break;
//		else
//			rs485_send_data(cmd_buff,7);
//	}
}


void pelcod_set_pre_packet_send(u8 val)
{
	u8 cnt;
	cmd_buff[0] = 0xff;
	cmd_buff[1] = target_id;
	cmd_buff[2] = 0;
	cmd_buff[3] = 0x03;
	cmd_buff[4] = 0;
	cmd_buff[5] = val;
	
	cmd_buff[6] = cmd_buff[1] + cmd_buff[2] + cmd_buff[3] + cmd_buff[4] + cmd_buff[5];
	rs485_send_data(cmd_buff,7);
}

void pelcod_set_pre_extend_packet_send(u8 val,u8 cmd)
{
	u8 cnt;
	cmd_buff[0] = 0xff;
	cmd_buff[1] = target_id;
	cmd_buff[2] = 0xff;
	cmd_buff[3] = cmd;
	cmd_buff[4] = val;
	cmd_buff[5] = 0;
	
	cmd_buff[6] = cmd_buff[1] + cmd_buff[2] + cmd_buff[3] + cmd_buff[4] + cmd_buff[5];
	rs485_send_data(cmd_buff,7);
}


//val: 0,open; 1,close
void pelcod_open_close_packet_send(u8 val)
{
	u8 cnt;
	cmd_buff[0] = 0xff;
	cmd_buff[1] = target_id;
	if(val)//close
		cmd_buff[2] = 0x04;
	else
		cmd_buff[2] = 0x02;
	cmd_buff[3] = 0;
	cmd_buff[4] = 0;
	cmd_buff[5] = 0;
	
	cmd_buff[6] = cmd_buff[1] + cmd_buff[2] + cmd_buff[3] + cmd_buff[4] + cmd_buff[5];
	rs485_send_data(cmd_buff,7);

//	cnt=3;
//	while(cnt--)
//	{
//		if(RT_EOK == rs485_recieve_check(val))
//			break;
//		else
//			rs485_send_data(cmd_buff,7);
//	}
}

void pelcod_lrud_pre_packet_send(u8 lrudcmd,u8 lrspeed,u8 udspeed)
{
	u8 cnt;
	cmd_buff[0] = 0xff;
	cmd_buff[1] = target_id;
	cmd_buff[2] = 0;
	cmd_buff[3] = lrudcmd;
	cmd_buff[4] = lrspeed;
	cmd_buff[5] = udspeed;
	
	cmd_buff[6] = cmd_buff[1] + cmd_buff[2] + cmd_buff[3] + cmd_buff[4] + cmd_buff[5];
	rs485_send_data(cmd_buff,7);
}

//cmd,0,stop; 1,tele,2wide; 3,far,4,near
void pelcod_zf_packet_send(u8 cmd,u8 zfspeed)
{
	u8 cnt;
	cmd_buff[0] = 0xff;
	cmd_buff[1] = target_id;

	switch(cmd)
	{
	case 1:
		cmd_buff[3] = 0x20;
		cmd_buff[2] = 0;
		break;
	case 2:
		cmd_buff[3] = 0x40;
		cmd_buff[2] = 0;
		break;
	case 3:
		cmd_buff[3] = 0x00;
		cmd_buff[2] = 0x10;
		break;
	case 4:
		cmd_buff[3] = 0x80;
		cmd_buff[2] = 0;
		break;
	case 0:
		cmd_buff[3] = 0x00;
		cmd_buff[2] = 0;
		break;
	}
	
	cmd_buff[4] = 0;
	cmd_buff[5] = 0;
	
	cmd_buff[6] = cmd_buff[1] + cmd_buff[2] + cmd_buff[3] + cmd_buff[4] + cmd_buff[5];
	rs485_send_data(cmd_buff,7);
}

void pelcod_stop_packet_send(void)
{
	u8 cnt;
	cmd_buff[0] = 0xff;
	cmd_buff[1] = target_id;
		cmd_buff[2] = 0;
	cmd_buff[3] = 0;
	cmd_buff[4] = 0;
	cmd_buff[5] = 0;
	
	cmd_buff[6] = cmd_buff[1] + cmd_buff[2] + cmd_buff[3] + cmd_buff[4] + cmd_buff[5];
	rs485_send_data(cmd_buff,7);
}




