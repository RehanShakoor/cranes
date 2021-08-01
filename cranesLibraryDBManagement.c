#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char displayMainMenu();  /*this function display main menu*/
void login();            /*this function will login existing user*/
void newAccount();       /*this funciton will create new account*/
char readLastUserId();   /*this function will read last user id from userDatabase.txt*/
void studentDashboard(char,char*,char*); /*this function display dashborad based on user details*/
void waitForInput();     /*this funtion halts our program*/


/*global variables*/

int main()
{
	while(1)
	{
		char choice=displayMainMenu();
		
		switch(choice)
		{
		   case '1': login();
		             break;
		             
		   case '2': newAccount();
		             break;
		             
		   case '3': printf("\n--------------------------------------------------------\n\n");
		   	     exit(2);
		   	     
		   default : printf("Invalid choice, please enter a valid choice\n");
		             break; 
		}
	}
	return 0;
}

void waitForInput()
{
	printf("\nPress any key to continue");
	getchar();
}

char displayMainMenu()
{
	printf("\n---------------Welcome to Cranes Library----------------\n\n");
	printf("1) Login\n");
	printf("2) Create new account\n");
	printf("3) Exit\n\n");
	printf("Enter your choice : ");
	char choice=0;
	choice=getchar();
	return choice;
}

void login()
{
	/*taking login credentials*/
	
	char loginStatus=0; 
	
	struct loginData /*this will store login input data from user*/
	{
		char name[11],password[11]; /*maximum size is 10*/
	};
	
	struct userDbData /*this will store read data from "userDatabase.txt" file*/
	{
		char id;
		char name[11],password[11];          /*maximum size is 10*/	
	};
	
	struct loginData logData;
	struct userDbData dbData;
	
	printf("\n------------------------Login---------------------------\n\n");
	HERE1 : printf("Enter user name : ");
	scanf("%s",logData.name);
	printf("Enter password : ");
	scanf("%s",logData.password);
	getchar();
	
	/*fetching data from user data base to check whether name and password are correct or not*/
	
	FILE *userDbPtr=fopen("userDatabase.txt","r");
	if(fgetc(userDbPtr)==EOF) /*user database is empty*/
	{
		printf("\nData base is empty\n");
		printf("First created a account, then login\n");
	}
	else
	{
		fseek(userDbPtr,133,SEEK_SET);               /*file ptr is moved to first user name (position is calclulated)*/
		dbData.id=readLastUserId()-'0';              /*lastUserId*/
		
		while(ftell(userDbPtr)<=120+(dbData.id)*80)  /*get out of loop if file ptr goes out of EOF*/
		{
			fgets(dbData.name,11,userDbPtr);     /*reading name from data base*/
			fseek(userDbPtr,4,SEEK_CUR);
			fgets(dbData.password,11,userDbPtr); /*reading password from data base*/
			for(char i=9;i>=0;i--)               /*this will replace all the space at end with null character, this will help in strcmp*/
			{
				if(dbData.name[i]==' ')
				{
					dbData.name[i]='\0';
				}
				else
				{
				}
				
				if(dbData.password[i]==' ')
				{
					dbData.password[i]='\0';
				}
				else
				{
				}	
			}
			if(strcmp(dbData.name,logData.name)==0 && strcmp(dbData.password,logData.password)==0)
			{
				printf("\nLogin succesfully !!\n");
				loginStatus=1;
				break;
			}
			else
			{
				fseek(userDbPtr,56,SEEK_CUR); /*file ptr is moved to next user name (position is calclulated)*/
			}	
		}
		
		if(loginStatus==0)
		{
			printf("\nERROR : Incorrect login credentials\n");
		}
		else
		{
		}
	}
	
	printf("\n--------------------------------------------------------\n");
	
	waitForInput();
	
	if(loginStatus==1)
	{
		studentDashboard(dbData.id,dbData.name,dbData.password); /*after login dashboard is displayed*/
	}
	else
	{
		fclose(userDbPtr);
	}
}

