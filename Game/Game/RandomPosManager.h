#pragma once

class RandomPosManager
{
public:
	RandomPosManager();

	~RandomPosManager();

	void AddPlayerPos(CVector3 position)
	{
		m_playersPos.push_back(position);
	}

private:
	std::vector<CVector3> m_playersPos;
	std::vector<CVector3> m_itemPos;
};

