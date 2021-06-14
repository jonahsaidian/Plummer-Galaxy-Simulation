#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define Maxpnt  1000 /* the maximum number of points. this can be changed for a larger system */
#define dim 3
#define G 6.67408e-11 /* units of m3 /kg /s2 */
#define kpc 3.086e19 /*conversion of meters to kiloparsecs */
#define Msolar 1.98855e30 /* mass of the sun in kg */
#define Pi 3.14159265358979323846
#define bmass 5.683e26 /* the mass of the central  body */
#define lmass 1e24 /* the mass of the orbiting bodies*/
/*#define baxis sqrt(1-(ecc*ecc))*axis */
#define ecc sqrt(1-(baxis*baxis)/(axis*axis))

void main(argc, argv)
int argc;
char *argv[];
{


    int numParticles, n, i;
    double mass[Maxpnt],posx[Maxpnt],posy[Maxpnt],posz[Maxpnt], vx[Maxpnt],vy[Maxpnt], vz[Maxpnt],grav;
    grav=G *Msolar/(kpc*kpc*kpc); /*gravitational constant in proper units */




    FILE *inputFile;
    FILE *out;
    inputFile = fopen("./plummerdist.c", "r");
    out = fopen("./out0.c","w");





    if (inputFile == NULL) {
        printf("Can't open input file in.list!\n");
        exit(1);
    }




    fscanf(inputFile, "%d", &numParticles);
    n=numParticles;
    printf("%d \n", numParticles);



    for(i=0; i<n; i++)
    {
            fscanf(inputFile, "%lf", &mass[i]);
            fscanf(inputFile, "%lf", &posx[i]);
            fscanf(inputFile, "%lf", &posy[i]);
            fscanf(inputFile, "%lf", &posz[i]);
            fscanf(inputFile, "%lf", &vx[i]);
            fscanf(inputFile, "%lf", &vy[i]);
            fscanf(inputFile, "%lf", &vz[i]);




     printf("%d %.10e %.10e %.10e %.10e %.10e %.10e %.10e\n", i, mass[i], posx[i], posy[i], posz[i], vx[i], vy[i], vz[i]);


    }



    fclose(inputFile);


    /*Begin the simulation here! be sure to set parameters properly
    */


    double t=0.0, dt;

   /* double tmax=3e7;  the maximum time to run the     code    for in seconds */

    int nsteps = 5e5; /* the number of steps to iterate */

    dt= 10; /*the step size. if you want this fixed simply remove tmax and set this to the desired value */

    int nout = 30; /* the number of steps to skip when printing */

   for(i=0;i<n;i++){


        fprintf(out, "%f %d %.10e %.10e %.10e %.10e %.10e %.10e     0.0    0.0   0.0\n", t, i, posx[i], posy[i], posz[i], vx[i],vy[i],vz[i]);


    }

    int j;

    double ax[Maxpnt], ay[Maxpnt], az[Maxpnt], dx, dy,dz,dr;
    for(j=0; j<=nsteps; j++){
        int i;
            for(i=0;i<n;i++){

                    ax[i]=0;
                    ay[i]=0;
                    az[i]=0;


                    int k;
                    for(k=0;k<n;k++){
                        if (k!=i){
                            dx=posx[i]-posx[k];
                            dy=posy[i]-posy[k];
                            dz=posz[i]-posz[k];
                            dr=sqrt(dx*dx + dy*dy + dz*dz);
                            ax[i]=ax[i] -1*mass[k]*(dx/(dr*dr*dr));
                            ay[i]=ay[i] -1*mass[k]*(dy/(dr*dr*dr));
                            az[i]=az[i] -1*mass[k]*(dz/(dr*dr*dr));
                        }
                    }



                    vx[i]+=ax[i]*dt*.5;
                    vy[i]+=ay[i]*dt*.5;
                    vz[i]+=az[i]*dt*.5;


            }
            for(i=0;i<n;i++){

                    posx[i]+=vx[i]*dt;
                    posy[i]+=vy[i]*dt;
                    posz[i]+=vz[i]*dt;
            }
            for(i=0;i<n;i++){

                    ax[i]=0;
                    ay[i]=0;
                    az[i]=0;



                    int k;
                    for(k=0;k<n;k++){
                        if (k!=i){
                            dx=posx[i]-posx[k];
                            dy=posy[i]-posy[k];
                            dz=posz[i]-posz[k];
                            dr=sqrt(dx*dx + dy*dy +dz*dz);
                            ax[i]= ax[i]-1*mass[k] * (dx/(dr*dr*dr));
                            ay[i]=ay[i]-1*mass[k] * (dy/(dr*dr*dr));
                            az[i]=az[i]-1*mass[k] * (dz/(dr*dr*dr));
                        }
                    }



                    vx[i]+=ax[i]*dt*.5;
                    vy[i]+=ay[i]*dt*.5;
                    vz[i]+=az[i]*dt*.5;
                }
            t += dt;
               if (j % nout ==0){
               for(i=0;i<n;i++){
                    fprintf(out, "%f %d %.10e %.10e %.10e %.10e %.10e %.10e %.10e %.10e %.10e\n", t, i, posx[i], posy[i], posz[i],vx[i], vy[i], vz[i], ax[i], ay[i],az[i]);
                }
                }
            }

}
