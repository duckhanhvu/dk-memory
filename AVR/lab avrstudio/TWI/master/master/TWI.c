/*
 * TWI.c
 *
 * Created: 11/22/2015 11:42:28 PM
 *  Author: Duc Khanh
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TWI.h"
#include "setandclear_bit.h"


//volatile uint8_t R_byte_num =0;
//volatile uint8_t Tr_byte_num =0;

void Init_TWI(void){
	//initLization for SCL
	TWBR=32;
	TWSR=0x00;
	//-----------------
	
	TWCR=(1<<TWEA)|(1<<TWEN)|(1<<TWIE);
	TWAR=(Device_Addr<<1)+GENERAL_CALL_ENABLE;
}

//code for master-----------------------------------------------------------
//----master transmitter mode--------
uint8_t MASTER_Trans(uint8_t addr, uint8_t data[], uint8_t lenght){
	clearbit(TWCR,TWIE);
	//sent start condition for slave
	TWCR=TWI_START;
	while((TWCR&0x80)==0x00){};
	if((TWSR&0xF8)!=MASTER_GIVE_STA){
		Init_TWI();
		return (TWSR&0xF8);
	}
	//sent device's address
	TWDR=(addr<<1)+TWI_W;
	TWCR=TWI_CLEAR_TWINT;
	while((TWSR&0x80)==0x00){};
	if((TWSR&0xF8)!=MASTER_TRANS_SLA_W_REACK){
		Init_TWI();
		return (TWSR&0xF8);
	}		
	//sent DATA
	for(int i=0;i<lenght;i++){
		TWDR=data[i];
		TWCR=TWI_CLEAR_TWINT;
		while((TWCR&0x80)==0x00){};
		if((TWSR&0xF8)!=MASTER_TRANS_DATA_REACK){
			Init_TWI();
			return (TWSR&0xF8);
		}	
	}
	//sent stop condition
	TWCR=TWI_STOP;
	Init_TWI();
	return 0;
}
//-----master receiver mode-----------
uint8_t MASTER_Receiver(uint8_t addr, uint8_t data[], uint8_t lenght){
	uint8_t status;
	clearbit(TWCR,TWIE);
	//sent start condition
	TWCR=TWI_START;
	while((TWCR&0x80)==0x00){};
	status=TWSR&0xF8;
	if(status!=MASTER_GIVE_STA){
		TWCR=TWI_STOP;
		Init_TWI();
		return status;
	}
	
	//sent device's address
	TWDR=(addr<<1)+TWI_R;
	TWCR=TWI_CLEAR_TWINT;
	while((TWSR&0x80)==0x00){};
	status=TWSR&0xF8;
	if(status!=MASTER_TRANS_SLA_R_REACK){
		TWCR=TWI_STOP;
		Init_TWI();
		return status;
	}
	//receiver bytes data
	for(int i=0;i<lenght;i++){
		TWCR= TWI_READ_ACK;
		while((TWCR&0x80)==0x00){};
		status=TWSR&0xF8;
	    if(status!=MASTER_RECEIVER_DATA_TRACK){
			TWCR=TWI_STOP;
			Init_TWI();
			return status;
		}	
		data[i]=TWDR;
	}
	//receiver last data
	TWCR=TWI_CLEAR_TWINT;
	while((TWSR&0x80)==0x00){};
	status=TWSR&0xF8;
	if(status!=MASTER_RECEIVER_DATA_TRNACK){
		TWCR=TWI_STOP;
		Init_TWI();
		return status;
	}
	data[lenght-1]=TWDR;
	//sent stop condition 
	TWCR=TWI_STOP;
	Init_TWI();
	return 0;
}
//-------------------------------------------------------------------------

//code for slave------------------------------------------------------------
ISR(TWI_vect){
	R_byte_num=0;
	Tr_byte_num=0;
	uint8_t status;
	status=TWSR;
//----------code for slave receiver-------------
    switch(status){
	case ADDRESS_SLAVE_RECEIVER_MATCH :
		R_byte_num=0;
		TWCR|=(1<<TWINT)|(1<<TWEA);
	    break;
		
	case SLAVE_RECEIVER_DATA_TRACK :
		slave_reciver_data[R_byte_num++]=TWDR;
		TWCR|=(1<<TWINT)|(1<<TWEA);
		break;	
	case SLAVE_RECEIVER_DATA_TRNACK :
		slave_reciver_data[R_byte_num++]=TWDR;
		TWCR|=(1<<TWINT)|(1<<TWEA);
	    break;
	case SLAVE_GENERAL_CALL :
	    R_byte_num=0;
		TWCR|=(1<<TWINT)|(1<<TWEA);
	    break;
	case SLAVE_GENERAL_CALL_TRACK :
		slave_reciver_data[R_byte_num++]=TWDR;
		TWCR|=(1<<TWINT)|(1<<TWEA);
	    break;
	case SLAVE_GENERAL_CALL_TRNACK :
		slave_reciver_data[R_byte_num++]=TWDR;
		TWCR|=(1<<TWINT)|(1<<TWEA);
		break;
	case STOP_CALL_SLAVE :
		TWCR|=(1<<TWINT)|(1<<TWEA);
	    break;	
//----------code for slave transmitter----------
    case ADDRESS_SLAVE_TRANS_MATCH :
	    Tr_byte_num++;
		TWDR=slave_trans_data[Tr_byte_num];
		TWCR|=(1<<TWINT)|(1<<TWEA);
	    break;
	case MASTER_LOST_SLA_TRANS_MATCH :
		TWDR=slave_trans_data[Tr_byte_num];
		TWCR|=(1<<TWINT)|(1<<TWEA);
		break;	
	case SLAVE_TRANS_DATA_REACK :
		TWDR=slave_trans_data[Tr_byte_num];
		TWCR|=(1<<TWINT)|(1<<TWEA);
		break;
	case SLAVE_TRANS_DATA_RENACK :
		TWCR|=(1<<TWINT)|(1<<TWEA);
		break;
	case SLAVE_TRANS_DATA_LAST :
		TWDR=slave_trans_data[Tr_byte_num];
		TWCR|=(1<<TWINT)|(1<<TWEA);
	    break;	
	default:
	break;			
}
}