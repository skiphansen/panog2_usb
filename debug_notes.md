# Detailed Debug notes

## Status

Currently usbhw_reset() wakes up the root hub successfully and Start of
Frame (SOP) packets are generated.  Sometime they are valid sometime they
are not (see below).

After usbhw_reset() usb_configure_device() is called to configure the root hub, 
but it never returns.

** MORE TO COME ... STAY TUNED TO THIS CHANNEL !**

