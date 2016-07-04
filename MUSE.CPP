#include<fstream.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define file "record.dat"
struct med
{
	int code,stkor,price;
	char name[30],manuname[30];
   //	char exp[20],mfg[20];
	char bno[20];
	void get();
	void show();
};
void med::get()
{
	 gotoxy(5,4);
	printf("Enter Code :");
	gotoxy(5,6);
	printf("Enter Name :");
	gotoxy(5,8);
	printf("Enter Quantity :");
	gotoxy(5,10);
	printf("Enter Manufacturer Name :");
	gotoxy(5,12);
	printf("Enter Batch No :");
	gotoxy(5,14);
	printf("Enter Price :");
	gotoxy(5,16);

	gotoxy(42,4);
	cin>>code;
	gotoxy(42,6);
	cin>>name;
	gotoxy(42,8);
	cin>>stkor;
	gotoxy(42,10);
	cin>>manuname;
	gotoxy(42,12);
	cin>>bno;
	gotoxy(42,14);
	cin>>price;
	gotoxy(42,16);
}
void med::show()
{
	cout<<"  "<<code<<"\t"<<name<<"\t"<<stkor<<"\t"<<manuname<<"\t"<<bno<<"\t"<<price<<endl;
}
void box()
{
	int i;
	for(i=2;i<78;++i)
	{
		gotoxy(i,1);
		printf("%c",205);
		gotoxy(i,48);
		printf("%c",205);
	}
	for(i=2;i<48;++i)
	{
		gotoxy(1,i);
		printf("%c",186);
		gotoxy(78,i);
		printf("%c",186);
	}
	gotoxy(1,1);
	printf("%c",201);
	gotoxy(78,1);
	printf("%c",187);
	gotoxy(1,48);
	printf("%c",200);
	gotoxy(78,48);
	printf("%c",188);
}
void add()
{
	char c;
	fstream f(file,ios::app);
	med m;
	clrscr();
//	cout<<"CODE/t"<<"NAME/t"<<"STOCK/t";
       //	cout<<"  CODE_NO"<<"  "<<"MEDICINE"<<"   "<<"QUANTITY"<<" "<<"MANUFACTURER"<<"  "<<"BNO."<<"  "<<"PRICE"<<"  "<<"MFG.DATE"<<"  "<<"EXP.DATE"<<endl;
	do
	{
		clrscr();
		m.get();
		f.write((char*)&m,sizeof(m));
		gotoxy(5,22);
		cout<<"  want to add more items?\n     (y/n): \n"<<endl;
		gotoxy(5,24);
		c=getche();
	 }
	 while(c=='y'||c=='Y');
	 f.close();
}
//**************************************************
//FUNCTION TO READ FROM FILE
void show()
{
	med m;
	fstream f(file,ios::in);
	clrscr();
	cout <<"\t                "<< "...........PRODUCT REPORT...........\n" <<endl;
	cout<<"    Code"<<"\t"<<"Medicine"<<"\t"<<"Quantity"<<"\t"<<"Manufacturer"<<" \t"<<"Batch"<<" \t "<<"Price"<<endl<<endl;
	while(f.read((char*)&m,sizeof(m)))
	m.show();
	f.close();
	getch();
}
//*****UPDATE DATA******

