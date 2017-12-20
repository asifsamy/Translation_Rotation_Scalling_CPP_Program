#include<stdio.h>
#include <cctype>
#include <conio.h>
#include <windows.h>
#include<math.h>

#define PI 3.14159265

float tr[100][100], sc[100][10], rtn[100][100], pnt[100][100], res_tr[100][100];
int p_no;
FILE *f = fopen("file2.txt", "w");

void Translate(float dx, float dy)
{
    int i, j, k;
    float sum;

    tr[0][0] = 1; tr[0][1] = 0; tr[0][2] = dx;
    tr[1][0] = 0; tr[1][1] = 1; tr[1][2] = dy;
    tr[2][0] = 0; tr[2][1] = 0; tr[2][2] = 1;

    for (i=0; i<3; i++)
    {
        for (j=0; j<p_no; j++)
        {
            sum=0;
            for (k=0; k<3; k++)
            {
                sum = sum + (tr[i][k]*pnt[k][j]);
            }
            res_tr[i][j]=sum;
        }
    }

}

void Scalling(float sx, float sy)
{
    int i, j, k;
    float fx, fy, sum, tmp[100][100], tmp2[100][100];
    printf("\nEnter fixed point of x: ");
    scanf("%f", &fx);
    printf("\nEnter fixed point of y: ");
    scanf("%f", &fy);

    tr[0][0] = 1; tr[0][1] = 0; tr[0][2] = -fx;
    tr[1][0] = 0; tr[1][1] = 1; tr[1][2] = -fy;
    tr[2][0] = 0; tr[2][1] = 0; tr[2][2] = 1;

    sc[0][0] = sx; sc[0][1] = 0;  sc[0][2] = 0;
    sc[1][0] = 0;  sc[1][1] = sy; sc[1][2] = 0;
    sc[2][0] = 0;  sc[2][1] = 0;  sc[2][2] = 1;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            sum=0;
            for (k=0; k<3; k++)
            {
                sum = sum + (sc[i][k]*tr[k][j]);
            }
            tmp[i][j]=sum;
        }
    }

    tr[0][0] = 1; tr[0][1] = 0; tr[0][2] = fx;
    tr[1][0] = 0; tr[1][1] = 1; tr[1][2] = fy;
    tr[2][0] = 0; tr[2][1] = 0; tr[2][2] = 1;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            sum=0;
            for (k=0; k<3; k++)
            {
                sum = sum + (tr[i][k]*tmp[k][j]);
            }
            tmp2[i][j]=sum;
        }
    }

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            sum=0;
            for (k=0; k<3; k++)
            {
                sum = sum + (tmp2[i][k]*pnt[k][j]);
            }
            res_tr[i][j]=sum;
        }
    }

}

void Rotation(float r)
{
    int i, j, k;
    float fx, fy, degree, sum, tmp[100][100], tmp2[100][100];
    printf("\nEnter fixed point of x: ");
    scanf("%f", &fx);
    printf("\nEnter fixed point of y: ");
    scanf("%f", &fy);

    tr[0][0] = 1; tr[0][1] = 0; tr[0][2] = fx;
    tr[1][0] = 0; tr[1][1] = 1; tr[1][2] = fy;
    tr[2][0] = 0; tr[2][1] = 0; tr[2][2] = 1;

    degree = PI / 180.0;

    rtn[0][0] = cos(r*degree); rtn[0][1] = -sin(r*degree); rtn[0][2] = 0;
    rtn[1][0] = sin(r*degree); rtn[1][1] = cos(r*degree);  rtn[1][2] = 0;
    rtn[2][0] = 0;             rtn[2][1] = 0;              rtn[2][2] = 1;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            sum=0;
            for (k=0; k<3; k++)
            {
                sum = sum + (tr[i][k]*rtn[k][j]);
            }
            tmp[i][j]=sum;
        }
    }

    tr[0][0] = 1; tr[0][1] = 0; tr[0][2] = -fx;
    tr[1][0] = 0; tr[1][1] = 1; tr[1][2] = -fy;
    tr[2][0] = 0; tr[2][1] = 0; tr[2][2] = 1;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            sum=0;
            for (k=0; k<3; k++)
            {
                sum = sum + (tmp[i][k]*tr[k][j]);
            }
            tmp2[i][j]=sum;
        }
    }

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            sum=0;
            for (k=0; k<3; k++)
            {
                sum = sum + (tmp2[i][k]*pnt[k][j]);
            }
            res_tr[i][j]=sum;
        }
    }

}

void showResult()
{
    int i, j, k;
    for(i=0; i<3; i++)
    {
        for(j=0; j<p_no; j++)
        {
            if(j==0)
            {
                fprintf(f, "\nx%d = %f", i+1, res_tr[j][i]);
                //fprintf(f, "\n(x%d, y%d) = (%d", j+1, j+1, res_tr[i][j]);
            }
            else if(j==1)
            {
                fprintf(f, "\ny%d = %f", i+1, res_tr[j][i]);
                //fprintf(f, ", %d)", res_tr[i][j]);
            }
        }
        fprintf(f, "\n");

    }
    printf("\nSuccess!\nCheck the file....\n");
}

int main()

{

    int i, j, key;
    float px, py, r;
    printf("\n\n************TRANSFORMATION-2D***************\n\n");
    printf("\nEnter the total no. of points of any object: ");
    scanf("%d", &p_no);

    printf("\nEnter the points: ");
    for(i=0; i<3; i++)
    {
        for(j=0; j<p_no; j++)
        {
            if(j==0)
            {
                printf("\nx%d: ",i+1);
                scanf("%f", &pnt[j][i]);
            }
            else if(j==1)
            {
                printf("\ny%d: ",i+1);
                scanf("%f", &pnt[j][i]);
            }
            else
            {
                pnt[j][i] = 1;
            }

        }

    }

    printf("\n\nWhat do you Want??");
    printf("\n\t01. Translation");
    printf("\n\t02. Scalling");
    printf("\n\t03. Rotation");

    printf("\n\nSelect Your Option (1-3): ");
    scanf("%d", &key);

    switch(key)
    {
    case 1:
        printf("\nEnter distance from x axis: ");
        scanf("%f", &px);
        printf("\nEnter distance from y axis: ");
        scanf("%f", &py);
        Translate(px, py);

        if (f == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
        else
        {
            showResult();
        }
        break;

    case 2:
        printf("\nEnter size from x axis: ");
        scanf("%f", &px);
        printf("\nEnter size from y axis: ");
        scanf("%f", &py);
        Scalling(px, py);

        if (f == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
        else
        {
            showResult();
        }
        break;

    case 3:
        printf("\nEnter the degree of rotation: ");
        scanf("%f", &r);
        Rotation(r);

        if (f == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
        else
        {
            showResult();
        }
        break;

    }


    return 0;
}


