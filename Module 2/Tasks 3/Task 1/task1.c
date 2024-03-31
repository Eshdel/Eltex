#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

void convertStringPermissionsToMask(char * permissions, char * result) {
    unsigned short mask = 0;

    for(int i = 0; i < strlen(permissions); ++i) {
        switch (permissions[i])
        {
            case 'r':
            case 'R':
            case 'w':
            case 'W':
            case 'x':
            case 'X':
                mask |= (1 << (8 - i));
                result[i] = '1';
                break;
            case '-':
                result[i] = '0';
                break;
            default:
                printf("Invalid input argument in access rights");
                exit(666);
        }
    }

    return mask;
}

void convertNumbersPermissionsToMask(char *octalNumber, char *binaryNumber) {
    int i = 0, j = 0;

    while (octalNumber[i]) {
        char octalDigit = octalNumber[i];
        if (octalDigit < '0' || octalDigit > '7') {
            printf("Incorrect entry of an octal number\n");
            return;
        }
        int octal = octalDigit - '0'; 
        for (int k = 2; k >= 0; k--) {
            binaryNumber[j++] = (octal & (1 << k)) ? '1' : '0';
        }
        i++;
    }

    binaryNumber[j] = '\0';
}


void printPermissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");

    // User access permission
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    
    // Group access permisson
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
   
    // Other users access permission
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");

    printf("\n");
    int _mode = mode & 0777;
    printf("Numbers presentaion right access: %o\n", _mode);
}

void setMod(mode_t mode, char * X,char Y,char * Z) {
    for (int i = 0; i < strlen(X); i++) {
        tmpSetMode(mode,X[i],Y,Z);
    }

    printPermissions(mode);
}

void tmpSetMode(mode_t * mode,char X,char Y, char * Z) {
    const int maxPos = 8;
    int pos;
    unsigned char byte = 0;

    switch (X)
    {
        case 'u':
            pos = maxPos - 0;
            break;
        case 'g':
            pos = maxPos - 3;
            break;
        case 'o':
            pos = maxPos - 6;

        case 'a':
            tmpSetMode(mode,'u',Y,Z);
            tmpSetMode(mode,'g',Y,Z);
            tmpSetMode(mode,'o',Y,Z);
        default:
            break;
    }

    for (int i = 0; i < strlen(Z);i++) {
        switch (Z[i])
        {
            unsigned char mask = 0;

            case 'r':
                byte |= mask << pos;
                break;  
            case 'w':
                byte |= mask << pos - 1;
                break;
            case 'x':
                byte |= mask << pos - 2;
                break;

            default:
                break;
        }
    }
    switch (Y)
    {
        case '+':
            *mode |= byte;
            return mode;
        case '-':
            *mode ^= *mode & byte;
            return mode;
        case '=':
            *mode &= *mode | byte;
            return mode;
        default:
            break;
    }

    printf("Error change mode");
    exit(666);
}

int main() {
    //For the task 1.1
    char permissions[10];
    char mask[10];
    
    //For the task 1.2
    struct stat fileData;
    char filePath[100];
    char permissions_2[10];
    char mask_2[10];
    
    //For the task 1.3
    char cmodAttributes[10];
  
    //Task 1.1

    printf("Enter permissions: ");
    scanf("%s", permissions);

    if(isdigit(permissions[0])) {
        convertNumbersPermissionsToMask(permissions,mask);
    }
    else {
        convertStringPermissionsToMask(permissions,mask);
    }
    printf("Mask: %s\n", mask);

    //Task 1.2

    printf("Enter path to file: ");
    scanf("%s", filePath);

    if(stat(filePath, &fileData) != 0) {
        perror("Error when retrieving file information");
        return 0;
    }

    printf("File access right %s: ", filePath);
    printPermissions(fileData.st_mode);
    
    snprintf(permissions_2, sizeof(permissions_2),"%o", fileData.st_mode & 0777);
    convertNumbersPermissionsToMask(permissions_2, mask_2);
    printf("Bits presentaion right access: %s\n", mask_2);
   
    //Task 1.3
    char * x = 'u';
    char y = '-';
    char * z = 'r';
    setMod(fileData.st_mode,x,y,z);

    return 1;
}