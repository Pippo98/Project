/*
* I run this code on ubuntu 16.04
*
* This code takes in input a file named "log.txt" whith a log of real data from a sensor
* The data are in a specific order: timestamp(ms), acccelerometer x, acccelerometer y, acccelerometer z, gyroscope x, gyroscope y, gyroscope z
* The data are separated by a "\t" (tab) character, if you don't use this separator you have to change it in get_number() function
* At the end of the file remember to use some "/" to let the program know that the file is finished
* Unit and decimal must be separated by a dot
*
* The data on the file are of my smartphone sensor
*/

#include "stdlib.h"
#include "stdio.h"
#include <math.h>
#include "time.h"
#include "main.h"

//declaring the pointer to file
FILE *fil;

int main(){

  //structures declared in main.h
  gyro_accel_stc gyro;
  gyro_accel_stc accel;
  angles_data_stc angle;

  //initializing variables
  gyro.sensitivity = 131;

  accel.x_offset = 0;
  accel.y_offset = 0;
  accel.z_offset = 0;
  gyro.x_offset = 0;
  gyro.y_offset = 0;
  gyro.z_offset = 0;

  angle.PI = 3.14159265359;

  dt = 10000;

  accel.past_size = 100;
  gyro.past_size = 100;

  //comment or uncomment this line to calculate the initial offset of the sensor
  //get_offset(&accel, &gyro);

  //opening the file
  fil = fopen("log.txt", "r");

  while(1){

    //get_accel(&accel);
    //get_gyro(&gyro);

    //reading the data from the file
    get_data(&accel, &gyro, buffer);

    //map_accel(&accel, 32768,  100);
    //map_gyro (&gyro,  32768, 100);

    //shiftinh the array and calculating the average of the members
    shift_array(accel.x_past, 100, accel.x);
    shift_array(accel.y_past, 100, accel.y);
    shift_array(accel.z_past, 100, accel.z);
    dynamic_average(accel.x_past, 100, &accel.x);
    dynamic_average(accel.y_past, 100, &accel.y);
    dynamic_average(accel.z_past, 100, &accel.z);

    shift_array(gyro.x_past, 100, gyro.x);
    shift_array(gyro.y_past, 100, gyro.y);
    shift_array(gyro.z_past, 100, gyro.z);
    dynamic_average(gyro.x_past, 100, &gyro.x);
    dynamic_average(gyro.y_past, 100, &gyro.y);
    dynamic_average(gyro.z_past, 100, &gyro.z);

    //doing some math to get the angle given the accelerometer and gyroscope data
    get_angle(&accel, &gyro, &angle);

    //printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\r\n", timestamp, accel.x, accel.y, accel.z, gyro.x, gyro.y, gyro.z);
    printf("%f\t%f\t%f\r\n", angle.pitch, angle.roll, angle.force);
    //printf("%d\r\n", dt);

    delay(dt + 10000);

  }

  return 0;

}

void get_angle(gyro_accel_stc * a, gyro_accel_stc * g, angles_data_stc * angle){

  //calculating the pitch and roll only integrating the gyroscope data
  angle->pitch += (g->x / g->sensitivity)*dt;
  angle->roll  -= (g->y / g->sensitivity)*dt;

  //calculating the total force on the object
  //I multiplied and divided the values ecause the abs() function returns integers
  angle->force = abs(a->x * 1000000000) +
                 abs(a->y * 1000000000) +
                 abs(a->z * 1000000000);
  angle->force /= 1000000000;

  //calculating the angle fron the accelerometer data
  angle->accel_pitch = atan2(a->y, a->z) * 180 / angle->PI;
  angle->accel_roll  = atan2(a->x, a->z) * 180 / angle->PI;

  //using the complementary filter to make a better calculation
  //you can use different constants (0.98, 0.02) to calibrate the filter
  angle->pitch = angle->pitch * 0.98 + angle->accel_pitch * 0.02;
  angle->roll  = angle->roll  * 0.98 + angle->accel_roll  * 0.02;

}

//function that calculates the initial offset
void get_offset(gyro_accel_stc * a, gyro_accel_stc * g){

  //change the a->past_size to modify how many iterations will be done
  for(int i = 0; i < a->past_size; i++){

    get_accel(a);
    get_gyro(g);

    shift_array(a->x_past, a->past_size, a->x);
    shift_array(a->y_past, a->past_size, a->y);
    shift_array(a->z_past, a->past_size, a->z);
    shift_array(g->x_past, a->past_size, g->x);
    shift_array(g->y_past, a->past_size, g->y);
    shift_array(g->z_past, a->past_size, g->z);

  }

  //calculate the offset by making the average of the values calculated
  dynamic_average(a->x_past, a->past_size, &a->x_offset);
  dynamic_average(a->y_past, a->past_size, &a->y_offset);
  dynamic_average(a->z_past, a->past_size, &a->z_offset);
  dynamic_average(g->x_past, a->past_size, &g->x_offset);
  dynamic_average(g->y_past, a->past_size, &g->y_offset);
  dynamic_average(g->z_past, a->past_size, &g->z_offset);

}

