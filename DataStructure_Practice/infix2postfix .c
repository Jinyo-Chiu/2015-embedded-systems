#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define STACK_SIZE 50 

#define ADD_SUB   1       /*�N�� �[��*/
#define MULT_DIV  2   	   /* �N�� ���� */
#define LEFT      3         /* �N���A�� */
#define RIGHT     4          /* �N��k�A�� */

char stack[STACK_SIZE];       /* ���|�}�C */
int top=-1;                  /* ���|���ݫ��� */ 
int priority[STACK_SIZE];        /*�u���v���| */


void push(char s,int number){
   if(top>=STACK_SIZE-1){
      printf("���|���F");
   }
   else{
     top++;
     stack[top]=s;
     priority[top]=number;
   }
}

void pop(){
    if (top==-1){
      printf("���|�w��\n");
    }
    else{
  /*���n�L�X  '('*/
       if( priority[top ]!=LEFT){
    printf("%c",stack[top]);
       }
       top--;
    }
} 

/* �B��l�B�z */
void Operator(char ch,int number) {

  if(top==-1&&number!=RIGHT) /* �Y���|���� ����push */
      push(ch,number);
  else{
        switch(number){          
             /* �Y��J�� ')' �q���|���ݨ̧�pop����X�{'('  */
           case RIGHT:
                for(priority[top];priority[top]!=LEFT;pop()) ;
                    pop();//��̫᪺ '(' pop �����L�X 
                break;                       
            /* �Y��J�� '('  ���� PUSH  */
           case LEFT:
                push(ch,number);
                break;    
            /* �Y��J�O '+' '-' '*' '/' */
           case ADD_SUB:
           case MULT_DIV:
   
                if( priority[top]==LEFT||priority[top]<number){
                   push(ch,number);
                }
                else{
       /* �Y���|���u���v �j��number  */
                    while((priority[top]>=number)&&priority[top]!=LEFT)
                           pop(); /* ��POP ���|���APUSH number  */ 
                    push(ch,number);
                }   
                break;
            /*��r��wscan�� ���|������ pop �ѤU���B��l*/           
            case 0:  
       while(top!=-1) 
                      pop();
                 break;
        }        
    }  
}         

int main(void){
    
    char *IndString;
    char buf[STACK_SIZE];
    int i=0;
    int error_OP = 0;
    printf("�п�J���� :");
    IndString=gets(buf);//���ǿ�J
    printf("\n");
    printf("��Ǭ�:");

   /*�Y�����󵲧��r��*/ 
   while(*(IndString+i)!='\0' & !error_OP) {

       /*�Ʀr�M�r���O�B�⤸�ҥH�����L�X */
      if(isalnum(*(IndString+i))) {    
               printf("%c",*(IndString+i));
      }
      else if(ispunct(*(IndString+i))) {     //�Y���O�Ʀr �ť� �r��  �h���u 
       
             switch(*(IndString+i)){
                case '+':
                             Operator(*(IndString+i),ADD_SUB);                       
                             break;
                case '-':   
                             Operator(*(IndString+i),ADD_SUB);                       
                             break;         
             
                case '*':
                             Operator(*(IndString+i),MULT_DIV);
                             break;
                case '/':
                             Operator(*(IndString+i),MULT_DIV);
                             break;
                case '(':
                             Operator(*(IndString+i),LEFT);
                             break; 
                case ')':
                            Operator(*(IndString+i),RIGHT);
                            break;  
                default:
                            printf(" error Operator\n");
                            error_OP = 1;
       break;
            }   
       }     
     i++; 
   } 

   Operator('\0',0);//�r��scan���� 
   puts("\n------------------------------------\n");
   return 0;
}