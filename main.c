#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <ctype.h>


int file_ends_with(const char* name, const char* extension)
{
    const char* ldot = strrchr(name, '.');
    if (ldot != NULL)
    {
        return strncmp(ldot + 1, extension, 3) == 0;
    }
    return 0;
}

int if_operators_count(FILE *fp)
{
    char line[100];
    int if_count = 0;
    rewind(fp);
    if (fp == NULL)
    {
        printf("File can't be read...");
        exit(1);
    }

    while (fgets(line, sizeof(line), fp))
    {
        int i = 0;
        while(line[i] != '\0')
        {
            if('i'==line[i])
            {
                if ('f'==line[i+1])
                {
                    if ('(' == line[i+2] || ' ' == line[i+2]) if_count++;
                }
            }
            i++;
        }
    }
    return if_count;
}

int file_line_count(FILE *fp)
{
    if (fp == NULL)
    {
        printf("File can't be read...");
        exit(1);
    }
    char line[100];
    int line_index = 0;

    while (fgets(line, sizeof(line), fp))
    {
        line_index++;
    }
    return (line_index);
}

void write_result_to_file(FILE *fp, int shortest_line, int if_count)
{
    fputs("file lines: ", fp);
    fprintf(fp, "%d", shortest_line);
    fputc('\n', fp);
    fputs("if count: ", fp);
    fprintf(fp, "%d", if_count);
}

int main()
{
    FILE *read_file, *written_file;
    char READ_FILENAME[_MAX_FNAME], WRITTEN_FILENAME[_MAX_FNAME];
    int shortest_line, if_count;

    do
    {
        printf("Enter file you want to be read(should end on '.c'): ");
        gets(READ_FILENAME);
    } while (!file_ends_with(READ_FILENAME, "c"));

    read_file = fopen(READ_FILENAME, "r");
    shortest_line = file_line_count(read_file);
    if_count = if_operators_count(read_file);
    fclose(read_file);

    printf("Enter file name you want to write results on: ");
    gets(WRITTEN_FILENAME);

    written_file = fopen(WRITTEN_FILENAME, "w");


    write_result_to_file(written_file, shortest_line, if_count);
    fclose(written_file);

    printf("File lines: %d\n", shortest_line);
    printf("IF and IF-ELSE number: %d", if_count);

    return 0;
}