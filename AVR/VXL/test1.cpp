#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <fstream>
#include "mylib.h"
#define B 26
#define MAX 100
using namespace std; 
struct Mean{
       char nghia[MAX];
       char vidu[MAX];
       };
struct node{
       Mean mean;
       struct node *left,*right;
       };
       typedef struct node *ptr;
struct NODE{
       ptr dau;
       ptr cuoi;
       };
       typedef struct NODE PTR;
struct Word{
       char tu[MAX];
       char loaitu[MAX];
       char dongnghia[MAX];
       PTR w;
       };
struct mang{
       Word myword;
       struct mang *next,*prev;
       };
       typedef struct mang*nodeptr;
struct MANG{
       nodeptr first;
       nodeptr last;
       };
       typedef struct MANG NODEPTR;
       NODEPTR myList[B];
struct TuNghia{
       char tu[30];
       char loaitu[30];
       char dongnghia[30];
       char nghia1[30];
       char vidu1[30];
       char nghia2[30];
       char vidu2[30];
       char nghia3[30];
       char vidu3[30];
       };
void initialize(){   
     for (int i=0;i<B;i++){
        myList[i].first=NULL;
         }
         }
int hashtable(Word word){
    if(word.tu[0]>'z'||word.tu[0]<'a')
        return -1;
    else return (tolower(word.tu[0])-97);   
    }
nodeptr search_word(Word word){
        int n=hashtable(word);
        nodeptr p=myList[n].first;
        while(p!=NULL){
           if(strcmp(word.tu,p->myword.tu)==0)
              return p;
           p=p->next;
              }
        return NULL;
        }
void init(PTR &p){
     p.dau=NULL;
     }
void init2(char xau[][MAX]){
     for(int i=0;i<6;i++)
        strcpy(xau[i]," ");
        } 
char ktkytu(char c)
{
	char c1;
	if(c==0) c1=getch();
	else c1=c;
	return c1;
}
void themcuoi1nghia(PTR &p,char xau1[],char xau2[]){
     ptr q=new node;
     //ptr q=(ptr)malloc(sizeof(struct node));
     strcpy(q->mean.nghia,xau1);
     strcpy(q->mean.vidu,xau2);
     if(p.dau==NULL){
        q->left=NULL;
        p.dau=q;
        }
     else{
        q->left=p.cuoi;
        p.cuoi->right=q;
        }
        p.cuoi=q;
        q->right=NULL;
        }    
void addword(Word word,nodeptr &First,nodeptr &Last){
     int n=hashtable(word);
     nodeptr p=new mang;
     strcpy(p->myword.dongnghia,word.dongnghia);
     strcpy(p->myword.loaitu,word.loaitu);
     strcpy(p->myword.tu,word.tu);
     p->myword.w=word.w;
     if(First==NULL){
        p->next=NULL;
        Last=p;
        }
     else{
          p->next=First;
          First->prev=p;
          }
     First=p;
     p->prev=NULL;
     }     
void sap_xep(NODEPTR &myList){
  nodeptr p,q,pmin;
  Word word;
       for(p=myList.first;p->next!=NULL;p=p->next){
             strcpy(word.tu,p->myword.tu);
             pmin=p;
             PTR b;
            for(q=p->next;q!=NULL;q=q->next)
              if(strcmp(q->myword.tu,word.tu)<0)
              { 
                strcpy(word.tu," ");
                strcpy(word.tu,q->myword.tu);
                strcpy(word.dongnghia,q->myword.dongnghia);
                strcpy(word.loaitu,q->myword.loaitu);
                b=q->myword.w;
                pmin=q;
                strcpy(pmin->myword.tu,p->myword.tu);
                strcpy(pmin->myword.dongnghia,p->myword.dongnghia);
                strcpy(pmin->myword.loaitu,p->myword.loaitu);
                pmin->myword.w=p->myword.w;
                strcpy(p->myword.tu,word.tu);
                strcpy(p->myword.dongnghia,word.dongnghia);
                strcpy(p->myword.loaitu,word.loaitu);
                p->myword.w=b;
                }
                }
                }
int do_tim(int n,char xau[]){
     nodeptr p;
     for (p=myList[n].first;p!=NULL;p=p->next){
         if(strcmp(p->myword.tu,xau)==0)
            return 1;
            break;
            }
          return 0;
          }  
         
void load_file(){
     TuNghia tn;
     Word word;
     int n=0;
     char xau[6][MAX];
     //ifstream filein("anh.txt",ios::in|ios::binary);
     FILE *f=fopen("anh.txt","r");
     /*
     if(!filein){
      cout<<"\n Khong the mo duoc tep tin \n";
      exit(1);
      }*/
      while(!feof(f)){
      fread(&tn,sizeof(tn),1,f);
       init2(xau);
       strcpy(word.tu,tn.tu);
       strcpy(word.loaitu,tn.loaitu);
       strcpy(word.dongnghia,tn.dongnghia);
       strcpy(xau[0],tn.nghia1);
       strcpy(xau[1],tn.vidu1);
       strcpy(xau[2],tn.nghia2);
       strcpy(xau[3],tn.vidu2);
       strcpy(xau[4],tn.nghia3);
       strcpy(xau[5],tn.vidu3);
       init(word.w);
       themcuoi1nghia(word.w,xau[0],xau[1]);
       themcuoi1nghia(word.w,xau[2],xau[3]);
       themcuoi1nghia(word.w,xau[4],xau[5]);
        n=hashtable(word);
       if(do_tim(n,word.tu)==0){
         addword(word,myList[n].first,myList[n].last);
         sap_xep(myList[n]);
       }
         }
         //filein.close();
         }
void save_file(){
     TuNghia tn;
     //ofstream fileout("anh.txt",ios::out|ios::binary);
     FILE *f=fopen("anh.txt","w");
     /*
     if(!fileout){
                  cout<<"\n Khong the tao duoc tep tin \n";
                  exit(1);
                  }*/
          fflush(stdin);
          for(int i=0;i<B;i++){
                  nodeptr p=myList[i].first;
                  while(p!=NULL){
                   strcpy(tn.tu,p->myword.tu);
                   strcpy(tn.loaitu,p->myword.loaitu);
                   strcpy(tn.dongnghia,p->myword.dongnghia);
                   ptr q=p->myword.w.dau;
                   if(q!=NULL){
                         strcpy(tn.nghia1,q->mean.nghia);
                         strcpy(tn.vidu1,q->mean.vidu);
                         q=q->right;
                         }
                   if(q!=NULL){
                         strcpy(tn.nghia2,q->mean.nghia);
                         strcpy(tn.vidu2,q->mean.vidu);
                         q=q->right;
                         }
                   if(q!=NULL){
                         strcpy(tn.nghia3,q->mean.nghia);
                         strcpy(tn.vidu3,q->mean.vidu);
                         q=q->right;
                         }
                   fwrite(&tn,sizeof(tn),1,f);
                         p=p->next;
                   }
                   }
                //fileout.close();
                }
void clear(){ 
	for(int i = 0;i<9;i++){
		gotoxy(30,2+i);
		cout<<"                                ";
	}
	gotoxy(30,2);
}
int check(int a, int b)
{
	if(a==224&&b==80)
			return 1;
	if(a==224&&b==72)
			return -1;
	return 0;
} 
int check1(int a, int b)
{
	if(a==224&&b==77)
			return 1;
	if(a==224&&b==75)
			return -1;
	return 0;
}         
void design()
{

    // while(1){
    char a=5;
    char b=6;
     for(int i=1;i<79;i++){
          if(i%2==0){
          textcolor(1);
          gotoxy(i,1);
          cout<<a;
          //sleep(100);
          }
          else{
          textcolor(04);
          gotoxy(i,1);
          cout<<b;
         // sleep(100);
          }
          }
     for(int i=1;i<20;i++){
          if(i%2==0){
          textcolor(1);
          gotoxy(78,i);
          cout<<a;
          //sleep(100);
          }
          else{
          textcolor(04);
          gotoxy(78,i);
          cout<<b;
          //sleep(100);
          }
          }
     for(int i=78;i>=1;i--){
          if(i%2==0){
          textcolor(1);
          gotoxy(i,20);
          cout<<a;
          //sleep(100);
          }
          else{
          textcolor(04);
          gotoxy(i,20);
          cout<<b;
          //sleep(100);
          }
          }   
     for(int i=20;i>=1;i--)
     {
        if(i%2==0){
         textcolor(1);
         gotoxy(1,i);
         cout<<a;
         //sleep(100);
         }
         else {
         textcolor(04);
         gotoxy(1,i);
         cout<<b;
         //sleep(100);
         }
         }
    
      
          // }   
          }                  
