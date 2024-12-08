char all_find(FILE *, int, char *, FILE *);
int fname_r(FILE *, char *, int *, int *);
void sort(FILE *, char *, int);

/*  This function takes four arguments and display listed data
1.  fa -> This is a file pointer which stores the names of all the file
2.  num -> This is integer pointer which store the number of lables
3.  ps -> This is file pointer which store all match data position
4.  search -> this is the searched name pointer
*/
void data_show(FILE *fa, int num, FILE *ps, char *search)
{
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE); // This line colorfull text display argument
    fflush(fa);                                  // all file buffer are clear
    FILE *temp[num];                             // initialise the array file pointer 'array size' = number of lables
    int size[num];
    int size1;

    fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET); // move file curser to lable data list
    SetConsoleTextAttribute(hc, 6);
    printf("\n%c ->\t", 1); // this is only for fun
    SetConsoleTextAttribute(hc, 2);

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

        temp[i] = fopen(read_name, "rb"); // open file one by one on diffrent file pointer
        size[i] = size1;                  // contain size of all lable name one by one
        rewind(temp[i]);                  // all file curser set the begning of file
    }
    {
        fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET); // move file curser to lable data list
        SetConsoleTextAttribute(hc, 4);
        printf("\n%c ->\t", 3); // this is only for fun
        SetConsoleTextAttribute(hc, 1);

        // iteration for print lable counter
        for (size_t i = 0, j = 65; i < num; i++, j++)
        {
            fread(&size1, sizeof(size1), 1, fa);       // read size of lables name
            fseek(fa, sizeof(char) * size1, SEEK_CUR); // move the next lable position
            printf("%c", j);                           // Display lable counter

            // decorate the lables counter
            for (size_t k = 0; k < size1 - 1; k++)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    rewind(ps); // curser set the begning of file

    // iteration start for display all matched data list
    for (size_t j = 1; 1; j++)
    {
        if (fread(&size1, sizeof(size1), 1, ps) == 0)
        {
            break; // iteration break if end of file pointer 'ps'
        }
        SetConsoleTextAttribute(hc, 1);
        printf("\n%d\t", j); // print serial number of data

        // this iteration display all lable data in matching list
        for (size_t i = 0; i < num; i++)
        {
            char temp_data[size[i]];                                  // initialise data size of lables
            fseek(temp[i], sizeof(char) * size[i] * size1, SEEK_SET); // move the cursur on matched data position
            fread(temp_data, sizeof(temp_data), 1, temp[i]);          // read data one by one every file pointer
            SetConsoleTextAttribute(hc, 3);
            if (strcmp(search, temp_data) == 0) // searched data color change
            {
                SetConsoleTextAttribute(hc, 5);
            }
            printf("%s", temp_data); // print every lables data one by one

            // decorate the lables name
            for (size_t k = 0; k < size[i] - strlen(temp_data); k++)
            {
                printf(" ");
            }
        }
    }
    printf("\n");
    SetConsoleTextAttribute(hc, 7);

    // iteration for close all file
    for (size_t i = 0; i < num; i++)
    {
        fclose(temp[i]);
    }
}

/* This function match lable and return size of lable otherwise return Zero
1.  fa -> This is a file pointer which stores the names of all the file
2.  num -> This is integer pointer which store the number of lables
3.  input -> this is the searched lable pointer dynamically allocated
*/
int find_lable(FILE *fa, int num, char *input)
{
    int i = atoi(input); // converted to integer if input is integer string
    int size;
    if (i > 0 && i <= num) // i is position os leble data if this is true
    {
        fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET); // move file curser to lable data list

        // iteration for move the file curser is correct position
        for (int j = 1; j != i; j++)
        {
            fread(&size, sizeof(size), 1, fa);
            fseek(fa, sizeof(char) * size, SEEK_CUR);
        }
        fread(&size, sizeof(size), 1, fa);                   // read size of intered lable
        input = (char *)realloc(input, sizeof(char) * size); // resize input
        fread(input, sizeof(char) * size, 1, fa);            // read the searched lable name
        return size;                                         // return size of searched lable name
    }
    else // input is string then its run
    {
        fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET); // move file curser to lable data list

        // char *read_name = (char*)malloc(sizeof(char)*4);

        // iteration for matching searched data with lable name
        while (1)
        {
            if (fread(&size, sizeof(size), 1, fa) == 0)
            {
                break;
            }
            char read_name[size];
            // read_name = (char *)realloc(read_name,sizeof(char *) * size);

            if (fread(read_name, sizeof(read_name), 1, fa) == 0)
            {
                break;
            }
            if (strcmp(input, read_name) == 0)
            {
                input = (char *)realloc(input, sizeof(char) * size); // resize input
                strcpy(input, read_name);
                return size; // return size of matched lable name
            }
        }
    }
    return 0; // if input don't match any lable returned Zero
}

