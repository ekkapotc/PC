#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <omp.h>
#include <iostream>

static int numParticles;
static int timeSteps = 10000;
static float dt = 1e-3;
static float G = 6.67e-11; 

static float * Mass;
static float * Rx;
static float * Ry;
static float * Vx;
static float * Vy;
static float * Fx;
static float * Fy;

void compute_forces(){
  
   for(int i=0;i<numParticles;i++)
   {
        for(int j=0;j<numParticles;j++)
        {
            if(i!=j)
            {
                float dx = Rx[i] - Rx[j];
                float dy = Ry[i] - Ry[j];
                
                float dr = std::sqrt(dx*dx + dy*dy);
                float dr3 = dr*dr*dr;
                
                Fx[i] += (G*(Mass[i])*(Mass[j])*dx)/dr3;
                Fy[i] += (G*(Mass[i])*(Mass[j])*dy)/dr3;
            }
        }
   }
}


void update_trajectories(){
    
    for(int i=0;i<numParticles;i++)
    {        
        Vx[i] += (dt*Fx[i])/Mass[i];
        Vy[i] += (dt*Fy[i])/Mass[i];
        Rx[i] += dt*Vx[i];
        Ry[i] += dt*Vy[i];
    }
}

int main(int argc , char ** argv){

  if(argc!=3){
    fprintf(stderr,"USAGE: NBSim <INPUTFILE> <OUTPUTFILE>");
    exit(1);
  }
    
  FILE * fp = fopen(argv[1],"r");
  
  fscanf(fp,"%d",&numParticles);  
 
  Mass = new float[numParticles];
  Rx = new float[numParticles];
  Ry = new float[numParticles];
  Vx = new float[numParticles];
  Vy = new float[numParticles];
  Fx = new float[numParticles];
  Fy = new float[numParticles];
  
  for(int i=0;i<numParticles;i++)
  {
    fscanf(fp,"%f %f %f %f %f",&Mass[i],&Rx[i],&Ry[i],&Vx[i],&Vy[i]);
    
    Fx[i] = 0.0;
    Fy[i] = 0.0;
  }
  
  fclose(fp);
  
  struct timespec startTime, endTime;
  clock_gettime(CLOCK_REALTIME, &startTime);
  
  float time = 0.0;

  for(int i=0;i<timeSteps;i++)
  {
      compute_forces();
      
      update_trajectories();
  }
  
  clock_gettime(CLOCK_REALTIME, &endTime);

  float runtime = (endTime.tv_sec-startTime.tv_sec)+(endTime.tv_nsec-startTime.tv_nsec)/1e9;
  
  fp = fopen(argv[2],"w");
  
  fprintf(fp,"%d\n",numParticles);
  
  for(int i=0;i<numParticles;i++)
  {
    fprintf(fp,"%f %f %f %f %f\n",Mass[i],Rx[i],Ry[i],Vx[i],Vy[i]);
  }
  
  fclose(fp);
  
  delete [] Mass;
  delete [] Rx;
  delete [] Ry;
  delete [] Vx;
  delete [] Vy;
  delete [] Fx;
  delete [] Fy;
  
  std::cout << "The simulation took " << runtime << " sec." << std::endl;
    
  return 0;
}