void nhap_tu(NODEPTR &mylist){
      design();
      gotoxy(5,16);
      textcolor(15);
cout<<"ENTER  :  KET THUC QUA TRINH NHAP";
gotoxy(47,16);
cout<<"ESC  :   THOAT CHUC NANG NHAP";
      int x[]={30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65};
      char tu[MAX];
      char loaitu[MAX];
      char dongnghia[MAX];
      char xau[6][MAX];
      char ch,c;
      Word word;
      int index=0,y=2,i1=0,i2=0,i3=0,i4=0,i5=0,i6=0,i7=0,i8=0,i9=0;
      int             j1=1,j2=1,j3=1,j4=1,j5=1,j6=1,j7=1,j8=1,j9=1;
      init2(xau);
      gotoxy(10,2);
      textcolor(15);
      cout<<"Nhap tu : ";
      gotoxy(10,3);
      cout<<"Nhap loai tu : ";
      gotoxy(10,4);
      cout<<"Nhap dong nghia : ";
      gotoxy(10,5);
      cout<<"Nhap nghia 1 : ";
      gotoxy(10,6);
      cout<<"Nhap vi du 1 : ";
      gotoxy(10,7);
      cout<<"Nhap nghia 2 : ";
      gotoxy(10,8);
      cout<<"Nhap vi du 2: ";
      gotoxy(10,9);
      cout<<"Nhap nghia 3 : ";
      gotoxy(10,10);
      cout<<"Nhap vi du 3 : ";
      //design();
      gotoxy(31,2);
      textcolor(14);
      while(1){
nhaptu:
       ch=getch();
       if(ch==72)
         {
         if(index<=0){
         index=8;          
         gotoxy(31,10);
         }
         else {
         index--;
         gotoxy(31,y+index);
         }
         j1=1, j2=1, j3=1, j4=1, j5=1, j6=1, j7=1, j8=1, j9=1;
         }
       else if(ch==80||ch==9)
        {
        if(index>=8){
        index=0;
        gotoxy(31,2);
        }
        else{
        index++;
        gotoxy(31,y+index);
        }
        j1=1, j2=1, j3=1, j4=1, j5=1, j6=1, j7=1, j8=1, j9=1;
        }
        else if(ch==27){
        return;
        }
        else if(ch==8){
           switch(index){
                 if(i1>0){
                      case 0:
                           i1--;
                           tu[i1]='\0';
                           gotoxy(31,2);
                           cout<<"                                ";
                           gotoxy(31,2);
                           cout<<tu;
                          break;
                         }
                  if(i2>0){
                      case 1:
                           i2--;
                           loaitu[i2]='\0';
                           gotoxy(31,3);
                           cout<<"                                ";
                           gotoxy(31,3);
                           cout<<loaitu;
                           break;
                           }
                  if(i3>0){
                      case 2:
                           i3--;
                           dongnghia[i3]='\0';
                           gotoxy(31,4);
                           cout<<"                                ";
                           gotoxy(31,4);
                           cout<<dongnghia;
                           break;
                           }
                  if(i4>0){
                      case 3:
                           i4--;
                           xau[0][i4]='\0';
                           gotoxy(31,5);
                           cout<<"                                ";
                           gotoxy(31,5);
                           cout<<xau[0];
                           break;
                           }
                  if(i5>0){
                      case 4:
                           i5--;
                           xau[1][i5]='\0';
                           gotoxy(31,6);
                           cout<<"                                ";
                           gotoxy(31,6);
                           cout<<xau[1];
                           break;
                           }
                  if(i6>0){
                      case 5:
                           i6--;
                           xau[2][i6]='\0';
                           gotoxy(31,7);
                           cout<<"                                ";
                           gotoxy(31,7);
                           cout<<xau[2];
                           break;
                           }
                  if(i7>0){
                      case 6:
                           i7--;
                           xau[3][i7]='\0';
                           gotoxy(31,8);
                           cout<<"                                ";
                           gotoxy(31,8);
                           cout<<xau[3];
                           break;
                           }
                  if(i8>0){
                      case 7:
                           i8--;
                           xau[4][i8]='\0';
                           gotoxy(31,9);
                           cout<<"                                ";
                           gotoxy(31,9);
                           cout<<xau[4];
                           break;
                           }
                  if(i9>0){
                      case 8:
                           i9--;
                           xau[5][i9]='\0';
                           gotoxy(31,10);
                           cout<<"                                 ";
                           gotoxy(31,10);
                           cout<<xau[5];
                           break;
                           }
                           }
                           }
        else 
           if(ch==77)
           {  switch(index){
                 case 0:
                      if(j1==i1+1) j1=0;
                      j1++;
                      gotoxy(x[j1],y+index);
                      break;
                 case 1:
                      if(j2==i2+1) j2=0;
                      j2++;
                      gotoxy(x[j2],y+index);
                      break;
                 case 2:
                      if(j3==i3+1) j3=0;
                      j3++;
                      gotoxy(x[j3],y+index);
                      break;
                 case 3:
                      if(j4==i4+1) j4=0;
                      j4++;
                      gotoxy(x[j4],y+index);
                      break;
                 case 4:
                      if(j5==i5+1) j5=0;
                      j5++;
                      gotoxy(x[j5],y+index);
                      break;
                 case 5:
                      if(j6==i6+1) j6=0;
                      j6++;
                      gotoxy(x[j6],y+index);
                      break;
                 case 6:
                      if(j7==i7+1) j7=0;
                      j7++;
                      gotoxy(x[j7],y+index);
                      break;
                 case 7:
                      if(j8==i8+1) j8=0;
                      j8++;
                      gotoxy(x[j8],y+index);
                      break;
                 case 8:
                      if(j9==i9+1) j9=0;
                      j9++;
                      gotoxy(x[j9],y+index);
                      break;
                      }
                           }
           else if(ch==75)
           {  switch(index){
                 case 0:
                      if(j1==1) j1=i1+1;
                      j1--;
                      gotoxy(x[j1],y+index);
                      break;
                 case 1:
                      if(j2==1) j2=i2+1;
                      j2--;
                      gotoxy(x[j2],y+index);
                      break;
                 case 2:
                      if(j3==1) j3=i3+1;
                      j3--;
                      gotoxy(x[j3],y+index);
                      break;
                 case 3:
                      if(j4==1) j4=i4+1;
                      j4--;
                      gotoxy(x[j4],y+index);
                      break;
                 case 4:
                      if(j5==1) j5=i5+1;
                      j5--;
                      gotoxy(x[j5],y+index);
                      break;
                 case 5:
                      if(j6==1) j6=i6+1;
                      j6--;
                      gotoxy(x[j6],y+index);
                      break;
                 case 6:
                      if(j7==1) j7=i7+1;
                      j7--;
                      gotoxy(x[j7],y+index);
                      break;
                 case 7:
                      if(j8==1) j8=i8+1;
                      j8--;
                      gotoxy(x[j8],y+index);
                      break;
                 case 8:
                      if(j9==1) j9=i9+1;
                      j9--;
                      gotoxy(x[j9],y+index);
                      break;
                      }
                           }      
                           
        else
          if(isalpha(ch)||ch==32)
          {
             switch(index){
                   case 0:
                        tu[i1++]=ch;  //gan bang chuoi ky tu nhap vao
                        tu[i1]='\0';
                        gotoxy(x[i1],y+index);
                        cout<<ch;  
                        break;
                   case 1:
                        loaitu[i2++]=ch;
                        loaitu[i2]='\0';
                        gotoxy(x[i2],y+index);
                        cout<<ch; 
                        break;
                   case 2:
                        dongnghia[i3++]=ch;
                        dongnghia[i3]='\0';
                        gotoxy(x[i3],y+index);
                        cout<<ch; 
                        break;
                   case 3:
                        xau[0][i4++]=ch;
                        xau[0][i4]='\0';
                        gotoxy(x[i4],y+index);
                        cout<<ch; 
                        break;
                   case 4:
                        xau[1][i5++]=ch;
                        xau[1][i5]='\0';
                        gotoxy(x[i5],y+index);
                        cout<<ch; 
                        break;
                   case 5:
                        xau[2][i6++]=ch;
                        xau[2][i6]='\0';
                        gotoxy(x[i6],y+index);
                        cout<<ch; 
                        break;
                   case 6:
                        xau[3][i7++]=ch;
                        xau[3][i7]='\0';
                        gotoxy(x[i7],y+index);
                        cout<<ch; 
                        break;
                   case 7:
                        xau[4][i8++]=ch;
                        xau[4][i8]='\0';
                        gotoxy(x[i8],y+index);
                        cout<<ch; 
                        break;
                   case 8:
                        xau[5][i9++]=ch;
                        xau[5][i9]='\0';
                        gotoxy(x[i9],y+index);
                        cout<<ch; 
                        break;
                        }
                        //cout<<ch;
                        }
        else if(ch==13){
             if (i1==0)
             {
                gotoxy(35,12);
                cout<<"BAN NHAP THIEU DU LIEU";
                sleep(1000);
                gotoxy(35,12);
                cout<<"                      ";
                gotoxy(31,2);
                index=0;
                goto nhaptu;
                }
             else if(i2==0)
             {
                  gotoxy(35,12);
                  cout<<"BAN NHAP THIEU DU LIEU";
                  sleep(1000);
                  gotoxy(35,12);
                  cout<<"                      ";
                  gotoxy(31,3);
                  index=1;
                  goto nhaptu;
                  }
             else if(i4==0)
                     {
                        gotoxy(35,12);
                        cout<<"BAN NHAP THIEU DU LIEU";
                        sleep(1000);
                        gotoxy(35,12);
                        cout<<"                      ";
                        gotoxy(31,5);
                        index=3;
                        goto nhaptu;
                               }
             else if(i3==0)
             {
                  strcpy(dongnghia," ");
                  }   
             i1=0,i2=0,i3=0,i4=0,i5=0,i6=0,i7=0,i8=0,i9=0;
             strcpy(word.tu,tu);
             strcpy(word.loaitu,loaitu);
             strcpy(word.dongnghia,dongnghia);
             init(word.w);
                     themcuoi1nghia(word.w,xau[0],xau[1]);
                     themcuoi1nghia(word.w,xau[2],xau[3]);
                     themcuoi1nghia(word.w,xau[4],xau[5]);
             init2(xau);
              bool flag=false;
              nodeptr p=search_word(word);
              int n=hashtable(word);
              if(p!=NULL) flag=true;
              if(!flag){          
              addword(word,myList[n].first,myList[n].last);
              sap_xep(myList[n]);
              gotoxy(30,12);
              cout<<"Nhap tu thanh cong!";
              sleep(2000);
              clear();
              //i=0;
              index=0;
              if(ch==27) goto nhaptu;
              gotoxy(30,12);
              cout<<"                   ";
              gotoxy(30,2);
                      }
              else {
              gotoxy(20,12);
              cout<<"Tu nay da co trong tu dien,ban vui long nhap tu khac!";
              sleep(2000);
              clear();
              //i=0;
              index=0;
              if(ch==27)  goto nhaptu;
              gotoxy(20,12);
              cout<<"                                                       ";
              gotoxy(30,2); 
                                 }
                //i=0;
                index=0;   
                        }                                          
                        }
                        }