/*  This function show all lable and input command and return dynamically allocating memory
1.  fa -> This is a file pointer which stores the names of all the file
2.  num -> This is integer pointer which replace the number of lables
*/
char *lable_show(FILE *fa, int *num)
{
    int size;
    *num = 0;
    printf(" Search your data by giving any information \n");
    fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET); // move file curser to lable data list
    size_t i = 1;

    // iteration start for showing all lable name
    for (; 1; i++)
    {
        if (fread(&size, sizeof(size), 1, fa) == 0)
        {
            break;
        }
        char read_name[size];
        if (*num < size) // read maximum size of lable
        {
            *num = size;
        }
        if (fread(read_name, sizeof(read_name), 1, fa) == 0)
        {
            break;
        }
        printf(" %d. %s\n", i, read_name); // print lable name
    }
    printf(" %d. all\n", i);                             // print extra command
    char *input = (char *)malloc(sizeof(char) * (*num)); // Dynamically allocating memory lenght = maximum size of lable
    *num = i - 1;                                        // stored num of lable
    return input;                                        // return dynamically allocating memory
}

/*  This function takes six arguments and ready new matched list and returned
1.  lf -> Which stores previous matched data
2.  fname -> Which store lable name of file
3.  size -> Which store size of lable name
4.  search -> this is searched string and replace temp file name
5.  fa -> this is only for calling next function
6.  num -> this is only for calling next function
*/
char *data_list(FILE *lf, char *fname, int size, char *search, FILE *fa, int num)
{
    FILE *temp = fopen(fname, "rb"); // the search file opened
    rewind(temp);                    // curser set the begning of file
    rewind(lf);                      // curser set the begning of file

    char *temp_data = (char *)malloc(sizeof(char) * size);      // Dynamically initialise array size = size of lable
    char *temp_fname = (char *)malloc(sizeof(char) * L_tmpnam); // Dynamically initialise temp file

    tmpnam(temp_fname);                  // assign temp name
    FILE *tf = fopen(temp_fname, "wb+"); // open temp file
    int position, i = 0;

    // iteration start for write all matched data position
    while (1)
    {
        if (fread(&position, sizeof(position), 1, lf) == 0) // read position
        {
            break; // iteration break if end of file pointer 'lf -> listed file'
        }
        fseek(temp, sizeof(char) * size * position, SEEK_SET); // move the cursur on matched data position
        fread(temp_data, sizeof(char) * size, 1, temp);        // read data one by one
        if (strcmp(search, temp_data) == 0)
        {
            fwrite(&position, sizeof(position), 1, tf); // write matched data position on new temp file
            i++;
        }
    }
    fclose(temp);                           // close lable file
    printf(" *** %d data matched***\n", i); // print number of matched data
    if (i != 0)
    {
        printf(" ***Show matched data Enter the command 'show'\n");
    }
    temp_data = (char *)realloc(temp_data, sizeof(char) * 50);
    char show = 'a'; // initialise flag
    while (1)
    {
        fflush(stdin);
        scanf("%s", temp_data);
        if (strcmp("show", temp_data) == 0 && i != 0)
        {
            data_show(fa, num, tf, search); // print all matched data
            show = 'b';
        }
        else if (strcmp("edit", temp_data) == 0 && show == 'b')
        {
            char x[20];
            scanf("%s", x);
            fflush(stdin);
            edit(fa, num, x, tf, i);
        }
        else if (strcmp("remove", temp_data) == 0 && show == 'b')
        {
            scanf("%d", &position);
            fflush(stdin);
            if (position > 0 && position <= i)
            {
                fseek(tf, sizeof(int) * (position - 1), SEEK_SET);
                fread(&position, sizeof(position), 1, tf);
                delete1(fa, num, position, temp_fname, tf);
            }
            else
            {
                printf(" Invalid number \n");
            }
        }
        else if (strcmp("sort", temp_data) == 0)
        {
            scanf("%s", temp_data);
            if ((size = find_lable(fa, num, temp_data)) != 0)
            {
                sort(tf, temp_data, size);
            }
            else
            {
                puts(" Not match any lables\n");
            }
        }
        else if (strcmp("cls", temp_data) == 0)
        {
            system("cls"); // clear screen
        }
        else if (strcmp("all", temp_data) == 0)
        {
            scanf("%s", search);
            fflush(stdin);
            all_find(fa, num, search, lf);
            fflush(stdin);
        }
        else if (strcmp("back", temp_data) == 0)
        {
            break; // one step back
        }
        else if (strcmp("home", temp_data) == 0)
        {
            strcpy(temp_data, "home");
            break; // return home menu
        }
        else
        {
            if ((size = find_lable(fa, num, temp_data)) != 0)
            {
                scanf("%s", search);
                fflush(stdin);
                if (strcmp(data_list(tf, temp_data, size, search, fa, num), "home") == 0)
                {
                    strcpy(temp_data, "home");
                    break;
                }
            }
            else
            {
                puts(" Not match any lables or commands ");
            }
            continue;
        }
    }
    fflush(stdin);
    fclose(tf);
    remove(temp_fname);
    free(temp_fname); // free dynamically allocated memory
    if (strcmp(temp_data, "home") == 0)
    {
        free(temp_data); // free dynamically allocated memory
        return "home";
    }
    free(temp_data); // free dynamically allocated memory
    return "A";
}

