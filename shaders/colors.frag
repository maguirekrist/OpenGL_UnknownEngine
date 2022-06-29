#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

in vec3 Normal;
in vec3 FragPos;

uniform sampler2D aTexture;
uniform vec4 lightSource;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec4 aColor;

void main()
{
    float ambientStrength = 0.1;
    float specularStrength = 1.0;
    
    vec4 ambient = ambientStrength * lightSource;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec4 specular = specularStrength * spec * lightSource;
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightSource;
    FragColor = texture(aTexture, TexCoord) * (diffuse + ambient + specular) * aColor;
}
