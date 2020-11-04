#include "float4.h"
#include "float4x4.h"

#include <iostream>
using namespace std;

CFloat4 createVector()
{
	CFloat4 result;
	float values[4];
	for(int i = 0; i < 4; i++)
	{
		values[i] = i + 1;
	}
	result.Set(values);
	return result;
}

CFloat4x4 createMatrix()
{
	CFloat4x4 result;
	float values[16];
	for(int i = 0; i < 16; i++)
	{
		values[i] = i + 1;
	}
	result.Set(values);

	return result;
}

void outputVector(CFloat4* _pVector)
{
	cout << " | ";
	for(int i = 0; i < 4; i++)
	{
		cout << _pVector->Get(i) << " | ";
	}
	cout << "\n";
}

void outputMatrix(CFloat4x4* _pMatrix)
{
	for(int i = 0; i < 4; i++)
	{
		cout << " | ";
		for(int j = 0; j < 4; j++)
		{
			cout << _pMatrix->Get(i * 4 + j) << " | ";
		}
		cout << "\n";
	}
}

void main()
{
	bool doVector = false;

	if(doVector)
	{
		CFloat4 A;
		CFloat4 B = createVector();
		CFloat4 C = createVector();
		CFloat4 D = createVector();
		CFloat4 E = createVector();
		CFloat4 F = createVector();

		cout << "-------------GET-------------" << "\n";
		outputVector(&A);
		cout << "-------------ADD-------------" << "\n";
		CFloat4 add = A.Add(&A);
		outputVector(&add);
		cout << "-------------ADD AND SET-------------" << "\n";
		B.AddAndSet(&A);
		outputVector(&B);
		cout << "-------------MUL-------------" << "\n";
		float multiplier = 4;
		CFloat4 mul = A.Mul(multiplier);
		cout << "Multiplier " << multiplier << "\n";
		outputVector(&mul);
		cout << "-------------MUL AND SET-------------" << "\n";
		multiplier = 5;
		cout << "Multiplier " << multiplier << "\n";
		C.MulAndSet(multiplier);
		outputVector(&C);
		cout << "-------------DOT-------------" << "\n";
		cout << D.Dot(&A) << "\n";
		cout << "-------------GETLENGTH-------------" << "\n";
		cout << D.GetLength() << "\n";
		cout << "-------------GETNORMALIZED-------------" << "\n";
		CFloat4 norm = A.GetNormalized();
		outputVector(&norm);
		cout << "-------------NORMALIZE-------------" << "\n";
		E.Normalize();
		outputVector(&E);
	}
	else
	{
		CFloat4 Vector = createVector();
		CFloat4x4 A;
		CFloat4x4 helpMatrix = createMatrix();
		CFloat4x4 B = createMatrix();
		CFloat4x4 C = createMatrix();
		CFloat4x4 D = createMatrix();
		CFloat4x4 E = createMatrix();
		CFloat4x4 F = createMatrix();

		cout << "-------------GET-------------" << "\n";
		outputMatrix(&A);
		cout << "-------------ADD-------------" << "\n";
		CFloat4x4 add = helpMatrix.Add(&helpMatrix);
		outputMatrix(&add);
		cout << "-------------ADD AND SET-------------" << "\n";
		B.AddAndSet(&helpMatrix);
		outputMatrix(&B);
		cout << "-------------MUL MATRIX-------------" << "\n";
		CFloat4x4 mul = helpMatrix.Mul(&helpMatrix);
		outputMatrix(&mul);
		cout << "-------------MUL MATRIX AND SET-------------" << "\n";
		C.MulAndSet(&helpMatrix);
		outputMatrix(&C);
		cout << "-------------MUL VECTOR-------------" << "\n";
		CFloat4 mulVector = helpMatrix.Mul(&Vector);
		outputVector(&mulVector);
	}
}