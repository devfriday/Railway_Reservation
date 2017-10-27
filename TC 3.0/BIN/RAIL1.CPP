#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<process.h>
#include<dos.h>
#include<string.h>
#include<graphics.h>

fstream ms, pn, ti, de, fa, tre, tmp;

unsigned long temp=0;
int temp1=0, d1987, m1987, y1987;
char temp3[20], temp4[20];

void timenu();
void menu();
void pmenu();
void rmenu();
void welcome();
void design(int a);
int isLeap(int yy);
int countDays (int d1, int d2, int m1, int m2, int y1, int y2);

class reservation
{ char senc;
  unsigned long trno;
  int dd, mm, yy, cl, ber, tdd, tmm, tyy;
  char stfr[50], stto[50], boa[50], name[50][50];
  int age[50], km, bill;
  char sex[50], mp;
  unsigned long pnr_no;

  public:
  void reserv();
  void cancel();
  void status();
  void modify();
  void input();
} r;

class pnrno
{ unsigned long pnr;
  public:
  void initialise();
  unsigned long number();
} pr;

class trde
{ unsigned long tr_n;
  char upcity[20][20], tm[20][20];
  int kms[20], num;

  public:
  void initial();
  int search_city(char *sa);
  void search_time(char *sa);
  void display_time();
} det;

class fares
{ int ac, sl;
  public:
  void display();
  int fare_calc(int a);
} fr;

class trtime
{ char tim[50], tr_nam[50], da[100];
  unsigned long tr_no;

  public:
  void getdata();
  void putdata();
  unsigned long s_trno(unsigned long aas, int as);
} trt;

int fares::fare_calc (int a)
{ int y=1, num1, num2, rs;
  fflush(stdin);
  fa.open("fares.tra", ios::binary | ios::in);
  fa.seekp (0, ios::beg);
  while (fa.read ((char*)&fr, sizeof (fares)))
  { if (a == y)
    { if (::temp1 == 1)
	rs=sl;
      else if (::temp1 == 2)
	rs=ac;
    }
  y++;
  }
  fa.close();
  return (rs);
}

void fares::display()
{ int y=1, count=1, num1, num2;
  fflush(stdin);
  fa.open("fares.tra", ios::binary | ios::in);
  fa.seekp (0, ios::beg);
  cout<<"\nEnter the range in which you want to view the fares (<2000): ";
  cout<<"\nEnter the lower limit? ";
  cin>>num1;
  cout<<"\nEnter the upper limit? ";
  cin>>num2;
  cout<<"\n  Kms\t\tSl\t\tAC\n";
  while (fa.read ((char*)&fr, sizeof (fares)))
  { if (y >= num1 && y <= num2)
    { cout<<"\n  "<<y<<"\t\t"<<sl<<"\t\t"<<ac<<endl;
      count++;
    }
    if (count == 15)
    { getch();
      count = 1;
      cleardevice();
      cout<<"\n  Kms\t\tSl\t\tAC\n";
    }
    y++;
  }
  fa.close();
  getch();
}

void trde::display_time()
{ unsigned long no;
  char uui;
  st:
  cleardevice();
  gotoxy (20, 3); cout<<"Enter the Train number: ";
  cin>>no;
  cleardevice();
  int f1 = trt.s_trno(no, 11);
  if (f1==1)
  { cout<<"\n\n\n\t\tTrain not present";
    getch();
    cout<<"\n\t\tDo you want to return to main menu? ";
    cin>>uui;
    if (uui != 'y')
      goto st;
  }
  de.open ("trde.tra", ios::binary | ios::in);
  de.seekp (0, ios::beg);
  while (de.read ((char*)&det, sizeof (trde)))
  { if (no == tr_n)
    { gotoxy (2,10); cout<<"City";
      gotoxy (13,10); cout<<"Time";
      gotoxy (22,10); cout<<"Distance";
      for (int j=0, gt=12; j<num; j++)
      { gotoxy (2, gt); cout<<upcity[j];
	gotoxy (13, gt); cout<<tm[j];
	gotoxy (22, gt); cout<<kms[j];
	gt++;
      }
    }
  }
  de.close();
  getch();
}

