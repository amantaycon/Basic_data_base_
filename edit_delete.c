/*  This function takes three arguments and edit your data only one cell
1.  lable -> This is a editable data file name
2.  size -> size of lable
3.  y -> This is a editable data position
*/
void edit1(char *lable, int size, int y)
{
    FILE *x = fopen(lable, "rb+");               // open editable file
    fseek(x, sizeof(char) * size * y, SEEK_SET); // move curser on correct position
    char read[size];
    fread(read, sizeof(read), 1, x); // read old data
    printf("Lable\tOld_data  Enter New data\n%s\t%s\t", lable, read);
    scanf("%s", read); // input new data
    fflush(stdin);
    printf("Confirm your data modify now y/n(default y)");
    char flag = getchar();
    if (flag == 'y' || flag == 10) // modified your data
    {
        fseek(x, sizeof(char) * size * y, SEEK_SET);
        fwrite(read, sizeof(read), 1, x);
        printf("Successfully your data modified\n");
    }
    else
    {
        printf("Modification Canceled\n");
    }
    fflush(stdin);
    fclose(x);
}

/*  This function takes three arguments and edit your all data only one colum
1.  lable -> This is a editable data file name
2.  size -> size of lable
3.  temp -> This is file pointer which store all match data position
*/
void edit2(char *lable, int size, FILE *temp)
{
    FILE *x = fopen(lable, "rb+"); // open editable file
    int position;
    char read[size];
    rewind(temp);
    printf("Lable\tOld_data\tEnter New data   if you enter s for skip and c for cancel\n");

    // iteration for input one by one your new data
    while (1)
    {
        if (fread(&position, sizeof(position), 1, temp) == 0) // read position
        {
            break; // iteration break if end of file pointer 'lf -> listed file'
        }
        fseek(x, sizeof(read) * position, SEEK_SET); // move the cursur on matched data position
        fread(read, sizeof(read), 1, x);             // read data one by one
        printf("%s\t%s\t", lable, read);
        scanf("%s", read); // input new data one by one
        fflush(stdin);
        if (strcmp(read, "s") == 0) // skip current modification data
        {
            continue;
        }
        else if (strcmp(read, "c") == 0) // cancel for next modification
        {
            printf("Modification Canceled\n");
            break;
        }
        else
        {
            fseek(x, sizeof(read) * position, SEEK_SET); // move the cursur on matched data position
            fwrite(read, sizeof(read), 1, x);            // write new data one by one
        }
    }
    printf("Successfully your data modified\n");
    fflush(stdin);
    fclose(x);
}

/*  This function takes three arguments and edit your only one row data
1.  fa -> This is a file pointer which stores the names of all the file
2.  num -> This is integer pointer which store the number of lables
3.  y -> This is a editable data position
*/
void edit3(FILE *fa, int num, int y)
{
    fflush(fa); // all file buffer are clear
    fflush(stdin);
    FILE *temp[num]; // initialise the array file pointer 'array size' = number of lables
    int size[num];
    int size1;
    printf("if you enter s for skip and c for cancel");
    fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET); // move file curser to lable data list
    printf("\n%c ->\t", 1);                               // this is only for fun

    // iteration start for open all files and display all lables
    for (size_t i = 0; i < num; i++)
    {
        fread(&size1, sizeof(size1), 1, fa); // read size of lables name
        char read_name[size1];
        fread(read_name, sizeof(read_name), 1, fa); // read lable name
        printf("%s", read_name);                    // Display lable name

        // decorate the lables name
        for (size_t k = 0; k < size1 - strlen(read_name); k++)
        {
            printf(" ");
        }

        temp[i] = fopen(read_name, "rb+"); // open file one by one on diffrent file pointer
        size[i] = size1;                   // contain size of all lable name one by one
        rewind(temp[i]);                   // all file curser set the begning of file
    }
    printf("\nOld->\t");

    // this iteration display all lable Old data
    for (size_t i = 0; i < num; i++)
    {
        char temp_data[size[i]];                              // initialise data size of lables
        fseek(temp[i], sizeof(char) * size[i] * y, SEEK_SET); // move the cursur on correct data position
        fread(temp_data, sizeof(temp_data), 1, temp[i]);      // read data one by one every file pointer

        printf("%s", temp_data); // print every lables data one by one

        // decorate the lables data
        for (size_t k = 0; k < size[i] - strlen(temp_data); k++)
        {
            printf(" ");
        }
    }

    printf("\nNew->\t"); // print serial number of data

    // this iteration input all lable new data
    for (size_t i = 0; i < num; i++)
    {
        char temp_data[size[i]];         // initialise data size of lables
        scanf("%s", temp_data);          // print every lables data one by one
        if (strcmp(temp_data, "s") == 0) // skip edit current lable
        {
            continue;
        }
        if (strcmp(temp_data, "c") == 0) // cancel for nest editing lable
        {
            break;
        }

        fseek(temp[i], sizeof(char) * size[i] * y, SEEK_SET); // move the cursur on matched data position
        fwrite(temp_data, sizeof(temp_data), 1, temp[i]);     // read data one by one every file pointer
    }

    // iteration for close all file
    for (size_t i = 0; i < num; i++)
    {
        fclose(temp[i]);
    }
    printf("Successfully your data modified\n");
    fflush(stdin);
}

