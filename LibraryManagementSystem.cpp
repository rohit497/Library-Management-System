#include <iostream.h>
#include<fstream.h>
#include <stdio.h>
#include <string.h>
static int nbook=0, i=1;
static int nmember=0, j=1;
class book
{
private: 
 char name[20], author[20], status;
 int bookno;
 float rating;
public:
book()
{
}

book(int a)
{ cout<<"\n Enter the book's name \t";
  cin.ignore(256,'\n');
  cin.getline(name,20);
  cout<<"\n Enter the author \t";
  cin.getline(author,20);
  cout<<"\n Enter the rating of the book \t";
  cin>>rating;
  bookno = a;
  status = 'y';
}

char getstatus()
{return(status);
}

char* getname()
{return(name);
}

char* getauthor()
{return(author);
}

void changestatus(char stat1)
{status = stat1;
}

int getbookno()
{return(bookno);
}

float getrating()
{return(rating);
}

void display()
{cout<<"\n The book details are \t";
cout<<"\n Name : \t"<<name;
cout<<"\n Author : \t"<<author;
cout<<"\n ID Number : \t"<<bookno;
cout<<"\n Rating : \t"<<rating;
}

};

class member
{private:
char name[20], address[50];
int idno, booksdue;
float deposit;
public:

member()
{
}

member(int n)
{cout<<"\n Enter the member's name \t";
 cin.ignore(256,'\n');
 cin.getline(name,20);
 cout<<"\n Enter the address \t";
 cin.getline(address,50);
 booksdue = 0;
 idno = n;
 deposit = 1000;
}

float getdeposit()
{return(deposit);
}

char* getname()
{return(name);
}

char* getaddress()
{return(address);
}

void updatebooks(int n)
{booksdue = n;
}

void booktrans(int n)
{booksdue = booksdue + n;
}

void adddeposit(int amt)
{ deposit = deposit+amt;
}

void reducedeposit(int amt)
{deposit = deposit-amt;
}

int getbooks()
{return(booksdue);
}

int getidno()
{return(idno);
}

void display()
{cout<<"\n The member details are \t";
cout<<"\n Name : \t"<<name;
cout<<"\n Address : \t"<<address;
cout<<"\n ID Number : \t"<<idno;
cout<<"\n The books due are \t"<<booksdue;
cout<<"\n The remaining deposit is \t"<<deposit;
}

};

void displayall()
{book b;
fstream fdisp("Library.dat",ios::in);
while(fdisp.read((char*)&b,sizeof(b)))
{b.display();
}
fdisp.close();
}

void searchbookrating(float rating)
{int found = 0;
 book b;
fstream libsrat("Library.dat",ios::in); 
while (libsrat.read((char*)&b,sizeof(b)))
{
if(rating == b.getrating())
{found = 1;
b.display();
}
}
if(found == 0)
cout<<"\n There is no book with this rating \t";
}

void searchbookauthor(char auth [20])
{book b;
int found = 0;
fstream libsanam("Library.dat",ios::in); 
while (libsanam.read((char*)&b,sizeof(b)))
{
if(strcmpi(auth,b.getauthor())==0)
{found = 1;
 b.display();
}
}
if(found == 0)
cout<<"\n There is no book by this author \t";
libsanam.close();
}

void searchbookname(char name [20])
{book b;
int found = 0;
fstream libsbnam("Library.dat",ios::in); 
while(libsbnam.read((char*)&b,sizeof(b)))
{
if(strcmpi(name,b.getname())==0)
{found = 1;
 b.display();
}
}
if(found == 0)
cout<<"\n There is no book with this name \t";
libsbnam.close();
}

void searchbookno(int bkno)
{fstream libsno("Library.dat",ios::in); 
int found =0;
book b;
while(libsno.read((char*)&b,sizeof(b)))
{
if(bkno == b.getbookno())
{found = 1;
 b.display();
 break;
}
}
if(found == 0)
cout<<"\n There is no book with this book number \t";
libsno.close();
}

