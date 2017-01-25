#include <stdio.h>
#include<stdlib.h>
#include <strings.h>
#define filename "students.txt"
#define maxSize 100
struct StudentRecord {
       char *courseName;
       float Mark;
       struct StudentRecord *next;
};
typedef struct StudentRecord *StudentRecordType;

typedef struct {
        char *firstName;
        char *lastName;
        int idNumber;
        StudentRecordType courses;
} StudentType;

struct classNodeStruct {
       StudentType *aStudent;
       struct classNodeStruct *next;
};
typedef struct classNodeStruct *ClassNodeType;
//ftiaksame tis domes
int comparison(char *,char*,char*,char*);
void mo(ClassNodeType);
void insertData(ClassNodeType*);
void deleteNode(ClassNodeType*,int);
void insertNode(ClassNodeType,ClassNodeType*);
int main()
{
    ClassNodeType list=NULL,p;
    char command[maxSize];
    char clear[maxSize];  
    insertData(&list);//eisagei kai emfanizei ta dedomena
    mo(list);//ypologizei kai emfanizei ton meso oro gia kathe foithth
    printf("Dwse ''delete *arithmos mitrwwou*'' gia na diakrapseis kapoion foithth, \n''display'' gia na emfaniseis th lista i dwse exit gia exodo\n");
    scanf("%s",command);
    while(strcmp(command,"exit")!=0)
    {
                                    if (strcmp(command,"delete")==0)
                                    {
                                                                     int id;
                                                                     scanf("%d",&id);
                                                                     deleteNode(&list,id);//anazhta kai diagrafei ton komvo.sth sunexeia emfanizei ta stoixeia tou
                                    }
                                    else if(strcmp(command,"display")==0)
                                    {
                                         p=list;
                                         if (p!=NULL)
                                         {
                                                     while(p->next!=NULL)
                                                     {
                                                                         printf("%s %s %d\n",p->aStudent->lastName,p->aStudent->firstName,p->aStudent->idNumber);
                                                                         p=p->next;
                                                     }
                                                     printf("%s %s %d\n",p->aStudent->lastName,p->aStudent->firstName,p->aStudent->idNumber);
                                         }
                                         else
                                         {
                                             printf("The list is empty!\n");
                                         }
                                    }
                                         
                                    else 
                                    {
                                         printf("command %s is invalid \n",command);
                                         gets(clear);
                                    }
                                    printf("Dwse ''delete *arithmos mitrwwou*'' gia na diakrapseis kapoion foithth, \n''display'' gia na emfaniseis th lista i dwse exit gia exodo\n");
                                    scanf("%s",command);
    }
    
    system("pause");
    return 0;
}

                                   
void insertData(ClassNodeType*p)
{
     int size;
     FILE *fp;
     fp=fopen(filename,"r");
     if (fp==NULL)//elenxoume an yparxei to arxeio
     {
                  printf("ERROR-file not found\n");
                  system("pause");
                  exit(1);
     }
     fscanf(fp,"%d",&size);printf("Tha eisaxthoun %d foithtes\n",size);
     if (size==0) //elenxoume an yparxoun foithtes
     {
                  printf("No Data\n");
                  system("pause");
                  exit(1);
     }
     ClassNodeType n;
     StudentRecordType c,q;
     char *fname,*lname,*cname;
     int coursesNumber,i,j;
     float mark;
     for (i=0;i<size;i++)
     {
         n=(ClassNodeType)malloc(sizeof(struct classNodeStruct));//anoigoume neo komvo
         n->aStudent=malloc(sizeof(StudentType));
         
         if ((n==NULL)||(n->aStudent==NULL))
         {
                     printf("ERROR-Out of memory\n");
                     return;
         }
     
         
         
         fname=(char*)malloc(sizeof(char)*maxSize);
         lname=(char*)malloc(sizeof(char)*maxSize);
         n->aStudent->firstName=fname;
         n->aStudent->lastName=lname;
         if ((fname==NULL)||(lname==NULL))
            {
                  printf("ERROR-out of memory\n");
                  return;
            }
         fscanf(fp,"%s",fname);//diavazoume ta stoixeia
         fscanf(fp,"%s",lname);
         fscanf(fp,"%d",&n->aStudent->idNumber);
         fscanf(fp,"%d",&coursesNumber);
         n->aStudent->courses=NULL;//arxika exoume kenh lista
         for(j=0;j<coursesNumber;j++)
         {
                                     fgetc(fp);
                                     
                                    
                                     c=(StudentRecordType)malloc(sizeof(struct StudentRecord));
                                     if (c==NULL)
                                     {
                                                 printf("ERROR-out of memory\n");
                                                 return;
                                     }
                                     if (n->aStudent->courses==NULL)//an einai to prwto mathima
                                     {
                                                                        c->next=NULL;//vazoume NULL giati einai to telos ths listas
                                                                        n->aStudent->courses=c;
                                     }
                                     else
                                     {
                                         c->next=n->aStudent->courses;
                                         n->aStudent->courses=c;
                                     }
                                    
                                     cname=malloc(sizeof(char)*maxSize);
                                     mark=n->aStudent->courses->Mark;
                                     cname=fgets(cname,maxSize,fp);
                                     fscanf(fp,"%f",&mark);
                                     c->courseName=cname;
                                     c->Mark=mark;
                                      
                  
         }
        
         insertNode(n,p);//sinarthsh pou eisagei enan komvo me alfavhtikh seira
         printf("Eisixthise o parakatw foithths:\n %s %s %d\n",n->aStudent->lastName,n->aStudent->firstName,n->aStudent->idNumber);
         q=n->aStudent->courses;
         if (q!=NULL)
         {
                     printf("%s Vathmos: %f\n",q->courseName,q->Mark);
                     while(q->next!=NULL)
                     {
                                         q=q->next;
                                         printf("%s Vathmos: %f\n",q->courseName,q->Mark);
                     }
         }
        
                                         
     }
     fclose(fp);
     
}
                      
                                     
void insertNode(ClassNodeType n,ClassNodeType* p)
{
     ClassNodeType curr,prev;
     curr=*p;
     prev=NULL;
    
     
         while((curr!=NULL)&&(comparison(curr->aStudent->lastName,curr->aStudent->firstName,n->aStudent->lastName,n->aStudent->firstName)))
         {
                                                                                            prev=curr;
                                                                                            curr=curr->next;
         }
         if (prev==NULL)//an einai to proto stoixeio  
         {
                         n->next=*p;
                         *p=n;
         }
         else
         {
             n->next=curr;
             prev->next=n;
         }
}

