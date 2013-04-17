// Requires libhid (http://libhid.alioth.debian.org/)
#include <hid.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define DELCOM_COLOR_GREEN 0x01
#define DELCOM_COLOR_RED 0x02
#define DELCOM_COLOR_BLUE 0x04
#define DELCOM_COLOR_OFF 0x00

// Set up the libhid interface.
HIDInterface* hid;
int iface_num = 0;
hid_return ret;

// These are for a delcom gen 2 usb light. YMMV.
unsigned short vendor_id  = 0x0fc5;
unsigned short product_id = 0xb080;

int delcom_OpenDevice() {

    HIDInterfaceMatcher matcher = { vendor_id, product_id, NULL, NULL, 0 };

    ret = hid_init();
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_init failed with return code %x\n", ret);
        return 1;
    }

    hid = hid_new_HIDInterface();
    if (hid == 0) {
        fprintf(stderr, "hid_new_HIDInterface() failed, out of memory?\n");
        return 1;
    }

    ret = hid_force_open(hid, iface_num, &matcher, 3);
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_force_open failed with return code %d\n", ret);
        return 1;
    }

    return 0;
}

unsigned int delcom_GetColor() {

    // Path to the LEDs
    int path[2];
    path[0] = 0xff000000;
    path[1] = 0x00000000;

    char* buf = malloc(8);
    unsigned int color;

    buf[0] = 100;
    hid_get_feature_report(hid, path, 1, buf, 8);

    if (ret != HID_RET_SUCCESS) {
       fprintf(stderr, "hid_get_feature_report failed()\n");
       return -1;
    }

    color = ~buf[2];
    
    free(buf);

    return color;
}

int delcom_SetColor(unsigned int color) {

    // Path to the LEDs
    int path[2];
    path[0] = 0xff000000;
    path[1] = 0x00000000;

    char* buf = malloc(8);

    // We are doing an 8 byte write feature to set the active LED.
    buf[0] = 101;
    buf[1] = 12;
    //buf[2] = color;
    buf[3] = 0xFF;

    // buf[2] is the LSB, buf[3] is the MSB
    if (color == DELCOM_COLOR_GREEN)
        buf[2] = 0x01<<0;
    else if (color == DELCOM_COLOR_RED)
        buf[2] = 0x01<<1;
    else if (color == DELCOM_COLOR_BLUE)
        buf[2] = 0x01<<2;
    else if (color == DELCOM_COLOR_OFF)
        buf[2] = 0x00;
    
    hid_set_feature_report(hid, path, 1, buf, 8);
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_set_feature_report failed()\n");
        return 1;
    }

    free(buf);

    return 0;
}

int delcom_CloseDevice() {
    ret = hid_close(hid);
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_close failed with return code %d\n", ret);
        return 1;
    }

    hid_delete_HIDInterface(&hid);

    ret = hid_cleanup();
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_cleanup failed with return code %d\n", ret);
        return 1;
    }

    return 0;
}