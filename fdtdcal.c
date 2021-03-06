#include "fdtdcal.h"
int initecal(double ex[],double ey[],double ez[],int strides[],int shapes[])
{
    I=shapes[0];
    J=shapes[1];
    K=shapes[2];
    S0 = strides[0] / sizeof(double);
    S1 = strides[1] / sizeof(double);
    S2 = strides[2] / sizeof(double);
    ex1=ex;
    ey1=ey;
    ez1=ez;
    flog++;
    return 0;
}
int initbcal(double bx[],double by[],double bz[],int strides[],int shapes[])
{
    bx1=bx;
    by1=by;
    bz1=bz;
    flog++;
    return 0;
}
int inite2cal(double ex[],double ey[],double ez[],int strides[],int shapes[])
{
    ex2=ex;
    ey2=ey;
    ez2=ez;
    flog++;
    return 0;
}
int initb2cal(double bx[],double by[],double bz[],int strides[],int shapes[])
{
    bx2=bx;
    by2=by;
    bz2=bz;
    flog++;
    return 0;
}
int cal(int n)
{
    double * tem;
    
    for (int ii = 0; ii < n; ii++)
    {
        // printf("%s \n","85");
        for(int i = 2; i < I-2; i++)
        {
            // printf("%s \n","777");
            for(int j = 2; j < J-2; j++)
            {
                //printf("%s","++");
                #pragma omp parallel for
                for(int k = 2; k < K-1; k++)
                {
                    ex2[S0*i+S1*j+S2*k]=1*ex1[S0*i+S1*j+S2*k]+1*(1/det)*((bz1[S0*i+S1*j+S2*k]-bz1[S0*i+S1*(j-1)+S2*k])-by1[S0*i+S1*j+S2*k]+by1[S0*i+S1*j+S2*(k-1)]);
                    ey2[S0*i+S1*j+S2*k]=1*ey1[S0*i+S1*j+S2*k]+1*(1/det)*((bx1[S0*i+S1*j+S2*k]-bx1[S0*i+S1*j+S2*(k-1)])-bz1[S0*i+S1*j+S2*k]+bz1[S0*(i-1)+S1*j+S2*(k)]);
                    ez2[S0*i+S1*j+S2*k]=1*ez1[S0*i+S1*j+S2*k]+1*(1/det)*((by1[S0*i+S1*j+S2*k]-by1[S0*(i-1)+S1*j+S2*(k)])-bx1[S0*i+S1*j+S2*k]+by1[S0*(i)+S1*(j-1)+S2*(k)]);
                    bx2[S0*i+S1*j+S2*k]=1*bx1[S0*i+S1*j+S2*k]-1*(1/det)*((ez1[S0*i+S1*j+S2*k]-ez1[S0*i+S1*(j-1)+S2*k])-ey1[S0*i+S1*j+S2*k]+ey1[S0*i+S1*j+S2*(k-1)]);
                    by2[S0*i+S1*j+S2*k]=1*by1[S0*i+S1*j+S2*k]-1*(1/det)*((ex1[S0*i+S1*j+S2*k]-ex1[S0*i+S1*j+S2*(k-1)])-ez1[S0*i+S1*j+S2*k]+ez1[S0*(i-1)+S1*j+S2*(k)]);
                    bz2[S0*i+S1*j+S2*k]=1*bz1[S0*i+S1*j+S2*k]-1*(1/det)*((ey1[S0*i+S1*j+S2*k]-ey1[S0*(i-1)+S1*j+S2*(k)])-ex1[S0*i+S1*j+S2*k]+ey1[S0*(i)+S1*(j-1)+S2*(k)]);
                }
                
            }
            
        }
    // printf("%s \n","66");
    tem=ex1;
    ex1=ex2;
    ex2=tem;

    tem=ey1;
    ey1=ey2;
    ey2=tem;

    tem=ez1;
    ez1=ez2;
    ez2=tem;

    tem=bx1;
    bx1=bx2;
    bx2=tem;

    tem=by1;
    by1=by2;
    by2=tem;

    tem=bz1;
    bz1=bz2;
    bz2=tem;
    }
    
    return 0;
}
int intarry(double adet)
{
    det=adet;
    return 0;
}

