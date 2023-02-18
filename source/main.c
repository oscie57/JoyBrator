// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

// Main program entrypoint
int main(int argc, char* argv[])
{
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
    printf("\n  (c)2023 oscie57, UntitledOutput");

    printf("\n\n");

    printf("\n  DISCLAIMER: To avoid injury or aggravation of pre-existing conditions,");
    printf("\n  the vibrating remote should not be used on swollen or inflamed areas or");
    printf("\n  skin lacerations. No medical claims are warranted or implied by the use");
    printf("\n  of this software. Exessive use of your vibrating remote will wear out");
    printf("\n  the motor.");

    printf("\n\n\n\n");

    printf("\n  Supported controllers: Joy-Con (HAC-016)");

    printf("\n\n");

    printf("\n  Press 'A' to enable/disable rumble");
    printf("\n  Press 'B' to enable/disable pulse mode");
    printf("\n  Press '+' to toggle the LED");

    printf("\n\n");

    printf("\n  Press 'Home' when you're done");

    printf("\n\n\n");

    printf("\n  PULSE COMING SOON!");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");

    printf("\n  https://github.com/oscie57/JoyBrator");

    // Main loop
    while (appletMainLoop())
    {
        // Scan the gamepad. This should be done once for each frame
        padUpdate(&pad);

        // padGetButtonsDown returns the set of buttons that have been
        // newly pressed in this frame compared to the previous one
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus)
            break; // break in order to return to hbmenu

        // Your code goes here

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}
