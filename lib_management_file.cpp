#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using namespace std;

class book{
    char book_name[20],author[30];
    int page_no,stock;
    char book_id[6];
    
    public:
    
    book(){
        strcpy(book_name,"");
        strcpy(author,"");
        page_no=stock=0;
        strcpy(book_id,"");
    }

    void set_book_info(char* b_name,char* writter,int pg_no,int stk,char b_id[]){
        strcpy(book_name,b_name);
        strcpy(author,writter);
        page_no = pg_no;
        stock = stk;
        strcpy(book_id,b_id);
    }

    void get_book_info(){
        cout<<"**** New book entry ****"<<endl;
        cout<<"Enter book id: ";
        cin>>book_id;
        cout<<"Enter the name of the book: ";
        cin>>book_name;
        cout<<"Enter the Author's name: ";
        cin>>author;
        cout<<"Number of pages in book? ";
        cin>>page_no;
        cout<<"How many books are there in stock? ";
        cin>>stock;
        cout<<"Book data stored......";
    }

    void show_book(){
        cout<<"Book Name: "<<book_name<<endl;
        cout<<"Book ID: ";
        puts(book_id);
        cout<<"\nAuthor of this book is: "<<author<<endl;
        cout<<"Number of pages is: "<<page_no<<endl;
    }

    char* ret_book_id(){
        return book_id;
    }

    char* ret_book_name(){
        return book_name;
    }

    char* ret_book_author(){
        return author;
    }

    int ret_page_num(){
        return page_no;
    }

    int ret_book_stock(){
        return stock;
    }

    friend void display_all_book(fstream &file);
    friend void display_speci_book(fstream &file);
};

class student{
    char stu_name[30];
    char stu_id[12];
    int current_sem,books_token;
    
    public:
    
    student(){
        strcpy(stu_name ,"");
        strcpy(stu_id,"");
        current_sem = books_token = 0;
    }
    
    void get_student_info(){
        cout<<"Enter student name: ";
        cin>>stu_name;
        cout<<"Enter student ID: ";
        cin>>stu_id;
        cout<<"Student is currently studying in which sem: ";
        cin>>current_sem;
    }

    void set_student_info(char  *s_name,char s_id[],int sem){
        strcpy(stu_name ,s_name);

        strcpy(stu_id,s_id);
        current_sem = sem;
    }

    char* ret_stu_id(){
        return stu_id;
    }

    char * ret_stu_name(){
        return stu_name;
    }
    int ret_stu_sem(){
        return current_sem;
    }

    int ret_b_token(){
        return books_token;
    }

    void reset_b_token(){
        books_token = 0;
    }

    void add_book(){
        if(books_token<6)
        books_token++;
        else
        cout << "You have already reached your limit(that is 6) to borrow a book from this library." << endl;
    }

    void given_book(){
        if(books_token>0)
        books_token--;
        else
        cout << "No book is issued by this student." << endl;
    }

    friend void display_all_stu(fstream &file);
    friend void display_speci_stu(fstream &file);
};