void trde::initial ()
{ cleardevice();
  cout<<"\nEnter the train number: ";
  cin>>tr_n;
  cout<<"Enter the number of cities on the way of the train: ";
  cin>>num;
  cout<<"Enter the names of the cities:\n";
  for (int i=0; i<num; i++)
  { cout<<endl<<i+1<<". Name: ";
    gets (upcity[i]);
    cout<<i+1<<". Kms: ";
    cin>>kms[i];
    cout<<i+1<<". Time: ";
    cin>>tm[i];
  }
  de.open ("trde.tra", ios::binary | ios::app);
  de.seekg (0, ios::end);
  de.write ((char*)&det, sizeof(trde));
  de.close();
}

void trde::search_time(char *sa)
{ fflush (stdin);
  de.open ("trde.tra", ios::binary | ios::in);
  de.seekp (0, ios::beg);
  while (de.read ((char*)&det, sizeof (trde)))
  { if (::temp == tr_n)
    { for (int yt=0; yt<det.num; yt++)
      { if (strcmpi (upcity [yt], sa)==0)
	{ cout<<"\nTime of departure of train: "<<tm[0];
	  cout<<"\nTime of reaching your destination is: "<<tm[yt];
	  goto pp;
	}
      }
    }
  }
  pp:
  de.close();
}

int trde::search_city(char *sa)
{ int f=1, yt=0;
  fflush (stdin);
  de.open ("trde.tra", ios::binary | ios::in);
  de.seekp (0, ios::beg);
  while (de.read ((char*)&det, sizeof (trde)))
  { if (::temp == tr_n)
    { for (yt=0; yt<det.num; yt++)
      { if (strcmpi (upcity [yt], sa)==0)
	{ f=det.kms[yt];
	  goto pp;
	}
      }
    }
  }
  pp:
  de.close();
  return (f);
}

unsigned long trtime::s_trno(unsigned long aas, int as)
{ int f=1;
  ti.open ("time.tra", ios::binary | ios::in);
  ti.seekp (0, ios::beg);
  while (ti.read ((char*)&trt, sizeof (trtime)))
  { if (aas == tr_no && as == 11)
    { cout<<"\nName of Train: "<<tr_nam;
      cout<<"\nTrain number: "<<tr_no;
      cout<<"\nDays it will run: "<<da<<endl;
      f=0;
      break;
    }
    if (aas == tr_no && as == 12)
    { gotoxy (35, 21);
      cout<<"\nName of Train: "<<tr_nam;
      f=0;
      break;
    }
  }
  if (f == 1)
    cout<<"\n\tWrong train number";
  ti.close();
  return (f);
}

void trtime::getdata()
{ int h;
  cleardevice();
  cout<<"Enter how many data you want to input? ";
  cin>>h;
  for (int l=1; l<=h; l++)
  { cout<<"\nEnter the name of the train: ";
    gets (tr_nam);
    cout<<"Enter the train number: ";
    cin>>tr_no;
    cout<<"Enter the timing for the train: ";
    gets (tim);
    cout<<"Enter the days it will run: ";
    gets(da);
  }
  ti.open ("time.tra", ios::binary | ios::app);
  ti.seekg (0, ios::end);
  ti.write ((char*)&trt, sizeof (trtime));
  ti.close();
}

void trtime::putdata()
{ int u=0;
  cleardevice();
  fflush (stdin);
  ti.open("time.tra", ios::binary | ios::in);
  ti.seekp(0, ios::beg);
  while (ti.read ((char*)&trt, sizeof (trtime)))
  { cout<<"\nName:\t"<<tr_nam<<"\nTimings:\t"<<tim;
    cout<<"\nThe days it will run:\t"<<da;
    cout<<"\nTrain number:\t"<<tr_no<<endl;
    u++;
    if (u>4)
    { cout<<"\n\t\tPress any key to continue!";
      u=0;
      getch();
      cleardevice();
    }
  }
  getch();
  ti.close();
}

