#version 330 core                                        
layout(location = 0) in vec3 aPos;                       
//layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord; 
layout(location=3) in vec3 aNormal;   

//uniform mat4 transform;
uniform mat4 modelMat2;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat4 model;
                   
out vec4 vertexColor; 
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;                                   
void main() {
        //这里是有顺序的
		mat4 modelMat=modelMat2*model;	                                            
		gl_Position = projMat*viewMat*modelMat*vec4(aPos,1.0); 
		FragPos=(modelMat*vec4(aPos.xyz,1.0)).xyz;
		Normal=mat3(transpose(inverse(modelMat)))*aNormal;                   
       //vertexColor=vec4(aColor.x,aColor.y,aColor.z,1.0); 
	   TexCoord=aTexCoord;
}    