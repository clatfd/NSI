//By: Li Chen (li_chen12@fudan.edu.cn) on 2014
//obsolete
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream> 
#include "setting.h"

using namespace std;

//#define DEBUG 1

int store[TIMES][M][2]={};
float p0[M][M]={0};
vector<int> G[T];	//G[0] is  level 1 neighbor


vector<int> IM;	//immunized nodes
vector<int> IF;	//infected nodes
vector<int> IFt;	//to be infected nodes
ofstream lgot("log.txt");	//file to store Infect/Immune nodes
ofstream fo ("indepthrandom.csv");	//file to store node num data
ofstream fo ("nodenum.csv");	//file to store node num data
//ofstream ra ("ra.txt");	//file to store randomnum

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
float calNSI(int ranchoose,float p[M][M] ){					//classify levels
	for(int i=0;i<T;i++)
		G[i].clear();
	G[0].push_back(ranchoose);
	for(int j =1; j<T;j++){		//level j+1
		for(int l=0;l<G[j-1].size();l++){
			int k=G[j-1][l];
			for(int i =0; i<M;i++){
				if(p[k][i]!=0){
					if(!existbefore(i,j,G))
						G[j].push_back(i);
				}
			}
		}
	}

	//add level connections
	float L[T][T]={0};

	L[0][0]=0;
	for(int j =0; j<G[1].size();j++){		//in G[1] index
		L[0][1]+=p[ranchoose][G[1][j]]*v[G[1][j]];
	}

	for(int j =1; j<T-1;j++){		//start level j+1
		for(int k =0; k<G[j].size();k++){		//in start level index 
			for(int l =0; l<G[j-1].size();l++){		//in desti level index
				L[j][j-1]+=p[G[j][k]][G[j-1][l]]*v[G[j-1][l]];
			}
			for(int l =0; l<G[j].size();l++){		//in desti level index
				L[j][j]+=p[G[j][k]][G[j][l]]*v[G[j][l]];
			}
			for(int l =0; l<G[j+1].size();l++){		//in desti level index
				L[j][j+1]+=p[G[j][k]][G[j+1][l]]*v[G[j+1][l]];
			}
		}
	}

	for(int k =0; k<G[T-1].size();k++){		//in start level index 
		for(int l =0; l<G[T-2].size();l++){		//in desti level index
			L[T-1][T-2]+=p[G[T-1][k]][G[T-2][l]]*v[G[T-2][l]];;
		}
		for(int l =0; l<G[T-1].size();l++){		//in desti level index
			L[T-1][T-1]+=p[G[T-1][k]][G[T-1][l]]*v[G[T-1][l]];
		}
	}

	//arrange in N
	float N[T][T]={0};
	N[0][0]=L[0][0]*e[0][0];
	N[0][1]=L[0][1]*e[0][1];
	for(int j =1; j<T-1;j++){
		N[j][j-1]=L[j][j-1]*e[j][j-1];
		N[j][j]=L[j][j]*e[j][j];
		N[j][j+1]=L[j][j+1]*e[j][j+1];
	}
	N[T-1][T-2]=L[T-1][T-2]*e[T-1][T-2];
	N[T-1][T-1]=L[T-1][T-1]*e[T-1][T-1];

	float NSI=0;
	NSI+=N[0][0]+N[0][1]+N[T-1][T-2]+N[T-1][T-1];
	for(int j =1; j<T-1;j++){
		NSI+=N[j][j-1]+N[j][j]+N[j][j+1];
	}
	return NSI;
}
int randnode(){
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
	srand(time(0));
	for(int i=0;i<M;i++)
		v[i]=1;
	initnetwork(p0[0],M);
	for(int tms=0;tms<TIMES;tms++){
		IF.clear();
		IM.clear();
		float p[M][M];
		memcpy(p, p0, sizeof(p0));  
		cout<<"Times:"<<tms<<endl;
		bool immucontrol=1;
		bool neighborimmune=1;
		int ranchoose;
		int fromneighborimmuned;	//num of nodes immunized by neighbor
		for(int j=0;j<M;j++){
			ranchoose=randnode();	
			if(hasunimmneigh(ranchoose,p))
				break;
		}
	//		ranchoose = RANDC; //for test sample
		int infectchoose;
	
		for(int imtime=0;imtime<M;immucontrol){	
			IFt.clear();
			#ifdef DEBUG 
			cout<<"Infect/Immune time "<<imtime+1<<":"<<endl;
			#endif
			for(int i=0;i<IF.size();i++){		//spread virus
				for(int j=0;j<M;j++){
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
				#ifdef DEBUG 
				cout<<"virus spread to node No."<<IFt[i]+1<<endl;
				#endif
			}

			infectchoose=randnode(imtime*2+21);			//new infect
			//infectchoose=IFRAN[imtime];
			if(!inIMvec(infectchoose)){
				if(!inIFvec(infectchoose)){
					IF.push_back(infectchoose);
					#ifdef DEBUG 
					cout<<"new infection: node No."<<infectchoose+1<<endl;
					#endif
					lgot<<"F:"<<infectchoose+1<<endl;
				}
				else{
					#ifdef DEBUG 
					cout<<"Node No."<<infectchoose+1<<" already infected"<<endl;
					#endif
				}
			}
			else{
				#ifdef DEBUG 
				cout<<"virus spread to node No."<<infectchoose+1<<" but it has been immunized"<<endl;
				#endif
			}
			if(neighborimmune){
				vector<int> neighbor;
				neighbor.clear();
				vector<float> neighborNSI;
				neighborNSI.clear();
				int immuneindex=-1;
				for(int i =0; i<M;i++){			//find neigbor nodes and calculate NSI
					if(p[ranchoose][i]!=0){
						neighbor.push_back(i);
						float currentNSI=calNSI(i,p);
						neighborNSI.push_back(currentNSI);
						if(immuneindex==-1||currentNSI>neighborNSI[immuneindex])
							immuneindex=neighbor.size()-1;
					}
				}
				#ifdef DEBUG 
				cout<<"Select node No."<<ranchoose+1<<endl;
				cout<<"Node No."<<ranchoose+1<<" has "<<neighbor.size()<<" neighbor nodes"<<endl;
				for(int i =0; i<neighbor.size();i++){			
					cout<<"NSI of neighbor node No."<<(neighbor[i]+1)<<" is "<<neighborNSI[i]<<endl;
				}
				
				cout<<"Best solution is to immunize node No."<<neighbor[immuneindex]+1<<" which has an NSI of "<<neighborNSI[immuneindex]<<endl;
				#endif
				ifectvecremove(neighbor[immuneindex]);	//remove infected node from IF
				IM.push_back(neighbor[immuneindex]);
				lgot<<"M:"<<neighbor[immuneindex]+1<<endl;

				for(int i=0;i<M;i++){		//delete connections to immunized node
					p[i][neighbor[immuneindex]]=0;
					p[neighbor[immuneindex]][i]=0;
				}
				if(!hasunimmneigh(neighbor[immuneindex],p)){
					#ifdef DEBUG 
					cout<<"random choose another node"<<endl;
					#endif
					for(int j=0;j<M;j++){
						ranchoose=randnode(j*M+tms*j);
						if(hasunimmneigh(ranchoose,p))
							break;
					}
					if(!hasunimmneigh(ranchoose,p)){	//if random choose can not find the rest,start from 0 to M
						for(int j=0;j<M;j++){
							if(hasunimmneigh(j,p)){
								ranchoose=j;
								break;
							}
						}
					}
					if(!hasunimmneigh(ranchoose,p)){
						#ifdef DEBUG 
						cout<<"all neighbor nodes immuned"<<endl;
						#endif
						neighborimmune=0;
						fromneighborimmuned=IM.size();
					}

				}
				else{
					int ranzo =rand() / double(RAND_MAX)*neighbor.size();		
					ranchoose=neighbor[ranzo];
				}

			}
			else{
				for(int j=0;j<M;j++){
					if(!inIMvec(j)){
						IM.push_back(j);
						ifectvecremove(j);	//remove infected node from IF
						#ifdef DEBUG 
						cout<<"Direct immunize node No."<<j+1<<endl;
						#endif
						lgot<<"M:"<<j+1<<endl;
						break;
					}
				}
			}
			#ifdef DEBUG 
			cout<<"Infected:"<<IF.size()<<"  Immunized:"<<IM.size()<<endl;
			#endif
			store[tms][imtime][0]=IF.size();
			store[tms][imtime][1]=IM.size();

			#ifdef DEBUG 
			//cout<<"Still immunize? 1 or 0 :";
			#endif
			//cin>>immucontrol;
			#ifdef DEBUG 
			cout<<endl;
			#endif
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
		fo<<","<<float(suminfectthisday/TIMES);
		fo<<endl;
	}
}