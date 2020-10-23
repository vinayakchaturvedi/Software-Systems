#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include"LoginStruct.c"

void loginHandler(int accountType, char db[30]){
    printf("\nPlease Enter the login details: \n\n");
    char userName[40], password[40];
    write(1, "UserName: ", sizeof("UserName: "));
    int uBytes = read(0, userName, sizeof(userName));
    write(1, "Password: ", sizeof("Password: "));
    int pBytes = read(0, password, sizeof(password));

    //Call the server for authentication
    int fd = open(db, O_RDONLY);
    struct Login record;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    fcntl(fd, F_SETLKW, &lock);
    int currBytes = read(fd, &record, sizeof(record));
    while(currBytes != 0){

        if(strncmp(record.userName, userName, uBytes - 1) == 0 && strncmp(record.password, password, pBytes - 1) == 0){
            printf("Logged-in successfully");
            //go to services page;
            close(fd);
            return;
        }
        currBytes = read(fd, &record, sizeof(record));
    }
    printf("Incorrect UserName/Password");
    close(fd);
    return;
}


int main(){


    int accountType;

    printf("\nPlease Enter the login details: \n\n");
    printf("Enter \"1\" for Administrator login \"2\" for Normal User login \"3\" for Joint Account holder login: ");
    scanf("%d", &accountType);

    int retry = 1;

    while(1){
        if(accountType == 1){
            loginHandler(1, "./db/admin_Login_DB");
            break;
        }
        else if(accountType == 2 || accountType == 3){
            loginHandler(2, "./db/user_login_DB");
            break;
        }
        else{
            if(retry == 3){
                printf("Terminating the connection after 3 unsuccessful retries\n");
                return -1;
            }
            printf("Invalid selection Please Enter valid number: ");
            scanf("%d", &accountType);
            retry++;
        }
    }

    printf("\n---------------------------Thanks for Visiting Hydra Bank------------------------------\n\n");

}