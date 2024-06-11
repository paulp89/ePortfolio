#version 330 core
//color & texture
in vec4 vertexColor;
in vec2 tc;
uniform sampler2D tex;

//lightning
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 lightPos2; 

out vec4 FragColor;
void main(){
		// ambient
		float ambientStrength = 0.3;
		vec3 ambient = ambientStrength * objectColor;

		// diffuse 
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor;

		// specular
		float specularStrength = 1.0;
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * lightColor;  

		//light 2
		vec3 lightDir2 =  normalize(lightPos2 - FragPos);
		float diff2 = max(dot(norm, lightDir2), 0.0);
		vec3 secondColor = vec3(0.5f,0.5f, 0.5f );
		vec3 light2 = diff2 * secondColor;
	
		vec3 result = (ambient + diffuse + specular + light2 ) * objectColor;
		FragColor = vec4(result, 1.0) * texture(tex, tc);
}