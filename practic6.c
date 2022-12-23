#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

#define ESC 27

int verify_int(int *), verify_float(float *), rows, matrix_size;
void addNumbers(int, float (*matrix)[matrix_size], float *), clear(), calculations(int, float (*matrix)[matrix_size], float *, float (*roots)[matrix_size], float), displayMatrix(int, float matrix[rows][rows], float outcome[]);
float det(int, float matrix[][rows]);

int main()
{
    char key;
    do
    {
        printf("Press any button to keep going or escape to quit.");
        key = getch();
        if (key != ESC)
        {
            int matrix_size;
            float detCoefs;
            do
            {
                printf("\nSize of matrix: ");
            } while ((verify_int(&matrix_size) == 1));

            float matrix[matrix_size][matrix_size];
            float outcome[matrix_size];
            float roots[matrix_size][matrix_size];

            addNumbers(matrix_size, matrix, outcome);
            displayMatrix(matrix_size, matrix, outcome);
            detCoefs = det(matrix_size, matrix);

            if (detCoefs == 0)
            {
                printf("Impossible to calculate using Kramer's method!");
                return 0;
            }

            calculations(matrix_size, matrix, outcome, roots, detCoefs);
        }
    } while (key != ESC);
}

void calculations(int matrix_size, float (*matrix)[matrix_size], float *outcome, float (*roots)[matrix_size], float detCoefs)
{
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            for (int k = 0; k < matrix_size; k++)
            {
                if (k == i)
                {
                    roots[j][k] = outcome[j];
                }
                else
                {
                    roots[j][k] = matrix[j][k];
                }
            }
        }

        printf("x%d = %g\n", i + 1, det(matrix_size, roots) / detCoefs);
    }
}

void addNumbers(int matrix_size, float (*matrix)[matrix_size], float *outcome)
{
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < (matrix_size + 1); j++)
        {
            if (j == matrix_size)
            {
                do
                {
                    printf("b[%d]: ", i + 1);
                } while ((verify_float(&outcome[i]) == 1));
            }
            else
            {
                do
                {
                    printf("a[%d %d]: ", i + 1, j + 1);
                } while ((verify_float(&matrix[i][j]) == 1));
            }
        }
    }
}

float det(int rows, float matrix[rows][rows])
{
    float determinant = 0;
    float temp[rows - 1][rows - 1];
    if (rows == 1)
    {
        return matrix[0][0];
    }
    // exclude first row and current column
    for (int i = 0; i < rows; i++)
    {
        for (int row = 1; row < rows; row++)
        {
            short shift = 0;
            for (int column = 0; column < rows; column++)
            {
                if (column != i)
                {
                    temp[row - 1][column - shift] = matrix[row][column];
                }
                else
                {
                    shift = 1;
                }
            }
        }
        determinant += matrix[0][i] * pow((-1), i) * det(rows - 1, temp);
    }

    return determinant;
}

void displayMatrix(int rows, float matrix[rows][rows], float outcome[])
{
    printf("\nYou have entered:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j <= rows; j++)
        {
            if (j == rows - 1)
            {
                printf("%g(x%d) = ", matrix[i][j], j + 1);
            }
            else if (j == rows)
            {
                printf("%g\n", outcome[i]);
            }
            else
            {
                printf("%g(x%d) + ", matrix[i][j], j + 1);
            }
        }
    }
}

int verify_int(int *variable_int)
{
    char ch;
    scanf("%d%c", variable_int, &ch);
    if (ch != '\n')
    {
        printf("Invalid number. Try again!\n");
        clear();
        return 1;
    }
    else
    {
        if (*variable_int > 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

int verify_float(float *variable_float)
{
    char ch;
    scanf("%f%c", variable_float, &ch);
    if (ch != '\n')
    {
        printf("Invalid number. Try again!\n");
        clear();
        return 1;
    }
    else
    {
        return 0;
    }
}

void clear()
{
    int character;
    while ((character = getchar()) != '\n' && character != EOF) // end of file
        ;
}