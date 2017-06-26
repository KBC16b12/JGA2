#pragma once

namespace Status
{
	enum RunStat
	{
		enFadeIn,
		enRun,
		enFadeOut
	};

	enum SceneData
	{
		enGame,
		enJoin,
		enMenu,
		enResult,
		enRanking,
		enWait,
		enTitle,
		enSolo,
		enChar
	};

	struct SMapInfo 
	{
		const char*	s_modelName;
		CVector3	s_position;
		CQuaternion	s_rotation;
	};

	enum CharData 
	{
		enChar001,
		enChar002,
	};

	struct JoinData
	{
		ULONG		s_address;
		CharData	s_char;
	};
};