void reservation::modify()
{ cleardevice();
  unsigned long tmp;
  char ch;
  int i=0, f=1;
  gotoxy (20, 5); cout<<"\nEnter the pnr number of the ticket to be modified? ";
  cin>>tmp;
  fflush(stdin);
  ms.open ("reser.tra", ios::binary | ios::in | ios::out);
  ms.seekp (0, ios::beg);
  while (ms.read((char*)&r, sizeof (reservation)))
  { if (pnr_no == tmp)
    { f=0;
      cout<<"\n\n\t\t\tTicket found!";
      cout<<"\n\n\t\tAre you sure you want to modify(y/n)? ";
      cin>>ch;
      if (ch == 'y')
      {  r.input();
	 int off=i*sizeof (reservation);
	 ms.seekp(off, ios::beg);
	 ms.write((char*)&r, sizeof (reservation));
      }
      break;
    }
    i++;
  }
  ms.close();
  if (f!=0)
  { cout<<"\n\n\t\t\tTicket not found!";
    getch();
  }
}

void reservation::status()
{ cleardevice();
  unsigned long ch, prno, io = 0;
  ddds:
  gotoxy (25, 6);
  cout<<"<<<< Passenger Status >>>>";
  cout<<"\n\n\n\t\t\t1. Know status all passenger";
  cout<<"\n\n\t\t\t2. Know status through PNR";
  cout<<"\n\n\t\t\t3. Return to Main Menu";
  cout<<"\n\n\n\t\t\tEnter choice? ";
  design (5);
  cin>>ch;
  if (ch !=1 && ch != 2 && ch != 3)
  { cout<<"\n\t\t\tWrong choice";
    getch();
    cleardevice();
    goto ddds;
  }
  if (ch == 2)
  { cleardevice();
    gotoxy (1,5);
    cout<<"Enter the PNR number of the passenger whose Status you want to know? ";
    cin>>prno;
    fflush(stdin);
    ms.open ("reser.tra", ios::binary | ios::in);
    ms.seekp (0, ios::beg);
    while (ms.read((char*)&r, sizeof (reservation)))
    { if (pnr_no == prno)
      { cleardevice();
	gotoxy (17,1);
	cout<<"Indian Railways\t\tHappy journey";
	gotoxy (2,3);
	cout<<"PNR number:";
	gotoxy (2,4);
	cout<<pnr_no;
	gotoxy (18,3);
	cout<<"Train No.:";
	gotoxy (18,4);
	cout<<trno;
	gotoxy (30,3);
	cout<<"Date:";
	gotoxy (30,4);
	cout<<dd<<"-"<<mm<<"-"<<yy;
	gotoxy (42,3);
	cout<<"Kms:";
	gotoxy (42,4);
	cout<<km;
	gotoxy (48, 3);
	cout<<"Passengers:";
	gotoxy (48, 4);
	cout<<ber;
	gotoxy (23, 6);
	cout<<"Journey cum reservation ticket";
	gotoxy (14, 9);
	cout<<"From: "<<stfr<<"\t\tTo: "<<stto;
	gotoxy (2,12);
	cout<<"Name of passengers";
	gotoxy (24, 12);
	cout<<"Age";
	gotoxy (31, 12);
	cout<<"Sex:";
	gotoxy (39, 12);
	cout<<"Berth";
	for (int jk = 13; jk<13+ber; jk++)
	{ gotoxy (2, jk);
	  cout<<name[jk-13];
	  gotoxy (24, jk);
	  cout<<age[jk-13];
	  gotoxy (31, jk);
	  cout<<sex[jk-13];
	  gotoxy (39, jk);
	  cout<<"Berth";
	}
	gotoxy (49, 15);
	cout<<"You have to pay Rs. "<<bill;
	int u=trt.s_trno(trno, 12);
	~u;
	det.search_time (stto);
	struct date d;
	getdate (&d);
	io=1;
	getch();
      }
    }
    ms.close();
  }
  if (ch == 1)
  { fflush(stdin);
    ms.open ("reser.tra", ios::binary | ios::in);
    ms.seekp (0, ios::beg);
    while (ms.read((char*)&r, sizeof (reservation)))
    {   cleardevice();
	::temp=trno;
	gotoxy (17,1);
	cout<<"Indian Railways\t\tHappy journey";
	gotoxy (2,3);
	cout<<"PNR number:";
	gotoxy (2,4);
	cout<<pnr_no;
	gotoxy (18,3);
	cout<<"Train No.:";
	gotoxy (18,4);
	cout<<trno;
	gotoxy (30,3);
	cout<<"Date:";
	gotoxy (30,4);
	cout<<dd<<"-"<<mm<<"-"<<yy;
	gotoxy (42,3);
	cout<<"Kms:";
	gotoxy (42,4);
	cout<<km;
	gotoxy (48, 3);
	cout<<"Passengers:";
	gotoxy (48, 4);
	cout<<ber;
	gotoxy (23, 6);
	cout<<"Journey cum reservation ticket";
	gotoxy (14, 9);
	cout<<"From: "<<stfr<<"\t\tTo: "<<stto;
	gotoxy (2,12);
	cout<<"Name of passengers";
	gotoxy (24, 12);
	cout<<"Age";
	gotoxy (31, 12);
	cout<<"Sex:";
	gotoxy (39, 12);
	cout<<"Berth";
	for (int jk = 13; jk<13+ber; jk++)
	{ gotoxy (2, jk);
	  cout<<name[jk-13];
	  gotoxy (24, jk);
	  cout<<age[jk-13];
	  gotoxy (31, jk);
	  cout<<sex[jk-13];
	  gotoxy (39, jk);
	  cout<<"Berth";
	}
	gotoxy (49, 15);
	cout<<"You have to pay Rs. "<<bill;
	int u=trt.s_trno(trno, 12);
	~u;
	det.search_time (stto);
	struct date d;
	getdate (&d);
	io=1;
	getch();
    }
    ms.close();
  }
  if (io == 0 && ch != 3)
  { cout<<"\n\n\t\t\tMember not found!";
    getch();
  }
}