//fake function to generate test angles
void get_gyro(gyro_accel_stc * g){

  g->x = (rand() % 201) - 100;
  g->y = (rand() % 201) - 100;
  g->z = (rand() % 201) - 100;

  g->x -= g->x_offset;
  g->y -= g->y_offset;
  g->z -= g->z_offset;

}

//fake function to generate test angles
void get_accel(gyro_accel_stc * a){

  a->x = (rand() % 201)- 100;
  a->y = (rand() % 201) - 100;
  a->z = (rand() % 201) + 8800;

  a->x -= a->x_offset;
  a->y -= a->y_offset;
  a->z -= a->z_offset;

}

//function to map var between two values
//min and max are the current minimum and maximum values that var could get
//n_min and n_max are the new min and max values that var could get
void map(double * var, double min, double max, double n_min, double n_max){

  double range, n_range;
  range = max - min;
  n_range = n_max - n_min;

  *var = ((*var - min) * n_range) / range;
  *var += n_min;

}

//function to map only accelerometer data
//scale determins the min and max values of the variable after this function is called
void map_accel(gyro_accel_stc * a, int actual_scale, int scale){

  map(&a->x, -actual_scale, actual_scale, -scale, scale);
  map(&a->y, -actual_scale, actual_scale, -scale, scale);
  map(&a->z, -actual_scale, actual_scale, -scale, scale);

}

//function to map only gyroscope data
//scale determins the min and max values of the variable after this function is called
void map_gyro(gyro_accel_stc * g, int actual_scale, int scale){

  map(&g->x, -actual_scale, actual_scale, -scale, scale);
  map(&g->y, -actual_scale, actual_scale, -scale, scale);
  map(&g->z, -actual_scale, actual_scale, -scale, scale);

}

//average of an array
void dynamic_average(double * arr, int size, double * sum){

  for(int i = 0; i < size; i++){
    *sum += arr[i];
  }
  *sum /= size;

}

//shift an array from right to left
void shift_array(double * arr, int size, double data){

  for(int i = 1; i < size; i++){
    arr[i-1] = arr[i];
  }
  arr[size-1] = data;

}

//d_time is expressed in microseconds
void delay(int d_time){
  d_time += clock();
  while(d_time > clock());
}

//read one line from the file
void get_line(){

  //I choose that the line can't be more than 100 characters long
  //Change it if you need to
  for(int i = 0; i < 100; i++){
    buffer[i] = fgetc(fil);
    //The end of the line is "\n" so if if finds that character breaks the loop
    if(buffer[i] == '\n'){
      break;
    }

    //I used this character to let the program know that the file is finished
    if(buffer[i] == '/'){
      fclose(fil);
      printf("\n\nSimulation terminated\r\n\n\n");
      exit(1);
    }
  }
}

//convert a char into a float
double get_number(char * data, int start, double * num){

  char number[100];
  int index = 0;

  //because I set that a line of the file can't be longer than 100 characters, also this loop can't do more iterations
  for(int i = start; i < 100; i++){
    //I used the tab separator to divide the different data
    if(data[i] != '\t'){
      number[index] = data[i];
      //clear the character just read
      data[i] = ' ';
      index ++;
    }
    else{
      //clear also the "/t" character
      data[i] = ' ';
      break;
    }
  }

  //atof function separates the unit from the decimals with a point so remember to use that instead a comma when you save data in the file
  *num = atof(number);
  //returns the index of the last character read so the next time this function is
  //called you could pass that index to it to start looking for numbers from the index passed
  return index;

}
//4.000	0.05923255	4486715.000	78453684.000	0.04394739	-0.2514147	-0.08496263
//time   accx       accy        accz          gyrox       gyroy       gyroz
void get_data(gyro_accel_stc * a, gyro_accel_stc * g, char * data){

  int start_index = 0;
  int tim = 0;

  //read one line from the file
  get_line();

  tim = timestamp;
  //read the timestamp
  start_index = get_number(data, start_index, &timestamp);

  //dt = abs(timestamp - tim);
  dt = 10;

  //read all the data from the line
  start_index = get_number(data, start_index, &a->x);
  start_index = get_number(data, start_index, &a->y);
  start_index = get_number(data, start_index, &a->z);
  start_index = get_number(data, start_index, &g->x);
  start_index = get_number(data, start_index, &g->y);
  start_index = get_number(data, start_index, &g->z);

}
