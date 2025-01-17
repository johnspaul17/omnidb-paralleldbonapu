#include "common.h"
#include "Helper.h"
#include "OpenCL_DLL.h"
#include "KernelScheduler.h"
// OpenCL Vars---------0 for CPU, 1 for GPU
extern cl_context Context;        // OpenCL context
extern cl_program Program;           // OpenCL program
extern cl_command_queue CommandQueue[2];// OpenCL command que
extern cl_platform_id Platform[2];      // OpenCL platform
extern cl_device_id Device[2];          // OpenCL device
extern cl_ulong totalLocalMemory[2];      /**< Max local memory allowed */
extern cl_device_id allDevices[10];


void setValueListImpl (cl_mem d_ValueList,int delta, int rLen, cl_mem d_destRin,  int numThreadPB, int numBlock,int *index,cl_event *eventList,cl_kernel *kernel,int *Flag_CPU_GPU,double * burden,int _CPU_GPU)
	//setRIDListImpl(d_ValueList, d_tempOutput, numThreadPerBlock,numBlock, rLen, d_destRin, CPU_GPU);
{	
	size_t numThreadsPerBlock_x=numThreadPB;
	size_t globalWorkingSetSize=numThreadPB*numBlock;
	cl_getKernel("setValueList_kernel",kernel);
    // Set the Argument values
    cl_int ciErr1 = clSetKernelArg((*kernel), 0, sizeof(cl_mem), (void*)&d_ValueList);
	ciErr1 |= clSetKernelArg((*kernel), 1, sizeof(cl_int), (void*)&delta);
    ciErr1 |= clSetKernelArg((*kernel), 2, sizeof(cl_int), (void*)&rLen);
    ciErr1 |= clSetKernelArg((*kernel), 3, sizeof(cl_mem), (void*)&d_destRin);    
    //printf("clSetKernelArg 0 - 3...\n\n"); 
    if (ciErr1 != CL_SUCCESS)
    {
        printf("Error in clSetKernelArg, Line %u in file %s !!!\n\n", __LINE__, __FILE__);
        cl_clean(EXIT_FAILURE);
    }	
	kernel_enqueue(rLen, 12
		,1, &globalWorkingSetSize, &numThreadsPerBlock_x,eventList,index,kernel,Flag_CPU_GPU,burden,_CPU_GPU);
}
void getValueListImpl (cl_mem d_Rin,int delta, int rLen, cl_mem* d_ValueList, cl_mem d_tempOutput,  int numThreadPB, int numBlock,int *index,cl_event *eventList,cl_kernel *kernel,int *Flag_CPU_GPU,double * burden,int _CPU_GPU)
{	
	size_t numThreadsPerBlock_x=numThreadPB;
	size_t globalWorkingSetSize=numThreadPB*numBlock;
	//getValueList_kernel(__global int *d_ValueList,int delta,__global int *d_output, int rLen,__global Record *d_Rin) 

	cl_getKernel("getValueList_kernel",kernel);
    // Set the Argument values
    cl_int ciErr1 = clSetKernelArg((*kernel), 0, sizeof(cl_int), (void*)d_ValueList);
	ciErr1 |= clSetKernelArg((*kernel), 1, sizeof(cl_int), (void*)&delta);
	ciErr1 |= clSetKernelArg((*kernel), 2, sizeof(cl_mem), (void*)&d_tempOutput);
    ciErr1 |= clSetKernelArg((*kernel), 3, sizeof(cl_int), (void*)&rLen);
    ciErr1 |= clSetKernelArg((*kernel), 4, sizeof(cl_mem), (void*)&d_Rin);    
    //printf("clSetKernelArg 0 - 3...\n\n"); 
    if (ciErr1 != CL_SUCCESS)
    {
        printf("Error in clSetKernelArg, Line %u in file %s !!!\n\n", __LINE__, __FILE__);
        cl_clean(EXIT_FAILURE);
    }
	kernel_enqueue(rLen, 13
		,1, &globalWorkingSetSize, &numThreadsPerBlock_x,eventList,index,kernel,Flag_CPU_GPU,burden,_CPU_GPU);
}
void testsetValueListImpl(int rLen, int numThreadPB , int numBlock, int CPU_GPU )
{

}