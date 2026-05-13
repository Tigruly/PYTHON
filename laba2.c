#define _CRT_SECURE_NO_WARNINGS
#define K 2
#include <stdio.h>
#include <locale.h>

int main(int argc, char* argv[])
{
    FILE* in;
    char ch;
    long posB, posE;     // позиция начала и конца предложения
    long pos;            // текущая позиция
    int n;               // нужное количество слов
    int words;           // счётчик слов
    int inWord;          // флаг: внутри слова или нет
    long i;

    setlocale(0, "");

    if (argc != K)
    {
        printf("Неверное количество аргументов");
        return 1;
    }

    in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Файл %s не найден", argv[1]);
        return 1;
    }

    printf("Введите количество слов: ");
    scanf("%d", &n);

    posB = ftell(in);
    words = 0;
    inWord = 0;

    while (fscanf(in, "%c", &ch) == 1)
    {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            if (inWord == 0)
            {
                inWord = 1;
                words++;
            }
        }
        else
        {
            inWord = 0;
            if (ch == '.' || ch == '?' || ch == '!')
            {
                posE = ftell(in);

                if (words == n)
                {
                    pos = posE;
                    fseek(in, posB, SEEK_SET);
                    for (i = posB; i < posE; i++)
                    {
                        fscanf(in, "%c", &ch);
                        printf("%c", ch);
                    }
                    printf("\n");
                    fseek(in, pos, SEEK_SET);
                }

                posB = posE;
                words = 0;
                inWord = 0;
            }
        }
    }

    _fcloseall();
    return 0;
}
