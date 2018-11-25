#include "stdlib.h"
#include "stdio.h"
#include <math.h>
#include "time.h"
#include "main.h"

//data between 32767 -32768
int counter = 0;

FILE *fil;

int main(){

  gyro_accel_stc gyro;
  gyro_accel_stc accel;
  angles_data_stc angle;

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
  //get_offset(&accel, &gyro);

  fil = fopen("log.txt", "r");


  while(1){

    //get_accel(&accel);
    //get_gyro(&gyro);
    pointer = buffer;
    get_data(&accel, &gyro, buffer);

    //map_accel(&accel, 100);
    //map_gyro(&gyro, 100);

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

    get_angle(&accel, &gyro, &angle);

    //printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\r\n", timestamp, accel.x, accel.y, accel.z, gyro.x, gyro.y, gyro.z);
    printf("%f\t%f\t%f\r\n", angle.pitch, angle.roll, angle.force);
    //printf("%d\r\n", dt);

    delay(dt + 10000);

    counter ++;
  }

  return 0;

}

void get_angle(gyro_accel_stc * a, gyro_accel_stc * g, angles_data_stc * angle){

  angle->pitch += (g->x / g->sensitivity)*dt;
  angle->roll  -= (g->y / g->sensitivity)*dt;

  angle->force = abs(a->x * 1000000000) +
                 abs(a->y * 1000000000) +
                 abs(a->z * 1000000000);
  angle->force /= 1000000000;

  angle->accel_pitch = atan2(a->y, a->z) * 180 / angle->PI;
  angle->accel_roll  = atan2(a->x, a->z) * 180 / angle->PI;

  angle->pitch = angle->pitch * 0.98 + angle->accel_pitch * 0.02;
  angle->roll  = angle->roll  * 0.98 + angle->accel_roll  * 0.02;

}

void get_offset(gyro_accel_stc * a, gyro_accel_stc * g){

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

  dynamic_average(a->x_past, a->past_size, &a->x_offset);
  dynamic_average(a->y_past, a->past_size, &a->y_offset);
  dynamic_average(a->z_past, a->past_size, &a->z_offset);
  dynamic_average(g->x_past, a->past_size, &g->x_offset);
  dynamic_average(g->y_past, a->past_size, &g->y_offset);
  dynamic_average(g->z_past, a->past_size, &g->z_offset);

}

void get_gyro(gyro_accel_stc * g){

  g->x = (rand() % 201) - 100;
  g->y = (rand() % 201) - 100;
  g->z = (rand() % 201) - 100;

  g->x -= g->x_offset;
  g->y -= g->y_offset;
  g->z -= g->z_offset;

}

void get_accel(gyro_accel_stc * a){

  a->x = (rand() % 201)- 100;
  a->y = (rand() % 201) - 100;
  a->z = (rand() % 201) + 8800;

  a->x -= a->x_offset;
  a->y -= a->y_offset;
  a->z -= a->z_offset;

}

void map(double * var, double min, double max, double n_min, double n_max){

  double range, n_range;
  range = max - min;
  n_range = n_max - n_min;

  *var = ((*var - min) * n_range) / range;
  *var += n_min;

}

void map_accel(gyro_accel_stc * a, int scale){

  map(&a->x, -32767, 32678, -scale, scale);
  map(&a->y, -32767, 32678, -scale, scale);
  map(&a->z, -32767, 32678, -scale, scale);

}


void map_gyro(gyro_accel_stc * g, int scale){

  map(&g->x, -32767, 32678, -scale, scale);
  map(&g->y, -32767, 32678, -scale, scale);
  map(&g->z, -32767, 32678, -scale, scale);

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

void delay(int d_time){
  d_time += clock();
  while(d_time > clock());
}

//read one line from the file
void get_line(){

  for(int i = 0; i < 100; i++){
    buffer[i] = fgetc(fil);
    if(buffer[i] == '\n'){
      break;
    }

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

  for(int i = start; i < 100; i++){
    if(data[i] != '\t'){
      number[index] = data[i];
      data[i] = ' ';
      index ++;
    }
    else{
      data[i] = ' ';
      break;
    }
  }

  *num = atof(number);
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






















































//
