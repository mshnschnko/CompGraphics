#include "Consts.h"

struct CubeGeomBuffer
{
    float4x4 worldMatrix;
    float4x4 norm;
    float4 cubeParams;
};

StructuredBuffer<CubeGeomBuffer> geomBuffers : register(t10);
StructuredBuffer<uint4> objectID : register(t11);

cbuffer SceneCB : register(b1)
{
    float4x4 viewProjectionMatrix;
    float4 planes[6];
    int4 drawMode; // x - current mode
};