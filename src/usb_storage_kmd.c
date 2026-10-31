#include "usb_storage.h"
#include <kmd/kmd.h>

static bool usb_storage_class_probe(usb_device_t *dev, const uint8_t *config, size_t len) {
    if (!usb_storage_probe(dev, config, len))
        return false;
    usb_storage_automount();
    return true;
}

static const usb_class_t usb_storage_class = {
    .name       = "usb storage",
    .probe      = usb_storage_class_probe,
    .disconnect = usb_storage_disconnect,
    .hotplug    = usb_storage_automount,
};

static int usb_storage_load(void) {
    return usb_class_register(&usb_storage_class);
}

KMD_DRIVER(usb_storage_kmd) = {
    .description = "USB mass storage (bulk only SCSI)",
    .load        = usb_storage_load,
};
