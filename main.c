#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct student
{
	char fname[11],lname[11],fsname[11],flname[11];
	char dob[11],presch[32],contact[11],addr[32];
	char roll[16];
	float twcgpa;
};

struct sub
{
	float gain;
	float total;
};

struct test
{
	char sname[10];
	struct sub ct1;
	struct sub ct2;
	struct sub put;
	
};

 all_func(char filename[])
 {
 	
	int choice;
 	FILE *fp;
	struct student stu;
	
	top_view();
		
	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("\n No such student registered\n\n");
		return 0;
	}
	
	fread(&stu,sizeof(struct student),1,fp);
	
	fclose(fp);
	
	printf("    ####  ALLENHOUSE INSTITUTE OF TECHNOLOGY   ####\n\n");
	printf("        Student's dtails are given below  :  \n\n");
	printf(" STUDENT's NAME           : %s %s\n",stu.fname,stu.lname);
	printf(" ROLL NUMBER              : %s\n",stu.roll);
	printf(" Date of Birth            : %s\n",stu.dob);
	fflush(stdin);

	printf(" FATHER'S NAME            : %s %s \n",stu.fsname,stu.flname);

 		
 		printf("\n\n");
 		
	do
	{
		
	printf("  1. EDIT My Profile\n");
	printf("  2. to upload marks\n");
	printf("  3. to view marks\n");
	printf("  4. to DELETE\n");
	printf("  5. to go Back\n");
	
	choice = getch();
		
	switch(choice) 
	{
		case '1' : up_date(filename);
		break;
		
		case '2' : add_marks(filename);
		break;
		
		case '3' : get_marks(filename);
		break ;
		
		case '4' : del_rec(filename);
		break ;
		
		case '5' : choice = '5';
		break ; 
		
		default : printf(" invaalid \n");
	}

	}while(choice!='5');
	
 	
 	top_view();
 	
 }
 
acadmics(char filename[])
{
	
	FILE *fp;
	struct student stu;
	int choice=0;
	
	top_view();
		
	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("\n No such student registered\n\n");
		return 0;
	}
	
	fread(&stu,sizeof(struct student),1,fp);
	
	fclose(fp);
	
	printf("    ####  ALLENHOUSE INSTITUTE OF TECHNOLOGY   ####\n\n");
	printf("        Student's dtails are given below  :  \n\n");
	printf(" STUDENT's NAME           : %s %s\n",stu.fname,stu.lname);
	printf(" ROLL NUMBER              : %s\n",stu.roll);
	printf(" Date of Birth            : %s\n",stu.dob);
	fflush(stdin);

	printf(" FATHER'S NAME            : %s %s \n",stu.fsname,stu.flname);
	
	do
	{
		
		
	printf(" 1. to upload marks\n");
	printf(" 2. to view marks\n");
	printf(" 3. to go back\n");
	
	choice = getch();
		
	switch(choice) 
	{
		case '1' : add_marks(filename);
		break;
		
		case '2' : get_marks(filename);
		break;
		
		case '3' :choice = '3';
		break ;
		
		default: 	printf(" invaalid \n");
	}
	
	}while(choice!='3');
	
	top_view();
	
}

int view_subs()
{
	
	struct test CT[10];
	FILE *fp;
	int i=0,j=0;
	COORD co;
	
	top_view();
	fp=fopen("subjects","r");

	while(1)
	{
		fread(&CT[i],sizeof(struct test),1,fp);
		
		if(feof(fp))
		{
			break;
		}
	
		i++;
	
		
	}
	
	frame(i);
	
	print_marks(CT,i,0);
	
	return i;
	
}

create_sub()
{
	
	struct test SUB;
	FILE *fp;
	int n;	
	
	top_view();
	
	while(1)
	{
	
	fp=fopen("subjects","a");
	
	n=view_subs();
	
	if(n==10)
	{
		printf(" Already %d subjects no more subjects can be assigned\n",n);
		return 0;
	}
	
	
	printf(" Press any key to ADD and ENTER when you are done\r");
	
	if(getch()=='\r')
	{
		printf("                                               \r");
		view_subs();
		break;
	}
	
	printf("                                                  \r");
		
	
	printf("Enter sub name : ");
	scanf("%s",SUB.sname);
	
	
	SUB.ct1.gain=0;
	
	printf("Enter max marks for CT1 :");
	scanf("%f",&SUB.ct1.total);
	
	SUB.ct2.gain=0;
	
	printf("Enter max marks for CT2 :");
	scanf("%f",&SUB.ct2.total);
	
	SUB.put.gain=0;
	
	printf("Enter max marks for PUT :");
	scanf("%f",&SUB.put.total);
	
	fflush(stdin);
	
	
	if(fwrite(&SUB,sizeof(struct test),1,fp))
	{
		printf(" Recorded successfully...\n");
	}
	
	
	ass_sub2all(SUB);
	
	fclose(fp);
	
	}
	
	
}

ass_sub21(char fname[])
{
	FILE *fp1,*fp2;
	struct test CT;
	int i=0,j=0;
	
	if((fp1=fopen("subjects","r"))==NULL)
	{
		printf(" subject file unable to open\n");
		return 0;
		
	}
	
	if((fp2=fopen(fname,"r+"))==NULL)
	{
		printf(" %s file unable to open\n",fname);
		return 0;
		
	}
	
		fseek(fp2,sizeof(struct student),0);
	
	while(1)
	{
	
		if(fread(&CT,sizeof(struct test),1,fp1))
		{
			printf(" %s readed \n",CT.sname);
		}
	
	
		if(feof(fp1))
		{
			printf(" process complete \n");
			break;
		}
	
	
		if(fwrite(&CT,sizeof(struct test),1,fp2))
		{
			printf(" %s assigned to %s\n",CT.sname,fname);
		}
		
	}
	
	
	fclose(fp1);
	fclose(fp2);
	
	
}

