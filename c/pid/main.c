#include <stdio.h>
#include <unistd.h>

#include "pid.h"

/* Controller parameters */
#define PID_KP 2.0f
#define PID_KI 0.5f
#define PID_KD 0.25f

#define PID_TAU 0.02f

#define PID_LIM_MIN -10.0f
#define PID_LIM_MAX 10.0f

#define PID_LIM_MIN_INT -5.0f
#define PID_LIM_MAX_INT 5.0f

#define SAMPLE_TIME_S 0.01f

/* Maximum run-time of simulation */
#define SIMULATION_TIME_MAX 20.0f

static float system_update(float inp) {
  static float output = 0.0f;
  static const float alpha = 0.02f;
  output = (SAMPLE_TIME_S * inp + output) / (1.0f + alpha * SAMPLE_TIME_S);
  return output;
}

int main(void) {
  /* Initialise PID controller */
  pid_ctl_t pid = {.kp = PID_KP,
                   .ki = PID_KI,
                   .kd = PID_KD,
                   .out_min = PID_LIM_MIN,
                   .out_max = PID_LIM_MAX,
                   .int_min = PID_LIM_MIN_INT,
                   .int_max = PID_LIM_MAX_INT,
                   .tau = PID_TAU,
                   .t = SAMPLE_TIME_S};

  pid_init();

  /* Simulate response using test system */
  float setpoint = 1.0f;
  float stimulus = 0.0f;
  float t = 0.0f;
  for (int i = 0; i <= 100000; i++) {
    t = i * SAMPLE_TIME_S;
    if (t >= SIMULATION_TIME_MAX) {
      break;
    }
    printf("%f ", t);
    /* Get measurement from system */
    float measurement = system_update(stimulus);
    /* Compute new control signal */
    pid_update(&pid, setpoint, measurement, &stimulus);
    if (i % 1000 == 0) {
      setpoint = -setpoint;
    }
    usleep(10000);
  }
  return 0;
}
