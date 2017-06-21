/*!
 * @brief	�p�[�e�B�N���B
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/particle/tkParticleEmitter.h"
#include "tkEngine/particle/tkParticle.h"
#include "tkEngine/shape/tkShapeVertex.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/random/tkRandom.h"

namespace tkEngine{
	CParticle::CParticle()
	{
		applyForce = CVector3::Zero;
		texture = nullptr;
	}

	CParticle::~CParticle()
	{
		cameraArray.clear();
		primitive.Release();
	}
	void CParticle::Init(CRandom& random, const CCamera& camera, const SParicleEmitParameter& param, const CVector3& emitPosition )
	{
		float halfW = param.w * 0.5f;
		float halfH = param.h * 0.5f;
		
		TK_ASSERT(param.uvTableSize <= ARRAYSIZE(param.uvTable), "uvTable size over!!!");
		CVector4 uv;
		if (param.uvTableSize > 0) {
			uv = param.uvTable[random.GetRandInt() % param.uvTableSize];
		}
		else {
			uv = param.uvTable[0];
		}
		
		SShapeVertex_PT vb[] = {
			{
				-halfW, halfH, 0.0f, 1.0f,
				uv.x, uv.y
			},
			{
				halfW, halfH, 0.0f, 1.0f,
				uv.z, uv.y
			},
			{
				-halfW, -halfH, 0.0f, 1.0f,
				uv.x, uv.w
			},
			{
				halfW, -halfH, 0.0f, 1.0f,
				uv.z, uv.w
			},
			
		};
		short index[]{
			0,1,2,3
		};
		primitive.Create(
			CPrimitive::eTriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vb,
			4,
			eIndexFormat16,
			index
			);
		
		texture = ParticleResources().LoadTextureEx(param.texturePath);
		shaderEffect = EffectManager().LoadEffect("Assets/presetShader/ColorTexPrim.fx");
		this->camera = &camera;
		this->random = &random;
		life = param.life;
		velocity = param.initVelocity;
		//�����x�ɗ�����������B
		velocity.x += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.x;
		velocity.y += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.y;
		velocity.z += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.z;
		position = emitPosition;
		position.x += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.x;
		position.y += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.y;
		position.z += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.z;
		addVelocityRandomMargih = param.addVelocityRandomMargih;
		gravity = param.gravity;
		isFade = param.isFade;
		state = eStateRun;
		initAlpha = param.initAlpha;
		alpha = initAlpha;
		fadeTIme = param.fadeTime;
		isBillboard = param.isBillboard;
		brightness = param.brightness;
		alphaBlendMode = param.alphaBlendMode;
		mulColor = param.mulColor;
		rotateZ = CMath::PI * 2.0f * (float)random.GetRandDouble();
		sizeScale = param.scale;
		size = 1.0f;
	}
	bool CParticle::Start()
	{
		return true;
	}
	void CParticle::Update()
	{
		float deltaTime = 1.0f / 60.0f;
		CVector3 addGrafity = gravity;
		addGrafity.Scale(deltaTime);
		velocity.Add(addGrafity);
		CVector3 force = applyForce;
		force.x += (((float)random->GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.x;
		force.y += (((float)random->GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.y;
		force.z += (((float)random->GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.z;
		force.Scale(deltaTime);
		velocity.Add(force);
		CVector3 addPos = velocity;
		addPos.Scale(deltaTime);
		applyForce = CVector3::Zero;
		position.Add(addPos);

		mWorld = CMatrix::Identity;
		//�g��s��̍쐬
		size *= sizeScale;
		CMatrix scaleMatrix;
		CVector3 scaleVector = CVector3::One;
		scaleVector.Scale(size);
		scaleMatrix.MakeScaling(scaleVector);
		//���s�ړ��s��̍쐬
		CMatrix mTrans;
		mTrans.MakeTranslation(position);
		if (isBillboard) {
			//�r���{�[�h�������s���B
			const CMatrix& mCameraRot = camera->GetCameraRotation();
			CQuaternion qRot;
			qRot.SetRotation(CVector3(mCameraRot.m[2][0], mCameraRot.m[2][1], mCameraRot.m[2][2]), rotateZ);
			CMatrix rot;
			rot.MakeRotationFromQuaternion(qRot);
			//�s��̏�Z
			mWorld.Mul(mWorld, mCameraRot);
			mWorld.Mul(mWorld, scaleMatrix);
			mWorld.Mul(mWorld, rot);
			mWorld.Mul(mWorld, mTrans);
		}
		else {
			mWorld = mTrans;
		}
		timer += deltaTime;
		switch (state) {
		case eStateRun:
			if (timer >= life) {
				if (isFade) {
					state = eStateFadeOut;
					timer = 0.0f;
				}
				else {
					state = eStateDead;
				}
			}
			break;
		case eStateFadeOut: {
			float t = timer / fadeTIme;
			timer += deltaTime;
			alpha = initAlpha + (-initAlpha)*t;
			if (alpha <= 0.0f) {
				alpha = 0.0f;
				state = eStateDead;	//���S�B
			}
		}break;
		case eStateDead:
			GameObjectManager().DeleteGameObject(this);
			break;
		}
		
	}
	void CParticle::Render( CRenderContext& renderContext )
	{
		CMatrix m;
		m.Mul(mWorld, camera->GetViewMatrix());
		m.Mul(m, camera->GetProjectionMatrix());
		renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		switch (alphaBlendMode) {
		case 0:
			renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_SRCALPHA);
			renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_INVSRCALPHA);
			shaderEffect->SetTechnique(renderContext, "ColorTexPrimTrans");
			break;
		case 1:
			renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_ONE);
			renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_ONE);
			shaderEffect->SetTechnique(renderContext, "ColorTexPrimAdd");
			break;
		case 2:
			renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_SRCALPHA);
			renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_INVSRCALPHA);
			shaderEffect->SetTechnique(renderContext, "SoftTransParticle");
			break;
		case 3:
			renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_ONE);
			renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_ONE);
			shaderEffect->SetTechnique(renderContext, "SoftAddParticle");
			break;
		}
		
		shaderEffect->Begin(renderContext);
		shaderEffect->BeginPass(renderContext, 0);
		renderContext.SetRenderState(D3DRS_ZENABLE, TRUE);
		renderContext.SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		shaderEffect->SetValue(renderContext, "g_mWVP", &m, sizeof(CMatrix));
		shaderEffect->SetValue(renderContext, "g_alpha", &alpha, sizeof(alpha));
		shaderEffect->SetValue(renderContext, "g_brightness", &brightness, sizeof(brightness));
		if (texture) {
			shaderEffect->SetTexture(renderContext, "g_texture", texture);
		}
		shaderEffect->SetTexture(renderContext, "g_depthTexture", Dof().GetDepthRenderTarget()->GetTexture());
		shaderEffect->SetValue(renderContext, "g_mulColor", &mulColor, sizeof(mulColor));
		shaderEffect->CommitChanges(renderContext);
		renderContext.SetStreamSource(0, primitive.GetVertexBuffer());
		renderContext.SetIndices(primitive.GetIndexBuffer());
		renderContext.SetVertexDeclaration(primitive.GetVertexDecl());
		renderContext.DrawIndexedPrimitive(&primitive);
		shaderEffect->EndPass(renderContext);
		shaderEffect->End(renderContext);
		renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_ONE);
		renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_ZERO);
		renderContext.SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		renderContext.SetRenderState(D3DRS_ZENABLE, TRUE);
		
	}
	void CParticle::Render(CRenderContext& renderContext, int playerNum)
	{
		CCamera* cam = cameraArray[playerNum];
		if (isBillboard) {
			mWorld = CMatrix::Identity;
			CMatrix scaleMatrix;
			CVector3 scaleVector = CVector3::One;
			scaleVector.Scale(size);
			scaleMatrix.MakeScaling(scaleVector);
			//���s�ړ��s��̍쐬
			CMatrix mTrans;
			mTrans.MakeTranslation(position);
			//�r���{�[�h�������s���B
			const CMatrix& mCameraRot = cam->GetCameraRotation();
			//��]�s��̍쐬
			CQuaternion qRot;
			qRot.SetRotation(CVector3(mCameraRot.m[2][0], mCameraRot.m[2][1], mCameraRot.m[2][2]), rotateZ);
			CMatrix rot;
			rot.MakeRotationFromQuaternion(qRot);
			//�s��̏�Z
			mWorld.Mul(mWorld, scaleMatrix);
			mWorld.Mul(mWorld, mCameraRot);
			mWorld.Mul(mWorld, rot);
			mWorld.Mul(mWorld, mTrans);
		}
		ViewPortParam l_viewPortParam = GetViewSprit().GetSprit(playerNum);
		CVector4 l_uv;
		l_uv.x = l_viewPortParam.x;
		l_uv.y = l_viewPortParam.y;
		float l_Width = Engine().GetScreenWidth() / 2;
		float l_Height = Engine().GetScreenHeight() / 2;
		l_uv.x -= l_Width;
		l_uv.y -= l_Height;

		l_uv.z = l_viewPortParam.width + l_uv.x;
		l_uv.w = l_viewPortParam.height + l_uv.y;

		l_uv.x /= l_Width;
		l_uv.y /= l_Height;
		l_uv.z /= l_Width;
		l_uv.w /= l_Height;
		CMatrix m;
		m.Mul(mWorld, cam->GetViewMatrix());
		m.Mul(m, cam->GetProjectionMatrix());
		renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		switch (alphaBlendMode) {
		case 0:
			renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_SRCALPHA);
			renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_INVSRCALPHA);
			shaderEffect->SetTechnique(renderContext, "ColorTexPrimTrans");
			break;
		case 1:
			renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_ONE);
			renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_ONE);
			shaderEffect->SetTechnique(renderContext, "ColorTexPrimAdd");
			break;
		case 2:
			renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_SRCALPHA);
			renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_INVSRCALPHA);
			shaderEffect->SetTechnique(renderContext, "SoftTransParticle");
			break;
		case 3:
			renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_ONE);
			renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_ONE);
			shaderEffect->SetTechnique(renderContext, "SoftAddParticle");
			break;
		}

		shaderEffect->Begin(renderContext);
		shaderEffect->BeginPass(renderContext, 0);
		renderContext.SetRenderState(D3DRS_ZENABLE, TRUE);
		renderContext.SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		shaderEffect->SetValue(renderContext, "g_mWVP", &m, sizeof(CMatrix));
		shaderEffect->SetValue(renderContext, "g_alpha", &alpha, sizeof(alpha));
		shaderEffect->SetValue(renderContext, "g_brightness", &brightness, sizeof(brightness));
		shaderEffect->SetValue(renderContext, "g_uv", &l_uv, sizeof(l_uv));
		if (texture) {
			shaderEffect->SetTexture(renderContext, "g_texture", texture);
		}
		shaderEffect->SetTexture(renderContext, "g_depthTexture", Dof().GetDepthRenderTarget()->GetTexture());
		shaderEffect->SetValue(renderContext, "g_mulColor", &mulColor, sizeof(mulColor));
		shaderEffect->CommitChanges(renderContext);
		renderContext.SetStreamSource(0, primitive.GetVertexBuffer());
		renderContext.SetIndices(primitive.GetIndexBuffer());
		renderContext.SetVertexDeclaration(primitive.GetVertexDecl());
		renderContext.DrawIndexedPrimitive(&primitive);
		shaderEffect->EndPass(renderContext);
		shaderEffect->End(renderContext);
		renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_ONE);
		renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_ZERO);
		renderContext.SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		renderContext.SetRenderState(D3DRS_ZENABLE, TRUE);

	}
}