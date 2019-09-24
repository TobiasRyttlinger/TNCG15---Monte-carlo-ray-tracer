// =======================================================
// Ex2
// Name:
// Personal number:
// =======================================================

#include <iostream>

using namespace std;


/********************************
* Class List definition         *
*********************************/

class List
{
public:

    //Default constructor
    List(); //Hej

    //Destructor
    ~List();

    //Exercise a
    List& add(int i);

    //Exercise b
    List* copy_interval(int i, int j) const;

    //Copy constructor disabled
    List(const List &source) = delete;

    //Assignment operator disabled
    List& operator=(const List &source) = delete;

    friend ostream& operator<<(ostream& os, const List& L);

private:

    class Node
    {
        public:
            // Constructor
            Node (int i, Node* ptr):  value (i), next (ptr)
            { }

            int value;
            Node* next;

            friend ostream& operator<<(ostream &os, const List& L);
    };

    Node *head;
};

/*****************************************************
* Class List member functions implementation         *
******************************************************/

//Default constructor
List::List()
    : head(new Node (0, nullptr))  //dummy node
{

}

//Destructor
List::~List()
{
    Node *temp = head -> next;

    while (temp != nullptr)
    {
        delete head;
        head = temp;
        temp = temp -> next;
    }

    delete head;

    //cout << "Destructor called ..." << endl;
}

//Exercise a
List& List::add(int i)
{
    //Add a new node to the beginning of the list
    head->next= new Node(i, head->next);

    return *this;
}

 //Exercise b
List* List::copy_interval(int i, int j) const
{
    List* res = new List;
    Node* ptr1 = res->head;

    Node* ptr2 = head->next;

    while (ptr2 != nullptr)
    {
        if (ptr2->value >= i && ptr2->value <= j)
        {
            ptr1->next = new Node(ptr2->value, nullptr);
            ptr1 = ptr1->next;
        }

        ptr2 = ptr2->next;
    }

    return res;
}


ostream& operator<< (ostream& os, const List& L)
{
    List::Node *ptr = L.head->next;

    if (ptr == nullptr)
    {
        os << "The list is empty!!" << endl;
        return os;
    }

    while (ptr != nullptr)
    {
        os << ptr->value << " ";
        ptr= ptr->next;
    }

    return os;
}


/**************************************
* Main function  -- test              *
* DELIVER UNMODIFIED                  *
***************************************/

int main()
{
    /*********************************************
    * Test 1: add                                *
    **********************************************/
    cout << "\n** Test 1" << endl << endl;

    List L1;

    cout << "List L1: " << L1 << endl;

    L1.add(1).add(-1).add(2).add(10).add(-2).add(0);
    cout << "List L1: " << L1 << endl;

    /*********************************************
    * Test 2: copy_interval                      *
    **********************************************/
    cout << "\n** Test 2" << endl << endl;

    List* L2 = L1.copy_interval(-5,0);

    cout << "List L2: " << *L2 << endl;

    delete L2;

    /*********************************************
    * Test 3: copy_interval                      *
    **********************************************/
    cout << "\n** Test 3" << endl << endl;

    const List L3;

    L2 = L3.copy_interval(5,5);

    cout << "List L2: " << *L2 << endl;

    delete L2;

    return 0;
}