void Delete_first(nodeptr &First)
   {
     nodeptr p;
     if(First==NULL)
       return;
      else
      {
          p=First;
          if(First->next==NULL)
               First=NULL;
          else
          {
              First=p->next;
              First->prev=NULL;
          }
         free(p);
         }
         }
void Delete_last(nodeptr &Last)
   {
     nodeptr p;
     if(Last==NULL)
       return;
      else
      {
          p=Last;
          if(Last->prev==NULL)
               Last=NULL;
          else
          {
              Last=p->prev;
              Last->next=NULL;
          }
         free(p);
         }
         }
void Delete_node(nodeptr &First,nodeptr &Last,nodeptr p)
{
     nodeptr q,r;
     if(p==NULL)
       return;
     else
     {
         if(First==NULL)
         return;
         else
         {
             if(p==First)
               Delete_first(First);
             else if(p==Last)
               Delete_last(Last);  
            else
            {
                q=p->prev;
                r=p->next;
                r->prev=q;
                q->next=r;
                free(p);
                }
                }
                }
                }
void xoa_nghia(ptr &First){
     ptr p;
     if(First==NULL)
        return;
     else
     {
         p=First;
         if(First->left==NULL)
            First=NULL;
         else
         {
             First=p->right;
             First->left=NULL;
             }
             free(p);
             }
             }
void clear1(){
     for(int i=11;i<=18;i++){
             gotoxy(25,i);
             cout<<"                                           ";
             }
             }
             /*
char  ktkytu(char c){
      char c1;
	if(c==0) c1=getch();
	else c1=c;
	return c1;
}
*/
void xoa_tu()
{
      design();
      gotoxy(5,14);
     Word word;
     char ch,xau[100]=" ";
     int k=0,a,c1;
     gotoxy(10,5);
     textcolor(6);
     cout<<"Nhap tu can xoa : ";
     textcolor(15);
     gotoxy(27,5); 
   while(1){
xoatu:
      ch=getch();
      if(isalpha(ch)&&ch!=80&&ch!=72&&ch!=75&&ch!=77)
      {
         xau[k++]=ch;
         xau[k]='\0';
         gotoxy(27,5);
         cout<<xau;
         }
      if(ch==8){
        if(k>0){
          xau[k--];
          xau[k]='\0';
          gotoxy(27,5);
          cout<<"                                ";
          gotoxy(27,5);
          cout<<xau;
          }
          }
      if(ch==32){
         xau[k++]=ch;
         xau[k]='\0';
         gotoxy(27,5);
         cout<<xau;
         }
      if(ch==13){
          strcpy(word.tu,xau);
          int n=hashtable(word);
          nodeptr p=search_word(word);
          if(n!=-1&&p!=NULL){
            gotoxy(33,10);
            cout<<"Ban muon xoa: "<<p->myword.tu;
            gotoxy(25,11);
            cout<<"Loai tu : "<<p->myword.loaitu;
            gotoxy(25,12);
            cout<<"Dong nghia : "<<p->myword.dongnghia;
            ptr q=p->myword.w.dau;
            if(q!=NULL){
            gotoxy(25,13);
            cout<<"Nghia cua tu : "<<q->mean.nghia;
            gotoxy(25,14);
            cout<<"Vi du cua tu : "<<q->mean.vidu;
            q=q->right;
            }
            if(q!=NULL){
            gotoxy(25,15);
            cout<<"Nghia cua tu : "<<q->mean.nghia;
            gotoxy(25,16);
            cout<<"Vi du cua tu : "<<q->mean.vidu;
            q=q->right;
            }
            if(q!=NULL){
            gotoxy(25,17);
            cout<<"Nghia cua tu : "<<q->mean.nghia;
            gotoxy(25,18);
            cout<<"Vi du cua tu : "<<q->mean.vidu;
            q=q->right;
            }
            //}
            sleep(3000);
            clear1();
            gotoxy(25,12);
            cout<<"YES";
            gotoxy(50,12);
            cout<<"NO";
       int l=1;
       int m=25;
       int cho=0;
       char u;
       Word word;
       gotoxy(20,12);
      while(cho!=13)
	{	
		gotoxy(l*m,12);
		if(l==1){
		SetBGColor(13);
		cout<<"   ";
		cout<<"YES ";
        }
         else if(l==2){
         SetBGColor(10);
         cout<<"  ";
         cout<<"NO ";
         }
		cho = getch();
		gotoxy(l*m,12);
		if(l==1){
		SetBGColor(0);
		cout<<"   ";
		cout<<"YES ";
         }
        else if(l==2){
         SetBGColor(0);
         cout<<"  ";
         cout<<"NO ";
         }
		if(cho==13) break;
		l=l+check1(cho,getch());
		if(l<1) l=2;
			else if (l>2) l=1;
	  }
	     gotoxy(25,12);
	     cout<<"      ";
	     gotoxy(50,12);
	     cout<<"      ";
                      if(l==1){
                      Delete_node(myList[n].first,myList[n].last,p);
                      ptr z=p->myword.w.dau;
                      if(z!=NULL){
                         xoa_nghia(p->myword.w.dau);
                         z=z->right;
                         }
                      if(z!=NULL){
                         xoa_nghia(p->myword.w.dau);
                         z=z->right;
                         }
                      if(z!=NULL){
                         xoa_nghia(p->myword.w.dau);
                         z=z->right;
                         }
                      gotoxy(30,10);
                      cout<<"                                    ";
                      gotoxy(30,10);
                      cout<<"XOA THANH CONG";
                      sleep(1000);
                      gotoxy(18,10);
                      cout<<"                                                     ";
                      gotoxy(27,5);
                      cout<<"                   ";
                      k=0;
                      xau[k]='\0';
                      gotoxy(27,5);
                      goto xoatu;
                      }
                      if(l==2)
                      {
                      gotoxy(27,5);
                      cout<<"                                   ";
                      gotoxy(30,10);
                      cout<<"                                   ";
                      gotoxy(15,10);
                      cout<<"Ban co muon tiep tuc xoa! (ENTER tiep tuc/ESC de tro ve) ";
                      do{
                          c1=getch();
                          ch=ktkytu(c1);
                      }while(ch!=13 && ch!=27);
                      if(ch==13){
                        gotoxy(15,10);
                        cout<<"                                                         ";
                        gotoxy(27,5);
                        cout<<"                           ";
                        k=0;
                        xau[k]='\0';
                        gotoxy(27,5);
                        goto xoatu;
                        }
                      if(ch==27) return;
                      //}
                      }
                      }
          else
          {
              k=0;
              gotoxy(20,15);
              cout<<"Khong co tu "<<xau<<" trong tu dien!";
              sleep(1000);
              gotoxy(20,15);
              cout<<"                                    ";
              gotoxy(27,5);
              cout<<"                                    ";
              gotoxy(27,5);
              goto xoatu;
             }
             }
          if(ch==27) return;
            }
            }
