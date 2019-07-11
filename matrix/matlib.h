#include<cstdlib>
#include<thread>

template<int rows, int cols>
void RandomFillMatrix(int mat[rows][cols])
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
			mat[i][j] = rand()%5;
	}
}

template<int rows, int cols>
void ZeroFillMatrix(int mat[rows][cols])
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
			mat[i][j] = 0;
	}
}

void ThreadRangeCreator(int range, int* rng_str_arr)
{
	int ptn = (int)(range/4);
	for(int i=0;i<4;i++)
	{
		rng_str_arr[2*i]   = ptn*i;
		rng_str_arr[2*i+1] = ptn*(i+1);
	}
	rng_str_arr[7]=range;
}

template <int rows, int cols>
void MatDisplay(int mat[rows][cols])
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			std::cout<<mat[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"---------------------"<<std::endl;
}

template <int rows, int cols>
void MaTPThread(int mat1[rows][cols], int mat2[cols][rows], int rowst, int rowed)
{
	for(int i=rowst;i<rowed;i++)
	{
		for(int j=0;j<cols;j++)
		{
			mat2[j][i] = mat1[i][j];
		}
	}
}

template <int rows, int cols>
int MatTranspose(int mat1[rows][cols], int mat2[cols][rows])
{
	try
	{
		if(!(mat1 && mat2))
		{
			throw -1;
		}
		std::thread tds[4];
		int ranges[7];
		ThreadRangeCreator(rows, ranges);
		for(int i=0;i<4;i++)
		{
			tds[i] = std::thread(MaTPThread<rows, cols>, mat1, mat2, ranges[2*i], ranges[2*i+1]);
		}
		for(int i=0;i<4;i++)
		{
			tds[i].join();
		}		
		return 1;
	}
	catch (const std::exception& ex) {
	    return -1;
	} catch (const std::string& ex) {
	    std::cout<<ex<<std::endl;
	    return -1;
	} catch(int param) {
		std::cout<<"NULL address received"<<std::endl;
	} catch (...) {
	    return -1;
	}

}

template<int row1, int col1, int col2>
void MMulThread(int mat1[row1][col1], int mat2[col1][col2], int mat3[row1][col2], int rowst, int rowed)
{
	for(int i=rowst;i<rowed;i++)
	{
		for(int j=0;j<col2;j++)
		{
			for(int k=0;k<col1;k++)
			{
				mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}

template<int row1, int col1, int col2>
int MatMultiplication(int mat1[row1][col1], int mat2[col1][col2], int mat3[row1][col2])
{
	try
	{
		if(!(mat1 && mat2))
		{
			throw -1;
		}
		std::thread tds[4];
		int ranges[7];
		ThreadRangeCreator(row1, ranges);
		ZeroFillMatrix<row1, col2>(mat3);
		for(int i=0;i<4;i++)
		{
			tds[i] = std::thread(MMulThread<row1, col1, col2>, mat1, mat2, mat3, ranges[2*i], ranges[2*i+1]);
		}
		for(int i=0;i<4;i++)
		{
			tds[i].join();
		}
		return 1;		
	}
	catch (const std::exception& ex) {
	    return -1;
	} catch (const std::string& ex) {
	    std::cout<<ex<<std::endl;
	    return -1;
	} catch(int param) {
		std::cout<<"NULL address received"<<std::endl;
	} catch (...) {
	    return -1;
	}

}