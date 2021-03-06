//******************************************************************************
// モデルの階層構造の処理 [model_hierarchy.cpp]
// Author : 管原司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model_hierarchy.h"
//******************************************************************************
// インクルードファイル
//******************************************************************************
#define MODEL_PARENT	(-1)	// モデル毎の親
//******************************************************************************
// インクリメント
//******************************************************************************
CModelhierarchy::CModelhierarchy(int nPriority) :CScene3d(nPriority)
{
	// パーツの最大数分回す
	for (int nCount = INIT_INT; nCount < MAX_PARTS; nCount++)
	{
		m_Model[nCount].m_pMeshParts = NULL;
		m_Model[nCount].m_pBuffMatParts = NULL;
		m_Model[nCount].m_nNumMatParts = NULL;

		m_modelParent[nCount].m_pos = INIT_D3DXVECTOR3;
		m_modelParent[nCount].m_rot = INIT_D3DXVECTOR3;
	}
	m_pos = INIT_D3DXVECTOR3;
	m_rot = INIT_D3DXVECTOR3;
	m_nNumModel = INIT_INT;
}

//******************************************************************************
// デクリメント
//******************************************************************************
CModelhierarchy::~CModelhierarchy()
{

}
//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT CModelhierarchy::Init(void)
{

	return S_OK;
}
//******************************************************************************
// 終了処理
//******************************************************************************
void CModelhierarchy::Uninit(void)
{
	CScene3d::Uninit();
}
//******************************************************************************
// 更新処理
//******************************************************************************
void CModelhierarchy::Update(void)
{

}
//******************************************************************************
// 描画処理
//******************************************************************************
void CModelhierarchy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL*pMat;

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// モデルパーツ分
	for (int nCount = INIT_INT; nCount < m_nNumModel; nCount++)
	{
		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&m_Model[nCount].m_mtxWorldParts);

		//向きを反転
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_modelParent[nCount].m_rot.y, m_modelParent[nCount].m_rot.x, m_modelParent[nCount].m_rot.z);
		D3DXMatrixMultiply(&m_Model[nCount].m_mtxWorldParts, &m_Model[nCount].m_mtxWorldParts, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_modelParent[nCount].m_pos.x, m_modelParent[nCount].m_pos.y, m_modelParent[nCount].m_pos.z);
		D3DXMatrixMultiply(&m_Model[nCount].m_mtxWorldParts, &m_Model[nCount].m_mtxWorldParts, &mtxTrans);

		if (m_Model[nCount].m_pBuffMatParts != NULL)
		{
			//マテリアルデータへのポインタを取得する
			pMat = (D3DXMATERIAL*)m_Model[nCount].m_pBuffMatParts->GetBufferPointer();
		}

		D3DXMATRIX mtxParent;

		if (m_Model[nCount].m_nldxModelParent == MODEL_PARENT)
		{
			mtxParent = m_mtxWorld;
		}
		else
		{
			mtxParent = m_Model[m_Model[nCount].m_nldxModelParent].m_mtxWorldParts;
		}

		//モデルパーツに親のマトリックスを掛け合わせることで、位置や回転を親に追従させる
		D3DXMatrixMultiply(&m_Model[nCount].m_mtxWorldParts, &m_Model[nCount].m_mtxWorldParts, &mtxParent);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_Model[nCount].m_mtxWorldParts);

		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);

		for (int nCntMat = INIT_INT; nCntMat < (int)m_Model[nCount].m_nNumMatParts; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// 色
			pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

			if (m_Model[nCount].m_pMeshParts != NULL)
			{
				//モデルパーツの描画
				m_Model[nCount].m_pMeshParts->DrawSubset(nCntMat);
			}
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//******************************************************************************
// モデルのテクスチャ設定
//******************************************************************************
void CModelhierarchy::BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat, int nldxModelParent)
{
	// メッシュ、マテリアル情報のポインタ、マテリアル情報の数、親モデルのインデックスのバインド
	m_Model[m_nNumModel].m_pMeshParts = pMesh;
	m_Model[m_nNumModel].m_pBuffMatParts = pBuffMat;
	m_Model[m_nNumModel].m_nNumMatParts = nNumMat;
	m_Model[m_nNumModel].m_nldxModelParent = nldxModelParent;

	// モデルのパーツ分加算
	m_nNumModel++;
}

//******************************************************************************
// モデルの場所、角度設定
//******************************************************************************
void CModelhierarchy::SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;
}

//******************************************************************************
// 各モデルパーツの場所、角度設定
//******************************************************************************
void CModelhierarchy::SetModelParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCount)
{
	m_modelParent[nCount].m_pos = pos;
	m_modelParent[nCount].m_rot = rot;
}