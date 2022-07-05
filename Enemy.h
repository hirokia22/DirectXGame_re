#pragma once
#include "WorldTransform.h"
#include"Model.h"
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

	//行動フェーズ
	enum class Phase {
		Approach,	//接近
		Leave,		//離脱
	};
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
};
