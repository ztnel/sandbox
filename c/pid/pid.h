#ifndef __PID_H__
#define __PID_H__

typedef struct pid_ctl_t {
  float kp;       // proportional gain
  float ki;       // integrator gain
  float kd;       // differentiator gain
  float out_min;  // output minimum
  float out_max;  // output maximum
  float int_min;  // integrator minimum
  float int_max;  // integrator maximum
  float tau;      // derivative LPF time constant
  float t;        // sample time
} pid_ctl_t;

typedef int pid_err_t;

#define PID_SUCCESS (pid_err_t)0
#define PID_ERR (pid_err_t)1

pid_err_t pid_init(void);
pid_err_t pid_update(pid_ctl_t *pid, float setpoint, float measurement,
                     float *stimulus);

#endif  // __PID_H__