void pnrno::initialise()
  { cout<<"Enter the number? ";
    cin>>pnr;
    pn.open ("pnr_no.tra", ios::binary | ios::out);
    pn.seekg(0, ios::beg);
    pn.write((char*)&pr, sizeof (pnrno));
    pn.close();
  }

unsigned long pnrno::number()
{ fflush (stdin);
  pn.open ("pnr_no.tra", ios::binary | ios::in);
  tre.open("temptt", ios::binary | ios::out);
  pn.seekp (0, ios::beg);
  tre.seekg (0, ios::beg);
  pn.read ((char*)&pr, sizeof (pnrno));
  pnr -= 13;
  tre.write ((char*)&pr, sizeof (pnrno));
  pn.close();
  tre.close();
  remove ("pnr_no.tra");
  rename ("temptt", "pnr_no.tra");
  return (pnr);
}

void reservation::reserv()
{ char yu;
  struct date d;
  getdate (&d);
  tdd = d.da_day;
  tmm = d.da_mon;
  tyy = d.da_year;
  cleardevice();
  gotoxy (10, 9); cout<<"Do you know the train number and place where you want to go";
  gotoxy (10, 11); cout<<"If not then type 'n'  and know it by the train schedule menu";
  gotoxy (17, 13); cout<<"or type 'y' to continue: ";
  cin>>yu;
  if (!(yu == 'n'))
  { r.input();
    fflush (stdin);
    ms.open ("reser.tra", ios::binary | ios::app);
    ms.seekg (0, ios::end);
    ms.write ((char*)&r, sizeof (reservation));
    ms.close();
  }
}

