
char Read2Nib();
void write2Nib(unsigned char chr);
void write8bit(unsigned char chr);
void wait_lCD();
void clear_bit();
void init_lCD();
void clr_lCD();
void home_lCD();
void move_lCD(unsigned y, unsigned x);
void putChar_lCD(unsigned chr);
void print_lCD(char *str, unsigned char lenght);


#define EN        PORTA.2
#define RW        PORTA.1
#define RS        PORTA.0
#define DATA_I    PINA
#define DATA_O    PORTA
#define DDR_DATA  DDRA
#define CTRl      PORTA

void write2Nib(unsigned char chr){
  unsigned char HNib,lNib;
   HNib = chr&0xF0;
   lNib = (chr<<4)&0xF0;
  
  unsigned x;
   x = DATA_O&0x0F;
  
   DATA_O=(HNib|x);
   EN=1;
   EN=0;
   
   DATA_O = (lNib|x);
   EN=1;
   EN=0;
   }
char Read2Nib(void){
  unsigned char HNib, lNib
   EN=1;
   DDR_DATA = 0xFF;
   HNib = DATA_I&0xF0;
   EN=0;
   
   EN=1;
   lNib = DATA_I&0xF0;
   EN=0;
   lNib=lNib>>4;
   
   return (HNib|lNib);
   }
void wait_lCD(void){
  while(1){
   RS=0;
   RW=1;
   unsigned char temp;
   temp = Read2Nib();
   if(clear_bit(temp,7)) break; 
  } 
   RW=;
   DDR_DATA = 0xFF;
}
void init_lCD(){
  RS=0;
  RW=0;
//function set  
  DDR_DATA = 0xF0;
  EN=0;
  EN=1;
  clear_bit(CTRl,4);
  write2Nib(0x58);
  wait_lCD();
  
//display control
  write2Nib(0x0E);
  wait_lCD();
//entry mode set
  write2Nib(0x06);
  wait_lCD();  
}
void clr_lCD(void){
  RS=0;
  RW=0;
  write2Nib(0x01);
  wait_lCD(); 
}
void home_lCD(void){
  RS=0;
  RW=1;
  write2Nib(0x02);
  wait_lCD();
}
void move_lCD(unsigned int y, unsigned int x){//y dong, x cot
  unsigned int temp;
  temp = 64*(y-1)+ (x-1)+ 0x80;
  RS=0;
  RW=0;
  write2Nib(temp);
  wait_lCD();
}
void putChar_lCD(unsigned char chr){
  RS=1;
  RW=0;
  write2Nib(char);
  wait_lCD();
}
void print_lCD(char *str, unsigned char lenght){
  int i;
  for(i=0;i<lenght;i++){
   if(str[i]>0) putChar_lCD(str[i]);
   else putChar_lCD(' ');
  }
}
     
   
   
   
  
