#include <iostream>
#include <list>
#include <string>

using namespace std;

class Process {
 public: 
  Process():service_time(0), elapsed_time(0), remaining_time(0), count(0), round(2), state('W')
  {

  }

  void AfterRun() {
    state = 'W';
    if (elapsed_time + round > service_time) {
      elapsed_time = service_time;
      remaining_time = 0;
      priority = 0;
    } else {
      elapsed_time += round;
      remaining_time -= round;
      priority -= round;
    }

    count++;
  }

  void BeforeRun() {
    state = 'R';
  }

  void Wait() {
    priority += round;
  }

  bool IsFinish() {
    if (service_time == elapsed_time) {
      state = 'F';
      priority = 0;
      return true;
    } else {
      return false;
    }
  }

  int service_time;
  int elapsed_time;
  string name;
  int remaining_time;
  int count; 
  int round;
  char state;
  int priority;
};


void Display(list<Process> ready, list<Process> finish) {   
  cout << "Name\t" << "Elapsed_Time\t" << "Remaining_Time\t" << "Count\t" << "Round\t" << "Priority\t" << "State" << endl;
  
  for (list<Process>::iterator iter=ready.begin(); iter!=ready.end(); ++iter) {
    cout << (*iter).name << "\t" 
         << (*iter).elapsed_time << "\t\t"
         << (*iter).remaining_time << "\t\t"
         << (*iter).count << "\t" 
         << (*iter).round << "\t"
         << (*iter).priority << "\t\t"
         << (*iter).state <<  endl;
  }

  for (list<Process>::iterator iter=finish.begin(); iter!=finish.end(); ++iter) {
    cout << (*iter).name << "\t" 
         << (*iter).elapsed_time << "\t\t"
         << (*iter).remaining_time << "\t\t"
         << (*iter).count << "\t" 
         << (*iter).round << "\t"
         << (*iter).priority << "\t\t"
         << (*iter).state << endl;
  }

  cout << "\nReady query£º ";
  for (list<Process>::iterator iter=ready.begin(); iter!=ready.end(); ++iter) {
    cout << (*iter).name << "  ";
  }
  cout << "\nFinish query£º ";
  for (list<Process>::iterator iter=finish.begin(); iter!=finish.end(); ++iter) {
    cout << (*iter).name << "  ";
  }
  cout << endl << endl;
}

void PCB_TimeSlice(list<Process> ready, list<Process> finish) {
  while (ready.size() != 0) {
    ready.front().BeforeRun();
    Display(ready, finish);
    ready.front().AfterRun();
    if (ready.front().IsFinish()) {
      finish.push_back(ready.front());
    } else {
      ready.push_back(ready.front());
    }
    ready.pop_front();
  }
  
  Display(ready, finish);
}

bool Compare (Process first, Process second)
{
  return first.priority > second.priority ? true : false;
}

void PCB_Priority(list<Process> ready, list<Process> finish) {  
  while (ready.size() != 0) {
    ready.sort(Compare);
    ready.front().BeforeRun();
    Display(ready, finish);
    ready.front().AfterRun();

    if (ready.front().IsFinish()) {
      finish.push_back(ready.front());
      for (list<Process>::iterator iter=ready.begin(); iter!=ready.end(); ++iter) {
        iter->Wait();
      }
    } else {
      ready.push_back(ready.front());
      for (list<Process>::iterator iter=ready.begin(); iter!=ready.end(); ++iter) {
        iter->Wait();
      }
      ready.back().priority -= ready.back().round;
    }
    ready.pop_front();    
  }
  
  Display(ready, finish);
}




int main()
{
  int num;
  list<Process> ready;
  list<Process> finish;

  cout << "Input the number of processes : ";
  cin >> num;

  cout << "input name and service time :" << endl;

  for (int i=0; i!=num; ++i) {
    Process index;
    cin >> index.name >> index.service_time;
    index.remaining_time = index.service_time;
    index.priority = 50 - index.service_time;
    ready.push_back(index);
  }

  cout << "Choose the PCB type : " << endl;
  cout << "1: TimeSlice" << endl;
  cout << "2: Priority" << endl;
  
  int index;
  cin >> index;
  switch (index) {
    case 1:PCB_TimeSlice(ready, finish);break;
    case 2:PCB_Priority(ready, finish);break;
    default:break;
  }
  
  return 0;
}