/* This function return file pointer for stored all data position
1.  fname = searched lable name pointer
2.  temp_file = dynamically allocated memory for creating temp file
3.  size = size of searched lable name
*/
FILE *count_data(char *fname, char *temp_file, int size)
{
    FILE *fl = fopen(fname, "rb");          // open searched lable file
    tmpnam(temp_file);                      // temp file name calling
    FILE *temp_f = fopen(temp_file, "wb+"); // open temp file

    fseek(fl, 0, SEEK_END); // file curser move end of file
    int list = ftell(fl);   // store end of file curser
    list /= size;           // get number of data
    fclose(fl);             // close lable file

    // iteration for writing all position of all data
    for (int i = 0; i < list; i++)
    {
        fwrite(&i, sizeof(i), 1, temp_f);
    }
    return temp_f; // file pointer which stored all data position
}

/*  This function search in all data
1.  fa -> This is a file pointer which stores the names of all the file
2.  num -> This is integer pointer which store the number of lables
3.  search -> this is the searched name pointer
4. pos -> Which stores previous matched data
*/
char all_find(FILE *fa, int num, char *search, FILE *pos)
{
    FILE *temp[num]; // initialise the array file pointer 'array size' = number of lables
    int size[num];
    int position, list, count = 0;
    int data;
    char *temp_file = (char *)malloc(sizeof(char) * L_tmpnam); // dynamically allocating memory for temp file name
    tmpnam(temp_file);                                         // temp file name calling
    FILE *temp_f = fopen(temp_file, "wb+");                    // open temp file

    fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET); // move file curser to lable data list

    // iteration start for open all files
    for (size_t i = 0; i < num; i++)
    {
        fread(&position, sizeof(position), 1, fa); // read size of lables name
        char read_name[position];
        fread(read_name, sizeof(read_name), 1, fa); // read lable name
        temp[i] = fopen(read_name, "rb");           // open file one by one on diffrent file pointer
        size[i] = position;                         // contain size of all lable name one by one
        rewind(temp[i]);                            // all file curser set the begning of file
    }

    // read number of data
    {
        fseek(temp[0], 0, SEEK_END); // file curser move end of file
        list = ftell(temp[0]);       // store end of file curser position
        list /= size[0];             // get number of data
        rewind(temp[0]);
    }

    rewind(pos);
    // iteration for write all matched data position
    while (1)
    {
        position = -1;
        if (fread(&data, sizeof(data), 1, pos) == 0)
        {
            break;
        }
        // iteration for seaching data
        for (size_t i = 0; i < num; i++)
        {
            char temp_data[size[i]]; // initialise data size of lables
            fseek(temp[i], sizeof(temp_data) * data, SEEK_SET);
            fread(temp_data, sizeof(temp_data), 1, temp[i]); // read data one by one every file pointer
            if (strcmp(search, temp_data) == 0)
            {
                position = data; // searched data position stored
                count++;
            }
        }
        if (position != -1)
        {
            fwrite(&position, sizeof(position), 1, temp_f); // write matched data position
        }
    }

    // iteration for close all file
    for (size_t i = 0; i < num; i++)
    {
        fclose(temp[i]);
    }

    printf(" *** %d data or word matched***\n", count); // print number of match data
    if (count != 0)
    {
        printf(" ***Show matched data Enter the command 'show'\n");
    }
    char *show = (char *)malloc(sizeof(char) * 30);
    char flag = 'a';

    while (1)
    {
        fflush(stdin);
        scanf("%s", show);
        if (strcmp(show, "show") == 0)
        {
            data_show(fa, num, temp_f, search); // calling for all matched data print
            flag = 'b';
        }
        else if (strcmp("edit", show) == 0 && flag == 'b')
        {
            char x[20];
            scanf("%s", x);
            fflush(stdin);
            edit(fa, num, x, temp_f, list);
        }
        else if (strcmp("remove", show) == 0 && flag == 'b')
        {
            scanf("%d", &position);
            fflush(stdin);
            if (position > 0 && position <= list)
            {
                fseek(temp_f, sizeof(int) * (position - 1), SEEK_SET);
                fread(&position, sizeof(position), 1, temp_f);
                delete1(fa, num, position, temp_file, temp_f);
            }
            else
            {
                printf(" Invalid number \n");
            }
        }
        else if (strcmp("cls", show) == 0)
        {
            system("cls"); // clear screen
        }
        else if (strcmp("back", show) == 0)
        {
            break; // one step back
        }
        else if (strcmp("home", show) == 0)
        {
            flag = 'r';
            break; // one step back
        }
        else
        {
            if ((position = find_lable(fa, num, show)) != 0)
            {
                scanf("%s", search);
                fflush(stdin);
                if (strcmp(data_list(temp_f, show, position, search, fa, num), "home") == 0)
                {
                    flag = 'r';
                    break;
                }
            }
            else
            {
                puts(" Not match any lables or commands ");
            }
            continue;
        }
    }
    fclose(temp_f);
    remove(temp_file);
    free(temp_file);
    fflush(stdin);
    return flag;
}