void reservation::input()
{ cleardevice();
  gotoxy(24, 3);
  cout<<"Fill up the following form";
  gotoxy(26, 4);
  cout<<"Central Railways";
  aa:
  cout<<"\n\nAre you a senior citizen (y/n)? ";
  cin>>senc;
  if (senc != 'y' && senc !='n')
  { cout<<"\n\t\tWrong input";
    goto aa;
  }
  bb:
  cout<<"\nEnter the train number? ";
  cin>>trno;
  int f1 = trt.s_trno(trno, 11);
  if (f1==1)
    goto bb;
  ::temp = trno;
  cc:
  cout<<"\nEnter the Date of your journey separated by spaces (dd mm yy)? ";
  cin>>dd>>mm>>yy;
  struct date dt;
  getdate(&dt);
  int tmpmon=dt.da_mon;
  int tmpdate=dt.da_day;
  int tmpyea=dt.da_year;
  int chec1987=countDays (tmpdate, dd, tmpmon, mm, tmpyea, yy);
  if (chec1987==0)
  {	cout<<"\n\nEnter Correct Date!!!\n\n";
	goto cc;
  }
  else
  {     if (y1987!=0 || m1987>2 || (m1987==2 && d1987!=0))
	{	cout<<"\nYou can't reserve in advance more than 2 months";
		goto cc;
	}
  }
  uyt:
  cout<<"\nClass:\t1. Sleeper\n     \t2. AC\nEnter choice? ";
  cin>>cl;
  if (cl != 1 && cl != 2)
  { cout<<"\n\tWrong data";
    goto uyt;
  }
  ::temp1 = cl;
  ddd:
  cout<<"\nNumber of berths / seats? ";
  cin>>ber;
  if (ber > 6)
  { cout<<"\n You can book only 6 berths\n";
    goto ddd;
  }
  cout<<"\nStation from: Bhopal";
  strcpy (stfr, "Bhopal");
  asd:
  cout<<"\nStation to: ";
  gets (stto);
  km = det.search_city(stto);
  if (km == 1)
  { cout<<"\nThis station is not present in the train's route\n";
    km=0;
    goto asd;
  }
  cout<<"\nBoarding at: ";
  gets (boa);
  cout<<"\n\n\nEnter the name, age and sex:\n";
  for (int i=0; i<ber; i++)
  { cout<<"\nPassenger number "<<i+1;
    cout<<"\nName: ";
    gets (name[i]);
    cout<<"\nAge: ";
    cin>>age[i];
    yti:
    cout<<"\nSex (f/m): ";
    cin>>sex[i];
    if (sex[i] != 'm' && sex[i] != 'f')
    { cout<<"\n\t\tWrong input\n";
      goto yti;
    }
  }
  cout<<"\nAre you an medical practitioner (y/n)? ";
  cin>>mp;
  bill = fr.fare_calc(km) * ber;
  pnr_no = pr.number();
  cleardevice();
  gotoxy (17,1);
  cout<<"Indian Railways\t\tHappy journey";
  gotoxy (2,3);
  cout<<"PNR number:";
  gotoxy (2,4);
  cout<<pnr_no;
  gotoxy (18,3);
  cout<<"Train No.:";
  gotoxy (18,4);
  cout<<trno;
  gotoxy (30,3);
  cout<<"Date:";
  gotoxy (30,4);
  cout<<dd<<"-"<<mm<<"-"<<yy;
  gotoxy (42,3);
  cout<<"Kms:";
  gotoxy (42,4);
  cout<<km;
  gotoxy (48, 3);
  cout<<"Passengers:";
  gotoxy (48, 4);
  cout<<ber;
  gotoxy (23, 6);
  cout<<"Journey cum reservation ticket";
  gotoxy (13, 9);
  cout<<"From: "<<stfr<<"\t\tTo: "<<stto;
  gotoxy (2,12);
  cout<<"Name of passengers ";
  gotoxy (24, 12);
  cout<<"Age ";
  gotoxy (31, 12);
  cout<<"Gender";
  gotoxy (39, 12);
  cout<<"Berth";
  for (int jk = 13; jk<13+ber; jk++)
  { gotoxy (2, jk);
    cout<<name[jk-13];
    gotoxy (24, jk);
    cout<<age[jk-13];
    gotoxy (31, jk);
    cout<<sex[jk-13];
    gotoxy (39, jk);
    cout<<"Alloted";
  }
  gotoxy (49, 15);
  cout<<"You have to pay Rs. "<<bill;
  int u=trt.s_trno(trno, 12);
  ~u;
  det.search_time (stto);
  cout<<"\n\nNote:-";
  gotoxy (2, 27);
  cout<<"\nPlease note down your ticket's PNR as it will be required for other operation";
  getch();
}

