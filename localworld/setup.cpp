#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <algorithm>
//#include "setting.h"

#define M 4
#define XM 2
#define M0 5
#define MAX 100

using namespace std;

vector<int> degree,currentlocalvec;
vector<vector<int>> con;
vector<int> conunit;

bool invec(int index,vector<int> targetvec){
	for(int i=0;i<targetvec.size();i++)
		if(targetvec[i]==index)
			return 1;
	return 0;
}
void calnodedistr(double nodedistri[M]){
	int sumall=0;
	for(int i =0;i<M;i++){
		sumall+=degree[i];
	}
	int sumtoi=0;
	for(int i=0;i<M;i++){
		sumtoi+=degree[i];
		nodedistri[i]=double(sumtoi)/sumall;
	}
}

//find random number falls to which node
int finddesti(double nodedistri[M],double randpos){
	int desti = 0;
	for(desti =0;desti<M;desti++){
		if(randpos<nodedistri[desti])
			break;
	}
	return desti;
}
void addtocon(int i,int j){
	conunit.clear();
	conunit.push_back(i);
	conunit.push_back(j);
	con.push_back(conunit);
}
void main(){
	//init
	addtocon(0,1);
	addtocon(1,2);
	addtocon(2,3);
	addtocon(3,4);
	addtocon(4,5);
	for(int i =0; i<5;i++){
		degree.push_back(2);
	}
	
	for(int t=M0;t<MAX;t++){
		int reptms=0;
		//find local
		currentlocalvec.clear();
		for(int j=0;j<M;j++){
			srand(time(0)*(t+1)*(j+1)*reptms);
			int randnum=int(rand()/double(RAND_MAX)*degree.size());//0~m0+t
			if(!invec(randnum,currentlocalvec)){
				currentlocalvec.push_back(randnum);
			}
			else{
				j--;
				reptms++;
			}
		}
		//find degree
		double nodedistri[M];
		vector<int> linkednodes;
		linkednodes.clear();
		calnodedistr(nodedistri);
		for(int i=0;i<XM;i++){
			reptms=0;
			while(1){
				reptms++;
				srand(time(0)*(t+1)*(i+1)*reptms);
				double randpos=rand()/double(RAND_MAX);
				int linkpos=finddesti(nodedistri,randpos);
				if(!invec(currentlocalvec[linkpos],linkednodes)){
					degree[currentlocalvec[linkpos]]++;
					linkednodes.push_back(currentlocalvec[linkpos]);
					addtocon(t,currentlocalvec[linkpos]);
					//cout<<"con:"<<t<<"-"<<currentlocalvec[linkpos]<<endl;
					break;
				}
			}
		}
		degree.push_back(XM);
	}

	//output
	ofstream fo("lw.csv");
	for(int i=0;i<con.size();i++){
		fo<<con[i][0]<<","<<con[i][1]<<endl;
	}
}