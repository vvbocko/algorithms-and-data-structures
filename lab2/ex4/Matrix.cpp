#include <iostream>
#include <vector>
#include <string>

int saddlebackComparisons = 0;
int binaryComparisons = 0;


bool SaddlebackSearch(const std::vector<std::vector<int>>& matrix, int target) 
{
    int rows = matrix.size();
    int columns = matrix[0].size();
    int startRow = 0;
    int startCol = columns - 1;

    while (startRow < rows && startCol >= 0) 
    {
        saddlebackComparisons++;
        if(matrix[startRow][startCol] == target)
        {
            return true;
        }
        
        saddlebackComparisons++;
        if(matrix[startRow][startCol] < target) 
        {
            startRow++;
        }
        else startCol--;
    }
    return false;
}


bool BinarySearchMatrix(const std::vector<std::vector<int>>& matrix, int target) 
{
    int rows = matrix.size();
    int columns = matrix[0].size();

    if(rows > columns) //wysokosc
    {
        for (int i = 0; i < columns; i++) 
        {
            int start = 0;
            int end = rows - 1;
            while (start <= end) 
            {
                binaryComparisons++;
                int mid = start + (end - start) / 2;
                if (matrix[mid][i] == target)
                {
                    return true;
                }
                
                binaryComparisons++;
                if (matrix[mid][i] < target)
                {
                    start = mid + 1;
                }
                else 
                {
                    end = mid - 1;
                }
            }
        }
    }
    else //szerokosc
    {
        for(int i = 0; i < rows; i++)
        {
            int start = 0;
            int end = columns - 1;
            while (start <= end)
            {
                binaryComparisons++;
                int mid = start + (end - start) / 2;

                if(matrix[i][mid] == target) 
                {
                    return true;
                }
                
                binaryComparisons++;
                if(matrix[i][mid] < target)
                {
                    start = mid + 1;
                }
                else end = mid - 1;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) 
{
    if (argc < 3) return 1;
    
    int m = std::stoi(argv[1]);
    int n = std::stoi(argv[2]);

    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));
    for (int i = 0; i < m; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            matrix[i][j] = i * 100000 + j; 
        }
    }

    int target = -1; //najgorszy przypadek

    SaddlebackSearch(matrix, target);
    BinarySearchMatrix(matrix, target);

    std::cout << saddlebackComparisons << " " << binaryComparisons << "\n";
    return 0;
}