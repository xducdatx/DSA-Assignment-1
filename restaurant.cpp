#include "main.h"
void recentTableID(restaurant *r, int ID)
{
    while (r -> recentTable -> ID != ID) r -> recentTable = r -> recentTable -> next;
}
bool isEmpty(restaurant *r)
{
    if (r -> recentTable -> age == 0 && r -> recentTable -> name == "") return true;
    return false;
}
bool IDisExisting(restaurant *r, int ID)
{
    bool Exist = false;
    for (int i = 1; i <= MAXSIZE; i++)
    {
        if (r -> recentTable -> ID == ID)
        {
            Exist = true;
            break;
        }
         r -> recentTable = r -> recentTable -> next;
    }
    return Exist;
}
struct node
{
    int ID;
    string name;
    int age;
    int Enter;
    node *next;
};
node *createNode(int ID, string name, int age, int Enter = 0)
{
    node *temp = new node;
    temp -> ID = ID;
    temp -> name = name;
    temp -> age = age;
    temp -> Enter = Enter;
    temp -> next = NULL;
    return temp;
}
node *addTail(node *head, int ID, string name, int age, int Enter = 0)
{
    node *p = head;
    while (p -> next != NULL)
    {
        p = p -> next;
    }
    node *temp = new node;
    temp -> ID = ID;
    temp -> name = name;
    temp -> age = age;
    temp -> Enter = Enter;
    temp -> next = NULL;
    p -> next = temp;
    return head;
}
node *deleteAt(node *head, int k)
{
    node *p = head;
    if (k == 0)
    {
        head = head -> next;
        delete p;
        return head;
    }
    else
    {
        for (int i = 0; i < k - 1; i++)
        {
            p = p -> next;
        }
        node * temp = p -> next;
        p -> next = p -> next -> next;
        delete(temp);
        return head;
    }
}
node *deleteTail(node *head)
{
    node *p = head;
    while (p -> next -> next != NULL)
    {
        p = p -> next;
    }
    delete(p -> next);
    p -> next = NULL;
    return head;
}
    node* Reverse(node* need) {
        node* current = need;
        node* prev = NULL;
        node* next = NULL;
        while (current != NULL) 
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        need = prev;
        return need;
    }
