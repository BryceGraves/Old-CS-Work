// 1. Program header

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif
#include <omp.h>

#include "cl.h"
#include "cl_platform.h"

#ifndef SCALER
  #define SCALER 64
#endif

#define NUM_ELEMENTS SCALER * 512 * 512

#ifndef LOCAL_SIZE
  #define LOCAL_SIZE 64
#endif

#define NUM_WORK_GROUPS NUM_ELEMENTS / LOCAL_SIZE

const char *CL_FILE_NAME = {"project_6.cl"};
const float TOL = 0.0001f;

void Wait(cl_command_queue);
int LookAtTheBits(float);

int main(int argc, char *argv[]) {
  size_t local_size = LOCAL_SIZE, opt = 0, scaler = SCALER;
  const char *method = "ArrayMult";

  while ((opt = getopt(argc, argv, "hl:m:s:")) != -1) {
    switch (opt) {
      case 'h':
        fprintf(stderr,
                "Accepted command line arguments are h, l, m, and s.\n");
        return EXIT_SUCCESS;

      case 'l':
        local_size = atoi(optarg);
        break;

      case 'm':
        method = optarg;
        break;

      case 's':
        scaler = atoi(optarg);
        break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        return EXIT_FAILURE;
    }
  }

  size_t num_elements = scaler;
  size_t num_work_groups = num_elements / local_size;

  // see if we can even open the opencl kernel program
  // (no point going on if we can't):

  FILE *fp;
#ifdef WIN32
  errno_t err = fopen_s(&fp, CL_FILE_NAME, "r");
  if (err != 0)
#else
  fp = fopen(CL_FILE_NAME, "r");
  if (fp == NULL)
#endif
  {
    fprintf(stderr, "Cannot open OpenCL source file '%s'\n", CL_FILE_NAME);
    return 1;
  }

  cl_int status;  // returned status from opencl calls
                  // test against CL_SUCCESS

  // get the platform id:

  cl_platform_id platform;
  status = clGetPlatformIDs(1, &platform, NULL);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clGetPlatformIDs failed (2) with status code: %d\n",
            status);

  // get the device id:

  cl_device_id device;
  cl_device_id devices[2];  // number of devices this platform has
  status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 2, devices, NULL);
  // get one device id
  if (status != CL_SUCCESS)
    fprintf(stderr, "clGetDeviceIDs failed (2) with status code: %d\n", status);
  device = devices[0];  // use the first one

  // 2. allocate the host memory buffers:

  float *hA = new float[num_elements];
  float *hB = new float[num_elements];
  float *hC = new float[num_elements];
  float *hD = new float[num_elements];

  // fill the host memory buffers:

  for (int i = 0; i < num_elements; i++) {
    hA[i] = hB[i] = hC[i] = (float)sqrt((double)i);
    hD[i] = 0.0;
  }

  size_t dataSize = num_elements * sizeof(float);

  // 3. create an opencl context:

  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &status);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clCreateContext failed with status code: %d\n", status);

  // 4. create an opencl command queue:

  cl_command_queue cmdQueue = clCreateCommandQueue(context, device, 0, &status);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clCreateCommandQueue failed with status code: %d\n",
            status);

  // 5. allocate the device memory buffers:

  cl_mem dA =
      clCreateBuffer(context, CL_MEM_READ_ONLY, dataSize, NULL, &status);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clCreateBuffer failed (1) with status code: %d\n", status);

  cl_mem dB =
      clCreateBuffer(context, CL_MEM_READ_ONLY, dataSize, NULL, &status);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clCreateBuffer failed (2) with status code: %d\n", status);

  cl_mem dC =
      clCreateBuffer(context, CL_MEM_WRITE_ONLY, dataSize, NULL, &status);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clCreateBuffer failed (3) with status code: %d\n", status);

  cl_mem dD =
      clCreateBuffer(context, CL_MEM_WRITE_ONLY, dataSize, NULL, &status);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clCreateBuffer failed (3) with status code: %d\n", status);

  // 6. enqueue the 2 commands to write the data from the host buffers to the
  // device buffers:

  status = clEnqueueWriteBuffer(cmdQueue, dA, CL_FALSE, 0, dataSize, hA, 0,
                                NULL, NULL);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clEnqueueWriteBuffer failed (1)\n");

  status = clEnqueueWriteBuffer(cmdQueue, dB, CL_FALSE, 0, dataSize, hB, 0,
                                NULL, NULL);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clEnqueueWriteBuffer failed (2)\n");

  status = clEnqueueWriteBuffer(cmdQueue, dC, CL_FALSE, 0, dataSize, hB, 0,
                                NULL, NULL);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clEnqueueWriteBuffer failed (2)\n");

  Wait(cmdQueue);

  // 7. read the kernel code from a file:

  fseek(fp, 0, SEEK_END);
  size_t fileSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char *clProgramText = new char[fileSize + 1];  // leave room for '\0'
  size_t n = fread(clProgramText, 1, fileSize, fp);
  clProgramText[fileSize] = '\0';
  fclose(fp);

  // Commented this out since the compiler couldn't seem to see I changed %d to
  // %zu
  // if (n != fileSize)
  //   fprintf(stderr,
  //           "Expected to read %d bytes read from '%s' -- actually read
  //           %zu.\n", fileSize, CL_FILE_NAME, n);

  // create the text for the kernel program:

  char *strings[1];
  strings[0] = clProgramText;
  cl_program program = clCreateProgramWithSource(
      context, 1, (const char **)strings, NULL, &status);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clCreateProgramWithSource failed\n");
  delete[] clProgramText;

  // 8. compile and link the kernel code:

  const char *options = {""};
  status = clBuildProgram(program, 1, &device, options, NULL, NULL);
  if (status != CL_SUCCESS) {
    size_t size;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL,
                          &size);
    cl_char *log = new cl_char[size];
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, size, log,
                          NULL);
    fprintf(stderr, "clBuildProgram failed:\n%s\n", log);
    delete[] log;
  }

  // 9. create the kernel object:

  cl_kernel kernel = clCreateKernel(program, method, &status);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clCreateKernel failed with status code: %d\n", status);

  // 10. setup the arguments to the kernel object:

  status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &dA);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clSetKernelArg failed (1) with status code: %d\n", status);

  status = clSetKernelArg(kernel, 1, sizeof(cl_mem), &dB);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clSetKernelArg failed (2) with status code: %d\n", status);

  status = clSetKernelArg(kernel, 2, sizeof(cl_mem), &dC);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clSetKernelArg failed (3) with status code: %d\n", status);

  status = clSetKernelArg(kernel, 3, sizeof(cl_mem), &dD);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clSetKernelArg failed (3) with status code: %d\n", status);

  if (strcmp(method, "ArrayMultReduce") == 0) {
    status = clSetKernelArg(kernel, 4, local_size * sizeof(float), NULL);
    if (status != CL_SUCCESS)
      fprintf(stderr, "clSetKernelArg failed (3) with status code: %d\n",
              status);
  }

  // 11. enqueue the kernel object for execution:

  size_t globalWorkSize[3] = {num_elements, 1, 1};
  size_t localWorkSize[3] = {local_size, 1, 1};

  Wait(cmdQueue);
  double time0 = omp_get_wtime();

  time0 = omp_get_wtime();

  status = clEnqueueNDRangeKernel(cmdQueue, kernel, 1, NULL, globalWorkSize,
                                  localWorkSize, 0, NULL, NULL);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clEnqueueNDRangeKernel failed: %d\n", status);

  Wait(cmdQueue);

  if (strcmp(method, "ArrayMultReduce") == 0) {
    float sum;
    for (int i = 0; i < num_work_groups; i++) {
      sum += hC[i];
    }
  }

  double time1 = omp_get_wtime();

  // 12. read the results buffer back from the device to the host:

  status = clEnqueueReadBuffer(cmdQueue, dD, CL_TRUE, 0, dataSize, hD, 0, NULL,
                               NULL);
  if (status != CL_SUCCESS)
    fprintf(stderr, "clEnqueueReadBuffer failed with status code: %d\n",
            status);

  // In GigaMultsPerSecond
  fprintf(stdout, "%s,%zu,%zu,%lf\n", method, num_elements, local_size,
          (double)num_elements / (time1 - time0) / 1000000.0);

#ifdef WIN32
  Sleep(2000);
#endif

  // 13. clean everything up:

  clReleaseKernel(kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(cmdQueue);
  clReleaseMemObject(dA);
  clReleaseMemObject(dB);
  clReleaseMemObject(dC);
  clReleaseMemObject(dD);

  delete[] hA;
  delete[] hB;
  delete[] hC;
  delete[] hD;

  return 0;
}

int LookAtTheBits(float fp) {
  int *ip = (int *)&fp;
  return *ip;
}

// wait until all queued tasks have taken place:

void Wait(cl_command_queue queue) {
  cl_event wait;
  cl_int status;

  status = clEnqueueMarker(queue, &wait);
  if (status != CL_SUCCESS)
    fprintf(stderr, "Wait: clEnqueueMarker failed with status code: %d\n",
            status);

  status = clWaitForEvents(1, &wait);
  if (status != CL_SUCCESS)
    fprintf(stderr, "Wait: clWaitForEvents failed with status code: %d\n",
            status);
}
