#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define Maxpnt  10000 /* the maximum number of points. this can be changed for a larger system */
#define length(i) sqrt((posx[i]+axis*ecc)*(posx[i]+axis*ecc) + posy[i]*posy[i])
#define dim 3
#define G 6.67408e-11 /* units of m3 /kg /s2 */
#define kpc 3.086e19 /*conversion of meters to kiloparsecs */
#define Msolar 1.98855e30 /* mass of the sun in kg */
#define Pi 3.14159265358979323846
#define ecc sqrt(1-(baxis*baxis)/(axis*axis))
#define mu 2.2266e+23 /*the mass units in Sm chosen to make G=1 kpc^3 /mass / year^2
 */

void main(argc, argv)
int argc;
char *argv[];
{
    int n= 1000; /*the number of particles */
    double Mtot=1e11/mu; /*the total mass in Msolar */
    double Rtot=1; /* the radius in Kiloparsecs */
    double grav=1; /*gravitational constant in proper units */
    double b, posx[Maxpnt], posy[Maxpnt], posz[Maxpnt], r[Maxpnt], vx[Maxpnt], vy[Maxpnt], vz[Maxpnt], v[Maxpnt],x2,x3,x4,x5,x6,x7, mass, energy;
    b=Rtot/sqrt(3); /*b is the parameter refered to as R in the lab note */

    FILE *out;

    out = fopen("./plummerdist.c","w");

    fprintf(out,"%d \n",n);


    int i;
    srand((unsigned)time(NULL));
    for(i=0;i<n;i++){

            double x1=((double)rand()/(double)RAND_MAX);

            r[i]=1/sqrt( pow( x1 , -2.0/3.0) -1 );

            double x2=2*((double)rand()/(double)RAND_MAX) -1;
            x2=acos(x2);
            double x3=2*Pi*((double)rand()/(double)RAND_MAX);

            posz[i]=r[i]*cos(x2);
            posx[i]=r[i]*sin(x2)*cos(x3);
            posy[i]=r[i]*sin(x2)*sin(x3);

            double x4=((double)rand()/(double)RAND_MAX);
            double x5=((double)rand()/(double)RAND_MAX);


            while (.1*x5> x4*x4* pow( 1-(x4*x4) ,7.0/2.0)){
                x4=((double)rand()/(double)RAND_MAX);
                x5=((double)rand()/(double)RAND_MAX);
            }

            v[i]= x4* sqrt(2)* pow(1+ (r[i]*r[i]),-0.25) ;

            double x6=2*((double)rand()/(double)RAND_MAX) -1;
            x6=acos(x6);
            double x7=2*Pi*((double)rand()/(double)RAND_MAX);

            vz[i]=v[i]*cos(x6);
            vx[i]=v[i]*sin(x6)*cos(x7);
            vy[i]=v[i]*sin(x6)*sin(x7);
            mass=1.0/n;


            mass=Mtot/n;
            energy=-(3*Pi/64)*1*Mtot*Mtot/b;

            posx[i]*=(3*Pi/64)*1*Mtot*Mtot/(-energy);
            posy[i]*=(3*Pi/64)*1*Mtot*Mtot/(-energy);
            posz[i]*=(3*Pi/64)*1*Mtot*Mtot/(-energy);


            vx[i]*=(64/(3*Pi)) *sqrt(-energy)/sqrt(Mtot);
            vy[i]*=(64/(3*Pi)) *sqrt(-energy)/sqrt(Mtot);
            vz[i]*=(64/(3*Pi)) *sqrt(-energy)/sqrt(Mtot);




           printf("%.10e  %.10e %.10e %.10e %.10e %.10e %.10e \n", mass, posx[i], posy[i], posz[i], vx[i], vy[i], vz[i]);

           fprintf(out,"%.10e  %.10e %.10e %.10e %.10e %.10e %.10e \n", mass, posx[i], posy[i], posz[i], vx[i], vy[i], vz[i]);

        }
        fclose(out);


}
