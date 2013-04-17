
SRC_DIR=src
TEST_DIR=test

all: install test

.PHONY: src install test clean

src:
	$(MAKE) -C $(SRC_DIR)

install:
	$(MAKE) -C $(SRC_DIR) install

uninstall:
	$(MAKE) -C $(SRC_DIR) uninstall

test:
	$(MAKE) -C $(TEST_DIR)

clean:
	$(MAKE) -C $(SRC_DIR) clean
	$(MAKE) -C $(TEST_DIR) clean