void searchbookstatus(char stat[20])
{int i; 
 char stat1;

 char statusA[]="Available";
 char statusB[] = "Unavailable";
 book b;
 fstream libstat("Library.dat",ios::in);
 
 if(strcmpi(stat,statusA)==0) 
{ stat1 = 'y';
  while(libstat.read((char*)&b,sizeof(b)))
  {
  if(stat1 == b.getstatus())
  b.display();
  }
}
else if(strcmpi(stat,statusB)==0)
{ stat1 = 'n';
 while(libstat.read((char*)&b,sizeof(b)))
 {
 if(stat1 == b.getstatus())
  b.display();

 }
}
}

void delete1(int bookno) 
{ fstream fdel("Library.dat",ios::in);
  fstream fnew("Temp.dat",ios::out);
  book b;
  if(bookno <= nbook)
  {while(fdel.read((char*)&b,sizeof(b)))
   if(bookno != b.getbookno())
    fnew.write((char*)&b,sizeof(b));
  fdel.close();
  fnew.close();
remove("Library.dat");
rename("Temp.dat","Library.dat");
cout<<"\n The updated list is \t";
displayall();
}
else
cout<<"\n No such book exists \t";
}

void create()
{int a; 
 cout<<"\n Enter the number of books \t";
 cin>>a;
 nbook=nbook+a;
 if(nbook-a==0)
 { fstream libout("Library.dat",ios::out);
 for(;i<=nbook;i++)
 {
 book b(i); 
  libout.write((char*)&b,sizeof(b));
 }
libout.close();                                  
displayall();
}
else
{ofstream libout("Library.dat",ios::app);
for(;i<=nbook;i++)
 {
 book b(i); 
 libout.write((char*)&b,sizeof(b));
 }
libout.close();                                  
displayall();
}
}

void updatebook(int bookno)
{book b;
 char stat[20],stat1;
 char statusA[]="Available";
 char statusB[] = "Unavailable";
 fstream fup("Library.dat",ios::in);
 fstream fnew("Temp.dat",ios::out);
 if(bookno <= nbook)
 {while(fup.read((char*)&b,sizeof(b)))
 {
  if(bookno == b.getbookno())
  {cout<<"\n Enter the details \t";
   book b1(bookno);
   cout<<"\n Enter the status \t";
   cin>>stat;
   if(strcmpi(stat,statusA)==0)
   stat1 = 'y';
   else if(strcmpi(stat,statusB)==0)
   stat1 = 'n';
   b1.changestatus(stat1);
   fnew.write((char*)&b1,sizeof(b1));
  }
  else
  fnew.write((char*)&b,sizeof(b));
 }
 fup.close();
 fnew.close();
 remove("Library.dat");
rename("Temp.dat","Library.dat");
cout<<"\n The updated list is \t";
displayall();
}
else
cout<<"\n No such book exists \t";
}

void sortbookno (book b[30])
{ int k,l;
 book temp;
  for(k=0;k<nbook;k++)
   for(l=k+1;l<nbook;l++)
   if(b[k].getbookno()<b[l].getbookno())
   {temp = b[k];
    b[k] = b[l];
    b[l] = temp;
   }
   fstream fwrite("Temp.dat",ios::out);
   for(k=0;k<nbook;k++)
   fwrite.write((char*)&b[k],sizeof(b[k])); 
   fwrite.close();
   remove("Library.dat");
   rename("Temp.dat","Library.dat");
   displayall();
}

void sortrating(book b[30])
{ int k,l;
 book temp;
  for(k=0;k<nbook;k++)
   for(l=k+1;l<nbook;l++)
   if(b[k].getrating()<b[l].getrating())
   {temp = b[k];
    b[k] = b[l];
    b[l] = temp;
   }
    fstream fwrite("Temp.dat",ios::out);
   for(k=0;k<nbook;k++)
   fwrite.write((char*)&b[k],sizeof(b[k])); 
   fwrite.close();
   remove("Library.dat");
   rename("Temp.dat","Library.dat");
   displayall();
}

