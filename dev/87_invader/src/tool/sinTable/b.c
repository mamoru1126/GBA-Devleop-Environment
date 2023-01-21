#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    double x, y, a;
    double i;
    
    if((fp=fopen("m_Atntbl.txt","w"))!=NULL){

        fprintf(fp, "short m_Atntbl[] = {\n");
    
        for(i=0; i<64; i++){
            /* �Z�o */
            x = cos(((63 - i + 0.5) / 128) * 3.1415926536);
            y = sin(((63 - i + 0.5) / 128) * 3.1415926536);
            a = (x / y) * 256;

            /* �e�L�X�g�t�@�C����C�`���ŏo�� */
            if(i==0)    fprintf(fp, "\t");
            else        fprintf(fp, "\t");
            fprintf(fp, "%5d,\t\t/* no.%3d */\n", (short)a, (int)i);
        }
        fprintf(fp, "};\n");
        fclose(fp);
    }
    return 0;
}
