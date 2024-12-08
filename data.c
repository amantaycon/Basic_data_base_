
short data(FILE *fa, long long pass)
{
    FILE *tf;
    fflush(fa);
repeat:
    fseek(fa, 0, SEEK_END);
    if (ftell(fa) == sizeof(long long) + sizeof(int))
    {
        printf(" ---> Not found any Lable <---\n");
        return -1;
    }

    fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET);
    int size;
    printf(" ---> Add the detail sequentially <---\n  ");
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
        if ((tf = fopen(read_name, "rb")) == 0)
        {
            printf("\n ---> Some file are missing <---\n");
            return -1;
        }
        else
        {
            fclose(tf);
        }
        printf(" %s", read_name);
        size = size - strlen(read_name) - 1;
        while (size > 0)
        {
            printf(" ");
            size--;
        }
    }
    printf("\n   ");
    fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET);
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
        if ((tf = fopen(read_name, "ab")) == 0)
        {
            printf(" ---> Some files Error <---\n");
            return -1;
        }
        char temp_data[size];
        scanf("%s", temp_data);
        fwrite(temp_data, sizeof(temp_data), 1, tf);
        fclose(tf);
    }
    fflush(fa);
    printf(" ---> Your data will be successfully added <---\n ---> Would you like to add more data (y/n)(default y) <---\n");
    fflush(stdin);
    char y = getchar();
    if (y == 'y' || y == 10)
    {
        goto repeat;
    }
    return 0;
}