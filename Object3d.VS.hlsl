

struct VertexShaderShaderOutput
{
    float32_t4 position : SV_POSITION;
};

struct VertexShaderShaderInput
{
    float32_t4 position : POSITION0;
};

VertexShaderShaderOutput main(VertexShaderShaderInput inpurt)
{
    VertexShaderShaderOutput output;
    output.position = input.position;
    return output;
    
}





