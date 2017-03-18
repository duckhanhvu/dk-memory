/*
 * TWI.h
 *
 * Created: 11/22/2015 9:48:32 PM
 *  Author: Duc Khanh
 */ 
 

#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#include <avr/interrupt.h>
//SLAVE receiver mode
#define GENERAL_CALL_ENABLE   1      

#define ADDRESS_SLAVE_RECEIVER_MATCH  0x60
#define MASTER_LOST_SLA_RECEIVER      0x68 
#define SLAVE_RECEIVER_DATA_TRACK     0x80 
#define SLAVE_RECEIVER_DATA_TRNACK    0x88 
#define SLAVE_GENERAL_CALL            0x70 
#define SLAVE_GENERAL_CALL_TRACK      0x90
#define SLAVE_GENERAL_CALL_TRNACK     0x98
#define STOP_CALL_SLAVE               0xA0

//slave transmitter mode
#define ADDRESS_SLAVE_TRANS_MATCH     0xA8
#define MASTER_LOST_SLA_TRANS_MATCH   0xB0
#define SLAVE_TRANS_DATA_REACK        0xB8
#define SLAVE_TRANS_DATA_RENACK       0xC0
#define SLAVE_TRANS_DATA_LAST         0xC8

//master transmitter mode
#define MASTER_GIVE_STA               0x08
#define MASTER_TRANS_SLA_W_REACK      0x18
#define MASTER_TRANS_SLA_W_RENACK     0x20
#define MASTER_TRANS_DATA_REACK       0x28
#define MASTER_TRANS_DATA_RENACK      0x30
#define MASTER_TRANS_Rs               0x10 //Rs:repeat start

//master receiver mode
#define MASTER_TRANS_SLA_R_REACK      0x40
#define MASTER_RECEIVER_DATA_TRACK    0x50
#define MASTER_RECEIVER_DATA_TRNACK   0x58
#define MASTER_TRANS_SLA_R_RENACK     0x48


#define TWI_R   1
#define TWI_W   0
#define TWI_START        (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
#define TWI_STOP         (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)
#define TWI_READ_ACK     (1<<TWINT)|(1<<TWEA)|(1<<TWEN)
#define TWI_CLEAR_TWINT  (1<<TWINT)|(1<<TWEN)

//??a ch? c?a mode slave----------------

volatile uint8_t Device_Addr ;
volatile uint8_t slave_reciver_data[100];
volatile uint8_t slave_trans_data[100];
volatile uint8_t R_byte_num ;
volatile uint8_t Tr_byte_num ;

void Init_TWI(void);
uint8_t MASTER_Trans(uint8_t addr, uint8_t data[], uint8_t lenght);
uint8_t MASTER_Receiver(uint8_t addr, uint8_t data[], uint8_t lenght);


#endif /* TWI_H_ */