void sortauthor(book b[30])
{ int k,l;
 book temp;
  for(k=0;k<nbook;k++)
   for(l=k+1;l<nbook;l++)
   if(strcmpi(b[k].getauthor(),b[l].getauthor())>0)
   {temp = b[k];
    b[k] = b[l];
    b[l] = temp;
   }
   fstream fwrite("Temp.dat",ios::out);
   for(k=0;k<nbook;k++)
   fwrite.write((char*)&b[k],sizeof(b[k])); 
   fwrite.close();
   remove("Library.dat");
   rename("Temp.dat","Library.dat");
   displayall();
}

void sortbookname(book b[30])
{ int k,l;
  book temp;
  for(k=0;k<nbook;k++)
   for(l=k+1;l<nbook;l++)
   if(strcmpi(b[k].getname(),b[l].getname())>0)
   {temp = b[k];
    b[k] = b[l];
    b[l] = temp;
   }
   fstream fwrite("Temp.dat",ios::out);
   for(k=0;k<nbook;k++)
   fwrite.write((char*)&b[k],sizeof(b[k])); 
   fwrite.close();
   remove("Library.dat");
   rename("Temp.dat","Library.dat");
   displayall();
}

void sort()
{int k=0,ch;
 book b[30],b1;
 fstream fsort("Library.dat",ios::in);
 while((fsort.read((char*)&b1,sizeof(b1)))&&(k < nbook))
 {b[k] = b1;
 k++;
 }
 fsort.close();
 do 
       {cout<<"\n Sort based on: \t";
        cout<<"\n 1. Name in alphabetical order \t";
        cout<<"\n 2. Book no. in descending order \t";
        cout<<"\n 3. Author in alphabetical order \t";
        cout<<"\n 4. Rating in descending order \t";
        cout<<"\n 5. Exit \t";
        cout<<"\n Enter your choice \t";
        cin>>ch;
        switch(ch)
        {case 1: sortbookname(b);
                 break;
         case 2: sortbookno(b);
                 break;
         case 3: sortauthor(b);
                 break;
         case 4: sortrating(b);
                 break;
         }
        }while(ch<=4);  
}

void bookadmin()
{int chA, a, chAB, bkno, j, found = 0;
float rating; 
char bookname[20], author[20], astat[20];
do
{cout<<"\n Menu \t";
cout<<"\n 1. Add a new book \t";
cout<<"\n 2. Remove a book \t";
cout<<"\n 3. Modify/ Update a book \t";
cout<<"\n 4. Display books \t";
cout<<"\n 5. Search for a book \t";
cout<<"\n 6. Sort \t";
cout<<"\n 7. Exit \t";
cout<<"\n Enter your choice \t";
cin>>chA;
switch(chA)
{
     case 1:create();
            break; 
 case 2:cout<<"\n Enter the number of the book to be deleted \t";
        cin>>bkno;
       delete1(bkno);
        break;
 case 3:cout<<"\n Enter the ID no. of the book whose details are to be modified \t";
        cin>>bkno;
        updatebook(bkno);
        break;
 case 4:displayall();
        break;
case 5: do 
       {cout<<"\n Search  based on: \t";
        cout<<"\n 1. Name \t";
        cout<<"\n 2. Book no. \t";
        cout<<"\n 3. Author \t";
        cout<<"\n 4. Status \t";
        cout<<"\n 5. Rating \t";
        cout<<"\n 6. Exit \t";
        cout<<"\n Enter your choice \t";
        cin>>chAB;
        switch(chAB)
                    {case 1: cout<<"\n Enter the name of the book \t";
                            cin.ignore(256,'\n');
                           cin.getline(bookname,20);
                            searchbookname(bookname);
                            break;
                     case 2: cout<<"\n Enter the number of the book \t";
                            cin>>bkno;
                            searchbookno(bkno); 
                            break; 
                     case 3: cout<<"\n Enter the author of the book \t";
                            cin.ignore(256,'\n');
                            cin.getline(author,20);
                            searchbookauthor(author); 
                             break;
                     case 4: cout<<"\n Enter the status of the book (Available/Unavailable) \t";
                             cin.ignore(256,'\n');
                             cin.getline(astat,20); 
                             searchbookstatus(astat);
                             break;
                     case 5: cout<<"\n Enter the rating of the book \t";
                             cin.ignore(256,'\n');
                             cin>>rating; 
                             searchbookrating(rating); 
                             break;
                    }
                    }while(chAB<=5);
break;
case 6: sort();
}
}while(chA<=6);
}

