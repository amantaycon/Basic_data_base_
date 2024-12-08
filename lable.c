
int lable(char lname[], FILE *fa, long long *pass, int size)
{
    fflush(fa);

    FILE *fn;
    if ((fn = fopen(lname, "r")) != 0)
    {
        fclose(fn);
        return -1;
    }
    else if ((fn = fopen(lname, "wb")) == 0)
    {
        return -2;
    }
    fseek(fa, 0, SEEK_END);
    fwrite(&size, sizeof(size), 1, fa);
    fwrite(lname, sizeof(char) * size, 1, fa);

    if (ftell(fa) != sizeof(long long) + sizeof(int) + sizeof(size) + (sizeof(char) * size))
    {
        char temp_name[size];
        strcpy(temp_name, " ");

        fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET);
        fread(&size, sizeof(size), 1, fa);
        char read_name[size];
        fread(read_name, sizeof(read_name), 1, fa);

        FILE *ftemp;
        if ((ftemp = fopen(read_name, "rb")) == 0)
        {
            fclose(fn);
            remove(lname);
            return -3;
        }
        fseek(ftemp, 0, SEEK_END);
        int temp1 = (ftell(ftemp) / size);
        fclose(ftemp);

        rewind(fn);
        while (temp1 != 0)
        {
            fwrite(temp_name, sizeof(temp_name), 1, fn);
            temp1--;
        }
        fclose(fn);
    }
    return 0;
}