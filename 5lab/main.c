#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
double func(double x)
{
    double f;
    f=2*x+1;
    return f;
}

void memory(double ***mass,int n)
{
    *mass=(double**)calloc(n,sizeof(double)); //Динамічне виділення пам'яті в C
    for (int i=0; i<n; i++)
    {
        (*mass)[i]=(double*)calloc(2,sizeof(double));
        if ((*mass)[i]==NULL) exit(1);
    }
}
void fill(double ***mass,int n,double x1,double delta)
{
    for (int i=0; i<n; i++)
    {
        (*mass)[i][0]=x1;  // масив оперує двома рядками і динамічно їх змінює
        (*mass)[i][1]=func(x1);
        x1+=delta;
    }
}
int main()
{
   double x1,x2,delta;
   double **mass=NULL;
   char s[10];
   int n;
   printf("if data put in file press any key...");
   getch();
   printf("\r                                    \r"); // повертає курсор на початок рядка
   FILE *input=fopen("input.txt","r"); // режим зчитування даних з файлу

    fscanf(input,"%s",&s);
   fscanf(input,"%lf%lf%d%lf",&x1,&x2,&n,&delta);
   fclose(input);

  printf("%s", s);

   if (n==0) n=(x2-x1+delta)/delta; else delta=(x2-x1)/(n-1);
   memory(&mass,n);
   fill(&mass,n,x1,delta);
   FILE *resulttxt=fopen("result.txt","w"); // створює файл для запису (по замовчуванню відкриває як текстовий)


   if (resulttxt==NULL) {exit(1);}
   fprintf(resulttxt,"Klymenko Maksym, RE-11 \n");
   fprintf(resulttxt,"number of rows in table is %d\n",n);

   for (int i=0; i<n; i++)
   {
        fprintf(resulttxt,"+-----+--------------------+-------------------------+\n");
        fprintf(resulttxt,"|%5.0d|%20.2lf|%25.2lf|\n",(i+1),mass[i][0],mass[i][1]); // i starts from 0
   }
    fprintf(resulttxt,"+-----+--------------------+-------------------------+\n");
   fclose(resulttxt);

   FILE *resultbin=fopen("result.bin","wb"); // створює двійковий файл для запису.
   if (resultbin==NULL) {exit(1);}

   fwrite(&n,sizeof(int),1,resultbin);
   for (int i=0; i<n; i++)
   {
      fwrite(&mass[i][0],sizeof(double),1,resultbin);
      fwrite(&mass[i][1],sizeof(double),1,resultbin);
   }
    fclose(resultbin);

   printf("Klymenko , RE-11\n");
   printf("number of rows in table is %d\n",n);
   for (int i=0; i<54; i++)
      printf("*");
   printf("\n*  N  *          X         *           F(x)          *\n");
   for (int i=0; i<54; i++)
      printf("*");
   printf("\n");
   for (int i=0; i<2*n; i++)
   {
      if (i%2==0) printf("+-----+--------------------+-------------------------+\n");
      else printf("|%5.0d|%20.2lf|%25.2lf|\n",(i+1)/2,mass[i/2][0],mass[i/2][1]); // бо і насправді вдвічі менше і рахунок починається не з нуля
      if (i%20==0 && i>0) { printf("press any key to continue...");
                                                  getch();
                                                  printf("\r"); }
   }
   printf("+-----+--------------------+-------------------------+\n");
   return 0;
}