void displayallmembers()
{member m;
 fstream fdisp("Member.dat",ios::in);
 while(fdisp.read((char*)&m,sizeof(m)))
 m.display();
 fdisp.close();
}

void createmember()
{int a; 
 cout<<"\n Enter the number of members \t";
 cin>>a;
 nmember=nmember+a;
 if(nmember-a==0)
 { fstream fout("Member.dat",ios::out);
 for(;j<=nmember;j++)
 {
 member m(j); 
  fout.write((char*)&m,sizeof(m));
 }
fout.close();                                  
displayallmembers();
}
else
{ofstream fout("Member.dat",ios::app);
for(;j<=nmember;j++)
 {
 member m(j); 
 fout.write((char*)&m,sizeof(m));
 }
fout.close();                                  
displayallmembers();
}
}

void sortmembno (member m[30])
{ int k,l;
 member temp;
  for(k=0;k<nmember;k++)
   for(l=k+1;l<nmember;l++)
   if(m[k].getidno()< m[l].getidno())
   {temp = m[k];
    m[k] = m[l];
    m[l] = temp;
   }
   fstream fwrite("Temp.dat",ios::out);
   for(k=0;k<nmember;k++)
   fwrite.write((char*)&m[k],sizeof(m[k]));
   fwrite.close();
   remove("Member.dat");
   rename("Temp.dat", "Member.dat");
   displayallmembers();
}

void sortbooksdue (member m[30])
{ int k,l;
 member temp;
  for(k=0;k<nmember;k++)
   for(l=k+1;l<nmember;l++)
   if(m[k].getbooks() < m[l].getbooks())
   {temp = m[k];
    m[k] = m[l];
    m[l] = temp;
   }
   fstream fwrite("Temp.dat",ios::out);
   for(k=0;k<nmember;k++)
   fwrite.write((char*)&m[k],sizeof(m[k]));
   fwrite.close();
   remove("Member.dat");
   rename("Temp.dat", "Member.dat");
   displayallmembers();
}

void sortmembername (member m[30])
{  int k,l;
 member temp;
  for(k=0;k<nmember;k++)
   for(l=k+1;l<nmember;l++)
   if(strcmpi(m[k].getname(),m[l].getname())>0)
   {temp = m[k];
    m[k] = m[l];
    m[l] = temp;
   }
   fstream fwrite("Temp.dat",ios::out);
   for(k=0;k<nmember;k++)
   fwrite.write((char*)&m[k],sizeof(m[k]));
   fwrite.close();
   remove("Member.dat");
   rename("Temp.dat", "Member.dat");
   displayallmembers();
}

void searchmembername(char membername [20])
{member m;
 int found = 0;
 fstream fmembname("Member.dat",ios::in);
 while(fmembname.read((char*)&m,sizeof(m)))
 if(strcmpi(membername,m.getname())==0)
 {found = 1;
  m.display();
 }
 if(found==0)
 cout<<"\n There is no member with this name \t";
 fmembname.close(); 
}