void newAccount() 
{
	/***Taking new user data***/
	char nameLen=0,passLen=0;
	struct userData
	{
		char userId;
		char name[11],password[11]; /*maximum size is 10*/
	};
	
	struct userData newUserData;
	char reEnterPassword[11];
	
	newUserData.userId=1+(readLastUserId()-'0'); /*new userId is lastUserId + 1*/
	
	printf("\n------------------Create new Account--------------------\n\n");
	printf("Instructions\n\n");
	printf("1) max. length of name and password is 10\n");
	printf("2) no space in between name and password\n\n");
	
	HERE1 : printf("Enter name : ");
	scanf("%s",newUserData.name);
	getchar();
	
	nameLen=strlen(newUserData.name);
	
	if(nameLen>10)
	{
		printf("\nERROR : length of name is greater than 10, re-enter name\n\n");
		
		goto HERE1;
	}
	else
	{
		/*checking whether new user name is unique or not*/
	
		FILE *userDbPtr=fopen("userDatabase.txt","r");
		
		if(fgetc(userDbPtr)==EOF) /*user database is empty*/
		{
			printf("\nData base is empty\n");
			printf("First created a account, then login\n");
			
		}
		else
		{        
			char dbname[11],dbId=0;                      /*this will store name and id read from db*/				
			
			fseek(userDbPtr,133,SEEK_SET);               /*file ptr is moved to first user name (position is calclulated)*/
			dbId=readLastUserId()-'0';                   /*lastUserId*/
			
			while(ftell(userDbPtr)<=120+(dbId)*80)  /*get out of loop if file ptr goes out of EOF*/
			{
				fgets(dbname,11,userDbPtr);          /*reading name from data base*/
				for(char i=9;i>=0;i--)               /*this will replace all the space at end with null character, this will help in strcmp*/
				{
					if(dbname[i]==' ')
					{
						dbname[i]='\0';
					}
					else
					{
					}	
				}
				if(strcmp(dbname,newUserData.name)==0)
				{
					printf("\nERROR : %s already exits\n\n",newUserData.name);
					goto HERE1;
				}
				else
				{
					fseek(userDbPtr,70,SEEK_CUR); /*file ptr is moved to next user name (position is calclulated)*/
				}	
			}
			fclose(userDbPtr);	
		}
	}
	
	HERE2 : printf("Enter new password : ");
	scanf("%s",newUserData.password);
	passLen=strlen(newUserData.password);
	if(passLen>10)
	{
		printf("\nERROR : length of password is greater than 10, re-enter password\n\n");
		goto HERE2;
	}
	else
	{
		printf("Re-enter new password : ");
		scanf("%s",reEnterPassword);
		getchar();
		if(strcmp(newUserData.password,reEnterPassword)==0)
		{
			printf("\nNew account is created succesfully!!\n\n");
			printf("New Account details\n\n");
			printf("User ID : %d\n",newUserData.userId);
			printf("Username : %s\n",newUserData.name);
			printf("Password : %s\n",newUserData.password);
		}
		else
		{
			printf("\nERROR : Re-enter password doesn't match new password entered, re-enter name\n\n");
			goto HERE1;	
		}
	}

	/***writing new user data to userDatabase.txt***/
	
	FILE *userDbPtr=fopen("userDatabase.txt","a"); 
	fprintf(userDbPtr,"| %d       |",newUserData.userId); /*writing user ID*/
	fprintf(userDbPtr,"| ");  /*writing user name*/
	for(char i=0;i<nameLen;i++)
	{
		fprintf(userDbPtr,"%c",newUserData.name[i]);
	}
	for(char i=1;i<=(10-nameLen);i++) /*writing space*/
	{
		fprintf(userDbPtr," ");
	}
	fprintf(userDbPtr," || ");
	for(char i=0;i<passLen;i++)  /*writing user password*/
	{
		fprintf(userDbPtr,"%c",newUserData.password[i]);
	}
	for(char i=1;i<=(10-passLen);i++) /*writing space*/
	{
		fprintf(userDbPtr," ");
	}
	fprintf(userDbPtr," |\n");
	fprintf(userDbPtr,"---------------------------------------\n");
	fclose(userDbPtr);
	printf("\n--------------------------------------------------------\n");
	
	waitForInput();
}

