#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <tuple>
#include <bits/stdc++.h>
#include <algorithm>
#include "hw2_output.h"
#include "hw2_output.c"


using namespace std;



struct point{
  int x;
  int y;
};

struct private_data {
   int  thread_id;
   int gid, si , sj , tg, ng;
   vector<vector<point>> rectangles;
   vector<int> intersect_privates;
};

int grid_size;
int grid_i;
int grid_j;
int privates_count;
int tmp;
vector<vector<int>> grid;
vector<vector<pthread_mutex_t>> grid_mutex;
vector<pthread_mutex_t> mutex_row;
vector<pthread_t> private_threads;
vector<private_data> pp_datas;

void* thread_test(void* arg);
//
void input_test(struct private_data data[], int grid_i,int grid_j,  vector<vector<int>> grid,int privates_count ){
  cout<<"--Input Test--"<<endl;
  cout<< grid_i<<" "<<grid_j<<endl;
  for (int i = 0; i < grid_i; i++){
    for (int j = 0; j < grid_j; j++){
        cout<<grid[i][j]<<" ";
    }
      cout << endl;
  }
  cout <<privates_count<<endl;

  for (size_t m = 0; m < privates_count; m++) {
    cout <<  data[m].gid <<" "<< data[m].si<<" "<< data[m].sj<<" "<< data[m].tg<<" "<< data[m].ng<<endl;

  	for (int i = 0; i < data[m].rectangles.size(); i++)
  	{
  		for (int j = 0; j < data[m].rectangles[i].size(); j++)
  		{
  			cout << data[m].rectangles[i][j].x<<" "<<data[m].rectangles[i][j].y<<endl;
  		}
  		cout << endl;
  	}
  }
  cout<<endl;
}

void mutex_initialization(){
  for(int i=0; i < grid_i; i++){
    for(int j=0; j < grid_j; j++){
      pthread_mutex_t mutex;
      pthread_mutex_init(&mutex, NULL);
      mutex_row.push_back(mutex);
      //cout << i << j << " mutex created" << endl;
    }
    grid_mutex.push_back(mutex_row);
  }
}

void* thread_test(void* arg){
  int id = *(int*) arg;
  cout << "id:       " << id << endl;
  hw2_notify(PROPER_PRIVATE_CREATED, id, 0, 0); //cout<< "thread execution started."<< endl; 
  for(int i=0; i<grid_i; i++){
    for(int j=0; j<grid_j; j++){
      pthread_mutex_lock(&grid_mutex[i][j]);
      //cout << "a a a" << endl;
      pthread_mutex_unlock(&grid_mutex[i][j]);
    }
  }
}

void thread_creation(){
  for(int i=0; i<privates_count; i++){
    pthread_t p;
    private_threads.push_back(p);
    if(pthread_create(&private_threads[i], NULL, &thread_test, &pp_datas[i].gid) != 0){
      perror("Failed to create thread!");
      break;
    }
    cout<< "eaeffefqafeaefaf:   "<< pp_datas[i].gid << endl;
  }
}

void thread_join(){
  for(int i=0; i<privates_count; i++){
    if(pthread_join(private_threads[i], NULL) != 0){
      break;
    }
    //cout<< "thread execution finished."<< endl; 
  }
}

void get_private_data(){
  struct private_data data[privates_count];
  int mm =1;
  for (size_t i = 0; i < privates_count; i++) {
      cin >> data[i].gid >>data[i].si>>data[i].sj>>data[i].tg>>data[i].ng;
      cout << "gid: " << data[i].gid << endl;
      
      for (size_t j = 0; j < data[i].ng; j++) {

        int x,y;
        cin >> x >> y;
        vector<point> rectangle;

        for (size_t k = 0; k < data[i].si; k++) {

          for (size_t m = 0; m < data[i].sj; m++) {

            struct point pt;
            pt.x = x+k;
            pt.y = y+m;
            rectangle.push_back(pt);
            mm++;
          }
        }
        data[i].rectangles.push_back(rectangle);
        pp_datas.push_back(data[i]);
      }

  } 
}

int main() {
  hw2_init_notifier();
  cin >> grid_i;
  cin >> grid_j;
  grid_size = grid_i*grid_j;
  

  for (int i = 0; i < grid_i; i++) {
    vector<int> v1;
    for (int j = 0; j < grid_j; j++) {
        cin >> tmp;
        //cout << "temp: " << tmp << endl;
        v1.push_back(tmp);
    }
    grid.push_back(v1);
  }

  cin>>privates_count;
  cout << "private_count: " << privates_count << endl;
  //pthread_t private_threads[privates_count];
  get_private_data();

  mutex_initialization();

  thread_creation();
  
  thread_join();

  //input_test(data,grid_i,grid_j,grid,privates_count);
  return 0;
}
