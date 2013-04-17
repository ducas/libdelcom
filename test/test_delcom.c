// Requires libhid (http://libhid.alioth.debian.org/)
#include <hid.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <delcom.h>

int main (argc, argv)
    int argc;
    char **argv; {

    // First, grab the user's options.
    static int blue_flag;
    static int get_flag;
    static int green_flag;
    static int help_flag;
    static int off_flag;
    static int red_flag;

    int c;
    while (1) {
        static struct option long_options[] = {
            // These options set a flag.
            {"blue",  no_argument,  &blue_flag,  1},
            {"get",   no_argument,  &get_flag,   1},
            {"green", no_argument,  &green_flag, 1},
            {"help",  no_argument,  &help_flag,  1},
            {"off",   no_argument,  &off_flag,   1},
            {"red",   no_argument,  &red_flag,   1},
        };

        int option_index = 0;
        c = getopt_long(argc, argv, "", long_options, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 0:
                if (long_options[option_index].flag != 0)
                    break;
        }
    }

    // Print usage if the user didn't supply a valid option or asked for help.
    if (
        (! blue_flag && ! red_flag && ! green_flag && ! off_flag && ! get_flag)
        || help_flag
    ) {
        printf(
            "Usage: %s [ --blue | --red | --green | --off | --get ]\n",
            argv[0]
        );

        exit(1);
    }

    int ret;
    ret = delcom_OpenDevice();
    if (ret != 0) return ret;

    if (get_flag) {
        ret = delcom_GetColor();
        printf("Got color %d\n", ret);
    }

    if (blue_flag || red_flag || green_flag || off_flag) {
        int color = 0;
        if (blue_flag)
            color |= DELCOM_COLOR_BLUE;
        if (red_flag)
            color |= DELCOM_COLOR_RED;
        if (green_flag)
            color |= DELCOM_COLOR_GREEN;
        
        if (off_flag)
            color = DELCOM_COLOR_OFF;

        printf("Setting color to %d\n", color);

        ret = delcom_SetColor(color);

        if (ret != 0) return ret;
    }
    ret = delcom_CloseDevice();

    return ret;
}