ass_sub2all(struct test SUB)
{
	char fname[30];
	FILE *fp1,*fp2;
	
	if(!(fp1=fopen("records","r")))
	{
		return 0;
	}
	
	while(1)
	{
		fscanf(fp1,"%s",fname);
		
		
		if(feof(fp1))
		{
			break;
		}
		
		printf("%s\n",fname);
		
		fp2=fopen(fname,"a");
		
		fwrite(&SUB,sizeof(struct test),1,fp2);
		
		fclose(fp2);
		
	}
	
	fclose(fp1);
	
}

frame(int n)
{
	int k,l;
	n++;
	
	for(k=0;k<126;k++)
	{
		printf("-");
	
	}
	printf("\n");
	
	printf("|      Subject Name      |           CT1          |          CT2           |          PUT           |        average         |");
	
	printf("\n");
	
	for(k=0;k<n;k++)
	{
		
		for(l=0;l<126;l++)
		{
	
			if(l%25==0)
			{
				printf("|");
			}
			else
			{
				printf(" ");
			}
			
		}
		
		printf("\n");
		
	}
	
	for(k=0;k<126;k++)
	{
		printf("-");
	
	}
	printf("\n");
	
	printf("|        TOTAL :         |                        |                        |                        |                        |\n");
	
	for(k=0;k<126;k++)
	{
		printf("-");
	
	}
	printf("\n");
	
	
	
}

print_marks(struct test t[],int i,int p)
{

	COORD frm;
	int j;
	float sum[4]={0,0,0,0},total[4]={0,0,0,0};


	frm.Y=p+8;
	
	
	for(j=0;j<i;j++)
	{
		frm.X=3;
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),frm);
		printf("%d. %s  ",j+1,t[j].sname);
		frm.X+=26;
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),frm);
		printf("%0.2f out of %0.2f ",t[j].ct1.gain,t[j].ct1.total);
		frm.X+=25;
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),frm);
		printf("%0.2f out of %0.2f ",t[j].ct2.gain,t[j].ct2.total);
		frm.X+=25;
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),frm);
		printf("%0.2f out of %0.2f ",t[j].put.gain,t[j].put.total);

		frm.X+=25;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),frm);
		printf(" %0.2f / %0.2f ",(t[j].put.gain+t[j].ct2.gain+t[j].ct1.gain)/3,(t[j].ct1.total+t[j].ct2.total+t[j].put.total)/3);

		frm.Y+=1;
			
		sum[0]+=t[j].ct1.gain;sum[1]+=t[j].ct2.gain;sum[2]+=t[j].put.gain;sum[3]+=(t[j].put.gain+t[j].ct2.gain+t[j].ct1.gain)/3;
		total[0]+=t[j].ct1.total;total[1]+=t[j].ct2.total;total[2]+=t[j].put.total;total[3]+=(t[j].put.total+t[j].ct2.total+t[j].ct1.total)/3;

		
	}

	frm.Y++;
	frm.X=30;
	
	for(j=0;j<4;j++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),frm);
	 	printf(" %0.2f / %0.2f ",sum[j],total[j]);
 
  	frm.X+=25;
	
	}

	
	frm.Y=p+i+12;
  frm.X=0;	
  
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),frm);
		
	
}

add_marks(char name[])
{
	
	struct test CT[10];
	FILE *fp;
	int i=0,j=0,k,l;
	COORD curr,w;
	
	top_view();
	
	if((fp=fopen(name,"r+"))==NULL)
	{
		printf("No Such Student\n");
		return ;
	}
	
	fseek(fp,sizeof(struct student),0);
	
	while(i<10)
	{
		fread(&CT[i],sizeof(struct test),1,fp);
		
		if(feof(fp))
		{
			break;
		}
	
		i++;
		
	}
	
	frame(i);
	
	print_marks(CT,i,0);

	curr.X=15;
	curr.Y=i+12;
	
	w.X=45;
	w.Y=i+11;
	
	for(j=0;j<i;j++)
	{
		printf("\r");
		printf(" %s ",CT[j].sname);
		printf("          ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
		
		printf("%0.2f  out of %0.2f ",CT[j].ct1.gain,CT[j].ct1.total);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
		if(getch()!='\r')
		{
			
			while(1)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
				printf("      ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
				scanf("%f",&CT[j].ct1.gain);
				
				if(CT[j].ct1.gain>CT[j].ct1.total)
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),w);
					printf(" marks cannot be above %0.2f",CT[j].ct1.total);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
					continue;
				}
				
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),w);
				printf("                                           ");
				
				break ;
				
			}
			
			print_marks(CT,i,0);
			
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
		}
			
		printf("%0.2f  out of %0.2f ",CT[j].ct2.gain,CT[j].ct2.total);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
		
		if(getch()!='\r')
		{
			
			while(1)
			{
				printf("      ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
				scanf("%f",&CT[j].ct2.gain);
				
				if(CT[j].ct2.gain>CT[j].ct2.total)
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),w);
					printf(" marks cannot be above %0.2f",CT[j].ct2.total);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
					continue;
				}
				
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),w);
				printf("                                           ");
				
				break ;
				
			}
			
			print_marks(CT,i,0);
			
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
		
		}
		
		printf("%0.2f  out of %0.2f",CT[j].put.gain,CT[j].put.total);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);		
		if(getch()!='\r')
		{
			while(1)
			{ 
				printf("      ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
				scanf("%f",&CT[j].put.gain);
				
				if(CT[j].put.gain>CT[j].put.total)
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),w);
					printf(" marks cannot be above %0.2f",CT[j].put.total);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
					continue;
				}
				
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),w);
				printf("                                           ");
				
				break ;
				
			}
			
			print_marks(CT,i,0);
			
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),curr);
		
		}
	
			
	}


	fseek(fp,sizeof(struct student),0);
	
	for(j=0;j<i;j++)
	{
		fwrite(&CT[j],sizeof(struct test),1,fp);
		printf(" Marks uploaded of sub %s \n",CT[j].sname);
	}
	
	fclose(fp);
	
	top_view();
	
}

