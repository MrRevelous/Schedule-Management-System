//*********************************************************************
//            	Header Files Used(AS PER THE C++11 STANDARD)
//*********************************************************************
#include<iostream>
#include<fstream>
#include<conio.h>
#include<string>
#include<iomanip>
#include<algorithm>
#include<windows.h>
#include<limits>
#include<cstdlib>
using namespace std;
//*********************************************************************
//                   Class used In The Programme
//*********************************************************************
class faculty
{
   public:
   int e_id;
   char name[25];
   char gender;
   char sub[10];
   char desg[5];
   char attendance_status=' ';
   int class_room_no[8];
   void faculty_list_casual() const
   {
     cout<<"\n\t"<<e_id;setw(30);cout<<"\t\t"<<sub;cout<<"\t\t"<<desg;setw(30);cout<<"\t\t"<<attendance_status;setw(30);cout<<"\t\t"<<name;
   }
   void all_faculty_list() const
   {
      cout<<"\n\t"<<e_id;cout<<"\t\t"<<sub;cout<<"\t\t"<<desg;cout<<"\t\t"<<name;
   }
   void print_data() const
   {
         cout<<"\n\tFaculty Id   : ";cout<<e_id<<endl;
         cout<<"\n\tFaculty Name : ";cout<<name<<endl;
         cout<<"\n\tGender       : ";cout<<gender<<endl;
         cout<<"\n\tDesignation  : ";cout<<desg<<endl;
         cout<<"\n\tSubject      : ";cout<<sub<<endl;
         cout<<"\n\tAtt. Status  : ";cout<<attendance_status<<endl;
         cout<<"\n\n\t\t\t   Time Table\n";
         cout<<"\n\t\t  Period\t\tRoom No.\n";
         for(int j=0;j<8;++j)
         {
            cout<<"\n\t\t  Period "<<j+1<<"\t=>\t"<<class_room_no[j];
         }
   }
   void display_schedule() const
   {
       cout<<"\n  "<<e_id;
       for(int i=0;i<8;++i)
       {
           cout<<"\t"<<class_room_no[i];
       }
   }
   int get_e_id() const//Accessor Function
   {
       return e_id;
   }
   void retrn_gndr()
   {
       if(gender=='M'||gender=='m')
        cout<<"Mr.";
       else
        cout<<"Ms.";
   }
}; //Class Ends Here
//*********************************************************************
//        Declaration Of Global Variables,Class & Stream Objects
//*********************************************************************
ifstream x;
ofstream y;
ifstream u;
ofstream v;
ifstream p;
ofstream q;
faculty t,T,f1;
//int total_class_rooms[1000];
//*********************************************************************
//              Declaration Of  Global Functions & Variables
//*********************************************************************
void get_fdata();
void attendance();
void view_sngl();
void generate_rg_f_schedule();
void generate_rg_cr_schedule();
void generate_tschedule();
void generate_ctime_table();
int a_size=0,p_size=0;
//*********************************************************************
//                     Function Definitions
//*********************************************************************
//***********************************************************
//          Functions To Input New Faculty Record
//***********************************************************
void get_fdata()
{
    system("cls");
    cout<<"*********************************************************************\n";
    cout<<"                          Record Intake Module                       \n";
    cout<<"*********************************************************************\n";
    cout<<"\n\n\tFaculty ID   : \t";
    while (!(std::cin >>t.e_id))
    {
        std::cin.clear(); // clears the error flags
                          // this line discards all the input waiting in the stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"\n\t\tError: Please Enter An Integer Value!!!"<<std::endl;
        getch();
        get_fdata();

    }
    x.open("fdata.dat",ios::in|ios::binary);
    while(x.read(reinterpret_cast<char*>(&T),sizeof(T)))//To check Duplicate ID
    {
        if(t.e_id==T.get_e_id())
        {
            cout<<"\n\t\tError: ID Already Exists!!!";
            cout<<"\n\tPlease Try Again...";
            getch();
            x.close();
            get_fdata();
        }
    }
    x.close();
    cout<<"\n\tName         : \t";
    cin.ignore();
    gets(t.name);cout<<endl;
    cout<<"\n\tGender[M/F]  : \t";
    cin>>t.gender;cout<<endl;
    cout<<"\n\tSubjects     : \t";
    cin.ignore();
    gets(t.sub);cout<<endl;
    cout<<"\n\tDesignation  : \t";
    gets(t.desg);cout<<endl;
   m:cout<<"\n\tEnter Schedule Now:-\n";
    for(int i=0;i<8;++i)
    {
       p:cout<<"\n\tPeriod "<<i+1;
        cout<<"\t=>\tRoom No. : ";
        while (!(std::cin >>t.class_room_no[i]))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout<<"\n\t\tError: Please Enter An Integer Value!!!"<<std::endl;
            getch();
            goto p;
        }
        x.open("fdata.dat",ios::in|ios::binary);
        while(x.read(reinterpret_cast<char*>(&T),sizeof(T)))//To Avoid Clashes
        {
            if(t.class_room_no[i]!=100&&t.class_room_no[i]==T.class_room_no[i])
            {
                cout<<"\n\tError: Clash Detected!!!\n";
                cout<<"\n\tEntered Class Room No. Clashes With:\n";
                cout<<"\n\t"<<"ID:"<<T.e_id<<"   Name:   "<<T.name<<"'s"<<"\n\tPeriod No.=>"<<i+1;
                cout<<"\n\tPlease Check The Class Room No. And Then Enter The Schedule Again...\n";
                x.close();
                getch();
                goto p;
            }
        }
        x.close();
    }
    int cnt=0;
    for(int i=0;i<8;++i)
    {
        if(t.class_room_no[i]==100)
            ++cnt;
    }
    if(cnt<2)
    {
        cout<<"\n\n\tWarning: A Faculty Must Have At least 2 Free Periods!!!";
        cout<<"\n\n\t\tEnter The Schedule Again...\n";
        getch();
        goto m;
    }
    else
    {
        y.open("fdata.dat",ios::out|ios::app|ios::binary);
        y.write(reinterpret_cast<char*>(&t),sizeof(t));
        y.close();
        cout<<"\n\n\tRecord Entry Successfull!!!...";
    }
    char ch;
    cout<<"\n\n\tDo You Wish To Enter More Records???[Y/N]...";
    cin>>ch;
    if(ch=='y'||ch=='Y')
        get_fdata();
    else
        return;
}//End Of Function
//***********************************************************
//         Function To Get The List Of All Faculties
//***********************************************************
void list_all_faculties()
{
    x.open("fdata.dat",ios::in|ios::binary);
    if(!x)
       {
	    cout<<"Error:File Not Found!!!";
	    return;
       }
    cout<<"*********************************************************************\n";
	cout<<"                         All Faculties' Record                       \n";
    cout<<"*********************************************************************\n";
    cout<<"\n\tFaculty ID\tSubjects\tDesignation\tName";
    while(x.read(reinterpret_cast<char*>(&t),sizeof(faculty)))
    {
	  t.all_faculty_list();
    }
    x.close();
    return;
}//End Of Function
//***********************************************************
//       Function To Get The List Of Present Faculties
//***********************************************************
void list_prsnt_faculties()
{
    x.open("present_staff.dat",ios::in|ios::binary);
    if(!x)
    {
        cout<<"\n\n\t\tError:File Not Found!!!\n";
        cout<<"\n\n\tPlease Take The attendance First...";
        return;
    }
    cout<<"*********************************************************************\n";
	cout<<"                     Present Faculties' Record                       \n";
    cout<<"*********************************************************************\n";
    cout<<"\n\tFaculty ID\tSubjects\tDesignation\tAtt. Status\tName";
    while(x.read(reinterpret_cast<char*>(&t),sizeof(t)))
    {
        t.faculty_list_casual();
    }
    x.close();
    return;
}//End Of Function
//***********************************************************
//       Function To Get The List Of Absent Faculties
//***********************************************************
void view_absenteese()
{
    x.open("absenteese.dat",ios::in|ios::binary);
    if(!x)
    {
        cout<<"\n\n\t\tError:File Not Found!!!\n";
        cout<<"\n\n\tPlease Take The attendance First...";
        return;
    }
    cout<<"*********************************************************************\n";
	cout<<"                      Absent Faculties' Record                       \n";
    cout<<"*********************************************************************\n";
    cout<<"\n\tFaculty ID\tSubjects\tDesignation\tAtt. Status\tName";
    while(x.read(reinterpret_cast<char*>(&t),sizeof(t)))
    {
        t.faculty_list_casual();
    }
    x.close();
    return;
}
//***********************************************************
//        Function To View The Record Of Single Faculty
//***********************************************************
void view_sngl()
{
    int id;
    char ch;
    bool flag=false;
    x.open("fdata.dat",ios::in|ios::binary);
    system("cls");
    cout<<"*********************************************************************\n";
    cout<<"                   View Data Of A Single Faculty                     \n";
    cout<<"*********************************************************************\n";
    cout<<"\nEnter The Faculty ID : ";
    while (!(std::cin>>id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"\n\t\tError: Please Enter An Integer Value!!!"<<std::endl;
    }
    while(x.read(reinterpret_cast<char*>(&t),sizeof(t)))
    {
       if(t.get_e_id()==id)
       {
            t.print_data();
            flag=true;
       }
    }
    if(flag==false)
        cout<<"\n\t\t\tError: Faculty ID Mismatch!!!";
    x.close();
    cout<<"\n\n\tDo You Wish To View More Records???[Y/N]...";
    cin>>ch;
    if(ch=='y'||ch=='Y')
        view_sngl();
    else
        return;
}
//***********************************************************
//            Function To Delete A Faculty Record
//***********************************************************
void del_data()
{
    int tmp_id;
    char ch1,ch2;
    system("cls");
    cout<<"*********************************************************************\n";
    cout<<"                        Record Deletion Module                       \n";
    cout<<"*********************************************************************\n";
    cout<<"Enter The Faculty ID: ";
    while(!(std::cin>>tmp_id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"\n\t\tError: Please Enter An Integer Value!!!"<<std::endl;
        cout<<"Enter The Faculty ID: ";
    }
    x.open("fdata.dat",ios::in|ios::binary);
    bool flag1=false,flag2=false;
    while(x.read(reinterpret_cast<char*>(&t),sizeof(t)))
    {
        if(tmp_id==t.get_e_id())
        {
            t.print_data();
            flag1=true;
        }
    }
    x.close();
    if(flag1==true)
    {
        cout<<"\n\n\tAre You Sure With The Deletion Of This Record???[Y/N]...";
        cin>>ch1;
        if(ch1=='y'||ch1=='Y')
        {
            x.open("fdata.dat",ios::in|ios::binary);
            while(x.read(reinterpret_cast<char*>(&T),sizeof(T)))
            {
                if(T.e_id!=tmp_id)
                {
                    y.open("temp.dat",ios::out|ios::binary);
                    y.write(reinterpret_cast<char*>(&T),sizeof(T));
                    y.close();
                }
            }
            x.close();
            flag2=true;
            remove("fdata.dat");
            rename("temp.dat","fdata.dat");
        }
    }
    if(flag1==false)
        cout<<"\n\n\t\t\tError:Faculty Id Mismatch!!!";
    if(flag2==true)
        cout<<"\n\n\tRecord Deleted...";
    cout<<"\n\n     Do You Wish To Continue With Deletion Of More Records???[Y/N]...";
    cin>>ch2;
    if(ch2=='y'||ch2=='Y')
        del_data();
    else
        return;
}
void attendance()
{
    faculty f2;
    ifstream m;
    ifstream n;
    int att_id;
    char choice;
    char ch;
    bool flag1=false,flag2=false,flag3=false;
    system("cls");
    cout<<"*********************************************************************\n";
    cout<<"                        Attendance Intake Module                     \n";
    cout<<"*********************************************************************\n";
    n.open("fdata.dat",ios::in|ios::binary);
    m.open("absenteese.dat",ios::in|ios::binary);
    if(!m)
    {
        m.close();
        q.open("absenteese.dat",ios::out|ios::binary);
        while(n.read(reinterpret_cast<char*>(&T),sizeof(T)))
        {
            T.attendance_status='A';
            q.write(reinterpret_cast<char*>(&T),sizeof(T));
        }
        q.close();
    }
    m.close();
    n.close();
    cout<<"\nEnter Your Faculty ID :";
    while (!(std::cin>>att_id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"\n\t\tError: Please Enter An Integer Value!!!"<<std::endl;
        getch();
        attendance();
    }
    u.open("present_staff.dat",ios::in|ios::binary);
    while(u.read(reinterpret_cast<char*>(&f2),sizeof(f2)))
    {
        if(att_id==f2.get_e_id())
        {
            flag3=true;
            cout<<"\n\tAttendance Of This Faculty Has Already Been Marked...";
        }
    }
    u.close();
    if(flag3==false)
    {
        x.open("fdata.dat",ios::in|ios::binary);
        y.open("present_staff.dat",ios::out|ios::app|ios::binary);
        while(x.read(reinterpret_cast<char*>(&t),sizeof(t)))
        {
            if(att_id==t.get_e_id())
            {
                t.print_data();
                flag1=true;
                cout<<"\n\n\tIs The Above Information Correct???[Y/N]...";
                cin>>ch;
                if(ch=='y'||ch=='Y')
                {
                    t.attendance_status='P';
                    y.write(reinterpret_cast<char*>(&t),sizeof(t));
                    y.close();
                    cout<<"\n\n\tWelcome ";t.retrn_gndr();
                    cout<<t.name<<" ; Your Atttendence Has Been Marked...";
                    p.open("absenteese.dat",ios::in|ios::binary);
                    v.open("temp.dat",ios::out|ios::app|ios::binary);
                    while(p.read(reinterpret_cast<char*>(&f1),sizeof(f1)))
                    {
                        if(f1.e_id!=att_id)
                        {
                            f1.attendance_status='A';
                            v.write(reinterpret_cast<char*>(&f1),sizeof(f1));
                            flag2=true;
                        }
                    }
                    p.close();
                    v.close();
                }
                else
                {
                    goto p;
                }
            }
        }
    }
    if(flag1==false&&flag3==false)
        cout<<"\n\t\tError: Faculty ID Mismatch!!!";
  p:x.close();
    y.close();
    if(flag2==true)
    {
        remove("absenteese.dat");
        rename("temp.dat","absenteese.dat");
    }
    cout<<"\n\n\tDo You Wish To Continue With attendance???[Y/N]...";
    cin>>choice;
    if(choice=='y'||choice=='Y')
        attendance();
    else
        return;
}//End Of Function*/
//***********************************************************
//          Function To Generate Regular Schedule
//***********************************************************
void generate_rg_f_schedule()
{
    x.open("fdata.dat",ios::in|ios::binary);
    if(!x)
    {
        cout<<"Error: File Not Found!!!";
        return;
    }
    y.open("rg_f_schedule.dat",ios::out|ios::binary);
    if(!y)
    {
        cout<<"Error: File Not Found!!!";
        return;
    }
    cout<<"*********************************************************************\n";
    cout<<"                          Regular Schedule                           \n";
    cout<<"*********************************************************************\n";
    cout<<" ID";
    for(int j=0;j<8;++j)
    {
        cout<<"\tP-"<<j+1;
    }
    x.seekg(0);
    while(x.read(reinterpret_cast<char*>(&t),sizeof(t)))
    {
        t.display_schedule();
        y.write(reinterpret_cast<char*>(&t),sizeof(t));
    }
    x.close();
    y.close();
}//End Of Function
//***********************************************************
//        Functions To Generate Temporary Schedule
//***********************************************************
int cnt_p_size(int &tp_size)//count the number of present faculties
{
    u.open("present_staff.dat",ios::in|ios::binary);
    while(u.read(reinterpret_cast<char*>(&T),sizeof(T)))
    {
        if(T.attendance_status=='P')
        {
            ++tp_size;
        }
    }
    u.close();
    return tp_size;
}
int cnt_a_size(int &ta_size)//count the number of absent faculties
{
    ifstream f;
    f.open("absenteese.dat",ios::in|ios::binary);
    while(f.read(reinterpret_cast<char*>(&T),sizeof(T)))
    {
        if(T.attendance_status=='A')
        {
            ++a_size;
        }
    }
    f.close();
    return ta_size;
}
bool srch(faculty f)
{
    p.open("tmp3.dat",ios::in|ios::binary);
    if(!p)
        return false;
    while(p.read(reinterpret_cast<char*>(&f1),sizeof(f1)))
    {
        if(f.e_id==f1.e_id)
        {
            p.close();
            return true;
        }
    }
    p.close();
    return false;
}
void t_sch_stg1()
 {
    cnt_p_size(p_size);
    cout<<"p_size="<<p_size<<endl;
    cnt_a_size(a_size);
    cout<<"a_size="<<a_size<<endl;
}
void t_sch_stg2()//stage-2//use null pointer
{
    remove("tmp1.dat");
    remove("tmp2.dat");
    remove("tmp3.dat");
    for(int i=0;i<8;++i)
    {
        int j=0,k=0;
        int arrx[p_size];
        for(int x=0;x<p_size;++x)
        {
            arrx[x]=0;
        }
        int arry[a_size];
        for(int x=0;x<a_size;++x)
        {
            arry[x]=0;
        }
        x.open("present_staff.dat",ios::in|ios::binary);
        if(!x)
        {
            cout<<"\n\tError(stg2_1): File Not Found!!!";
            return;
        }
        u.open("absenteese.dat",ios::in|ios::binary);
        if(!u)
        {
            cout<<"\n\tError(stg2_2): File Not Found!!!";
            return;
        }
        cout<<"\nInside for loop 1...for i="<<i<<endl;
        while(x.read(reinterpret_cast<char*>(&t),sizeof(t)))
        {

            cout<<endl;
            cout<<"\nInside while loop 1...";
            cout<<"\nt.e_id="<<t.e_id;
            cout<<"\nt.classroom_no["<<i<<"]="<<t.class_room_no[i];
            if (t.class_room_no[i]==100)
            {
                cout<<"\ninside if...";
                cout<<"\nt.classroomno["<<i<<"]="<<t.class_room_no[i];
                int p=t.class_room_no[i];
                cout<<"\np="<<p;
                arrx[j]=p;
                cout<<"\narrx["<<j<<"]="<<arrx[j]<<endl;
                ++j;
            }
        }
        cout<<endl;
        while(u.read(reinterpret_cast<char*>(&T),sizeof(T)))
        {
            cout<<endl;
            cout<<"\nInside while loop 2...";
            cout<<"\nT.e_id="<<T.e_id;
            cout<<"\nT.classroom_no["<<i<<"]="<<T.class_room_no[i];
            if (T.class_room_no[i]!=100)
            {
                cout<<"\ninside if...";
                cout<<"\nt.classroomno["<<i<<"]="<<T.class_room_no[i];
                cout<<"\n"<<(T.class_room_no[i]);
                int p=T.class_room_no[i];
                cout<<"\np="<<p;
                arry[k]=p;
                cout<<"\narry["<<k<<"]="<<arry[k]<<endl;
                ++k;
            }
        }
        cout<<endl;
        int n_p[j],n_a[k],o;
        if(j<k)
            o=j;
        else
            o=k;
        for(int x=0;x<j;++x)
        {
             cout<<"\narrx["<<x<<"]="<<arrx[x];

        }
        cout<<endl;
        for(int x=0;x<k;++x)
        {
             cout<<"\narry["<<x<<"]="<<arry[x];

        }
        for(int x=0;x<k;++x)
             n_a[x]=x;
        std::random_shuffle(n_a,n_a+(k));
        for(int x=0;x<k;++x)
        {
            cout<<"\nn_a["<<x<<"]="<<n_a[x];
        }
        for(int x=0;x<j;++x)
             n_p[x]=x;
        std::random_shuffle(n_p,n_p+(j));//for random values of n_p
        for(int x=0;x<j;++x)
        {
            cout<<"\nn_p["<<x<<"]="<<n_p[x];
        }
        for(int x=0;x<o;++x)
        {
            int m,n;
            m=n_p[x];
            n=n_a[x];
            arrx[m]=arry[n];
        }
        for(int x=0;x<j;++x)
        {
            cout<<"\nfinally...\narrx["<<x<<"]="<<arrx[x];
        }
        x.close();
        u.close();
        j=0;
        p.open("present_staff.dat",ios::in|ios::binary);
        u.open("tmp1.dat",ios::in|ios::binary);
        faculty f2;
        while(p.read(reinterpret_cast<char*>(&f1),sizeof(f1)))
        {

            cout<<endl;
            cout<<"\nInside while loop 3...";
            cout<<"\nt.e_id="<<t.e_id;
            cout<<"\nt.classroom_no["<<i<<"]="<<f1.class_room_no[i];
            if (f1.class_room_no[i]==100)
            {
                cout<<"\ninside if...";
                cout<<"\nt.classroomno["<<i<<"]="<<f1.class_room_no[i];
                f1.class_room_no[i]=arrx[j];
                cout<<"\nf1.class_room_no["<<i<<"]"<<f1.class_room_no[i]<<endl;
                v.open("tmp1.dat",ios::out|ios::app|ios::binary);
                v.write(reinterpret_cast<char*>(&f1),sizeof(f1));
                v.close();
                j++;
            }
        }
        u.close();
        p.close();
    }
    x.open("tmp1.dat",ios::in|ios::binary);
    while(x.read(reinterpret_cast<char*>(&t),sizeof(t)))
    {
        p.open("tmp1.dat",ios::in|ios::binary);
        while(p.read(reinterpret_cast<char*>(&T),sizeof(T)))
        {
            if(t.e_id==T.e_id)
            {
                for(int i=0;i<8;i++)
                {
                    if(t.class_room_no[i]==100&&T.class_room_no[i]!=100)
                        t.class_room_no[i]=T.class_room_no[i];
                }
            }
        }
        y.open("tmp2.dat",ios::out|ios::app|ios::binary);
        y.write(reinterpret_cast<char*>(&t),sizeof(t));
        y.close();
        p.close();
    }
    x.close();
    x.open("tmp2.dat",ios::in|ios::binary);
    while(x.read(reinterpret_cast<char*>(&t),sizeof(t)))
    {
        cout<<"\n\t\t\t"<<t.e_id;
        bool flag;
        flag=srch(t);
        if(flag==false)
        {
            cout<<"\n\t"<<t.e_id;
            y.open("tmp3.dat",ios::out|ios::app|ios::binary);
            y.write(reinterpret_cast<char*>(&t),sizeof(t));
            y.close();
        }
    }
    x.close();
    /*    bool flag =false;
        cout<<"\n\t\t"<<t.e_id;
        for(int i=0;i<p_size;i++)
        {
            if(t.e_id==a[i])
            {
                flag=true;
                break;
            }
            cout<<"\n\ti="<<i<<"\ta[i]="<<a[i];
        }
        if(flag==false)
        {
           cout<<"\n"<<t.e_id;
            a[j]=t.e_id;
           cout<<"\t"<<a[j];
            j++;
        }
    }
    x.close();
    cout<<endl;
    for(int i=0;i<p_size;++i)
        cout<<"\t"<<a[i];
    remove("tmp3.dat");
    x.open("tmp2.dat",ios::in|ios::binary);
    for(int i=0;i<p_size;++i)
    {
        while(x.read(reinterpret_cast<char*>(&t),sizeof(t)))
        {
            if(a[i]==t.e_id)
            {
                y.open("tmp3.dat",ios::out|ios::app|ios::binary);
                y.write(reinterpret_cast<char*>(&t),sizeof(t));
                y.close();
            }
        }
    }
    x.close();*/
    return;
}
void t_sch_stg3()
{
    system("cls");
    x.open("tmp3.dat",ios::in|ios::binary);
    cout<<"*********************************************************************\n";
    cout<<"                           Today's Schedule                          \n";
    cout<<"*********************************************************************\n";
    cout<<" ID";
    for(int j=0;j<8;++j)
    {
        cout<<"\tP-"<<j+1;
    }
    while(x.read(reinterpret_cast<char*>(&t),sizeof(t)))
        t.display_schedule();
    x.close();
    return;
}
/*int secure_intro(char &acc)
{
    string pass ="";
    char ch,ch2;
 x: system("cls");
    cout<<"*********************************************************************\n";
    cout<<"               Welcome To Schedule Management Utility                \n";
    cout<<"*********************************************************************\n";
    cout<<"\n\n\n\t\tPlease Enter Password:";
    ch=_getch();
    while(ch!=13)
    {
        pass.push_back(ch);
        cout<<'*';
        ch=_getch();
    }
    if(pass=="password")
    {
        cout<<"\n\n\t\tAccess granted!!!\n";
        getch();
        acc=1;
        return acc;
    }
    else
    {
        cout<<"\n\n\n\t\tAccess aborted!!!\n";
        cout<<"\n\t\t\tHit R or r to Retry OR Press Any Other Key To Exit...";
        cin>>ch2;
        if(ch2=='R'||ch2=='r')
            goto x;
        else
            return acc;
    }
}*/
//***********************************************************
//             Main() Function Of The Programme
//***********************************************************
int main()
{
   /* char access=0;
    secure_intro(access);
    if(access==0)
        return(0);*/
    char ch1,ch2,ch3,chx='y';
    while(chx=='y'||chx=='Y')
    {
         system("cls");
         cout<<"***********************************************************\n";
         cout<<"          Welcome To Schedule Management Utility         \n";
         cout<<"***********************************************************\n";
         cout<<"\n    What Can I Do For You???";
         cout<<"\n\t1.Take attendance...";
         cout<<"\n\t2.Generate Time Table...";
         cout<<"\n\t3.View The List Of All Faculties...";
         cout<<"\n\t4.View The List Of Present Faculties...";
         cout<<"\n\t5.View The List Of Absent Faculties...";
         cout<<"\n\t6.View The Record Of Single Faculty...";
         cout<<"\n\t7.Administrative Tools...";
         cout<<"\n\t8.Quit...";
         cout<<"\n\n\t\tEnter Your choice...";
         cin>>ch1;
         switch(ch1)
         {
           case'1':system("cls");
                   attendance();
                   break;
           case'2':system("cls");
                   cout<<"***********************************************************\n";
                   cout<<"                Schedule Generation Module                 \n";
                   cout<<"***********************************************************\n";
                   cout<<"\n    What Can I Do For You???";
                   cout<<"\n\t1.Generate Schedule For Regular Days...";
                   cout<<"\n\t2.Generate A Temporary Schedule...";
                   cout<<"\n\t3.Go Back To The Main Menu...";
                   cout<<"\n\t4.Quit...";
                   cout<<"\n\n\t\tEnter Your choice...";
                   cin>>ch2;
                   switch(ch2)
                   {
                       case '1':system("cls");
                                generate_rg_f_schedule();
                                break;
                       case '2':system("cls");
                                t_sch_stg1();
                                if(p_size>=a_size)
                                {
                                    t_sch_stg2();
                                    t_sch_stg3();
                                }
                                else
                                {
                                    system("cls");
                                    cout<<"\n\t\tSorry...Temporary Schedule Generation";
                                    cout<<"\n\t\tIs Beyond My Limits Now...";
                                    cout<<"\n\t\tPlease Do It Manually...";
                                }
                                break;
                       case '3':break;
                       default:exit(0);
                   }
                   break;
           case'3':system("cls");
                   list_all_faculties();
                   break;
           case'4':system("cls");
                   list_prsnt_faculties();
                   break;
           case'5':system("cls");
                   view_absenteese();
                   break;
           case'6':system("cls");
                   view_sngl();
                   break;
           case'7':system("cls");
                   cout<<"***********************************************************\n";
                   cout<<"                    Administrative Tools                   \n";
                   cout<<"***********************************************************\n";
                   cout<<"\n    What Can I Do For You???";
                   cout<<"\n\t1.Generate New Faculty Record...";
                   cout<<"\n\t2.Delete A Faculty Record...";
                   cout<<"\n\t3.Change Administrator Password...";
                   cout<<"\n\t4.Go Back To The Main Menu...";
                   cout<<"\n\t5.Quit...";
                   cout<<"\n\n\t\tEnter Your choice...";
                   cin>>ch3;
                   switch(ch3)
                   {
                       case'1': system("cls");
                                get_fdata();
                                break;
                       case'2': system("cls");
                                del_data();
                                break;
                       case'3': system("cls");
                                break;
                       case'5': break;
                       default: exit(0);
                   }
                   break;
           case '8':exit(0);
                    break;
           default :cout<<"\n\n\tError: Wrong Choice...!!!";
          }
          cout<<"\n\n   Do You Wish To Continue With Schedule Management System???[Y/N]...";
          cin>>chx;
    }
        return(0);
}//End Of Main
//***********************************************************
//                 End Of The Maiin Programme
//***********************************************************
