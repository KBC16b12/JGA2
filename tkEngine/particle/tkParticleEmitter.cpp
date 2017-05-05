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
		m_isDelete = false;
		m_isDeth = false;
	}
	CParticleEmitter::~CParticleEmitter()
	{
	}
	void CParticleEmitter::Init(CRandom& random, const CCamera& camera, const SParicleEmitParameter& param, const CVector3& emitPosition )
	{
		this->random = &random;
		this->camera = &camera;
		this->param = param;
		this->emitPosition = emitPosition;
		timer = param.intervalTime;
	}
	bool CParticleEmitter::Start()
	{
		return true;
	}
	void CParticleEmitter::Update()
	{
		if (timer >= param.intervalTime && !m_isDeth) {
			//�p�[�e�B�N���𐶐��B
			CParticle* p = GameObjectManager().NewGameObject<CParticle>(0);
			p->Init(*random, *camera, param, emitPosition);
			for (int i = 0;i < PLAYER_NUM;i++)
			{
				p->SetCamera(*cameraArray[i], i);
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
	void CParticleEmitter::Render( CRenderContext& renderContext )
	{
		
	}

	void CParticleEmitter::Render(CRenderContext& renderContext, int playerNum)
	{
		for (CParticle *particle : particleList)
		{
			particle->Render(renderContext, playerNum);
		}
	}

	void CParticleEmitter::DethCheck()
	{
		m_lifeTimer += GameTime().GetFrameDeltaTime();
		if (0.5f < m_lifeTimer)
		{
			m_isDeth = true;
		}
		if (particleList.empty())
		{
			m_isDelete = true;
		}
	}
}
