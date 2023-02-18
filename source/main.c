// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

// Main program entrypoint
int main(int argc, char* argv[])
{
    HidVibrationDeviceHandle VibrationDeviceHandles[2];
    Result rc = 0, rc2 = 0;

    HidVibrationValue VibrationValue;
    HidVibrationValue VibrationValue_stop;
    HidVibrationValue VibrationValues[2];

    // This example uses a text console, as a simple way to output text to the screen.
    // If you want to write a software-rendered graphics application,
    //   take a look at the graphics/simplegfx example, which uses the libnx Framebuffer API instead.
    // If on the other hand you want to write an OpenGL based application,
    //   take a look at the graphics/opengl set of examples, which uses EGL instead.
    consoleInit(NULL);

    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    PadState pad;
    padInitializeDefault(&pad);

    // Other initialization goes here. As a demonstration, we print hello world.

    printf("\n");
    printf("\n  JoyBrator v1.0");
    printf("\n  (c)2023 oscie57, UntitledOutput, shadowninja108");
    printf("\n\n");
    printf("\n  DISCLAIMER: To avoid injury or aggravation of pre-existing conditions,");
    printf("\n  the vibrating remote should not be used on swollen or inflamed areas or");
    printf("\n  skin lacerations. No medical claims are warranted or implied by the use");
    printf("\n  of this software. Vibrating your remote for a long period of time may");
    printf("\n  (and probably will) damage the motor. Please be careful and take breaks");
    printf("\n  breaks in between use to ensure safety of the HD rumble.");
    printf("\n\n\n\n");
    printf("\n  Supported/tested controllers: Joy-Con (HAC-016), Pro Controller (HAC-013)");
    printf("\n\n");
    printf("\n  Press 'A' to enable/disable rumble");
    printf("\n  Press 'B' to enable/disable pulse mode");
    printf("\n\n");
    printf("\n  Press '+' when you're done");
    printf("\n\n\n");
    printf("\n  PULSE COMING SOON!");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n  https://github.com/oscie57/JoyBrator");

    // Two VibrationDeviceHandles are returned: first one for left-joycon, second one for right-joycon.
    // Change the total_handles param to 1, and update the hidSendVibrationValues calls, if you only want 1 VibrationDeviceHandle.
    rc = hidInitializeVibrationDevices(VibrationDeviceHandles, 2, HidNpadIdType_No1, HidNpadStyleTag_NpadJoyDual);

    // Setup VibrationDeviceHandles for HidNpadIdType_No1 too, since we want to support both HidNpadIdType_Handheld and HidNpadIdType_No1.

    VibrationValue.amp_low   = 1.0f;
    VibrationValue.freq_low  = 10.0f;
    VibrationValue.amp_high  = 1.0f;
    VibrationValue.freq_high = 10.0f;

    memset(VibrationValues, 0, sizeof(VibrationValues));

    memset(&VibrationValue_stop, 0, sizeof(HidVibrationValue));
    // Switch like stop behavior with muted band channels and frequencies set to default.
    VibrationValue_stop.freq_low  = 160.0f;
    VibrationValue_stop.freq_high = 320.0f;

    bool rumbling = false;

    // Main loop
    while (appletMainLoop())
    {
        // Scan the gamepad. This should be done once for each frame
        padUpdate(&pad);

        // padGetButtonsDown returns the set of buttons that have been
        // newly pressed in this frame compared to the previous one
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus) {
            break; // break in order to return to hbmenu
        };

        if (R_SUCCEEDED(rc) && (kDown & HidNpadButton_A)) {

            if ( rumbling ) {

                rumbling = false;

                memcpy(&VibrationValues[0], &VibrationValue_stop, sizeof(HidVibrationValue));
                memcpy(&VibrationValues[1], &VibrationValue_stop, sizeof(HidVibrationValue));

                rc2 = hidSendVibrationValues(VibrationDeviceHandles, VibrationValues, 2);

                //Could also do this with 1 hidSendVibrationValues() call + a larger VibrationValues array.
                rc2 = hidSendVibrationValues(VibrationDeviceHandles, VibrationValues, 2);

            } else {

                rumbling = true;

                //Calling hidSendVibrationValue/hidSendVibrationValues is really only needed when sending new VibrationValue(s).
                //If you just want to vibrate 1 device, you can also use hidSendVibrationValue.

                memcpy(&VibrationValues[0], &VibrationValue, sizeof(HidVibrationValue));
                memcpy(&VibrationValues[1], &VibrationValue, sizeof(HidVibrationValue));
                
                rc2 = hidSendVibrationValues(VibrationDeviceHandles, VibrationValues, 2);
                if (R_FAILED(rc2)) printf("hidSendVibrationValues() returned: 0x%x\n", rc2);

            };
        };

        if (kDown & HidNpadButton_B) {
            // Add pulse later
        };
        
        // Your code goes here

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
