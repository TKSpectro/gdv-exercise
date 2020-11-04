#pragma once

class CFloat4;

class CFloat4x4
{
public:
	CFloat4x4();
	CFloat4x4(const CFloat4x4& _pOther);
	float Get(int index);
	CFloat4x4* Set(float values[16]);
	CFloat4x4 Add(CFloat4x4* _pOther);			// A = B + C
	CFloat4x4* AddAndSet(CFloat4x4* _pOther);	// B += C
	// Multiply with a vector
	CFloat4 Mul(CFloat4* _pOther);
	// Multiply with a matrix
	CFloat4x4 Mul(CFloat4x4* _pOther);
	CFloat4x4* MulAndSet(CFloat4x4* _pOther);
private:
	float m_V[4 * 4];

};