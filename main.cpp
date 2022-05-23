#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <tuple>
#include <bits/stdc++.h>
#include <algorithm>


using namespace std;

struct point{
  int x;
  int y;
};

struct thread_data {
   int  thread_id;
   int gid, si , sj , tg, ng;
   vector<vector<point>> rectangles;
   vector<int>  intersect_privates;
};

//
void input_test(struct thread_data data[], int grid_i,int grid_j,  vector<vector<int>> grid,int privates_count ){
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

bool contains(const point& pt, vector<point> vect )
{
   auto iter = std::find_if(vect.begin(), vect.end(),[&](const point& ts)
   {return (ts.x == pt.x && ts.y == pt.y);}
 );
   return iter != vect.end();
}

void set_intersections(thread_data data[], int &privates_count){
  for (size_t i = 0; i < privates_count; i++) {
      for (size_t j = 1; j < privates_count; j++) {
        if(i>=j)
        continue;

        for (size_t k = 0;  k < data[i].rectangles.size(); k++) {
          for (size_t m = 0; m < data[i].rectangles[k].size(); m++) {
            point key;
            key.x = data[i].rectangles[k][m].x;
            key.y = data[i].rectangles[k][m].y;

            for (size_t n = 0; n < data[j].rectangles.size(); n++) {

              if(contains(key,data[j].rectangles[n])){
                cout << "Element found"<<endl;
                cout <<key.x<<" "<<key.y<<endl;
              }

            }

          }

        }

      }
  }
}


int main() {

  int grid_i;
  int grid_j;
  vector<vector<int>> grid;
  int privates_count;
  int tmp;


  cin >> grid_i;
  cin >> grid_j;

  for (int i = 0; i < grid_i; i++) {
    vector<int> v1;
    for (int j = 0; j < grid_j; j++) {
        cin >> tmp;
        v1.push_back(tmp);
    }
    grid.push_back(v1);
  }
  cin>>privates_count;
  struct thread_data data[privates_count];
    int mm =1;
  for (size_t i = 0; i < privates_count; i++) {
      cin >> data[i].gid >>data[i].si>>data[i].sj>>data[i].tg>>data[i].ng;

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
      }

}

  input_test(data,grid_i,grid_j,grid,privates_count);
  //set_intersections(data,privates_count);

  return 0;
}
