//By: Li Chen (li_chen12@fudan.edu.cn) on 2014
//function to create network in matrix
void initnetwork(float * p0,int M){	
	float threshold=0.5;	//pij which means node i has a percentage of pij spreading virus to node j, see in paper section 2.2
	
	//paste codes from here
p0[1*M+2]=threshold;
p0[1*M+3]=threshold;
p0[1*M+4]=threshold;
p0[1*M+5]=threshold;
p0[1*M+7]=threshold;
p0[1*M+9]=threshold;
p0[1*M+12]=threshold;
p0[1*M+20]=threshold;
p0[1*M+31]=threshold;
p0[1*M+36]=threshold;
p0[1*M+58]=threshold;
p0[1*M+73]=threshold;
p0[2*M+1]=threshold;
p0[2*M+3]=threshold;
p0[2*M+4]=threshold;
p0[2*M+5]=threshold;
p0[2*M+7]=threshold;
p0[2*M+8]=threshold;
p0[2*M+9]=threshold;
p0[2*M+11]=threshold;
p0[2*M+12]=threshold;
p0[2*M+13]=threshold;
p0[2*M+24]=threshold;
p0[2*M+35]=threshold;
p0[2*M+36]=threshold;
p0[2*M+40]=threshold;
p0[2*M+44]=threshold;
p0[2*M+86]=threshold;
p0[2*M+95]=threshold;
p0[3*M+1]=threshold;
p0[3*M+2]=threshold;
p0[3*M+4]=threshold;
p0[3*M+5]=threshold;
p0[3*M+7]=threshold;
p0[3*M+11]=threshold;
p0[3*M+13]=threshold;
p0[3*M+23]=threshold;
p0[3*M+24]=threshold;
p0[4*M+1]=threshold;
p0[4*M+2]=threshold;
p0[4*M+3]=threshold;
p0[4*M+5]=threshold;
p0[4*M+6]=threshold;
p0[4*M+9]=threshold;
p0[4*M+10]=threshold;
p0[4*M+11]=threshold;
p0[4*M+12]=threshold;
p0[4*M+27]=threshold;
p0[4*M+28]=threshold;
p0[4*M+48]=threshold;
p0[5*M+1]=threshold;
p0[5*M+2]=threshold;
p0[5*M+4]=threshold;
p0[5*M+6]=threshold;
p0[5*M+7]=threshold;
p0[5*M+8]=threshold;
p0[5*M+11]=threshold;
p0[5*M+15]=threshold;
p0[5*M+19]=threshold;
p0[5*M+23]=threshold;
p0[5*M+29]=threshold;
p0[5*M+33]=threshold;
p0[6*M+1]=threshold;
p0[6*M+2]=threshold;
p0[6*M+4]=threshold;
p0[6*M+9]=threshold;
p0[6*M+42]=threshold;
p0[6*M+69]=threshold;
p0[7*M+1]=threshold;
p0[7*M+2]=threshold;
p0[7*M+12]=threshold;
p0[7*M+16]=threshold;
p0[7*M+19]=threshold;
p0[7*M+23]=threshold;
p0[7*M+92]=threshold;
p0[7*M+96]=threshold;
p0[8*M+5]=threshold;
p0[8*M+43]=threshold;
p0[9*M+1]=threshold;
p0[9*M+3]=threshold;
p0[9*M+4]=threshold;
p0[9*M+5]=threshold;
p0[9*M+6]=threshold;
p0[9*M+11]=threshold;
p0[9*M+31]=threshold;
p0[9*M+46]=threshold;
p0[9*M+48]=threshold;
p0[9*M+49]=threshold;
p0[9*M+57]=threshold;
p0[9*M+58]=threshold;
p0[9*M+82]=threshold;
p0[10*M+4]=threshold;
p0[11*M+1]=threshold;
p0[11*M+2]=threshold;
p0[11*M+4]=threshold;
p0[11*M+5]=threshold;
p0[11*M+7]=threshold;
p0[11*M+8]=threshold;
p0[11*M+9]=threshold;
p0[11*M+31]=threshold;
p0[11*M+37]=threshold;
p0[11*M+46]=threshold;
p0[11*M+63]=threshold;
p0[12*M+5]=threshold;
p0[12*M+6]=threshold;
p0[13*M+11]=threshold;
p0[14*M+11]=threshold;
p0[14*M+74]=threshold;
p0[15*M+7]=threshold;
p0[16*M+2]=threshold;
p0[16*M+9]=threshold;
p0[16*M+64]=threshold;
p0[17*M+11]=threshold;
p0[18*M+4]=threshold;
p0[19*M+9]=threshold;
p0[20*M+1]=threshold;
p0[21*M+14]=threshold;
p0[22*M+19]=threshold;
p0[23*M+1]=threshold;
p0[23*M+6]=threshold;
p0[23*M+27]=threshold;
p0[24*M+2]=threshold;
p0[24*M+3]=threshold;
p0[25*M+2]=threshold;
p0[26*M+17]=threshold;
p0[26*M+20]=threshold;
p0[27*M+4]=threshold;
p0[27*M+9]=threshold;
p0[27*M+11]=threshold;
p0[28*M+2]=threshold;
p0[29*M+26]=threshold;
p0[30*M+5]=threshold;
p0[30*M+7]=threshold;
p0[31*M+2]=threshold;
p0[31*M+4]=threshold;
p0[31*M+14]=threshold;
p0[31*M+68]=threshold;
p0[32*M+11]=threshold;
p0[33*M+4]=threshold;
p0[34*M+1]=threshold;
p0[35*M+5]=threshold;
p0[36*M+2]=threshold;
p0[36*M+16]=threshold;
p0[36*M+58]=threshold;
p0[37*M+26]=threshold;
p0[37*M+32]=threshold;
p0[38*M+4]=threshold;
p0[39*M+11]=threshold;
p0[40*M+23]=threshold;
p0[41*M+36]=threshold;
p0[42*M+9]=threshold;
p0[43*M+5]=threshold;
p0[44*M+4]=threshold;
p0[45*M+2]=threshold;
p0[46*M+6]=threshold;
p0[47*M+12]=threshold;
p0[48*M+31]=threshold;
p0[48*M+39]=threshold;
p0[49*M+9]=threshold;
p0[50*M+1]=threshold;
p0[51*M+5]=threshold;
p0[52*M+2]=threshold;
p0[53*M+9]=threshold;
p0[54*M+31]=threshold;
p0[55*M+2]=threshold;
p0[56*M+37]=threshold;
p0[57*M+43]=threshold;
p0[58*M+3]=threshold;
p0[59*M+30]=threshold;
p0[60*M+1]=threshold;
p0[61*M+33]=threshold;
p0[62*M+5]=threshold;
p0[63*M+2]=threshold;
p0[64*M+31]=threshold;
p0[65*M+6]=threshold;
p0[66*M+1]=threshold;
p0[67*M+6]=threshold;
p0[68*M+51]=threshold;
p0[69*M+36]=threshold;
p0[69*M+56]=threshold;
p0[70*M+39]=threshold;
p0[71*M+21]=threshold;
p0[72*M+60]=threshold;
p0[73*M+27]=threshold;
p0[74*M+72]=threshold;
p0[75*M+56]=threshold;
p0[76*M+28]=threshold;
p0[77*M+66]=threshold;
p0[78*M+6]=threshold;
p0[79*M+5]=threshold;
p0[80*M+46]=threshold;
p0[81*M+18]=threshold;
p0[82*M+2]=threshold;
p0[83*M+4]=threshold;
p0[84*M+53]=threshold;
p0[85*M+67]=threshold;
p0[86*M+74]=threshold;
p0[87*M+2]=threshold;
p0[88*M+26]=threshold;
p0[89*M+79]=threshold;
p0[90*M+41]=threshold;
p0[91*M+80]=threshold;
p0[92*M+17]=threshold;
p0[93*M+70]=threshold;
p0[94*M+11]=threshold;
p0[95*M+34]=threshold;
p0[96*M+2]=threshold;
p0[97*M+6]=threshold;
p0[98*M+11]=threshold;
p0[99*M+27]=threshold;
p0[100*M+4]=threshold;
p0[2*M+1]=threshold;
p0[3*M+1]=threshold;
p0[4*M+1]=threshold;
p0[5*M+1]=threshold;
p0[7*M+1]=threshold;
p0[9*M+1]=threshold;
p0[12*M+1]=threshold;
p0[20*M+1]=threshold;
p0[31*M+1]=threshold;
p0[36*M+1]=threshold;
p0[58*M+1]=threshold;
p0[73*M+1]=threshold;
p0[1*M+2]=threshold;
p0[3*M+2]=threshold;
p0[4*M+2]=threshold;
p0[5*M+2]=threshold;
p0[7*M+2]=threshold;
p0[8*M+2]=threshold;
p0[9*M+2]=threshold;
p0[11*M+2]=threshold;
p0[12*M+2]=threshold;
p0[13*M+2]=threshold;
p0[24*M+2]=threshold;
p0[35*M+2]=threshold;
p0[36*M+2]=threshold;
p0[40*M+2]=threshold;
p0[44*M+2]=threshold;
p0[86*M+2]=threshold;
p0[95*M+2]=threshold;
p0[1*M+3]=threshold;
p0[2*M+3]=threshold;
p0[4*M+3]=threshold;
p0[5*M+3]=threshold;
p0[7*M+3]=threshold;
p0[11*M+3]=threshold;
p0[13*M+3]=threshold;
p0[23*M+3]=threshold;
p0[24*M+3]=threshold;
p0[1*M+4]=threshold;
p0[2*M+4]=threshold;
p0[3*M+4]=threshold;
p0[5*M+4]=threshold;
p0[6*M+4]=threshold;
p0[9*M+4]=threshold;
p0[10*M+4]=threshold;
p0[11*M+4]=threshold;
p0[12*M+4]=threshold;
p0[27*M+4]=threshold;
p0[28*M+4]=threshold;
p0[48*M+4]=threshold;
p0[1*M+5]=threshold;
p0[2*M+5]=threshold;
p0[4*M+5]=threshold;
p0[6*M+5]=threshold;
p0[7*M+5]=threshold;
p0[8*M+5]=threshold;
p0[11*M+5]=threshold;
p0[15*M+5]=threshold;
p0[19*M+5]=threshold;
p0[23*M+5]=threshold;
p0[29*M+5]=threshold;
p0[33*M+5]=threshold;
p0[1*M+6]=threshold;
p0[2*M+6]=threshold;
p0[4*M+6]=threshold;
p0[9*M+6]=threshold;
p0[42*M+6]=threshold;
p0[69*M+6]=threshold;
p0[1*M+7]=threshold;
p0[2*M+7]=threshold;
p0[12*M+7]=threshold;
p0[16*M+7]=threshold;
p0[19*M+7]=threshold;
p0[23*M+7]=threshold;
p0[92*M+7]=threshold;
p0[96*M+7]=threshold;
p0[5*M+8]=threshold;
p0[43*M+8]=threshold;
p0[1*M+9]=threshold;
p0[3*M+9]=threshold;
p0[4*M+9]=threshold;
p0[5*M+9]=threshold;
p0[6*M+9]=threshold;
p0[11*M+9]=threshold;
p0[31*M+9]=threshold;
p0[46*M+9]=threshold;
p0[48*M+9]=threshold;
p0[49*M+9]=threshold;
p0[57*M+9]=threshold;
p0[58*M+9]=threshold;
p0[82*M+9]=threshold;
p0[4*M+10]=threshold;
p0[1*M+11]=threshold;
p0[2*M+11]=threshold;
p0[4*M+11]=threshold;
p0[5*M+11]=threshold;
p0[7*M+11]=threshold;
p0[8*M+11]=threshold;
p0[9*M+11]=threshold;
p0[31*M+11]=threshold;
p0[37*M+11]=threshold;
p0[46*M+11]=threshold;
p0[63*M+11]=threshold;
p0[5*M+12]=threshold;
p0[6*M+12]=threshold;
p0[11*M+13]=threshold;
p0[11*M+14]=threshold;
p0[74*M+14]=threshold;
p0[7*M+15]=threshold;
p0[2*M+16]=threshold;
p0[9*M+16]=threshold;
p0[64*M+16]=threshold;
p0[11*M+17]=threshold;
p0[4*M+18]=threshold;
p0[9*M+19]=threshold;
p0[1*M+20]=threshold;
p0[14*M+21]=threshold;
p0[19*M+22]=threshold;
p0[1*M+23]=threshold;
p0[6*M+23]=threshold;
p0[27*M+23]=threshold;
p0[2*M+24]=threshold;
p0[3*M+24]=threshold;
p0[2*M+25]=threshold;
p0[17*M+26]=threshold;
p0[20*M+26]=threshold;
p0[4*M+27]=threshold;
p0[9*M+27]=threshold;
p0[11*M+27]=threshold;
p0[2*M+28]=threshold;
p0[26*M+29]=threshold;
p0[5*M+30]=threshold;
p0[7*M+30]=threshold;
p0[2*M+31]=threshold;
p0[4*M+31]=threshold;
p0[14*M+31]=threshold;
p0[68*M+31]=threshold;
p0[11*M+32]=threshold;
p0[4*M+33]=threshold;
p0[1*M+34]=threshold;
p0[5*M+35]=threshold;
p0[2*M+36]=threshold;
p0[16*M+36]=threshold;
p0[58*M+36]=threshold;
p0[26*M+37]=threshold;
p0[32*M+37]=threshold;
p0[4*M+38]=threshold;
p0[11*M+39]=threshold;
p0[23*M+40]=threshold;
p0[36*M+41]=threshold;
p0[9*M+42]=threshold;
p0[5*M+43]=threshold;
p0[4*M+44]=threshold;
p0[2*M+45]=threshold;
p0[6*M+46]=threshold;
p0[12*M+47]=threshold;
p0[31*M+48]=threshold;
p0[39*M+48]=threshold;
p0[9*M+49]=threshold;
p0[1*M+50]=threshold;
p0[5*M+51]=threshold;
p0[2*M+52]=threshold;
p0[9*M+53]=threshold;
p0[31*M+54]=threshold;
p0[2*M+55]=threshold;
p0[37*M+56]=threshold;
p0[43*M+57]=threshold;
p0[3*M+58]=threshold;
p0[30*M+59]=threshold;
p0[1*M+60]=threshold;
p0[33*M+61]=threshold;
p0[5*M+62]=threshold;
p0[2*M+63]=threshold;
p0[31*M+64]=threshold;
p0[6*M+65]=threshold;
p0[1*M+66]=threshold;
p0[6*M+67]=threshold;
p0[51*M+68]=threshold;
p0[36*M+69]=threshold;
p0[56*M+69]=threshold;
p0[39*M+70]=threshold;
p0[21*M+71]=threshold;
p0[60*M+72]=threshold;
p0[27*M+73]=threshold;
p0[72*M+74]=threshold;
p0[56*M+75]=threshold;
p0[28*M+76]=threshold;
p0[66*M+77]=threshold;
p0[6*M+78]=threshold;
p0[5*M+79]=threshold;
p0[46*M+80]=threshold;
p0[18*M+81]=threshold;
p0[2*M+82]=threshold;
p0[4*M+83]=threshold;
p0[53*M+84]=threshold;
p0[67*M+85]=threshold;
p0[74*M+86]=threshold;
p0[2*M+87]=threshold;
p0[26*M+88]=threshold;
p0[79*M+89]=threshold;
p0[41*M+90]=threshold;
p0[80*M+91]=threshold;
p0[17*M+92]=threshold;
p0[70*M+93]=threshold;
p0[11*M+94]=threshold;
p0[34*M+95]=threshold;
p0[2*M+96]=threshold;
p0[6*M+97]=threshold;
p0[11*M+98]=threshold;
p0[27*M+99]=threshold;
p0[4*M+100]=threshold;

	//paste codes ends here

}