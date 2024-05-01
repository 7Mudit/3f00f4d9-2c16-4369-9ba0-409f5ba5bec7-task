#include <iostream>
// #include </Users/mudit/Desktop/Invisible/c++ pointer/code.cpp>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node
{
public:
    Node *link;
    int data;
};
void PrintList(Node *head)
{
    while (head != nullptr)
    {
        cout << head->data << " -> ";
        head = head->link;
    }
    cout << "NULL\n";
}

// model's wrong function

// void MakeOddsAndEvensMeshedAtFront(Node *&headPtr)
// {
//     if (!headPtr || !headPtr->link)
//     {
//         return; // Empty list or single node, no need to reorder
//     }

//     Node *oddEnd = nullptr, *evenEnd = nullptr;
//     Node *oddHead = nullptr, *evenHead = nullptr;
//     Node *curr = headPtr;

//     while (curr)
//     {
//         Node *next = curr->link;

//         if (curr->data % 2 == 0)
//         {
//             if (evenEnd)
//             {
//                 evenEnd->link = curr;
//             }
//             else
//             {
//                 evenHead = curr;
//             }
//             evenEnd = curr;
//         }
//         else
//         {
//             if (oddEnd)
//             {
//                 oddEnd->link = curr;
//             }
//             else
//             {
//                 oddHead = curr;
//             }
//             oddEnd = curr;
//         }
//         curr->link = nullptr;
//         curr = next;
//     }
//     if (headPtr->data % 2 == 0)
//     {
//         headPtr = evenHead;
//         if (evenEnd)
//         {
//             evenEnd->link = oddHead;
//         }
//     }
//     else
//     {
//         headPtr = oddHead;
//         if (oddEnd)
//         {
//             oddEnd->link = evenHead;
//         }
//     }
// }

// Updated correct code
void MakeOddsAndEvensMeshedAtFront(Node *&headPtr)
{
    if (!headPtr || !headPtr->link)
        return;

    Node *oddHead = nullptr, *oddTail = nullptr;
    Node *evenHead = nullptr, *evenTail = nullptr;
    Node *curr = headPtr;

    while (curr)
    {
        Node *next = curr->link;
        curr->link = nullptr;

        if (curr->data % 2 == 0)
        {
            if (evenTail)
            {
                evenTail->link = curr;
            }
            else
            {
                evenHead = curr;
            }
            evenTail = curr;
        }
        else
        {
            if (oddTail)
            {
                oddTail->link = curr;
            }
            else
            {
                oddHead = curr;
            }
            oddTail = curr;
        }
        curr = next;
    }

    Node *newHead = nullptr, *newTail = nullptr;
    bool oddTurn = (headPtr->data % 2 != 0);

    while (oddHead || evenHead)
    {
        Node **chosenList = oddTurn ? &oddHead : &evenHead;

        if (*chosenList)
        {
            if (newTail)
            {
                newTail->link = *chosenList;
            }
            else
            {
                newHead = *chosenList;
            }
            newTail = *chosenList;
            *chosenList = (*chosenList)->link;
        }
        oddTurn = !oddTurn;
    }
    headPtr = newHead;
}

void SeedRand()
{
    srand(static_cast<unsigned>(time(NULL)));
}

int BoundedRandomInt(int lowerBound, int upperBound)
{
    return rand() % (upperBound - lowerBound + 1) + lowerBound;
}

int ListLengthCheck(Node *head, int whatItShouldBe)
{
    int count = 0;
    Node *current = head;
    while (current != nullptr)
    {
        current = current->link;
        count++;
    }
    return count == whatItShouldBe ? 0 : (count < whatItShouldBe ? -1 : 1);
}

bool match(Node *head, const int procInts[], int procSize)
{
    Node *current = head;
    int index = 0;
    while (current != nullptr && index < procSize)
    {
        if (current->data != procInts[index])
        {
            return false;
        }
        current = current->link;
        index++;
    }
    return index == procSize && current == nullptr;
}

void ShowArray(const int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

void InsertAsTail(Node *&head, int newData)
{
    Node *newNode = new Node;
    newNode->data = newData;
    newNode->link = nullptr;
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->link != nullptr)
        {
            temp = temp->link;
        }
        temp->link = newNode;
    }
}

int FindListLength(Node *head)
{
    int length = 0;
    Node *current = head;
    while (current != nullptr)
    {
        length++;
        current = current->link;
    }
    return length;
}