void reservation::cancel()
{ unsigned long pir, f=0;
  cleardevice();
  gotoxy (1,8); cout<<"Enter the PNR number of the ticket which is to be cancelled: ";
  cin>>pir;
  ms.open ("reser.tra", ios::binary | ios::in);
  tmp.open ("temptt", ios::binary | ios::out);
  ms.seekp (0, ios::beg);
  tmp.seekg (0, ios::beg);
  while (ms.read ((char*)&r, sizeof (reservation)))
  { if (pnr_no != pir)
      tmp.write ((char*)&r, sizeof (reservation));
    else if (pnr_no == pir)
      f=1;
  }
  tmp.close();
  ms.close();
  remove ("reser.tra");
  rename ("temptt", "reser.tra");
  if (f == 1)
  {  gotoxy (25, 11); cout<<"Ticket cancelled";
  }
  else
  {  gotoxy (25, 11); cout<<"Wrong PNR number";
  }
  getch();
}

void main()
{ clrscr();
  /* request auto detection */
  int gdriver = DETECT, gmode, errorcode;
  /* initialize graphics and local variables */
  initgraph(&gdriver, &gmode, "");
  cleardevice();
  welcome();
  menu();
  getch();
}

void menu()
{ int ch;
  struct date e;
  getdate (&e);
  st:
  cleardevice();
  setcolor(14);
  for (int ii=10; ii<631; ii+=10)
  { ellipse (ii, 40, 0, 360, 20, 15);
    ellipse (ii, 440, 0, 360, 20, 15);
  }
  setcolor(2);
  for (ii=10; ii<470; ii=ii+10)
  { ellipse (80, ii, 0, 360, 15, 20);
    ellipse (560, ii, 0, 360, 15, 20);
  }

  int j1=e.da_day, j2=e.da_mon;
  gotoxy (52,5);
  cout<<"Date: "<<j1<<"-"<<j2<<"-"<<e.da_year;
  gotoxy (17, 1);
  cout<<"Welcome to Bhopal Station of Indian Railways";
  gotoxy (20, 6);
  cout<<"<<<<<<<<< Main Menu >>>>>>>>>";
  gotoxy (20, 8);
  cout<<"1. Reservation Menu";
  gotoxy (20, 10);
  cout<<"2. Get Train number and timings";
  gotoxy (20, 12);
  cout<<"3. Train fares";
  gotoxy (20, 14);
  cout<<"4. Know Passenger Status";
  gotoxy (20, 16);
  cout<<"5. Get train schedule";
  gotoxy (20, 18);
  cout<<"6. Add train schedule or timings";
  gotoxy (20, 20);
  cout<<"7. Exit";
  gotoxy (22, 23);
  cout<<"Enter your choice? ";
  cin>>ch;
  if (ch<1 || ch>7 && ch!=420 && ch!=111)
  { cout<<"\n\t\t\tWrong choice\n\t\t\tTry again";
    getch();
    goto st;
  }
  cleardevice();
  switch (ch)
  { case 1: rmenu();
      break;

    case 2: trt.putdata();
      break;

    case 3: fr.display();
      break;

    case 4: r.status();
      break;

    case 5: det.display_time();
      break;

    case 420: timenu();
      break;

    case 111: det.initial();
      break;

    case 6: pmenu();
      break;

    case 7: closegraph();
      exit (0);
  }
  goto st;
}

void design (int a)
{ //cleardevice();
  int t=30;
  for (int o=0; o<4; o++)
  { setcolor (a);
    line (0,t,640,t);
    line (0,480-t,640,480-t);
    t+=3;
  }
  t=30;
  for (o=0; o<4; o++)
  { setcolor (a);
    line (t,0,t,480);
    line (640-t,0,640-t,480);
    t+=3;
  }
}