get_marks(char name[])
{
	struct test CT[10];
	FILE *fp;
	int i=0,j=0;
	int sum[4]={0,0,0,0},total[4]={0,0,0,0};
	
	top_view();
	
	if((fp=fopen(name,"r"))==NULL)
	{
		printf(" Student Not registered\n");
		return 0;
	}

	fseek(fp,sizeof(struct student),0);
	
	
	while(i<10)
	{
		
		fread(&CT[i],sizeof(struct test),1,fp);
		
		
		if(feof(fp))
		{
			break;
		}
	
	
		i++;
	
	}
	
	
	fclose(fp);
	
	frame(i);
	
	print_marks(CT,i,0);	
		
}

int match(char str1[],char str2[],int i,int j,int m,int n)
{	
	if(i==0&&j==0)
	{
		m+=2;
	}
	
	 if(str1[i-1]==' '||str2[j-1]==' ') 
	{
		m++;
	}
	
	if(str1[i+1]==str2[j+1]&&str1[i+1]!='\0'&&str2[j+1]!='\0')
	{
		m++;
		n=match(str1,str2,i+1,j+1,m,n);
	}
		
	if(m<n)
	{
		return n;
	}
		
}

search_rec()
{
	
	struct priority
	{
		int fn;
		int p;
	};
	
	
	FILE *fp1,*fp2;	
	struct student stu[20];
	char ch[31],filename[35];

	if((fp1=fopen("records","r"))==NULL)
	{
		printf(" NO Record available \n\n");
		return 0;
	}
	
	int i=0,j=0,k=0,l=0;
	
	while(1)
	{
		fscanf(fp1,"%s",filename);
		
		if((fp2=fopen(filename,"r"))==NULL)
		{
			continue;
		}
		
		fread(&stu[l],sizeof(struct student),1,fp2);
		
		if(feof(fp1))
		{
			break;
		}
		
		fclose(fp2);

		l++;
	}
		
	int x=0,q=0;
	char in;
	COORD co;
	co.X=2;
	co.Y=6;
	int m=0,n=0,p,arr[l-1];
	struct priority pr[l-1],temp;
	
	top_view();
	
	while(in!='\e')
	{
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);
	
	printf("\n");
	printf("  Press ENETR key for more option\n");	
	printf("  Press BACKSPACE to go back\n");	
	printf("  Press TAB key to switch between students\n");	
	printf("\n Type Name ");	
	
	in=getch();
	
	switch(in)
	{
		case '\b': if(x!=0)
					{
						x--;
						ch[x]='\0';
					}
		break ;
		
		case '\e' : break;
		
		case '\t' : if(q==l-1)
					{
						q=0;
					}
					else
					{
						q++;
					}
		break ;
		
		case '\r' : strcpy(filename,stu[pr[q].fn].fname);
					strlwr(filename);
		    		strcat(filename,stu[pr[q].fn].roll);
					all_func(filename);
					fp2=fopen(filename,"r");
				    fread(&stu[pr[q].fn],sizeof(struct student),1,fp2);
					fclose(fp2);

		
		default : 	if(((in>='a'&&in<='z')||(in>='A'&&in<='z')||in ==' ')&&x!=30)
					{ 
						fflush(stdin);
						ch[x]=in;
						ch[x+1]='\0';
						x++;
					}
		break ;
		
		
	}
	
	
	top_view();
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);
	printf("\n\n\n\n\n           %s\n",ch);
	strlwr(ch);
	
	for(i=0;i<l;i++)
	{ 
		strcpy(filename,stu[i].fname);
		strcat(filename," ");
		strcat(filename,stu[i].lname);
		strlwr(filename);
		n=0;
		j=0;
		while(filename[j]!='\0')
		{
		
			k=0;
			while(ch[k]!='\0')
			{
				if(filename[j]==ch[k])
				{
					m++;
					p=match(filename,ch,j,k,m,n);
					n=p;
					m=0;
				}
			
			k++;
			
			}
			
		 j++;
		
		}
		pr[i].fn=i;
		pr[i].p=n;
	}
	
		
	for(j=0;j<l-1;j++)																							//sorting of structure by roll.no
	{																																// of student
		for(k=0;k<l-j-1;k++)
		{
			if(pr[k].p<pr[k+1].p)
			{	
				temp=pr[k];
				pr[k]=pr[k+1];
				pr[k+1]=temp;
			}
		}
	}
	
	for(i=0;i<l;i++)
	{
		if(i==q)
		{
			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 
																						 FOREGROUND_RED  |
													 									 FOREGROUND_GREEN | 
																						 //FOREGROUND_BLUE |
																						 FOREGROUND_INTENSITY );
	
		}
		
		printf("\n      %s %s",stu[pr[i].fn].fname,stu[pr[i].fn].lname);
	
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	}
	
	
	printf("\n");
	
	show_stu(stu[pr[q].fn],50,6,q);
	
	printf("\n");
	
		
	}
		
	top_view();
	
}

