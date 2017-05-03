/*!
 * @brief	パーティクル。
 */
#ifndef _TKPARTICLE_H_
#define _TKPARTICLE_H_

namespace tkEngine{
#define PLAYER_NUM 4
	class CRandom;
	class CCamera;
	struct SParicleEmitParameter;
	/*!
	 * @brief	パーティクル。
	 */
	class CParticle : public IGameObject{
		enum eState {
			eStateRun,
			eStateFadeOut,
			eStateDead,
		};
	private:
		CPrimitive		primitive;					//!<プリミティブ。
		CTexture*		texture;					//!<テクスチャ。
		CEffect*		shaderEffect;				//!<シェーダーエフェクト。
		const CCamera*	camera;						//!<カメラ。
		CRandom*		random;						//!<乱数。
		float			life;						//!<ライフ。
		float			timer;						//!<タイマー。
		CVector3		velocity;					//!<速度。
		CVector3		position;					//!<座標。
		CVector3		gravity;					//!<重力。
		float			rotateZ;					//!<Z軸周りの回転。
		float			rotateY;					//!<Y軸周りの回転。
		CMatrix			mWorld;						//!<ワールド行列。
		CVector3		addVelocityRandomMargih;	//!<速度の積分のときのランダム幅。
		bool			isDead;						//!<死亡フラグ。
		bool			isFade;						//!<死ぬときにフェードアウトする？
		float			fadeTIme;					//!<フェードの時間。
		eState			state;						//!<状態。
		float			initAlpha;					//!<初期アルファ。
		float			alpha;						//!<アルファ。
		bool			isBillboard;				//!<ビルボード？
		CVector3		applyForce;					//!<外部から加わる力。
		float			brightness;					//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		int				alphaBlendMode;				//!<0半透明合成、1加算合成。
		CVector3		mulColor;					//!<乗算カラー。
		CCamera*		cameraArray[PLAYER_NUM];
	public:
		CParticle();
		~CParticle();
		void Init(CRandom& random, const CCamera& camera, const SParicleEmitParameter& param, const CVector3& emitPosition);
		bool Start() override ;
		void Update() override;
		void Render( CRenderContext& renderContext ) override;
		void Render(CRenderContext& renderContext, int playerNum)override;

		void SetCamera(CCamera& camera, int playerNum)
		{
			cameraArray[playerNum] = &camera;
		}

		/*!
		*@brief	パーティクルに力を加える。
		*@param[in]	applyForce		乱数生成に使用する乱数生成機。
		*/
		void ApplyForce(const CVector3& applyForce)
		{
			this->applyForce = applyForce;
		}
	};
}

#endif //_TKPARTICLE_H_