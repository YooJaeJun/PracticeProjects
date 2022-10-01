
struct VertexInput
{
	// GPU�� 16����Ʈ�� �д´�. float 4����Ʈ * 4
    float4 position : POSITION0; //�ø�ƽ -> �뵵
    float4 color : COLOR0;
};
// PI
struct PixelInput
{
    float4 position : SV_POSITION; //ȭ����ǥ�� ������
    float4 color : COLOR0;
};

//������Ʈ�� ũ�� ȸ�� �̵�
cbuffer VS_WVP : register(b0) //register(b0)
{
    matrix WVP;
}
cbuffer VS_COLOR : register(b1)
{
    //4 ���� 4����Ʈ
    float4 color;
}

cbuffer PS_LIGHT : register(b0)
{
	float2 screenPos; //��ũ����ǥ
	float radius; //������ũ��
	float select; //���°�
	float4 lightColor; //���� ��
	float4 outColor; //�ܰ� ��
};

PixelInput VS(VertexInput input)
{
    //������ȯ�� ���� ������ ��
    PixelInput output;
    
    output.position = mul(input.position, WVP);
	// �׶��̼� ȿ���� ���� ���Ϳ��� �� ���� ���� �κ��� ���͸� �� �۰�, �ٸ� �κ��� ���͸� �� ũ��
    output.color = input.color + (color * 2.0f - 1.0f);
	// saturate: 1���� ũ�� 1, 0���� ������ 0, ���հ��� �״��.
    saturate(output.color); 
    return output;
}

//->pixel  PS   ->color
//�ȼ����̴� ���� �Լ�
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET �� Ÿ���̵� ���� 
{
	float4 outputColor;
	outputColor = saturate(input.color);
    
	float2 minus = input.position.xy - screenPos;
	float dis = minus.x * minus.x + minus.y * minus.y;
	dis = sqrt(dis);
    
	if (select == 0.0f)
	{
		if (dis > radius)
		{
			outputColor.rgb += (outColor.rgb * 2.0f - 1.0f);
		}
		else
		{
			outputColor.rgb += (lightColor.rgb * 2.0f - 1.0f);
		}
	}
	else
	{
		float temp = 1.0f - saturate(dis / radius);
		outputColor.rgb += (lightColor.rgb * 2.0f - 1.0f);
		outputColor.rgb *= temp;
	}
	outputColor = saturate(outputColor);
    
	return outputColor;
	}