[shader("fragment")]
float4 fragMain() : SV_Target
{
  return float4(0.1, 0.2, 0.3, 1);
}

[shader("vertex")]
float4 vertMain(float3 pos)
{
  return float4(pos, 1.0);
}
