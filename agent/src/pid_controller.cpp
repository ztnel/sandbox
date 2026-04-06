/**
 * @file pid_controller.cpp
 * @brief Implementation of PIDController
 *
 * Implements a simple discrete PID controller.
 */

#include "pid_controller.hpp"

PIDController::PIDController(double kp, double ki, double kd, double dt)
    : kp(kp),
      ki(ki),
      kd(kd),
      dt(dt),
      prev_error(0.0),
      integral(0.0),
      out_min(-1e9),
      out_max(1e9)
{
}

void PIDController::reset()
{
    this->prev_error = 0.0;
    this->integral = 0.0;
}

static double clamp_val(double v, double lo, double hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

double PIDController::compute(double setpoint, double measurement)
{
    double error = setpoint - measurement;
    double p_term = this->kp * error;

    // update integral (accumulate error)
    this->integral += error * this->dt;

    // derivative (difference)
    double d_term = 0.0;
    if (this->dt > 0.0) {
        d_term = this->kd * (error - this->prev_error) / this->dt;
    }

    // compute integral term
    double i_term = this->ki * this->integral;

    // compute raw output
    double output = p_term + i_term + d_term;

    // clamp output to limits
    double clamped = clamp_val(output, this->out_min, this->out_max);

    // anti-windup: if output was clamped and ki != 0, adjust integral to match clamped output
    if (this->ki != 0.0 && clamped != output) {
        double desired_i = clamped - p_term - d_term;
        this->integral = desired_i / this->ki;
        i_term = this->ki * this->integral;
        output = p_term + i_term + d_term;
    } else {
        output = clamped;
    }

    this->prev_error = error;
    return output;
}

void PIDController::set_output_limits(double out_min, double out_max)
{
    if (out_max < out_min) {
        double tmp = out_min;
        out_min = out_max;
        out_max = tmp;
    }
    this->out_min = out_min;
    this->out_max = out_max;

    if (this->ki != 0.0) {
        double i_term = this->ki * this->integral;
        if (i_term > this->out_max) this->integral = this->out_max / this->ki;
        else if (i_term < this->out_min) this->integral = this->out_min / this->ki;
    }
}

void PIDController::set_tunings(double kp, double ki, double kd)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}

void PIDController::set_sample_time(double dt)
{
    if (dt <= 0.0) return;
    this->dt = dt;
}