void inkhung()
{
     char c=196;
     char d=179;
     char e=191;
     char f=192;
     char g=193;
     char h=194;
     char a=195;
     char p=217;
     char v=218;
     char n=180;
	gotoxy(3,4); textcolor(15);cout<<"FIND: ";
	gotoxy(23,6); textcolor(15); cout<<"Loai Tu: ";
	gotoxy(23,8); textcolor(15); cout<<"Dong nghia: ";
	gotoxy(23,10); textcolor(15); cout<<"Nghia va vi du:";
	for(int i=0;i<6;i++){
        gotoxy(23,12+i);
        cout<<"_";
        }
	gotoxy(1,3); for(int i = 0 ; i< 78 ; i++) cout<<c;
	gotoxy(1,5); for(int i = 0 ; i< 20 ; i++) cout<<c;
	gotoxy(22,5); for(int i = 0 ; i< 56 ; i++) cout<<c;
	gotoxy(21,5); cout<<h;
	gotoxy(1,3); cout<<v;
	gotoxy(1,5); cout<<a; 
	gotoxy(1,4); cout<<d;
	gotoxy(78,3); cout<<e;
	gotoxy(78,4); cout<<d;
	gotoxy(78,5); cout<<n;
	gotoxy(1,6); 
	for(int i = 6 ; i< 26 ; i++){
		gotoxy(1,i); cout<<d;
	}
	gotoxy(78,6);
	for(int i = 6 ; i< 26 ; i++){
		gotoxy(78,i); cout<<d;
	}	
	gotoxy(21,6);
	for(int i = 6 ; i< 26; i++){
		gotoxy(21,i); cout<<d;
	}
	gotoxy(1,25); cout<<f;
	gotoxy(21,25); cout<<g;
	gotoxy(78,25); cout<<p;
	gotoxy(2,25); for(int i = 0 ; i< 19 ; i++) cout<<c;
	gotoxy(22,25); for(int i = 0 ; i< 56 ; i++) cout<<c;
	
}
void in_khung1(){
             design();
             char c=16,d=2;
             system("color 0");
             textcolor(1);
             gotoxy(30,4);
             cout<<d<<" Tu ban can tra: ";
             textcolor(15);
	         gotoxy(25,8);
	         cout<<c<<" Loai tu: ";
	         gotoxy(25,10);
             cout<<c<<" Dong nghia: ";
             gotoxy(25,12);
             cout<<c<<" Nghia va vi du: ";
             gotoxy(25,14);
             cout<<c<<" Nghia 1: ";
             gotoxy(25,15);
             cout<<c<<" Vi du 1: ";
             gotoxy(25,16);
             cout<<c<<" Nghia 2: ";
             gotoxy(25,17);
             cout<<c<<" Vi du 2: ";
             gotoxy(25,18);
             cout<<c<<" Nghia 3: ";
             gotoxy(25,19);
             cout<<c<<" Vi du 3: "; 
       }  
void intu2(nodeptr p,int s){
     while(p!=NULL){
             gotoxy(3,s);
             cout<<p->myword.tu<<"\n";
             s++;
             p=p->next;
             if(s>=19)return;
             }
             }                     
void xoakhung(){
		for(int i=6;i<25;i++){
		gotoxy(2,i);
		cout<<"                 ";
	}
}
void xoa_space(){
             gotoxy(11,4);
             cout<<"                                   ";
	         gotoxy(32,6);
	         cout<<"                                   ";
	         gotoxy(34,8);
             cout<<"                                   ";
             gotoxy(24,12);
             cout<<"                                   ";
             gotoxy(24,13);
             cout<<"                                   ";
             gotoxy(24,14);
             cout<<"                                   ";
             gotoxy(24,15);
             cout<<"                                   ";
             gotoxy(24,16);
             cout<<"                                   ";
             gotoxy(24,17);
             cout<<"                                   ";
             } 
