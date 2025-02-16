#include <iostream>
#include <limits.h>
#include<string>
#include<math.h>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<time.h>
#include<windows.h>
using namespace std;
const int V=248;
struct station_code
{
    string name;
    int code;
    string color;
};
struct station_code station[V];
float graph[V][V];

struct node1
    {
        vector <float>p;
    }P[V];
string makecapital(string str)
{
    for(int i=0;i<str.length();i++)
    {
        if(str[i]>96&&str[i]<123)
            str[i]=str[i]-32;
    }
    return str;
}

COORD coord;
//void clrscreen();
void gotoxy(int x,int y);
int timetaken(float dist);
int money(float dist);
void Path(float dist,int e,int st,int inter);
int minDistance(float dist[], bool sptSet[]);
void dijkstra(float graph[V][V], int src,int targ);
int printSolution(float dist[], int n,int src,int temp);
void take_input();
void secondWindow();

void gotoxy(int x,int y)
{
  coord.X=x;
  coord.Y=y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int timetaken(float dist)
{
    float speed=0.55;
    return ceil(dist/speed);
}

int money(float dist)
{
    if(dist<=2)
        return 10;
    else if(dist>2&&dist<=5)
        return 20;
    else if(dist>5&&dist<=12)
        return 30;
    else if(dist>12&&dist<=21)
        return 40;
    else if(dist>21&&dist<=32)
        return 50;
    else
        return 60;
}

void Path(float d,int e,int st,int inter)
{
    int t=e,s;
    static float dist=0;
    dist+=d;

     gotoxy(16,11);
    cout<<"THE SHORTEST PATH IS : ";

    static int pos_x=12;
    static int pos_y=15;
    vector <int> path;
    path.push_back(t);
    while(t!=st)
    {
        s=P[t].p.size();
        t=P[t].p[s-1];
        path.push_back(t);
    }
    vector <int>::iterator i=path.end();
    string str;
    string color;
    if(!inter){
    gotoxy(44,13);
    cout<<"****** LOADING ******";
    gotoxy(42,13);
    cout<<"****** ROUTE FOUND ******";
    }
    vector<int>::iterator i2=path.end();
    i2--;
    int n_of_stations=0;
    while(i!=path.begin())
    {
        i--;
        color=station[*i].color;
        

        if(i!=i2)
        {
        if(station[*(i2)].color!=station[*(i)].color)
        {
            pos_x=8;
            pos_y++;
            gotoxy(pos_x,pos_y);
            cout<<"{change from "<<station[*i2].color<<" to "<<station[*i].color<<"}";
            pos_x=12;
            pos_y++;
            gotoxy(pos_x,pos_y);
        }
        i2--;
        }
        str=station[*i].name;
        if(pos_x+5+str.size()<106)
        {
            gotoxy(pos_x,pos_y);
            cout<<" ->> "<<str;
            pos_x=pos_x+str.size()+5;
        }
        else
        {
            pos_x=12;
            pos_y++;
            gotoxy(pos_x,pos_y);
            cout<<" ->> "<<str;
            pos_x=pos_x+str.size()+5;
        }
        n_of_stations++;
        
    }
    if(!inter)
    {
      gotoxy(12,++pos_y);
      cout<<"INTERMEDIATE STATION";
      pos_y++;
      pos_x=12;
    }

    if(inter){
    gotoxy(72,11);
    cout<<"PATH LENGTH IS :";
    gotoxy(97,11);
    cout<<d<<" KM";
    gotoxy(16,10);
    cout<<"AVERAGE TIME : ";
    gotoxy(39,10);
    cout<<timetaken(d)<<" MIN";
    gotoxy(72,10);
    cout<<"AVERAGE FARE : ";
    gotoxy(94,10);
    cout<<" Rs. "<<money(d);
    gotoxy(72,12);
    cout<<"NO OF STATIONS : ";
    gotoxy(92,12);
    cout<<n_of_stations-1;
    }
    else{

      gotoxy(72,11);
      cout<<"PATH LENGTH IS :";
      gotoxy(89,11);
      cout<<d<<" KM,";

      gotoxy(16,10);
      cout<<"AVERAGE TIME : ";
      gotoxy(32,10);
      cout<<timetaken(d)<<" MIN,";

      gotoxy(72,10);
      cout<<"AVERAGE FARE : Rs. ";
      gotoxy(91,10);
      cout<<money(d)<<",";

      gotoxy(72,12);
      cout<<"NO OF STATIONS : ";
      gotoxy(89,12);
      cout<<n_of_stations-1<<",";
    }

    if(inter){
    gotoxy(44,9);
    cout<<"WANT TO SEARCH AGAIN ?  ";
    string choice;
    pos_x=12; pos_y=15;
    cin>>choice;
    choice=makecapital(choice);
    if(choice=="Y"||choice=="YES")
        secondWindow();
    gotoxy(5,30);
    char ch;
    scanf("%c",&ch);
    cout<<endl;
  }
  return;
}

int minDistance(float dist[], bool sptSet[])
{
   float min = INT_MAX;
   int min_index;

   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}

int printSolution(float dist[], int n,int src,int temp,int inter)
{
    
    Path(dist[temp],temp,src,inter);
}

void dijkstra(float graph[V][V], int src,int targ,int inter)
{
     float dist[V];
     bool sptSet[V];
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
     dist[src] = 0;
     for (int count = 0; count < V-1; count++)
     {
         int u = minDistance(dist, sptSet);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                P[v].p.push_back(u);
            }
     }
     printSolution(dist, V,src,targ, inter);
}

