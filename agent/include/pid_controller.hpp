/**
 * @file pid_controller.hpp
 * @brief Basic PID controller class
 *
 * Simple discrete PID controller with configurable gains, sample time,
 * output limits, and anti-windup via integral clamping.
 */

#pragma once

class PIDController {
public:
    /**
     * @brief Construct a new PIDController object
     * @param[in] kp Proportional gain
     * @param[in] ki Integral gain
     * @param[in] kd Derivative gain
     * @param[in] dt Sample time in seconds
     * @return void
     */
    PIDController(double kp = 1.0, double ki = 0.0, double kd = 0.0, double dt = 0.01);

    /**
     * @brief Reset internal state (integral and previous error)
     * @return void
     */
    void reset();

    /**
     * @brief Compute controller output for given setpoint and measurement
     * @param[in] setpoint Desired value
     * @param[in] measurement Current measured value
     * @return double The control output
     */
    double compute(double setpoint, double measurement);

    /**
     * @brief Set output limits for the controller
     * @param[in] out_min Minimum allowable output
     * @param[in] out_max Maximum allowable output
     * @return void
     */
    void set_output_limits(double out_min, double out_max);

    /**
     * @brief Update PID tunings
     * @param[in] kp Proportional gain
     * @param[in] ki Integral gain
     * @param[in] kd Derivative gain
     * @return void
     */
    void set_tunings(double kp, double ki, double kd);

    /**
     * @brief Set the controller sample time
     * @param[in] dt Sample time in seconds
     * @return void
     */
    void set_sample_time(double dt);

private:
    double kp;
    double ki;
    double kd;
    double dt;
    double prev_error;
    double integral;
    double out_min;
    double out_max;
};