void add_book_data(fstream &fbd, book &bk){
    char ch;
    if (!fbd.is_open()){
    	cout << "File is not open "; 
    	return ;	
    }
	fbd.clear(); 
	fbd.sync(); 
	fbd.seekp(0l,ios::end);
    do
    {
        bk.get_book_info();
        fbd.write((char*)&bk,sizeof(book));
        cout<<"\n\nDo you want to add more record..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    
    cout<<"Data of books given by you is saved...";
}

void add_stu_data(fstream &fsd,student &st){
	char ch;
    if (!fsd.is_open()){
    	cout << "File is not open "; 
    	return ;	
    }
	fsd.clear(); 
	fsd.sync(); 
	fsd.seekp(0l,ios::end);
    do
    {
        st.get_student_info();

     	fsd.write((char*)&st, sizeof(st));
    	cout << "Enter another record"; 
		cin >> ch;
    }while(ch=='y'||ch=='Y');
    cout<<"Data of books given by you is saved...";
}

void display_all_book(fstream &file){
    book b;
    file.clear();
	file.seekg( 0L , ios::beg);
    cout << "              --------------Books detils---------------" << endl;
	cout << endl << "book_id\tbook_name\tauthor\tno_of_pages\tstock_left" << endl;  
	for(int i=1;i<=75;i++){
        cout << "-";
    }
	while(file.read((char*)&b,sizeof(b)))
	{
		cout << endl << b.book_id << "\t" << b.book_name << "\t\t" << b.author << "\t" << b.page_no << "\t\t" <<b.stock<<endl<<endl;  
	}
}

void display_speci_book(fstream &file){
    book b;
    char b_id[6];
    cout << "Enter ID of Book you want to find: ";
    cin >> b_id;
    file.clear();
	file.seekg( 0L , ios::beg);
    cout << "              --------------Specific Book detils---------------" << endl;
	cout << endl << "book_id\tbook_name\tauthor\tno_of_pages\tstock_left" << endl;  
	for(int i=1;i<=75;i++){
        cout << "-";
    }
	while(file.read((char*)&b,sizeof(b)))
	{
        if(strcmp(b_id,b.book_id)==0){
		    cout << endl << b.book_id << "\t" << b.book_name << "\t\t" << b.author << "\t\t" << b.page_no << "\t\t\t" <<b.stock<<endl<<endl;
        }  
	}
}

void display_all_stu(fstream &file){
    student s;
   	
    cout << "       --------------Student detils---------------" << endl;
	cout << endl << "student_id\tstudent_name\tcurrent_sem\tbooks_taken" << endl;  
	for(int i=1;i<=61;i++){
        cout << "-";
    }
    file.clear(); 
	file.seekg(0L , ios::beg);
	file.sync(); 
	while(file.read((char*)&s,sizeof(s)))
	{
		cout << endl << s.stu_id << "\t\t" <<s.stu_name << "\t\t" << s.current_sem << "\t\t" <<s.books_token<<endl<<endl;
	}
}

void display_speci_stu(fstream &file){
    student s;
    char s_id[12];
    cout << "Enter ID of Student you want to find: ";
    cin >> s_id;
    file.clear(); 
	file.seekg( 0L , ios::beg);
    cout << "       --------------Student detils---------------" << endl;
	cout << endl << "student_id\tstudent_name\tcurrent_sem\tbooks_taken" << endl;  
	for(int i=1;i<=61;i++){
        cout << "-";
    }
	while(file.read((char*)&s,sizeof(s)))
	{
        if(strcmp(s_id,s.stu_id)==0){
		    cout << endl << s.stu_id << "\t\t" << s.stu_name << "\t\t" << s.current_sem << "\t\t" <<s.books_token<<endl<<endl; 
        }
	}
}

void rem_book(fstream &file, ofstream &outfile){
    book b;
    display_all_book(file);
    char b_id[6];
    cout << endl << "Enter ID of book you wanna remove : " ; 
	cin >> b_id; 
	file.clear();
    file.sync();
	file.seekg( 0L , ios::beg);
	outfile.open("./tbook.dat");
	while(file.read((char*)&b,sizeof(b)))
	{
		if (strcmp(b_id, b.ret_book_id()) != 0){
			outfile.write((char*)&b,sizeof(b));	
		}
	}
	remove("./book.dat");
	rename("./tbook.dat","./book.dat");
    cout << "Data of Book with Book ID " << b.ret_book_id() << " removed successfully...";
}

void rem_student(fstream &file, ofstream &outfile){
    student s;
    display_all_stu(file);
    char s_id[12];
    cout << endl << "Enter ID of Student whose data you wanna remove : " ; 
	cin >> s_id; 
	file.clear();
    file.sync();
	file.seekg( 0L , ios::beg);
	outfile.open("./tstudent.dat");
	while(file.read((char*)&s,sizeof(s)))
	{
		if (s_id!=s.ret_stu_id()){
			outfile.write((char*)&s,sizeof(s));	
		}
	}	
	remove("./student.dat");
	rename("./tstudent.dat","./student.dat");
    cout << "Data of Student with Student ID " << s.ret_stu_id() << " removed successfully...";
}

void book_issue(fstream &fbd, fstream &fsd, book &bk, student &st){
    char sid[12],bid[6];
    int found=0,flag=0;
    cout << "... BOOK ISSUE ..." << endl << endl;
    cout << "Enter The student's ID: ";
    cin >> sid;
    if (!fbd.is_open()){
    	cout << "File is not open "; 
    	return ;	
    }
    if (!fsd.is_open()){
    	cout << "File is not open "; 
    	return ;	
    }
    while(fsd.read((char*)&st,sizeof(student)) && found==0){
        if(strcmp(st.ret_stu_id(),sid)==0){
            found=1;
            cout << "\n\nEnter the Book ID you wanna borrow: ";
            cin >> bid;
            while(fbd.read((char*)&bk,sizeof(book))&& flag==0){
                if(strcmp(bk.ret_book_id(),bid)==0){
                    bk.show_book();
                    flag = 1;
                    st.add_book();
                    int pos =- 1*sizeof(st);
                    fsd.seekp(pos,ios::cur);
                    fsd.write((char*)&st,sizeof(student));
                    cout << "\n\n Book issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 20 for each day after 15 days period" << endl << endl;
                }
            }
            if(flag==0)
                cout << "Book with this ID does not exist" << endl << endl;
        }
        else
            cout << "You have not returned the last books issued by you, please return them because you have exhausted card limit!! " << endl << endl;

    }
    if(found==0)
        cout<<"Student record does not exist..." << endl << endl;
}

void book_deposit(fstream &fbd, fstream &fsd, book &bk, student &st){
    char sid[12],bid[12];
    int found=0,flag=0,day,fine;
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The Student's ID";
    cin>>sid;
    while(fsd.read((char*)&st,sizeof(student)) && found==0){
        if(strcmp(st.ret_stu_id(),sid)==0){
            found=1;
            cout << "\n\nEnter the Book ID you wanna deposit: ";
            cin >> bid;
            if(st.ret_b_token()>=1){
                while(fbd.read((char*)&bk,sizeof(book))&& flag==0){
                    if(strcmp(bk.ret_book_id(),bid)==0){
                        bk.show_book();
                        flag=1;
                        cout<<"\n\nBook deposited in no. of days";
                        cin>>day;
                        if(day>15){
                            fine=(day-15)*1;
                            cout<<"\n\nFine has to deposited Rs. "<<fine;
                        }
                        st.reset_b_token();
                        int pos =- 1*sizeof(st);
                        fsd.seekp(pos,ios::cur);
                        fsd.write((char*)&st,sizeof(student));
                        cout<<"\n\n\t Book deposited successfully";
                    }
                }
                if(flag==0)
                    cout<<"Book with this ID does not exist";
            }
            else
                cout<<"No book is issued..please check!!";
        }
    }
    if(found==0)
        cout<<"Student record does not exist...";
}

void admin_menu(fstream &fbd,fstream &fsd,student &st, book &bk, ofstream &outfile){
    int ch;
    cout << "************* Administration Menu *************" << endl << endl;
    cout << "1. Add Student Record" << endl;
    cout << "2. Add Book Record" << endl;
    cout << "3. Display all Books Record" << endl;
    cout << "4. Display specific Books Record" << endl;
    cout << "5. Display all Students Record" << endl;
    cout << "6. Display specific Student Record" << endl;
    cout << "7. Delete Student Record" << endl;
    cout << "8. Delete Book Record" << endl;
    cout << "9. Back to Main Menu" << endl << endl;
    cout << "Enter your choice: ";
    cin >> ch;
    switch(ch){
        case 1:
            system("clear");
            add_stu_data(fsd,st);
        break;
        case 2:
            system("clear");
            add_book_data(fbd,bk);
        break;
        case 3:
            system("clear");
            display_all_book(fbd);
        break;
        case 4:
            system("clear");
            display_speci_book(fbd);
        break;
        case 5:
            system("clear");
            display_all_stu(fsd);
        break;
        case 6:
            system("clear");
            display_speci_stu(fsd);
        break;
        case 7:
            system("clear");
            rem_student(fsd,outfile);
        break;
        case 8:
            system("clear");
            rem_book(fbd,outfile);
        break;
        case 9:
            return;
    }
}

void search_bk_name(fstream &file){
    book b;
    string bk;
    cout << "Enter Name of Book you want to find: ";
    cin >> bk;
    file.clear();
	file.seekg( 0L , ios::beg);
    cout << "              --------------Specific Book detils---------------" << endl;
	cout << endl << "book_id\tbook_name\tauthor\tallocated_to\tno_of_pages\tstock_left" << endl;  
	for(int i=1;i<=75;i++){
        cout << "-";
    }
	while(file.read((char*)&b,sizeof(b)))
	{
        if(b.ret_book_name()==bk){
		    cout << endl << b.ret_book_id() << "\t" << b.ret_book_name() << "\t" << b.ret_book_author() << "\t" << b.ret_page_num() << "\t" <<b.ret_book_stock()<<endl<<endl;
        }  
	}
}

void search_bk_author(fstream &file){
    book b;
    string aut;
    cout << "Enter Author Name of Book you want to find: ";
    cin >> aut;
    file.clear();
	file.seekg( 0L , ios::beg);
    cout << "              --------------Specific Book detils---------------" << endl;
	cout << endl << "book_id\tbook_name\tauthor\tallocated_to\tno_of_pages\tstock_left" << endl;  
	for(int i=1;i<=75;i++){
        cout << "-";
    }
	while(file.read((char*)&b,sizeof(b)))
	{
        if(b.ret_book_author()==aut){
		    cout << endl << b.ret_book_id() << "\t" << b.ret_book_name() << "\t" << b.ret_book_author() << "\t" << b.ret_page_num() << "\t" <<b.ret_book_stock()<<endl<<endl;
        }  
	}
}

void search_stu_name(fstream &file){
    student s;
    string stu;
    cout << "Enter Name of Student you want to find: ";
    cin >> stu;
    file.clear(); 
	file.seekg( 0L , ios::beg);
    cout << "       --------------Student detils---------------" << endl;
	cout << endl << "student_id\tstudent_name\tcurrent_sem\tbooks_taken" << endl;  
	for(int i=1;i<=61;i++){
        cout << "-";
    }
	while(file.read((char*)&s,sizeof(s)))
	{
        if(stu==s.ret_stu_name()){
		    cout << endl << s.ret_stu_id() << "\t" << s.ret_stu_name() << "\t" << s.ret_stu_sem() << "\t" <<s.ret_b_token()<<endl<<endl; 
        }
	}
}

void search_stu_sem(fstream &file){
    student s;
    int sem;
    cout << "Enter Current Semester of Student you want to find: ";
    cin >> sem;
    file.clear(); 
	file.seekg( 0L , ios::beg);
    cout << "       --------------Student detils---------------" << endl;
	cout << endl << "student_id\tstudent_name\tcurrent_sem\tbooks_taken" << endl;  
	for(int i=1;i<=61;i++){
        cout << "-";
    }
	while(file.read((char*)&s,sizeof(s)))
	{
        if(sem==s.ret_stu_sem()){
		    cout << endl << s.ret_stu_id() << "\t" << s.ret_stu_name() << "\t" << s.ret_stu_sem() << "\t" <<s.ret_b_token()<<endl<<endl; 
        }
	}
}

void search_menu_book(fstream &fbd){
    int ch;
    cout << "************* Searching Methods For Books *************" << endl << endl;
    cout << "1. Search by Book Name" << endl;
    cout << "2. Search by Book Id" << endl;
    cout << "3. Search by Author Name" << endl << endl;
    cout << "Enter your choice: ";
    cin >> ch;
    switch(ch){
        case 1:
            search_bk_name(fbd);
        break;
        case 2:
            display_speci_book(fbd);
        break;
        case 3:
            search_bk_author(fbd);
        break;
    }
}

void search_menu_student(fstream &fsd){
    int ch;
    cout << "************* Searching Methods For Students *************" << endl << endl;
    cout << "1. Search by Student Name" << endl;
    cout << "2. Search by Student Id" << endl;
    cout << "3. Search by Current Sem" << endl << endl;
    cout << "Enter your choice: ";
    cin >> ch;
    switch(ch){
        case 1:
            search_stu_name(fsd);
        break;
        case 2:
            display_speci_stu(fsd);
        break;
        case 3:
            search_stu_sem(fsd);
        break;
    }
}

void search_menu(fstream &fbd, fstream &fsd){
    int ch;
    cout << "************* Searching Menu *************" << endl << endl;
    cout << "1. Seaching methods for Books" << endl;
    cout << "2. Seaching methods for Students" << endl;
    cout << "3. Back to Main Menu" << endl << endl;
    cout << "Enter your choice: ";
    cin >> ch;
    switch(ch){
        case 1:
            system("clear");
            search_menu_book(fbd);
        break;
        case 2:
            system("clear");
            search_menu_student(fsd);
        break;
        case 3:
            return;
    }
}

int  main(){
	
	fstream fbd, fsd;
    ofstream outfile;
    book bk;
    student st;
	
	fbd.open("./book.dat",ios::in | ios::out | ios::binary); 
	if (!fbd.is_open()) {
        fbd.open("./book.dat",ios::in | ios::out | ios::trunc |ios::binary);
		if (!fbd.is_open()) {
            cout << "Contact to the concern person" ;
            return (1); 
        }
    }
   
	fsd.open("./student.dat",ios::in | ios::out | ios::binary);;
	if (!fsd.is_open()) 
	{
		fsd.open("./student.dat",ios::in | ios::out | ios::trunc |ios::binary);
        if (!fsd.is_open()) 
		{
            cout << "Contact to the concern person" ;
            return 1; 
        }
    }
	
    int choice;
    
    do{
        cout << "\033[0m";
		cout << endl << endl << "********* Main Menu **********" << endl << endl;
        cout << "1. Book Issue" << endl;
        cout << "2. Book Deposite" << endl;
        cout << "3. Administration Menu" << endl;
        cout << "4. Searching menu" << endl;
        cout << "5. Exit" << endl << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                system("clear");
                cout << "\033[33;44m";
                cout << "\033[31m";
                book_issue(fbd,fsd,bk,st);
                break;
            case 2:
                system("clear");
                book_deposit(fbd,fsd,bk,st);
                break;
            case 3:
                system("clear");
                cout << "\033[33;45m";
                admin_menu(fbd,fsd,st,bk,outfile);
                break;
            case 4:
                system("clear");
                cout << "\033[31m";
                search_menu(fbd,fsd);
            break;
            case 5:
                exit(1);
        }
    }while(1);
    
    fsd.close(); 
    fbd.close(); 
    outfile.close();
    
    return 0 ; 
}