show_stu(struct student stu,int i,int j,int n)
{
	
	COORD co;
	
	co.X=i;
	co.Y=j;
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),
																						 //FOREGROUND_RED  |
																						 FOREGROUND_GREEN |
																						 FOREGROUND_BLUE |
																						 FOREGROUND_INTENSITY );
				
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);
		
	printf(" sr.[%d] name is                  : %s %s ",n+1,stu.fname,stu.lname);co.Y++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);
	printf(" sr.[%d] father's name is         : %s %s",n+1,stu.fsname,stu.flname);co.Y++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);
	printf(" sr.[%d] roll no. is              : %s ",n+1,stu.roll);co.Y++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);
	printf(" sr.[%d] Twelwth Sgpa             : %0.3f ",n+1,stu.twcgpa);co.Y++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);
	printf(" sr.[%d] Date of Birth            : %s",n+1,stu.dob);co.Y++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);
	printf(" sr.[%d] Pre School               : %s",n+1,stu.presch);co.Y++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);
	printf(" sr.[%d] Permanent Address        : %s",n+1,stu.addr);	co.Y++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);
	printf(" sr.[%d] Contact Number           : %s",n+1,stu.contact);co.Y++;
	
  SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE );

}

sort_rec()
{
	FILE *fp1,*fp2;																				//	getting the whole data into array ofstructure
	struct student stu[10];
	char ch[10],filename[30];
	char choice;
	int j,l,m,n=0;
	struct student temp;
	COORD s;
	
	s.X=2;
	s.Y=7;
	
	if((fp1=fopen("records","r"))==NULL)
	{
		printf(" No record available\n\n");
		return 0;
	}
	
	int i=0;
	
	while(1)
	{
		fscanf(fp1,"%s",filename);
	
		if((fp2=fopen(filename,"r"))==NULL)
		{
			continue;
		}
		fread(&stu[i],sizeof(struct student),1,fp2);
		
		if(feof(fp1))
		{
			break;
		}
		
		fclose(fp2);
	
		i++;
	}
	
		fclose(fp1);



	do
	{
		top_view();
	
		show_stu(stu[n],60,4,n);
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),s);
		
		printf(" Press n To sort by NAME\n");
		printf(" Press r To sort by ROLL.NO \n");
		printf(" Press s To sort by SGPA \n");
		printf(" Press o No sorting \n");
		printf(" Press ESC key to go back\n");
		printf(" Press ENTER for acadmics\n");
		printf("\n");
	
		for(j=0;j<i;j++)
		{
			if(j==n)
			{
 			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
				
			printf("\n");
			
			printf(" sr.[%d] name is                  : %s %s \n",j+1,stu[j].fname,stu[j].lname);
			
			SetConsoleTextAttribute ( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE |FOREGROUND_GREEN );

			}
			else
			{
				printf("\n");
				
				printf(" sr.[%d] name is                  : %s %s \n",j+1,stu[j].fname,stu[j].lname);
					
			}
			
		
		
		}
		
		
		printf("\n Press any key\n");
		
	choice=getch();
	
	switch(choice)
	{
		case 'n' :{ for(l=0;l<i-1;l++)																							//sorting of structure by name
							{																																// of student
								for(m=0;m<i-l-1;m++)
								{
									if(strcmp(stu[m].fname,stu[m+1].fname)>0)
									{
										temp=stu[m];
										stu[m]=stu[m+1];
										stu[m+1]=temp;
									}	
								}
							}
						}
		break;
				
		case 'r' :{	for(l=0;l<i-1;l++)																							//sorting of structure by roll.no
							{																																// of student
								for(m=0;m<i-l-1;m++)
								{
										if(strcmp(stu[m].roll,stu[m+1].roll)>0)
										{
											temp=stu[m];
											stu[m]=stu[m+1];
											stu[m+1]=temp;
										}
								}
							}
						}
		break;	
							
		case 's' :{
								for(l=0;l<i-1;l++)																							//sorting of structure by roll.no
							{																																// of student
								for(m=0;m<i-l-1;m++)
								{
									if(stu[m].twcgpa<stu[m+1].twcgpa)
									{	
										temp=stu[m];
										stu[m]=stu[m+1];
										stu[m+1]=temp;
									}
								}
							}
						}
		break ;					
		
		case 'o' : 
		break;
		
		case 9	: if(n==i-1)
				  {
					n=0;
				  }
   	   			  else	
			 	  {
			 		n++;
				  }
		break ;	
		
		case '\r' : strcpy(filename,stu[n].fname);
					strlwr(filename);
		   		    strcat(filename,stu[n].roll);
				    all_func(filename);
				    fp2=fopen(filename,"r");
				    fread(&stu[n],sizeof(struct student),1,fp2);
				    fclose(fp2);
								
		break ;
		
		case 27 :	 break ;		
		
							
		default : printf(" Incorrect choice ");
		break ;
								
	}
	
		
		
		
	}while(choice !=27);

	printf("\n");
	
	top_view();
	
}

