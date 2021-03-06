#include "model.h"

#define M_COUNT 31 
#define O_COUNT 1 
#define R_COUNT 30 

struct ddpStruct
{
    float oWeight[O_COUNT+1];
    float oAttainment[O_COUNT+1];
    float oAtRiskProp[O_COUNT+1];
    float rAPL[R_COUNT+1];
    float rLikelihood[R_COUNT+1];
    float mCost[M_COUNT+1];
    float roImpact[R_COUNT+1][O_COUNT+1];
    float mrEffect[M_COUNT+1][R_COUNT+1];
};

struct ddpStruct *ddpData;

void setupModel(void)
{
	ddpData = (struct ddpStruct*) malloc(sizeof(struct ddpStruct));
	ddpData->mCost[1]= 100;
    ddpData->mCost[2]= 75;
    ddpData->mCost[3]= 1250;
    ddpData->mCost[4]= 2600;
    ddpData->mCost[5]= 2000;
    ddpData->mCost[6]= 900;
    ddpData->mCost[7]= 2500;
    ddpData->mCost[8]= 0;
    ddpData->mCost[9]= 0;
    ddpData->mCost[10]= 200;
    ddpData->mCost[11]= 10000;
    ddpData->mCost[12]= 1000;
    ddpData->mCost[13]= 100;
    ddpData->mCost[14]= 0;
    ddpData->mCost[15]= 0;
    ddpData->mCost[16]= 0;
    ddpData->mCost[17]= 25;
    ddpData->mCost[18]= 800;
    ddpData->mCost[19]= 25;
    ddpData->mCost[20]= 750;
    ddpData->mCost[21]= 0;
    ddpData->mCost[22]= 2000;
    ddpData->mCost[23]= 100;
    ddpData->mCost[24]= 25;
    ddpData->mCost[25]= 25;
    ddpData->mCost[26]= 2000;
    ddpData->mCost[27]= 75;
    ddpData->mCost[28]= 75;
    ddpData->mCost[29]= 100;
    ddpData->mCost[30]= 0;
    ddpData->mCost[31]= 40;
    ddpData->rAPL[1]=1;
    ddpData->rAPL[2]=1;
    ddpData->rAPL[3]=1;
    ddpData->rAPL[4]=1;
    ddpData->rAPL[5]=1;
    ddpData->rAPL[6]=1;
    ddpData->rAPL[7]=1;
    ddpData->rAPL[8]=1;
    ddpData->rAPL[9]=1;
    ddpData->rAPL[10]=1;
    ddpData->rAPL[11]=1;
    ddpData->rAPL[12]=1;
    ddpData->rAPL[13]=1;
    ddpData->rAPL[14]=1;
    ddpData->rAPL[15]=1;
    ddpData->rAPL[16]=1;
    ddpData->rAPL[17]=1;
    ddpData->rAPL[18]=1;
    ddpData->rAPL[19]=1;
    ddpData->rAPL[20]=1;
    ddpData->rAPL[21]=1;
    ddpData->rAPL[22]=1;
    ddpData->rAPL[23]=1;
    ddpData->rAPL[24]=1;
    ddpData->rAPL[25]=1;
    ddpData->rAPL[26]=1;
    ddpData->rAPL[27]=1;
    ddpData->rAPL[28]=1;
    ddpData->rAPL[29]=1;
    ddpData->rAPL[30]=1;
    ddpData->oWeight[1]=1;
    ddpData->roImpact[1][1] = 0.3;
    ddpData->roImpact[2][1] = 0.9;
    ddpData->roImpact[4][1] = 0.3;
    ddpData->roImpact[10][1] = 0.7;
    ddpData->roImpact[15][1] = 0.7;
    ddpData->roImpact[17][1] = 0.9;
    ddpData->roImpact[18][1] = 0.7;
    ddpData->roImpact[19][1] = 0.1;
    ddpData->roImpact[20][1] = 0.7;
    ddpData->roImpact[21][1] = 0.1;
    ddpData->roImpact[22][1] = 0.3;
    ddpData->roImpact[25][1] = 0.9;
    ddpData->roImpact[26][1] = 0.7;
    ddpData->roImpact[28][1] = 0.3;
    ddpData->roImpact[29][1] = 0.3;
    ddpData->roImpact[30][1] = 0.1;
    ddpData->mrEffect[4][1] = 0.7;
    ddpData->mrEffect[5][1] = 0.1;
    ddpData->mrEffect[6][1] = 0.3;
    ddpData->mrEffect[13][1] = 0.1;
    ddpData->mrEffect[16][1] = 0.7;
    ddpData->mrEffect[22][1] = 0.3;
    ddpData->mrEffect[23][1] = 0.3;
    ddpData->mrEffect[1][2] = 0.3;
    ddpData->mrEffect[2][2] = 0.1;
    ddpData->mrEffect[3][2] = 0.3;
    ddpData->mrEffect[4][2] = 0.3;
    ddpData->mrEffect[5][2] = 0.3;
    ddpData->mrEffect[6][2] = 0.3;
    ddpData->mrEffect[7][2] = 0.3;
    ddpData->mrEffect[11][2] = 0.3;
    ddpData->mrEffect[12][2] = 0.7;
    ddpData->mrEffect[22][2] = 0.3;
    ddpData->mrEffect[26][2] = 0.9;
    ddpData->mrEffect[31][2] = 0.9;
    ddpData->mrEffect[5][3] = 0.1;
    ddpData->mrEffect[5][4] = 0.1;
    ddpData->mrEffect[6][4] = 0.9;
    ddpData->mrEffect[13][4] = 0.9999;
    ddpData->mrEffect[23][4] = 0.9;
    ddpData->mrEffect[31][4] = 0.9;
    ddpData->mrEffect[2][5] = 0.7;
    ddpData->mrEffect[3][5] = 0.3;
    ddpData->mrEffect[7][5] = 0.3;
    ddpData->mrEffect[13][6] = 0.9;
    ddpData->mrEffect[2][7] = 0.7;
    ddpData->mrEffect[7][7] = 0.4;
    ddpData->mrEffect[12][7] = 0.3;
    ddpData->mrEffect[3][8] = 0.1;
    ddpData->mrEffect[7][8] = 0.3;
    ddpData->mrEffect[12][8] = 0.7;
    ddpData->mrEffect[11][9] = 0.1;
    ddpData->mrEffect[17][9] = 0.3;
    ddpData->mrEffect[18][9] = 0.7;
    ddpData->mrEffect[5][10] = 0.3;
    ddpData->mrEffect[26][10] = 0.9;
    ddpData->mrEffect[31][10] = 0.3;
    ddpData->mrEffect[4][11] = 0.1;
    ddpData->mrEffect[5][11] = 0.1;
    ddpData->mrEffect[13][11] = 0.3;
    ddpData->mrEffect[2][15] = 0.1;
    ddpData->mrEffect[5][15] = 0.1;
    ddpData->mrEffect[6][15] = 0.1;
    ddpData->mrEffect[13][15] = 1;
    ddpData->mrEffect[23][15] = 0.3;
    ddpData->mrEffect[1][16] = 0.1;
    ddpData->mrEffect[10][16] = 0.7;
    ddpData->mrEffect[15][16] = 0.3;
    ddpData->mrEffect[2][17] = 0.1;
    ddpData->mrEffect[5][17] = 0.3;
    ddpData->mrEffect[13][17] = 0.3;
    ddpData->mrEffect[23][17] = 0.9;
    ddpData->mrEffect[10][18] = 0.1;
    ddpData->mrEffect[13][18] = 0.7;
    ddpData->mrEffect[24][18] = 0.9;
    ddpData->mrEffect[1][19] = 0.1;
    ddpData->mrEffect[2][19] = 0.3;
    ddpData->mrEffect[3][19] = 0.7;
    ddpData->mrEffect[4][19] = 0.1;
    ddpData->mrEffect[5][19] = 0.1;
    ddpData->mrEffect[6][19] = 0.3;
    ddpData->mrEffect[7][19] = 0.7;
    ddpData->mrEffect[13][19] = 0.3;
    ddpData->mrEffect[31][19] = 0.7;
    ddpData->mrEffect[5][20] = 0.3;
    ddpData->mrEffect[8][20] = 0.3;
    ddpData->mrEffect[9][20] = 0.7;
    ddpData->mrEffect[20][20] = 0.2;
    ddpData->mrEffect[27][20] = 0.7;
    ddpData->mrEffect[3][21] = 0.3;
    ddpData->mrEffect[13][21] = 0.1;
    ddpData->mrEffect[26][21] = 0.9;
    ddpData->mrEffect[31][21] = 0.3;
    ddpData->mrEffect[5][22] = 0.1;
    ddpData->mrEffect[13][22] = 0.9;
    ddpData->mrEffect[22][22] = 0.3;
    ddpData->mrEffect[1][23] = 0.1;
    ddpData->mrEffect[2][23] = 0.1;
    ddpData->mrEffect[3][23] = 0.1;
    ddpData->mrEffect[6][23] = 0.1;
    ddpData->mrEffect[11][23] = 0.1;
    ddpData->mrEffect[12][23] = 0.3;
    ddpData->mrEffect[26][23] = 0.3;
    ddpData->mrEffect[2][24] = 0.3;
    ddpData->mrEffect[3][24] = 0.3;
    ddpData->mrEffect[19][24] = 0.9;
    ddpData->mrEffect[26][24] = 0.7;
    ddpData->mrEffect[5][25] = 0.9;
    ddpData->mrEffect[6][25] = 0.7;
    ddpData->mrEffect[22][25] = 0.3;
    ddpData->mrEffect[25][25] = 0.9;
    ddpData->mrEffect[13][26] = 0.1;
    ddpData->mrEffect[26][26] = 0.1;
    ddpData->mrEffect[27][26] = 0.3;
    ddpData->mrEffect[28][26] = 0.7;
    ddpData->mrEffect[29][26] = 0.3;
    ddpData->mrEffect[30][26] = 0.7;
    ddpData->mrEffect[31][26] = 0.7;
    ddpData->mrEffect[3][27] = 0.1;
    ddpData->mrEffect[12][27] = 0.7;
    ddpData->mrEffect[1][28] = 0.7;
    ddpData->mrEffect[2][28] = 0.7;
    ddpData->mrEffect[3][28] = 0.3;
    ddpData->mrEffect[7][28] = 0.7;
    ddpData->mrEffect[12][28] = 0.3;
    ddpData->mrEffect[13][28] = 0.8;
    ddpData->mrEffect[31][28] = 0.3;
    ddpData->mrEffect[1][29] = 0.1;
    ddpData->mrEffect[3][29] = 0.1;
    ddpData->mrEffect[7][29] = 0.1;
    ddpData->mrEffect[12][29] = 0.7;
    ddpData->mrEffect[13][29] = 0.7;
    ddpData->mrEffect[1][30] = 0.3;
    ddpData->mrEffect[2][30] = 0.1;
    ddpData->mrEffect[3][30] = 0.1;
    ddpData->mrEffect[4][30] = 0.3;
    ddpData->mrEffect[6][30] = 0.7;
    ddpData->mrEffect[7][30] = 0.3;
    ddpData->mrEffect[11][30] = 0.1;
    ddpData->mrEffect[12][30] = 0.9;
    ddpData->mrEffect[14][30] = 0.7;
    ddpData->mrEffect[21][30] = 0.3;
    ddpData->mrEffect[22][30] = 0.3;
    ddpData->mrEffect[31][30] = 0.3;
}

