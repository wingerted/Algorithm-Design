#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

bool IsSecurity(map< string, vector< vector<int> > > process_map, vector<int> available, list<string> &todo_list) {
  if (process_map.empty()) {
    return true;
  }

  map< string, vector<int> > need;

  for (map< string, vector< vector<int> > >::iterator iter=process_map.begin(); iter!=process_map.end(); ++iter) {
    vector<int> data;
    for (vector<int>::iterator miter=iter->second[0].begin(), aiter=iter->second[1].begin();
      miter!=iter->second[0].end() && aiter!=iter->second[1].end();
      ++miter, ++aiter) {
        data.push_back(*miter - *aiter);
    }
    need.insert(pair< string, vector<int> >(iter->first, data));
  }

  list<string> test;
  for (map< string, vector<int>>::iterator iter=need.begin(); iter!=need.end(); ++iter) {
    bool flag = true;

    for (int i=0; i!=available.size(); ++i) {
      if (available[i] < iter->second[i]) {
        flag = false;
      }
    }

    if (flag) {
      test.push_back(iter->first);
    }
  }

  if (test.empty()) {
    return false;
  } else {
    for (int i=0; i!=available.size(); ++i) {
      available[i] += process_map.at(test.front())[1][i];
    }

    todo_list.push_back(test.front());
    process_map.erase(test.front());
    return IsSecurity(process_map, available, todo_list);
  }

  return false;
}

void Display(map< string, vector< vector<int> > > process_map, vector<int> available, list<string> todo_list){
  cout << "\tWork\tNeed\tAllocation\tWork + Allocation\tFinish" << endl;  for (list<string>::iterator iter=todo_list.begin(); iter!=todo_list.end(); ++iter) {    cout << *iter << "\t";    for (int i=0; i!=available.size(); ++i) {      cout << available[i] << " ";    }    cout << "\t";    for (int i=0; i!=available.size(); ++i) {      cout << process_map.at(*iter)[0][i] - process_map.at(*iter)[1][i] << " ";    }    cout << "\t";    for (int i=0; i!=available.size(); ++i) {      cout << process_map.at(*iter)[1][i] << " ";    }    cout << "\t\t";    for (int i=0; i!=available.size(); ++i) {      cout << available[i] + process_map.at(*iter)[1][i] << " ";      available[i] += process_map.at(*iter)[1][i];    }    cout << "\t\t\t" << "T" << endl;  }
}

int main()
{
  cout << "Input the type of resource and number of customer: " << endl;  int resource_num, customer_num;  cin >> resource_num >> customer_num;  cout << "Input the amount of resource (maximum , allocated) of each customer: " << endl;  map< string, vector< vector<int> > > process_map;  for (int i=0; i!=customer_num; ++i) {    string name;    vector< vector<int> > resource(2);    cin >> name;    for (int j=0; j!=resource_num*2; ++j) {      int data;      cin >> data;      if (j < resource_num) {        resource[0].push_back(data);      } else {        resource[1].push_back(data);      }      cin.ignore();    }    process_map.insert(pair<string, vector< vector<int> >>(name, resource));     }  cout << "Input the amount of resource(available): " << endl;  vector<int> available;  for (int i=0; i!=resource_num; ++i) {    int data;    cin >> data;    available.push_back(data);    cin.ignore();  }  while (true) {    cout << "1¡¢judge the system security\n"       << "2¡¢judge the request security\n"      << "3¡¢quit" << endl;    int choice;    cin >> choice;
    list<string> todo_list;

    switch (choice)     {    case 1: 
      if (IsSecurity(process_map, available, todo_list)) {
        Display(process_map, available, todo_list); 
        cout << "SYSTEM SECURITY!!!\n" << endl;
      } break;
    case 2:
      {
        cout << "Please input the customer¡¯s name and request: " << endl;
        string name; 
        vector<int> request;
        map< string, vector< vector<int> > > process_map2(process_map);
        cin >> name;
        bool flag = true;

        for (int i=0; i!=resource_num; ++i) {          int data;          cin >> data;          process_map2.at(name)[1][i] += data;          data = available[i] - data;          if (data < 0) {            flag = false;            break;          }          request.push_back(data);          cin.ignore();        }

        if (!flag) {
          cout << "RESOURCE INSUFFICIENT!!!\n" << endl;          cout << "CUSTOMER " << name << " CAN NOT  OBTAIN RESOURCES IMMEDIATELY." << endl;

        } else {
          if (IsSecurity(process_map2, request, todo_list)) {
            Display(process_map2, request, todo_list); 
            cout << "SYSTEM SECURITY!!!\n" << endl;
            cout << "CUSTOMER " << name << " CAN GET RESOURCES IMMEDIATELY." << endl;  

          } else {
            cout << "SYSTEM INSECURITY!!!\n" << endl;            cout << "CUSTOMER " << name << " CAN NOT  OBTAIN RESOURCES IMMEDIATELY." << endl;
          }
        }
        break;
      }
    default: return 0;
    }
  }
  return 0;
}