#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<fstream.h>
#include<math.h>


/*==============//DECLARATION OF CLASS //=================================*/
class account
{
    private:
        char customerName[20],acc_type;
        int account_num;
        double balance, pre_transaction,deposite;

        public:
/*================//FUNCTION TO CREATE ACCOUNT//==========================*/
        void create_account()
        {
        cout<<endl<<"========================================="<<endl;
	    cout<<"ENTER THE CUSTOMER NAME:";
	    cout<<endl<<"========================================="<<endl;
		gets(customerName);
		if(customerName=="")
			cout<<"Please enter your name";

	    cout<<endl<<"========================================="<<endl;
	    cout<<"ENTER THE NEW ACCOUNT NUMBER:";
	    cout<<endl<<"========================================="<<endl;
	    cin>>account_num;
	    cout<<endl<<"========================================="<<endl;
	    cout<<"CHOOSE THE ACCOUNT TYPE:"<<endl<<"S FOR SAVING ACCOUNT"<<endl<<"C FOR CURRENT ACCOUNT";
    	cout<<endl<<"========================================="<<endl;
		cin>>acc_type;
			if (acc_type!='s' && acc_type!='S' && acc_type!='c' && acc_type!='C' ) {
			cout<<"Invalid! Please Choose S FOR SAVING ACCOUNT or C FOR CURRENT ACCOUNT"<<endl;
			cin>>acc_type;
		}

		


	    clrscr();
	    cout<<endl;
	    cout<<endl;
	    cout<<endl;
	    cout<<endl;
	    cout<<endl;
	    cout<<endl<<"\t\t========================================="<<endl;
	    cout<<"\t\t\t!ACCOUNT HAS BEEN CREATED!"<<endl<<endl<<"\t\t       YOUR ACCOUNT NUMBER IS : "<<account_num<<endl<<endl<<"\t\t   ACCOUNT HOLDER'S NAME : "<<customerName<<endl;
	    cout<<"\t\t========================================="<<endl;
	    balance=0;
            }
//FUNCTION TO SHOW HEADING WHILE ACCESSING THE EXISTING ACCOUNT //====
        void Heading()
        {
                clrscr();
                cout<<"\t\t     ==================================="<<endl;
				cout<<"\t\t\t\t"<<customerName<<endl;
				cout<<"\t\t\t\tACCOUNT NO.:"<<account_num<<endl;
				if(acc_type=='C'  || acc_type=='c')
				cout<<"\t\t\t\tCURRENT ACCOUNT"<<endl;
				else {
				cout<<"\t\t\t\tSAVING ACCOUNT"<<endl;
				cout<<"\t\t     ==================================="<<endl<<endl;
				}

	    }

/*//=========FUNCTION TO SHOW THE DETAILS OF ACCOUNT HOLDER//============*/
   void show_account()
	{
	    cout<<"\n=========================================="<<endl;
		cout<<"\nACCOUNT NO.              : "<<account_num;
		cout<<"\nACCOUNT HOLDERS NAME     : "<<customerName;
		cout<<"\nTYPE OF ACCOUNT          : ";
			if(acc_type=='C'|| acc_type=='c')
				cout<<"CURRENT ACCOUNT"<<endl;
				else
				cout<<"SAVING ACCOUNT"<<endl;
		cout<<"\nBALANCE AMOUNT           : "<<balance;
		cout<<"\n=========================================="<<endl;
	}

//====FUNCTION TO RETURN AC/NO, BALANCE AND PREVIOUS TRANSACTION.//=====
        int retacno()
        {
            return account_num;
            }

        double retrun_deposite()
        {
            return balance;
            }