void model(float *cost, float *att, float m[31])
{
	float costTotal, attTotal;
    ddpData->rLikelihood[1] = ddpData->rAPL[1] * (1 - m[4] * ddpData->mrEffect[4][1]) * (1 - m[5] * ddpData->mrEffect[5][1]) * (1 - m[6] * ddpData->mrEffect[6][1]) * (1 - m[13] * ddpData->mrEffect[13][1]) * (1 - m[16] * ddpData->mrEffect[16][1]) * (1 - m[22] * ddpData->mrEffect[22][1]) * (1 - m[23] * ddpData->mrEffect[23][1]);
    ddpData->rLikelihood[2] = ddpData->rAPL[2] * (1 - m[1] * ddpData->mrEffect[1][2]) * (1 - m[2] * ddpData->mrEffect[2][2]) * (1 - m[3] * ddpData->mrEffect[3][2]) * (1 - m[4] * ddpData->mrEffect[4][2]) * (1 - m[5] * ddpData->mrEffect[5][2]) * (1 - m[6] * ddpData->mrEffect[6][2]) * (1 - m[7] * ddpData->mrEffect[7][2]) * (1 - m[11] * ddpData->mrEffect[11][2]) * (1 - m[12] * ddpData->mrEffect[12][2]) * (1 - m[22] * ddpData->mrEffect[22][2]) * (1 - m[26] * ddpData->mrEffect[26][2]) * (1 - m[31] * ddpData->mrEffect[31][2]);
    ddpData->rLikelihood[3] = ddpData->rAPL[3] * (1 - m[5] * ddpData->mrEffect[5][3]);
    ddpData->rLikelihood[4] = ddpData->rAPL[4] * (1 - m[5] * ddpData->mrEffect[5][4]) * (1 - m[6] * ddpData->mrEffect[6][4]) * (1 - m[13] * ddpData->mrEffect[13][4]) * (1 - m[23] * ddpData->mrEffect[23][4]) * (1 - m[31] * ddpData->mrEffect[31][4]);
    ddpData->rLikelihood[5] = ddpData->rAPL[5] * (1 - m[2] * ddpData->mrEffect[2][5]) * (1 - m[3] * ddpData->mrEffect[3][5]) * (1 - m[7] * ddpData->mrEffect[7][5]);
    ddpData->rLikelihood[6] = ddpData->rAPL[6] * (1 - m[13] * ddpData->mrEffect[13][6]);
    ddpData->rLikelihood[7] = ddpData->rAPL[7] * (1 - m[2] * ddpData->mrEffect[2][7]) * (1 - m[7] * ddpData->mrEffect[7][7]) * (1 - m[12] * ddpData->mrEffect[12][7]);
    ddpData->rLikelihood[8] = ddpData->rAPL[8] * (1 - m[3] * ddpData->mrEffect[3][8]) * (1 - m[7] * ddpData->mrEffect[7][8]) * (1 - m[12] * ddpData->mrEffect[12][8]);
    ddpData->rLikelihood[9] = ddpData->rAPL[9] * (1 - m[11] * ddpData->mrEffect[11][9]) * (1 - m[17] * ddpData->mrEffect[17][9]) * (1 - m[18] * ddpData->mrEffect[18][9]);
    ddpData->rLikelihood[10] = ddpData->rAPL[10] * (1 - m[5] * ddpData->mrEffect[5][10]) * (1 - m[26] * ddpData->mrEffect[26][10]) * (1 - m[31] * ddpData->mrEffect[31][10]);
    ddpData->rLikelihood[11] = ddpData->rAPL[11] * (1 - m[4] * ddpData->mrEffect[4][11]) * (1 - m[5] * ddpData->mrEffect[5][11]) * (1 - m[13] * ddpData->mrEffect[13][11]);
    ddpData->rLikelihood[12] = ddpData->rAPL[12];
    ddpData->rLikelihood[13] = ddpData->rAPL[13];
    ddpData->rLikelihood[14] = ddpData->rAPL[14];
    ddpData->rLikelihood[15] = ddpData->rAPL[15] * (1 - m[2] * ddpData->mrEffect[2][15]) * (1 - m[5] * ddpData->mrEffect[5][15]) * (1 - m[6] * ddpData->mrEffect[6][15]) * (1 - m[13] * ddpData->mrEffect[13][15]) * (1 - m[23] * ddpData->mrEffect[23][15]);
    ddpData->rLikelihood[16] = ddpData->rAPL[16] * (1 - m[1] * ddpData->mrEffect[1][16]) * (1 - m[10] * ddpData->mrEffect[10][16]) * (1 - m[15] * ddpData->mrEffect[15][16]);
    ddpData->rLikelihood[17] = ddpData->rAPL[17] * (1 - m[2] * ddpData->mrEffect[2][17]) * (1 - m[5] * ddpData->mrEffect[5][17]) * (1 - m[13] * ddpData->mrEffect[13][17]) * (1 - m[23] * ddpData->mrEffect[23][17]);
    ddpData->rLikelihood[18] = ddpData->rAPL[18] * (1 - m[10] * ddpData->mrEffect[10][18]) * (1 - m[13] * ddpData->mrEffect[13][18]) * (1 - m[24] * ddpData->mrEffect[24][18]);
    ddpData->rLikelihood[19] = ddpData->rAPL[19] * (1 - m[1] * ddpData->mrEffect[1][19]) * (1 - m[2] * ddpData->mrEffect[2][19]) * (1 - m[3] * ddpData->mrEffect[3][19]) * (1 - m[4] * ddpData->mrEffect[4][19]) * (1 - m[5] * ddpData->mrEffect[5][19]) * (1 - m[6] * ddpData->mrEffect[6][19]) * (1 - m[7] * ddpData->mrEffect[7][19]) * (1 - m[13] * ddpData->mrEffect[13][19]) * (1 - m[31] * ddpData->mrEffect[31][19]);
    ddpData->rLikelihood[20] = ddpData->rAPL[20] * (1 - m[5] * ddpData->mrEffect[5][20]) * (1 - m[8] * ddpData->mrEffect[8][20]) * (1 - m[9] * ddpData->mrEffect[9][20]) * (1 - m[20] * ddpData->mrEffect[20][20]) * (1 - m[27] * ddpData->mrEffect[27][20]);
    ddpData->rLikelihood[21] = ddpData->rAPL[21] * (1 - m[3] * ddpData->mrEffect[3][21]) * (1 - m[13] * ddpData->mrEffect[13][21]) * (1 - m[26] * ddpData->mrEffect[26][21]) * (1 - m[31] * ddpData->mrEffect[31][21]);
    ddpData->rLikelihood[22] = ddpData->rAPL[22] * (1 - m[5] * ddpData->mrEffect[5][22]) * (1 - m[13] * ddpData->mrEffect[13][22]) * (1 - m[22] * ddpData->mrEffect[22][22]);
    ddpData->rLikelihood[23] = ddpData->rAPL[23] * (1 - m[1] * ddpData->mrEffect[1][23]) * (1 - m[2] * ddpData->mrEffect[2][23]) * (1 - m[3] * ddpData->mrEffect[3][23]) * (1 - m[6] * ddpData->mrEffect[6][23]) * (1 - m[11] * ddpData->mrEffect[11][23]) * (1 - m[12] * ddpData->mrEffect[12][23]) * (1 - m[26] * ddpData->mrEffect[26][23]);
    ddpData->rLikelihood[24] = ddpData->rAPL[24] * (1 - m[2] * ddpData->mrEffect[2][24]) * (1 - m[3] * ddpData->mrEffect[3][24]) * (1 - m[19] * ddpData->mrEffect[19][24]) * (1 - m[26] * ddpData->mrEffect[26][24]);
    ddpData->rLikelihood[25] = ddpData->rAPL[25] * (1 - m[5] * ddpData->mrEffect[5][25]) * (1 - m[6] * ddpData->mrEffect[6][25]) * (1 - m[22] * ddpData->mrEffect[22][25]) * (1 - m[25] * ddpData->mrEffect[25][25]);
    ddpData->rLikelihood[26] = ddpData->rAPL[26] * (1 - m[13] * ddpData->mrEffect[13][26]) * (1 - m[26] * ddpData->mrEffect[26][26]) * (1 - m[27] * ddpData->mrEffect[27][26]) * (1 - m[28] * ddpData->mrEffect[28][26]) * (1 - m[29] * ddpData->mrEffect[29][26]) * (1 - m[30] * ddpData->mrEffect[30][26]) * (1 - m[31] * ddpData->mrEffect[31][26]);
    ddpData->rLikelihood[27] = ddpData->rAPL[27] * (1 - m[3] * ddpData->mrEffect[3][27]) * (1 - m[12] * ddpData->mrEffect[12][27]);
    ddpData->rLikelihood[28] = ddpData->rAPL[28] * (1 - m[1] * ddpData->mrEffect[1][28]) * (1 - m[2] * ddpData->mrEffect[2][28]) * (1 - m[3] * ddpData->mrEffect[3][28]) * (1 - m[7] * ddpData->mrEffect[7][28]) * (1 - m[12] * ddpData->mrEffect[12][28]) * (1 - m[13] * ddpData->mrEffect[13][28]) * (1 - m[31] * ddpData->mrEffect[31][28]);
    ddpData->rLikelihood[29] = ddpData->rAPL[29] * (1 - m[1] * ddpData->mrEffect[1][29]) * (1 - m[3] * ddpData->mrEffect[3][29]) * (1 - m[7] * ddpData->mrEffect[7][29]) * (1 - m[12] * ddpData->mrEffect[12][29]) * (1 - m[13] * ddpData->mrEffect[13][29]);
    ddpData->rLikelihood[30] = ddpData->rAPL[30] * (1 - m[1] * ddpData->mrEffect[1][30]) * (1 - m[2] * ddpData->mrEffect[2][30]) * (1 - m[3] * ddpData->mrEffect[3][30]) * (1 - m[4] * ddpData->mrEffect[4][30]) * (1 - m[6] * ddpData->mrEffect[6][30]) * (1 - m[7] * ddpData->mrEffect[7][30]) * (1 - m[11] * ddpData->mrEffect[11][30]) * (1 - m[12] * ddpData->mrEffect[12][30]) * (1 - m[14] * ddpData->mrEffect[14][30]) * (1 - m[21] * ddpData->mrEffect[21][30]) * (1 - m[22] * ddpData->mrEffect[22][30]) * (1 - m[31] * ddpData->mrEffect[31][30]);
    ddpData->oAtRiskProp[1] = (ddpData->rLikelihood[1] * ddpData->roImpact[1][1]) + (ddpData->rLikelihood[2] * ddpData->roImpact[2][1]) + (ddpData->rLikelihood[4] * ddpData->roImpact[4][1]) + (ddpData->rLikelihood[10] * ddpData->roImpact[10][1]) + (ddpData->rLikelihood[15] * ddpData->roImpact[15][1]) + (ddpData->rLikelihood[17] * ddpData->roImpact[17][1]) + (ddpData->rLikelihood[18] * ddpData->roImpact[18][1]) + (ddpData->rLikelihood[19] * ddpData->roImpact[19][1]) + (ddpData->rLikelihood[20] * ddpData->roImpact[20][1]) + (ddpData->rLikelihood[21] * ddpData->roImpact[21][1]) + (ddpData->rLikelihood[22] * ddpData->roImpact[22][1]) + (ddpData->rLikelihood[25] * ddpData->roImpact[25][1]) + (ddpData->rLikelihood[26] * ddpData->roImpact[26][1]) + (ddpData->rLikelihood[28] * ddpData->roImpact[28][1]) + (ddpData->rLikelihood[29] * ddpData->roImpact[29][1]) + (ddpData->rLikelihood[30] * ddpData->roImpact[30][1]);
    ddpData->oAttainment[1] = ddpData->oWeight[1] * (1 - minValue(1, ddpData->oAtRiskProp[1]));
    attTotal = ddpData->oAttainment[1];
    costTotal = 1710 + m[1] * ddpData->mCost[1] + m[2] * ddpData->mCost[2] + m[3] * ddpData->mCost[3] + m[4] * ddpData->mCost[4] + m[5] * ddpData->mCost[5] + m[6] * ddpData->mCost[6] + m[7] * ddpData->mCost[7] + m[8] * ddpData->mCost[8] + m[9] * ddpData->mCost[9] + m[10] * ddpData->mCost[10] + m[11] * ddpData->mCost[11] + m[12] * ddpData->mCost[12] + m[13] * ddpData->mCost[13] + m[14] * ddpData->mCost[14] + m[15] * ddpData->mCost[15] + m[16] * ddpData->mCost[16] + m[17] * ddpData->mCost[17] + m[18] * ddpData->mCost[18] + m[19] * ddpData->mCost[19] + m[20] * ddpData->mCost[20] + m[21] * ddpData->mCost[21] + m[22] * ddpData->mCost[22] + m[23] * ddpData->mCost[23] + m[24] * ddpData->mCost[24] + m[25] * ddpData->mCost[25] + m[26] * ddpData->mCost[26] + m[27] * ddpData->mCost[27] + m[28] * ddpData->mCost[28] + m[29] * ddpData->mCost[29] + m[30] * ddpData->mCost[30] + m[31] * ddpData->mCost[31];

	for (int i = 1; i < 31; i++) {
		printf("Likelihood[i] = %.5f\n", ddpData->rLikelihood[i]);
	}
	
	printf("At-risk-prop: %.5f\n", ddpData->oAtRiskProp[1]);
	
	*cost = costTotal;
	*att = attTotal; 
}

float minValue(float val1, float val2)
{
	if (val1 < val2)
		return val1;
	else
		return val2;
}
