
UNTAR = tar -xvf
CONFIG = ./configure

LUSB_TB = libusb-1.0.9.tar.bz2
LUSB_DIR = libusb-1.0.9

LUSBC_TB = libusb-compat-0.1.4.tar.bz2
LUSBC_DIR = libusb-compat-0.1.4

LHID_TB = libhid-0.2.16.tar.gz
LHID_DIR = libhid-0.2.16

OVR_DIR = override

all: libusb libusb-compat libhid

libusb:
	$(UNTAR) $(LUSB_TB)
	cd $(LUSB_DIR); $(CONFIG); cd ..;
	$(MAKE) -C $(LUSB_DIR)
	sudo $(MAKE) install -C $(LUSB_DIR)

libusb-compat:
	$(UNTAR) $(LUSBC_TB)
	cd $(LUSBC_DIR); $(CONFIG); cd ..;
	$(MAKE) -C $(LUSBC_DIR)
	sudo $(MAKE) install -C $(LUSBC_DIR)

libhid:
	$(UNTAR) $(LHID_TB)
	cp $(OVR_DIR)/lshid.c $(LHID_DIR)/test/
	cd $(LHID_DIR); $(CONFIG); cd ..;
	sudo $(MAKE) install -C $(LHID_DIR)

clean:
	rm -rf $(LUSB_DIR) $(LUSBC_DIR) $(LHID_DIR)

