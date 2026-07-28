#include "src/HeptaSat.h"

HeptaCdh    cdh;
HeptaEps    eps;
HeptaSensor sensor;

void setup() {
  cdh.begin();
  eps.init();
  sensor.begin();

  cdh.wait_for_serial();
  cdh.wait_for_sd();
  cdh.println("Hit any key to take a picture...");
}

void loop() {
  if (cdh.is_cmd_received()) {
    cdh.get_command(); // Ignore the command content, just wait for any key press

    // Default is VGA (640x480). Pass a size to override, e.g. ARDUCAM_JPEG_QVGA.
    // UXGA (1600x1200) produces large JPEGs and slower downloads.
    if (sensor.camera_snapshot("picture.jpg", ARDUCAM_JPEG_VGA)) {
      cdh.println("Picture saved successfully.");
    } else {
      cdh.println("Failed to save picture.");
    }
  }
}
