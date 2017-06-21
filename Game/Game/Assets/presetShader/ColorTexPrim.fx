/*!
 *@brief	カラーテクスチャプリミティブ。
 */

float4x4	g_mWVP;		//ワールドビュープロジェクション行列。

struct VS_INPUT{
	float4	pos		: POSITION;
	float2	uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4 pos		: POSITION;
	float2	uv		: TEXCOORD0;
	float4 screenPos : TEXCOORD1;
};
float g_brightness;
float g_alpha;			//!<アルファ
float3 g_mulColor;		//!<乗算カラー。
texture g_texture;		//ディフューズテクスチャ。
float4 g_uv;
sampler g_textureSampler = 
sampler_state
{
	Texture = <g_texture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Wrap;
	AddressV = Wrap;
};

texture g_depthTexture;	//深度テクスチャ。
sampler g_depthSampler =
sampler_state
{
	Texture = <g_depthTexture>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = mul(In.pos, g_mWVP);
	Out.screenPos = Out.pos;
	Out.uv = In.uv;
	return Out;
}
/*!
 * @brief	半透明合成用のピクセルシェーダー。
 */
float4 PSMainTrans( VS_OUTPUT In ) : COLOR0
{
	float4 tex = tex2D(g_textureSampler, In.uv);
	return float4(tex.xyz * g_mulColor, tex.a * g_alpha );
}
/*!
 * @brief	加算合成用のピクセルシェーダー。
 */
float4 PSMainAdd( VS_OUTPUT In ) : COLOR0
{
	float4 tex = tex2D(g_textureSampler, In.uv);
	return float4(tex.xyz * g_alpha, 1.0f );
}

/*!
* @brief	加算合成用のソフトパーティクルピクセルシェーダー。
*/
float4 PSMainSoftAdd(VS_OUTPUT In) : COLOR0
{
	float4 tex = tex2D(g_textureSampler, In.uv);
	float4 position = In.screenPos;
	position.x /= position.w;
	position.y /= position.w;
	position.x *= 0.5f;
	position.y *= -0.5f;
	position.x += 0.5f;
	position.y += 0.5f;

	//画面分割したときの補正
	position.x *= abs(g_uv.z - g_uv.x) / 2;
	position.x += (g_uv.x + 1.0f) / 2;
	position.y *= abs(g_uv.w - g_uv.y) / 2;
	position.y += (g_uv.y + 1.0f) / 2;
	float zBuffer = In.screenPos.w;
	float depthTex = tex2D(g_depthSampler, position.xy).r;
	float diff = min(abs(depthTex - zBuffer), 2.0f);
	float alpha = diff / 2.0f;
	//alpha = pow(alpha, 5);
	return float4(tex.xyz * g_alpha, alpha);
}

/*!
* @brief	半透明合成用のソフトパーティクルピクセルシェーダー。
*/
float4 PSMainSoftTrans(VS_OUTPUT In) : COLOR0
{
	float4 tex = tex2D(g_textureSampler, In.uv);
	float4 position = In.screenPos;
	position.x /= position.w;
	position.y /= position.w;
	position.x *= 0.5f;
	position.y *= -0.5f;
	position.x += 0.5f;
	position.y += 0.5f;

	//画面分割したときの補正
	position.x *= abs(g_uv.z - g_uv.x) / 2;
	position.x += (g_uv.x + 1.0f) / 2;
	position.y *= abs(g_uv.w - g_uv.y) / 2;
	position.y += (g_uv.y + 1.0f) / 2;
	float zBuffer = In.screenPos.w;
	float depthTex = tex2D(g_depthSampler, position.xy).r;
	float diff = min(abs(depthTex - zBuffer), 2.0f);
	float alpha = diff / 2.0f;
	//alpha = pow(alpha, 5);
	tex.a *= alpha;
	return float4(tex.xyz * g_mulColor, tex.a * g_alpha);
}

/*!
 * @brief	半透明合成用のテクニック。
 */
technique ColorTexPrimTrans
{
	pass P0
    {          
        VertexShader = compile vs_3_0 VSMain();
        PixelShader  = compile ps_3_0 PSMainTrans();
    }
}
/*!
 * @brief	加算用テクニック。
 */
technique ColorTexPrimAdd
{
    pass P0
    {          
        VertexShader = compile vs_3_0 VSMain();
        PixelShader  = compile ps_3_0 PSMainAdd();
    }
}
/*!
* @brief	半透明合成用のソフトパーティクルテクニック。
*/
technique SoftTransParticle
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMainSoftTrans();
	}
}

/*!
* @brief	半透明合成用のソフトパーティクルテクニック。
*/
technique SoftAddParticle
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMainSoftAdd();
	}
}