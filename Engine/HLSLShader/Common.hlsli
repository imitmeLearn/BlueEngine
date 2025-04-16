//Lambert cosine law.
float CalcLambert(float3 worldNormal, float3 lightDirection)
{
    return saturate(dot(worldNormal, -lightDirection));
}

//Half Lambert.
float CalcHalfLambert(
    float3 worldNormal
    , float3 lightDirection
    , float param =2)
{
    float nDotL = CalcLambert(worldNormal,lightDirection);
    return pow(nDotL * 0.5f + 0.5f ,param);
}

//Phong
float CalcPhong(
    float3 worldNormal
    ,float3 lightDirection
    ,float3 cameraDirection
    ,float shineness  = 16.f
)
{
    float nDotl = CalcLambert(worldNormal, lightDirection);
    float specular = 0;
	if(nDotl)
	{
		float3 reflection = reflect(lightDirection, worldNormal);
		float3 viewDirection = normalize(cameraDirection);
		float 	rDotv = dot(reflection, -viewDirection);
				rDotv = saturate(rDotv);
		specular = pow(rDotv,shineness);
	}

    return specular;
}

float CalcBlinnPhong(
    float3 worldNormal
    ,float3 lightDirection
    ,float3 cameraDirection
    ,float shineness  = 32.f
)
{
    float NoL = CalcLambert(worldNormal, lightDirection);

	float specular = 0;
	if(NoL > 0)
	{
		//	half vector
		float3 viewDirection = normalize(cameraDirection);
		float3 halfVector = normalize ((-lightDirection)+(-viewDirection));

		//nDoth
		float NoH =saturate(dot(worldNormal, halfVector));
		float shineness =32.f;
		specular = pow(NoH, shineness);
	}

    return specular;

}