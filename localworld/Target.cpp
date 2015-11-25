#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <algorithm>
#include "setting.h"

using namespace std;

int store[TIMES][M][2]={};
float p0[M][M]={0};
vector<int> G[T];	//G[0] is  level 1 neighbor

vector<int> IM;	//immunized nodes
vector<int> IF;	//infected nodes
vector<int> IFt;	//to be infected nodes
vector<int>neighnum;	//every node's neighbor num

ofstream fo ("nodenum.csv");	//file to store node num data
//ofstream ra ("ra.txt");	//file to store randomnum
ofstream lgot("log.txt");	//file to store Infect/Immune nodes

extern void initnetwork(float * p0,int m);

bool existinvector(int i, vector<int> G){
	for(int k=0;k<G.size();k++)
		if(G[k]==i)
			return 1;
	return 0;
}
bool existbefore(int i,int j,vector<int> G[T]){
	for(int k=0;k<=j;k++){
		if(existinvector(i,G[k]))
			return 1;
	}
	return 0;
}
int randnode(int modif){
	srand(time(NULL)*modif);	//generate random seed according to time now
	double ranzo =rand() / double(RAND_MAX);		//0-1
	//ra<<ranzo*M<<endl;	//check random number
	return int(ranzo*M);	//choose a node result is array index not num id
}
bool hasunimmneigh(int index,float p[M][M]){
	for(int i=0;i<M;i++)
		if(p[index][i]!=0)
			return 1;
	return 0;
}

void ifectvecremove(int removetarget){
	vector<int>::iterator itr = IF.begin();
	while (itr!=IF.end()){
		if (*itr==removetarget){
			  itr=IF.erase(itr);
		 }
		else{
			itr++;
		}
	}
}
bool inIMvec(int index){
	for(int i=0;i<IM.size();i++)
		if(IM[i]==index)
			return 1;
	return 0;
}
bool inIFvec(int index){
	for(int i=0;i<IF.size();i++)
		if(IF[i]==index)
			return 1;
	return 0;
}
bool inIFtvec(int index){
	for(int i=0;i<IFt.size();i++)
		if(IFt[i]==index)
			return 1;
	return 0;
}

void main(){
	for(int i=0;i<M;i++)
		v[i]=1;
	initnetwork(p0[0],M);
	for(int tms=0;tms<TIMES;tms++){
		IF.clear();
		IM.clear();
		neighnum.clear();
		float p[M][M];
		memcpy(p, p0, sizeof(p0));  
		cout<<"Times:"<<tms<<endl;
		bool immucontrol=1;
		bool neighborimmune=1;
		int hdchoose;
		
		for(int i=0;i<M;i++){
			int ineighbor=0;
			for(int j=0;j<M;j++){
				if(p[i][j])
					ineighbor++;
			}
			neighnum.push_back(ineighbor);
		}
		
		
		int infectchoose;
		
		for(int imtime=0;imtime<M;immucontrol){	
			IFt.clear();
			cout<<"Infect/Immune time "<<imtime+1<<":"<<endl;

			for(int i=0;i<IF.size();i++){		//spread virus
				for(int j=0;j<M;j++){
					srand(time(0)*(j+1)*(tms+1));
					if(rand()/double(RAND_MAX)<p[IF[i]][j]){
						if(!inIFvec(j)&&!inIFtvec(j)&&!inIMvec(j)){
							IFt.push_back(j);
							lgot<<"F:"<<IF[i]+1<<"->"<<j+1<<endl;
						}
					}
				}
			}
			for(int i=0;i<IFt.size();i++){		//spread virus
				IF.push_back(IFt[i]);
				cout<<"virus spread to node No."<<IFt[i]+1<<endl;
			}

			//infectchoose=randnode(imtime*2+21);			//new infect
			infectchoose=IFRAN[imtime];
			if(!inIMvec(infectchoose)){
				if(!inIFvec(infectchoose)){
					IF.push_back(infectchoose);
					cout<<"new infection: node No."<<infectchoose+1<<endl;
					lgot<<"F:"<<infectchoose+1<<endl;
				}
				else{
					cout<<"Node No."<<infectchoose+1<<" already infected"<<endl;
				}
			}
			else{
				cout<<"virus spread to node No."<<infectchoose+1<<" but it has been immunized"<<endl;
			}
			
			hdchoose = max_element (neighnum.begin(), neighnum.end())-neighnum.begin();
			neighnum[hdchoose]=-1;
			ifectvecremove(hdchoose);	//remove from infected list
			IM.push_back(hdchoose);	//add to im list
			
			for(int i=0;i<M;i++){		//delete connections to immunized node
				p[i][hdchoose]=0;
				p[hdchoose][i]=0;
			}
			cout<<"Direct immunize node No."<<hdchoose+1<<endl;
			lgot<<"M:"<<hdchoose+1<<endl;

			cout<<"Infected:"<<IF.size()<<"  Immunized:"<<IM.size()<<endl;
			store[tms][imtime][0]=IF.size();
			store[tms][imtime][1]=IM.size();
			//cout<<"Still immunize? 1 or 0 :";
			//cin>>immucontrol;
			cout<<endl;
			imtime++;
		}
	}
	for(int imtime=0;imtime<M;imtime++){
		fo<<imtime;
		float suminfectthisday=0;
		for(int tms=0;tms<TIMES;tms++){
			fo<<","<<store[tms][imtime][0];
			suminfectthisday+=store[tms][imtime][0];
		}
		fo<<","<<suminfectthisday/TIMES;
		fo<<endl;
	}
}