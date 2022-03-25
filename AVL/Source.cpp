#include"Header.h"
#include<cmath>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(suppress : 4996)



#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Base
{
    string Name;
    string Surname;
    int Age;
    int Course;
    string Subject;
};


Base readLine(ifstream& File, size_t columns)
{
    Base element;
    string str;
    getline(File, str);
   
   // const char delim = ' ';
    string* ar_char = new string[columns];
    stringstream str_elem(str);
    int i = 0;
    while (!str_elem.eof())
    {
        string s;
        str_elem >> s;
        ar_char[i] = s;
        ++i;

    }
   /* for (int i = 0; i < columns; ++i)
    {
        cout << ar_char[i]<<endl;
   }*/
    element.Name = ar_char[0];
    element.Surname = ar_char[1];
    stringstream myString;
    myString << ar_char[2];
    myString >> element.Age;
   
    stringstream myString1;
    myString1 << ar_char[3];
    myString1 >> element.Course;

    element.Subject = ar_char[4];
    delete[]ar_char;
    return element;
}

Base* ReadBaseData(ifstream& File, size_t columns, size_t lines)
{
    Base* b = new Base[lines];
    
    for (int i = 0; i < lines; i++)
    {
        b[i] = readLine(File, columns);
    }
    return b;
}

void Name_tree(Base* b, size_t lines, Tree<string, int> &tr)
{
    
    for (int i = 0; i < lines; ++i)
    {
        tr.insert(b[i].Name, i);
    }
 }

void Surname_tree(Base* b, size_t lines, Tree<string, int> &tr)
{
   
    for (int i = 0; i < lines; ++i)
    {
        tr.insert(b[i].Surname, i);
    }
}

void Age_tree(Base* b, size_t lines, Tree<int, int> &tr)
{
    
    for (int i = 0; i < lines; ++i)
    {
        tr.insert(b[i].Age, i);
    }
}

void Course_tree(Base* b, size_t lines, Tree<int, int> &tr)
{
    
    for (int i = 0; i < lines; ++i)
    {
        tr.insert(b[i].Course, i);
    }
}

void Subject_tree(Base* b, size_t lines, Tree<string, int>& tr)
{
    
    for (int i = 0; i < lines; ++i)
    {
        tr.insert(b[i].Subject, i);
    }
}

