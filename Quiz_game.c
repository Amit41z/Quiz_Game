#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#define QNO 30
#define totques 10
#define size 200
char playername[10];
void asked(char option[size], const char option1[size], const char option2[size],
           const char option3[size], const char option4[size], const char correct[size], const char category[size], FILE *fp, int *);
void Display();
void warmup();
void main()
{
    char text[size], option1[size], option2[size], option3[size], option4[size], option[size],
        correct[size], category[size];
    char empty[256][256];
    int i, j, k;
    int arr[QNO], x, loc;
    time_t t;
    char line[256];
    int score = 0;
    FILE *fp;
    FILE *output;
    fp = fopen("Quiz.txt", "r");
    output = fopen("NewText.txt", "w");
    if (fp == NULL)
    {
        printf("\n\n\n \t\t\t Quiz File Can't Be OPENED \t\t\t \n\n\n");
    }
    if (output == NULL)
    {
        printf("\n\n\n \t\t\t NewText File Can't Be CREATED \t\t\t \n\n\n");
    }
    system("cls");
    Display();
    warmup();
    k = 0;
    for (i = 0; i < 30; i++)
    {
        arr[i] = 10 * i + 1;
    }
    for (j = 0; j < totques; j++)
    {
        /* Intializes random number generator */
        srand((unsigned)time(&t));
        /* stores random number from 0 to 3 */
        x = rand() % 3;
        loc = (3 * j) + x;
        for (i = arr[3 * j]; i < arr[loc]; i++)
        {
            fgets(empty[k], sizeof(empty[k]), fp);
            k++;
        }
        for (i = 1; i <= 10; i++)
        {
            fgets(line, sizeof(line), fp);
            if (i == 1)
            {
                printf("\n\n\n\n\n\nQ%d) %s", j + 1, line);
                fprintf(output, "Q%d) %s", j + 1, line);
            }
            if (i == 2)
            {
                fputs(line, output);
            }
            if (i == 3)
                strncpy(option1, line, 30);
            if (i == 4)
                strncpy(option2, line, 30);
            if (i == 5)
                strncpy(option3, line, 30);
            if (i == 6)
                strncpy(option4, line, 30);
            if (i > 1 && i <= 7)
            {
                printf("%s", line);
            }
            if (i == 8)
                strncpy(correct, line, 30);
            if (i == 9)
                strncpy(category, line, 30);
        }
        asked(option, option1, option2, option3, option4, correct, category, output, &score);
        if (j != 9)
        {
            if (arr[loc] + 10 < arr[3 * (j + 1)])
            {
                for (i = arr[loc] + 10; i < arr[3 * (j + 1)]; i++)
                {
                    fgets(empty[k], sizeof(empty[k]), fp);
                    k++;
                }
            }
        }
        system("cls");
    }
    fprintf(output, " \nHeyy %s, You got total %d out of 20 ", playername, score);
    fclose(fp);
    fclose(output);
    output = fopen("Newtext.txt", "r");
    while (fgets(line, sizeof(line), output))
    {
        printf(" %s", line);
    }
    fclose(output);
    system("pause");
}
void asked(char option[size], const char option1[size], const char option2[size], const char option3[size], const char option4[size],
           const char correct[size], const char category[size], FILE *fp, int *score)
{
    printf("Your Option : ");
    scanf("%str", &option[0]);
    option[1] = '\0';
    strupr(option);
    char correctanswer[size];
    char wronganswer[size];
    fprintf(fp, "%s \n", category);
    if (option[0] == correct[0])
    {
        if (option[0] == option1[0])
            fprintf(fp, " \nYou entered correct answer : %s \n ", option1);
        if (option[0] == option2[0])
            fprintf(fp, " \nYou entered correct answer : %s \n ", option2);
        if (option[0] == option3[0])
            fprintf(fp, " \nYou entered correct answer : %s \n ", option3);
        if (option[0] == option4[0])
            fprintf(fp, " \nYou entered correct answer : %s \n ", option4);
        *score += 2;
        fprintf(fp, " \n You are awarded 2 marks for this correct answer \n ");
    }
    else
    {
        if (correct[0] == option1[0])
            strncpy(correctanswer, option1, 24);
        if (correct[0] == option2[0])
            strncpy(correctanswer, option2, 24);
        if (correct[0] == option3[0])
            strncpy(correctanswer, option3, 24);
        if (correct[0] == option4[0])
            strncpy(correctanswer, option4, 24);
        correctanswer[24] = '\0';
        if (option[0] == option1[0])
            strncpy(wronganswer, option1, 24);
        if (option[0] == option2[0])
            strncpy(wronganswer, option2, 24);
        if (option[0] == option3[0])
            strncpy(wronganswer, option3, 24);
        if (option[0] == option4[0])
            strncpy(wronganswer, option4, 24);
        wronganswer[24] = '\0';
        fprintf(fp, " You entered : %s \n", wronganswer);
        fprintf(fp, " Correct answer : %s \n", correctanswer);
        fprintf(fp, " \n You are awarded 0 marks for this wrong answer \n ");
    }
    fprintf(fp, " -----------------------------------------------------------------------------\n");
    fprintf(fp, " -----------------------------------------------------------------------------\n");
}
void Display()
{
    printf("\n\n\n\n\n\n");
    printf("\t\t\t\t PLEASE ENTER YOUR NAME\n");
    scanf("%s", &playername);
    system("cls");
    printf("\n\n\n\n\n\n");
    printf("\t\t\t\t HEYY!!! %s\n", playername);
    printf("\n\n\n\t\t\t PRESS ENTER TO PLAY ");
    printf("\n\n\n\t\t\t\t RULES OF THE GAME : \n");
    printf("\n\t\t\t\t 1) There are 2 rounds in this Quiz Game, ---> WARMUP ROUND & CHALLENGE ROUND");
    printf("\n\t\t\t\t 2) In warmup round you will be asked a total of 3 questions to test your");
    printf("\n\t\t\t\t general knowledge. You are eligible to play the game if you give atleast 2");
    printf("\n\t\t\t\t right answers, otherwise you can't proceed further to the Challenge Round.");
    printf("\n\t\t\t\t 3) Your game starts with CHALLANGE ROUND. In this round you will be asked a");
    printf("\n\t\t\t\t random questions of any topic all in total of 10 questions.");
    printf("\n\t\t\t\t 4) 4 marks will be awarded for correct");
    printf("\n\t\t\t\t 5) No marks will be awarded for incorrect");
    printf("\n\t\t\t\t 6) Score will be displayed at the end\n");
    system("pause");
    system("cls");
}

