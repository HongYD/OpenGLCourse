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
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

void main() {
	
	vec3 lightDir=normalize(lightPos-FragPos);
	vec3 reflectVec=reflect(-lightDir,Normal);
	vec3 cameraVec=normalize(cameraPos-FragPos);

	//specular:
	float specularAmount=pow(max(dot(reflectVec,cameraVec),0.0),material.shininess);
	vec3 specularColor=material.specular*specularAmount*lightColor;

	//diffuse:
	vec3 diffuseColor=material.diffuse*max(dot(lightDir,Normal),0.0)*lightColor;
	             
    //FragColor = vertexColor;
	//ambient:
	vec3 ambient=material.ambient*ambientColor;

	FragColor = (texture(ourTexture,TexCoord) * texture(ourFace,TexCoord)) * vec4((ambient+10.0f*diffuseColor+80.0f*specularColor)*objColor,1.0);
	//FragColor=vec4(objColor*ambientColor,1.0);
}