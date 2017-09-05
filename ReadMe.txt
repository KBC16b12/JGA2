実行ファイル
JGA2/exe/Game.exe

動画ファイル
JGA2/movie/movie.mp4

プロジェクト
JGA2/Game/Game.sln

プロジェクトのソースコード

・Game
	・9割がた藤井雄稀が書きました。

・tkEngine(学校のライブラリ)

	・追加したファイル
		・ViewPortSprit/tkViewPortSprit.h
		・ViewPortSprit/tkViewPortSprit.cpp
		・理由
		・ゲームの仕様で画面分割する必要があり
		　Gameを変えるよりエンジン部分を変えた方が楽だったからです。
		・描画してる部分のコードは
		　元々あったGameObjectManagerからコピー＆ペーストしたものをif文で分けただけです。
		
		・graphics/tkShadeCommon.h
		・理由
		・シェーダーのテクニックをGame側から簡単に変えれるように、
　　　　　　　　　CSkinModelやCSkinModelDataなどでテクニックのenumを共有したかったため専用のヘッダーを作成しました。
		・中に書いてあるenumはもともとエンジンのコードをコピー＆ペーストしたもので、
		　そこにゲームで使う新しいテクニックを増やしていきました。

		
	・改造したファイル
		・character/tkCharacterController.h
		・character/tkCharacterController.cpp
		・理由
		・反射ベクトルを求める必要が出てきたので、
		　Execute関数が衝突したときに壁の法線を返すようにしました。

		・gameObject/tkGameObject.h
		・理由
		・画面分割に対応させるため画面分割用の描画関数をオブジェクトの基底クラスに追加しました。
		
		・gameObject/tkGameObjectManager.h
		・gameObject/tkgameobjectmanager.cpp
		・理由
		・画面分割用の描画をするために画面分割用のクラスのインスタンスを持たせて、
		　描画の時だけオブジェクトのリストを渡すようにしました。

		・gameObject/tkSkinModelMaterial.h
		・gameObject/tkSkinModelMaterial.cpp
		・理由
		・トゥーンなどの新しいテクニックを追加したかったためです。

		・graphics/postEffect/tkBloomRender.cpp
		・理由
		・m_isEnableが初期化されておらず不具合が発生したため初期化処理を追加しました。

		
		・graphics/tkSkinModel.h
		・graphics/tkSkinModelData.h
		・理由
		・シェーダーテクニックを変えるためのセッター関数を作成しました。


		・graphics/sprite/tkSprite.h
		・graphics/sprite/tkSprite.cpp
		・理由
		・スプライト用のシェーダーテクニックを新しく作ったので、
		　テクニックを変えるためにテクニックを保持する変数とセッター関数を作りました。		

		・particle/tkParticle.h
		・particle/tkParticle.cpp
		・理由
		・画面分割用の描画処理が必要だったので、
		　関数を追加してそこでカメラ毎のビルボード処理をしました。
		・拡大率をCParticleEmitterからもらいサイズを大きくできるようにしました。

		・particle/tkParticleEmitter.h
		・particle/tkParticleEmitter.cpp
		・理由
		・インスタンスを生成したオブジェクトが管理して消さないといけなかったので、
		　初期化時のパラメーターで寿命を与えて勝手に死んでくれるようにしました。

外部ライブラリ(物理エンジン)
	・BulletCollision
	・BulletDynamics
	・BulletSoftBody
	・LinerMath




		


		
		