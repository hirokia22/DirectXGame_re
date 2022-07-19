#pragma once
#include "WorldTransform.h"
#include"Model.h"
#include"EnemyBullet.h"
#include<memory>
#include<list>

class Player;
/// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection &viewProjection);

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	//行動フェーズ
	enum class Phase {
		Approach,	//接近
		Leave,		//離脱
	};

	//接近フェーズ初期化関数
	void InitializeApproach();
	
	//発射間隔
	static const int kFireInterval = 60;
    
	void SetPlayer(Player* player) { player_ = player; }

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
	//弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullet() { return bullets_; }

	//弾の大きさ
	static const int kRadius = 1;
private:
	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//フェーズ
	Phase phase_ = Phase::Approach;
	//接近フェーズの更新関数
	void UpdateApproach();
	//離脱フェーズの更新関数
	void UpdateLeave();
	//弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	//発射タイマー
	int32_t fireTimer_ = 0;
	//自キャラ
	Player* player_ = nullptr;
};