void ListClear(Node *&head, bool deleteData)
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->link;
        if (deleteData)
        {
            delete current;
        }
        current = next;
    }
    head = nullptr;
}

void ShowAll(ostream &os, Node *head)
{
    Node *current = head;
    while (current != nullptr)
    {
        os << current->data << " ";
        current = current->link;
    }
    os << endl;
}

int main()
{
    int testCasesToDo = 750000, testCasesDone = 0, loSize = 1, hiSize = 25, loValue = 0, hiValue = 9;
    int numInts, numOdds, numEvens, intCount, newInt, iLenChk, iOdd, iEven, iProc;
    int *rawInts = nullptr, *procInts = nullptr, *rawOddInts = nullptr, *rawEvenInts = nullptr;
    Node *head = nullptr;

    MakeOddsAndEvensMeshedAtFront(head);
    cout << "================================" << endl;
    cout << "passed crash test on empty list" << endl;

    do
    {
        ++testCasesDone;
        numInts = BoundedRandomInt(loSize, hiSize);
        numOdds = numEvens = 0;
        rawInts = new int[numInts];
        procInts = new int[numInts];
        rawOddInts = new int[numInts];
        rawEvenInts = new int[numInts];

        intCount = 0;
        while (intCount < numInts)
        {
            newInt = BoundedRandomInt(loValue, hiValue);
            rawInts[intCount++] = newInt;
            if (newInt % 2)
            {
                rawOddInts[numOdds++] = newInt;
            }
            else
            {
                rawEvenInts[numEvens++] = newInt;
            }
            InsertAsTail(head, newInt);
        }

        iOdd = iEven = iProc = 0;
        if (rawInts[0] % 2)
        {
            while (iProc < numInts)
            {
                if (iOdd < numOdds)
                {
                    procInts[iProc++] = rawOddInts[iOdd++];
                }
                if (iEven < numEvens)
                {
                    procInts[iProc++] = rawEvenInts[iEven++];
                }
            }
        }
        else
        {
            while (iProc < numInts)
            {
                if (iEven < numEvens)
                {
                    procInts[iProc++] = rawEvenInts[iEven++];
                }
                if (iOdd < numOdds)
                {
                    procInts[iProc++] = rawOddInts[iOdd++];
                }
            }
        }

        MakeOddsAndEvensMeshedAtFront(head);
        iLenChk = ListLengthCheck(head, numInts);
        if (iLenChk != 0)
        {
            if (iLenChk == -1)
            {
                cout << "Node-count error ... too few ... (on test case "
                     << testCasesDone << ") ... " << endl;
                cout << "test_case: ";
                ShowArray(rawInts, numInts);
                cout << "#expected: " << numInts << endl;
                cout << "#returned: " << FindListLength(head) << endl;
            }
            else
            {
                cout << "Node-count error ... too many (circular list?) ... (on test case "
                     << testCasesDone << ") ... " << endl;
                cout << "test_case: ";
                ShowArray(rawInts, numInts);
                cout << "#expected: " << numInts << endl;
                cout << "returned # is higher (may be infinite)" << endl;
            }
            exit(EXIT_FAILURE);
        }
        if (!match(head, procInts, numInts))
        {
            cout << "Contents error ... mismatch found in value or order ... (on test case "
                 << testCasesDone << ") ... " << endl;
            cout << "initial: ";
            ShowArray(rawInts, numInts);
            cout << "ought2b: ";
            ShowArray(procInts, numInts);
            cout << "outcome: ";
            ShowAll(cout, head);
            exit(EXIT_FAILURE);
        }

        if (testCasesDone % 10000 == 0)
        {
            cout << "================================" << endl;
            clog << "testing case " << testCasesDone
                 << " of " << testCasesToDo << endl;
            clog << "================================" << endl;
            cout << "initial: ";
            ShowArray(rawInts, numInts);
            cout << "ought2b: ";
            ShowArray(procInts, numInts);
            cout << "outcome: ";
            ShowAll(cout, head);
        }

        ListClear(head, 1);
        delete[] rawInts;
        delete[] procInts;
        delete[] rawOddInts;
        delete[] rawEvenInts;
        rawInts = procInts = rawOddInts = rawEvenInts = nullptr;

    } while (testCasesDone < testCasesToDo);
    cout << "================================" << endl;
    cout << "test program terminated normally" << endl;
    cout << "================================" << endl;

    return EXIT_SUCCESS;
}