void edit(FILE *fa, int num, char *po, FILE *tf, int count)
{
    int x, y;
    {
        x = po[0] - 65;
        char temp[20];
        for (size_t i = 1; i < 20; i++)
        {
            temp[i - 1] = po[i];
        }
        y = atoi(temp);
    }
    if ((x < 0 || x >= num || y < 0 || y > count) && (po[0] != 48 || (y == 0 && po[0] == 48)))
    {
        printf(" Invalid cell \n");
        return;
    }
    else
    {
        int position, size;
        char *input;
        if (y != 0)
        {
            fseek(tf, sizeof(int) * (y - 1), SEEK_SET);
            fread(&position, sizeof(position), 1, tf);
        }
        if (po[0] != 48)
        {
            int i = x + 1;
            if (i > 0 && i <= num) // i is position os leble data if this is true
            {
                fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET); // move file curser to lable data list

                // iteration for move the file curser is correct position
                for (int j = 1; j != i; j++)
                {
                    fread(&size, sizeof(size), 1, fa);
                    fseek(fa, sizeof(char) * size, SEEK_CUR);
                }
                fread(&size, sizeof(size), 1, fa); // read size of intered lable
                input = (char *)malloc(sizeof(char) * size);
                fread(input, sizeof(char) * size, 1, fa); // read the searched lable name
            }
            else
            {
                printf(" Invalid cell \n");
                return;
            }
        }

        if (po[0] == 48)
        {
            edit3(fa, num, position);
        }
        else if (y == 0)
        {
            edit2(input, size, tf);
        }
        else
        {
            edit1(input, size, position);
        }
    }
}

void delete1(FILE *fa, int num, int y, char *temp_file_n, FILE *tf)
{
    fflush(fa); // all file buffer are clear
    char *temp_file_name[num];
    FILE *temp[num], *temp_file[num]; // initialise the array file pointer 'array size' = number of lables
    int size[num];
    int size1;
    fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET); // move file curser to lable data list

    // iteration start for open all files and display all lables
    for (size_t i = 0; i < num; i++)
    {
        fread(&size1, sizeof(size1), 1, fa); // read size of lables name
        char read_name[size1];
        fread(read_name, sizeof(read_name), 1, fa); // read lable name

        temp[i] = fopen(read_name, "rb"); // open file one by one on diffrent file pointer
        size[i] = size1;                  // contain size of all lable name one by one
        rewind(temp[i]);                  // all file curser set the begning of file
    }

    for (size_t i = 0; i < num; i++)
    {
        temp_file_name[i] = (char *)malloc(sizeof(char) * L_tmpnam);
        tmpnam(temp_file_name[i]);
        temp_file[i] = fopen(temp_file_name[i], "wb");
        rewind(temp_file[i]);
    }

    // this iteration display all lable Old data
    for (size_t i = 0; i < num; i++)
    {
        char temp_data[size[i]]; // initialise data size of lables
        for (size_t j = 0; 1; j++)
        {
            if (fread(temp_data, sizeof(temp_data), 1, temp[i]) == 0)
            {
                break;
            }
            if (j != y)
            {
                fwrite(temp_data, sizeof(temp_data), 1, temp_file[i]);
            }
        }
        fclose(temp[i]);
        fclose(temp_file[i]);
    }

    fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET); // move file curser to lable data list

    // iteration start for open all files and display all lables
    for (size_t i = 0; i < num; i++)
    {
        fread(&size1, sizeof(size1), 1, fa); // read size of lables name
        char read_name[size1];
        fread(read_name, sizeof(read_name), 1, fa); // read lable name
        remove(read_name);
        rename(temp_file_name[i], read_name);
        free(temp_file_name[i]);
    }
    printf("Your data successfully removed\n");
}

void delete2(char *main_name, char *fname)
{
    FILE *fa = fopen(main_name, "rb");
    char *temp_file_name = (char *)malloc(sizeof(char) * L_tmpnam);
    tmpnam(temp_file_name);
    int size;
    FILE *tf = fopen(temp_file_name, "wb");
    {
        long long pass;
        fread(&pass, sizeof(pass), 1, fa);
        fread(&size, sizeof(size), 1, fa);
        fwrite(&pass, sizeof(pass), 1, tf);
        fwrite(&size, sizeof(size), 1, tf);
    }
    while (1)
    {
        if (fread(&size, sizeof(size), 1, fa) == 0)
        {
            break;
        }
        char read_name[size];
        if (fread(read_name, sizeof(read_name), 1, fa) == 0)
        {
            break;
        }
        if (strcmp(read_name, fname) != 0)
        {
            fwrite(&size, sizeof(size), 1, tf);
            fwrite(read_name, sizeof(read_name), 1, tf);
        }
    }
    fclose(fa);
    fclose(tf);
    remove(main_name);
    rename(temp_file_name, main_name);
    remove(fname);
    free(temp_file_name);
    printf("Your lable is successfully removed\n");
}