void tra_tu(){
     Word word;                 
     int s=6,k=0,a,g,h,y=4,l=1,m=5,cho=0;
     int x[]={11,12,13,14,15,16,17,18,19,20};
     int i=0;
	 char ch,xau[100]="";
     for(a=0; a<B; a++)
	{   
        nodeptr q=myList[a].first;
		while(q!=NULL)
		{
		 gotoxy(3,s);
         cout<<q->myword.tu<<"\n";
         s++;
         q=q->next;
         if(s>=19) break;		
		}
	}          
 while(1){
tratu:
      gotoxy(11+k,4);
      s=6;
      ch=getch();
      if(ch>0){
          if(isalpha(ch)&&ch!=77&&ch!=75&&ch!=80&&ch!=72||ch==32)
          {
               xoakhung();
               xau[k++]=ch;
               xau[k]='\0';
               gotoxy(11,4);
               cout<<xau;
               g=wherex();
               h=wherey();
               strcpy(word.tu,xau);
               int ab=hashtable(word);
               if(myList[ab].first==NULL)
                  {
                   xoakhung();
                   gotoxy(3,6);
                   SetColor(15);
                   cout<<"EMPTY";
                   gotoxy(g+1,h);
                   }
                if(myList[ab].first!=NULL)
                {
                    int dong=6,dem=0;
                    xoakhung();
                    nodeptr p;
                    for(p=myList[ab].first;p!=NULL;p=p->next)
                    {
                      if(strncmp(p->myword.tu,xau,strlen(xau))==0) 
                             {
                              intu2(p,dong);
                              gotoxy(2,6);
                              SetBGColor(3);
                              cout<<"               ";
                              gotoxy(3,6);
                              cout<<p->myword.tu;
                              SetBGColor(0);
                              gotoxy(g+1,h);
                              dem++;
                              break;
                              }
                              }
                    if(dem==0)
                    {
                        gotoxy(2,6);
	                    SetBGColor(0);
					    cout<<"                ";
 			            gotoxy(3,6);
					    SetColor(15);
					    cout<<"EMPTY";
					    gotoxy(g+1,h);
		           }
   			  }
   		  }
       if(ch==8)
	   {
			if(k>0)
               {
				xau[k--];
				xau[k]='\0';
				gotoxy(11,4); 
				printf("                                         ");
				gotoxy(11,4);
				printf("%s",xau);
				if(k>0)
				{
                    strcpy(word.tu,xau);				  
					int abc=hashtable(word);
					if(myList[abc].first==NULL)
                    {
						xoakhung();
						gotoxy(3,6);
						SetColor(15);
						cout<<"EMPTY";
						gotoxy(g+1,h);
				    }
                       if(myList[abc].first!=NULL)
			     	{
						xoakhung();
						int dong =6, dem=0;
						nodeptr q;
						for(q=myList[abc].first;q!=NULL;q=q->next)
						{
							if(strncmp(q->myword.tu,xau,strlen(xau))==0)
							{
								intu2(q,dong);
								gotoxy(2,6);
								SetBGColor(3);
								cout<<"                ";
								gotoxy(3,6);
								cout<<q->myword.tu;//
								SetBGColor(0);
					   			y=wherey();
					   			gotoxy(g+1,h);
							    dem++;break;
			   				}
                       }
                       if(dem==0)
                       {
                             gotoxy(3,6);
                             SetColor(15);
                             cout<<"EMPTY";
                             gotoxy(23+strlen("Loai Tu: "),6);
					   		 cout<<"                                 ";
					   		 gotoxy(23+strlen("Dong nghia: "),8);
					   		 cout<<"                                 ";
                             for(int z=0;z<B;z++)
						   		{
						   			gotoxy(24,12+z);
							   		cout<<"                                     ";
						   		}
							gotoxy(g+1,h);
				   		}
	   		    	 }
			   }                                    
               else{
                    gotoxy(2,6);
					SetBGColor(0);
					cout<<"                ";
					xoakhung();
	   				for(a=0; a<B; a++)
					{
                          nodeptr h=myList[a].first;
						while(h!=NULL)
						{
							gotoxy(3,s);
							cout<<h->myword.tu<<endl;
							s++;
							h=h->next;
							if(s==19) break;
						}
					}
			   }
			}
	   }
        if(ch==13)
        {
            char xaun[MAX]=" ";
            gotoxy(11,4); 
			printf("                                         ");
			gotoxy(11,4);
			printf("%s",xau);
			strcpy(word.tu,xau);
			int v = hashtable(word);
			int i;
			gotoxy(23+strlen("Loai Tu: "),6);
	   		cout<<"                                 ";
	   		gotoxy(23+strlen("Dong nghia: "),8);
	   		cout<<"                                 ";
	   		for(int z=0;z<6;z++)
	   		{
	   			gotoxy(24, 12+z);
   		   		cout<<"                                     ";
	   		}
	   		for(nodeptr c=myList[v].first;c!=NULL;c=c->next)
               {
                    if(strncmp(c->myword.tu,xau,strlen(xau))==0)
                    {
                    gotoxy(23+strlen("Loai Tu: "),6);
		   		   	cout<<"                                 ";
		   		   	gotoxy(23+strlen("Loai Tu:  "),6);
		   		   	cout<<c->myword.loaitu;
		   		   	gotoxy(23+strlen("Dong nghia:  "),8);
		   		   	cout<<"                                 ";
		   		   	gotoxy(23+strlen("Dong nghi:   "),8);
		   		   	cout<<c->myword.dongnghia;
		   		   	strcpy(xaun,c->myword.dongnghia);
		   		   	int m=0;
                    gotoxy(11,4); 
                    cout<<c->myword.tu;
		   		   	strcpy(xau,c->myword.tu);
		   		   	k=strlen(xau);
		   		   	ptr s=c->myword.w.dau;
                       if(s!=NULL){
                       gotoxy(25, 12);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(25, 12);
	   		   		   cout<<s->mean.nghia;
	   		   		   gotoxy(25,13);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(25,13);
	   		   		   cout<<s->mean.vidu;
	   		   		   s=s->right;
                    }
                    if(s!=NULL){
                       gotoxy(25, 14);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(25, 14);
	   		   		   cout<<s->mean.nghia;
	   		   		   gotoxy(25,15);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(25,15);
	   		   		   cout<<s->mean.vidu;
	   		   		   s=s->right;
                    }
                    if(s!=NULL){
                       gotoxy(25, 16);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(25, 16);
	   		   		   cout<<s->mean.nghia;
	   		   		   gotoxy(25,17);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(25,17);
	   		   		   cout<<s->mean.vidu;
	   		   		   s=s->right;
                    }
	   		            	break;	   	
                   }	
			}
		  Word word;
		 strcpy(word.tu,xaun);
         int n=hashtable(word);
         nodeptr z=search_word(word);
       if(z!=NULL){
       k=0;
       int l=1;
       int m=5;
       int cho=0;
       char u;
       gotoxy(23,6);
     while(cho!=13)
	{
tu:	
		gotoxy(23,l+m);
		if(l==1){
		textcolor(3);
		cout<<"Loai tu: ";
        }
         else if(l==3){
         textcolor(4);
         cout<<"Dong nghia: ";
         }
         else if(l==5){
         textcolor(10);
         cout<<"Nghia va vi du: ";
         }
         else 
         if(l==7||l==8||l==9||l==10||l==11||l==12){
         textcolor(4);
         cout<<"_";
         }
		cho = getch();
		gotoxy(23,l+m);
		if(l==1){
		textcolor(15);
		cout<<"Loai tu: ";
         }
        else if(l==3){
         textcolor(15);
         cout<<"Dong nghia: ";
         }
         else if(l==5){
         textcolor(15);
         cout<<"Nghia va vi du: ";
         }
         if(l==7||l==8||l==9||l==10||l==11||l==12){
         textcolor(15);
         cout<<"_";
         } 
		if(cho==13) break;
		if(cho==27){
            int s=6;
                k=0;
                sleep (3000);
                xoa_space();
                xoakhung();
                textcolor(15);
                for(int a=0;a<B;a++)
                {
                        nodeptr h=myList[a].first;
                        if(h!=NULL)
                        intu2(h,s);
                        }
                gotoxy(11,4);
                goto tratu;
                textcolor(15);
                break;
                }  
		l=l+check(cho,getch());
		if(l<1) l=12;
			else if (l>12) l=1;
	  }
	      if(l==3){
                system("cls");
                in_khung1();
                gotoxy(50,4);
                cout<<z->myword.tu;
                gotoxy(36,8);
	            cout<<z->myword.loaitu;
	            gotoxy(39,10);
                cout<<z->myword.dongnghia;
                gotoxy(25,12);
                cout<<"Nghia va vi du: ";
                ptr b=z->myword.w.dau;
                 if(b!=NULL){
                gotoxy(36,14);
                cout<<b->mean.nghia;
                gotoxy(36,15);
                cout<<b->mean.vidu;
                b=b->right;
                }
                if(b!=NULL){
                gotoxy(36,16);
                cout<<b->mean.nghia;
                gotoxy(36,17);
                cout<<b->mean.vidu;
                b=b->right;
                }
                if(b!=NULL){
                gotoxy(36,18);
                cout<<b->mean.nghia;
                gotoxy(36,19);
                cout<<b->mean.vidu;
                b=b->right;
                }
                }
             else {
                  gotoxy(23,6);
                  goto tu;
                 }
           int s=6;
           sleep(3000);
               system("cls");
               inkhung();
               for(int a=0;a<B;a++){
                  nodeptr h=myList[a].first;
                  if(h!=NULL)
                  intu2(h,s);
                  }
                  gotoxy(11,4);
                  goto tratu;
              }
          else { 
                int s=6;
                k=0;
                sleep (3000);
                xoa_space();
                xoakhung();
                for(int a=0;a<B;a++)
                {
                        nodeptr h=myList[a].first;
                        if(h!=NULL)
                        intu2(h,s);
                        }
                gotoxy(11,4);
                goto tratu;
                }
          strcpy(xaun," ");
      }
		if(ch==27) return;
    }
   }
 }                   

