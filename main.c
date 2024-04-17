#include "ultrasonic.h"
#include "camera.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    // Initialize both the ultrasonic sensor and the camera
    ultrasonic_init(TRIGGER_PIN, ECHO_PIN); // Assuming you have constants defined for these pins
    init_camera();                          // Initialize the camera

    while (1)
    {
        // Get distance from the ultrasonic sensor
        float distance = ultrasonic_get_distance();
        printf("Distance: %.2f cm\n", distance);

        // Function to check the camera (capture an image or check camera status)
        int camera_status = capture_image(); // Assumes this function returns a status code
        if (camera_status == 0)
        {
            printf("Image captured successfully\n");
        }
        else
        {
            printf("Failed to capture image\n");
        }

        // Delay for one second before next measurement
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1000 milliseconds delay
    }
}
