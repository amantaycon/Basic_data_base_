#include "maha.h"
int main()
{
    FILE *fa;
    long long pass;
    int size = 11;
    char *protect = (char *)malloc(sizeof(char) * 51);
    char *file_name = (char *)malloc(sizeof(char) * 260);
    logo();
    printf("********************* Welcome TO Our Database Management System *********************\n\n");
    while (1)
    {
        printf(" 1. Creat new database\n 2. Open exist database\n");
        gets(protect);
        if (strcmp("exit", protect) == 0 || strcmp("back", protect) == 0)
        {
            exit(0);
        }
        if (strcmp(protect, "1") == 0)
        {
            puts(" *** Important instruction -> use the separate folder ***\n\n Enter name of database");
            while (1)
            {
                gets(file_name);
                if (strcmp("exit", file_name) == 0)
                {
                    exit(0);
                }
                if (strcmp("back", file_name) == 0)
                {
                    break;
                }
                puts(" ---> Set your password <--- ");
                gets(protect);
                if (strcmp("exit", protect) == 0)
                {
                    exit(0);
                }
                if (strcmp("back", protect) == 0)
                {
                    break;
                }
                if ((fa = fopen(file_name, "wb+")) == 0)
                {
                    puts("Error Please use the deferent name");
                    continue;
                }
                break;
            }
            if (fa == 0)
            {
                continue;
            }
            pass = password(protect, fa, 'a');
            fwrite(&size, sizeof(size), 1, fa);
            printf(" ---> your password is successfully added <--- \n");
            break;
        }
        else if (strcmp(protect, "2") == 0)
        {
            while (1)
            {
                puts(" Enter name of database");
                gets(file_name);
                if (strcmp("exit", file_name) == 0)
                {
                    exit(0);
                }
                printf(" ---> Enter Password <--- \n");
                gets(protect);
                if (strcmp("exit", protect) == 0)
                {
                    exit(0);
                }

                if ((fa = fopen(file_name, "rb+")) != 0)
                {
                    if (pass = password(protect, fa, 'c') != 0)
                    {
                        fread(&size, sizeof(size), 1, fa);
                        break;
                    }
                    else
                    {
                        printf(" ---> Wrong Password <--- \n");
                        fclose(fa);
                        continue;
                    }
                }
                else
                {
                    puts(" Your database is not exist\n");
                    break;
                }
            }
            if (fa == 0)
            {
                continue;
            }
            break;
        }
        else
        {
            puts("Enter wrong command");
        }
    }

    char *lname = (char *)malloc(sizeof(char) * size);
    while (1)
    {
        printf("\n\nEnter any Command \n 1. add_lable\n 2. add_data\n 3. find\n 4. show_all\n 5. delete_lable\n");
        char command[15];
        lname = (char *)realloc(lname, sizeof(char) * size);
        fflush(stdin);
        scanf("%s", command);
        int temp;
        if (strcmp("1", command) == 0 || strcmp("add_lable", command) == 0)
        {
            printf("your old size %d give me a new size and lable name\n", size - 1);
            scanf("%d", &size);
            fseek(fa, sizeof(pass), SEEK_SET);
            size++;
            fwrite(&size, sizeof(size), 1, fa);

            scanf("%s", lname);
            fflush(stdin);
            temp = lable(lname, fa, &pass, size);
            if (temp == 0)
            {
                printf(" ---> Successfully addad lable %s <--- \n", lname);
            }
            if (temp == -1)
            {
                printf(" ---> lable %s is already exists use the diffrent name <--- \n", lname);
            }
            if (temp == -2)
            {
                printf(" ---> lable %s not added use the diffrent name <--- \n", lname);
            }
            if (temp == -3)
            {
                printf(" ---> Some Error Occurred <--- \n");
            }
            fflush(stdin);
            continue;
        }

        else if (strcmp("2", command) == 0 || strcmp("add_data", command) == 0)
        {
            fflush(stdin);
            data(fa, pass);
            fflush(stdin);
            continue;
        }

        else if (strcmp("3", command) == 0 || strcmp("find", command) == 0)
        {
            find(fa);
            continue;
        }
        else if (strcmp("4", command) == 0 || strcmp("show_all", command) == 0)
        {
            show_all(fa);
            continue;
        }

        else if (strcmp("5", command) == 0 || strcmp("delete_lable", command) == 0)
        {
            scanf("%s", lname);
            printf("If you want to remove lable %s\n Enter any key for cancel(Enter y for continue)", lname);
            fflush(stdin);
            if (getchar() == 'y')
            {
                fclose(fa);
                delete2(file_name, lname);
                fa = fopen(file_name, "rb+");
            }
        }

        else if (strcmp("exit", command) == 0)
        {
            fclose(fa);
            exit(0);
        }

        else if (strcmp("cls", command) == 0)
        {
            system("cls");
            continue;
        }

        else if (strcmp("passw", command) == 0)
        {
            printf(" ---> Enter New Password <---\n");
            fflush(stdin);
            gets(protect);
            if (strcmp("exit", protect) == 0)
            {
                exit(0);
            }
            pass = password(protect, fa, 'a');
            printf(" ---> your password is successfully added <--- \n");
            continue;
        }

        else
        {
            printf("\n Error your command not valid\n");
        }
    }
    fclose(fa);
    return 0;
}