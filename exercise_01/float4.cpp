#include "float4.h"
#include <math.h>

CFloat4::CFloat4()
{
	this->m_V[0] = 0;
	this->m_V[1] = 0;
	this->m_V[2] = 0;
	this->m_V[3] = 0;
}

CFloat4::CFloat4(const CFloat4& _pOther)
{
	this->m_V[0] = _pOther.m_V[0];
	this->m_V[1] = _pOther.m_V[1];
	this->m_V[2] = _pOther.m_V[2];
	this->m_V[3] = _pOther.m_V[3];
}

float CFloat4::Get(int index)
{
	return this->m_V[index];
}

CFloat4* CFloat4::Set(float values[4])
{
	this->m_V[0] += values[0];
	this->m_V[1] += values[1];
	this->m_V[2] += values[2];
	this->m_V[3] += values[3];

	return this;
}

CFloat4 CFloat4::Add(CFloat4* _pOther)
{
	CFloat4 result;

	result.m_V[0] = this->m_V[0] + _pOther->m_V[0];
	result.m_V[1] = this->m_V[1] + _pOther->m_V[1];
	result.m_V[2] = this->m_V[2] + _pOther->m_V[2];
	result.m_V[3] = this->m_V[3] + _pOther->m_V[3];

	return result;
}

CFloat4* CFloat4::AddAndSet(CFloat4* _pOther)
{
	this->m_V[0] += _pOther->m_V[0];
	this->m_V[1] += _pOther->m_V[1];
	this->m_V[2] += _pOther->m_V[2];
	this->m_V[3] += _pOther->m_V[3];

	return this;
}

CFloat4 CFloat4::Mul(float _pMultiplier)
{
	CFloat4 result;

	result.m_V[0] = this->m_V[0] * _pMultiplier;
	result.m_V[1] = this->m_V[1] * _pMultiplier;
	result.m_V[2] = this->m_V[2] * _pMultiplier;
	result.m_V[3] = this->m_V[3] * _pMultiplier;

	return result;
}

CFloat4* CFloat4::MulAndSet(float _pMultiplier)
{
	this->m_V[0] *= _pMultiplier;
	this->m_V[1] *= _pMultiplier;
	this->m_V[2] *= _pMultiplier;
	this->m_V[3] *= _pMultiplier;

	return this;
}

float CFloat4::Dot(CFloat4* _pOther)
{
	float result = 0;

	result += this->m_V[0] * _pOther->m_V[0];
	result += this->m_V[1] * _pOther->m_V[1];
	result += this->m_V[2] * _pOther->m_V[2];
	result += this->m_V[3] * _pOther->m_V[3];

	return result;
}

CFloat4 CFloat4::Cross(CFloat4* _pOther)
{
	// TODO 
	// For cross we need 2 other vectors instead of 1
	return CFloat4();
}

CFloat4* CFloat4::CrossAndSet(CFloat4* _pOther)
{
	// TODO
	// For cross we need 2 other vectors instead of 1
	return nullptr;
}

float CFloat4::GetLength()
{
	return sqrt(pow(this->m_V[0], 2) + pow(this->m_V[1], 2) + pow(this->m_V[2], 2) + pow(this->m_V[3], 2));
}

CFloat4 CFloat4::GetNormalized()
{
	CFloat4 result;

	float sum = this->GetLength();

	result = this->Mul(1 / sum);

	return result;
}

CFloat4* CFloat4::Normalize()
{
	float sum = this->GetLength();

	this->MulAndSet(1 / sum);

	return this;
}