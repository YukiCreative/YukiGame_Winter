#include "MapImageStore.h"
#include <DxLib.h>

namespace
{
	constexpr int kChipSize = 16;
	// �J��Ԃ��������Ăق�������萔�ŏ����܂�
	constexpr int kWidthChipNum = 12;
	constexpr int kHeightChipNum = 14;
}

MapImageStore::MapImageStore()
{
	// �}�b�v�`�b�v�̉摜��ǂ�ŁA�����16x16�ɕ�������������
	// ������n���h���͔z��ɓ����
	m_sourceHandle = LoadGraph("Image/Water+.png");
	for (int y = 0; y < kHeightChipNum; ++y)
	{
		for (int x = 0; x < kWidthChipNum; ++x)
		{
			int index = kWidthChipNum * y + x;
			m_imageArray[index] = 
				DerivationGraph(kChipSize * x, kChipSize * y, kChipSize, kChipSize, m_sourceHandle);
		}
	}
}

MapImageStore::~MapImageStore()
{
	// �摜�̏���
	DeleteGraph(m_sourceHandle);
	for (const auto& handle : m_imageArray)
	{
		// ����ł�����͂�
		DeleteGraph(handle);
	}
}

MapImageStore& MapImageStore::GetInstance()
{
	static MapImageStore instance;
	return instance;
}

int MapImageStore::GetGraph(int id)
{
	return m_imageArray[id];
}