void searchmemberno(int memberno)
{ member m;
 int found = 0;
 fstream fmembname("Member.dat",ios::in);
 while(fmembname.read((char*)&m,sizeof(m)))
 if(memberno == m.getidno())
 {found = 1;
  m.display();
 }
 if(found==0)
 cout<<"\n There is no member with this number \t";
 fmembname.close(); 
}

void searchbooksdue(int booksdue)
{ member m;
 int found = 0;
 fstream fmembname("Member.dat",ios::in);
 while(fmembname.read((char*)&m,sizeof(m)))
 if(booksdue == m.getbooks())
 {found = 1;
  m.display();
 }
 if(found==0)
 cout<<"\n There is no member with this many books due \t";
 fmembname.close(); 
}


void delete2(int memberno)
{ fstream fdel("Member.dat",ios::in);
  fstream fnew("Temp.dat",ios::out);
  member m;
  if(memberno <= nmember)
  {while(fdel.read((char*)&m,sizeof(m)))
   if(memberno != m.getidno())
    fnew.write((char*)&m,sizeof(m));
  fdel.close();
  fnew.close();
remove("Member.dat");
rename("Temp.dat","Member.dat");
cout<<"\n The updated list is \t";
displayallmembers();
}
else
cout<<"\n No such member exists \t";
}  

void updatemember(int memberno)
{member m;
 int n;
 fstream fup("Member.dat",ios::in);
 fstream fnew("Temp.dat",ios::out);
 if(memberno <= nmember)
 {while(fup.read((char*)&m,sizeof(m)))
 {
  if(memberno == m.getidno())
  {cout<<"\n Enter the details \t";
   member m1(memberno);
   cout<<"\n Enter the books due \t";
   cin>>n;
   m1.updatebooks(n);
   fnew.write((char*)&m1,sizeof(m1));
  }
  else
  fnew.write((char*)&m,sizeof(m));
 }
 fup.close();
 fnew.close();
 remove("Member.dat");
rename("Temp.dat","Member.dat");
cout<<"\n The updated list is \t";
displayallmembers();
}
else
cout<<"\n No such member exists \t";
}


void searchmemberaddress(char address [50])
{member m;
 int found = 0;
 fstream fmembname("Member.dat",ios::in);
 while(fmembname.read((char*)&m,sizeof(m)))
 if(strcmpi(address,m.getaddress())==0)
 {found = 1;
  m.display();
 }
 if(found==0)
 cout<<"\n There is no member with this address \t";
 fmembname.close(); 
}

void sortmember()
{int k=0,ch;
 member m[30],m1;
 fstream fsort("Member.dat",ios::in);
 while((fsort.read((char*)&m1,sizeof(m1)))&&(k < nmember))
 {m[k] = m1;
 k++;
 }
 fsort.close();
do 
       {cout<<"\n Sort based on: \t";
        cout<<"\n 1. Name in alphabetical order \t";
        cout<<"\n 2. Member no. in descending order \t";
        cout<<"\n 3. Books due in descending order \t";
        cout<<"\n 4. Exit \t";
        cout<<"\n Enter your choice \t";
        cin>>ch;
        switch(ch)
        {case 1: sortmembername(m);
                 break;
         case 2: sortmembno(m);
                 break;
         case 3: sortbooksdue(m);
                 break;
         
         }
        }while(ch<=3);    
}

