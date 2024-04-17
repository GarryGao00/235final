#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h> // For standard integer types

// Function prototypes
void ultrasonic_init(int trigger_pin, int echo_pin);
float ultrasonic_get_distance(void);

#endif // ULTRASONIC_H
