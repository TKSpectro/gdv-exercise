#pragma once

class CFloat4x4; // Forward declaration

class CFloat4 {

public:
	CFloat4();
	CFloat4(const CFloat4& _pOther);
	float Get(int index);
	CFloat4* Set(float values[4]);
	CFloat4 Add(CFloat4* _pOther);			// A = B + C
	CFloat4* AddAndSet(CFloat4* _pOther);	// B += C
	CFloat4 Mul(float _pMultiplier);
	CFloat4* MulAndSet(float _pMultiplier);
	float Dot(CFloat4* _pOther);
	CFloat4 Cross(CFloat4* _pOther);
	CFloat4* CrossAndSet(CFloat4* _pOther);
	float GetLength();
	CFloat4 GetNormalized();
	CFloat4* Normalize();

private:
		/*
		*	m_V[0] => x
		*	m_V[1] => y
		*	m_V[2] => z
		*	m_V[3] => w
		*/
		float m_V[4];
};