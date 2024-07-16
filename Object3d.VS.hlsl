

struct TrsnsformationMatrix
{
    float32_t4x4 WVP;
};
ConstantBuffer<TrsnsformationMatrix> gTransformationMatrix : register(b0);

struct VertexShaderShaderOutput
{
    float32_t4 position : SV_POSITION;
};

struct VertexShaderShaderInput
{
    float32_t4 position : POSITION0;
};

VertexShaderShaderOutput main(VertexShaderShaderInput input)
{
    VertexShaderShaderOutput output;
    output.position = mul(input.position, gTransformationMatrix.WVP);
    return output;
    
}





