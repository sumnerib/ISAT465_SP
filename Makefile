default: tkip_driver

tkip_driver: tkip_driver.c crypto.o
	gcc crypto.o tkip_driver.c -lssl -lcrypto -o tkip_driver

clean:
	rm -f tkip_driver