void in_khung2()
{
     char c=196;
     char d=179;
     char e=191;
     char f=192;
     char g=193;
     char h=194;
     char a=195;
     char p=217;
     char v=218;
     char n=180;
    textcolor(14);
    gotoxy(22,4); cout<<"THE OLD INFORMATION ";
    gotoxy(52,4); cout<<"THE NEW INFORMATION ";
    textcolor(03);
    gotoxy(3,8); cout<<"Loai tu: ";
    textcolor(04);
    gotoxy(3,9); cout<<"Dong nghia: ";
    textcolor(05);
    gotoxy(3,10); cout<<"Nghia 1: ";
    gotoxy(3,11); cout<<"Vi du 1: ";
    gotoxy(3,12); cout<<"Nghia 2: ";
    gotoxy(3,13); cout<<"Vi du 2: ";
    gotoxy(3,14); cout<<"Nghia 3: ";
    gotoxy(3,15); cout<<"Vi du 3: ";
    textcolor(15);
	gotoxy(1,3); for(int i = 0 ; i< 78 ; i++) cout<<c;
	gotoxy(1,5); for(int i = 0 ; i< 40 ; i++) cout<<c;
	gotoxy(22,5); for(int i = 0 ; i< 56 ; i++) cout<<c;
	gotoxy(15,3); cout<<h;
	gotoxy(1,3); cout<<v;
	gotoxy(1,5); cout<<a; 
	gotoxy(1,4); cout<<d;
	gotoxy(78,3); cout<<e;
	gotoxy(78,4); cout<<d;
	gotoxy(78,5); cout<<n;
	gotoxy(1,6); 
	for(int i = 6 ; i< 26 ; i++){
		gotoxy(1,i); cout<<d;
	}
	gotoxy(78,6);
	for(int i = 6 ; i< 26 ; i++){
		gotoxy(78,i); cout<<d;
	}	
	gotoxy(15,4);
	for(int i = 4 ; i<= 25; i++){
		gotoxy(15,i); cout<<d;
	}
	gotoxy(1,25); cout<<f;
	gotoxy(21,25);cout<<g;
	gotoxy(78,25); cout<<p;
	gotoxy(2,25); for(int i = 0 ; i< 38 ; i++) cout<<c;
	gotoxy(22,25); for(int i = 0 ; i< 56 ; i++) cout<<c;
	
}
void edit_tu(){
     Word word;                 
     int s=6,k=0,a,g,h,y=4,l=1,m=5,cho=0;
     nodeptr q;
	 char ch,xau[MAX]=" ";
     for(a=0; a<B; a++)
	{   
         q=myList[a].first;
		while(q!=NULL)
		{
			gotoxy(3,s);
			cout<<q->myword.tu<<endl;
			s++;
			q=q->next;
			if(s>=19) break;
		}
	}          
 while(1){
tratu:
      gotoxy(11+k,4);
      s=6;
      ch=getch();
      if(ch==27) return;
      if(ch>0){
          if(isalpha(ch)&&ch!=75&&ch!=77&&ch!=80&&ch!=72||ch==32)
          {
               xoakhung();
               xau[k++]=ch;
               xau[k]='\0';
               gotoxy(11,4);
               cout<<xau;
               g=wherex();
               h=wherey();
               strcpy(word.tu,xau);
               int ab=hashtable(word);
               if(myList[ab].first==NULL)
                  {
                   xoakhung();
                   gotoxy(3,6);
                   SetColor(15);
                   cout<<"EMPTY";
                   gotoxy(g+1,h);
                   }
                if(myList[ab].first!=NULL)
                {
                    int dong=6,dem=0;
                    xoakhung();
                    nodeptr p;
                    for(p=myList[ab].first;p!=NULL;p=p->next)
                    {
                      if(strncmp(p->myword.tu,xau,strlen(xau))==0) 
                             {
                              intu2(p,dong);
                              gotoxy(2,6);
                              SetBGColor(3);
                              cout<<"               ";
                              gotoxy(3,6);
                              cout<<p->myword.tu;
                              SetBGColor(0);
                              gotoxy(g+1,h);
                              dem++;
                              break;
                              }
                              }
                    if(dem==0)
                    {
                        gotoxy(2,6);
	                    SetBGColor(0);
					    cout<<"                ";
 			            gotoxy(3,6);
					    SetColor(15);
					    cout<<"EMPTY";
					    gotoxy(g+1,h);
		           }
   			  }
   		  }
       if(ch==8)
	   {
			if(k>0)
               {
				xau[k--];
				xau[k]='\0';
				gotoxy(11,4); 
				printf("                                         ");
				gotoxy(11,4);
				printf("%s",xau);
				if(k>0)
				{
                    strcpy(word.tu,xau);				  
					int abc=hashtable(word);
					if(myList[abc].first==NULL)
                    {
						xoakhung();
						gotoxy(3,6);
						SetColor(15);
						cout<<"EMPTY";
						gotoxy(g+1,h);
				    }
                       if(myList[abc].first!=NULL)
			     	{
						xoakhung();
						int dong =6, dem=0;
						nodeptr q;
						for(q=myList[abc].first;q!=NULL;q=q->next)
						{
							if(strncmp(q->myword.tu,xau,strlen(xau))==0)
							{
								intu2(q,dong);
								gotoxy(2,6);
								SetBGColor(3);
								cout<<"                ";
								gotoxy(3,6);
								cout<<q->myword.tu;
								SetBGColor(0);
					   			y=wherey();
					   			gotoxy(g+1,h);
							    dem++;break;
			   				}
                       }
                       if(dem==0)
                       {
                             gotoxy(3,6);
                             SetColor(15);
                             cout<<"EMPTY";
                             gotoxy(23+strlen("Loai Tu: "),6);
					   		 cout<<"                                 ";
					   		 gotoxy(23+strlen("Dong nghia: "),8);
					   		 cout<<"                                 ";
                             for(int z=0;z<B;z++)
						   		{
						   			gotoxy(24,12+z);
							   		cout<<"                                     ";
						   		}
							gotoxy(g+1,h);
				   		}
	   		    	 }
			   }                                    
               else{
                    gotoxy(2,6);
					SetBGColor(0);
					cout<<"                ";
					xoakhung();
	   				for(a=0; a<B; a++)
					{
                          nodeptr h=myList[a].first;
						while(h!=NULL)
						{
							gotoxy(3,s);
							cout<<h->myword.tu<<endl;
							s++;
							h=h->next;
							if(s>=19) break;
						}
					}
			   }
			}
	   }
        if(ch==13)
        {
            char tu[MAX]=" ";
            char loaitu[MAX]=" ";
            char dongnghia[MAX]=" ";
            char xau1[MAX]=" ";
            char xau2[MAX]=" ";
            char xau3[MAX]=" ";
            char xau4[MAX]=" ";
            char xau5[MAX]=" ";
            char xau6[MAX]=" ";
            gotoxy(11,4); 
			printf("                                         ");
			gotoxy(11,4);
			printf("%s",xau);
			strcpy(word.tu,xau);
			int v = hashtable(word);
			int i;
			gotoxy(23+strlen("Loai Tu: "),6);
	   		cout<<"                                 ";
	   		gotoxy(23+strlen("Dong nghia: "),8);
	   		cout<<"                                 ";
	   		for(int z=0;z<6;z++)
	   		{
	   			gotoxy(24, 12+z);
   		   		cout<<"                                     ";
	   		}
	   		for(nodeptr c=myList[v].first;c!=NULL;c=c->next)
               {
                    if(strncmp(c->myword.tu,xau,strlen(xau))==0)
                    {
                    strcpy(tu,c->myword.tu);
                    gotoxy(23+strlen("Loai Tu: "),6);
		   		   	cout<<"                                 ";
		   		   	gotoxy(23+strlen("Loai Tu: "),6);
		   		   	cout<<c->myword.loaitu;
		   		   	strcpy(loaitu,c->myword.loaitu);
		   		   	gotoxy(23+strlen("Dong nghia: "),8);
		   		   	cout<<"                                 ";
		   		   	gotoxy(23+strlen("Dong nghi: "),8);
		   		   	cout<<c->myword.dongnghia;
		   		   	strcpy(dongnghia,c->myword.dongnghia);
		   		   	strcpy(xau1,c->myword.dongnghia);
		   		   	int m=0;
                    gotoxy(11,4); 
                    cout<<c->myword.tu;
		   		   	strcpy(xau,c->myword.tu);
		   		   	k=strlen(xau);
		   		   	ptr s=c->myword.w.dau;
		   		   	if(s!=NULL){
                       gotoxy(24, 12);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(24, 12);
	   		   		   cout<<s->mean.nghia;
	   		   		   strcpy(xau1,s->mean.nghia);
	   		   		   gotoxy(24,13);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(24,13);
	   		   		   cout<<s->mean.vidu;
	   		   		   strcpy(xau2,s->mean.vidu);
	   		   		   s=s->right;
                         }
                    if(s!=NULL){
                       gotoxy(24, 14);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(24, 14);
	   		   		   cout<<s->mean.nghia;
	   		   		   strcpy(xau3,s->mean.nghia);
	   		   		   gotoxy(24,15);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(24,15);
	   		   		   cout<<s->mean.vidu;
	   		   		   strcpy(xau4,s->mean.vidu);
	   		   		   s=s->right;
                         }
                         if(s!=NULL){
                       gotoxy(24, 16);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(24, 16);
	   		   		   cout<<s->mean.nghia;
	   		   		   strcpy(xau5,s->mean.nghia);
	   		   		   gotoxy(24,17);
	   		   		   cout<<"                         ";
	   		   		   gotoxy(24,17);
	   		   		   cout<<s->mean.vidu;
	   		   		   strcpy(xau6,s->mean.vidu);
	   		   		   s=s->right;
                         }
                         break;
	   		             }	   	
                   }	
     char ch,c;
     char xau[6][MAX];
     init2(xau);
     Word eword;
     gotoxy(27,21);
     SetBGColor(3);
     gotoxy(29,21);
     cout<<" BAN CO MUON THAY DOI THONG TIN TU TREN ! ";
     SetBGColor(0);
     sleep(2000);
     gotoxy(27,21);
     cout<<"                                              ";
     gotoxy(33,21);
     SetBGColor(1);
     gotoxy(35,21);
     cout<<"   NHAN PHIM Y/N DE TIEP TUC !  ";
     SetBGColor(0);
     sleep(2000);
     gotoxy(33,21);
     cout<<"                                     ";
     while(1)
             {
           ch=toupper(getch());
           if(ch=='Y'){
           system("cls");
           in_khung2();
           gotoxy(39,6);
           cout<<"TU BAN CAN SUA: ";
           gotoxy(55,6);
           cout<<tu;
           gotoxy(22,8);
           textcolor(03);
           cout<<loaitu;
           gotoxy(22,9);
           textcolor(04);
           cout<<dongnghia;
           gotoxy(22,10);
           textcolor(05);
           cout<<xau1;
           gotoxy(22,11);
           cout<<xau2;
           gotoxy(22,12);
           cout<<xau3;
           gotoxy(22,13);
           cout<<xau4;
           gotoxy(22,14);
           cout<<xau5;
           gotoxy(22,15);
           cout<<xau6;
           strcpy(loaitu," ");
           strcpy(dongnghia," ");
           int x[]={51,52,53,54,55,56,57,58,59,60,61,62,63,64,65};
            int index=0,y=8,i1=0,i2=0,i3=0,i4=0,i5=0,i6=0,i7=0,i8=0;
            int             j1=1,j2=1,j3=1,j4=1,j5=1,j6=1,j7=1,j8=1;
           gotoxy(52,8);
           while(1){
     nhaptu:
            c=getch();
             if(c==72)
                {
                if(index<=0){
                index=1;          
                gotoxy(52,25);
                 }
               else {
               index--;
               gotoxy(52,y+index);
               }
               j1=1, j2=1, j3=1, j4=1, j5=1, j6=1, j7=1, j8=1;
               }
             else if(c==80||c==9){
               if(index>=7){
               index=0;
               gotoxy(52,8);
               }
               else{
               index++;
               gotoxy(52,y+index);
               }
             j1=1, j2=1, j3=1, j4=1, j5=1, j6=1, j7=1, j8=1;
             }
             else if(c==27) return;
             else if(c==8){
                 switch(index){
                     if(i1>0){
                      case 0:
                           i1--;
                           loaitu[i1]='\0';
                           gotoxy(52,8);
                           cout<<"                          ";
                           textcolor(03);
                           gotoxy(52,8);
                           cout<<loaitu;
                           break;
                           }
                      if(i2>0){
                      case 1:
                           i2--;
                           dongnghia[i2]='\0';
                           gotoxy(52,9);
                           cout<<"                          ";
                           textcolor(04);
                           gotoxy(52,9);
                           cout<<dongnghia;
                           break;
                           }
                      if(i3>0){
                      case 2:
                           i3--;
                           xau[0][i3]='\0';
                           gotoxy(52,10);
                           cout<<"                          ";
                           textcolor(05);
                           gotoxy(52,10);
                           cout<<xau[0];
                           break;
                           }
                      if(i4>0){
                      case 3:
                           i4--;
                           xau[1][i4]='\0';
                           gotoxy(52,11);
                           cout<<"                          ";
                           textcolor(05);
                           gotoxy(52,11);
                           cout<<xau[1];
                           break;
                           }
                      if(i5>0){
                      case 4:
                           i5--;
                           xau[2][i5]='\0';
                           gotoxy(52,12);
                           cout<<"                          ";
                           textcolor(05);
                           gotoxy(52,12);
                           cout<<xau[2];
                           break;
                           }
                      if(i6>0){
                      case 5:
                           i6--;
                           xau[3][i6]='\0';
                           gotoxy(52,13);
                           cout<<"                          ";
                           textcolor(05);
                           gotoxy(52,13);
                           cout<<xau[3];
                           break;
                           }
                      if(i7>0){
                      case 6:
                           i7--;
                           xau[4][i7]='\0';
                           gotoxy(52,14);
                           cout<<"                          ";
                           textcolor(05);
                           gotoxy(52,14);
                           cout<<xau[4];
                           break;
                           }
                      if(i8>0){
                       case 7:
                           i8--;
                           xau[5][i8]='\0';
                           gotoxy(52,15);
                           cout<<"                          ";
                           textcolor(05);
                           gotoxy(52,15);
                           cout<<xau[5];
                           break;    
                           }
                           }
                           }
              else 
           if(c==77)
           {  switch(index){
                 case 0:
                      if(j1==i1) j1=0;
                      j1++;
                      gotoxy(x[j1],y+index);
                      break;
                 case 1:
                      if(j2==i2) j2=0;
                      j2++;
                      gotoxy(x[j2],y+index);
                      break;
                 case 2:
                      if(j3==i3) j3=0;
                      j3++;
                      gotoxy(x[j3],y+index);
                      break;
                 case 3:
                      if(j4==i4) j4=0;
                      j4++;
                      gotoxy(x[j4],y+index);
                      break;
                 case 4:
                      if(j5==i5) j5=0;
                      j5++;
                      gotoxy(x[j5],y+index);
                      break;
                 case 5:
                      if(j6==i6) j6=0;
                      j6++;
                      gotoxy(x[j6],y+index);
                      break;
                 case 6:
                      if(j7==i7) j7=0;
                      j7++;
                      gotoxy(x[j7],y+index);
                      break;
                 case 7:
                      if(j8==i8) j8=0;
                      j8++;
                      gotoxy(x[j8],y+index);
                      break;
                      }
                           }
           else if(c==75)
           {  switch(index){
                 case 0:
                      if(j1==1) j1=i1+1;
                      j1--;
                      gotoxy(x[j1],y+index);
                      break;
                 case 1:
                      if(j2==1) j2=i2+1;
                      j2--;
                      gotoxy(x[j2],y+index);
                      break;
                 case 2:
                      if(j3==1) j3=i3+1;
                      j3--;
                      gotoxy(x[j3],y+index);
                      break;
                 case 3:
                      if(j4==1) j4=i4+1;
                      j4--;
                      gotoxy(x[j4],y+index);
                      break;
                 case 4:
                      if(j5==1) j5=i5+1;
                      j5--;
                      gotoxy(x[j5],y+index);
                      break;
                 case 5:
                      if(j6==1) j6=i6+1;
                      j6--;
                      gotoxy(x[j6],y+index);
                      break;
                 case 6:
                      if(j7==1) j7=i7+1;
                      j7--;
                      gotoxy(x[j7],y+index);
                      break;
                 case 7:
                      if(j8==1) j8=i8+1;
                      j8--;
                      gotoxy(x[j8],y+index);
                      break;
                      }
                           } 
               else if(isalpha(c)||c==32){
                    switch(index){
                   case 0:
                        textcolor(03);
                        loaitu[i1++]=c;
                        loaitu[i1]='\0';
                        gotoxy(52,8);
                        cout<<"                        ";
                        gotoxy(52,8);
                        cout<<loaitu;
                        break;
                   case 1:
                        textcolor(04);
                        dongnghia[i2++]=c;
                        dongnghia[i2]='\0';
                        gotoxy(52,9);
                        cout<<"                        ";
                        gotoxy(52,9);
                        cout<<dongnghia;
                        break;
                   case 2:
                        textcolor(05);
                        xau[0][i3++]=c;
                        xau[0][i3]='\0';
                        gotoxy(52,10);
                        cout<<"                        ";
                        gotoxy(52,10);
                        cout<<xau[0];
                        break;
                   case 3:
                        textcolor(05);
                        xau[1][i4++]=c;
                        xau[1][i4]='\0';
                        gotoxy(52,11);
                        cout<<"                       ";
                        gotoxy(52,11);
                        cout<<xau[1];
                        break;
                   case 4:
                        textcolor(05);
                        xau[2][i5++]=c;
                        xau[2][i5]='\0';
                        gotoxy(52,12);
                        cout<<"                       ";
                        gotoxy(52,12);
                        cout<<xau[2];
                        break;
                   case 5:
                        textcolor(05);
                        xau[3][i6++]=c;
                        xau[3][i6]='\0';
                        gotoxy(52,13);
                        cout<<"                       ";
                        gotoxy(52,13);
                        cout<<xau[3];
                        break;
                   case 6:
                        textcolor(05);
                        xau[4][i7++]=c;
                        xau[4][i7]='\0';
                        gotoxy(52,14);
                        cout<<"                    ";
                        gotoxy(52,14);
                        cout<<xau[4];
                        break;
                   case 7:
                        textcolor(05);
                        xau[5][i8++]=c;
                        xau[5][i8]='\0';
                        gotoxy(52,15);
                        cout<<"                     ";
                        gotoxy(52,15);
                        cout<<xau[5];
                        break;
                        }
                        //cout<<c;
                        }
               else if(c==13){
                    textcolor(14);
                    if (i1==0)
             {
                gotoxy(35,22);
                cout<<"BAN NHAP THIEU DU LIEU";
                sleep(1000);
                gotoxy(35,22);
                cout<<"                      ";
                gotoxy(52,8);
                index=0;
                goto nhaptu;
                }
             else if(i3==0)
             {
                  gotoxy(35,22);
                  cout<<"BAN NHAP THIEU DU LIEU";
                  sleep(1000);
                  gotoxy(35,22);
                  cout<<"                      ";
                  gotoxy(52,10);
                  index=2;
                  goto nhaptu;
                  }
             else if(i2==0)
             {
                  strcpy(dongnghia," ");
                  }   
             i1=0,i2=0,i3=0,i4=0,i5=0,i6=0,i7=0,i8=0;
                    strcpy(eword.tu,tu);
                    strcpy(eword.loaitu,loaitu);
                    strcpy(eword.dongnghia,dongnghia);
                    init(eword.w);
                       themcuoi1nghia(eword.w,xau[0],xau[1]);
                       themcuoi1nghia(eword.w,xau[2],xau[3]);
                       themcuoi1nghia(eword.w,xau[4],xau[5]);
                     init2(xau);
                    nodeptr p=search_word(eword);
                    p->myword=eword;
                    p->myword.w=eword.w;
                    strcpy(tu," ");
                    strcpy(loaitu," ");
                    strcpy(dongnghia," ");
                    init2(xau);
                    gotoxy(35,22);
                    textcolor(14);
                    cout<<"HIEU CHINH TU THANH CONG !";
                    sleep(1000);
                    gotoxy(45,22);
                    cout<<"                          ";
                    system("cls");
                    inkhung();
                    for(int a=0;a<26;a++){
                       nodeptr h=myList[0].first;
                        if(h!=NULL)
                         intu2(h,s);
                         }
                         k=0;
                         gotoxy(11,4);
                         cout<<"       ";
                         gotoxy(11,4);
                         goto tratu;
                        }   
                        }                                          
                        }
                      if(ch=='N')
                      {
                      k=0;
                      xoa_space();
                      gotoxy(11,4);
                      cout<<"            ";
                      gotoxy(11,4);
                      goto tratu;
                        }
     } 	
		}
    }
   }
  }
