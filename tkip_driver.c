#include <string.h>
#include <stdio.h>
#include "crypto.h"

/*
 * Takes chars representing data in hex 
 * and converts it to bytes.
 */
unsigned char *hex2string(char *hex, int len)
{
    unsigned char *string = (char*)malloc(sizeof(char) * (len/2));
    char *substring = (char*)malloc(sizeof(char) * 2);
    int index = 0;

    int i;
    for (i = 0; i < len; i+=2) {
        
        strncpy(substring, hex+i, 2);
        int x = strtol(substring, NULL, 16);
        string[index] = (char)x;
        index++;
    }
    
    free(substring);
    return string;
}

void dump_formatted_hex(unsigned char *data, int len)
{
    int i;
    for (i = 1; i < len; i++) {
        
        if ((i % 16) == 0)
            printf("%02x\n", data[i-1]);
        else if ((i % 8) == 0)
            printf("%02X ", data[i-1]);
        else
            printf("%02X:", data[i-1]);
    }
    printf("%02X\n", data[len-1]);
}

int main(int argc, char *argv[])
{
    if (argc != 5) {
        printf("Usage: tkip_driver <tk_file> <packet_file>"); 
        printf(" <length> <target length>\n");
        return 0;
    }

    int len = atoi(argv[3]);
    int targ_len = atoi(argv[4]);
    FILE *fp1 = fopen(argv[1], "r");
    char tk_hex[33];
    fgets(tk_hex, 33, (FILE*)fp1);
    fclose(fp1);

    printf("TK: %s\n\n", tk_hex);

    int str_len = (len * 2) + 1;
    FILE *fp2 = fopen(argv[2], "r");
    char *packet = 
        (char*)malloc(sizeof(char) * str_len);
    fgets(packet, str_len, (FILE*)fp2);
    fclose(fp2);

    printf("Packet Data: %s\n\n", packet);  
    
    unsigned char *tk_ascii = hex2string(tk_hex, 33);
    unsigned char *packet_ascii = hex2string(packet, str_len);
    unsigned char rc4key[16];

    // Calculate the ppk
    calc_tkip_ppk(packet_ascii, len, tk_ascii, rc4key);
    
    // Print the ppk
    printf("Per Packet Key:\n");
    dump_formatted_hex(rc4key, 16);
    printf("\n");

    printf("Before decrypt:\n");
    dump_formatted_hex(packet_ascii, len);
    printf("\n");

    //encrypt_wep(packet_ascii+z+8, len-z-8, rc4key, 16);

    //printf("After encrypt: \n");
    //for(i = 0; i < len; i++)
       // printf("%02X:", packet_ascii[i]);
    //printf("\n");
    
    // Decrypting
    decrypt_tkip(packet_ascii, len, tk_ascii);
    printf("After decrypt:\n");
    dump_formatted_hex(packet_ascii+34, targ_len);

    // clean up
    free(packet_ascii);
    free(tk_ascii); 
    free(packet);
    
    return 0;    
}

