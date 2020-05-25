#version 330 core   
//Attribute:每个顶点值都不一样
//Uniform:每个顶点值都一样       
//in vec4 vertexColor;         
//uniform vec4 ourColor;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;

	sampler2D diffuseMap;
	sampler2D specularMap;
	sampler2D emissionMap;
};

struct LightDirectional{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};

struct LightPoint{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;

	float constant;
	float linear;
	float quadratic;
};

struct LightSpot{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;

	float constant;
	float linear;
	float quadratic;

	float cosPhyInner;
	float cosPhyOutter;
};

      
out vec4 FragColor;

in vec2 TexCoord; 
in vec3 FragPos;
in vec3 Normal;  

uniform Material material;


uniform sampler2D ourTexture;
uniform sampler2D ourFace;      
uniform vec3 objColor;
uniform vec3 ambientColor;
//uniform vec3 lightPos;
//uniform vec3 lightColor;
//uniform vec3 lightDirUniform;
uniform vec3 cameraPos;

uniform LightDirectional lightD;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;

vec3 CalculateLightDirectional(LightDirectional _light, vec3 _uNormal,vec3 _dirtocamera)
{
	//Ambient
	vec3 ambientColorFinal=material.ambient*ambientColor*texture(material.diffuseMap,TexCoord).rgb;
	
	//DIFFUSE
	float diffuseIntensity=max(dot(_light.dirToLight,_uNormal),0);
	vec3 diffuseColor=diffuseIntensity*_light.color*texture(material.diffuseMap,TexCoord).rgb;
	//SPECULAR
	vec3 R=normalize(reflect(-_light.dirToLight,_uNormal));
	float specIntensity=pow(max(dot(R,_dirtocamera),0),material.shininess);
	vec3 specColor=specIntensity*_light.color*texture(material.specularMap,TexCoord).rgb;

	vec3 result=ambientColorFinal+diffuseColor+specColor;
	return result;
}

vec3 CalculateLightPoint(LightPoint _light, vec3 _uNormal,vec3 _dirtocamera)
{
	//attenuation
	float dist=length(_light.pos-FragPos);
	float attenuation=1.0/(_light.constant+_light.linear*dist+_light.quadratic*(dist*dist));

	//DIFFUSE
	float diffuseIntensity=max(dot(normalize(_light.pos-FragPos),_uNormal),0)*attenuation;
	vec3 diffuseColor=diffuseIntensity*_light.color*texture(material.diffuseMap,TexCoord).rgb;
	//SPECULAR
	vec3 R=normalize(reflect(normalize(FragPos-_light.pos),_uNormal));
	float specIntensity=pow(max(dot(R,_dirtocamera),0),material.shininess)*attenuation;
	vec3 specColor=specIntensity*_light.color*texture(material.specularMap,TexCoord).rgb;

	vec3 result=diffuseColor+specColor;
	return result;
}

vec3 CalculateLightSpot(LightSpot _light,vec3 _uNormal,vec3 _dirToCamera){
	float dist=length(_light.pos-FragPos);
	float attenuation=1.0/(_light.constant+_light.linear*dist+_light.quadratic*(dist*dist));
	float spotRatio;
	float CosTheta=dot(normalize(FragPos-_light.pos),-_light.dirToLight);

	if(CosTheta>_light.cosPhyInner)
	{
		spotRatio=1.0;
	}
	else if(CosTheta>_light.cosPhyOutter){

		spotRatio=1.0-(CosTheta-_light.cosPhyOutter)/(_light.cosPhyInner-_light.cosPhyOutter);
	}
	else
	{
		spotRatio=0;
	}
		
	
	

	//DIFFUSE
	float diffuseIntensity=max(dot(normalize(_light.pos-FragPos),_uNormal),0)*attenuation*spotRatio;
	vec3 diffuseColor=diffuseIntensity*_light.color*texture(material.diffuseMap,TexCoord).rgb;
	//SPECULAR
	vec3 R=normalize(reflect(normalize(FragPos-_light.pos),_uNormal));
	float specIntensity=pow(max(dot(R,_dirToCamera),0),material.shininess)*attenuation*spotRatio;
	vec3 specColor=specIntensity*_light.color*texture(material.specularMap,TexCoord).rgb;

	vec3 result=diffuseColor+specColor;
	return result;

}

void main() {
	vec3 finalResult;
	vec3 uNormal=normalize(Normal);
	vec3 dirToCamera=normalize(cameraPos-FragPos);
	
	finalResult+=CalculateLightDirectional(lightD,uNormal,dirToCamera);

	finalResult+=CalculateLightPoint(lightP0,uNormal,dirToCamera);
	finalResult+=CalculateLightPoint(lightP1,uNormal,dirToCamera);
	finalResult+=CalculateLightPoint(lightP2,uNormal,dirToCamera);
	finalResult+=CalculateLightPoint(lightP3,uNormal,dirToCamera);

	finalResult+=CalculateLightSpot(lightS,uNormal,dirToCamera);

	FragColor=vec4(finalResult,1.0);
	//FragColor=vec4(1.0,1.0,1.0,1.0);
}