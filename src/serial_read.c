/**
 * @file serial_read.c
 * @name Stephen Abraham
 * @date 08/06/2018
 * @email sabrah03@uoguelph.ca
 * @brief Reads data from a serial port and outputs the data to a file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>

#define port "/dev/ttyACM0"

/**
 *@brief initializes the serial port to communicating
 *@pre port must be open and exist
 **/
void initComPort(int *sfd, char *device);

/**
 *@brief delays code by given amount of milliseconds
 *@pre must be a postive value
 *@param number_of_seconds the quanity of time for the delay in milli_seconds
 **/
void delay(int number_of_seconds);

void main(){
  int sfd;
  char currTime[64];
  FILE *filePtr = NULL;
  int32_t bitsReceived;
  u_int32_t bytes;
  u_int8_t buff[10000];

  initComPort(&sfd, port); //Initializes the serial port defined by port
  delay(5000); //delays program executation by 5 seconds

  /* Adds the column titles delimitted by commas */
  filePtr = fopen("fuel_data.csv", "a");
  fseek(filePtr, 0, SEEK_END);
  if(ftell(filePtr) == 0){
      fprintf(filePtr, "Time,Sample #,Flow Rate (L/Min),Pressure (PSI),Temperature (Celsius)");
  }
  fclose(filePtr);

  while (1)
  {
    ioctl(sfd, FIONREAD, &bytes); //checls if there is data available
    if (bytes > 0)
    {
      bitsReceived = read(sfd, buff, 10000); //read whats available

      /* Timestamp functionality disabled. Uncomment to re-enable */
      //strftime(currTime, sizeof(currTime), "%c", localtime(&t));

      if (bitsReceived < 0)
      {
        fprintf(stderr, "read failed\n");
      }
      else if (bitsReceived > 0)
      {
        filePtr = fopen("fuel_data.csv", "a");
        if (access("fuel_data.csv", F_OK) == -1)
        {
          fprintf(stderr, "unable to open output file\n");
          exit(-1);
        }else{
          fwrite(buff, 1, bitsReceived, filePtr);
        }
        fclose(filePtr);
      }
    }
    usleep(1000);
  }
}

void initComPort(int *sfd, char *device) {
  struct termios options;

  *sfd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
  if (*sfd == -1)
  {
    fprintf(stderr, "unable to open %s\n", device);
    exit(1);
  }
  else
  {
    fcntl(*sfd, F_SETFL, FNDELAY);
  }

  tcgetattr(*sfd, &options);

  cfsetispeed(&options, B9600);
  cfsetospeed(&options, B9600);

  cfmakeraw(&options);

  options.c_cflag &= ~(PARENB | CSTOPB | CSIZE | CRTSCTS);
  options.c_cflag |= (CLOCAL | CREAD | CS8);

  options.c_oflag &= ~OPOST;
  options.c_cc[VMIN] = 1;
  options.c_cc[VTIME] = 0;

  tcsetattr(*sfd, TCSANOW, &options);
}

void delay(int number_of_seconds)
{
  // Converting time into milli_seconds
  int milli_seconds = 1000 * number_of_seconds;

  // Stroing start time
  clock_t start_time = clock();

  // looping till required time is not acheived
  while (clock() < start_time + milli_seconds)
    ;
}