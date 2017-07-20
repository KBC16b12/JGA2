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
		m_particleNum = 1;
	}
	CParticleEmitter::~CParticleEmitter()
	{
		cameraVector.clear();
	}

	void CParticleEmitter::Init(CRandom& random, const CCamera& camera, const SParicleEmitParameter& param, const CVector3& emitPosition , std::vector<CCamera*> cameravector)
	{
		this->random = &random;
		this->camera = &camera;
		this->param = param;
		this->emitPosition = emitPosition;
		timer = param.intervalTime;
		m_lifeTimer = param.lifeTime;
		cameraVector = cameravector;
		m_particleNum = param.particleNum;
	}

	bool CParticleEmitter::Start()
	{
		return true;
	}

	void CParticleEmitter::Update()
	{
		if (timer >= param.intervalTime) {
			for (int i = 0; i < m_particleNum; i++)
			{
				//�p�[�e�B�N���𐶐��B
				CParticle* p = GameObjectManager().NewGameObject<CParticle>(2);
				p->Init(*random, *camera, param, emitPosition);
				for (CCamera* cam : cameraVector)
				{
					p->AddCamera(*cam);
				}
				particleList.push_back(p);
			}
			timer = 0.0f;
		}
		timer += 1.0f / 60.0f;
		//remove-erase�C�f�B�I���B
		auto delIt = remove_if(
			particleList.begin(), 
			particleList.end(),
			[](CParticle* p)->bool { return p->IsDead(); }
		);
		particleList.erase(delIt, particleList.end());
		DeathCheck();
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

	void CParticleEmitter::DeathCheck()
	{
		m_lifeTimer -= GameTime().GetFrameDeltaTime();
		if (m_lifeTimer < 0.0f)
		{
			DeleteGO(this);
		}
	}
}