int main()
{
    size_t count_lines = 300000;
    size_t count_columns = 5;
    Base* array = new Base[count_lines];
    ifstream file("Textbig.txt");
    array = ReadBaseData(file, count_columns, count_lines);
    file.close();
    Tree<string, int> NameTree;
    Name_tree(array, count_lines, NameTree);
    int lenght;
    lenght = NameTree.Height();
    cout << endl << "The length of the tree is " << lenght << endl;
    Tree<string, int> SurnameTree;
    Surname_tree(array, count_lines, SurnameTree);
    lenght = SurnameTree.Height();
    cout << endl << "The length of the tree is " << lenght << endl;
    Tree<int, int> AgeTree;
    Age_tree(array, count_lines, AgeTree);
    lenght = AgeTree.Height();
    cout << endl << "The length of the tree is " << lenght << endl;
    Tree<int, int> CourseTree;
    Course_tree(array, count_lines, CourseTree);
    lenght = CourseTree.Height();
    cout << endl << "The length of the tree is " << lenght << endl;
    Tree<string, int> SubjectTree;
    Subject_tree(array, count_lines, SubjectTree);
    lenght = SubjectTree.Height();
    cout << endl << "The length of the tree is " << lenght << endl;
    /*Tree<string, int>::P_Iterator NameIt;
    Tree<string, int>::P_Iterator SurnameIt;
    Tree<int, int>::P_Iterator AgeIt;
    Tree<int, int>::P_Iterator CourseIt;
    Tree<string, int>::P_Iterator SubjectIt;
   

    cout << "Name tree\n";
    for (NameIt = NameTree.pbegin(); NameIt != NameTree.pend(); ++NameIt) {
        cout << *NameIt << endl;
    }

    cout << endl;
    cout << "Surname tree\n";
    for (SurnameIt = SurnameTree.pbegin(); SurnameIt != SurnameTree.pend(); ++SurnameIt) {
        cout << *SurnameIt << endl;
    }

    cout << endl;
    cout << "Age tree\n";
    for (AgeIt = AgeTree.pbegin(); AgeIt != AgeTree.pend(); ++AgeIt) {
        cout << *AgeIt << endl;
    }

    cout << endl;
    cout << "Course tree\n";
    for (CourseIt = CourseTree.pbegin(); CourseIt != CourseTree.pend(); ++CourseIt) {
        cout << *CourseIt << endl;
    }

    cout << endl;
    cout << "Subject tree\n";
    for (SubjectIt = SubjectTree.pbegin(); SubjectIt != SubjectTree.pend(); ++SubjectIt) {
        cout << *SubjectIt << endl;
    }*/

    
    int x = 54;
  
    int index = AgeTree.SearchValue(x);
    cout << "Search " << x << " "<< AgeTree.SearchValue(x)  << endl;
    if (index >= 0)
    {
        cout << array[index].Name << " " << array[index].Surname << " " << array[index].Age << " " << array[index].Course << " " << array[index].Subject << endl;
    }
    else
    {
        cout << "Element not found" << endl;
    }
   
    string n = "name5687"s;
    index = NameTree.SearchValue(n);
    cout << "Search " << n << " " << NameTree.SearchValue(n) << endl;
    if (index >= 0)
    {
        cout << array[index].Name << " " << array[index].Surname << " " << array[index].Age << " " << array[index].Course << " " << array[index].Subject << endl;
    }
    else
    {
        cout << "Element not found" << endl;
    }

    string x_str = "subject299977"s;
    index = SubjectTree.SearchValue(x_str);
    cout << "Search " << x_str << " " << SubjectTree.SearchValue(x_str) << endl;
    if (index >= 0)
    {
        cout << array[index].Name << " " << array[index].Surname << " " << array[index].Age << " " << array[index].Course << " " << array[index].Subject << endl;
    }
    else
    {
        cout << "Element not found" << endl;
    }
    delete[]array;
}

