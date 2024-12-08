#define skey 6548
long long password(char *protect, FILE *fa, char sbl)
{
    long long pass, fpass = pass = 0;
    short i;
    for (i = 0; protect[i] != 13 && protect[i] != '\0'; i++)
    {
        srand((unsigned int)protect[i] * skey * i);
        pass = ~pass;
        pass += rand() * 2010 * rand() * i;
        pass <<= (protect[i] % 10);
        pass = ~pass;
        pass ^= (~rand() * 867);
        pass >>= (protect[i] % 10);
        pass = ~pass;
        pass ^= (~protect[i] * rand());
    }
    srand(pass % 584848);
    for (i = 1; i < 5; i++, pass += (((((rand() * (long long)rand()) * 16) * skey) * 54) * i))
        ;
    for (i = 0; protect[i] != 13 && protect[i] != '\0'; i++)
    {
        srand((unsigned int)protect[i] * (pass % skey) * i);
        fpass = ~fpass;
        fpass += rand() * 2010 * rand() * i;
        fpass <<= (protect[i] % 10);
        fpass = ~fpass;
        fpass ^= (~rand() * 867);
        fpass >>= (protect[i] % 10);
        fpass += pass;
        fpass ^= (~protect[i] * rand());
    }
    srand(fpass % 264864);
    for (i = 1; i < 5; i++, fpass += (((((rand() * (long long)rand()) * 16) * skey) * 54) * i))
        ;
    rewind(fa);
    if (sbl == 'c')
    {
        long long temp;
        fread(&temp, sizeof(temp), 1, fa);
        if (temp == fpass)
        {
            return pass;
        }
        return 0;
    }
    else if (sbl == 'a')
    {
        fwrite(&fpass, sizeof(fpass), 1, fa);
    }
    return 0;
}