void update()
{
	med m;
	int code; //code= to be asked by user
	int n=0;
	clrscr();
	fstream fil;
	gotoxy(2,2);
	cout<<"Enter code of medicine to be updated"<<endl;
	cin>>code;
	fil.open(file,ios::in|ios::out);
//	fstream f1("y.dat",ios::app);
	while(fil.read((char *)&m,sizeof(m)))
	{
		if(m.code==code)
		{
		     //	m.get();
		     fil.seekp(fil.tellg()-sizeof(m),ios::beg);
		     m.get();
		    // pos=(int)fil.tellg() - sizeof(m);
		    // fil.seekp(pos);
			fil.write((char *)&m,sizeof(m));
			n=1;
		}
	}
	fil.close();
       /*	f1.close();
	remove(file);
	rename("y.txt",file);*/
	if(n==1)
	{
		gotoxy(5,32);
		cout<<"Record updated";
	}
	else
	{
		gotoxy(5,32);
		cout<<"Record not found";
	}
	getch();
}
// *******CHECK AVAILABILITY*****************8
void check()
{
	med m;
	int n=0;    //to check availability
	clrscr();
	fstream f(file,ios::in);
	fstream f1("y.txt",ios::out);
	while(f.read((char *)&m,sizeof(m)))
	{
		if(!m.stkor==0)
		{
			f1.write((char*)&m,sizeof(m));
		}
		else
		{

			n=1;
			gotoxy(4,4);
			cout<<m.name <<" is not available";
		}
	}

	f.close();
	f1.close();
	remove(file);
	rename("y.txt",file);
	if(n==0)
	{
		gotoxy(4,4);
		cout<<"Every medicine is Available";
	}
	getch();
}
void findname()
{
	med m;
	char name[10];//to be asked by user
	int n=0;
	clrscr();
	gotoxy(3,3);
	cout<<"Enter name of medicine"<<endl;
	cin>>name;
	fstream f(file,ios::in);
	while(f.read((char *)&m,sizeof(m)))
	{
		if(!strcmp(m.name,name))
		{
				cout<<"    Code"<<"\t"<<"Medicine"<<"\t"<<"Quantity"<<"\t"<<"Manufacturer"<<" \t"<<"Batch"<<" \t "<<"Price"<<endl<<endl;
			m.show();
			n=1;
		}
	}
	f.close();
	if(n==0)
	{                                 	gotoxy(3,5);
		cout<<"Record not found";
	}
	getch();
}
void bill()
{
	med m;
	int code,tc=0,tax,t,qty,item=0;
	char c;//tc=total cost
	clrscr();
	do
	{

	       gotoxy(5,5);
		cout<<"Enter the code of medicines being purchased:";
		cin>>code;
		gotoxy(5,7);
		cout<<"Quantity:";
		cin>>qty;
		item=qty+item;
		fstream f(file,ios::in);
		while(f.read((char *)&m,sizeof(m)))
		{
			if(m.code==code)
			{
				t=m.price*qty;
				tc=t+tc;
				m.stkor=m.stkor-qty;
				break;
			}
			f.close();
		 }
		 gotoxy(5,10);
		cout<<"Want to enter more?(y/n)";
		c=getche();
	}
	while(c=='y'||c=='Y');
	gotoxy(5,13);
	cout<<"$$$$$$$$$$$$ BILL $$$$$$$$$$$$$$"<<endl;
	gotoxy(15,16);
	cout<<endl<<"TOTAL ITEMS:"<<item<<endl;
	gotoxy(15,19);
	cout<<endl<<"TOTAL PRICE"<<tc<<endl;
	tax=tc+((12.5*tc)/100);
	gotoxy(15,22);
	cout<<endl<<"PRICE INCLUDING TAX: "<<tax<<endl<<endl;
	gotoxy(5,26);
	cout<<"====== THANKS FOR VISITING ======"<<endl;
	getch();
}

void data()
{
	char c;
	textcolor(15);
	textbackground(11);
	int i;
	clrscr();
	box();
	for(i=0;i<45;++i)
	{
		gotoxy(5,38);
		cout<<"LOADING";
		gotoxy(10+i,41);
		printf("%c",179);
		delay(60) ;
	}
	while(1)
	{
		clrscr();
		box();
		gotoxy(20,10);
		cout<<"WHAT YOU WANT TO DO?";
		gotoxy(25,14);
		cout<<"1.ADD MORE ITEMS.";
		gotoxy(25,16);
		cout<<"2.DISPLAY THE DATA";
		gotoxy(25,18);
		cout<<"3.CHECK AVAILABILITY ";
		gotoxy(25,20);
		cout<<"4.UPDATE RECORD";
		gotoxy(25,22);
		cout<<"5.FIND AN ITEM";
		gotoxy(25,24);
		cout<<"6.MAKE A BILL";
		c=getche();
		switch(c)
		{
			case '1': add(); 	break;
			case '2': show();	break;
			case '3': check(); 	break;
			case '4': update();	break;
			case '5': findname();	break;
			case '6': bill();	break;
			case '0':exit(0);	break;
			default:exit(0);
		}
	}

	getch();
}
//**********************************************
//THE MAIN FUNCTION OF PROGRAM
void main()
{
	char c;
	textcolor(11);
	textbackground(1);

	while(1)
	{
	clrscr();
	gotoxy(28,15);
	cout<<"MEDICAL SHOP MANAGEMENT ";
       //	gotoxy(50,45);
       //	cout<<"BY:POONAM VASHIST"<<endl;
	gotoxy(7,44);
	cout<<"TO PROCEED PRESS 'p'"<<endl;
	gotoxy(7,45);
	cout<<"TO EXIT PRESS 'e'";
	box();
	c=getche();
	switch(c)
	{
		case 'p':data();       	break;
		case 'e':exit(0);	break;
		default:exit(0);
	}
	}
		getch();

}