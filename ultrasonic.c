#include "ultrasonic.h"
#include <sys/time.h> // For time measurement
#include <unistd.h>   // For usleep
#include "driver/gpio.h"

// Global variables to store pin numbers
static int trigger_pin;
static int echo_pin;

// Function to initialize the GPIO pins
void ultrasonic_init(int trg_pin, int ech_pin)
{
    trigger_pin = trg_pin;
    echo_pin = ech_pin;

    // Setup the GPIO pin directions
    gpio_set_direction(trigger_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(echo_pin, GPIO_MODE_INPUT);
}

// Function to get the distance from the ultrasonic sensor
float ultrasonic_get_distance(void)
{
    // Ensure trigger pin is LOW for a few microseconds
    gpio_set_level(trigger_pin, 0);
    usleep(2); // Sleep for 2 microseconds

    // Trigger the sensor by setting the trigger pin HIGH for at least 10 microseconds
    gpio_set_level(trigger_pin, 1);
    usleep(10);
    gpio_set_level(trigger_pin, 0);

    // Wait for echo pin to go high
    while (gpio_get_level(echo_pin) == 0)
        ;

    // Record the time when the echo pin goes high
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Wait for echo pin to go low
    while (gpio_get_level(echo_pin) == 1)
        ;

    gettimeofday(&end, NULL);

    // Calculate the difference in time from start to end
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    // Calculate distance in centimeters (speed of sound is approximately 343 meters per second)
    float distance = (elapsed * 34300) / 2;

    return distance;