int travel(int l){
	system ("cls");
	gotoxy(10,3);
	system("color 0");
	textcolor(3);
    cout <<"\n \t\t\t+-----------------o0o----------------+";
    cout <<"\n \t\t\t|                                    |";
	cout <<"\n \t\t\t|    ENGLISH-VIETNAMESE DICTIONARY   |";
	cout <<"\n \t\t\t|                                    |";
	cout <<"\n \t\t\t+-----------------o0o----------------+";
	cout <<"\n \t\t\t|       ** BASICS OF FUNCTION **     |";
	cout <<"\n \t\t\t|           ADD    : THEM TU         |";
	cout <<"\n \t\t\t|           SEARCH : TRA TU          |";
	cout <<"\n \t\t\t|           DELETE : XOA TU          |";
	cout <<"\n \t\t\t|           EDIT   : SUA TU          |";
	cout <<"\n \t\t\t+-----------------o0o----------------+";
	cout <<"\n";
    textcolor(15);	
       gotoxy(8,18);
       cout<<"ADD";
       gotoxy(28,18);
       cout<<"DELETE";
       gotoxy(48,18);
       cout<<"SEARCH";
       gotoxy(68,18);
       cout<<"EDIT";
        l=0;
       int m=20;
       int cho=0;
       char u;
       Word word;
       gotoxy(8,18);
     while(cho!=13)
	{
tu:	
		gotoxy(l*m+8,18);
		if(l==0){
		textcolor(1);
		cout<<"ADD";
        }
         else if(l==1){
         textcolor(1);
         cout<<"DELETE";
         }
         else if(l==2){
         textcolor(5);
         cout<<"SEARCH";
         }
         else 
         if(l==3){
         textcolor(14);
         cout<<"EDIT";
         }
		cho = getch();
		gotoxy(l*m+8,18);
		if(l==0){
		textcolor(15);
		cout<<"ADD";
         }
         else if(l==1){
         textcolor(15);
         cout<<"DELETE";
         }
         else if(l==2){
         textcolor(15);
         cout<<"SEARCH";
         }
         if(l==3){
         textcolor(15);
         cout<<"EDIT";
         } 
		if(cho==13) break;
		if(cho==27) exit(1);
		l=l+check1(cho,getch());
		if(l<0) l=3;
			else if (l>3) l=0;
	  }
	  return l;
}
void intro(){
	textcolor(14);
	gotoxy(25,3);
	cout<<"D";
	sleep(200);
	cout<<"O";
	sleep(200);
	cout<<" A";
	sleep(200);
	cout<<"N";
	sleep(200);
	cout<<" C";
	sleep(200);
	cout<<"U";
	sleep(200);
	cout<<"O";
	sleep(200);
	cout<<"I";
	sleep(200);
	cout<<" K";
	sleep(200);
	cout<<"Y";
	sleep(200);
	cout<<" C";
	sleep(200);
	cout<<"T";
	sleep(200);
	cout<<"D";
	sleep(200);
	cout<<"L";
	sleep(200);
	cout<<"&";
	sleep(200);
	cout<<"G";
	sleep(200);
	cout<<"T";
	sleep(200);
	cout<<":";
	sleep(200);
	gotoxy(29,4);
	cout<<"T";
	sleep(200);
	cout<<"U";
	sleep(200);
	cout<<" ";
	sleep(200);
	cout<<"D";
	sleep(200);
	cout<<"I";
	sleep(200);
	cout<<"E";
	sleep(200);
	cout<<"N";
	sleep(200);
	cout<<" ";
	sleep(200);
	cout<<"A";
	sleep(200);
	cout<<"N";
	sleep(200);
	cout<<"H";
	sleep(200);
	cout<<"-";
	sleep(200);
	cout<<"V";
	sleep(200);
	cout<<"I";
	sleep(200);
	cout<<"E";
	sleep(200);
	cout<<"T";
	sleep(1500);
	gotoxy(29,7);
	textcolor(10);
	cout<<"N";
	sleep(200);
    cout<<"G";
	sleep(200);
    cout<<"O";
	sleep(200);
	cout<<" ";
	sleep(200);
	cout<<"T";
	sleep(200);
	cout<<"H";
	sleep(200);
	cout<<"I";
	sleep(200);
	cout<<" ";
	sleep(200);
	cout<<"K";
	sleep(200);
	cout<<"I";
	sleep(200);
	cout<<"M";
	sleep(200);
	cout<<" ";
	sleep(200);
	cout<<"D";
	sleep(200);
	cout<<"U";
	sleep(200);
	cout<<"N";
	sleep(200);
	cout<<"G";
	sleep(200);
	sleep(1500);
	textcolor(13);
	gotoxy(31,9);
	cout<<"B";
	sleep(200);
	cout<<"U";
	sleep(200);
	cout<<"I";
	sleep(200);
	cout<<" ";
	sleep(200);
	cout<<"T";
	sleep(200);
	cout<<"H";
	sleep(200);
	cout<<"I";
	sleep(200);
	cout<<" ";
	sleep(200);
	cout<<"B";
	sleep(200);
	cout<<"E";
	sleep(200);
	cout<<" ";
	sleep(200);
	cout<<"B";
	sleep(200);
	cout<<"A";
	sleep(200);
	sleep(1500);
}                                       
using namespace std;

int main(int argc, char *argv[])
{
    NODEPTR List;
    int n;
    int cn;
    char xau[MAX];
    //intro();
    initialize();
    load_file();
	do{ 
		system("cls");
		 cn=travel(n);
		switch(cn)
		{
			case 0:
				system("cls");
				nhap_tu(List);
				remove("anh.txt");
				save_file();
				break;
			case 1:	
				system("cls");
				xoa_tu();
				remove("anh.txt");
				save_file();
				break;
			case 2:	
				system("cls");
				inkhung();
				tra_tu();
				break;
			case 3:
				system("cls");
				inkhung();
				edit_tu();
				remove("anh.txt");
				save_file();
				break;
		}
	}while(cn>=0&&cn<=3);
    system("PAUSE");
    return EXIT_SUCCESS;
}
