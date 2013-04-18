
SRC_DIR=src
TEST_DIR=test
LIBS_DIR=libs

all: install test

.PHONY: src libs install uninstall test clean

src:
	$(MAKE) -C $(SRC_DIR)

libs:
	$(MAKE) -C $(LIBS_DIR)

install:
	$(MAKE) -C $(SRC_DIR) install

uninstall:
	$(MAKE) -C $(SRC_DIR) uninstall

test:
	$(MAKE) -C $(TEST_DIR)

clean:
	$(MAKE) -C $(SRC_DIR) clean
	$(MAKE) -C $(TEST_DIR) clean
	$(MAKE) -C $(LIBS_DIR) clean