add_inf()
{
	char filename[35],in,year[5];
	struct student stu;
	int i=0,yr;
	
	printf("   Kindly  provide  the given  information\n");
	printf("  Youir first name   ");
	
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.fname[i]='\0';
			
		}else if(in=='\r')
		{
			stu.fname[i]='\0';
			i=0;
			break;
		
		}else if(in==' '||(in=='\b'&&i==0)||i==10)
		{
			continue;
			
		}
		else{
			stu.fname[i]=in;
			i++;
			stu.fname[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.fname);
		printf("  Youir first name   ");
	
	}while(in!='\r');
	
	
	if(stu.fname[0]>96&&stu.fname[0]<123)
	{
		stu.fname[0]=stu.fname[0]-32;	
	}
	
	printf("\n  Your last name     ");
	
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.lname[i]='\0';
			
		}else if(in=='\r')
		{
			stu.lname[i]='\0';
			i=0;
			break;
		}else if(in==' '||in=='\b'||i==10)
		{
			continue;
			
		}
		else{
			stu.lname[i]=in;
			i++;
			stu.lname[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.lname);
		printf("  Your last name     ");
	
	}while(in!='\r');
	
	if(stu.lname[0]>96&&stu.lname[0]<123)
	{
		stu.lname[0]=stu.lname[0]-32;	
	}
	
	printf("\n  university Roll no. ");
	
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.roll[i]='\0';
			
		}else if(in=='\r')
		{
			stu.roll[i]='\0';
			i=0;
			break;
		
		}else if(in==' '||in=='\b'||i==15)
		{
			continue;
		}
		else{
			stu.roll[i]=in;
			i++;
			stu.roll[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.roll);
		printf("  Your University Roll Number     ");
	
	}while(in!='\r');
	
	
	strcpy(filename,stu.fname);
	strlwr(filename);
	strcat(filename,stu.roll);
	
	FILE *fptr,*fp;
		
		fp=fopen("records","a");
		
		if(fputs(filename,fp)!=EOF)
		{
			printf("\n Successfully stored in records\n");
		}
		
		fputc('\n',fp);
		fclose(fp);	
		
	if((fptr=fopen(filename,"r"))!=NULL)
	{
		printf("   Data has already added to the records\n\n  You can go and view details");
		fclose(fptr);
		return ;
	}
	
	fptr=fopen(filename,"w");

	printf("\n  Date of Birth       ");
	
	 do{
		in =getch();
		
		if(in=='\b')
		{
			if(i==0)
			{
				continue;
			}else if(i==3||i==6)
			{
				i-=2;
				stu.dob[i]='\0';
			}else{
				i--;
				stu.dob[i]='\0';
			}
			
		}else if(in=='\r')
		{
			stu.dob[i]='\0';
			i=0;
			break;
		
		}else if(in>='0'&&in<='9'&&i<=9){
			stu.dob[i]=in;
			i++;
			stu.dob[i]='\0';
		}
		
		if(i==2||i==5)
		{
			stu.dob[i]='/';
			i++;
			stu.dob[i]='\0';
		}
		
		if(i==6)
		{
			if((stu.dob[3]>='1'&&stu.dob[4]>'2'))
			{
				stu.dob[3]='1';
				stu.dob[4]='2';
			}
			
			if(stu.dob[3]=='0'&&stu.dob[4]=='2'&&stu.dob[0]>='3')
			{
				stu.dob[0]='2';
				stu.dob[1]='9';
			}else if(stu.dob[3]=='0'&&stu.dob[4]<='7'&&stu.dob[0]>='3')
			{
				stu.dob[0]='3';
				
				if(stu.dob[4]%2==0)
				{
					stu.dob[1]='0';
				}else{
					stu.dob[1]='1';
				}
				
			}else if(stu.dob[0]>='3')
			{
				stu.dob[0]='3';
			
				if((stu.dob[3]=='0'&&stu.dob[4]=='8')||stu.dob[3]=='1'&&(stu.dob[4]=='0'||stu.dob[4]>='2'))
				{
					stu.dob[1]='1';
				}else if((stu.dob[3]=='0'&&stu.dob[4]=='9')||(stu.dob[3]=='1'&&stu.dob[4]>='1'))
				{
					stu.dob[1]='0';
				}
			
			}
		}
		
		if(i==10)
		{
			
			if(stu.dob[3]=='0'&&stu.dob[4]=='2')
			{
				year[0]=stu.dob[6];
				year[1]=stu.dob[7];
				year[2]=stu.dob[8];
				year[3]=stu.dob[9];
				year[4]=stu.dob[10];
			
				sscanf(year, "%d", &yr); 
				if(((yr % 4 == 0) && (yr % 100 != 0)) ||(yr % 400 == 0))
				{
					stu.dob[1]='9';
				}else{
					stu.dob[1]='8';
				}
			
			}
			
		}
		
		printf("[ %s ]         \r",stu.dob);
		printf("  Date of Birth       ");
		
	}while(in!='\r');
	
	i=0;
	printf("\n  Father's first name      ");
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.fsname[i]='\0';
			
		}else if(in=='\r')
		{
			stu.fsname[i]='\0';
			i=0;
			break;
		}else if(in==' '||in=='\b'||i==10)
		{
			continue;
			
		}
		else{
			stu.fsname[i]=in;
			i++;
			stu.fsname[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.fsname);
		printf("  Father's first name      ");
	
	}while(in!='\r');
	
	if(stu.fsname[0]>96&&stu.fsname[0]<123)
	{
		stu.fsname[0]=stu.fsname[0]-32;	
	}
	
	printf("\n  Father's last name ");
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.flname[i]='\0';
			
		}else if(in=='\r')
		{
			stu.flname[i]='\0';
			i=0;
			break;
		}else if(in==' '||in=='\b'||i==10)
		{
			continue;
			
		}
		else{
			stu.flname[i]=in;
			i++;
			stu.flname[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.flname);
		printf("  Father's last name      ");
	
	}while(in!='\r');

	if(stu.flname[0]>96&&stu.flname[0]<123)
	{
		stu.flname[0]=stu.flname[0]-32;	
	}
	
	fflush(stdin);
	printf("\n  Permanent Address ");
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.addr[i]='\0';
			
		}else if(in=='\r')
		{
			stu.addr[i]='\0';
			i=0;
			break;
		}else if(in=='\b'||i==31)
		{
			continue;
			
		}
		else{
			stu.addr[i]=in;
			i++;
			stu.addr[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.addr);
		printf("  Permanent Address ");
	
	}while(in!='\r');
	
	printf("\n  School name ");
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.presch[i]='\0';
			
		}else if(in=='\r')
		{
			stu.presch[i]='\0';
			i=0;
			break;
		}else if(in=='\b'||i==31)
		{
			continue;
			
		}
		else{
			stu.presch[i]=in;
			i++;
			stu.presch[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.presch);
		printf("  Your School Name ");
	
	}while(in!='\r');

	
	fflush(stdin);
	printf("\n  Contact Number ");
	
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.contact[i]='\0';
			
		}else if(in=='\r')
		{
			stu.contact[i]='\0';
			i=0;
			break;
		}else if(in==' '||in=='\b'||i==10)
		{
			continue;
			
		}
		else if(in>='0'&&in<='9'){
			stu.contact[i]=in;
			i++;
			stu.contact[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.contact);
		printf("  Contact Number ");
	
	}while(in!='\r');

	printf("  Twelth score (cgpa) \n");
	scanf("%f",&stu.twcgpa);

	if(fwrite(&stu,sizeof(struct student),1,fptr))
	{
		printf("  YOUR DATA HAS STORED  SUCCESSFULLY\n");
	}
	
	fclose(fptr);
	
	ass_sub21(filename);
	
}