char readLastUserId()
{
	char lastUserId='0';
	FILE *userDbPtr=fopen("userDatabase.txt","a+");
	if(fgetc(userDbPtr)==EOF) /*if file is empty then a header is added*/
	{
		fprintf(userDbPtr,"---------------------------------------\n");
		fprintf(userDbPtr,"| User ID || Name       || Password   |\n");
		fprintf(userDbPtr,"---------------------------------------\n");
	}
	else
	{
		fseek(userDbPtr,-78,SEEK_END); /*file ptr is moved to last user id (position is calclulated)*/
		lastUserId=fgetc(userDbPtr);   /*last user id is stored in global variable 'lastUserId'*/	
	}
	fclose(userDbPtr);
	return lastUserId;
}

void studentDashboard(char id, char *name, char *password)
{
	char choice=0;
	
	struct bookNode
	{
		char bookId;
		char bookName[21];
		char bookAuthor[21];
		char bookContent[201];
		struct bookNode *nextBookNode;
		struct bookNode *prevBookNode;
	};

	struct bookNode *firstBookNode=NULL;
	struct bookNode *lastBookNode=NULL;

	HERE1 : printf("\n------------------Student Dashboard---------------------\n");
	printf("\nWelcome %s !!\n\n",name);
	printf("Following options are provided\n\n");
	printf("1) View your profile\n");
	printf("2) Open your library\n");
	printf("3) Exit dashboard\n\n");
	printf("Enter your choice : ");
	
	scanf("%c",&choice);
	getchar();
	
	if(choice=='1')
	{
		printf("\n---------------------Profile View-----------------------\n\n");
		printf("User Id   : %d\n",id);
		printf("User name : %s\n",name);
		printf("Password  : %s\n",password);
		printf("\n--------------------------------------------------------\n");
		waitForInput();
		goto HERE1;
	}
	else if(choice=='2') /*code for library using double linked list*/
	{
		char choice=0;
		
		HERE2 : printf("\n------------------------Library-------------------------\n");
		printf("\nLibrary is implemented using double Linked list\n\n");
		printf("Following operations can be done on library\n\n");
		printf("1) Add a new book\n");
		printf("2) Open a book\n");
		printf("3) Open list of books\n");
		printf("4) Delete a book\n");
		printf("5) Exit from library\n\n");
		printf("Enter your choice : ");
		
		scanf("%c",&choice);
		getchar();
		
		if(choice=='1') /*code for adding a new book*/
		{
			char newBookId=0;
			char newBookName[21];
			char newBookAuthor[21];
			char newBookContent[201];
			char choice=0;
			
			printf("\n-----------------------Add a book-----------------------\n");
			printf("\nInstructions\n\n");
			printf("1) Max. length of name and author is 20 characters\n");
			printf("2) Max. length of content is 200 characters\n\n");
			printf("Enter new book id : ");
			scanf("%c",&newBookId);
			getchar();
			printf("Enter new book name : ");
			fgets(newBookName,21,stdin);
			printf("Enter name of author : ");
			fgets(newBookAuthor,21,stdin);
			printf("Enter content of new book : ");
			fgets(newBookContent,201,stdin);
			
			struct bookNode *newBookNode=(struct bookNode *)malloc(sizeof(struct bookNode));
			
			newBookNode->nextBookNode=NULL;
			newBookNode->prevBookNode=NULL;
			
			newBookNode->bookId=newBookId;
			strcpy(newBookNode->bookName,newBookName);
			strcpy(newBookNode->bookAuthor,newBookAuthor);
			strcpy(newBookNode->bookContent,newBookContent);
			
			HERE3 : printf("\nWhere to add this book?\n\n");
			printf("1) Add at start\n");
			printf("2) Add at middle\n");
			printf("3) Add at end\n\n");
			printf("Enter your choice : ");
			scanf("%c",&choice);
			getchar();
			
			if(choice=='1')
			{
				if(firstBookNode==NULL) /*linked list is empty*/
				{
					firstBookNode=newBookNode;
					lastBookNode=newBookNode;
				}
				else
				{
					newBookNode->nextBookNode=firstBookNode;
					firstBookNode->prevBookNode=newBookNode;
					firstBookNode=newBookNode;
				}
				printf("\n\nNew book is added at the begining of the list, book name : %s",newBookName);
			}
			else if(choice=='2')
			{	
				char addBookId=0;
				printf("\nEnter book id : ");
				scanf("%c",&addBookId);
				getchar();
				
				struct bookNode *tempBookNode=firstBookNode;
				
				if(firstBookNode==NULL)
				{
					printf("\n\nERROR : Can't add at middle\n");
					printf("Linked list is empty\n");
				}
				else
				{
					while(tempBookNode->bookId!=addBookId)
					{
						tempBookNode=tempBookNode->nextBookNode;
						if(tempBookNode==NULL)
						{
							printf("\n\nERROR : Can't find book of id : %c\n",addBookId);
							goto HERE3;
						}
						else
						{
						}
					}
					
					if(tempBookNode->nextBookNode==NULL) /*same as add at last*/
					{
						tempBookNode->nextBookNode=newBookNode;
						newBookNode->prevBookNode=tempBookNode;
						lastBookNode=newBookNode;				
					}
					else
					{
						newBookNode->nextBookNode=tempBookNode->nextBookNode;
						tempBookNode->nextBookNode->prevBookNode=newBookNode;
						newBookNode->prevBookNode=tempBookNode;
						tempBookNode->nextBookNode=newBookNode;
					}
					
					printf("\nNew book added, book name : %s",newBookName);
					printf("Added after, book name : %s",tempBookNode->bookName);
				}
				
			}
			else if(choice=='3')
			{
				struct bookNode *tempBookNode=lastBookNode;
				
				if(lastBookNode==NULL)
				{
					firstBookNode=newBookNode;
					lastBookNode=newBookNode;
				}
				else
				{
					tempBookNode->nextBookNode=newBookNode;
					newBookNode->prevBookNode=tempBookNode;
					lastBookNode=newBookNode;
				}
				printf("\n\nNew book is added at the last of the list, book name : %s",newBookName);
							
			}
			else
			{
				printf("\n\nInvalid choice\n");
				goto HERE3;
			}
			
			printf("\n--------------------------------------------------------\n");
			
			waitForInput();
			
			goto HERE2;
		}
		else if(choice=='4') /*delete a book*/
		{
			char choice=0;
			
			HERE4 : printf("\n----------------------Delete a book---------------------\n\n");
			
			if(firstBookNode==NULL)
			{
				printf("Library is empty\n");
			}
			else
			{
			
				printf("From where to delete?\n\n");
				printf("1) Delete from front\n");
				printf("2) Delete from end\n");
				printf("3) Delete from mid\n");
				
				printf("\nEnter your choice : ");
				choice=getchar();
				getchar();
				
				if(choice=='1')
				{
					struct bookNode *tempBookNode=firstBookNode;
					
					printf("\nFront book is deleted, book name : %s",firstBookNode->bookName);
					firstBookNode=tempBookNode->nextBookNode;
					firstBookNode->prevBookNode=NULL;
					free(tempBookNode);
					
				}
				else if(choice=='2')
				{
					struct bookNode *tempBookNode=lastBookNode;
					
					printf("\nLast book is deleted, book name : %s",lastBookNode->bookName);
					lastBookNode=lastBookNode->prevBookNode;
					lastBookNode->nextBookNode=NULL;
					free(tempBookNode);

				}
				else if(choice=='3')
				{
					char deleteBookId=0;
					printf("\nEnter book id : ");
					deleteBookId=getchar();
					getchar();
					
					struct bookNode *tempBookNode=firstBookNode;
					
					while(tempBookNode->bookId!=deleteBookId)
					{
						tempBookNode=tempBookNode->nextBookNode;
						if(tempBookNode==NULL)
						{
							printf("\nERROR : Can't find book of id : %c\n",deleteBookId);
							goto HERE4;
						}
						else
						{
						}
					}
					
					if(tempBookNode==lastBookNode) /*same as delete at last*/
					{
						printf("\nLast book is deleted, book name : %s",lastBookNode->bookName);
						lastBookNode=lastBookNode->prevBookNode;
						lastBookNode->nextBookNode=NULL;
						free(tempBookNode);							
					}
					else
					{
						struct bookNode *tempBookNode2=tempBookNode->nextBookNode;
						
						printf("\nBook Deleted after, book name : %s",tempBookNode->bookName);
						printf("\nBook deleted, book name : %s",tempBookNode->nextBookNode->bookName);
						
						tempBookNode->nextBookNode=tempBookNode2->nextBookNode;	
						tempBookNode2->nextBookNode->prevBookNode=tempBookNode;
							
						free(tempBookNode2);
					}		
				}
				else
				{
					printf("\nInvalid input\n");
					goto HERE4;			
				}
			
			}
			printf("\n--------------------------------------------------------\n");
			
			waitForInput();
			
			goto HERE2;
		}
		else if(choice=='3')
		{
			printf("\n---------------------List of books----------------------\n\n");
			
			struct bookNode *tempBookNode=firstBookNode;
			
			if(tempBookNode==NULL)
			{
				printf("Your library is empty, please add some books\n\n");
			}
			else
			{
				while(tempBookNode!=NULL)
				{
					printf("Book Id : %c\n",tempBookNode->bookId);
					printf("Book name : %s",tempBookNode->bookName);
					printf("Book author : %s\n",tempBookNode->bookAuthor);
					tempBookNode=tempBookNode->nextBookNode;
				}
			}
		
			printf("--------------------------------------------------------\n");
			
			waitForInput();
			
			goto HERE2;
		}
		else if(choice=='2') /*code for open a book*/
		{
			char openBookId=0;
			char bookFoundFlag=1;
			
			printf("\n---------------------Open a book----------------------\n");
			printf("\nEnter the book id : ");
			openBookId=getchar();
			getchar();
			
			struct bookNode *tempBookNode=firstBookNode;
			
			if(tempBookNode==NULL)
			{
				printf("\nLibrary is empty\n");
			}
			else
			{
				while(tempBookNode->bookId!=openBookId)
				{
					tempBookNode=tempBookNode->nextBookNode;
					
					if(tempBookNode==NULL)
					{
						bookFoundFlag=0;
						break;
					}
					else
					{
					}
				}
				
				if(bookFoundFlag==0)
				{
					printf("Can't find the book, with id = %c\n",openBookId);
				}
				else
				{
					printf("\nBook found\n");
					printf("Book name : %s",tempBookNode->bookName);
					printf("Book author : %s",tempBookNode->bookAuthor);
					printf("Book content : \n%s",tempBookNode->bookContent);
				}
			}
		
			printf("\n--------------------------------------------------------\n");
			
			waitForInput();
			
			goto HERE2;
			
		}
		else if(choice=='5')
		{
			printf("\n--------------------------------------------------------\n");
			goto HERE1;
		}
		else
		{
			printf("\nInvalid entry\n");
			goto HERE2;
		}
			
	}
}
