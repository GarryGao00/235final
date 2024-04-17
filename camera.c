#include "esp_camera.h"
#include "camera.h"

// Configuration settings for the camera
static camera_config_t camera_config = {
    .pin_pwdn = -1,         // power down is not used
    .pin_reset = RESET_PIN, // reset pin
    .pin_xclk = XCLK_PIN,
    .pin_sscb_sda = SIOD_PIN,
    .pin_sscb_scl = SIOC_PIN,

    .pin_d7 = Y9_PIN,
    .pin_d6 = Y8_PIN,
    .pin_d5 = Y7_PIN,
    .pin_d4 = Y6_PIN,
    .pin_d3 = Y5_PIN,
    .pin_d2 = Y4_PIN,
    .pin_d1 = Y3_PIN,
    .pin_d0 = Y2_PIN,
    .pin_vsync = VSYNC_PIN,
    .pin_href = HREF_PIN,
    .pin_pclk = PCLK_PIN,

    .xclk_freq_hz = 20000000, // 20MHz XCLK frequency
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG, // YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_UXGA,   // UXGA-QXGA(2048x1536)
    .jpeg_quality = 10,             // Quality of JPEG output. 0-63 lower means higher quality
    .fb_count = 1,                  // Number of frame buffers to be allocated. If more than one, then each frame will be available.
};

void init_camera(void)
{
    // Initialize the camera with the configuration
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK)
    {
        printf("Camera Init Failed\n");
        return;
    }
    printf("Camera Init Success\n");
}

int capture_image(void)
{
    // Capture a picture
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb)
    {
        printf("Camera Capture Failed\n");
        return -1;
    }

    // Use the frame buffer data
    printf("Captured an image with size %d bytes\n", fb->len);

    // The image can be processed here or sent over the network

    // Return the frame buffer once done
    esp_camera_fb_return(fb);
    return 0; // Success
}