up_date(char filename[])
{
	struct student stu;
	FILE *fptr;
	int yr,choice,i=0;
	char in,year[5];
	
	if((fptr=fopen(filename,"r+"))==NULL)
	{
		printf(" No Such Record Found \n");
		fclose(fptr);
		return ;
	}
	
	fread(&stu,sizeof(struct student),1,fptr);
	
	do{
	
	top_view();
	
	printf("    ####  Enter the choice to modify   ####\n\n");
	printf("        Student's dtails are given below  :  \n\n");
	printf(" 1. STUDENT's NAME           : %s %s\n",stu.fname,stu.lname);
	printf(" 2. ROLL NUMBER              : %s\n",stu.roll);
	printf(" 3. Date of Birth            : %s\n",stu.dob);
	fflush(stdin);
	
	printf(" 4. FATHER'S NAME            : %s %s \n",stu.fsname,stu.flname);
	fflush(stdin);
	printf(" 5. Permanent Address        : ");	
    puts(stu.addr);
    fflush(stdin);
	printf(" 6. Contact Number           : %s\n",stu.contact);

	printf(" 7. Formar School Name       : "); puts(stu.presch);
	printf(" 8. Twelwth score (C.G.P.A)  : %f \n",stu.twcgpa);
	printf(" 9. Finish \n\n");
	fseek(fptr,0,0);
	
	printf("  Enter your choice  :  ");
	choice=getch();
		
	switch(choice)
	{
		case '1' :  printf(" You cannot change Your NAME \n ");
				  getch();
		break ;
		
		case '2' : printf(" You cannot change Your ROLL NUMBER \n");
			     	getch();
		break ;
		
		case '3' : printf("\n  Date of Birth       ");
	 do{
		in =getch();
		
		if(in=='\b')
		{
			if(i==0)
			{
				continue;
			}else if(i==3||i==6)
			{
				i-=2;
				stu.dob[i]='\0';
			}else{
				i--;
				stu.dob[i]='\0';
			}
			
		}else if(in=='\r')
		{
			stu.dob[i]='\0';
			i=0;
			break;
		
		}else if(in>='0'&&in<='9'&&i<=9){
			stu.dob[i]=in;
			i++;
			stu.dob[i]='\0';
		}
		
		if(i==2||i==5)
		{
			stu.dob[i]='/';
			i++;
			stu.dob[i]='\0';
		}
		
		if(i==6)
		{
			if((stu.dob[3]>='1'&&stu.dob[4]>'2'))
			{
				stu.dob[3]='1';
				stu.dob[4]='2';
			}
			
			if(stu.dob[3]=='0'&&stu.dob[4]=='2'&&stu.dob[0]>='3')
			{
				stu.dob[0]='2';
				stu.dob[1]='9';
			}else if(stu.dob[3]=='0'&&stu.dob[4]<='7'&&stu.dob[0]>='3')
			{
				stu.dob[0]='3';
				
				if(stu.dob[4]%2==0)
				{
					stu.dob[1]='0';
				}else{
					stu.dob[1]='1';
				}
				
			}else if(stu.dob[0]>='3')
			{
				stu.dob[0]='3';
			
				if((stu.dob[3]=='0'&&stu.dob[4]=='8')||stu.dob[3]=='1'&&(stu.dob[4]=='0'||stu.dob[4]>='2'))
				{
					stu.dob[1]='1';
				}else if((stu.dob[3]=='0'&&stu.dob[4]=='9')||(stu.dob[3]=='1'&&stu.dob[4]>='1'))
				{
					stu.dob[1]='0';
				}
			
			}
		}
		
		if(i==10)
		{
			
			if(stu.dob[3]=='0'&&stu.dob[4]=='2')
			{
				year[0]=stu.dob[6];
				year[1]=stu.dob[7];
				year[2]=stu.dob[8];
				year[3]=stu.dob[9];
				year[4]=stu.dob[10];
			
				sscanf(year, "%d", &yr); 
				if(((yr % 4 == 0) && (yr % 100 != 0)) ||(yr % 400 == 0))
				{
					stu.dob[1]='9';
				}else{
					stu.dob[1]='8';
				}
			
			}
			
		}
		
		printf("[ %s ]         \r",stu.dob);
		printf("  Date of Birth       ");
		
	}while(in!='\r');
	
		break ;
		
		case '4' :
		  
	printf("\n  Father's first name      ");
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.fsname[i]='\0';
			
		}else if(in=='\r')
		{
			stu.fsname[i]='\0';
			i=0;
			break;
		}else if(in==' '||in=='\b'||i==10)
		{
			continue;
			
		}
		else{
			stu.fsname[i]=in;
			i++;
			stu.fsname[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.fsname);
		printf("  Father's first name      ");
	
	}while(in!='\r');
	
	if(stu.fsname[0]>96&&stu.fsname[0]<123)
	{
		stu.fsname[0]=stu.fsname[0]-32;	
	}
	
	printf("\n  Father's last name ");
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.flname[i]='\0';
			
		}else if(in=='\r')
		{
			stu.flname[i]='\0';
			i=0;
			break;
		}else if(in==' '||in=='\b'||i==10)
		{
			continue;
			
		}
		else{
			stu.flname[i]=in;
			i++;
			stu.flname[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.flname);
		printf("  Father's last name      ");
	
	}while(in!='\r');

			
			
		break ;
		 
		case '5' :  fflush(stdin);
		
			printf("\n  Permanent Address ");
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.addr[i]='\0';
			
		}else if(in=='\r')
		{
			stu.addr[i]='\0';
			i=0;
			break;
		}else if(in=='\b'||i==31)
		{
			continue;
			
		}
		else{
			stu.addr[i]=in;
			i++;
			stu.addr[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.addr);
		printf("  Permanent Address ");
	
	}while(in!='\r');

		break ;
		
		case '6' :  
		
	printf("\n  Contact Number ");
	
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.contact[i]='\0';
			
		}else if(in=='\r')
		{
			stu.contact[i]='\0';
			i=0;
			break;
		}else if(in==' '||in=='\b'||i==10)
		{
			continue;
			
		}
		else if(in>='0'&&in<='9'){
			stu.contact[i]=in;
			i++;
			stu.contact[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.contact);
		printf("  Contact Number ");
	
	}while(in!='\r');
		
		break ;
		
		case '7' : fflush(stdin);
		
			printf("\n  School name ");
	do{
		in =getch();
		if(in=='\b'&&i!=0)
		{
			i--;
			stu.presch[i]='\0';
			
		}else if(in=='\r')
		{
			stu.presch[i]='\0';
			i=0;
			break;
		}else if(in=='\b'||i==31)
		{
			continue;
			
		}
		else{
			stu.presch[i]=in;
			i++;
			stu.presch[i]='\0';
		}
		
		printf("[ %s ]         \r",stu.presch);
		printf("  School Name ");
	
	}while(in!='\r');

		break ;
		
		case '8' : printf("  Enter changed  twelfth marks (C.G.P.A) ");
				 scanf("%f",&stu.twcgpa);
		break ;
		
		case '9' : printf("  Finished \n");
		break ;
		
		default : printf("  Please Enter Valid Choice \n");
		break ;				
		
	}
		
		}while(choice!='9');
	
		if(stu.fsname[0]>96&&stu.fsname[0]<123)
		{
			stu.fsname[0]=stu.fsname[0]-32;
		}
		
		if(stu.flname[0]>96&&stu.flname[0]<123)
		{
			stu.flname[0]=stu.flname[0]-32;
		}
		
		if(fwrite(&stu,sizeof(struct student),1,fptr))
		{
			printf(" Data successfully Updated \n");
		}
		else
		{
			printf("  Not Updated\n");
		}					
		
	
	
	
	fclose(fptr);
	
}

