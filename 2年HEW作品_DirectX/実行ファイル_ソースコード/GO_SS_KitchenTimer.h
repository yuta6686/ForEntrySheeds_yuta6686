#pragma once
#include "GameObject.h"


class GO_SS_KitchenTimer :
    public GameObject
{
private:
	static const int ADD_TIMER = 10;

	static const int KICHENTIMER_MAX = 30;
public:

	virtual void Initialize(void) override;
	virtual void Finalize(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	virtual int GetGameScene(void) override { return GAME_SCENE; }

	//	�L�b�`���^�C�}�[�̏��擾
	VERTEX_T* GetKitchenTimer(int index) { return &KitchenTimer_Vertex[index]; }

	//	�L�b�`���^�C�}�[�̍ő吔�擾
	int GetKichenTimerMax() { return KICHENTIMER_MAX; }

	//	�c�莞�ԑ��₷���
	int GetAddTimer(){ return ADD_TIMER; }

	//	Use�t���O�̃Z�b�^�[
	void SetUse(int index,bool flag) { KitchenTimer_Vertex[index].use = flag; }

	//	����
	void AddX(FLOAT x);

	void SetKTimer() {
		for (int i = 0; i < KICHENTIMER_MAX; i++) {
			if (KitchenTimer_Vertex[i].use == true)continue;
			KitchenTimer_Vertex[i].use = true;
			break;
		}
	}

	void SetKTimer(D3DXVECTOR2 pos) {
		for (int i = 0; i < KICHENTIMER_MAX; i++) {
			if (KitchenTimer_Vertex[i].use == true)continue;
			KitchenTimer_Vertex[i].pos = pos;
			KitchenTimer_Vertex[i].use = true;
			break;
		}
	}
private:

	int KitchenTimer_Texture;

	char KTIMER_TEX_NAME[128] = "data/TEXTURE/Timer.png";

	const int GAME_SCENE = GAMESCENE_GAME_TEST;

	VERTEX_T KitchenTimer_Vertex[KICHENTIMER_MAX];
};
