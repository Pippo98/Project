#ifndef __MAIN_H__
#define __MAIN_H__

int dt; //100 microseconds between two samples
double timestamp;
char buffer[100000];
char * pointer;

typedef struct{

  double x;
  double y;
  double z;

  double x_offset;
  double y_offset;
  double z_offset;

  double x_past[100];
  double y_past[100];
  double z_past[100];

  double sensitivity;

  double past_size;

}gyro_accel_stc;

typedef struct{

  double pitch;
  double roll;

  double accel_pitch;
  double accel_roll;

  double force;

  double PI;

}angles_data_stc;

void get_angle(gyro_accel_stc *, gyro_accel_stc *, angles_data_stc *);
void get_offset(gyro_accel_stc *, gyro_accel_stc *);
void get_gyro(gyro_accel_stc *);
void get_accel(gyro_accel_stc *);
void map(double *, double, double, double, double);
void map_accel(gyro_accel_stc *, int);
void map_gyro(gyro_accel_stc *, int);
void dynamic_average(double *, int, double *);
void shift_array(double *, int, double);
void delay(int);
void get_line();
double get_number(char *, int , double *);
void get_data(gyro_accel_stc *, gyro_accel_stc *, char *);


#endif