view_data(char filename[])
{
	top_view();
	
	struct student stu;
	
	FILE *fptr;
	
	fptr=fopen(filename,"r");
	if(fptr==NULL)
	{
		printf("\n  record not found\n");
		return ;
	}
	fread(&stu,sizeof(struct student),1,fptr);
	
	printf("        Student's dtails are given below  :  \n\n");
	printf(" STUDENT's NAME           : %s %s\n",stu.fname,stu.lname);
	printf(" ROLL NUMBER              : %s\n",stu.roll);
	printf(" Date of Birth            : %s\n",stu.dob);
	fflush(stdin);

	printf(" FATHER'S NAME            : %s %s \n",stu.fsname,stu.flname);
	fflush(stdin);
	
	printf(" Contact Number           : %s\n",stu.contact);
	fflush(stdin);
	
	printf(" Permanent Address        : ");
	puts(stu.addr);	
	fflush(stdin);
	
	printf(" Formar School Name       : "); 
	puts(stu.presch);
	printf(" Twelwth score (C.G.P.A)  : %0.2f \n\n",stu.twcgpa);
	
	fclose(fptr);
}

del_rec(char filename[])
{
	
	top_view();
	
	if(remove(filename)==0)
	{
		printf("\n  record successfully deleted \n");
	}
	else
	{
		printf("  Cannot be deleted\n");
		return;
	}
	
	FILE *fp1,*fp2;
	char str[30];
	
	fp1=fopen("records","r");
	fp2=fopen("temperory","w");
	
	while(1)
	{
		fscanf(fp1,"%s",str);
		
		if(feof(fp1))
		{
			break;
		}
		
		if(strcmp(str,filename))
		{
			fprintf(fp2,"%s",str);
			fputc('\n',fp2);	
		}
		
	}
	
	fclose(fp1);
	fclose(fp2);
	
	remove("records");
	rename("temperory","records");
	
}

top_view()
{
	system("cls");
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),
																						 FOREGROUND_RED  |
																						 FOREGROUND_GREEN |
																						 FOREGROUND_BLUE |
																						 FOREGROUND_INTENSITY );
	printf("\n       ****  ALLENHOUSE INSTITUTE OF TECHNOLOGY  ****\n\n");	
	printf("     #####  WELCOME TO STUDENT INFORMATION PORTAL #####\n\n");	
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),
																						 FOREGROUND_RED  |
																						 FOREGROUND_GREEN |
																						 FOREGROUND_BLUE );
	
}