        double return_previous()
        {
            return pre_transaction;
            }

//===========FUNCTION TO SHOW THE LIST OF ACCOUNT HOLDER//=============
        void report()
	   {
		    cout<<account_num<<"\t"<<customerName;
            if(acc_type=='C'|| acc_type=='c')
				cout<<"\t\t   CURRENT ACCOUNT";
				else
				cout<<"\t\t   SAVING ACCOUNT";
                cout<<"\t\t"<<balance<<endl;
            }

//======FUNCTION TO DEPOSITE AMOUNT IN BALANCE (CALCULATION PART)//=======
void deposit (double amount)
        {
            if(amount!=0)
            {
            balance = balance + amount;
	        pre_transaction = amount;
	        cout<<endl;
	        cout<<"==================================="<<endl;
    		cout<<"AMOUNT HAS BEEN DEPOSITED"<<endl;
    		cout<<"==================================="<<endl;
            }
        }

//=====FUNCTION TO WITHDRAW AMOUNT FROM BALANCE (CALCULATION PART) //=====
        void withdraw(double amount)
        {
            if(amount!=0&&amount<=balance)
                {
                    balance = balance - amount;
	                pre_transaction= -amount;
                    cout<<endl;
           	        cout<<"==================================="<<endl;
    		        cout<<"AMOUNT HAS BEEN WITHDRAWN"<<endl;
    		        cout<<"==================================="<<endl;
    		        cout<<endl;
                }
        else
                {
                    cout<<"\t\t!!SORRY ACCOUNT DOESN'T HAVE SUFFECIENT BALANCE!!";
                    cout<<endl;
                }

        }
    };
//===================END OF CLASS SCOPE. //===============================

//=======GLOBAL DECLARACTION OF FILE OBJECT AND CLASS OBJECT//===========
    fstream fp;
    account ac;

//======FUNCTION TO WRITE CREATED ACCOUNT IN FILE CALLING FUCNCTION TO CREATE ACCOUNT UNDER THE CLASS SCOPE//====
    void write_account()
    {
        fp.open("account.dat",ios::out|ios::app|ios::binary);
	    ac.create_account();
	    fp.write((char*)&ac,sizeof(account));
	    fp.close();
        }

//===========FUNCTION TO READ CREATED ACCOUNT IN FILE CALLING FUCNCTION TO SHOW ACCOUNT HOLDERS DETAIL UNDER THE CLASS SCOPE//==================
    void display_sp(int n)
    {
        cout<<"=========================================="<<endl;
	    cout<<"\t====BALANCE DETAILS====";

        int flag=0;
	    fp.open("account.dat",ios::in|ios::binary);
    	while(fp.read((char*)&ac,sizeof(account)))
	       {
		      if(ac.retacno()==n)
		      {
			     ac.show_account();
			     flag=1;
		      }
	       }

	   fp.close();
	   if(flag==0)
	   cout<<"\n\nACCOUNT NUMBER DOESN'T EXIST";
    }

//===========FUNCTION TO READ CREATED ACCOUNT DETAILS AND SHOW AFTER ACCESSING EXISTING ACCOUNT CALLING HEADING FUNCTION //=====
    int welcome(int n)
    {
        int flag=0;
	    fp.open("account.dat",ios::in|ios::out|ios::binary);
	    while(fp.read((char*)&ac,sizeof(account)))
	   {
		    if(ac.retacno()==n)
		  {
			ac.Heading();
			flag=1;
		  }
	   }
	       fp.close();
	       if(flag==0)
		cout<<"\n\n\t\t\tACCOUNT NUMBER DOESN'T EXIST";
		return flag;
    }

//==FUNCTION TO DELETE ACCOUNT FROM FILE USING READ AND WRITE MODE//====
    void delete_account()
        {
	        int no,flag=0;
	        cout<<"\n\n====Delete Record====";
	        cout<<"\n\nEnter The Account No. : ";
            cin>>no;
	        fp.open("account.dat",ios::in|ios::out|ios::binary);
	        fstream fp2;
	        fp2.open("Temp.dat",ios::out|ios::binary);
	        fp.seekg(0,ios::beg);
	        while(fp.read((char*)&ac,sizeof(account)))
	           {
		            if(ac.retacno()!=no)
		              {
			             fp2.write((char*)&ac,sizeof(account));
		              }
					else
						flag=1;
	           }
			
	        fp2.close();
	        fp.close();
	        remove("account.dat");
	        rename("Temp.dat","account.dat");
			if (flag == 0)
				cout<<"Record not found"<<endl;
			else
	        	cout<<"\n\n\tRECORD DELETED ..";
	       getch();
        }

