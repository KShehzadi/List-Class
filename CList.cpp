#include <iostream>
#include "Node.cpp"

using namespace std;

class CList
{
public:
  Node* head;
  int count;

  CList();
  CList(Node* &ptr);
  CList(const CList &src);
  ~CList();
  CList& operator = (const CList &src);

  CList& Insert(Node* &ptr);
  Node* Remove();
  CList& InsertAt(Node* &ptr, int index);
  Node* RemoveAt(int index);
  int SearchNode(Node* ptr);
  int SearchNodeFromIndex(Node* ptr, int index);
  void SwapNodesWithIndices(int index1, int index2);
  void Reverse();
  void SwapNodeAtIndex(Node* &ptr, int index);
  void WriteToFile(ofstream &ofile);
  void ReadFromFile(ifstream &infile);
  void Print() const;
  void PrintRev() const;
};

void printF(Node* ptr)
{
  if(ptr)
  {
    ptr->print();
    printF(ptr->next);
  }
}

void printR(Node* ptr) // cant be reference type bcz we'll create multiple ptrs
{
  if(ptr)
  {
    printR(ptr->next);
  }
  else
  {
    return;
  }
  ptr->print();
}

void deleteNodes(Node* ptr)
{
  if(ptr)
  {
    deleteNodes(ptr->next);
  }
  else
  {
    return ;
  }
  delete ptr;
}
Node* Copy(Node * ptr)
{
	Node * n;
	if(!ptr)
	{
		return ptr;
	}
	else
	{
		n = new Node(*ptr);
		n-> next = Copy(ptr->next);
	}
}
CList::CList():head(NULL), count(0)
{

}

CList::CList(Node* &ptr):count(1),head(ptr)
{

}

CList::CList(const CList &src)
{//--------------------Changed

this->head = Copy(src.head);
this->count = src.count;
 /* this->count = src.count;
  Node dptr;
  Node* sptr;
  dptr = sptr = this->head = src.head;
  if(src.head)
  {*
    dptr = this->head = new Node(*sptr);
    sptr = sptr->next;
    while(sptr)
    {
      dptr->next = new Node(*sptr);
      sptr = sptr->next;
      dptr = dptr->next;
    }

  }

*/

  /*if(src.head)
  {
    dptr = new Node(*src.head);
    while(sptr)
    {
      sptr = sptr->next;
      dptr->next = new Node(*sptr);
      dptr = dptr->next;
    }
  }*/
}

CList::~CList()
{
  /*
  Node* sptr = this->head;
  while(this->head)
  {
    this->head = this->head->next;
    delete sptr;
    sptr = this->head;
  }*/

  deleteNodes(head);

}

CList& CList::operator = (const CList& src)
{ //----------------Changed
  deleteNodes(this->head);

  this->count = src.count;
  Node* dptr;
  Node* sptr;
  dptr = sptr = this->head = src.head;
  if(src.head)
  {
    dptr = this->head = new Node(*sptr);
    sptr = sptr->next;
    while(sptr)
    {
      dptr->next = new Node(*sptr);
      sptr = sptr->next;
      dptr = dptr->next;
    }
  }
  return *this;

  /*Node* sptr = src.head;
  Node* dptr = this->head;
  this->count = src.count;

  while(this->head)
  {
    this->head = this->head->next;
    delete dptr;
    dptr = this->head;
  }

  if(src.head)
  {
    dptr = new Node(*src.head);
    while(sptr)
    {
      sptr = sptr->next;
      dptr->next = new Node(*sptr);
      dptr = dptr->next;
    }
  }*/
}

CList& CList::Insert(Node* &ptr)
{
  ptr->next = this->head;
  this->head = ptr;
  ptr = NULL;
  this->count++;
  return *this;
}

Node* CList::Remove()
{
  Node* ptr = this->head;
  if(this->head)
  {
    this->head = this->head->next;
    ptr->next = NULL;
    count--;
  }
  return ptr;
}

CList& CList::InsertAt(Node* &ptr, int index)
{
  if(index <= 0 || count == 0)
  {
    return Insert(ptr);
  }
  else if(index > count)
  {
    index = count; // Why not count - 1 ??
  }

  Node* rptr = head;
  for(int i = 1; i < index; i++)
  {
    rptr = rptr->next;
  }
  ptr->next = rptr->next;
  rptr->next = ptr;
  count++;
  return *this;
}

Node* CList::RemoveAt(int index)
{
  if(index <= 0)
  {
    return Remove();
  }
  if(index >= count)
  {
    index = count - 1;
  }

  Node* ptr;
  Node* rptr = head;
  for(int i = 1; i < index; i++)
  {
    rptr = rptr->next;
  }
  ptr = rptr->next;
  rptr->next = ptr->next;
  ptr->next = NULL;
  count--;
  return ptr;
}

