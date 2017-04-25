default: tkip_driver

tkip_driver: 
	gcc tkip_driver.c crypto.c -lssl -lcrypto -o tkip_driver

clean:
	rm -f tkip_driver