void membadmin()
{int chM, a, chMN, membno, j, booksdue; 
static int i = 0;
char membname[20], address[50];
do
{cout<<"\n Menu \t";
cout<<"\n 1. Add a new member \t";
cout<<"\n 2. Remove a member \t";
cout<<"\n 3. Modify/ Update a member \t";
cout<<"\n 4. Display member \t";
cout<<"\n 5. Search for a member \t";
cout<<"\n 6. Sort \t";
cout<<"\n 7. Exit \t";
cout<<"\n Enter your choice \t";
cin>>chM;
switch(chM)
{
 case 1: createmember();
        break; 
 case 2:cout<<"\n Enter the number of the member to be deleted \t";
        cin>>membno;
       delete2(membno);
        break;
 case 3:cout<<"\n Enter the ID no. of the member whose details are to be modified \t";
        cin>>membno;
        updatemember(membno);
        break;
 case 4:displayallmembers();
        break;
 case 5: do 
       {cout<<"\n Search  based on: \t";
        cout<<"\n 1. Name \t";
        cout<<"\n 2. Member no. \t";
        cout<<"\n 3. Address \t";
        cout<<"\n 4. Books due \t";
        cout<<"\n 5. Exit \t";
        cout<<"\n Enter your choice \t";
        cin>>chMN;
        switch(chMN)
                    {case 1: cout<<"\n Enter the name of the member \t";
                           cin.ignore(256,'\n');
                           cin.getline(membname,20);
                            searchmembername(membname);
                            break;
                     case 2: cout<<"\n Enter the ID number of the member \t";
                            cin>>membno;
                            searchmemberno(membno); 
                            break; 
                     case 3: cout<<"\n Enter the address of the member \t";
                            cin.ignore(256,'\n');
                            cin.getline(address,50);
                            searchmemberaddress(address); 
                             break;        
                     case 4:cout<<"\n Enter the books due \t";
                            cin>>booksdue;
                            searchbooksdue(booksdue); 
                            break;
                    }
                    }while(chMN<=4);
break;
case 6: sortmember();
         break;   
}
}while(chM<=6);
}