int CList::SearchNode(Node* ptr)
{
  Node* rptr = this->head;
  for(int i = 0; i < count; i++)
  {
    if(!ptr->CompareWith(*rptr)) return i;
    else rptr = rptr->next;
  }
  return -1;
}

int CList::SearchNodeFromIndex(Node* ptr, int index)
{
  Node* rp = this->head;
  int i;
  if(index < 0) index = 0;
  if(index >= count) index = count - 1;

  for(i = 0 ; i < index; i++) // correction: 0 instead of 1??
  {
    rp = rp->next;
  }
  for(int j = i; j < count; j++)
  {
    if(!ptr->CompareWith(*rp))
    {
      return j;
    }
    else
    {
      rp = rp->next;
    }
  }
  return -1;
}

void CList::SwapNodesWithIndices(int index1, int index2)
{
  if(index1 < 0) index1 = 0;
  if(index1 >= count) index1 = count - 1;
  if(index2 < 0) index2 = 0;
  if(index2 >= count) index2 = count - 1;

  Node* p;

  if(index1 < index2)
  {
    p = RemoveAt(index2);
    InsertAt(p, index1);

    p= RemoveAt(index1 + 1);
    InsertAt(p, index2);
  }
  else if(index1 > index2)
  {
    p = RemoveAt(index1);
    InsertAt(p, index2);

    p = RemoveAt(index2 + 1);
    InsertAt(p, index1);
  }
}

void CList::Reverse()
{
  Node** arr = new Node*[count];
  if(count < 2) return;
  Node* rp = this->head;
  for(int i = 0; i < count; i++)
  {
    arr[i] = rp;
    rp = rp->next;
  }
  for(int i = 0; i < count; i++)
  {
    arr[i]->next = arr[i-1];
  }
  arr[0]->next = NULL;
  this->head = arr[count - 1];
  delete[] arr;
}

void CList::SwapNodeAtIndex(Node* &ptr, int index)
{
  InsertAt(ptr, index);
  ptr = RemoveAt(index + 1);
}

void CList::WriteToFile(ofstream &ofile)
{
  Node* rp = this->head;
  ofile.write((char*) &this->count, sizeof(this->count));
  for(int i = 0; i < this->count; i++)
  {
    rp->WriteToFile(ofile);
    rp = rp->next;
  }
}

void CList::ReadFromFile(ifstream &infile)
{
  Node* bp;
  Node* rp;
  int newCount;
  infile.read((char*) &newCount, sizeof(newCount));
  if(this->count >= newCount)
  {
    rp = this->head;
    for(int i = 0; i < newCount; i++)
    {
      rp->ReadFromFile(infile);
      bp = rp;
      rp = rp->next;
    }
    bp->next = NULL;
    this->count = newCount;
    while(rp)
    {
      bp = rp;
      delete bp;
      rp = rp->next;
    }
  }
  else
  {
    rp = head;
    for(int i = 0; i < this->count; i++)
    {
      rp->ReadFromFile(infile);
      bp = rp;
      rp = rp->next;
    }
    if(this->count == 0 && newCount > 0)
    {
    	bp = head = new Node();
		bp->ReadFromFile(infile); 
	}
    for(int k = 1; k < (newCount - this->count); k++)
    {
      rp = new Node();
      rp->ReadFromFile(infile);
      bp->next = rp;
      bp = rp;
    }
    bp->next = NULL;
    this->count = newCount;
  }
}

void CList::Print() const
{
  void printF(Node* ptr);
  printF(this->head);
}

void CList::PrintRev() const
{
  void printR(Node* ptr);
  printR(this->head);
}

int main()
{
  ofstream ofile;
  ofile.open("ofile.txt");

  Node* ptr1 = new Node(1);
  Node* ptr2 = new Node(2);
  Node* ptr3 = new Node(3);
  Node* ptr4 = new Node(4);
  Node* ptr5 = new Node(5);
  Node* ptr6 = new Node(6);
  Node* ptr7 = new Node(7);
  Node* ptr8 = new Node(8);


  CList L1;
  L1.Insert(ptr1);
  L1.Insert(ptr2);
  L1.Insert(ptr3);
  L1.Insert(ptr4);
  L1.Insert(ptr5);
  L1.Insert(ptr6);
  L1.Insert(ptr7);
  L1.Insert(ptr8);
  CList L3(L1);
  L3.Print();
  cout<< endl;
  L1.Remove();
  L1.Remove();
  L1.Print();
  cout<< endl;
  L3.WriteToFile(ofile);
  L1.WriteToFile(ofile);
  ofile.close();
  ifstream infile;
  infile.open("ofile.txt");
  CList L2;
  L2.ReadFromFile(infile);
  cout<< "yayyyyy"<< endl;
  L2.Print();
  L2.ReadFromFile(infile);
  cout<< "pleeeaseeeee"<< endl;
  L2.Print();
 
 
  return 0;
}
