
#include "pid.h"

#include <stdio.h>

typedef struct pid_mem_t {
  float integrator;
  float differentiator;
  float error;
  float measurement;
  float stimulus;  // output stimulus
} pid_mem_t;

static struct pid_mem_t pid_mem;

static void log_pid(float setpoint, float measurement, float proportional) {
  printf("PID | %.5f\t%.5f\t%.5f\t%.5f\t%.5f\t%.5f\r\n", setpoint, measurement,
         pid_mem.stimulus, proportional, pid_mem.integrator,
         pid_mem.differentiator);
}

pid_err_t pid_init() {
  pid_mem.differentiator = 0.0;
  pid_mem.error = 0.0;
  pid_mem.integrator = 0.0;
  pid_mem.measurement = 0.0;
  pid_mem.stimulus = 0.0;
  log_pid(0.0, 0.0, 0.0);
  return PID_SUCCESS;
}
pid_err_t pid_update(pid_ctl_t *pid, float setpoint, float measurement,
                     float *stimulus) {
  float error = setpoint - measurement;
  float proportional = pid->kp * error;
  // integration branch
  pid_mem.integrator =
      pid_mem.integrator + 0.5f * pid->ki * pid->t * (error + pid_mem.error);
  // anti-windup
  if (pid_mem.integrator > pid->int_max) {
    pid_mem.integrator = pid->int_max;
  } else if (pid_mem.integrator < pid->int_min) {
    pid_mem.integrator = pid->int_min;
  }

  // derivitive output branch
  pid_mem.differentiator =
      -(2.0f * pid->kd * (measurement - pid_mem.measurement) +
        (2.0f * pid->tau - pid->t) * pid_mem.differentiator) /
      (2.0f * pid->tau + pid->t);

  // output and clamping
  pid_mem.stimulus = proportional + pid_mem.integrator + pid_mem.differentiator;
  if (pid_mem.stimulus > pid->out_max) {
    pid_mem.stimulus = pid->out_max;
  } else if (pid_mem.stimulus < pid->out_min) {
    pid_mem.stimulus = pid->out_min;
  }
  *stimulus = pid_mem.stimulus;
  log_pid(setpoint, measurement, proportional);
  pid_mem.error = error;
  pid_mem.measurement = measurement;
  return PID_SUCCESS;
}