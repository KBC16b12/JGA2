/*!
 * @brief	パーティクルの発生機。
 */

#ifndef _TKPARTICLEEMITTER_H_
#define _TKPARTICLEEMITTER_H_

#include "tkParticle.h"

namespace tkEngine{
	class CCamera;
	class CRandom;
	/*!
	* @brief	パーティクル生成パラメータ
	*/
	struct SParicleEmitParameter {
		//初期化。
		void Init()
		{
			memset(this, 0, sizeof(SParicleEmitParameter));
			initAlpha = 1.0f;
			uvTableSize = 1;
			brightness = 1.0f;
			isBillboard = true;
			mulColor = CVector3::Zero;
			lifeTime = 2.0f;
		}
		const char* texturePath;						//!<テクスチャのファイルパス。
		CVector3	initVelocity;						//!<初速度。
		float		life;								//!<寿命。単位は秒。
		float		intervalTime;						//!<発生時間。単位は秒。
		float		w;									//!<パーティクルの幅。
		float		h;									//!<パーティクルの高さ。
		CVector3	initPositionRandomMargin;			//!<初期位置のランダム幅。
		CVector3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
		CVector3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
		CVector4	uvTable[4];							//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
		int			uvTableSize;						//!<UVテーブルのサイズ。
		CVector3	gravity;							//!<重力。
		bool		isFade;								//!<死ぬときにフェードアウトする？
		float		fadeTime;							//!<フェードする時間。
		float		initAlpha;							//!<初期アルファ値。
		bool		isBillboard;						//!<ビルボード？
		float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		int			alphaBlendMode;						//!<0半透明合成、1加算合成。
		CVector3	mulColor;							//!<乗算カラー。
		float		lifeTime;							//!<パーティクルエミッターの寿命
		float		scale;								//!<拡大倍率。変わらないなら1.0f
		bool		isRotaion;							//!<パーティクルを回転させるか
		int			particleNum;						//!<1フレームに出てくるパーティクルの数
	};
	/*!
	 * @brief	パーティクルの発生機
	 */
	class CParticleEmitter : public IGameObject{
	public:
		
		/*!
		 * @brief	コンストラクタ。
		 */
		CParticleEmitter();
		/*!
		 * @brief	デストラクタ。
		 */
		~CParticleEmitter();
		/*!
		 *@brief	初期化。
		 *@param[in]	random		乱数生成に使用する乱数生成機。
		 *@param[in]	camera		パーティクルの描画で使用するカメラ。
		 *@param[in]	param		パーティクル生成用のパラメータ。
		 *@param[in]	emitPosition	エミッターの座標。
		 */
		void Init(CRandom& random, const CCamera& camera, const SParicleEmitParameter& param, const CVector3& emitPosition, std::vector<CCamera*>	cameraArray);
		bool Start() override ;
		void Update() override;
		
		void DeathCheck();
		/*!
		*@brief	パーティクルに力を加える。
		*@param[in]	applyForce		乱数生成に使用する乱数生成機。
		*/
		void ApplyForce(const CVector3& applyForce);

	private:
		float					timer;			//!<タイマー
		CRandom*				random;			//!<乱数生成機。
		const CCamera*			camera;			//!<カメラ。
		SParicleEmitParameter	param;			//!<パラメータ。
		CVector3				emitPosition;	//!<エミッターの座標。
		std::list<CParticle*>	particleList;	//!<パーティクルのリスト。
		std::list<CParticle*>	deleteParticleList;	//!<削除されたパーティクルのリスト。
		float					m_lifeTimer;	//!<エミッターの寿命
		std::vector<CCamera*>	cameraVector;
		int						m_particleNum;
	};
}

#endif // _TKPARTICLEEMITTER_H_