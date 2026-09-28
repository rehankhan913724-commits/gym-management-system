#include<stdlib.h>
#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<string.h>

struct Member
{
int id;
char name[30];
int age;
char membership[20];
int fee;
Member *next;
};

Member *head=NULL;

int fees[3]={1000,2500,8000};

int attendanceID[5];
char attendanceDate[5][20];

int front=-1;
int rear=-1;

void addMember()
{
Member *newMember=new Member;

cout<<"\nEnter Member ID: ";
cin>>newMember->id;

cout<<"Enter Name: ";
cin>>newMember->name;

cout<<"Enter Age: ";
cin>>newMember->age;

cout<<"\n1. Monthly - Rs.1000";
cout<<"\n2. Quarterly - Rs.2500";
cout<<"\n3. Yearly - Rs.8000";

int choice;
cout<<"\nEnter choice: ";
cin>>choice;

if(choice==1)
{
strcpy(newMember->membership,"Monthly");
newMember->fee=fees[0];
}
else if(choice==2)
{
strcpy(newMember->membership,"Quarterly");
newMember->fee=fees[1];
}
else if(choice==3)
{
strcpy(newMember->membership,"Yearly");
newMember->fee=fees[2];
}
else
{
cout<<"Invalid choice!";
delete newMember;
return;
}

newMember->next=NULL;

if(head==NULL)
head=newMember;
else
{
Member *temp=head;

while(temp->next!=NULL)
temp=temp->next;

temp->next=newMember;
}

cout<<"\nMember added successfully!";
}

void displayMembers()
{
Member *temp=head;

if(temp==NULL)
{
cout<<"\nNo members found!";
return;
}

cout<<"\n MEMBERS \n";

while(temp!=NULL)
{
cout<<"\nID: "<<temp->id;
cout<<"\nName: "<<temp->name;
cout<<"\nAge: "<<temp->age;
cout<<"\nMembership: "<<temp->membership;
cout<<"\nFee: Rs."<<temp->fee;
cout<<"\n";

temp=temp->next;
}
}

void searchMember()
{
int id;

cout<<"\nEnter Member ID: ";
cin>>id;

Member *temp=head;

while(temp!=NULL)
{
if(temp->id==id)
{
cout<<"\nMember Found!";
cout<<"\nName: "<<temp->name;
cout<<"\nAge: "<<temp->age;
cout<<"\nMembership: "<<temp->membership;
cout<<"\nFee: Rs."<<temp->fee;
return;
}

temp=temp->next;
}

cout<<"\nMember not found!";
}

void deleteMember()
{
int id;

cout<<"\nEnter Member ID: ";
cin>>id;

Member *temp=head;
Member *previous=NULL;

while(temp!=NULL)
{
if(temp->id==id)
{
if(previous==NULL)
head=temp->next;
else
previous->next=temp->next;

delete temp;

cout<<"\nMember deleted!";
return;
}

previous=temp;
temp=temp->next;
}

cout<<"\nMember not found!";
}

void markAttendance()
{
int id;
char date[20];

if((rear+1)%5==front)
{
cout<<"\nAttendance queue is full!";
return;
}

cout<<"\nEnter Member ID: ";
cin>>id;

Member *temp=head;

while(temp!=NULL)
{
if(temp->id==id)
break;

temp=temp->next;
}

if(temp==NULL)
{
cout<<"\nMember not found!";
return;
}

cout<<"Enter Date (DD/MM/YYYY): ";
cin>>date;

if(front==-1)
{
front=0;
rear=0;
}
else
rear=(rear+1)%5;

attendanceID[rear]=id;
strcpy(attendanceDate[rear],date);

cout<<"\nAttendance marked!";
}

void removeAttendance()
{
if(front==-1)
{
cout<<"\nAttendance is empty!";
return;
}

cout<<"\nRemoved ID: "<<attendanceID[front];
cout<<"\nDate: "<<attendanceDate[front];

if(front==rear)
{
front=-1;
rear=-1;
}
else
front=(front+1)%5;
}

void displayAttendance()
{
if(front==-1)
{
cout<<"\nNo attendance!";
return;
}

cout<<"\n ATTENDANCE\n";

int i=front;

while(1)
{
cout<<"\nMember ID: "<<attendanceID[i];
cout<<"\nDate: "<<attendanceDate[i];
cout<<"\n";

if(i==rear)
break;

i=(i+1)%5;
}
}

void saveData()
{
ofstream file("members.txt");

Member *temp=head;

while(temp!=NULL)
{
file<<temp->id<<" "
<<temp->name<<" "
<<temp->age<<" "
<<temp->membership<<" "
<<temp->fee<<endl;

temp=temp->next;
}

file.close();

cout<<"\nData saved successfully!";
}

void loadData()
{
ifstream file("members.txt");

if(!file)
return;

while(!file.eof())
{
Member *newMember=new Member;

file>>newMember->id
>>newMember->name
>>newMember->age
>>newMember->membership
>>newMember->fee;

if(file.fail())
{
delete newMember;
break;
}

newMember->next=NULL;

if(head==NULL)
head=newMember;
else
{
Member *temp=head;

while(temp->next!=NULL)
temp=temp->next;

temp->next=newMember;
}
}

file.close();
}

void main()
{
int choice;

loadData();

while(1)
{
cout<<"\n GYM MANAGEMENT SYSTEM\n";

cout<<"\n1. Add Member";
cout<<"\n2. Display Members";
cout<<"\n3. Search Member";
cout<<"\n4. Delete Member";
cout<<"\n5. Mark Attendance";
cout<<"\n6. Remove Attendance";
cout<<"\n7. Display Attendance";
cout<<"\n8. Save Data";
cout<<"\n9. Exit";

cout<<"\n\nEnter Choice: ";
cin>>choice;

switch(choice)
{
case 1:
addMember();
break;

case 2:
displayMembers();
break;

case 3:
searchMember();
break;

case 4:
deleteMember();
break;

case 5:
markAttendance();
break;

case 6:
removeAttendance();
break;

case 7:
displayAttendance();
break;

case 8:
saveData();
break;

case 9:
saveData();
cout<<"\n\nThank you!";
exit(0);

default:
cout<<"\nInvalid choice!";
}
}
}