//========FUNCTION TO WRITE IN FILE WHILE CALLING DEPOSITE AND WITHDRAW FUNCTION FROM CLASS SCOPE//====================
    void deposit_withdraw(int option,int n)
        {
	        int found=0;
            double amt;

	        fp.open("account.dat",ios::in|ios::out|ios::binary);
	        while(fp.read((char*)&ac,sizeof(account)) && found==0)
	           {
		          if(ac.retacno()==n)
		                {
			                 ac.show_account();
			                 if(option==1)
			                     {
				                        cout<<"\n\nENTER THE AMOUNT TO DEPOSIT : ";
				                        cin>>amt;
							ac.deposit(amt);
			                             cout<<"\n\nRECORD UPDATED";
			                     }
			                 else if(option==2)
			                     {
				                        cout<<"\n\nENTER THE AMOUNT TO WITHDRAW : ";
				                        cin>>amt;
				                        ac.withdraw(amt);
				                        cout<<"\n\nRECORD UPDATED";
			                     }
							else
								cout<<"Wrong option selected!"<<endl;

			                 int pos=-1*sizeof(ac);
			                 fp.seekp(pos,ios::cur);
			                 fp.write((char*)&ac,sizeof(account));

			                 found=1;
		                  }
	               }
	       fp.close();
	       if(found==0)
		  cout<<"\n\n RECORD NOT FOUND ";
	       getch();
        }

//========FUNCTION TO READ PREVIOUS TRANSACTION FROM THE FILE USING FUNCTION OF RETRUNING PREVIOUS TRANSACTION OF CLASS SCOPE//==========
    void getpre_Transaction(double n)
        {

	       double t;
	       int flag=0;
	       fp.open("account.dat",ios::in|ios::binary);
	       while(fp.read((char*)&ac,sizeof(account)))
	       {
		      if(ac.retacno()==n)
		          {
			         ac.return_previous();
                    {
                        if(ac.return_previous()>0)
                            {
                                cout<<"\t\t\t       DEPOSITED: "<<+ac.return_previous();
                            }
                        else if(ac.return_previous()<0)
                            {
                                cout<<"\t\t\t       WITHDRAWN: "<<abs(ac.return_previous());
                            }
                        else
                            {
                                cout<<"\t\t\tNO TRANSACTION OCCURED";
                            }
                    }
			         flag=1;
		            }
    	   }
	        fp.close();
       	    if(flag==0)
		    cout<<"\n\nACCOUNT NUMBER DOESN'T EXIST";

        }

//===========FUNCTION TO READ CREATED ACCOUNT CREATED ACCOUNT LIST FROM THE FILE CALLING FUNCTION FROM CLASS SCOPE//==================
    void display_all()
        {
	       fp.open("account.dat",ios::in|ios::binary);
	       if(!fp)
	           {
		          cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		          getch();
	           }
	               cout<<"\n\n\t\t\t\tACCOUNT HOLDER LIST\n\n";
	               cout<<"============================================================\n";
	               cout<<"A/c no.\tNAME\t\t\t\tType\t\t\tBalance\n";
	               cout<<"==============================================================\n";
	               while(fp.read((char*)&ac,sizeof(account)))
	            {
		          ac.report();
	            }
	           fp.close();
	           cout<<"\n\n\n---PRESS ANY KEY TO CONTINUE...---";
	       getch();

        }

//================MAIN FUNCTION OF THE PROGRAM WHERE SWITCH CASE IS GIVEN AS MEANU AND RUN THE ALL THE FUNCTION AVAILABLE.//=======================