int lcs( string X,string Y ) 
{ 
	int m=X.length();
	int n=Y.length();
   int L[m+1][n+1]; 
   int i, j; 
   
   for (i=0; i<=m; i++) 
   { 
     for (j=0; j<=n; j++) 
     { 
       if (i == 0 || j == 0) 
         L[i][j] = 0; 
   
       else if (X[i-1] == Y[j-1]) 
         L[i][j] = L[i-1][j-1] + 1; 
   
       else
         L[i][j] = max(L[i-1][j], L[i][j-1]); 
     } 
   } 
   return L[m][n]; 
} 
int sameMatch(string s){
	int max=0,maxi=-1;
	for(int i=0;i<248;i++){
		int val=lcs(s,station[i].name);
		if(val>max){
			maxi=station[i].code;
			max=val;
		}
	}
	if(max<station[maxi].name.length()/2)
		return -1;
	return maxi;
}
void take_input()
{		
		char ch;
        string start_s,end_s,inter_s,line,col;
        gotoxy(16,3);
        cout<<"ENTER THE STARTING STATION:";
        gotoxy(20,5);
        getline(cin,start_s);
        gotoxy(72,3);
        
        cout<<"ENTER THE DESTINATION STATION:";
        gotoxy(76,5);
        getline(cin,end_s);
        gotoxy(42,6);
        cout<<"ENTER THE INTERMEDIATE STATION:";
        gotoxy(46,8);
        getline(cin,inter_s);

        start_s=makecapital(start_s);
        end_s=makecapital(end_s);
        inter_s=makecapital(inter_s);

        int startcode,endcode,intercode=-1;
        int startflag=0,endflag=0,interflag1=0,interflag2=0;
        if(!(inter_s=="NO"||inter_s=="N"))
          interflag1=1;
        startcode=sameMatch(start_s);
        endcode=sameMatch(end_s);
        intercode=sameMatch(inter_s);
        if(startcode==-1)
        	startflag=1;
        if(endcode==-1)
        	endflag=1;
        
        if(endcode==-1)
        	interflag2=1;
        
        int fault=0;
        if(startflag==1)
        {
            gotoxy(42,10);
            cout<<"WRONG STARTING STATION NAME ENTERED";
            fault=1;
        }
        if(endflag==1)
        {
            gotoxy(40,11);
            cout<<"WRONG DESTINATION STATION NAME ENTERED";
            fault=1;
        }
        if(interflag1&&interflag2==1)
        {
            gotoxy(39,12);
            cout<<"WRONG INTERMEDIATE STATION NAME ENTERED";
            fault=1;
        }
        scanf("%c",&ch);    
        if(fault)
        {
          secondWindow();
          return;
        }
        if(interflag1){
          dijkstra(graph,startcode,intercode,0);
          dijkstra(graph,intercode,endcode,1);
          }
        else
          dijkstra(graph, startcode,endcode,1);
}
void secondWindow()
{
    gotoxy(48,19);
    system("color 00");
    take_input();
}
int main()
{
    int temp,n1,n2;
    float dis;
    ifstream fin;
    fin.open("node_values_new.txt");

    for(int i=0;i<248;i++)
    {
       for(int j=0;j<248;j++)
        graph[i][j]=0;
    }
    for(int i=1;i<=V;i++)
    {
        fin>>temp;
        fin>>n1;
        
        for( int j=0;j<temp;j++)
        {
           fin>>n2;
           fin>>dis;
           graph[n1-1][n2-1]=dis;
        }
    }
        string line,col;
        ifstream code;
        ifstream color;
        code.open("stationcodes.txt");
        color.open("stationcolorcodes.txt");
        for(int i=0;i<V;i++)
        {
            getline(code, line);
            station[i].name=line;
            station[i].code=i;
            getline(color,col);
            station[i].color=col;
        }  
    secondWindow();  
}