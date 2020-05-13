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

struct LightPoint{
	float constant;
	float linear;
	float quadratic;
};

struct LightSpot{
	float cosPhy;
};

      
out vec4 FragColor;

in vec2 TexCoord; 
in vec3 FragPos;
in vec3 Normal;  

uniform Material material;
uniform LightPoint lightP;
uniform LightSpot lightS;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;      
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDirUniform;
uniform vec3 cameraPos;

void main() {
	
	vec3 lightDir=normalize(lightPos-FragPos);
	vec3 reflectVec=reflect(-lightDir,Normal);
	vec3 cameraVec=normalize(cameraPos-FragPos);
	
	//Point Light衰减函数
	//float dist=length(lightPos-FragPos);
	//float attenuation=1.0/(lightP.constant+lightP.linear*dist+lightP.quadratic*(dist*dist));

	//EmissionMap:
	vec3 emissionColor=texture(material.emissionMap,TexCoord).rgb;

	//specular Color and Specular Map:
	float specularAmount=pow(max(dot(reflectVec,cameraVec),0.0),material.shininess);
	//vec3 specularColor=material.specular*specularAmount*lightColor;
	vec3 spcularMapColor=texture(material.specularMap,TexCoord).rgb*specularAmount*lightColor;

	//diffuse Color and diffuse Map:
	//vec3 diffuseColor=material.diffuse*max(dot(lightDir,Normal),0.0)*lightColor;
	vec3 diffuseMapColor=texture(material.diffuseMap,TexCoord).rgb*max(dot(lightDir,Normal),0.0)*lightColor;
	             
    //FragColor = vertexColor;
	//ambient:
	vec3 ambient=material.ambient*ambientColor*texture(material.diffuseMap,TexCoord).rgb;

	float cosTheta=dot(normalize(FragPos-lightPos),-1*lightDirUniform);

	if(cosTheta>lightS.cosPhy)
	{
		//inside
		FragColor = vec4((ambient+diffuseMapColor+spcularMapColor)*objColor,1.0);

	}
	else{
		//outside
		FragColor = vec4((ambient)*objColor,1.0);
	}

	//加上贴图(texture(ourTexture,TexCoord) * texture(ourFace,TexCoord)) * 
	//加上自发光emissionColor+
	//FragColor = vec4((attenuation*(ambient+2*diffuseMapColor+spcularMapColor))*objColor,1.0);
	//FragColor=vec4(objColor*ambientColor,1.0);
}