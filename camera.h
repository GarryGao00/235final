#ifndef CAMERA_H
#define CAMERA_H

#include "esp_err.h"

// Function declarations for camera initialization and image capture
void init_camera(void);
int capture_image(void);

#endif // CAMERA_H
