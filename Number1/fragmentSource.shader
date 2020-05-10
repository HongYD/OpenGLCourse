#version 330 core            
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

void main() {
	vec3 lightDir=normalize(lightPos-FragPos);
	vec3 diffuseColor=max(dot(lightDir,Normal),0.0)*lightColor;             
    //FragColor = vertexColor;
	FragColor = (texture(ourTexture,TexCoord) * texture(ourFace,TexCoord)) * vec4((10.0*ambientColor*diffuseColor)*objColor,1.0);
	//FragColor=vec4(objColor*ambientColor,1.0);
}