void mo(ClassNodeType list)
{
     StudentRecordType q;
     ClassNodeType p;
     p=list;
    
     float S,m;
     int i;
     system("pause");
     if (list!=NULL)//an i lista dn einai kenh
     {
                            do
                            {
                                    q=p->aStudent->courses;
                                    if (q!=NULL)
                                    {
                                                S=0;
                                                i=0;
                                                do
                                                {
                                                    S=S+q->Mark;
                                                    i++;
                                                    q=q->next;
                                                }while(q!=NULL);
                                                m=S/i;
                                                printf("%s %s %d Mesos Oros: %f\n",p->aStudent->lastName,p->aStudent->firstName,p->aStudent->idNumber,m);
                                    }
                                    else
                                    {
                                        printf("O/H %s %s den exei perasei kanena mathima\n",p->aStudent->lastName,p->aStudent->firstName);
                                    }
                                    p=p->next;
                            }
                            while(p!=NULL);
     }
     else
     {
         printf("Den exoun dwthei mathites");
     }
}
void deleteNode(ClassNodeType*p,int id)
{
     ClassNodeType curr,prev;
     prev=NULL;
     curr=*p;
     while((curr!=NULL)&&(curr->aStudent->idNumber!=id))
     {
                                                        prev=curr;
                                                        curr=curr->next;
     }
     if (curr==NULL)//an ftasoume sto telos ths listas kai dn vrethei
     {
                                      printf("Den yparxei foithths me arithmo mitrwwou %d\n",id);
                                      return;
     }
     else if(prev==NULL)//an einai to prwto stoixeio
     {
          *p=(*p)->next;
          printf("Diagrafhke o %s %s %d\n",curr->aStudent->lastName,curr->aStudent->firstName,curr->aStudent->idNumber);
          free(curr);
     }
     else//an einai kapoio stoixeio sth mesh ths listas
     {
              prev->next=curr->next;
              printf("Diagrafhke o/h %s %s %d\n",curr->aStudent->lastName,curr->aStudent->firstName,curr->aStudent->idNumber);
              free(curr);
              
     }
}
int comparison(char *lastName,char* firstName,char*lastName1,char*firstName1)
{
    if (strcasecmp(lastName,lastName1)<0)
    {
                                         return 1;
    }
    else if(strcasecmp(lastName,lastName1)==0)
    {
         if(strcasecmp(firstName,firstName1)<0)
         {
                                               return 1;
         }
         else
         {
             return 0;
         }
    }
    else 
    {
         return 0;
    }
}
    
     
         
          
                                      
                                    
                            
          
           