void rmenu()
{ struct date d;
  getdate (&d);
  int ch;
  st:
  cleardevice();
  design (9);
  gotoxy (7,4);
  int jj1=d.da_day, jj2=d.da_mon;
  cout<<"Date: "<<jj1<<"-"<<jj2<<"-"<<d.da_year;
  gotoxy (20, 6);
  cout<<"<<<<<<<<< Reservation Menu >>>>>>>>>";
  gotoxy (20, 10);
  cout<<"1. Reserve a ticket";
  gotoxy (20, 12);
  cout<<"2. Cancel the ticket";
  gotoxy (20, 14);
  cout<<"3. Modify a ticket";
  gotoxy (20, 16);
  cout<<"4. Return to main menu";
  gotoxy (20, 22);
  cout<<"Enter your choice? ";
  cin>>ch;
  if (ch<1 || ch>4)
  { cout<<"\n\t\t\tWrong choice\n\t\t\tTry again";
    getch();
    goto st;
  }
  cleardevice();
  switch (ch)
  { case 1: r.reserv();
      break;

    case 2: r.cancel();
      break;

    case 3: r.modify();
      break;

    case 4: break;
  }
}

void pmenu()
{ int h, t=30;
  st:
  cleardevice();
  for (int o=0; o<4; o++)
  { setcolor (2);
    line (0,t,640,t);
    line (0,480-t,640,480-t);
    t+=3;
  }
  t=30;
  for (o=0; o<4; o++)
  { setcolor (2);
    line (t,0,t,480);
    line (640-t,0,640-t,480);
    t+=3;
  }
  gotoxy (20,5); cout<<"Edit the files";
  gotoxy (8,8); cout<<"1. Add the train schedule";
  gotoxy (8,10); cout<<"2. Add or display the train timings";
  gotoxy (8,12); cout<<"3. Return to main menu";
  gotoxy (15,17); cout<<"Enter your choice? ";
  cin>>h;
  if ( h==1 )
    det.initial();
  else if (h==2)
    timenu();
  else if (h>3)
  { cout<<"\n\nt\t\tWrong choice";
    goto st;
  }
}

void timenu()
{ int ch;
  st:
  cleardevice();
  cout<<"\n<<<<<< Menu >>>>>>>";
  cout<<"\n1. Display data";
  cout<<"\n2. Input data";
  cout<<"\n3. Exit";
  cout<<"\n\nEnter your choice? ";
  cin>>ch;
  switch(ch)
  { case 1: trt.putdata();
      break;
    case 2: trt.getdata();
      break;
    case 3: break;
  }
  if(ch<3)
    goto st;
  getch();
}

void welcome()
{ cleardevice();
  setcolor(2);
  settextstyle (4, HORIZ_DIR, 8);
  outtextxy (50, 50, "Railway");
  outtextxy (140, 150, "Reservation");
  setcolor(4);
  settextstyle (4,HORIZ_DIR, 4);
  outtextxy (270,320, "Made by:-");
  setcolor(9);
  settextstyle (4,HORIZ_DIR, 4);
  outtextxy (200,350, "Sumit Bhattacharya");
  setcolor(4);
  rectangle (1,1,639,479);
  setcolor(2);
  rectangle (1+3,1+3,639-3,479-3);
  setcolor(1);
  rectangle (1+6,1+6,639-6,479-6);
  setcolor(3);
  rectangle (1+9,1+9,639-9,479-9);
  setcolor(5);
  for (int i=50; i<310; i++)
  {  line (50,130,i,130);
     line (50,130+1,i,131);
     line (50,132,i,132);
     delay (5);
  }
  for (i=140; i<510; i++)
  {  line (140,230,i,230);
     line (140,231,i,231);
     line (140,232,i,232);
     delay (5);
  }
  getch();
}

int isLeap(int yy)
{	if ((yy%4==0 && yy%400!=0 && yy%100!=0) || (yy%4==0 && yy%400==0))
		return 29;
	return 28;
}

int countDays (int d1, int d2, int m1, int m2, int y1, int y2)
{       int flag=0, feb;
	if (y1>y2 || (y1==y2 && m1>m2) || (y1==y2 && m1==m2 && d1>d2))
	{	return 0;
	}
	feb=isLeap(y1);
	int dates[]={ 31, feb, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	y1987=y2-y1;
	m1987=m2-m1;
	if (m1987<0)
	{	y1987--;
		flag=1;
		m1987+=12;
	}
	d1987=d2-d1;
	if (d1987<0)
	{	d1987+=dates[m1-1];
		m1987--;
		if (m1987<0)
			m1987+=12;
		if (flag==0)
			y1987--;
	}
	return 1;
}