//By: Li Chen (li_chen12@fudan.edu.cn) on 2014
//parameter settings 
#define M 100		//total node numbers
#define T 3 		//max level to be marked and calculated in NSI, see section 2.2 in paper
#define RANDC 0		//for test sample only
#define TIMES 100	//repeat time in each situation to avoid fluctuation
float v[M]={0};

//a set of random numbers for test only
//int IFRAN[M]={36,39,98,4,19,51,89,36,7,44,27,96,75,81,95,83,85,80,86,27,7,17,1,94,66,35,71,39,7,10,84,8,97,61,88,25,88,1,4,22,34,83,78,38,68,4,72,6,17,30,19,59,82,24,26,59,60,9,86,37,49,68,0,71,26,61,21,99,50,65,5,18,50,47,56,32,17,10,68,95,96,65,82,18,98,79,46,29,21,34,30,64,51,29,12,6,85,64,19,63};

float e[T][T]={			//used when T=3 levels
				0,1,0,
				1,0.6,0.5,
				0,0.5,0.3
};
/*
float e[T][T]={			//used when T=4 levels
				0,1,0,0,
				1,0.6,0.5,0,
				0,0.5,0.3,0.2,
				0,0,0.2,0.1
};
*/