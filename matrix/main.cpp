#include<iostream>
#include"matlib.h" 

// Transpose matrix dimension
// T(mat1) = mat2
#define mat1row 8
#define mat1col 7

// Multiplication matrix dimension
// mat1 * mat2 = mat3
#define matarow 4 
#define matacol 5
#define matbcol 6

int main()
{

	int mat[mat1row][mat1col], mat_tp[mat1col][mat1row];
	int mat1[matarow][matacol], mat2[matacol][matbcol], mat_mul[matarow][matbcol];
	
	RandomFillMatrix<mat1row,mat1col>(mat);
	RandomFillMatrix<matarow,matacol>(mat1);
	RandomFillMatrix<matacol,matbcol>(mat2);
	std::cout<<"we are here"<<std::endl;
	int tpres = MatTranspose<mat1row,mat1col>(mat, mat_tp);
	int mpres = MatMultiplication<matarow, matacol, matbcol>(mat1, mat2, mat_mul);	

	if(tpres)
	{
		std::cout<<"Original Matrix"<<std::endl;
		MatDisplay<mat1row,mat1col>(mat);
		std::cout<<"Transposed Matrix"<<std::endl;
		MatDisplay<mat1col,mat1row>(mat_tp);		
	}
	else
	{
		std::cout<<"error while tranposing matrix, check input"<<std::endl;
	}

	if(mpres)
	{
		std::cout<<"Matrix 1"<<std::endl;
		MatDisplay<matarow,matacol>(mat1);
		std::cout<<"Matrix 2"<<std::endl;
		MatDisplay<matacol,matbcol>(mat2);
		std::cout<<"Matrix Product"<<std::endl;
		MatDisplay<matarow,matbcol>(mat_mul);		
	}
	else
	{
		std::cout<<"error while Multiplying matrices, check input"<<std::endl;
	}

	
	return(0);
}