#pragma once
#include "WorldTransform.h"
#include"Model.h"
/// <summary>
/// �G
/// </summary>
class Enemy {
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const ViewProjection &viewProjection);
	
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldtransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�ڋ߃t�F�[�Y�̍X�V�֐�
	void UpdateApproach();
	//���E�t�F�[�Y�̍X�V�֐�
	void UpdateLeave();
};
