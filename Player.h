#pragma once
#include "WorldTransform.h"
#include<Model.h>
#include"DebugText.h"
#include"Input.h"

/// <summary>
/// 自キャラ
/// </summary>

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);
	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();
	/// <summary>
	///描画
	/// </summary>
	void Draw(ViewProjection viewProjection);

private:
	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};