/*!
 * @brief	�p�[�e�B�N�������@
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/particle/tkParticleEmitter.h"
#include "tkEngine/particle/tkParticle.h"
#include "tkEngine/shape/tkShapeVertex.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"

using namespace std;
namespace tkEngine{
	CParticleEmitter::CParticleEmitter()
	{
		m_lifeTimer = 0.0f;
	}
	CParticleEmitter::~CParticleEmitter()
	{
		cameraArray.clear();
	}
	void CParticleEmitter::Init(CRandom& random, const CCamera& camera, const SParicleEmitParameter& param, const CVector3& emitPosition )
	{
		this->random = &random;
		this->camera = &camera;
		this->param = param;
		this->emitPosition = emitPosition;
		timer = param.intervalTime;
		m_lifeTimer = param.lifeTime;
	}
	bool CParticleEmitter::Start()
	{
		return true;
	}
	void CParticleEmitter::Update()
	{
		if (timer >= param.intervalTime) {
			//�p�[�e�B�N���𐶐��B
			CParticle* p = GameObjectManager().NewGameObject<CParticle>(2);
			p->Init(*random, *camera, param, emitPosition);
			for (CCamera* cam: cameraArray)
			{
				p->AddCamera(*cam);
			}
			timer = 0.0f;
			particleList.push_back(p);
		}
		timer += 1.0f / 60.0f;
		//remove-erase�C�f�B�I���B
		auto delIt = remove_if(
			particleList.begin(), 
			particleList.end(),
			[](CParticle* p)->bool { return p->IsDead(); }
		);
		particleList.erase(delIt, particleList.end());
		DethCheck();
	}
	/*!
	*@brief	�p�[�e�B�N���ɗ͂�������B
	*@param[in]	applyForce		���������Ɏg�p���闐�������@�B
	*/
	void CParticleEmitter::ApplyForce(const CVector3& applyForce)
	{
		for (auto p : particleList) {
			p->ApplyForce(applyForce);
		}
	}

	void CParticleEmitter::DethCheck()
	{
		m_lifeTimer -= GameTime().GetFrameDeltaTime();
		if (m_lifeTimer < 0.0f)
		{
			DeleteGO(this);
		}
	}
}
