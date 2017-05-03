# ISAT465_SP

## Usage ##
This is intended to decrypt a wireless frame encrypted using TKIP(WPA1).
Capture packets using a tool like Wireshark and copy the encrypted data
(including 802.11 header) into a .txt file as a hex stream. You must also
provide the Temporal Key (TK). This can be found with a tool like aircrack-ng,
or, if you know the password, you can decrypt the packets in Wireshark and it will 
show you the TK.

A working demo of this project can be found here: https://www.youtube.com/watch?v=1HyEQI6Jweo

## Disclaimer ##
This is intended for educational purposes only. The routines used for generating the ppk and decrypting 
are from the aircrack-ng repository. See "https://github.com/aircrack-ng/aircrack-ng". The file crypto.h
was copied from this repo and is not our intellectual property.
