#include "stdafx.h"
#include "Bullet.h"
#include "../Camera/GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"
#include "../Player/Weapon.h"


Bullet::Bullet()
{
	m_position = CVector3::Zero;
	m_moveSpeed = CVector3::Zero;
	m_lifeTime = 0.0f;
}


Bullet::~Bullet()
{
}

void Bullet::Init(CVector3 position, CVector3 movespeed, int playerNum, CVector3 ambientLight)
{
	//�ǂ̃v���C���[���ł����̂��̔ԍ����蓖��
	m_playerNum = playerNum;
	//���W�̏�����
	m_position = position;
	CVector3 l_addPosition = movespeed;
	l_addPosition.Cross(CVector3::AxisY);
	l_addPosition.Scale(-1.3f);
	l_addPosition.y -= 0.8f;
	m_position.Add(l_addPosition);

	m_moveSpeed = movespeed;
	//�e�̈ړ������Ɣ��ˈʒu�̒���
	m_moveSpeed.Normalize();
	m_moveSpeed.Scale(100.0f);
	m_moveSpeed.Subtract(m_moveSpeed, l_addPosition);
	m_moveSpeed.Normalize();
	l_addPosition = m_moveSpeed;
	m_moveSpeed.Scale(50.0f);
	l_addPosition.Scale(2.5f);
	m_position.Add(l_addPosition);

	//characterController�̏�����
	m_characterController.Init(0.2f, 0.3f, m_position);
	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.SetGravity(0.0f);
	CVector3 l_ambientLight = ambientLight;
	l_ambientLight.Scale(1.5f);
	m_light = g_defaultLight;
	m_light.SetAmbinetLight(l_ambientLight);
}

bool Bullet::Start()
{
	SkinModelDataResources().Load(m_modelData, "Assets/modelData/Bullet.X", NULL, false, 1);
	m_skinModel.Init(m_modelData.GetBody());
	m_skinModel.SetLight(&m_light);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetTechnique(enTecShaderHandle_Toon);
	return true;
}

void Bullet::Update()
{
	if(g_gameScene == nullptr)
	{
		DeleteGO(this);
		return;
	}
	Move();
	DeathCheck();
	m_skinModel.Update(m_position, CQuaternion::Identity, CVector3::One);
	m_lifeTime += GameTime().GetFrameDeltaTime();
}

void Bullet::DeathCheck()
{
	float l_playerRadius = 5.0f;
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		Player *l_player = g_gameScene->GetPlayer(i);
		CVector3 l_distance = l_player->GetPosition();
		l_distance.Subtract(m_position);
		if (m_playerNum != i)
		{
			//�v���C���[�ɓ���������
			if (l_distance.Length() < l_playerRadius && l_player->IsActive())
			{
				DeleteGO(this);
				PlayerDamage(l_player);
				break;
			}
		}
		else
		{
			//�e��ł����v���C���[�Ƃ�����x����Ă���΃I�u�W�F�N�g�ƏՓ˂��ď���
			if (m_characterController.IsCollision() || 40.0f < m_lifeTime)
			{
				DeleteGO(this);
				break;
			}
		}
	}

}

void Bullet::Move()
{
	m_moveSpeed.y = m_characterController.GetMoveSpeed().y;
	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.Execute(GameTime().GetFrameDeltaTime());
	m_position = m_characterController.GetPosition();
}

void Bullet::PlayerDamage(Player *player)
{
	player->Damage(m_playerNum, BULLET_DAMAGE, m_position);
}

void Bullet::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext, g_gameCamera[0]->GetViewMatrix(), g_gameCamera[0]->GetProjectionMatrix());
}

void Bullet::Render(CRenderContext& renderContext, int playernum)
{
	m_skinModel.Draw(renderContext, g_gameCamera[playernum]->GetViewMatrix(), g_gameCamera[playernum]->GetProjectionMatrix());
}

