#include<stdio.h>
#include<cuda.h>

int main()
{
    cudaDeviceProp p;
    int device_id;
    int major;
    int minor;


    cudaGetDevice(&device_id);
    cudaGetDeviceProperties(&p,device_id);

    major=p.major;
    minor=p.minor;

    printf("Name of GPU on your system is %s\n",p.name);

    printf("\n Compute Capability of a current GPU on your system is %d.%d",major,minor);

    return 0;
}