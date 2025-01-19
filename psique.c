#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char question[256];
    char options[4][100];
    char correct_option;
}Question;
void load_questions(Question questions[],int * total_questions);
void update_leaderboard (const char *name,int score);
void display_leaderboard(void);
#define MAX_QUESTIONS 10
#define MAX_NAME_LENGTH 50


int main(void)
{
    Question questions[MAX_QUESTIONS];
    int total_questions;

    load_questions(questions, &total_questions);

    char player_name[MAX_NAME_LENGTH];
    printf("Enter your name: ");
    scanf("%s", player_name);

    int score = 0;
    for (int i = 0; i < total_questions; i++)
    {
        Question *q = &questions[i];
        printf("\nQuestion %d: %s\n", i + 1, q->question);
        printf("A) %s\n", q->options[0]);
        printf("B) %s\n", q->options[1]);
        printf("C) %s\n", q->options[2]);
        printf("D) %s\n", q->options[3]);

        char answer;
        printf("Your answer: ");
        scanf(" %c", &answer);

        while(answer != 'a' && answer !='A' && answer!='B' && answer!='b' && answer!='C' && answer!='c' && answer!='D' && answer!='d')
        {
            printf("choose correct option\n");
            printf("Your answer: ");
            scanf(" %c", &answer);
        }

        // Convert answer to uppercase to make it case-insensitive
        answer = toupper(answer);

        if (answer == q->correct_option)
        {
            printf("Correct!\n");
            score++;
        }
        else
        {
            printf("Wrong! The correct answer was %c.\n", q->correct_option);
        }
    }

    printf("\n%s, your final score is: %d\n", player_name, score);
    update_leaderboard(player_name, score);

    display_leaderboard();

    return 0;

}
void load_questions(Question questions[],int * total_questions)
{
    *total_questions=10;
    strcpy(questions[0].question,"what is scrondigher equation primarily used to describe");
    strcpy(questions[0].options[0],"black hole dyanmics");
    strcpy(questions[0].options[1],"electro magnetic fields");
    strcpy(questions[0].options[2],"quantum mechanics");
    strcpy(questions[0].options[3],"general relativity");
    questions[0].correct_option='C';

    strcpy(questions[1].question, "Who is credited with the discovery of the electron?");
strcpy(questions[1].options[0], "Ernest Rutherford");
strcpy(questions[1].options[1], "Niels Bohr");
strcpy(questions[1].options[2], "J.J. Thomson");
strcpy(questions[1].options[3], "James Clerk Maxwell");
questions[1].correct_option = 'C';

strcpy(questions[2].question, "Which element has the highest melting point?");
strcpy(questions[2].options[0], "Carbon");
strcpy(questions[2].options[1], "Tungsten");
strcpy(questions[2].options[2], "Osmium");
strcpy(questions[2].options[3], "Iridium");
questions[2].correct_option = 'B';

strcpy(questions[3].question, "Which chemical element is named after the creator of the periodic table?");
strcpy(questions[3].options[0], "Mendelevium");
strcpy(questions[3].options[1], "Newtonium");
strcpy(questions[3].options[2], "Curium");
strcpy(questions[3].options[3], "Fermium");
questions[3].correct_option = 'A';

strcpy(questions[4].question, "Which planet has the most moons?");
strcpy(questions[4].options[0], "Earth");
strcpy(questions[4].options[1], "Mars");
strcpy(questions[4].options[2], "Jupiter");
strcpy(questions[4].options[3], "Saturn");
questions[4].correct_option = 'C';

strcpy(questions[5].question, "Who developed the theory of general relativity?");
strcpy(questions[5].options[0], "Albert Einstein");
strcpy(questions[5].options[1], "Isaac Newton");
strcpy(questions[5].options[2], "Niels Bohr");
strcpy(questions[5].options[3], "Galileo Galilei");
questions[5].correct_option = 'A';

strcpy(questions[6].question, "Which element is the most abundant in the Earth's crust?");
strcpy(questions[6].options[0], "Oxygen");
strcpy(questions[6].options[1], "Silicon");
strcpy(questions[6].options[2], "Aluminum");
strcpy(questions[6].options[3], "Iron");
questions[6].correct_option = 'A';

strcpy(questions[7].question, "What is the primary component of natural gas?");
strcpy(questions[7].options[0], "Methane");
strcpy(questions[7].options[1], "Ethane");
strcpy(questions[7].options[2], "Propane");
strcpy(questions[7].options[3], "Butane");
questions[7].correct_option = 'A';

strcpy(questions[8].question, "Which of the following particles is not a fermion?");
strcpy(questions[8].options[0], "Electron");
strcpy(questions[8].options[1], "Proton");
strcpy(questions[8].options[2], "Neutron");
strcpy(questions[8].options[3], "Photon");
questions[8].correct_option = 'D';

strcpy(questions[9].question, "Which branch of mathematics deals with the study of rates of change and slopes of curves?");
strcpy(questions[9].options[0], "Algebra");
strcpy(questions[9].options[1], "Geometry");
strcpy(questions[9].options[2], "Calculus");
strcpy(questions[9].options[3], "Statistics");
questions[9].correct_option = 'C';


}
void update_leaderboard (const char *name,int score)
{
    FILE *file=fopen("leaderboard.csv", "a");
    if(!file)
    {
        printf("error: could not open leaderboard.csv\n");
        exit(1);
    }
    fprintf(file,"%s %d\n",name,score);
    fclose(file);
}
void display_leaderboard(void)
{
    FILE *file = fopen("leaderboard.csv", "r");
    if (!file)
    {
        printf("No leaderboard\n");
        return;
    }
    printf("\nScoreboard:\n");
    printf("-------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char name[MAX_NAME_LENGTH];
        int score;
        sscanf(line, "%s %d", name, &score);  // Fixed the sscanf format specifier
        printf("%s: %d\n", name, score);
    }

    fclose(file);
}