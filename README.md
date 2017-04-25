# ISAT465_SP

## Usage ##
This is intended to decrypt a wireless frame encrypted using TKIP(WPA1).
Capture packets using a tool like Wireshark and copy the encrypted data
(including 802.11 header) into a .txt file as a hex stream. You must also
provide the Temporal Key (TK). This can be found with a tool like aircrack-ng,
or, if you know the password, you can decrypt the packets in Wireshark and it will 
show you the TK.
