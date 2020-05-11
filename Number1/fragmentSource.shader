#version 330 core   
//Attribute:每个顶点值都不一样
//Uniform:每个顶点值都一样       
//in vec4 vertexColor;         
//uniform vec4 ourColor;

       
out vec4 FragColor;
in vec2 TexCoord; 

in vec3 FragPos;
in vec3 Normal;  
 
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

	float specularAmount=pow(max(dot(reflectVec,cameraVec),0.0),64);
	vec3 specularColor=specularAmount*lightColor;

	vec3 diffuseColor=max(dot(lightDir,Normal),0.0)*lightColor;             
    //FragColor = vertexColor;
	FragColor = (texture(ourTexture,TexCoord) * texture(ourFace,TexCoord)) * vec4((ambientColor+20.0*diffuseColor+10.0*specularColor)*objColor,1.0);
	//FragColor=vec4(objColor*ambientColor,1.0);
}