void swap(node *sw1, node *sw2)
{
    int ID = sw1 -> ID;
    string name = sw1 -> name;
    int age = sw1 -> age;
    int Enter = sw1 -> Enter;
    sw1 -> ID = sw2 -> ID;
    sw1 -> name = sw2 -> name;
    sw1 -> age = sw2 -> age;
    sw1 -> Enter = sw2 -> Enter;
    sw2 -> ID = ID;
    sw2 -> name = name;
    sw2 -> age = age;
    sw2 -> Enter = Enter;
}
void selectionSortfollowNum(node* head, int num) {
    node* i = head;
    while (i != NULL && num != 0) 
    {
        node* j = i -> next;
        node* max = i;
        while (j != NULL) 
        {
            if (j -> age > max -> age || (j -> age == max -> age && j -> Enter < max -> Enter)) 
            {
                max = j;
            }
            j = j -> next;
        }
        if (i != max) swap(i, max);
        i = i -> next;
        num--;
    }
}
void selectionSort(node *head)
{
    node* i = head;
    while (i != NULL) 
    {
        node* j = i -> next;
        node* max = i;
        while (j != NULL) 
        {
            if (j -> age > max -> age || (j -> age == max -> age && j -> Enter < max -> Enter)) 
            {
                max = j;
            }
            j = j -> next;
        }
        if (i != max) swap(i, max);
        i = i -> next;
    }
}
bool maxQueue(node *head)
{
    int countQueue = 0;
    node *p = head;
    while (p != NULL)
    {
        p = p -> next; 
        countQueue++;
    }
    if (countQueue == MAXSIZE) return true;
    return false;
}
node *head = NULL;
node *headVoid = NULL;
node *Order = NULL;
int LastEnter = -1;
int OrderEnter = 1;
void DoingREG(restaurant *r, string Infor)
{
bool successBooked = false;
bool testREG = false;
string test = Infor;
test = test.substr(test.find(' ') + 1);
test = test.substr(test.find(' ') + 1);
if (test.find(' ') == std::string::npos) testREG = true;
if (testREG) // XỬ LÍ TRƯỜNG HỢP NHÀ HÀNG CÒN TRỐNG VÀ KHÁCH KO CÓ ID
{
    Infor = Infor.substr(Infor.find(' ') + 1);
    string Name = Infor.substr(0, Infor.find(' '));
    string Age = Infor.substr(Infor.find(' ') + 1);
    if (stoi(Age) >= 16 && stoi(Age) <= 115){
    int minID = 99999;
    for (int i = 1; i<= MAXSIZE; i++)
    {
        int IDnow = r -> recentTable -> ID;
        if (IDnow < minID) minID = IDnow;
        r -> recentTable = r -> recentTable -> next;
    }
    recentTableID(r, minID);
    for (int i = 1; i <= MAXSIZE; i++)
    {
        if (isEmpty(r))
        {
            r -> recentTable -> name = Name;
            r -> recentTable -> age = stoi(Age);
            successBooked = true;
            LastEnter = r -> recentTable -> ID;
            if (Order == NULL)
            {
                Order = createNode(i, Name, stoi(Age));
            }
            else
            {
                node *p = Order;
                p = addTail(p, i, Name, stoi(Age));
            }
        }
        if (successBooked) break;
        r -> recentTable = r -> recentTable -> next;
    }
    if (successBooked == false) // NHÀ HÀNG ĐẦY THÊM VÀO HÀNG CHỜ
    {
        if (Order == NULL)
        {
             Order = createNode(0, Name, stoi(Age));
        }
        else
        {
            if (!maxQueue(head)){
            node *p = Order;
            p = addTail(p, 0, Name, stoi(Age));
            }
        }
        if (head == NULL)
        {
            head = createNode(0, Name, stoi(Age), OrderEnter);
            headVoid = createNode(0, Name, stoi(Age), OrderEnter);
            OrderEnter++;
        }
        else
        {
            if (!maxQueue(head)){
            node *p = head;
            p = addTail(p, 0, Name, stoi(Age), OrderEnter);
            }
            if (!maxQueue(headVoid)){
            node *p = headVoid;
            p = addTail(p, 0, Name, stoi(Age), OrderEnter);
            }
            OrderEnter++;
        }
    }
}
}
else // XỬ LÍ TRƯỜNG HỢP NHÀ HÀNG CÒN TRỐNG VÀ KHÁCH ĐẶT THEO ID
{
    Infor = Infor.substr(Infor.find(' ') + 1);
    string ID = Infor.substr(0, Infor.find(' '));
    Infor = Infor.substr(Infor.find(' ') + 1);
    string Name = Infor.substr(0, Infor.find(' '));
    string Age = Infor.substr(Infor.find(' ') + 1);
    if (stoi(Age) >= 16 && stoi(Age) <= 115){
    if (IDisExisting(r, stoi(ID))){
    recentTableID(r, stoi(ID));
    if(isEmpty(r))
    {
        r -> recentTable -> name = Name;
        r -> recentTable ->age = stoi(Age);
        LastEnter = r -> recentTable -> ID;
        if (Order == NULL)
        {
            Order = createNode(stoi(ID), Name, stoi(Age));
        }
        else
        {
            node *p = Order;
            p = addTail(p, stoi(ID), Name, stoi(Age));
        }
    }
    else
    {
        for (int i = 1; i <= MAXSIZE; i++)
        {
            if (isEmpty(r))
            {
                r -> recentTable -> name = Name;
                r -> recentTable ->age = stoi(Age);
                LastEnter = r -> recentTable -> ID;
                successBooked = true;
                if (Order == NULL)
                {
                    Order = createNode(i, Name, stoi(Age));
                }
                else
                {
                    node *p = Order;
                    p = addTail(p, stoi(ID), Name, stoi(Age));
                }
            }
            if (successBooked) break;
            r -> recentTable = r -> recentTable -> next;
        }
        if (successBooked == false) // NHÀ HÀNG ĐẦY THÊM VÀO HÀNG CHỜ
        {
            if (Order == NULL)
            {
                Order = createNode(stoi(ID), Name, stoi(Age));
            }
            else
            {
                if (!maxQueue(head)){
                node *p = Order;
                p = addTail(p, stoi(ID), Name, stoi(Age));
                }
            }
            if (head == NULL)
            {
                head = createNode(stoi(ID), Name, stoi(Age), OrderEnter);
                headVoid = createNode(stoi(ID), Name, stoi(Age), OrderEnter);
                OrderEnter++;
            }
            else
            {
                if (!maxQueue(head)){
                node *p = head;
                p = addTail(p, stoi(ID), Name, stoi(Age), OrderEnter);
                }
                if (!maxQueue(headVoid)){
                node *p = headVoid;
                p = addTail(p, stoi(ID), Name, stoi(Age), OrderEnter);
                }
                OrderEnter++;
            }
        }
    }
}
    else
    {
        bool successBooked = false;
        int minindex = 99999;
        for (int i = 1; i <= MAXSIZE; i++)
        {
            if (r -> recentTable -> ID < minindex)
            minindex = r -> recentTable -> ID;
            r -> recentTable = r -> recentTable -> next;
        }
        recentTableID(r, minindex);
        int flagREG = 0;
        for (int i = 1; i <= MAXSIZE; i++)
        {
            if (r -> recentTable -> ID > stoi(ID)) 
            {
                flagREG = r -> recentTable -> ID;
                break;
            }
             r -> recentTable = r -> recentTable -> next;
        }
        if (flagREG == 0)
        {
            recentTableID(r, minindex);
            for (int i = 1; i <= MAXSIZE ;i++)
            {
                if (isEmpty(r))
                {
                    r -> recentTable -> age = stoi(Age);
                    r -> recentTable -> name = Name;
                    if (Order == NULL)
                    {
                        Order = createNode(r -> recentTable -> ID, Name, stoi(Age));
                    }
                    else
                    {
                        node *p = Order;
                        p = addTail(p, r -> recentTable -> ID, Name, stoi(Age));
                    }
                    LastEnter = r -> recentTable -> ID;
                    successBooked = true; 
                    break;
                }
                r -> recentTable = r -> recentTable -> next;
            }
        }
        else
        {
            recentTableID(r, flagREG);
            for (int i = 1; i <= MAXSIZE ;i++)
            {
                if (isEmpty(r))
                {
                    r -> recentTable -> age = stoi(Age);
                    r -> recentTable -> name = Name;
                    if (Order == NULL)
                    {
                        Order = createNode(r -> recentTable -> ID, Name, stoi(Age));
                    }
                    else
                    {
                        node *p = Order;
                        p = addTail(p, r -> recentTable -> ID, Name, stoi(Age));
                    }
                    LastEnter = r -> recentTable -> ID;
                    successBooked = true; 
                    break;
                }
                r -> recentTable = r -> recentTable -> next;
            }
        }
        
        if (successBooked == false){
        if (Order == NULL)
        {
            Order = createNode(stoi(ID), Name, stoi(Age));
        }
        else
        {
            if (!maxQueue(head)){
            node *p = Order;
            p = addTail(p, stoi(ID), Name, stoi(Age));
            }
        }
        if (head == NULL)
            {
                head = createNode(stoi(ID), Name, stoi(Age), OrderEnter);
                headVoid = createNode(stoi(ID), Name, stoi(Age), OrderEnter);
                OrderEnter++;
            }
            else
            {
                if (!maxQueue(head)){
                node *p = head;
                p = addTail(p, stoi(ID), Name, stoi(Age), OrderEnter);
                }
                if(!maxQueue(headVoid)){
                node *p = headVoid;
                p = addTail(p, stoi(ID), Name, stoi(Age), OrderEnter);    
                }
                OrderEnter++;
            }
        }
    }
    }
}
}
bool MergedTable = false;
int flagREGM = -1;
table *KeepMergeTable = NULL;
int NumOfMergeTable = -1;
void DoingREGM(restaurant *r, string Infor)
{
        Infor = Infor.substr(Infor.find(' ') + 1);
        string Name = Infor.substr(0, Infor.find(' '));
        Infor = Infor.substr(Infor.find(' ') + 1);
        string Age = Infor.substr(0, Infor.find(' '));
        string Num = Infor.substr(Infor.find(' ') + 1);
        if (stoi(Age) >= 16 && stoi(Age) <= 115){
        int countTable = 0;
        bool temp = false;
        if (MergedTable == false)
        {
            recentTableID(r, 1);
            for(int i = 1; i <= MAXSIZE; i++)
            {
                if (isEmpty(r))
                {
                    countTable++;
                }
                else if (!isEmpty(r))
                {
                    countTable = 0;
                }
                if (countTable == stoi(Num))
                {
                    flagREGM = i- stoi(Num) + 1;
                    MergedTable = true;
                    temp = true;
                } 
                if (countTable > stoi(Num))
                {
                    flagREGM++;
                }
                r -> recentTable = r -> recentTable -> next;
            }
            if (stoi(Num) > 1){
            int countTable2 = 0 ;
            recentTableID(r, MAXSIZE - stoi(Num) + 2);
            for(int i = 0; i < stoi(Num) + stoi(Num) - 1; i++)
            {
                if (isEmpty(r))
                {
                    countTable2++;
                }
                else if (!isEmpty(r))
                {
                    countTable2 = 0;
                }
                if (countTable2 >= stoi(Num))
                {
                    MergedTable = true;
                    flagREGM = MAXSIZE - stoi(Num) + 2 + i - stoi(Num);
                } 
                 r -> recentTable = r -> recentTable -> next;
            }
            }
        }
        if (MergedTable && temp)
        {
            recentTableID(r, flagREGM);
            LastEnter = flagREGM;
            NumOfMergeTable = stoi(Num);
            if (KeepMergeTable == NULL)
            {
                KeepMergeTable = r -> recentTable -> next;
            }

            table *tableNext = r -> recentTable;
            for (int i = 0; i < stoi(Num); i++)
            {
                r -> recentTable = r -> recentTable -> next;
            }
            tableNext -> next = r -> recentTable;
            r -> recentTable = tableNext;
            r -> recentTable -> age = stoi(Age);
            r -> recentTable -> name = Name;
            if (Order == NULL)
            {
                Order = createNode(flagREGM, Name, stoi(Age));
            }
            else
            {
                node *p = Order;
                p = addTail(p, flagREGM, Name, stoi(Age));
            }
        }
    }
}
void DoingCLE(restaurant *r, string Infor)
{
    string ID = Infor.substr(Infor.find(' ') + 1);
    bool IDisExist = false;
    for (int i = 1; i <= MAXSIZE; i++)
    {
        if (r -> recentTable -> ID == stoi(ID))
        {
            IDisExist = true;
            break;
        }
            r -> recentTable = r -> recentTable -> next;
    }
    if (IDisExist && stoi(ID) >= 1 && stoi(ID) <= MAXSIZE)
    {
        recentTableID(r, stoi(ID));
        bool Can = false;
        if (stoi(ID) == flagREGM)
        {
            int countCLE = 0;
            for(node *p = Order; countCLE <= 2*MAXSIZE && p != NULL; p = p -> next)
            {
                if (r -> recentTable -> age == p -> age && r -> recentTable ->name == p -> name)
                {
                    Can = true;
                    break;
                }
                countCLE++;
            }
            if(Can) Order = deleteAt(Order, countCLE);
            recentTableID(r, stoi(ID));
            r -> recentTable -> next = KeepMergeTable;
            r -> recentTable -> age = 0;
            r -> recentTable -> name = "";
            LastEnter = r -> recentTable -> ID;
            if (head != NULL)
            {
                for (int i = 0; i  < NumOfMergeTable && head != NULL && headVoid != NULL; i++)
                {
                    if (head -> ID >= 1 && head -> ID <= 15)
                    {
                        string Doing = "REG " + to_string(head -> ID) + " " + head ->name + " " + to_string(head -> age);
                        DoingREG(r, Doing);
                        Order = deleteTail(Order);
                    }
                    else
                    {
                        string Doing = "REG " + head -> name + " " + to_string(head -> age);
                        DoingREG(r, Doing);
                        Order = deleteTail(Order);
                    }
                    int indexCLE = 0;
                    bool Delete = false;
                    node *run = headVoid;
                    for (int i = 0; i < MAXSIZE && head != NULL && headVoid != NULL; i++)
                    {
                        if (run -> age == head -> age && run -> name == head -> name)
                        {
                            Delete = true;
                            break;
                        }
                        indexCLE++;
                        run = run -> next;
                    }
                    if (Delete) headVoid = deleteAt(headVoid, indexCLE);
                    node *p = head;
                    head = head -> next;
                    delete p;
                }
            }
            flagREGM = -1;
            MergedTable = false;
            NumOfMergeTable = -1;
            KeepMergeTable = NULL;
        } 
        else
        {
            recentTableID(r, stoi(ID));
            int countCLE = 0;
            bool Can = false;
            for(node *p = Order; countCLE <= 2*MAXSIZE && p != NULL; p = p -> next)
            {
                if (r -> recentTable -> age == p -> age && r -> recentTable -> name == p -> name)
                {
                    Can = true;
                    break;
                }
                countCLE++;
            }
            if(Can) Order = deleteAt(Order, countCLE);
            r -> recentTable -> age = 0;
            r -> recentTable -> name = "";
            LastEnter = r -> recentTable -> ID;
            if (head != NULL)
            {
                bool CanCLE = false;
                r -> recentTable -> age = head -> age;
                r -> recentTable -> name = head -> name;
                int indexCLE1 = 0;
                node *p = headVoid;
                for (int i = 1; i <= MAXSIZE && head != NULL && headVoid != NULL; i++)
                {
                    if (p -> age == head -> age && p -> name == head -> name)
                    {
                        CanCLE= true;
                        break;
                    }
                    p = p -> next;
                    indexCLE1++;
                }
                if (CanCLE) headVoid = deleteAt(headVoid, indexCLE1);
                node *q = head;
                head = head -> next;
                delete q;
            }
        }
    }
}
void DoingPS(restaurant *r, string Infor)
{
    if (Infor == "PS")
    {
        if (Order == NULL)
        {
            cout << "Empty\n";
        }
        else
        {
            node *save = Reverse(Order);
            node *print = save;
            while(print != NULL)
            {
                cout << print -> name << "\n";
                print = print -> next;
            }
            Order = Reverse(save);
        }
    }
    else
    {
        if (Order == NULL) cout << "Empty\n";
        string Num = Infor.substr(Infor.find(' ') + 1);
        int countPS = 0;
        for (node *p = Order; p != NULL; p = p -> next)
        {
            countPS++;
        }
        if (stoi(Num) <= countPS)
        {
            node *save = Reverse(Order);
            node *print = save;
            for (int i = 0; i < stoi(Num); i++)
            {
                cout << print -> name << "\n";
                print = print -> next;
            }
            Order = Reverse(save);
        }
        else if (stoi(Num) > countPS && stoi(Num) <= 2*MAXSIZE)
        {
            node *save = Reverse(Order);
            node *print = save;
            while(print != NULL)
            {
                cout << print -> name << "\n";
                print = print -> next;
            }
            Order = Reverse(save);
        }
    }
}
void DoingPQ(restaurant *r, string Infor)
{
    if (Infor == "PQ")
    {
        if (headVoid == NULL)
        {
            cout << "Empty\n";
        }
        else
        {
            node *temp = headVoid;
            while (temp != NULL)
            {
                cout << temp -> name << "\n";
                temp = temp -> next;
            }
        }
    }
    else
    {
        string Num = Infor.substr(Infor.find(' ') + 1);
        if (stoi(Num) >= 1 && stoi(Num) <= MAXSIZE){
        if (headVoid == NULL)
        {
            cout << "Empty\n";
        }
        else
        {
            node *temp = headVoid;
            int count = 0;
            while (temp != NULL)
            {
                count++;
                temp = temp -> next;
            }
            if (stoi(Num) <= count)
            {
                node *temp = headVoid;
                for (int i = 0; i < stoi(Num); i++)
                {
                    cout << temp -> name << "\n";
                    temp = temp -> next;
                }
            }
            else
            {
                node *temp = headVoid;
                while (temp != NULL)
                {
                    cout << temp -> name << "\n";
                    temp = temp -> next;
                }
            }
        }
    }
    }
}
void DoingPT(restaurant *r)
{
    if (LastEnter >= 1 && LastEnter <= MAXSIZE){
    recentTableID(r, LastEnter);
    if (MergedTable)
    {
        for (int i = 1; i <= MAXSIZE - NumOfMergeTable + 1; i++)
        {
            if (!isEmpty(r)) cout << r -> recentTable -> ID << "-" << r -> recentTable ->  name << "\n";
            r -> recentTable = r -> recentTable -> next;
        }
    }
    else
    {
        for (int i = 1; i <= MAXSIZE; i++)
        {
            if (!isEmpty(r)) cout << r -> recentTable -> ID << "-" << r -> recentTable ->  name << "\n";
            r -> recentTable = r -> recentTable -> next;
        }
    }
}
}
void DoingSQ(restaurant *r, string Infor)
{
    string Num = Infor.substr(Infor.find(' ') + 1);
    if (head == NULL) cout << "Empty\n";
    else
    {
        int countSQ = 0;
        for (node *p = head; p != NULL; p = p -> next)
        {
            countSQ++;
        }
        if (stoi(Num) <= countSQ)
        {
            selectionSortfollowNum(head, stoi(Num));

        }
        else if(stoi(Num) > countSQ && stoi(Num) <= MAXSIZE)
        {
            selectionSort(head);
        }
            node *temp = head;
            while (temp != NULL)
            {
                cout << temp -> name << "\n";
                temp = temp -> next;
            }
    }
}
void simulate(string filename, restaurant* r)
{
ifstream file;
file.open(filename);
string x;
while(getline(file, x))
{
    if (x.substr(0, x.find(' ')) == "REG") DoingREG(r, x);
    if (x.substr(0, x.find(' ')) == "REGM") DoingREGM(r, x);
    if (x.substr(0, x.find(' ')) == "CLE") DoingCLE(r, x);
    if (x.substr(0, x.find(' ')) == "PS" || x == "PS") DoingPS(r, x);
    if (x.substr(0, x.find(' ')) == "PQ" || x == "PQ") DoingPQ(r, x);
    if (x == "PT") DoingPT(r);
    if (x.substr(0, x.find(' ')) == "SQ") DoingSQ(r, x);
}
file.close();
while (head != NULL)
{
    node *p = head;
    head = head -> next;
    delete p;
}
while (headVoid != NULL)
{
    node *p = headVoid;
    headVoid = headVoid -> next;
    delete p;
}
while(Order != NULL)
{
    node *p = Order;
    Order = Order -> next;
    delete p;
}

}

