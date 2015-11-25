#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include "setting.h"

using namespace std;

int store[TIMES][M][2]={};
float p0[M][M]={0};
vector<int> G[T];	//G[0] is  level 1 neighbor
vector<int> IM;	//immunized nodes
vector<int> IF;	//infected nodes
vector<int> IFt;	//to be infected nodes
vector<int> availim;	//available node to immunize

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
void availimremove(int removetarget){
	vector<int>::iterator itr = availim.begin();
	while (itr!=availim.end()){
		if (*itr==removetarget){
			  itr=availim.erase(itr);
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
	initnetwork(p0[0],M);
	for(int tms=0;tms<TIMES;tms++){
		IF.clear();
		IM.clear();
		availim.clear();
		float p[M][M];
		memcpy(p, p0, sizeof(p0));  
		cout<<"Times:"<<tms<<endl;
		for(int j=0;j<M;j++)
			availim.push_back(j);
		bool immucontrol=1;
		bool neighborimmune=1;
		int ranchoose;
		for(int j=0;j<M;j++){
			ranchoose=randnode(j*M*tms);	//2+j is changeable to specify difference
			if(hasunimmneigh(ranchoose,p))
				break;
		}
	//		ranchoose = RANDC; //for test sample
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
			
			srand(time(0)*(imtime+1)*tms);
			if(imtime<1)
				 ranchoose=rand()/double(RAND_MAX)*M;
			else{
				ranchoose=rand()/double(RAND_MAX)*availim.size();
				ranchoose=availim[ranchoose];
			}
			availimremove(ranchoose);	//remove from available im list
			ifectvecremove(ranchoose);	//remove from infected list
			IM.push_back(ranchoose);	//add to im list
			for(int i=0;i<M;i++)		//delete connections to immunized node
				p[i][ranchoose]=0;
			cout<<"Direct immunize node No."<<ranchoose+1<<endl;
			lgot<<"M:"<<ranchoose+1<<endl;

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
		for(int tms=0;tms<TIMES;tms++){
			fo<<","<<store[tms][imtime][0];
		}
		fo<<endl;
	}
}