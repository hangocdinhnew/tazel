[shader("fragment")]
float4 fragMain(float4 pos:SV_Position) : SV_Target
{
  return pos;
}

[shader("vertex")]
float4 vertMain(float4 pos) : SV_Position
{
  return pos;
}