/*
class Base { public: int ID; int value;};
              string* tokenize(string str, size_t num_tokens, char delim = ',')
                   {
                       string* str_tokenize = new string[num_tokens];
                       int count_token = 0;
                       int last_delimiter = 0;
                       int i = 0;
                       for (i = 0; i <= str.size(); i++)
                       {
                           if ((str.c_str())[i] == delim || i == str.size())
                           {
                               str_tokenize[count_token] = str.substr(last_delimiter, i - last_delimiter);
                               last_delimiter = i + 1;
                               count_token++;
                           }
                       }
                       return str_tokenize;
                   }
                   Base* readLine(ifstream& File, size_t columns)
                   {
                       Base* b = new Base;
                       const char delim = ',';
                       string str, str0;
                       getline(File, str);
                       string* str_token = tokenize(str, columns, delim);
                       b->ID = atoi((str_token[0]).c_str());
                       b->value = atoi((str_token[1]).c_str());
                       delete[] str_token;
                       return b;
                   }
                   Base** CSVtoBase(ifstream& File, size_t columns, size_t lines)
                   {
                       Base** b = new Base * [lines];
                       int i;
                       for (i = 0; i < lines; i++)
                           b[i] = readLine(File, columns);
                       return b;
                   }
                   string createString(ofstream& File, Base* b, size_t columns)
                   {
                       string str = to_string(b->ID) + "," + to_string(b->value);
                       return str;
                   }
                   void BasetoCSV(ofstream& File, Base** b, size_t columns, size_t lines)
                   {
                       int i;
                       for (i = 0; i < lines; i++)
                       {
                           string str = createString(File, b[i], columns);
                           File << str << endl;
                       }
                   }
                   Tree<int, Base*>* Base2Tree_ID(Base** b, size_t lines)
                   {
                       Tree<int, Base*>* tr = new Tree<int, Base*>[lines] ;
                       int i;
                       for (i = 0; i < lines; i++)
                       {
                           tr->insert(b[i]->ID, b[i]);
                       }
                       return tr;
                   }
                   Tree<int, Base*>* Base2Tree_value(Base** b, size_t lines)
                   {
                       Tree<int, Base*>* tr = new Tree<int, Base*>[lines];
                       int i;
                       for (i = 0; i < lines; i++)
                       {
                           tr->insert(b[i]->value, b[i]);
                       }
                       return tr;
                   }
                   using namespace std;
                   int main()
                   {
                       
                       ifstream file("test.txt");
                       Base** b = CSVtoBase(file, 2, 2);
                       file.close();
                       Tree <int, Base*>* tr = Base2Tree_ID(b, 2);
                       Tree<int, Base*> ::P_Iterator trIt;
                       
                       for (trIt = tr[0].pbegin(); trIt != tr[0].pend(); ++trIt) {
                           cout << *trIt << endl;
                       }
                       
                      // cout << *tr << endl;
                   }



*/
/*int main()
{
    Tree<int, string> BigTree;
    char key[64];
    int n = 1000000, i, k = 0;

    Tree<int, string>::P_Iterator BigTreeIt;
    cout << endl;
    for (i = 0; i < n; i++)
    {
        sprintf(key, "key_%d", i);
        BigTree.insert(i, key);
    }
    int lenght;
    lenght = BigTree.Height();
    cout << endl << "The length of the tree is " << lenght << endl;
    cout << log(n)/log(2);

   
   /* Tree<int, string> BigTree;
    char key[64];
    int n = 100, i, k = 0;
    
    Tree<int, string>::P_Iterator BigTreeIt;
    cout << endl;
    for (i = 0; i < n; i++)
    {
        sprintf(key, "key_%d", i);
        BigTree.insert(i, key);
    }

    cout << endl<<"iterator with parent ptr\n";
    for (BigTreeIt = BigTree.pbegin(); BigTreeIt != BigTree.pend(); ++BigTreeIt) {
        cout << *BigTreeIt << endl;
    }

    for (i = 0; i < n; i=i+2)
    {
       // sprintf(key, "key_%d", i);
        BigTree.pop(i);
    }
    int x = 52;
    string y = "key_52";
    cout << endl;
    cout << "Search " << x << (BigTree.Search(x, y) ? " Yes" : " No") << endl;
    x = 41;
    y = "key_41";
    cout << "Search " << x << (BigTree.Search(x, y) ? " Yes" : " No") << endl;
    cout << endl;

    cout << "iterator with parent ptr\n";
    for (BigTreeIt = BigTree.pbegin(); BigTreeIt != BigTree.pend(); ++BigTreeIt) {
        cout << *BigTreeIt << endl;
    }
     */
  /*  Tree<int, string> DelTest;
    DelTest.insert(5, "key5"s);
    DelTest.insert(3, "key3"s);
    DelTest.insert(8, "key8"s);
    DelTest.insert(2, "key2"s);
    DelTest.insert(4, "key4"s);
    DelTest.insert(7, "key7"s);
    DelTest.insert(10, "key10"s);
    DelTest.insert(1, "key1"s);
    DelTest.insert(6, "key6"s);
    DelTest.insert(9, "key9"s);
    DelTest.insert(11, "key11"s);
    
    Tree<int, string>::P_Iterator DelIt;
    cout << endl;

    cout << "iterator with parent ptr\n";
    for (DelIt = DelTest.pbegin(); DelIt != DelTest.pend(); ++DelIt) {
        cout << *DelIt << endl;
    }
    DelTest.pop(4);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (DelIt = DelTest.pbegin(); DelIt != DelTest.pend(); ++DelIt) {
        cout << *DelIt << endl;
    }
    DelTest.pop(6);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (DelIt = DelTest.pbegin(); DelIt != DelTest.pend(); ++DelIt) {
        cout << *DelIt << endl;
    }
    int lenght;
    lenght = DelTest.Height();
    cout << endl << "The length of the tree is " << lenght << endl;*/
   /* Tree<int, string> DelTest;
    DelTest.insert(5, "key5"s);
    DelTest.insert(2, "key2"s);
    DelTest.insert(7, "key7"s);
    DelTest.insert(1, "key1"s);
    DelTest.insert(3, "key3"s);
    DelTest.insert(6, "key6"s);
    DelTest.insert(10, "key10"s);
    DelTest.insert(9, "key9"s);
    DelTest.insert(11, "key11"s);
    

    Tree<int, string>::P_Iterator DelIt;
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (DelIt = DelTest.pbegin(); DelIt != DelTest.pend(); ++DelIt) {
        cout << *DelIt << endl;
    }
    DelTest.pop(6);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (DelIt = DelTest.pbegin(); DelIt != DelTest.pend(); ++DelIt) {
        cout << *DelIt << endl;
    }

    DelTest.pop(5); //2 children
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (DelIt = DelTest.pbegin(); DelIt != DelTest.pend(); ++DelIt) {
        cout << *DelIt << endl;
    }*/

   /* Tree<int, string> DelTest; //123
    DelTest.insert(6, "key6"s);
    DelTest.insert(3, "key3"s);
    DelTest.insert(9, "key9"s);
    DelTest.insert(2, "key2"s);
    DelTest.insert(4, "key4"s);
    DelTest.insert(8, "key8"s);
    //DelTest.insert(1, "key1"s);
    DelTest.insert(5, "key5"s);


    Tree<int, string>::P_Iterator DelIt;
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (DelIt = DelTest.pbegin(); DelIt != DelTest.pend(); ++DelIt) {
        cout << *DelIt << endl;
    }
    DelTest.pop(8);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (DelIt = DelTest.pbegin(); DelIt != DelTest.pend(); ++DelIt) {
        cout << *DelIt << endl;
    }
    */
   

    /*Tree<int, string> p;
    p.insert(44, "key44"s);
    p.insert(17, "key17"s);
    p.insert(62, "key62"s);
    p.insert(10, "key10"s);
    p.insert(32, "key32"s);
    p.insert(50, "key50"s);
    p.insert(78, "key78"s);
    p.insert(21, "key21"s);
    p.insert(48, "key48"s);
    p.insert(54, "key54"s);
    p.insert(72, "key72"s);
    p.insert(88, "key88"s);
    p.insert(45, "key45"s);
    p.insert(49, "key49"s);
    p.insert(52, "key52"s);
    p.insert(56, "key56"s);
    p.insert(81, "key81"s);
    p.insert(92, "key92"s);
    //cout << a;
    int lenght;
    lenght=p.Height();
    cout << endl<<"The length of the tree is " << lenght << endl;
    int x = 52;
    string y = "key52";
    cout << endl;
    cout << "Search " << x << (p.Search(x, y) ? " Yes" : " No") << endl;
    x = 44;
    cout << "Search " << x << (p.Search(x,y) ? " Yes" : " No") << endl;
    cout << endl;

    Tree<int, string>::P_Iterator P;
    cout << endl;

    cout << "iterator with parent ptr\n";
    for (P = p.pbegin(); P != p.pend(); ++P) {
        cout << *P << endl;
    }
    p.pop(32);
    cout << endl;

    cout << "iterator with parent ptr\n";
    for (P = p.pbegin(); P != p.pend(); ++P) {
        cout << *P << endl;
    }*/

    //Пример 1. Правый поворот. Удаление 

 /*   cout << "Right rotation"s << endl;
    Tree<int, string> a;
    a.insert(13, "key1"s);
    a.insert(10, "key2"s);
    a.insert(15, "key3"s);
    a.insert(5, "key4"s);
    a.insert(11, "key5"s);
    a.insert(16, "key6"s);
    a.insert(4, "key7"s);
    a.insert(8, "key8"s);
    //cout << a;
    Tree<int, string>::P_Iterator A;
    cout << endl;

   cout << "iterator with parent ptr\n";
    for (A = a.pbegin(); A != a.pend(); ++A) {
       cout << *A << endl;
    }

    a.insert(3, "key9"s);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (A = a.pbegin(); A != a.pend(); ++A) {
        cout << *A << endl;
    }

    cout << endl;

    a.pop(8);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (A = a.pbegin(); A != a.pend(); ++A) {
        cout << *A << endl;
    }


    //Пример 2. Левый Правый поворот
    cout << "Left Right rotation"s << endl;
    Tree<int, string> b;
    b.insert(13, "Key_13"s);
    b.insert(10, "Key_10"s);
    b.insert(15, "Key_15"s);
    b.insert(5, "Key_5"s);
    b.insert(11, "Key_11"s);
    b.insert(16, "Key_16"s);
    b.insert(4, "Key_4"s);
    b.insert(6, "Key_6"s);
    cout << endl;
    Tree<int, string>::P_Iterator B;
    cout << "iterator with parent ptr\n";
    for (B = b.pbegin(); B != b.pend(); ++B) {
        cout << *B << endl;
    }
    cout << endl;

    b.insert(7, "Key_7");
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (B = b.pbegin(); B != b.pend(); ++B) {
        cout << *B << endl;
    }

    //Пример 3. Левый поворот
    cout << "Left rotation"s << endl;
    Tree<int, string> c;
    c.insert(30, "Value_30"s);
    c.insert(5,"Value_5"s);
    c.insert(35, "Value_35"s);
    c.insert(32, "Value_32"s);
    c.insert(40, "Value_40"s);

    cout << endl;
    Tree<int, string>::P_Iterator C;
    cout << "iterator with parent ptr\n";
    for (C = c.pbegin(); C != c.pend(); ++C) {
        cout << *C << endl;
    }
    cout << endl;

    c.insert(45, "Value_45"s);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (C = c.pbegin(); C != c.pend(); ++C) {
        cout << *C << endl;
    }

    //Пример 4. Правый Левый поворот
    cout << "Right Left rotation"s << endl;
    Tree<int, string> d;
    d.insert(5, "Value_5");
    d.insert(2, "Value_2"s);
    d.insert(7, "Value_7"s);
    d.insert(1, "Value_1"s);
    d.insert(4, "Value_4"s);
    d.insert(6, "Value_6"s);
    d.insert(9, "Value_9"s);
    d.insert(3, "Value_3"s);
    d.insert(16, "Value_16"s);
    
    Tree<int, string>::P_Iterator D;
    cout << "iterator with parent ptr\n";
    for (D = d.pbegin(); D != d.pend(); ++D) {
        cout << *D << endl;
    }
    cout << endl;

    d.insert(15, "Value_15"s);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (D = d.pbegin(); D != d.pend(); ++D) {
        cout << *D << endl;
    }

       //cout << endl;
    //a.insert(5);
    //a.insert(11);
    //a.insert(16);
    //a.insert(4);
    //a.insert(8);
/*    //Пример 1. Правый поворот. Удаление 

    cout << "Right rotation"s << endl;
    Tree<int> a;
    a.insert(13);
    a.insert(10);
    a.insert(15);
    a.insert(5);
    a.insert(11);
    a.insert(16);
    a.insert(4);
    a.insert(8);
    cout << endl;
    Tree<int>::P_Iterator A;
    cout << "iterator with parent ptr\n";
    for (A = a.pbegin(); A != a.pend(); ++A) {
        cout << *A << endl;
    }
    cout << endl;

    a.insert(3);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (A = a.pbegin(); A != a.pend(); ++A) {
        cout << *A << endl;
    }

    cout << endl;

    a.pop(8);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (A = a.pbegin(); A != a.pend(); ++A) {
        cout << *A << endl;
    }



    //Пример 2. Левый Правый поворот
    cout << "Left Right rotation"s << endl;
    Tree<int> b;
    b.insert(13);
    b.insert(10);
    b.insert(15);
    b.insert(5);
    b.insert(11);
    b.insert(16);
    b.insert(4);
    b.insert(6);
    cout << endl;
    Tree<int>::P_Iterator B;
    cout << "iterator with parent ptr\n";
    for (B = b.pbegin(); B != b.pend(); ++B) {
        cout << *B << endl;
    }
    cout << endl;

    b.insert(7);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (B = b.pbegin(); B != b.pend(); ++B) {
        cout << *B << endl;
    }

    //Пример 3. Левый поворот
    cout << "Left rotation"s << endl;
    Tree<int> c;
    c.insert(30);
    c.insert(5);
    c.insert(35);
    c.insert(32);
    c.insert(40);
   
    cout << endl;
    Tree<int>::P_Iterator C;
    cout << "iterator with parent ptr\n";
    for (C = c.pbegin(); C != c.pend(); ++C) {
        cout << *C << endl;
    }
    cout << endl;

    c.insert(45);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (C = c.pbegin(); C != c.pend(); ++C) {
        cout << *C << endl;
    }

    //Пример 4. Правый Левый поворот
    cout << "Right Left rotation"s << endl;
    Tree<int> d;
    d.insert(5);
    d.insert(2);
    d.insert(7);
    d.insert(1);
    d.insert(4);
    d.insert(6);
    d.insert(9);
    d.insert(3);
    d.insert(16);
    int x = 100;
    cout << endl;
    cout << "Search " << x << (d.Search(x) ? " Yes" : " No") << endl;
    x = 9;
    cout << "Search " << x << (d.Search(x) ? " Yes" : " No") << endl;
    cout << endl;
    Tree<int>::P_Iterator D;
    cout << "iterator with parent ptr\n";
    for (D = d.pbegin(); D != d.pend(); ++D) {
        cout << *D << endl;
    }
    cout << endl;

    d.insert(15);
    cout << endl;
    cout << "iterator with parent ptr\n";
    for (D = d.pbegin(); D != d.pend(); ++D) {
        cout << *D << endl;
    }
  

   

   /*Tree<int> a;
   // a.create(15);
    a.insert(15);
    a.insert(21);
    a.insert(8);
    a.insert(10);
    a.insert(5);
    a.insert(17);
    a.insert(28);
    a.insert(3);
    a.insert(4);
    Tree<int>::P_Iterator i;
    cout << "iterator with parent ptr\n";
    for (i = a.pbegin(); i != a.pend(); ++i) {
        cout << *i << endl;
    }
    cout << endl;
    a.pop(4); //удаление с 2 потомками
    cout << endl;
  // a.pop(8);
   // a.pop(28);
   // a.pop(3);
  //  a.pop(15);
  //  a.pop(17);
    for (i = a.pbegin(); i != a.pend(); ++i) {
        cout << *i << endl;
    }
    

   /*Tree<int> b;
    // a.create(15);
    b.insert(44);
    b.insert(17);
    b.insert(62);
    b.insert(10);
    b.insert(32);
    b.insert(50);
    b.insert(78);
    b.insert(21);
    b.insert(48);
    b.insert(54);
    b.insert(72);
    b.insert(88);
    b.insert(45);
    b.insert(49);
    b.insert(52);
    b.insert(56);
    b.insert(81);
    b.insert(92);
   

    Tree<int>::P_Iterator j;
    cout << "iterator with parent ptr\n";
    for (j = b.pbegin(); j != b.pend(); ++j) {
        cout << *j << endl;
    }
    cout << endl;
        b.pop(32);
        for (j = b.pbegin(); j != b.pend(); ++j) {
            cout << *j << endl;
        }

        */
    
   /* Tree<int> c;
    c.insert(4);
    c.insert(2);
    c.insert(5);
    c.insert(1);
    //c.insert(3);

    Tree<int>::P_Iterator k;
    cout << "iterator with parent ptr\n";
    for (k = c.pbegin(); k != c.pend(); ++k) {
        cout << *k << endl;
    }
    cout << endl;
    c.pop(2);
    cout << endl;
    for (k = c.pbegin(); k != c.pend(); ++k) {
        cout << *k << endl;
    }
  */

   /* Tree<int> d;
    // a.create(15);
    d.insert(13);
    d.insert(10);
    d.insert(15);
    d.insert(5);
    d.insert(11);
    d.insert(16);
    d.insert(4);
    d.insert(6);
    cout << endl;
    Tree<int>::P_Iterator D;
    cout << "iterator with parent ptr\n";
    for (D = d.pbegin(); D != d.pend(); ++D) {
        cout << *D << endl;
    }
    cout << endl;
    d.insert(7);
    cout << endl;
    for (D = d.pbegin(); D != d.pend(); ++D) {
        cout << *D << endl;
    }
   /* d.insert(48);
    d.insert(54);
    d.insert(72);
    d.insert(88);
    d.insert(45);
    d.insert(49);
    d.insert(52);
    d.insert(56);
    d.insert(81);*/
   
 //   return 0;
//}