factory_reset()
{

	top_view();

	FILE *fp1,*fp2;	
	struct student stu[5];
	char ch[10],filename[25];

	if((fp1=fopen("records","r"))==NULL)
	{
		printf(" NO Record available \n\n");
	}
	else
	{
	
	while(1)
	{
		fscanf(fp1,"%s",filename);
		
	if(remove(filename)==0)
	{
		printf("\n %s record successfully deleted \n",filename);
	}
	else
	{
		printf(" %s file can't delete\n",filename);
	}
		
		if(feof(fp1))
		{
			break;
		}
		
	}
		
	}
	
		fclose(fp1);

	if(remove("records")==0)
	{
		printf("\n  record FILE successfully deleted \n");
	}
	else
	{
		printf(" Record file can't delete\n");
	}
		
	if(remove("subjects")==0)
	{
		printf("\n  subject FILE successfully deleted \n");
	}
	else
	{
		printf(" Subject file can't delete\n");
	}
	
}

char* file_name()
{
	static char name[36];
	char roll[20];
	
	printf(" Enter Your First Name : ");
	scanf("%s",name);
	
	printf(" Enter Your Roll No. : ");
	scanf("%s",roll);
	
	strlwr(name);
	strlwr(roll);
	
	strcat(name,roll);
	
	return name;
	
}

void copy_right(void)
{
	system("cls");
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),
																					//	 FOREGROUND_RED  |
																						 FOREGROUND_GREEN |
																						 FOREGROUND_BLUE |
																						 FOREGROUND_INTENSITY );
	printf("\n\n\n\tThis Software is Made by Vaibhav Mishra \n");
	printf("\n\tHelp support at vaibhavmishra5013@gmai.com \n\n\n");
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),
																						 FOREGROUND_RED  |
																						 FOREGROUND_GREEN |
																						 FOREGROUND_BLUE );
	getch();
	system("cls");	
	top_view();
	
}

int main(void)
{	
	
	char filename[36],roll[15];
	int choice1=1;
	int choice=1;
	
	top_view();
	
	do{	
		choice=1;
		
		printf(" 1. student login\n");
		printf(" 2. Faculty login\n");
		printf(" 3. Administration\n");
		printf(" 4. Factory Data reset\n");
		printf(" 5. Copyright \n");
		printf(" 6. EXIT \n");
		fflush(stdin);
		printf("    Enter your choice  \n");
		//scanf("%d",&choice);
		
		switch(getch())
		{
			case '1' : 		top_view();
							strcpy(filename,file_name());
							 
							 do
							 {
							 	choice1=1;
		
							 	printf(" 1. My profile\n");
								printf(" 2. Edit profile\n");
								printf(" 3. My scores\n");
								printf(" 4. Go back\n");
								printf("    Enter your choice  \n");
								fflush(stdin);
								//scanf("%d",&choice1);
		
								switch(getch())
								{
									case '1' : view_data(filename);
									break ;
									
									case '2': up_date(filename);
									break ;
									
									case '3' : get_marks(filename);
									break ;
									
									case '4' : choice1=0;
									break ;
									
									default : printf(" Enter valid choice \n");
									
								}
							
							 }while(choice1);
			
			break ;
			
			
			case '2' : 
							top_view();
							 do
							 {
							 	choice1=1;
							 	printf(" 1. View a student's profile\n");
								printf(" 2. Edit a student's profile\n");
								printf(" 3. Academics\n");
								printf(" 4. Upload marks\n");
								printf(" 5. Sort list\n");
								printf(" 6. Create Subjects\n");
								printf(" 7. Go back\n");
								
								printf("\n    Enter your choice  \n");
								fflush(stdin);
		
								switch(getch())
								{
									case '1' : strcpy(filename,file_name());
							 	   		     view_data(filename);
									break ;
									
									case '2' : strcpy(filename,file_name());
							 				 up_date(filename);
									break ;
									
									case '3' : strcpy(filename,file_name());
							 				 acadmics(filename);
									break ;
									
									case '4' : strcpy(filename,file_name());
							 				 add_marks(filename);
									break ;
									
									case '5' : sort_rec();
									break ;
									
									case '6' : create_sub();
									break ;
									
									case '7' : choice1 = 0; 
									break ;
									
									default : printf(" Enter valid choice \n");
									
								}
							
							 }while(choice1);
			
			break ;
			
			case '3' :		top_view();
							 do
							 {
							 	choice1=1;
							 	printf(" 1. Add a student\n");
								printf(" 2. Remove a student\n");
								printf(" 3. Edit a student's profile\n");
								printf(" 4. Search a student\n");
								printf(" 5. Sortlist\n");
								printf(" 6. Go back\n");
								
								printf("    Enter your choice  \n");
								fflush(stdin);
				
								switch(getch())
								{
									case '1' : add_inf();
									break ;
									
									case '2':  strcpy(filename,file_name());
							 				 del_rec(filename);
									break ;
									
									case '3' : strcpy(filename,file_name());
							 				 up_date(filename);
									break ;
									
									case '4' : search_rec();
									break ;
									
									case '5' : sort_rec();
									break ;
									
									case '6' : choice1 =0;
									break ;
									
									default : printf(" Enter valid choice \n");
									
								}
							
							 }while(choice1);
			
			break ;
			
			case '4' : factory_reset();
			break ;
			
			case '5' : copy_right();
			break ;
			
			case '6' : choice=0;
						exit(0);
			
		  default: printf("\n   please enter valid choice\n"); 
		
		}
		
	}while(choice);
	
	return 0;
}