void WELCOME()
{
    clrscr();
    cout<<"\t\t=================================================="<<endl<<endl;
    cout<<"\t\t\t   BANK MANAGEMENT SYSTEM"<<endl;
    cout<<"\t\t\t           BY"<<endl;
    cout<<"\t\t\t       Adya Singh"<<endl;
    cout<<"\t\t=================================================="<<endl;
    cout<<"\n\n\n\t\t\t====PRESS ANY KEY TO CONTINUE====";
    getch();

    }

	void main()
{

int ch, ch1, temp,i,p;
WELCOME();
do{
	clrscr();
	cout<<"\t\t     ==================================="<<endl;
	cout<<"\t\t\t\tMAIN MENU"<<endl;
	cout<<"\t\t     ==================================="<<endl<<endl;
	cout<<"\t\t\t01. CREATE NEW ACCOUNT"<<endl<<endl;
	cout<<"\t\t\t02. ACCESS EXISTING ACCOUNT"<<endl<<endl;
	cout<<"\t\t\t03. CLOSING AN ACCOUNT"<<endl<<endl;
	cout<<"\t\t\t04. LIST OF ACCOUNT HOLDERS"<<endl<<endl;
	cout<<"\t\t\t05. EXIT"<<endl<<endl;
	cout<<"\t\t     ==================================="<<endl;
	cout<<"\t\t     ||PLEASE SELECT YOUR OPTION (1-5)||"<<endl;
	cout<<"\t\t     ==================================="<<endl;
	ch=getch();

	switch(ch)
	{
        case '1':   clrscr();
	                write_account();
                    getch();
			        break;


            case '2':   clrscr();
                clrscr();
                cout<<"\t\t     ==================================="<<endl;
				cout<<"\t\t\t   Enter the Account Number "<<endl;
				cout<<"\t\t     ==================================="<<endl;
				cin>>temp;
				p=welcome(temp);
				if(p==0)
				{
				    cout<<"\n\n\n\t\t   ---PRESS ANY KEY TO CONTINUE...---";
				    getch();
				    break;
                    }
				else
    {
        	do{
			    clrscr();
		        welcome(temp);
				cout<<"\t\t\t01. CHECK BALANCE"<<endl<<endl;
				cout<<"\t\t\t02. DEPOSITE AMOUNT"<<endl<<endl;
				cout<<"\t\t\t03. WITHDRAW AMOUNT"<<endl<<endl;
				cout<<"\t\t\t04. PREVIOUS TRANSACTION"<<endl<<endl;
				cout<<"\t\t\t05. EXIT"<<endl<<endl;
				cout<<"\t\t     ==================================="<<endl;
				cout<<"\t\t     ||PLEASE SELECT YOUR OPTION (1-5)||"<<endl;
				cout<<"\t\t     ==================================="<<endl;
				ch1=getch();

			switch(ch1)
			{
		case '1':	clrscr();
			display_sp(temp);
			cout<<"\n\n\n---PRESS ANY KEY TO CONTINUE...---";
			getch();
			break;
		case '2': clrscr();
		    deposit_withdraw(1,temp);
		    cout<<"\n\n\n-----PRESS ANY KEY TO CONTINUE-----"<<endl<<endl;
            getch();
			break;
		case '3': clrscr();
		    deposit_withdraw(2,temp);
		    cout<<"\n\n\n-----PRESS ANY KEY TO CONTINUE-----"<<endl<<endl;
            getch();
			break;
		case '4': clrscr();
			cout<<"\t\t     ==================================="<<endl;
            getpre_Transaction(temp);
            cout<<"\n\t\t     ==================================="<<endl;
            cout<<"\n\n\n\t\t\t-----PRESS ANY KEY TO CONTINUE-----"<<endl<<endl;
            getch();
			break;
		case '5':	goto last;
		default :       clrscr();
					cout<<"\t\t\t-----Invalid Choice!!!-----"<<endl<<endl;
					cout<<"\t\t\tPRESS ANY KEY TO CONTINUE....."<<endl;
					getch();

			}

			}while(ch1!=5);

	}		    last:
                    cout<<endl;
                cout<<"\t\t     ------PRESS ENTER AGAIN TO EXIT------"<<endl;
                        getch();
			            break;

                case '3':   clrscr();
                            delete_account();
			                break;

                case '4':   clrscr();
                            display_all();
			                break;

                case '5':   cout<<endl<<endl<<endl;
                            cout<<"\t\t     ------PRESS ENTER AGAIN TO EXIT------"<<endl;
                            getch();
                            exit (0);

                                default : clrscr();
					            cout<<"\t\t\t-----INVALID CHOICE!!!-----"<<endl<<endl;
					            cout<<"\t\t\tPRESS ANY KEY TO CONTINUE....."<<endl;
					            getch();
        }
	}while(ch!=5);

getch();
}