/*  This function find datails or data
1.  fa -> This is a file pointer which stores the names of all the file
*/
void find(FILE *fa)
{
    fflush(stdin);
    int num, size;
    char *fname = lable_show(fa, &num); // stored dynamically allocating memory size = maximum size of lable
    char flag = 's';
    while (1)
    {
        scanf("%s", fname); // input command
        if (strcmp(fname, "back") == 0)
        {
            break;
        }
        else if (strcmp(fname, "cls") == 0)
        {
            system("cls");
        }
        else if (strcmp(fname, "all") == 0 || atoi(fname) == num + 1)
        {
            int size1, num;
            char *temp_file = (char *)malloc(sizeof(char) * L_tmpnam);
            if (fname_r(fa, fname, &size1, &num) == 0)
            {
                FILE *temp = count_data(fname, temp_file, size1);
                fname = (char *)realloc(fname, sizeof(char) * 30);
                scanf("%s", fname);
                flag = all_find(fa, num, fname, temp); // calling search all data function
                if (flag == 'r')
                {
                    break;
                }
                fclose(temp);
                remove(temp_file);
                free(temp_file);
            }
        }
        // if matched lable return lable size otherwise Zero
        else if ((size = find_lable(fa, num, fname)) != 0)
        {
            char *search = (char *)malloc(sizeof(char) * size); // dynamically allocating memory
            scanf("%s", search);
            fflush(stdin);
            char *t_f_name = (char *)malloc(sizeof(char) * L_tmpnam);                 // dynamically allocating memory for temp file name
            FILE *t_file = count_data(fname, t_f_name, size);                         // returned file pointer which stored all data position
            if (strcmp(data_list(t_file, fname, size, search, fa, num), "home") == 0) // calling data_list
            {
                flag = 'r';
            }
            fclose(t_file);   // close temp file
            remove(t_f_name); // removed temp file
            free(t_f_name);   // free dynamically allocated memory
            free(search);
            if (flag == 'r')
            {
                break;
            }
        }
        else
        {
            printf(" Not match any arguments \n"); // not matching any command or lables
        }
        fflush(stdin);
    }
    free(fname);
    fflush(stdin);
}

/* This function read any one lable and size in fname and size and also read total number of lable in num
fa -> This is a file pointer which stores the names of all the file
*/
int fname_r(FILE *fa, char *fname, int *size, int *num)
{
    fseek(fa, sizeof(long long) + sizeof(int), SEEK_SET); // move file curser to lable data list
    size_t i = 0;

    if (fread(size, sizeof(int), 1, fa) == 0) // read lable size
    {
        return -1;
    }
    fname = (char *)realloc(fname, sizeof(char) * (*size));
    if (fread(fname, sizeof(char) * (*size), 1, fa) == 0) // read any one lable
    {
        return -1;
    }
    i++;
    int size1;

    // iteration
    while (1)
    {
        if (fread(&size1, sizeof(int), 1, fa) == 0)
        {
            break;
        }
        char read_name[size1];
        if (fread(read_name, sizeof(read_name), 1, fa) == 0)
        {
            break;
        }
        i++;
    }
    *num = i; // stored count of lable
    return 0;
}