void warmup()
{
    system("cls");
    int count = 0;
    for (int i = 1; i <= 3; i++)
    {
        system("cls");
        int r1 = i;
        switch (r1)
        {
        case 1:
            printf("\n\nWhat least number must be added to 1056, so that the sum is completely divisible by 23 ?");
            printf("\n\nA.15\t\tB.30\n\nC.2\t\tD.50\n");
            if (toupper(getch()) == 'C')
            {
                printf("\n\nCorrect!!!");
                count++;
                getch();
                break;
            }
            else
            {
                printf("\n\nWrong!!! The correct answer is C.2");
                getch();
                break;
            }
        case 2:
            printf("\n\n\nWhat country was known as Ceylon until 1972?");
            printf("\n\nA.France\t\tB.Denmark\n\nC.Sri Lanka\t\tD.Finland\n");
            if (toupper(getch()) == 'C')
            {
                printf("\n\nCorrect!!!");
                count++;
                getch();
                break;
            }
            else
            {
                printf("\n\nWrong!!! The correct answer is C.Sri Lanka");
                getch();
                break;
            }
        case 3:
            printf("\n\n\nWhich is the largest mammals?");
            printf("\n\nA.Polar Bear\t\tB.Blue Whale\n\nC.Hippopotamus\t\tD.Elephant\n");
            if (toupper(getch()) == 'B')
            {
                printf("\n\nCorrect!!!");
                count++;
                getch();
                break;
            }
            else
            {
                printf("\n\nWrong!!! The correct answer is B.Blue Whale");
                getch();
                break;
            }
        }
    }
    if (count >= 2)
    {
        system("cls");
        printf("\n\n\t*** CONGRATULATION %s you are eligible to play the Game ***",playername);
    }
    else
    {
        system("cls");
        printf("\n\nSORRY YOU ARE NOT ELIGIBLE TO PLAY THIS GAME, BETTER LUCK NEXT TIME");
        exit(0);
    }
}
