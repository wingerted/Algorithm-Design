#include <iostream>
#include <list>
#include <string>

#define MAX_MEMORY 32767

using namespace std;

int FindFirstAssign(list< list<int> > &memory,  list<int>::size_type application) {
  int min = MAX_MEMORY;

  for (list< list<int> >::iterator iter=memory.begin(); iter!=memory.end(); ++iter) {
    if (iter->size() >= application) {
      for (int i=0; i!=application; ++i) {
        iter->pop_back();
      }
      return iter->back() + 1;
    }   
  }
  
  return -1;
}


int FindBestAssign(list< list<int> > &memory, list<int>::size_type application) {
  list< list<int> >::iterator min_iter = memory.end();
  int min = MAX_MEMORY;
 
  for (list< list<int> >::iterator iter=memory.begin(); iter!=memory.end(); ++iter) {
    int test = iter->size() - application;
    if (test>=0 && test<min) {
      min = test;
      min_iter = iter;
    }   
  }
  if (min_iter != memory.end()) {
    for (int i=0; i!=application; ++i) {
      min_iter->pop_back();
    }
    return min_iter->back() + 1;
  } else {
    return -1;
  }
}

bool Accept(list< list<int> > &memory, int address, int size) {
  if (address+size > MAX_MEMORY){
    return false;
  }
  
  for (list< list<int> >::reverse_iterator riter=memory.rbegin(); riter!=memory.rend(); ++riter) {
    if (riter->back() >= address) {
      continue;
    } else if (riter->back()+1 == address) {
      list< list<int> >::iterator iter = riter.base();
      iter--;

      if (++iter!=memory.end() && iter->front()<address+size) {
        return false;
      } else if (iter!=memory.end() && iter->front()==address+size) {
        size += iter->size();
        iter = memory.erase(iter);
        --iter;

        for (int i=0; i!=size; ++i) {
          iter->push_back(address++);
        }
               
        return true;
      } else {
        --iter;

        for (int i=0; i!=size; ++i) {
          iter->push_back(address++);
        }

        return true;
      }
    } else {
      list< list<int> >::iterator iter = riter.base();
      iter--;

      if (++iter!=memory.end() && iter->front()<address+size) {
        return false;
      } else if (iter!=memory.end() && iter->front()==address+size) {
        size += iter->size();
        iter = memory.erase(iter);
        --iter;

        list<int> new_block;

        for (int i=0; i!=size; ++i) {
          new_block.push_back(address++);
        }

        memory.insert(iter, new_block);
               
        return true;
      } else {
        if (iter!=memory.end()) {
          --iter;
        }
        list<int> new_block;

        for (int i=0; i!=size; ++i) {
          new_block.push_back(address++);
        }

        memory.insert(iter, new_block);

        return true;
      }
    }

    return false;
  }

  return false;
}


int DoProcess(string way, list< list<int> > &memory, list<int>::size_type application) {  if (way == "best") {    return FindBestAssign(memory, application);  } else if (way == "first") {    return FindFirstAssign(memory, application);  }  return -2;
}

void Display(list< list<int> > &memory) {
  cout << "\nIndex\t" << "Address\t" << "End\t" << "Size" << endl;
  int index = 1;
  for (list< list<int> >::iterator iter=memory.begin(); iter!=memory.end(); ++iter, ++index) {
    cout << index << "\t" << iter->front() << "\t" << iter->back() << "\t" << iter->size() << endl;
  }
  cout << endl;
}

int main()
{  list< list<int> > memory;
  list<int> block; 
  for (int i=0; i!=MAX_MEMORY; ++i) {
    block.push_back(i);
  }
  memory.push_back(block);

  Display(memory);

  cout << "Input the way (best or first): ";  string way;  cin >> way;  while (true) {    cout << "Assign or Accept: " ;    string type;    cin >> type;    if (type == "as") {      cout << "Input APPLICATION: ";      list<int>::size_type application;      cin >> application;             int flag = DoProcess(way, memory, application);            if (flag == -1 ) {        cout << "Too large application!" << endl;      } else if (flag != -2){        cout << "SUCCESS!!!  ADDRESS=" << flag << endl;      } else {        cout << "Choice Wrong !" << endl;      }      Display(memory);    } else if (type == "ac") {
        cout << "Input adr and size: ";
        int adr;
        int size;
        cin >> adr >> size;

        if (Accept(memory, adr, size)) { 
          Display(memory);
        } else {
          cout << "Memory Error !" << endl;
        }
      }    }
    return 0;}