/* This function display all data
1.  fa -> This is a file pointer which stores the names of all the file
*/
void show_all(FILE *fa)
{
    int size1, num;
    char *temp_file = (char *)malloc(sizeof(char) * L_tmpnam);
    char *fname = (char *)malloc(sizeof(char) * 5);
    if (fname_r(fa, fname, &size1, &num) == 0)
    {
        FILE *temp = count_data(fname, temp_file, size1);
        data_show(fa, num, temp, " ");

        char *show = (char *)malloc(sizeof(char) * 30);
        int list;
        // read number of data
        {
            fseek(temp, 0, SEEK_END); // file curser move end of file
            list = ftell(temp);       // store end of file curser position
            list /= sizeof(int);      // get number of data
        }
        while (1)
        {
            fflush(stdin);
            scanf("%s", show);
            if (strcmp("edit", show) == 0)
            {
                char x[20];
                scanf("%s", x);
                fflush(stdin);
                edit(fa, num, x, temp, list);
            }
            else if (strcmp("remove", show) == 0)
            {
                scanf("%d", &size1);
                fflush(stdin);
                if (size1 > 0 && size1 <= list)
                {
                    fseek(temp, sizeof(int) * (size1 - 1), SEEK_SET);
                    fread(&size1, sizeof(size1), 1, temp);
                    delete1(fa, num, size1, temp_file, temp);
                }
                else
                {
                    printf(" Invalid number \n");
                }
            }
            else if (strcmp("all", show) == 0)
            {
                scanf("%s", show);
                fflush(stdin);
                all_find(fa, num, show, temp);
                fflush(stdin);
            }
            else if (strcmp("cls", show) == 0)
            {
                system("cls"); // clear screen
            }
            else if (strcmp("back", show) == 0 || strcmp("home", show) == 0)
            {
                break; // one step back
            }
            else
            {
                if ((size1 = find_lable(fa, num, show)) != 0)
                {
                    char *search = (char *)malloc(sizeof(char) * size1);
                    scanf("%s", search);
                    fflush(stdin);
                    if (strcmp(data_list(temp, show, size1, search, fa, num), "home") == 0)
                    {
                        break;
                    }
                    free(search);
                }
                else
                {
                    puts(" Not match any lables or commands ");
                }
                continue;
            }
        }
        fclose(temp);
        remove(temp_file);
    }
    else
    {
        printf(" Not any data found\n");
    }
    free(fname);
    free(temp_file);
}

void sort(FILE *tf, char *lname, int size)
{
    FILE *lf = fopen(lname, "rb");
    char data_read1[size];
    char data_read2[size];
    int position1, list;
    int position2;
    char flag;
    fseek(tf, 0, SEEK_END); // file curser move end of file
    list = ftell(tf);       // store end of file curser position
    list /= sizeof(int);    // get number of data
    for (size_t i = 0; i < list; i++)
    {
        fflush(tf);
        fflush(lf);
        rewind(tf);
        for (size_t j = 1; j < list - i; j++)
        {
            flag = 'n';
            fread(&position1, sizeof(int), 1, tf);
            fseek(lf, sizeof(data_read1) * position1, SEEK_SET);
            fread(data_read1, sizeof(data_read1), 1, lf);

            fread(&position2, sizeof(int), 1, tf);
            fseek(lf, sizeof(data_read2) * position2, SEEK_SET);
            fread(data_read2, sizeof(data_read2), 1, lf);
            for (size_t k = 0; k < size; k++)
            {
                if (data_read1[k] == '\0' || data_read2[k] == '\0')
                {
                    break;
                }
                else if (data_read1[k] > data_read2[k])
                {
                    flag = 'y';
                    break;
                }
                else if (data_read1[k] < data_read2[k])
                {
                    break;
                }
            }
            if (flag == 'y')
            {
                fseek(tf, -(sizeof(int) * 2), SEEK_CUR);
                fwrite(&position2, sizeof(int), 1, tf);
                fwrite(&position1, sizeof(int), 1, tf);
            }
            fseek(tf, -sizeof(int), SEEK_CUR);
        }
    }
    printf("your %s is sorted\n", lname);
    fclose(lf);
}
