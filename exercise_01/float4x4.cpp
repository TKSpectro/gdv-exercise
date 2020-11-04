#include "float4x4.h"
#include "float4.h"

CFloat4x4::CFloat4x4()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(i == j)
			{
				this->m_V[i * 4 + j] = 1;
			}
			else
			{
				this->m_V[i * 4 + j] = 0;
			}
		}
	}
}

CFloat4x4::CFloat4x4(const CFloat4x4& _pOther)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			this->m_V[i * 4 + j] = _pOther.m_V[i * 4 + j];
		}
	}
}

float CFloat4x4::Get(int index)
{
	return this->m_V[index];
}

CFloat4x4* CFloat4x4::Set(float values[16])
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			this->m_V[i * 4 + j] = values[i * 4 + j];
		}
	}
	return this;
}

CFloat4x4 CFloat4x4::Add(CFloat4x4* _pOther)
{
	CFloat4x4 result;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			result.m_V[i * 4 + j] = this->m_V[i * 4 + j] + _pOther->m_V[i * 4 + j];
		}
	}
	return result;
}

CFloat4x4* CFloat4x4::AddAndSet(CFloat4x4* _pOther)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			this->m_V[i * 4 + j] = this->m_V[i * 4 + j] + _pOther->m_V[i * 4 + j];
		}
	}
	return this;
}

CFloat4 CFloat4x4::Mul(CFloat4* _pOther)
{
	CFloat4 result;
	float vectorValues[4];
	for(int i = 0; i < 4; i++)
	{
		vectorValues[i] = 
			_pOther->Get(0) * this->m_V[4 * i + 0] +
			_pOther->Get(1) * this->m_V[4 * i + 1] +
			_pOther->Get(2) * this->m_V[4 * i + 2] +
			_pOther->Get(3) * this->m_V[4 * i + 3];
	}
	result.Set(vectorValues);
	return result;
}

CFloat4x4 CFloat4x4::Mul(CFloat4x4* _pOther)
{
	CFloat4x4 result;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			result.m_V[i * 4 + j] =
				this->m_V[i * 4 + j] * _pOther->m_V[j * 4 + i] +
				this->m_V[i * 4 + j] * _pOther->m_V[j * 4 + i] +
				this->m_V[i * 4 + j] * _pOther->m_V[j * 4 + i] +
				this->m_V[i * 4 + j] * _pOther->m_V[j * 4 + i];
		}
	}
	return result;
}

CFloat4x4* CFloat4x4::MulAndSet(CFloat4x4* _pOther)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			this->m_V[i * 4 + j] =
				this->m_V[i * 4 + j] * _pOther->m_V[j * 4 + i] +
				this->m_V[i * 4 + j] * _pOther->m_V[j * 4 + i] +
				this->m_V[i * 4 + j] * _pOther->m_V[j * 4 + i] +
				this->m_V[i * 4 + j] * _pOther->m_V[j * 4 + i];
		}
	}
	return this;
}