void booktrans()
{member m;
char stat = 'n', stat1 = 'y';
 int mno,ch,n,k,bkno,days,fine,amt;
 do
 { cout<<"\n 1. Borrow Book \t";
   cout<<"\n 2. Return Book \t";
   cout<<"\n 3. Exit \t";
   cout<<"\n Enter your choice \t";
   cin>>ch;
   switch (ch)
   {
          case 1:  cout<<"\n Enter the member no \t";
                   cin>>mno;
               if(mno<=nmember) //if-1
            {fstream ftrans("Member.dat",ios::in); 
             fstream fnew1("Temp1.dat",ios::out);
             ftrans.seekg(0,ios::beg);
              while(ftrans.read((char*)&m,sizeof(m)))//while-1
              {
              if(mno == m.getidno())//if-2
                {
                if((m.getbooks()<4)&&(m.getdeposit()>100))//if-3
                    {cout<<"\n Enter the number of books being borrowed \t";
                    cin>>n;
                    m.booktrans(n);
                    if((m.getbooks() <4)&&(n<=4))//if-4
                      { 
                      for(k=0;k<n;k++)//for-1
                        {cout<<"\n Enter the no. of the book \t";
                       cin>>bkno;
                         if(bkno<=nbook)//if-5
                        {
                        book b;
                         fstream fborrow("Library.dat",ios::in);
                         fstream fnew("Temp.dat",ios::out);
                              while(fborrow.read((char*)&b,sizeof(b)))//while-2
                                  {
                                  if(bkno == b.getbookno())//if-6
                                    {
                                    if(b.getstatus()== 'y')//if-7
                                       {b.changestatus(stat);
                                        fnew.write((char*)&b,sizeof(b));
                                        cout<<"\n This book has successfully been borrowed \t";
                                       }//if-7close
                                        else
                                        {cout<<"\n The book is unavailable \t";
                                        m.booktrans(-1);
                                        }
                                     }//if-6close
                                     else
                                      fnew.write((char*)&b,sizeof(b));
                                   }//while-2 close
                                   fborrow.close();
                                   fnew.close();
                                   remove("Library.dat");
                                   rename("Temp.dat","Library.dat");
                         } //if-5 close
                        else
                        {cout<<"\n There is no such book \t";
                        m.booktrans(-1);
                        }
                        } // for-1 close
                      }  //if-4 close
                      else if((m.getbooks()>=4)&&(n<=4))
                       {m.booktrans(-n);
                       cout<<"\n You can only borrow "<< 4-m.getbooks() <<" more book(s)\t";
                        ftrans.close();
                       }
                       else if(((m.getbooks()-n)<4)&&(n>4))
                       {cout<<"\n You can borrow a maximum of 4 books \t";
                       m.booktrans(-n);
                        ftrans.close();
                       }
                  } //if-3 close
                  else
                   cout<<"\n You have already borrowed 4 books \t";
                   fnew1.write((char*)&m,sizeof(m));
                }//if-2 close
                else
                fnew1.write((char*)&m,sizeof(m));
                } //while-1 close
                ftrans.close();
                fnew1.close();
                remove("Member.dat");
                rename("Temp1.dat","Member.dat");
                }//if-1 close
                else
                cout<<"\n No such member exists \t";
break; 
case 2: cout<<"\n Enter the member no. \t";
        cin>>mno;
        fstream ftrans("Member.dat",ios::in);
        fstream new1("Temp1.dat",ios::out);
        while(ftrans.read((char*)&m,sizeof(m)))//while-1
          {if(mno == m.getidno())   //if-1     
             {cout<<"\n Enter the number of books being returned \t";
              cin>>n;
              m.booktrans(-n);
              for(k=0;k<n;k++)//for-1
              {cout<<"\n Enter the book no \t";
               cin>>bkno;
               if(bkno<=nbook)//if-11
              {book b;
              fstream fborrow("Library.dat",ios::in);
              fstream fnew("Temp.dat",ios::out);
                while(fborrow.read((char*)&b,sizeof(b))) //while-2
                     {if(bkno == b.getbookno()) //if-2
                         {if(b.getstatus() == 'n') //if-3
                               {cout<<"\n Enter the number of days \t";
                                cin>>days;
                                if(days>7)//if-4
                                { fine = 15*(days-7);                                
                                  m.reducedeposit(30+fine);
                                }//if-4 close
                                if(m.getdeposit()<=100)//if-5
                                  {cout<<"\n Please renew your membership \t";
                                   cout<<"\n Enter the amount you wish to add \t";
                                   cin>>amt;
                                   m.adddeposit(amt);
                                   }//if-5 close
                                b.changestatus(stat1);
                                fnew.write((char*)&b,sizeof(b));
                                cout<<"\n This book has been returned \t";
                                } //if-3 close
                           else
                            {cout<<"\n The book was not borrowed \t";
                             m.booktrans(1);
                             }
                         }//if-2 close
                          else
                          fnew.write((char*)&b,sizeof(b));
                     }//while-2 close
                 fborrow.close();
                 fnew.close();
                 remove("Library.dat");
                 rename("Temp.dat","Library.dat");
                 }//if-11 close
                 else   
                 {cout<<"\n No such book exists \t";
                  m.booktrans(1);        
                 } 
                 }//for-1 close
                 new1.write((char*)&m,sizeof(m));
                 }//if-1 close       
                 else
                  new1.write((char*)&m,sizeof(m));
                  }//while-1 close 
                  new1.close();
                 ftrans.close();
                 remove("Member.dat");
                 rename("Temp1.dat", "Member.dat");          
              break;
   }//switch close
}while(ch<=2);
}

                        
 
int main()
{int ch;
do
{cout<<"\n Menu \t";
cout<<"\n 1. Book Administration \t";
cout<<"\n 2. Member Administration \t";
cout<<"\n 3. Book Transaction \t";
cout<<"\n 4. Exit \t";
cout<<"\n Enter your choice \t";
cin>>ch;
switch (ch)
{case 1: bookadmin();
         break;
 case 2: membadmin(); 
         break;  
 case 3: booktrans();
         break;  
}
}while(ch<=3);
}
