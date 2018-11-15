#include "e_math.h"
#include <time.h> 
#include <fstream>

using namespace e_std;

const std::string LOG_NAME = "logs";
const std::string VEC_NAME = "vectors";
const std::string MAT_NAME = "matrices";


void writeToFile(const std::string& logName, const std::string& line)
{
    std::ofstream ofs;
    std::string fileName = logName + ".txt";

    ofs.open (fileName, std::ofstream::out | std::ofstream::app);
    ofs << line;
    ofs.close();
}

void checkMax(int* min, int* max)
{
    if(*min > *max)
    {
        int temp = *min;
        *min = *max;
        *max = temp;

        println("Maximum is less than Minimum.\nSwitching...");
    }   
}

int main(int argc, char* argv[])
{
    srand (time(NULL));

    short vector;
    int rangeMin;
    int rangeMax;
    int dimension;
    int rows;
    int cols;
    int num;
    int loop = 1;

    do
    {
        if(loop == 1)
        {
            vector = loopAccept("Vector(1) or Matrix(0)?", " ", NULL, ACCEPT_INT);
            rangeMin = loopAccept("Minimum Value of a Component?", " ", NULL, ACCEPT_INT);
            rangeMax = loopAccept("Maximum Value of a Component?", " ", NULL, ACCEPT_INT);
            num = loopAccept("Number to generate?", " ", NULL, ACCEPT_INT);

            if(num <= 0) num = 1;
        }

        checkMax(&rangeMin, &rangeMax);

        if(vector == TRUE)
        {
            if(loop == 1) dimension = loopAccept("Dimension?", " ", NULL, ACCEPT_INT);
            bool vector3d = dimension == 3 ? true : false; //loopAccept("?", " ", NULL, ACCEPT_INT);

            int vec[dimension];

            for(int n = 0; n < num; n++)
            {
                printf("Vector %dD: [", dimension);

                char line[100]; 
                sprintf(line, "Vector %dD: [", dimension);
                writeToFile(VEC_NAME, line);
                writeToFile(LOG_NAME, line);

                for(int i = 0; i < dimension; i++)
                {
                    vec[i] = randInt(rangeMin, rangeMax);
                    printf(" %d ", vec[i]);
                    sprintf(line, " %d ", vec[i]);
                    writeToFile(VEC_NAME, line);
                    writeToFile(LOG_NAME, line);
                }

                sprintf(line, "]\n");
                writeToFile(VEC_NAME, line);
                writeToFile(LOG_NAME, line);
                printf(" ]\n");
            }

            if(vector3d && num == 1)
            {
                e_math::vec3d_t vec3d(vec[0], vec[1], vec[2]);
            }
        
        }
        else
        {
            if(loop == 1)
            {
                rows = loopAccept("Dimension?", " ", NULL, ACCEPT_INT);
                cols = loopAccept("Dimension?", " ", NULL, ACCEPT_INT);
            }

            bool square3d = ((rows == cols) && (rows == 3)) ? true : false;

            int mat[rows][cols];

            for(int n = 0; n < num; n++)
            {
                printf("Matrix %dx%d: \n", rows, cols);

                char line[100]; 
                sprintf(line, "Matrix %dx%d: \n", rows, cols);
                writeToFile(MAT_NAME, line);
                writeToFile(LOG_NAME, line);

                for(int y = 0; y < rows; y++)
                {
                    printf("[");
                    sprintf(line, "[");
                    writeToFile(MAT_NAME, line);
                    writeToFile(LOG_NAME, line);

                    for(int x = 0; x < cols; x++)
                    {
                        mat[y][x] = randInt(rangeMin, rangeMax);
                        printf(" %d ", mat[y][x]);
                        sprintf(line, " %d ", mat[y][x]);
                        writeToFile(MAT_NAME, line);
                        writeToFile(LOG_NAME, line);
                    }

                    sprintf(line, "]\n");
                    writeToFile(MAT_NAME, line);
                    writeToFile(LOG_NAME, line);
                    printf("]\n");
                }
            }
            //printf(" ]\n");

            if(square3d && num == 1)
            {
                e_math::mat3d_t mat3d(mat[0][0], mat[0][1], mat[0][2],
                                      mat[1][0], mat[1][1], mat[1][2],
                                      mat[2][0], mat[2][1], mat[2][2]);
            }
        }


        loop = acceptInt("Waiting...\n(0 to Exit)\n(1 to Repeat)\n(2 to Repeat with same values)");  
    }
    while(loop > 0);

    return 0;
}
